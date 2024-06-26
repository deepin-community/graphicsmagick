/*
% Copyright (C) 2003-2020 GraphicsMagick Group
% Copyright (C) 2002 ImageMagick Studio
% Copyright 1991-1999 E. I. du Pont de Nemours and Company
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%                            SSSSS   GGGG  IIIII                              %
%                            SS     G        I                                %
%                             SSS   G  GG    I                                %
%                               SS  G   G    I                                %
%                            SSSSS   GGG   IIIII                              %
%                                                                             %
%                                                                             %
%                     Read/Write Irix RGB Image Format.                       %
%                                                                             %
%                                                                             %
%                              Software Design                                %
%                                John Cristy                                  %
%                                 July 1992                                   %
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
#include "magick/analyze.h"
#include "magick/attribute.h"
#include "magick/blob.h"
#include "magick/colormap.h"
#include "magick/log.h"
#include "magick/magick.h"
#include "magick/magick_endian.h"
#include "magick/monitor.h"
#include "magick/pixel_cache.h"
#include "magick/utility.h"

/*
  Typedef declaractions.
*/

/*
  The SGI file header is 512 bytes in size.
*/
typedef struct _SGIInfo
{
  unsigned short
    magic;                  /* Identification number (474) */

  magick_int8_t
    storage,                /* Compression flag */
    bytes_per_pixel;        /* Bytes per pixel (per bit plane) */

  magick_uint16_t
    dimension,              /* Number of image dimensions */
    xsize,                  /* Width of image in pixels */
    ysize,                  /* Height of image in pixels */
    zsize;                  /* Number of bit planes */

  magick_uint32_t
    pix_min,                /* Smallest pixel component value */
    pix_max;                /* Largest pixel component value */

  char
    dummy1[4];              /* Not used */

  char
    image_name[80];         /* Name of image (null terminated) */

  magick_uint32_t
    color_map;              /* Format of pixel data */

  char
    dummy2[404];            /* Not used */
} SGIInfo;

/*
  Forward declarations.
*/
static unsigned int
  WriteSGIImage(const ImageInfo *,Image *);
/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   I s S G I                                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method IsSGI returns True if the image format type, identified by the
%  magick string, is SGI.
%
%  The format of the IsSGI method is:
%
%      unsigned int IsSGI(const unsigned char *magick,const size_t length)
%
%  A description of each parameter follows:
%
%    o status:  Method IsSGI returns True if the image format type is SGI.
%
%    o magick: This string is generally the first few bytes of an image file
%      or blob.
%
%    o length: Specifies the length of the magick string.
%
%
*/
static unsigned int IsSGI(const unsigned char *magick,const size_t length)
{
  if (length < 2)
    return(False);
  if (memcmp(magick,"\001\332",2) == 0)
    return(True);
  return(False);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d S G I I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ReadSGIImage reads a SGI RGB image file and returns it.  It
%  allocates the memory necessary for the new Image structure and returns a
%  pointer to the new image.
%
%  The format of the ReadSGIImage method is:
%
%      Image *ReadSGIImage(const ImageInfo *image_info,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image:  Method ReadSGIImage returns a pointer to the image after
%      reading.  A null image is returned if there is a memory shortage or
%      if the image cannot be read.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o exception: return any errors or warnings in this structure.
%
%
*/

static int SGIDecode(const size_t bytes_per_pixel,
                     unsigned char *max_packets,unsigned char *pixels,
                     size_t npackets,size_t npixels)
{
  size_t
    count;

  register unsigned char
    *p,
    *q;

  unsigned int
    pixel;

  p=max_packets;
  q=pixels;
  if (bytes_per_pixel == 2)
    {
      for ( ; ; )
        {
          if (npackets-- == 0)
            return -1;
          pixel=(*p++) << 8U;
          pixel|=(*p++);
          count=(pixel & 0x7fU);
          if (count == 0)
            break;
          if (count > npixels)
            return -1;
          npixels -= count;
          if (pixel & 0x80U)
            for ( ; count != 0U; count--)
              {
                if (npackets-- == 0)
                  return -1;
                *q=(*p++);
                *(q+1)=(*p++);
                q+=8U;
              }
          else
            {
              if (npackets-- == 0)
                return -1;
              pixel=(*p++) << 8U;
              pixel|=(*p++);
              for ( ; count != 0; count--)
                {
                  *q=(unsigned char) (pixel >> 8U);
                  *(q+1)=(unsigned char) pixel;
                  q+=8U;
                }
            }
        }
      return 0;
    }
  for ( ; ; )
    {
      if (npackets-- == 0)
        return -1;
      pixel=(*p++);
      count= (pixel & 0x7fU);
      if (count == 0)
        break;
      if (count > npixels)
        return -1;
      npixels -= count;
      if (pixel & 0x80)
        for ( ; count != 0; count--)
          {
            if (npackets-- == 0)
              return -1;
            *q=(*p++);
            q+=4;
          }
      else
        {
          if (npackets-- == 0)
            return -1;
          pixel=(*p++);
          for ( ; count != 0; count--)
            {
              *q=(unsigned char) pixel;
              q+=4;
            }
        }
    }
  return 0;
}

#define ThrowSGIReaderException(code_,reason_,image_) \
{ \
  MagickFreeResourceLimitedMemory(iris_pixels) \
  MagickFreeResourceLimitedMemory(max_packets); \
  MagickFreeResourceLimitedMemory(offsets); \
  MagickFreeResourceLimitedMemory(runlength); \
  MagickFreeResourceLimitedMemory(scanline) \
  ThrowReaderException(code_,reason_,image_); \
}

static Image *ReadSGIImage(const ImageInfo *image_info,ExceptionInfo *exception)
{
  Image
    *image;

  size_t
    z;

  register IndexPacket
    *indexes;

  register size_t
    i;

  unsigned long
        x,
    y;

  register PixelPacket
    *q;

  register unsigned char
    *p;

  SGIInfo
    iris_info;

  magick_uint32_t
    *offsets = (magick_uint32_t *) NULL,
    *runlength = (magick_uint32_t *) NULL;

  unsigned char
    *iris_pixels = (unsigned char *) NULL,
    *max_packets = (unsigned char *) NULL,
    *scanline = (unsigned char *) NULL;

  unsigned int
    status;

  size_t
    bytes_per_pixel;

  magick_off_t
    file_size;

  /*
    Open image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);
  image=AllocateImage(image_info);
  status=OpenBlob(image_info,image,ReadBinaryBlobMode,exception);
  if (status == False)
    ThrowReaderException(FileOpenError,UnableToOpenFile,image);
  file_size=GetBlobSize(image);
  do
    {
      /*
        Read SGI raster header.
      */
      (void) memset(&iris_info, 0, sizeof(iris_info));
      iris_info.magic=ReadBlobMSBShort(image);
      iris_info.storage=ReadBlobByte(image);
      iris_info.bytes_per_pixel=ReadBlobByte(image) &0xF;
      iris_info.dimension=ReadBlobMSBShort(image) & 0xFFFF;
      iris_info.xsize=ReadBlobMSBShort(image) & 0xFFFF;
      iris_info.ysize=ReadBlobMSBShort(image) & 0xFFFF;
      iris_info.zsize=ReadBlobMSBShort(image) & 0xFFFF;
      iris_info.pix_min=ReadBlobMSBLong(image) & 0xFFFFFFFF;
      iris_info.pix_max=ReadBlobMSBLong(image) & 0xFFFFFFFF;

      (void) ReadBlob(image,(unsigned int) sizeof(iris_info.dummy1),
                      iris_info.dummy1);
      (void) ReadBlob(image,(unsigned int) sizeof(iris_info.image_name),
                      iris_info.image_name);
      iris_info.image_name[sizeof(iris_info.image_name)-1]=0;
      iris_info.color_map=ReadBlobMSBLong(image);
      (void) ReadBlob(image,(unsigned int) sizeof(iris_info.dummy2),
                      iris_info.dummy2);

      if (EOFBlob(image))
        ThrowReaderException(CorruptImageError,UnableToReadImageHeader,image);

      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "IRIS Header:\n"
                            "    MAGIC=%u\n"
                            "    STORAGE=%u (%s)\n"
                            "    BPC=%u\n"
                            "    DIMENSION=%u\n"
                            "    XSIZE=%u\n"
                            "    YSIZE=%u\n"
                            "    ZSIZE=%u\n"
                            "    PIXMIN=%u\n"
                            "    PIXMAX=%u\n"
                            "    IMAGENAME=\"%.79s\"\n"
                            "    COLORMAP=%u",
                            (unsigned int) iris_info.magic,
                            (unsigned int) iris_info.storage,
                            (iris_info.storage == 1 ? "RLE" : "VERBATIM"),
                            (unsigned int) iris_info.bytes_per_pixel,
                            (unsigned int) iris_info.dimension,
                            (unsigned int) iris_info.xsize,
                            (unsigned int) iris_info.ysize,
                            (unsigned int) iris_info.zsize,
                            iris_info.pix_min,
                            iris_info.pix_max,
                            iris_info.image_name,
                            iris_info.color_map);
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "File size %" MAGICK_OFF_F "d bytes", file_size);

      /*
        Validate image header and set image attributes.
      */
      if (iris_info.magic != 0x01DA)
        ThrowReaderException(CorruptImageError,ImproperImageHeader,image);

      if (iris_info.storage == 0U)
        {
          /* Uncompressed */
          image->compression=NoCompression;
        }
      else if (iris_info.storage == 1U)
        {
          /* RLE compressed */
          image->compression=RLECompression;
        }
      else
        {
          /* Error */
          ThrowReaderException(CorruptImageError,ImproperImageHeader,image);
        }

      if (iris_info.color_map != 0U)
        {
          /* We only support images with normal (no) colormap */
          ThrowReaderException(CorruptImageError,ImageTypeNotSupported,image);
        }

      if (iris_info.bytes_per_pixel == 1U)
        {
          /* 8 bits per sample */
          image->depth=8;
        }
      else if (iris_info.bytes_per_pixel == 2U)
        {
          /* 16 bits per sample */
          image->depth=Min(16,QuantumDepth);
        }
      else
        {
          /* Error */
          ThrowReaderException(CorruptImageError,ImproperImageHeader,image);
        }

      /* We only support zsize up to 4. Code further on assumes that. */
      if (iris_info.zsize > 4U)
        ThrowReaderException(CorruptImageError,ImproperImageHeader,image);

      if (iris_info.dimension == 1U)
        {
          /*
            Image contains one channel and one scanline, with scanline
            length specified by xsize.
          */
          image->columns=iris_info.xsize;
          image->rows=1;
          if (iris_info.ysize != image->rows)
            {
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                    "Overriding unexpected value of YSIZE (%u) "
                                    "for 1 dimensional image", iris_info.ysize);
              iris_info.ysize=image->rows;
            }
          image->is_grayscale=MagickTrue;
          if (iris_info.bytes_per_pixel == 1U)
            {
              /* Use a grayscale colormap */
              image->storage_class=PseudoClass;
              image->colors=256;
            }
        }
      else if (iris_info.dimension == 2U)
        {
          /*
            One channel with a number of scan lines.  Width and height
            of image are given by the values of xsize and ysize.
          */
          image->columns=iris_info.xsize;
          image->rows=iris_info.ysize;
          image->is_grayscale=MagickTrue;
          if (iris_info.bytes_per_pixel == 1)
            {
              /* Use a grayscale colormap */
              image->storage_class=PseudoClass;
              image->colors=256;
            }
        }
      else if (iris_info.dimension == 3U)
        {
          /*
            A number of channels.  Width and height of image are given
            by the values of xsize and ysize. The number of channels is
            specified by zsize.

            B/W images have a zsize of 1.  RGB images have a zsize of 3.
            RGB images with an alpha channel have a zsize of 4. Images
            may have more than four channels but the meaning of
            additional channels is implementation dependent.
          */

          image->columns=iris_info.xsize;
          image->rows=iris_info.ysize;

          if (iris_info.zsize == 1U)
            {
              /* B/W image */
              image->matte = MagickFalse;
              image->is_grayscale=MagickTrue;
              if (iris_info.bytes_per_pixel == 1U)
                {
                  /* Use a grayscale colormap */
                  image->storage_class=PseudoClass;
                  image->colors=256U;
                }
            }
          else if (iris_info.zsize == 3U)
            {
              /* RGB */
              image->matte=MagickFalse;
            }
          else if (iris_info.zsize == 4U)
            {
              /* RGBA  */
              image->matte=MagickTrue;
            }
          else
            {
              /* Error */
              ThrowReaderException(CorruptImageError,ImproperImageHeader,image);
            }
        }
      else
        {
          /* Error */
          ThrowReaderException(CorruptImageError,ImproperImageHeader,image);
        }

      if (iris_info.image_name[0])
        (void) SetImageAttribute(image,"comment",iris_info.image_name);

      if (image_info->ping && (image_info->subrange != 0))
        if (image->scene >= (image_info->subimage+image_info->subrange-1))
          break;

      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "Image columns=%lu rows=%lu", image->columns, image->rows);

      if (CheckImagePixelLimits(image, exception) != MagickPass)
        ThrowReaderException(ResourceLimitError,ImagePixelLimitExceeded,image);

      /*
        Allocate SGI pixels.
      */
      bytes_per_pixel=iris_info.bytes_per_pixel;
      if (iris_info.storage != 0x01)
        {
          double
              uncompressed_size;

          size_t
            iris_pixels_size;

          /*
            Check that filesize is reasonable given header
          */
          uncompressed_size=((double) (iris_info.dimension == 3U ? iris_info.zsize : 1U)*
                             image->columns*image->rows*iris_info.bytes_per_pixel);
          (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                "Uncompressed size: %.0f", uncompressed_size);

          /* Not compressed */
          if (uncompressed_size > file_size)
            ThrowReaderException(CorruptImageError,InsufficientImageDataInFile,
                                 image);

          /*
            Read standard image format.
          */
          scanline=MagickAllocateResourceLimitedArray(unsigned char *,
                                       bytes_per_pixel,iris_info.xsize);
          if (scanline == (unsigned char *) NULL)
            ThrowSGIReaderException(ResourceLimitError,MemoryAllocationFailed,
                                    image);

          iris_pixels_size = MagickArraySize(MagickArraySize(4U,bytes_per_pixel),
                                             MagickArraySize(iris_info.xsize,iris_info.ysize));
          iris_pixels=MagickAllocateResourceLimitedMemory(unsigned char *,iris_pixels_size);
          if (iris_pixels == (unsigned char *) NULL)
            ThrowSGIReaderException(ResourceLimitError,MemoryAllocationFailed,image);
          (void) memset(iris_pixels,0,iris_pixels_size);

          (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                "   Reading SGI scanlines");
          for (z=0U; z < iris_info.zsize; z++)
            {
              p=iris_pixels+bytes_per_pixel*z;
              for (y=0U; y < iris_info.ysize; y++)
                {
                  if (ReadBlob(image,bytes_per_pixel*iris_info.xsize,
                               (char *) scanline) != bytes_per_pixel*iris_info.xsize)
                    {
                      ThrowSGIReaderException(CorruptImageError,
                                              UnexpectedEndOfFile, image);
                      break;
                    }
                  if (bytes_per_pixel == 2U)
                    for (x=0; x < iris_info.xsize; x++)
                      {
                        *p=scanline[2U*x];
                        *(p+1U)=scanline[2U*x+1U];
                        p+=8U;
                      }
                  else
                    for (x=0; x < iris_info.xsize; x++)
                      {
                        *p=scanline[x];
                        p+=4U;
                      }
                }
              if (EOFBlob(image))
                break;
            }
          MagickFreeResourceLimitedMemory(scanline);
        }
      else
        {
          unsigned int
            data_order;

          magick_off_t
            offset;

          size_t
            iris_pixels_size,
            max_packets_alloc_size,
            rle_alloc_size,
            rle_dimensions;

          magick_off_t
            here;

          rle_dimensions=MagickArraySize(iris_info.ysize, iris_info.zsize);
          rle_alloc_size=MagickArraySize(rle_dimensions, sizeof(magick_uint32_t));

          if ((rle_dimensions == 0U) || (rle_alloc_size == 0U))
            ThrowSGIReaderException(ResourceLimitError,MemoryAllocationFailed,
                                    image);

          /*
            Read runlength-encoded image format.
          */
          if (TellBlob(image)+rle_alloc_size > (size_t) file_size)
            ThrowSGIReaderException(CorruptImageError,UnexpectedEndOfFile,image);
          offsets=MagickAllocateResourceLimitedMemory(magick_uint32_t *,rle_alloc_size);
          if (offsets == (magick_uint32_t *) NULL)
            ThrowSGIReaderException(ResourceLimitError,MemoryAllocationFailed,
                                    image);
          if (ReadBlob(image,rle_alloc_size,offsets) != rle_alloc_size)
            ThrowSGIReaderException(CorruptImageError,UnexpectedEndOfFile,image);

          if (TellBlob(image)+rle_alloc_size > (size_t) file_size)
            ThrowSGIReaderException(CorruptImageError,UnexpectedEndOfFile,image);
          runlength=MagickAllocateResourceLimitedMemory(magick_uint32_t *,rle_alloc_size);
          if (runlength == (magick_uint32_t *) NULL)
            ThrowSGIReaderException(ResourceLimitError,MemoryAllocationFailed,
                                    image);
          if (ReadBlob(image,rle_alloc_size,runlength) != rle_alloc_size)
            ThrowSGIReaderException(CorruptImageError,UnexpectedEndOfFile,image);

#if !defined(WORDS_BIGENDIAN)
          MagickSwabArrayOfUInt32(offsets,rle_dimensions);
          MagickSwabArrayOfUInt32(runlength,rle_dimensions);
#endif
          here=TellBlob(image);

          for (i=0U; i < rle_dimensions; i++)
            if ((offsets[i] != ((magick_off_t) offsets[i])) ||
                (offsets[i] < here) ||
                (offsets[i] > file_size))
              ThrowSGIReaderException(CorruptImageError,UnableToRunlengthDecodeImage,image);
          for (i=0U; i < rle_dimensions; i++)
            {
              if (runlength[i] > ((size_t) 4U*iris_info.xsize+10U))
                ThrowSGIReaderException(CorruptImageError,UnableToRunlengthDecodeImage,image);
            }

          max_packets_alloc_size=MagickArraySize((size_t) iris_info.xsize+10U,4U);
          max_packets=MagickAllocateResourceLimitedMemory(unsigned char *,max_packets_alloc_size);
          if (max_packets == (unsigned char *) NULL)
            ThrowSGIReaderException(ResourceLimitError,MemoryAllocationFailed,
                                    image);

          iris_pixels_size=MagickArraySize(MagickArraySize(4U,bytes_per_pixel),
                                           MagickArraySize(iris_info.xsize,iris_info.ysize));
          iris_pixels=MagickAllocateResourceLimitedMemory(unsigned char *,iris_pixels_size);
          if (iris_pixels == (unsigned char *) NULL)
            ThrowSGIReaderException(ResourceLimitError,MemoryAllocationFailed,image);

          (void) memset(iris_pixels,0,iris_pixels_size);

          /*
            Check data order.
          */
          offset=0;
          data_order=0U;
          for (y=0; ((y < iris_info.ysize) && !data_order); y++)
            for (z=0U; ((z < iris_info.zsize) && !data_order); z++)
              {
                const size_t run_index = (size_t) y+z*iris_info.ysize;
                if (run_index >= rle_alloc_size)
                  ThrowSGIReaderException(CorruptImageError,
                                          UnableToRunlengthDecodeImage,image);
                if (offsets[run_index] < offset)
                  data_order=1;
                offset=(magick_off_t) offsets[run_index];
              }
          offset=TellBlob(image);
          if (data_order == 1)
            {
              for (z=0U; z < iris_info.zsize; z++)
                {
                  p=iris_pixels;
                  for (y=0U; y < iris_info.ysize; y++)
                    {
                      const size_t run_index = (size_t) y+z*iris_info.ysize;
                      size_t length;
                      if (run_index >= rle_alloc_size)
                        ThrowSGIReaderException(CorruptImageError,
                                                UnableToRunlengthDecodeImage,image);
                      if (offset != (magick_off_t) offsets[run_index])
                        {
                          offset=(magick_off_t) offsets[run_index];
                          if (SeekBlob(image,offset,SEEK_SET) != offset)
                            ThrowSGIReaderException(CorruptImageError,
                                                    UnableToRunlengthDecodeImage, image);
                        }
                      length=runlength[run_index];
                      if (length > max_packets_alloc_size)
                        ThrowSGIReaderException(CorruptImageError,
                                                UnableToRunlengthDecodeImage,image);
                      if (ReadBlob(image,length,(char *) max_packets) != length)
                        ThrowSGIReaderException(CorruptImageError,
                                                UnexpectedEndOfFile, image);
                      offset+=(magick_off_t) length;
                      if (SGIDecode(bytes_per_pixel,max_packets,p+bytes_per_pixel*z,
                                    length/bytes_per_pixel,
                                    iris_info.xsize) == -1)
                        ThrowSGIReaderException(CorruptImageError,
                                                UnableToRunlengthDecodeImage,image);
                      p+=((size_t) iris_info.xsize*4U*bytes_per_pixel);
                    }
                }
            }
          else
            {
              p=iris_pixels;
              for (y=0; y < iris_info.ysize; y++)
                {
                  for (z=0; z < iris_info.zsize; z++)
                    {
                      const size_t run_index = (size_t) y+z*iris_info.ysize;
                      size_t length;
                      if (run_index >= rle_alloc_size)
                        ThrowSGIReaderException(CorruptImageError,
                                                UnableToRunlengthDecodeImage,image);
                      if (offset != (magick_off_t) offsets[run_index])
                        {
                          offset=(magick_off_t) offsets[run_index];
                          if (SeekBlob(image,offset,SEEK_SET) != offset)
                            ThrowSGIReaderException(CorruptImageError,
                                                    UnableToRunlengthDecodeImage, image);
                        }
                      length=runlength[run_index];
                      if (length > max_packets_alloc_size)
                        ThrowSGIReaderException(CorruptImageError,
                                                UnableToRunlengthDecodeImage,image);
                      if (ReadBlob(image,length, (char *) max_packets) != length)
                        ThrowSGIReaderException(CorruptImageError,
                                                UnexpectedEndOfFile, image);
                      offset+=length;
                      if (SGIDecode(bytes_per_pixel,max_packets,p+bytes_per_pixel*z,
                                    length/bytes_per_pixel,
                                    iris_info.xsize) == -1)
                        ThrowSGIReaderException(CorruptImageError,
                                                UnableToRunlengthDecodeImage,image);
                    }
                  p+=((size_t) iris_info.xsize*4U*bytes_per_pixel);
                  if (EOFBlob(image))
                    break;
                }
            }
          MagickFreeResourceLimitedMemory(runlength);
          MagickFreeResourceLimitedMemory(max_packets);
          MagickFreeResourceLimitedMemory(offsets);
        }

      /*
        Convert SGI raster image to pixel packets.
      */
      if (image->storage_class == DirectClass)
        {
          /*
            Convert SGI image to DirectClass pixel packets.
          */
          if (bytes_per_pixel == 2U)
            {
              for (y=0; y < image->rows; y++)
                {
                  p=iris_pixels+((size_t)image->rows-y-1)*8*image->columns;
                  q=SetImagePixels(image,0,y,image->columns,1);
                  if (q == (PixelPacket *) NULL)
                    break;
                  for (x=0U; x < image->columns; x++)
                    {
                      q->red=ScaleShortToQuantum((*(p+0) << 8U) | (*(p+1)));
                      q->green=ScaleShortToQuantum((*(p+2) << 8U) | (*(p+3)));
                      q->blue=ScaleShortToQuantum((*(p+4) << 8U) | (*(p+5)));
                      if (image->matte)
                        q->opacity=(Quantum)
                          (MaxRGB-ScaleShortToQuantum((*(p+6) << 8) | (*(p+7))));
                      else
                        q->opacity=OpaqueOpacity;
                      p+=8U;
                      q++;
                    }
                  if (!SyncImagePixels(image))
                    break;
                  if (QuantumTick(y,image->rows))
                    if (!MagickMonitorFormatted(y,image->rows,exception,
                                                LoadImageText,image->filename,
                                                image->columns,image->rows))
                      break;
                }
            }
          else
            for (y=0; y < image->rows; y++)
              {
                p=iris_pixels+((size_t) image->rows-y-1)*4*image->columns;
                q=SetImagePixels(image,0,y,image->columns,1);
                if (q == (PixelPacket *) NULL)
                  break;
                for (x=0; x < image->columns; x++)
                  {
                    q->red=ScaleCharToQuantum(*p);
                    q->green=ScaleCharToQuantum(*(p+1));
                    q->blue=ScaleCharToQuantum(*(p+2));
                    if (image->matte)
                      q->opacity=(Quantum) (MaxRGB-ScaleCharToQuantum(*(p+3)));
                    else
                      q->opacity=OpaqueOpacity;
                    p+=4;
                    q++;
                  }
                if (!SyncImagePixels(image))
                  break;
                if (QuantumTick(y,image->rows))
                  if (!MagickMonitorFormatted(y,image->rows,exception,
                                              LoadImageText,image->filename,
                                              image->columns,image->rows))
                    break;
              }
        }
      else
        {
          /*
            Create grayscale map.
          */
          if (!AllocateImageColormap(image,image->colors))
            ThrowSGIReaderException(ResourceLimitError,MemoryAllocationFailed,
                                    image);
          /*
            Convert SGI image to PseudoClass pixel packets.
          */
          if (bytes_per_pixel == 2)
            {
              for (y=0; y < image->rows; y++)
                {
                  p=iris_pixels+((size_t)image->rows-y-1)*8*image->columns;
                  q=SetImagePixels(image,0,y,image->columns,1);
                  if (q == (PixelPacket *) NULL)
                    break;
                  indexes=AccessMutableIndexes(image);
                  for (x=0; x < image->columns; x++)
                    {
                      indexes[x]=(*p << 8);
                      indexes[x]|=(*(p+1));
                      p+=8;
                      q++;
                    }
                  if (!SyncImagePixels(image))
                    break;
                  if (QuantumTick(y,image->rows))
                    if (!MagickMonitorFormatted(y,image->rows,exception,
                                                LoadImageText,image->filename,
                                                image->columns,image->rows))
                      break;
                }
            }
          else
            {
              for (y=0; y < image->rows; y++)
                {
                  p=iris_pixels+((size_t)image->rows-y-1)*4U*image->columns;
                  q=SetImagePixels(image,0,y,image->columns,1);
                  if (q == (PixelPacket *) NULL)
                    break;
                  indexes=AccessMutableIndexes(image);
                  for (x=0; x < image->columns; x++)
                    {
                      indexes[x]=(*p);
                      p+=4;
                      q++;
                    }
                  if (!SyncImagePixels(image))
                    break;
                  if (QuantumTick(y,image->rows))
                    if (!MagickMonitorFormatted(y,image->rows,exception,
                                                LoadImageText,image->filename,
                                                image->columns,image->rows))
                      break;
                }
            }
          if (y < image->rows)
            {
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                    "Only transferred %lu rows out of %lu",
                                    y, image->rows);
              MagickFreeResourceLimitedMemory(iris_pixels);
              /*
                Not sure what a proper error report is here
               */
              ThrowSGIReaderException(CorruptImageError,UnableToReadImageData,image);
            }
          (void) SyncImage(image);
        }
      MagickFreeResourceLimitedMemory(iris_pixels);
      if (EOFBlob(image))
        {
          ThrowSGIReaderException(CorruptImageError,UnexpectedEndOfFile,
                                  image);
          break;
        }
    } while (0);
  CloseBlob(image);
  StopTimer(&image->timer);
  return(image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r S G I I m a g e                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterSGIImage adds attributes for the SGI image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterSGIImage method is:
%
%      RegisterSGIImage(void)
%
*/
ModuleExport void RegisterSGIImage(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("SGI");
  entry->decoder=(DecoderHandler) ReadSGIImage;
  entry->encoder=(EncoderHandler) WriteSGIImage;
  entry->magick=(MagickHandler) IsSGI;
  entry->description="Irix RGB image";
  entry->module="SGI";
  entry->adjoin=MagickFalse;
  entry->seekable_stream=True;
  (void) RegisterMagickInfo(entry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r S G I I m a g e                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnregisterSGIImage removes format registrations made by the
%  SGI module from the list of supported formats.
%
%  The format of the UnregisterSGIImage method is:
%
%      UnregisterSGIImage(void)
%
*/
ModuleExport void UnregisterSGIImage(void)
{
  (void) UnregisterMagickInfo("SGI");
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e S G I I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method WriteSGIImage writes an image in SGI RGB encoded image format.
%
%  The format of the WriteSGIImage method is:
%
%      unsigned int WriteSGIImage(const ImageInfo *image_info,Image *image)
%
%  A description of each parameter follows.
%
%    o status: Method WriteSGIImage return True if the image is written.
%      False is returned is there is a memory shortage or if the image file
%      fails to write.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o image:  A pointer to an Image structure.
%
%
*/

static size_t SGIEncode(unsigned char *pixels,size_t count,
                        unsigned char *packets)
{
  short
    runlength;

  register unsigned char
    *p,
    *q;

  unsigned char
    *limit,
    *mark;

  p=pixels;
  limit=p+count*4;
  q=packets;
  while (p < limit)
    {
      mark=p;
      p+=8;
      while ((p < limit) && ((*(p-8) != *(p-4)) || (*(p-4) != *p)))
        p+=4;
      p-=8;
      count=((p-mark) >> 2);
      while (count)
        {
          runlength=(short) (count > 126 ? 126 : count);
          count-=runlength;
          *q++=0x80 | runlength;
          for ( ; runlength > 0; runlength--)
            {
              *q++=(*mark);
              mark+=4;
            }
        }
      mark=p;
      p+=4;
      while ((p < limit) && (*p == *mark))
        p+=4;
      count=((p-mark) >> 2);
      while (count)
        {
          runlength=(short) (count > 126 ? 126 : count);
          count-=runlength;
          *q++=(unsigned char) runlength;
          *q++=(*mark);
        }
    }
  *q++=0;
  return(q-packets);
}

#define ThrowSGIWriterException(code_,reason_,image_) \
{ \
  MagickFreeResourceLimitedMemory(scanline) \
  MagickFreeResourceLimitedMemory(offsets); \
  MagickFreeResourceLimitedMemory(packets); \
  MagickFreeResourceLimitedMemory(runlength); \
  MagickFreeResourceLimitedMemory(iris_pixels); \
  ThrowWriterException(code_,reason_,image_); \
}

static unsigned int WriteSGIImage(const ImageInfo *image_info,Image *image)
{
  long
    y,
    z;

  SGIInfo
    iris_info;

  register const PixelPacket
    *p;

  register long
    i,
    x;

  register unsigned char
    *q;

  unsigned long
    *offsets = (unsigned long *) NULL,
    *runlength = (unsigned long *) NULL;

  unsigned char
    *iris_pixels = (unsigned char *) NULL,
    *packets = (unsigned char *) NULL,
    *scanline = (unsigned char *) NULL;

  unsigned int
    status;

  unsigned long
    number_pixels;

  /*
    Open output image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  if ((image->columns > 65535L) || (image->rows > 65535L))
    ThrowWriterException(ImageError,WidthOrHeightExceedsLimit,image);
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,&image->exception);
  if (status == MagickFail)
    ThrowWriterException(FileOpenError,UnableToOpenFile,image);
  do
    {
      ImageCharacteristics
        characteristics;

      /*
        Ensure that image is in an RGB space.
      */
      (void) TransformColorspace(image,RGBColorspace);
      /*
        Analyze image to be written.
      */
      (void) GetImageCharacteristics(image,&characteristics,
                                     (OptimizeType == image_info->type),
                                     &image->exception);
      /*
        Initialize SGI raster file header.
      */
      iris_info.magic=0x01DA;
      if (image_info->compression == NoCompression)
        iris_info.storage=0x00;
      else
        iris_info.storage=0x01;
      iris_info.bytes_per_pixel=1;  /* one byte per pixel */
      iris_info.dimension=3;
      iris_info.xsize=(unsigned short) image->columns;
      iris_info.ysize=(unsigned short) image->rows;
      if (image->matte != MagickFalse)
        iris_info.zsize=4;
      else
        {
          if ((image_info->type != TrueColorType) &&
              (characteristics.grayscale))
            {
              iris_info.dimension=2;
              iris_info.zsize=1;
            }
          else
            iris_info.zsize=3;
        }
      iris_info.pix_min=0;
      iris_info.pix_max=ScaleQuantumToChar(MaxRGB);

      (void) memset(iris_info.dummy1,0,sizeof(iris_info.dummy1));
      {
        const ImageAttribute
          *attribute;

        (void) memset(iris_info.image_name,0,sizeof(iris_info.image_name));
        if ((attribute=GetImageAttribute(image,"comment")))
          (void) strlcpy(iris_info.image_name,attribute->value,sizeof(iris_info.image_name));
      }
      iris_info.color_map=0;
      (void) memset(iris_info.dummy2,0,sizeof(iris_info.dummy2));

      /*
        Write SGI header.
      */
      (void) WriteBlobMSBShort(image,iris_info.magic);
      (void) WriteBlobByte(image,iris_info.storage);
      (void) WriteBlobByte(image,iris_info.bytes_per_pixel);
      (void) WriteBlobMSBShort(image,iris_info.dimension);
      (void) WriteBlobMSBShort(image,iris_info.xsize);
      (void) WriteBlobMSBShort(image,iris_info.ysize);
      (void) WriteBlobMSBShort(image,iris_info.zsize);
      (void) WriteBlobMSBLong(image,iris_info.pix_min);
      (void) WriteBlobMSBLong(image,iris_info.pix_max);
      (void) WriteBlob(image,sizeof(iris_info.dummy1),
                       (char *) iris_info.dummy1);
      (void) WriteBlob(image,sizeof(iris_info.image_name),
                       (char *) iris_info.image_name);
      (void) WriteBlobMSBLong(image,iris_info.color_map);
      (void) WriteBlob(image,sizeof(iris_info.dummy2),
                       (char *) iris_info.dummy2);
      /*
        Allocate SGI pixels.
      */
      number_pixels=image->columns*image->rows;
      iris_pixels=MagickAllocateResourceLimitedArray(unsigned char *,4,number_pixels);
      if (iris_pixels == (unsigned char *) NULL)
        ThrowSGIWriterException(ResourceLimitError,MemoryAllocationFailed,image);
      /*
        Convert image pixels to uncompressed SGI pixels.
      */
      for (y=0; y < (long) image->rows; y++)
        {
          p=AcquireImagePixels(image,0,y,image->columns,1,&image->exception);
          if (p == (const PixelPacket *) NULL)
            break;
          q=iris_pixels+(((size_t)iris_info.ysize-1)-y)*((size_t)iris_info.xsize*4);
          for (x=0; x < (long) image->columns; x++)
            {
              *q++=ScaleQuantumToChar(p->red);
              *q++=ScaleQuantumToChar(p->green);
              *q++=ScaleQuantumToChar(p->blue);
              *q++=ScaleQuantumToChar(MaxRGB-p->opacity);
              p++;
            }
          if (QuantumTick(y,image->rows))
            if (!MagickMonitorFormatted(y,image->rows,&image->exception,
                                        SaveImageText,image->filename,
                                        image->columns,image->rows))
              break;
        }
      if (image_info->compression == NoCompression)
        {
          /*
            Write uncompressed SGI pixels.
          */
          scanline=MagickAllocateResourceLimitedMemory(unsigned char *,iris_info.xsize);
          if (scanline == (unsigned char *) NULL)
            ThrowSGIWriterException(ResourceLimitError,MemoryAllocationFailed,
                                    image);
          for (z=0; z < (int) iris_info.zsize; z++)
            {
              q=iris_pixels+z;
              for (y=0; y < (long) iris_info.ysize; y++)
                {
                  for (x=0; x < (long) iris_info.xsize; x++)
                    {
                      scanline[x]=(*q);
                      q+=4;
                    }
                  (void) WriteBlob(image,iris_info.xsize,(char *) scanline);
                }
            }
          MagickFreeResourceLimitedMemory(scanline);
        }
      else
        {
          unsigned long
            length,
            number_packets,
            offset;

          /*
            Convert SGI uncompressed pixels.
          */
          offsets=MagickAllocateResourceLimitedArray(unsigned long *,iris_info.ysize,
                                      MagickArraySize(iris_info.zsize,
                                                      sizeof(unsigned long)));
          packets=MagickAllocateResourceLimitedArray(unsigned char *,
                                      4*(2*(size_t) iris_info.xsize+10),
                                      image->rows);
          runlength=MagickAllocateResourceLimitedArray(unsigned long *,iris_info.ysize,
                                        MagickArraySize(iris_info.zsize,
                                                        sizeof(unsigned long)));
          if ((offsets == (unsigned long *) NULL) ||
              (packets == (unsigned char *) NULL) ||
              (runlength == (unsigned long *) NULL))
            ThrowSGIWriterException(ResourceLimitError,MemoryAllocationFailed,
                                    image);
          offset=512+4*2*((size_t) iris_info.ysize*iris_info.zsize);
          number_packets=0;
          q=iris_pixels;
          for (y=0; y < (long) iris_info.ysize; y++)
            {
              for (z=0; z < (int) iris_info.zsize; z++)
                {
                  length=(unsigned long)
                    SGIEncode(q+z,(int) iris_info.xsize,packets+number_packets);
                  number_packets+=length;
                  offsets[y+z*iris_info.ysize]=offset;
                  runlength[y+z*iris_info.ysize]=length;
                  offset+=length;
                }
              q+=((size_t)iris_info.xsize*4);
            }
          /*
            Write out line start and length tables and runlength-encoded pixels.
          */
          for (i=0; i < (int) (iris_info.ysize*iris_info.zsize); i++)
            (void) WriteBlobMSBLong(image,offsets[i]);
          for (i=0; i < (int) (iris_info.ysize*iris_info.zsize); i++)
            (void) WriteBlobMSBLong(image,runlength[i]);
          (void) WriteBlob(image,number_packets,(char *) packets);
          /*
            Free memory.
          */
          MagickFreeResourceLimitedMemory(runlength);
          MagickFreeResourceLimitedMemory(packets);
          MagickFreeResourceLimitedMemory(offsets);
        }
      MagickFreeResourceLimitedMemory(iris_pixels);
    } while (0);
  status &= CloseBlob(image);
  return(status);
}
