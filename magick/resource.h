/*
  Copyright (C) 2003 - 2023 GraphicsMagick Group
  Copyright (C) 2002 ImageMagick Studio

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  Resource methods.
*/
#ifndef _MAGICK_RESOURCE_H
#define _MAGICK_RESOURCE_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
  Typedef declarations.
*/
typedef enum
{
  UndefinedResource=0, /* Undefined value */
  DiskResource,        /* Pixel cache total disk space (Gigabytes) */
  FileResource,        /* Pixel cache number of open files (Files) */
  MapResource,         /* Pixel cache total file memory-mapping (Megabytes) */
  MemoryResource,      /* Maximum heap memory (e.g. malloc) allocations (Megabytes) */
  PixelsResource,      /* Maximum number of pixels in single image (Pixels) */
  ThreadsResource,     /* Maximum number of worker threads */
  WidthResource,       /* Maximum pixel width of an image (Pixels) */
  HeightResource,      /* Maximum pixel height of an image (Pixels) */
  ReadResource,        /* Maximum amount of uncompressed file data which may be read from one file */
  WriteResource        /* Maximum amount of uncompressed file data which may be written to one file */
} ResourceType;


/*
  Method declarations.
*/
extern MagickExport MagickPassFail
  AcquireMagickResource(const ResourceType type,const magick_uint64_t size),
  ListMagickResourceInfo(FILE *file,ExceptionInfo *exception),
  SetMagickResourceLimit(const ResourceType type,const magick_int64_t limit);

extern MagickExport magick_int64_t
  GetMagickResource(const ResourceType type),
  GetMagickResourceLimit(const ResourceType type);

extern MagickExport void
  DestroyMagickResources(void),
  InitializeMagickResources(void),
  LiberateMagickResource(const ResourceType type,const magick_uint64_t size);

#if defined(MAGICK_IMPLEMENTATION)

#  include "magick/resource-private.h"

#endif /* MAGICK_IMPLEMENTATION */

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
