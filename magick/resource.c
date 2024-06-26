/*
% Copyright (C) 2003 - 2023 GraphicsMagick Group
% Copyright (C) 2002 ImageMagick Studio
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%           RRRR    EEEEE   SSSSS   OOO   U   U  RRRR    CCCC  EEEEE          %
%           R   R   E       SS     O   O  U   U  R   R  C      E              %
%           RRRR    EEE      SSS   O   O  U   U  RRRR   C      EEE            %
%           R R     E          SS  O   O  U   U  R R    C      E              %
%           R  R    EEEEE   SSSSS   OOO    UUU   R  R    CCCC  EEEEE          %
%                                                                             %
%                                                                             %
%                        Get/Set ImageMagick Resources.                       %
%                                                                             %
%                                                                             %
%                              Software Design                                %
%                                John Cristy                                  %
%                               September 2002                                %
%                                                                             %
%                            Completely Re-written                            %
%                               Bob Friesenhahn                               %
%                                 April 2008                                  %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/log.h"
#include "magick/resource.h"
#include "magick/semaphore.h"
#include "magick/utility.h"

/*
  Define  declarations.
*/
/* #define MagickResourceInfinity ((magick_int64_t) (~((magick_uint64_t) 0) >> 1)) */
#define ResourceInfoMaxIndex ((unsigned int) (sizeof(resource_info)/sizeof(resource_info[0])-1))

/*
  Typedef declarations.
*/
typedef enum
{
  AbsoluteLimit,
  SummationLimit
} LimitType;

/*
  Definition of a resource.  We intentionally use signed types to
  store 'value' and 'limit'.
*/
typedef struct _ResourceInfo
{
  const char
    name[8],
    units[2],
    env[20];

  magick_int64_t
    value;

  magick_int64_t
    minimum,
    maximum,
    highwater;

  LimitType
    limit_type;

  SemaphoreInfo
    *semaphore;

} ResourceInfo;

/*
  Global declarations.
*/

/*
  Array must be in same order as ResourceType enum
*/
#define PIXEL_LIMIT (INT_MAX/(sizeof(PixelPacket)))
static ResourceInfo resource_info[] =
  {
   { "",       "",  "",                    0, 0,    MagickResourceInfinity, 0, AbsoluteLimit, 0  },
   { "disk",   "B", "MAGICK_LIMIT_DISK",   0, 0,    MagickResourceInfinity, 0, SummationLimit, 0 },
   { "files",  "",  "MAGICK_LIMIT_FILES",  0, 32,   256,                    0, SummationLimit, 0 },
   { "map",    "B", "MAGICK_LIMIT_MAP",    0, 0,    MagickResourceInfinity, 0, SummationLimit, 0 },
   { "memory", "B", "MAGICK_LIMIT_MEMORY", 0, 0,    MagickResourceInfinity, 0, SummationLimit, 0 },
   { "pixels", "P", "MAGICK_LIMIT_PIXELS", 0, 1,    MagickResourceInfinity, 0, AbsoluteLimit, 0  },
   { "threads", "", "OMP_NUM_THREADS",     1, 1,    MagickResourceInfinity, 0, AbsoluteLimit, 0  },
   { "width",  "P", "MAGICK_LIMIT_WIDTH",  0, 1,    PIXEL_LIMIT,            0, AbsoluteLimit, 0  },
   { "height", "P", "MAGICK_LIMIT_HEIGHT", 0, 1,    PIXEL_LIMIT,            0, AbsoluteLimit, 0  },
   { "read",   "B", "MAGICK_LIMIT_READ",   0, 4096, MagickResourceInfinity, 0, AbsoluteLimit, 0  },
   { "write",  "B", "MAGICK_LIMIT_WRITE",  0, 4096, MagickResourceInfinity, 0, AbsoluteLimit, 0  }
  };

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   A c q u i r e M a g i c k R e s o u r c e                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  AcquireMagickResource() acquires resources of the specified type.  True is
%  returned if the specified resource is available otherwise False.
%
%  The format of the AcquireMagickResource() method is:
%
%      MagickPassFail AcquireMagickResource(const ResourceType type,
%        const magick_int64_t size)
%
%  A description of each parameter follows:
%
%    o type: The type of resource.
%
%    o size: The number of bytes needed from for this resource.
%
%
*/
static ResourceInfo *GetResourceInfo(const ResourceType type)
{
  ResourceInfo
    *info;

  unsigned int
    index;

  info = (ResourceInfo *) NULL;
  index = type;
  if ((index != 0) && (index <= ResourceInfoMaxIndex))
    info = &resource_info[index];

  return info;
}

MagickExport MagickPassFail
AcquireMagickResource(const ResourceType type,
                      const magick_uint64_t size)
{
  ResourceInfo
    *info;

  MagickPassFail
    status;

  status=MagickPass;

  if ((info=GetResourceInfo(type)))
    {
      magick_uint64_t
        value=0;

      switch(info->limit_type)
        {
        case AbsoluteLimit:
          {
            /*
              Limit depends only on the currently requested size.
            */
            value=info->value;
            if ((info->maximum != MagickResourceInfinity) &&
                (size > (magick_uint64_t) info->maximum))
              {
                status=MagickFail;
              }
            else
              {
                LockSemaphoreInfo(info->semaphore);
                if (size > (magick_uint64_t) info->highwater)
                  info->highwater = size;
                UnlockSemaphoreInfo(info->semaphore);
              }
            break;
          }
        case SummationLimit:
          {
            /*
              Limit depends on sum of previous allocations as well as
              the currently requested size.
            */
            LockSemaphoreInfo(info->semaphore);
            value=info->value+size;
            if ((info->maximum != MagickResourceInfinity) &&
                (value > (magick_uint64_t) info->maximum))
              {
                value=info->value;
                status=MagickFail;
              }
            else
              {
                info->value=value;
                if (value > (magick_uint64_t) info->highwater)
                  info->highwater = value;
              }
            UnlockSemaphoreInfo(info->semaphore);
            break;
          }
        }
      if (IsEventLogged(ResourceEvent))
        {
          char
            f_limit[MaxTextExtent],
            f_size[MaxTextExtent],
            f_value[MaxTextExtent];

          if (info->maximum == MagickResourceInfinity)
            {
              strlcpy(f_limit,"Unlimited",sizeof(f_limit));
            }
          else
            {
              FormatSize(info->maximum, f_limit);
              strlcat(f_limit,info->units,sizeof(f_limit));
            }

          FormatSize(size, f_size);
          strlcat(f_size,info->units,sizeof(f_size));

          if (info->limit_type == AbsoluteLimit)
            {
              strlcpy(f_value,"----",sizeof(f_value));
            }
          else
            {
              FormatSize(value, f_value);
              strlcat(f_value,info->units,sizeof(f_value));
            }

          (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                                "%s %s%s/%s/%s",
                                info->name,
                                (status ? "+" : "!"),
                                f_size,
                                f_value,
                                f_limit);
        }
    }

  return(status);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   D e s t r o y M a g i c k R e s o u r c e s                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DestroyMagickResources() destroys the resource environment.
%
%  The format of the DestroyMagickResources() method is:
%
%      DestroyMagickResources(void)
%
%
*/
MagickExport void DestroyMagickResources(void)
{
  size_t
    index;

  if (IsEventLogged(ResourceEvent))
    {
#if 0
      const ResourceInfo *disc_info = GetResourceInfo(DiskResource);
      const ResourceInfo *file_info = GetResourceInfo(FileResource);
      const ResourceInfo *map_info = GetResourceInfo(MapResource);
      const ResourceInfo *memory_info = GetResourceInfo(MemoryResource);

      (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                            "Resource Consumption Summary\n"
                            "    %c%s Limit: %"MAGICK_INT64_F"d, Maximum Used: %"MAGICK_INT64_F"d\n"
                            "    %c%s Limit: %"MAGICK_INT64_F"d, Maximum Used: %"MAGICK_INT64_F"d\n"
                            "    %c%s Limit: %"MAGICK_INT64_F"d, Maximum Used: %"MAGICK_INT64_F"d\n"
                            "    %c%s Limit: %"MAGICK_INT64_F"d, Maximum Used: %"MAGICK_INT64_F"d",
                            toupper((int) disc_info->name[0]),disc_info->name+1, disc_info->maximum, (magick_int64_t) disc_info->highwater,
                            toupper((int) file_info->name[0]),file_info->name+1, file_info->maximum, (magick_int64_t) file_info->highwater,
                            toupper((int) map_info->name[0]),file_info->name+1, map_info->maximum, (magick_int64_t) map_info->highwater,
                            toupper((int) memory_info->name[0]),memory_info->name+1, map_info->maximum, (magick_int64_t) memory_info->highwater
                            );
#endif
#if 1
      const ResourceInfo *info;
      for (index = 1; index < ArraySize(resource_info); index++)
        {
          info=&resource_info[index];
          if (info->limit_type != SummationLimit && info->highwater == 0)
            continue;
          LockSemaphoreInfo(info->semaphore);
          (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                                "Resource - %c%s Limit: %"MAGICK_INT64_F"d,"
                                " Maximum Used: %"MAGICK_INT64_F"d",
                                toupper((int) info->name[0]),info->name+1,
                                info->maximum, (magick_int64_t) info->highwater);
          UnlockSemaphoreInfo(info->semaphore);
        }
#endif
    }

#if defined(DEBUG_MAGICK_RESOURCES) && DEBUG_MAGICK_RESOURCES
  {
    const ResourceInfo *info;

    for (index = 1; index < ArraySize(resource_info); index++)
      {
        info=&resource_info[index];
        if (info->limit_type != SummationLimit)
          continue;
        LockSemaphoreInfo(info->semaphore);
        if (info->value != 0)
          {
            fprintf(stderr,"Resource[%s] %s! %"MAGICK_INT64_F"d remaining\n",
                    info->name, info->value < 0 ? "underflow" : "leak",
                    (magick_int64_t) info->value);
            assert(info->value == 0);
          }
        UnlockSemaphoreInfo(info->semaphore);
      }
  }
#endif /* if defined(DEBUG_MAGICK_RESOURCES) && DEBUG_MAGICK_RESOURCES */

  for (index = 1; index < ArraySize(resource_info); index++)
    DestroySemaphoreInfo(&resource_info[index].semaphore);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t M a g i c k R e s o u r c e                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetMagickResource() returns the current consumption level for the
%  specified resource type.
%
%  The format of the GetMagickResource() method is:
%
%      magick_uint64_t GetMagickResource(const ResourceType type)
%
%  A description of each parameter follows:
%
%    o type: The type of resource.
%
%
*/
MagickExport magick_int64_t GetMagickResource(const ResourceType type)
{
  ResourceInfo
    *info;

  magick_int64_t
    resource;

  resource=0;

  if ((info=GetResourceInfo(type)))
    {
      LockSemaphoreInfo(info->semaphore);
      resource=info->value;
      UnlockSemaphoreInfo(info->semaphore);
    }

  return(resource);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t M a g i c k R e s o u r c e L i m i t                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetMagickResourceLimit() returns the current maximum limit for the
%  specified resource type.  Returns a maximum 64-bit integer value if
%  the resource has not been limited.
%
%  The format of the GetMagickResourceLimit() method is:
%
%      magick_int64_t GetMagickResourceLimit(const ResourceType type)
%
%  A description of each parameter follows:
%
%    o type: The type of resource.
%
%
*/
MagickExport magick_int64_t GetMagickResourceLimit(const ResourceType type)
{
  ResourceInfo
    *info;

  magick_int64_t
    resource;

  resource=0;

  if ((info=GetResourceInfo(type)))
    {
      LockSemaphoreInfo(info->semaphore);
      resource=info->maximum;
      UnlockSemaphoreInfo(info->semaphore);
    }

  return(resource);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   I n i t i a l i z e M a g i c k R e s o u r c e s                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  InitializeMagickResources() initializes the resource environment.
%
%  The format of the InitializeMagickResources() method is:
%
%      InitializeMagickResources(void)
%
%
*/
MagickExport void InitializeMagickResources(void)
{
  magick_int64_t
    max_disk=-1,
    max_files=256,
    max_map=4096,
    max_memory=1024,
    max_pixels=-1,
    max_threads=1,
    max_width=-1,
    max_height=-1,
    max_read=-1,
    max_write=-1;

  size_t
    index;

  /*
    Allocate semaphores.
  */
  for (index = 1; index < ArraySize(resource_info); index++)
    resource_info[index].semaphore=AllocateSemaphoreInfo();

  /*
    Set Magick resource limits.
  */
#if defined(POSIX)
  {
    unsigned long
      total_memory=0;

#  if  defined(HAVE_SYSCONF) && defined(_SC_PHYS_PAGES)
    {
      long
        pagesize=-1,
        pages=-1;
      /*
        Compute total physical memory based on number of memory pages,
        and page size.
      */
      pages=sysconf(_SC_PHYS_PAGES);
      pagesize = MagickGetMMUPageSize();

      if (pages > 0 && pagesize > 0)
        total_memory=((pages+512)/1024)*((pagesize+512)/1024);
      (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                            "Total physical memory %ld MB (%ld pages and %ld bytes per page)",
                            total_memory, pages, pagesize);
    }
#  elif defined(MAGICK_PHYSICAL_MEMORY_COMMAND) && defined(HAVE_POPEN)
    {
      double
        bytes=0;

      FILE
        *command;
      /*
        Execute the external command defined by
        MAGICK_PHYSICAL_MEMORY_COMMAND to obtain the total physical
        memory in bytes.  This external command should be quite speedy
        or else it will impact the time to start GraphicsMagick.
      */
      if ((command = popen(MAGICK_PHYSICAL_MEMORY_COMMAND, "r")) != NULL)
        {
          if (fscanf(command,"%lf",&bytes) == 1)
            total_memory=(bytes/(1024*1024));
          (void) pclose(command);
          (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                                "Total physical memory %ld MB",total_memory);
        }
    }
#  endif

    if (total_memory > 0)
      {
        /*
          We are not able to use more than size_t worth of address
          space.  On 32 bit systems, we can usually only use half or
          three quarters of it.  Regardless, we need address space
          for more than just image data.
        */
        size_t
          size_t_max = (size_t) ~0UL;

        size_t_max /= (1024U*1024U);
        max_memory = Min(size_t_max/2-100,total_memory);
        max_map = Min(size_t_max/2-100,2*total_memory);
      }
  }
#endif /* defined(POSIX) */

#if defined(MSWINDOWS)
  {
    long
      total_physical_memory=0,
      total_virtual_memory=0;

    /*
      GlobalMemoryStatusEx is necessary to handle results for
      large-memory (>4GB) machines (and to provide accurate results
      for 2 to 4 GB of memory), but it is not available on older
      versions of Windows.  Windows 32-bit applications are still
      usually limited to addressing only 2 GB of memory even if the
      system provides more (except for certain server versions of
      Windows with applications linked with the /LARGEADDRESSAWARE
      option). Test for API existence prior to using it.  MinGW
      headers currently lack support for this API so compilation of
      supportive code is made optional.
    */
#if defined(HAVE_GLOBALMEMORYSTATUSEX)
    if (NTKernelAPISupported("GlobalMemoryStatusEx"))
      {
        MEMORYSTATUSEX
          stat_ex;

        (void) memset(&stat_ex,0,sizeof(stat_ex));
        stat_ex.dwLength=sizeof(stat_ex);
        if (GlobalMemoryStatusEx(&stat_ex))
          {
            total_physical_memory=(long)(stat_ex.ullTotalPhys/1048576UL);
            total_virtual_memory=(long)(stat_ex.ullTotalVirtual/1048576UL);
          }
        else
          {
            (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                                  "GlobalMemoryStatusEx() call failed! (error %ld)",GetLastError());
          }
      }
#endif

    if (total_physical_memory == 0)
      {
        MEMORYSTATUS
          stat;

        GlobalMemoryStatus(&stat);
        total_physical_memory=stat.dwTotalPhys/1048576;
        total_virtual_memory=stat.dwTotalVirtual/1048576;
      }
    (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                          "Total physical memory %ld MB, Total virtual memory %ld MB",
                          total_physical_memory, total_virtual_memory);

    max_memory=Min(total_physical_memory,total_virtual_memory);
    /*
      We will default to using at most 80% of available memory for image data.
    */
    max_memory=(long)(0.8*max_memory);
    /*
      Use the maximum memory as our default memory map limit.  Memory
      mapping files larger than available RAM can cause VM thrashing.
      This implies that memory mapping won't get used much.  However,
      it is possible for heap memory allocations to fail (due to heap
      fragmentation) whereas memory mapping still succeeds.
    */
    max_map=max_memory;

    /*
      Windows lowio level supports up to 2048 open files.
      Reserve 512 handles for other uses.
    */
    max_files=2048-512;
  }
#endif /* defined(MSWINDOWS) */

  /*
    Compute fundamental limits based on build parameters.  Image size
    is fundamentally limited by how many pixels may reside in one row.
  */
  if (sizeof(size_t) == 4)
    max_pixels=(magick_int64_t) ((unsigned long) ULONG_MAX/(5*sizeof(Quantum)));


  /*
    Disk, map, and memory are in units of MB and need to be scaled up.
  */
  /* if (max_disk > 0) */
  /*   max_disk  *= 1024UL*1024UL; */
  if (max_map > 0)
    max_map   *= 1024UL*1024UL;
  if (max_memory > 0)
    max_memory *= 1024UL*1024UL;

  /*
    Support using environment variables to set limits
  */
  {
    const char
      *envp;

    if ((envp=getenv("MAGICK_LIMIT_DISK")))
      max_disk=MagickSizeStrToInt64(envp,1024);

    if ((envp=getenv("MAGICK_LIMIT_FILES")))
      max_files=MagickSizeStrToInt64(envp,1024);

    if ((envp=getenv("MAGICK_LIMIT_MAP")))
      max_map=MagickSizeStrToInt64(envp,1024);

    if ((envp=getenv("MAGICK_LIMIT_MEMORY")))
      max_memory=MagickSizeStrToInt64(envp,1024);

    if ((envp=getenv("MAGICK_LIMIT_PIXELS")))
      max_pixels=MagickSizeStrToInt64(envp,1024);

    if ((envp=getenv("MAGICK_LIMIT_WIDTH")))
      max_width=MagickSizeStrToInt64(envp,1024);

    if ((envp=getenv("MAGICK_LIMIT_HEIGHT")))
      max_height=MagickSizeStrToInt64(envp,1024);

    if ((envp=getenv("MAGICK_LIMIT_READ")))
      max_read=MagickSizeStrToInt64(envp,1024);

    if ((envp=getenv("MAGICK_LIMIT_WRITE")))
      max_write=MagickSizeStrToInt64(envp,1024);

#if defined(HAVE_OPENMP)
    max_threads=omp_get_num_procs();
    (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                          "%i CPU cores are available",(int) max_threads);
    if ((envp=getenv("OMP_NUM_THREADS")))
      {
        max_threads=MagickSizeStrToInt64(envp,1024);
        (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                              "OMP_NUM_THREADS requests %i threads",(int) max_threads);
      }
    if (max_threads < 1)
      max_threads=1;
    omp_set_num_threads((int) max_threads);
    max_threads=omp_get_max_threads();
#endif /* HAVE_OPENMP */
  }

#if defined(POSIX)
#  if defined(HAVE_GETRLIMIT) && defined(RLIMIT_NOFILE)
    {
      struct rlimit
        rlimits;

      rlim_t
        margin,
        target;

      margin=128;
      target=(rlim_t) max_files+margin;
      if (getrlimit(RLIMIT_NOFILE, &rlimits) != -1)
        {
          (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                                "System file open limits are %lu soft,"
                                " %lu hard",
                                (unsigned long) rlimits.rlim_cur,
                                (unsigned long) rlimits.rlim_max);
#    if defined(HAVE_SETRLIMIT)
          if (rlimits.rlim_max < target)
            rlimits.rlim_cur=rlimits.rlim_max;
          if (rlimits.rlim_cur < target)
            {
              (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                                    "Increasing file open soft limit from %lu "
                                    "to %lu",
                                    (unsigned long) rlimits.rlim_cur,
                                    (unsigned long) target);
              rlimits.rlim_cur=target;
              (void) setrlimit(RLIMIT_NOFILE, &rlimits);
            }
          if (getrlimit(RLIMIT_NOFILE, &rlimits) != -1)
            {
              if (rlimits.rlim_cur < target)
                {
                  if (rlimits.rlim_cur > margin*2)
                    max_files=rlimits.rlim_cur-margin;
                  else
                    max_files=rlimits.rlim_cur/2;
                }
            }
#    endif
        }
    }
#  elif defined(HAVE_SYSCONF) && defined(_SC_OPEN_MAX)
    {
      long
        margin,
        open_max,
        target;

      margin=128;
      target=max_files+margin;
      open_max=sysconf(_SC_OPEN_MAX);
      (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                            "System file open limit is %lu",
                            (unsigned long) open_max);
      if (open_max < target)
        {
          if (open_max > margin*2)
            max_files=open_max-margin;
          else
            max_files=open_max/2;
        }
    }
#  endif

#endif

  if (max_disk >= 0)
    (void) SetMagickResourceLimit(DiskResource,max_disk);
  if (max_files >= 0)
    (void) SetMagickResourceLimit(FileResource,max_files);
  if (max_map >= 0)
    (void) SetMagickResourceLimit(MapResource,max_map);
  if (max_memory >= 0)
    (void) SetMagickResourceLimit(MemoryResource,max_memory);
  if (max_pixels >= 0)
    (void) SetMagickResourceLimit(PixelsResource,max_pixels);
  if (max_threads >= 0)
    {
      (void) SetMagickResourceLimit(ThreadsResource,max_threads);
      _UpdateMagickResourceHighwater(ThreadsResource,max_threads);
    }
  if (max_width >= 0)
    (void) SetMagickResourceLimit(WidthResource,max_width);
  if (max_height >= 0)
    (void) SetMagickResourceLimit(HeightResource,max_height);
  if (max_read >= 0)
    (void) SetMagickResourceLimit(ReadResource,max_read);
  if (max_write >= 0)
    (void) SetMagickResourceLimit(WriteResource,max_write);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   L i b e r a t e M a g i c k R e s o u r c e                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  LiberateMagickResource() liberates resources of the specified type.
%
%  The format of the LiberateMagickResource() method is:
%
%      void LiberateMagickResource(const ResourceType type,
%        const magick_int64_t size)
%
%  A description of each parameter follows:
%
%    o type: The type of resource.
%
%    o size: The size of the resource.
%
%
*/
MagickExport void LiberateMagickResource(const ResourceType type,
  const magick_uint64_t size)
{
  ResourceInfo
    *info;

  if ((info=GetResourceInfo(type)))
    {
      magick_uint64_t
        value=0;

      switch(info->limit_type)
        {
        case AbsoluteLimit:
          {
            /*
              Limit depends only on the currently requested size.
            */
            break;
          }
        case SummationLimit:
          {
            /*
              Limit depends on sum of previous allocations as well as
              the currently requested size.
            */
            LockSemaphoreInfo(info->semaphore);
            info->value-=size;
#if defined(DEBUG_MAGICK_RESOURCES) && DEBUG_MAGICK_RESOURCES
            assert(info->value >= info->minimum);
#endif /* if defined(DEBUG_MAGICK_RESOURCES) && DEBUG_MAGICK_RESOURCES */
            value=info->value;
            UnlockSemaphoreInfo(info->semaphore);
            break;
          }
        }

      if (IsEventLogged(ResourceEvent))
        {
          char
            f_limit[MaxTextExtent],
            f_size[MaxTextExtent],
            f_value[MaxTextExtent];

          if (info->maximum == MagickResourceInfinity)
            {
              strlcpy(f_limit,"Unlimited",sizeof(f_limit));
            }
          else
            {
              FormatSize(info->maximum, f_limit);
              strlcat(f_limit,info->units,sizeof(f_limit));
            }

          FormatSize(size, f_size);
          strlcat(f_size,info->units,sizeof(f_size));

          if (info->limit_type == AbsoluteLimit)
            {
              strlcpy(f_value,"----",sizeof(f_value));
            }
          else
            {
              FormatSize(value, f_value);
              strlcat(f_value,info->units,sizeof(f_value));
            }

          (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                                "%s %s%s/%s/%s",
                                info->name,
                                "-",
                                f_size,
                                f_value,
                                f_limit);
        }
    }
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%  L i s t M a g i c k R e s o u r c e I n f o                                %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ListMagickResourceInfo lists the resource info to a file.
%
%  The format of the ListMagickResourceInfo method is:
%
%      unsigned int ListMagickResourceInfo(FILE *file,ExceptionInfo *exception)
%
%  A description of each parameter follows.
%
%    o file:  An pointer to a FILE.
%
%    o exception: Return any errors or warnings in this structure.
%
%
*/
MagickExport MagickPassFail ListMagickResourceInfo(FILE *file,
  ExceptionInfo *exception)
{
  unsigned int
    index;

  ARG_NOT_USED(exception);

  if (file == (const FILE *) NULL)
    file=stdout;

  fprintf(file,"Resource Limits (Q%d, %d bits/pixel, %dbit address)\n",
          QuantumDepth,4*QuantumDepth,
          (sizeof(PixelPacket *) > 4 ? 64 : 32));
  fprintf(file,"----------------------------------------------------\n");
  for (index=1 ; index <= ResourceInfoMaxIndex; index++)
    {
      char
        environment[MaxTextExtent],
        heading[MaxTextExtent],
        limit[MaxTextExtent];

      LockSemaphoreInfo(resource_info[index].semaphore);
      if (resource_info[index].maximum == MagickResourceInfinity)
        {
          strlcpy(limit,"Unlimited",sizeof(limit));
        }
      else
        {
          FormatSize(resource_info[index].maximum,limit);
          strlcat(limit,resource_info[index].units,sizeof(limit));
        }
      FormatString(heading,"%c%s",toupper((int) resource_info[index].name[0]),
                   resource_info[index].name+1);

      (void) strlcpy(environment,resource_info[index].env,sizeof(environment));

      fprintf(file,"%8s: %10s (%s)\n", heading, limit, environment);
      UnlockSemaphoreInfo(resource_info[index].semaphore);
    }
  fprintf(file,
          "\n"
          "  IEC Binary Ranges:\n"
          "    Ki = \"kibi\" (2^10)\n"
          "    Mi = \"mebi\" (2^20)\n"
          "    Gi = \"gibi\" (2^30)\n"
          "    Ti = \"tebi\" (2^40)\n"
          "    Pi = \"pebi\" (2^50)\n"
          "    Ei = \"exbi\" (2^60)\n"
          );

  (void) fflush(file);

  return(MagickPass);
}
/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S e t M a g i c k R e s o u r c e L i m i t                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SetMagickResourceLimit() sets the limit for a particular resource.  The
%  units for resource types are as follows:
%
%    DiskResource    -- Bytes
%    FileResource    -- Open files
%    MapResource     -- Bytes
%    MemoryResource  -- Bytes
%    PixelsResource  -- Pixels
%    ThreadsResource -- Threads
%    WidthResource   -- Pixels
%    HeightResource  -- Pixels
%    ReadResource    -- Bytes
%    WriteResource   -- Bytes
%
%  The format of the SetMagickResourceLimit() method is:
%
%      void SetMagickResourceLimit(const ResourceType type,
%        const unsigned long limit)
%
%  A description of each parameter follows:
%
%    o type: The type of resource.
%
%    o limit: The maximum limit for the resource.
%
%
*/
MagickExport MagickPassFail SetMagickResourceLimit(const ResourceType type,
                                                   const magick_int64_t limit)
{
  ResourceInfo
    *info;

  MagickPassFail
    status;

  status=MagickFail;

  if ((info=GetResourceInfo(type)))
    {
      LockSemaphoreInfo(info->semaphore);
      if (limit >= info->minimum)
        {
          char
            f_limit[MaxTextExtent];


          FormatSize((magick_int64_t) limit, f_limit);
          info->maximum = limit;
          /* Cap highwater to new maximum */
          if (info->maximum < info->highwater)
            info->highwater = info->maximum;
#if defined(HAVE_OPENMP)
          if (ThreadsResource == type)
            omp_set_num_threads((int) limit);
#endif /* HAVE_OPENMP */
          (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                                "Set %s resource limit to %s%s",
                                info->name,f_limit,info->units);
          status=MagickPass;
        }
      else
        {
          (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                                "Ignored bogus request to set %s resource limit"
                                " to %"MAGICK_INT64_F"d%s",
                                info->name,limit,info->units);
        }
      UnlockSemaphoreInfo(info->semaphore);
    }

  return(status);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   _UpdateMagickResourceHighwater                                            %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  _UpdateMagickResourceHighwater() updates the highwater for the specified
%  resource.  The highwater value is only updated if it is greater than the
%  minimum value for the resource, less than the current maximum for the
%  resource, and greater than the current highwater value for the resource.
%  The intention is that highwater values are only updated for resources
%  successfully used rather than for resources requested.
%
%  The format of the _UpdateMagickResourceHighwater() method is:
%
%      MagickPassFail _UpdateMagickResourceHighwater(const ResourceType type,
%        const unsigned long limit)
%
%  A description of each parameter follows:
%
%    o type: The type of resource.
%
%    o limit: The new proposed highwater for the resource.
%
%
*/
extern MagickPassFail _UpdateMagickResourceHighwater(const ResourceType type,
                                                     const magick_int64_t highwater)
{
  ResourceInfo
    *info;

  MagickPassFail
    status;

  status=MagickFail;

  if ((info=GetResourceInfo(type)))
    {
      LockSemaphoreInfo(info->semaphore);
      if ((highwater > info->minimum) && (highwater <= info->maximum)
          && (highwater > info->highwater))
        {
          char
            f_highwater[MaxTextExtent];


          FormatSize((magick_int64_t) highwater, f_highwater);
          info->highwater = highwater;
          (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                                "Updated %s resource highwater to %s%s",
                                info->name,f_highwater,info->units);
          status=MagickPass;
        }
      else
        {
          (void) LogMagickEvent(ResourceEvent,GetMagickModule(),
                                "Ignored request to set %s highwater to"
                                " %"MAGICK_INT64_F"d%s",
                                info->name,highwater,info->units);
        }
      UnlockSemaphoreInfo(info->semaphore);
    }

  return(status);
}
