/*
% Copyright (C) 2003-2021 GraphicsMagick Group
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
%                            PPPP   DDDD   BBBB                               %
%                            P   P  D   D  B   B                              %
%                            PPPP   D   D  BBBB                               %
%                            P      D   D  B   B                              %
%                            P      DDDD   BBBB                               %
%                                                                             %
%                                                                             %
%              Read/Write Palm Database ImageViewer Image Format.             %
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
  Some information on this format may be found at
  http://fileformats.archiveteam.org/wiki/Palm_Database_ImageViewer

  Round-trip tests do not pass so this format is not included in the
  test suite.
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/analyze.h"
#include "magick/attribute.h"
#include "magick/blob.h"
#include "magick/colormap.h"
#include "magick/constitute.h"
#include "magick/log.h"
#include "magick/magick.h"
#include "magick/monitor.h"
#include "magick/pixel_cache.h"
#include "magick/utility.h"

/*
  Typedef declarations.
*/
typedef struct _PDBInfo
{
  char
    name[32];

  short int
    attributes,
    version;

  unsigned long
    create_time,
    modify_time,
    archive_time,
    modify_number,
    application_info,
    sort_info;

  char
    type[4],  /* database type identifier "vIMG" */
    id[4];    /* database creator identifier "View" */

  unsigned long
    seed,
    next_record;

  short int
    number_records;
} PDBInfo;

typedef struct _PDBImage
{
  char
    name[32],
    version,
    type;

  unsigned long
    reserved_1,
    note;

  unsigned short int
    x_last,
    y_last;

  unsigned long
    reserved_2;

  unsigned short int
    x_anchor,
    y_anchor,
    width,
    height;
} PDBImage;
/*
  Forward declarations.
*/
static unsigned int
  WritePDBImage(const ImageInfo *,Image *);

static void LogPDPInfo(const PDBInfo *info)
{
  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "PDP Info:\n"
                        "    name            : %.32s\n"
                        "    attributes      : %d\n"
                        "    version         : %d\n"
                        "    create_time     : %lu\n"
                        "    modify_time     : %lu\n"
                        "    archive_time    : %lu\n"
                        "    modify_number   : %lu\n"
                        "    application_info: %lu\n"
                        "    sort_info       : %lu\n"
                        "    type            : %.4s\n"
                        "    id              : %.4s\n"
                        "    seed            : %lu\n"
                        "    next_record     : %lu\n"
                        "    number_records  : %u",
                        info->name,
                        info->attributes,
                        info->version,
                        info->create_time,
                        info->modify_time,
                        info->archive_time,
                        info->modify_number,
                        info->application_info,
                        info->sort_info,
                        info->type,
                        info->id,
                        info->seed,
                        info->next_record,
                        info->number_records);
}

static void LogPDPImage(const PDBImage *image)
{
  static const char *type_string;
  switch(image->type)
    {
    case 0: type_string = "2 bit gray"; break;
    case 2: type_string = "4 bit gray"; break;
    default: type_string = "monochrome"; break;
    }

  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "PDP Image:\n"
                        "    name:       %.32s\n"
                        "    version:    %d\n"
                        "    type:       %d (%s)\n"
                        "    reserved_1: %lu\n"
                        "    note:       %lu\n"
                        "    x_last:     %u\n"
                        "    y_last:     %u\n"
                        "    reserved_2: %lu\n"
                        "    x_anchor:   %u\n"
                        "    y_anchor:   %u\n"
                        "    width:      %u\n"
                        "    height:     %u",
                        image->name,
                        image->version,
                        image->type, type_string,
                        image->reserved_1,
                        image->note,
                        image->x_last,
                        image->y_last,
                        image->reserved_2,
                        image->x_anchor,
                        image->y_anchor,
                        image->width,
                        image->height
                        );
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D e c o d e I m a g e                                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method DecodeImage unpacks the packed image pixels into runlength-encoded
%  pixel packets.
%
%  The format of the DecodeImage method is:
%
%      unsigned int DecodeImage(Image *image,unsigned char *pixels,
%        const size_t length)
%
%  A description of each parameter follows:
%
%    o status:  Method DecodeImage returns True if all the pixels are
%      uncompressed without error, otherwise False.
%
%    o image: The address of a structure of type Image.
%
%    o pixels:  The address of a byte (8 bits) array of pixel data created by
%      the decoding process.
%
%
*/
static MagickPassFail DecodeImage(Image *image,unsigned char *pixels,
  const size_t length)
{
  int
    c,
    count,
    pixel;

  register long
    i;

  register unsigned char
    *p;

  MagickPassFail
    status = MagickPass;

  p=pixels;
  while (p < (pixels+length))
  {
    if ((pixel=ReadBlobByte(image)) == EOF)
      {
        status = MagickFail;
        goto decode_image_quit;
      }
    if (pixel <= 0x80)
      {
        count=pixel+1;
        for (i=0; i < count; i++)
          {
            if ((c = ReadBlobByte(image)) == EOF)
              {
                status = MagickFail;
                goto decode_image_quit;
              }
            *p++ = (unsigned char) c;
          }
        continue;
      }
    count=pixel+1-0x80;
    if ((pixel=ReadBlobByte(image)) == EOF)
      {
        status = MagickFail;
        goto decode_image_quit;
      }

    for (i=0; i < count; i++)
      *p++=(unsigned char) pixel;
  }
 decode_image_quit:;

  return(status);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   I s P D B                                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method IsPDB returns True if the image format type, identified by the
%  magick string, is PDB.
%
%  The format of the ReadPDBImage method is:
%
%      unsigned int IsPDB(const unsigned char *magick,const size_t length)
%
%  A description of each parameter follows:
%
%    o status:  Method IsPDB returns True if the image format type is PDB.
%
%    o magick: This string is generally the first few bytes of an image file
%      or blob.
%
%    o length: Specifies the length of the magick string.
%
%
*/
static unsigned int IsPDB(const unsigned char *magick,const size_t length)
{
  if (length < 68)
    return(False);
  if (memcmp(magick+60,"vIMGView",8) == 0)
    return(True);
  return(False);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d P D B I m a g e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ReadPDBImage reads an Pilot image file and returns it.  It
%  allocates the memory necessary for the new Image structure and returns a
%  pointer to the new image.
%
%  The format of the ReadPDBImage method is:
%
%      Image *ReadPDBImage(const ImageInfo *image_info,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image:  Method ReadPDBImage returns a pointer to the image after
%      reading. A null image is returned if there is a memory shortage or if
%      the image cannot be read.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o exception: return any errors or warnings in this structure.
%
%
*/
#define ThrowPDBReaderException(code_,reason_,image_) \
{ \
  MagickFreeResourceLimitedMemory(pixels);                   \
  ThrowReaderException(code_,reason_,image_); \
}

static Image *ReadPDBImage(const ImageInfo *image_info,ExceptionInfo *exception)
{
  int
    record_type;

  char
    tag[3];

  Image
    *image;

  IndexPacket
    index;

  long
    offset;

  PDBImage
    pdb_image;

  PDBInfo
    pdb_info;

  register IndexPacket
    *indexes;

  unsigned long
    y;

  register unsigned long
    x;

  register PixelPacket
    *q;

  register unsigned char
    *p;

  size_t
    count;

  unsigned char
    *pixels = (unsigned char *) NULL;

  unsigned int
    bits_per_pixel,
    status;

  size_t
    packets;

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
    ThrowPDBReaderException(FileOpenError,UnableToOpenFile,image);
  /*
    Determine if this is a PDB image file.
  */
  count=ReadBlob(image,32,pdb_info.name);
  if (count != 32)
    ThrowPDBReaderException(CorruptImageError,ImproperImageHeader,image);
  pdb_info.name[sizeof(pdb_info.name)-1]='\0';
  pdb_info.attributes=ReadBlobMSBShort(image);
  pdb_info.version=ReadBlobMSBShort(image);
  pdb_info.create_time=ReadBlobMSBLong(image);
  pdb_info.modify_time=ReadBlobMSBLong(image);
  pdb_info.archive_time=ReadBlobMSBLong(image);
  pdb_info.modify_number=ReadBlobMSBLong(image);
  pdb_info.application_info=ReadBlobMSBLong(image);
  pdb_info.sort_info=ReadBlobMSBLong(image);
  if ((ReadBlob(image,4,pdb_info.type) != 4) ||
      (ReadBlob(image,4,pdb_info.id) != 4))
    ThrowReaderException(CorruptImageError,UnexpectedEndOfFile,image);
  pdb_info.seed=ReadBlobMSBLong(image);
  pdb_info.next_record=ReadBlobMSBLong(image);
  pdb_info.number_records=ReadBlobMSBShort(image);
  if (image->logging)
    LogPDPInfo(&pdb_info);
  if ((memcmp(pdb_info.type,"vIMG",4) != 0) ||
      (memcmp(pdb_info.id,"View",4) != 0))
    ThrowPDBReaderException(CorruptImageError,ImproperImageHeader,image);
  if (pdb_info.next_record != 0)
    ThrowPDBReaderException(CoderError,MultipleRecordListNotSupported,image);
  /*
    Read record header.
  */
  offset=(long) ReadBlobMSBLong(image);
  if (ReadBlob(image,3,tag) != 3)
    ThrowReaderException(CorruptImageError,UnexpectedEndOfFile,image);
  record_type=ReadBlobByte(image);
  if (((record_type != 0x00) && (record_type != 0x01)) ||
      (memcmp(tag,"\x40\x6f\x80",3) != 0))
    ThrowPDBReaderException(CorruptImageError,CorruptImage,image);
  if ((offset-TellBlob(image)) == 6)
    {
      (void) ReadBlobByte(image);
      (void) ReadBlobByte(image);
    }
  if (pdb_info.number_records > 1)
    {
      offset=(long) ReadBlobMSBLong(image);
      (void) ReadBlob(image,3,tag);
      record_type=ReadBlobByte(image);
      if (((record_type != 0x00) && (record_type != 0x01)) ||
          (memcmp(tag,"\x40\x6f\x80",3) != 0))
        ThrowPDBReaderException(CorruptImageError,CorruptImage,image);
      if ((offset-TellBlob(image)) == 6)
        {
          (void) ReadBlobByte(image);
          (void) ReadBlobByte(image);
        }
    }
  /*
    Read image header.
  */
  (void) ReadBlob(image,32,pdb_image.name);
  pdb_image.version=ReadBlobByte(image);
  pdb_image.type=ReadBlobByte(image);
  pdb_image.reserved_1=ReadBlobMSBLong(image);
  pdb_image.note=ReadBlobMSBLong(image);
  pdb_image.x_last=ReadBlobMSBShort(image);
  pdb_image.y_last=ReadBlobMSBShort(image);
  pdb_image.reserved_2=ReadBlobMSBLong(image);
  pdb_image.x_anchor=ReadBlobMSBShort(image);
  pdb_image.y_anchor=ReadBlobMSBShort(image);
  pdb_image.width=ReadBlobMSBShort(image);
  pdb_image.height=ReadBlobMSBShort(image);
  if (image->logging)
    LogPDPImage(&pdb_image);
  /*
    Initialize image structure.
  */
  image->columns=pdb_image.width;
  image->rows=pdb_image.height;
  image->depth=8;
  image->storage_class=PseudoClass;
  bits_per_pixel=pdb_image.type == 0 ? 2 : pdb_image.type == 2 ? 4 : 1;
  if (!AllocateImageColormap(image,1 << bits_per_pixel))
    ThrowPDBReaderException(ResourceLimitError,MemoryAllocationFailed,image);
  if (image_info->ping)
    {
      CloseBlob(image);
      StopTimer(&image->timer);
      return(image);
    }

  if (CheckImagePixelLimits(image, exception) != MagickPass)
    ThrowPDBReaderException(ResourceLimitError,ImagePixelLimitExceeded,image);

  packets=MagickArraySize(MagickArraySize(bits_per_pixel,image->columns)/8,
                          image->rows);
  pixels=MagickAllocateResourceLimitedMemory(unsigned char *,packets + (packets != 0 ? 256 : 0));
  if (pixels == (unsigned char *) NULL)
    ThrowPDBReaderException(ResourceLimitWarning,MemoryAllocationFailed,image);
  (void) memset(pixels,0,packets+256);
  switch (pdb_image.version)
  {
    case 0:
    {
      image->compression=NoCompression;
      if (ReadBlob(image,packets,(char *) pixels) != packets)
        {
          MagickFreeResourceLimitedMemory(pixels);
          ThrowReaderException(CorruptImageError,UnexpectedEndOfFile,image);
        }
      break;
    }
    case 1:
    {
      image->compression=RLECompression;
      if (DecodeImage(image,pixels,packets) == MagickFail)
        ThrowPDBReaderException(CorruptImageError,UnexpectedEndOfFile,image);
      break;
    }
    default:
      {
        ThrowPDBReaderException(CorruptImageError,UnrecognizedImageCompression,image);
      }
  }
  p=pixels;
  switch (bits_per_pixel)
  {
    case 1:
    {
      int
        bit;

      /*
        Read 1-bit PDB image.
      */
      for (y=0; y < image->rows; y++)
      {
        q=SetImagePixels(image,0,y,image->columns,1);
        if (q == (PixelPacket *) NULL)
          break;
        indexes=AccessMutableIndexes(image);
        bit=0;
        for (x=0; x < image->columns; x++)
        {
          index=(*p & (0x80U >> bit) ? 0x00U : 0x01U);
          indexes[x]=index;
          *q++=image->colormap[index];
          bit++;
          if (bit == 8)
            {
              p++;
              bit=0;
            }
        }
        if (!SyncImagePixels(image))
          break;
        if (QuantumTick(y,image->rows))
          if (!MagickMonitorFormatted(y,image->rows,exception,LoadImageText,
                                      image->filename,
                                      image->columns,image->rows))
            break;
      }
      break;
    }
    case 2:
    {
      /*
        Read 2-bit PDB image.
      */
      unsigned int
        shift;

      for (y=0; y < image->rows; y++)
      {
        q=SetImagePixels(image,0,y,image->columns,1);
        if (q == (PixelPacket *) NULL)
          break;
        indexes=AccessMutableIndexes(image);
        shift = 8;
        for (x=0; x < image->columns; x++)
          {
            shift -= 2;
            index=(IndexPacket) (3-((*p >> shift) & 0x03));
            VerifyColormapIndex(image,index);
            indexes[x]=index;
            *q++=image->colormap[index];
            if (shift == 0)
              {
                shift = 8;
                p++;
              }
          }
        if (!SyncImagePixels(image))
          break;
        if (QuantumTick(y,image->rows))
          if (!MagickMonitorFormatted(y,image->rows,exception,LoadImageText,
                                      image->filename,
                                      image->columns,image->rows))
            break;
      }
      break;
    }
    case 4:
    {
      /*
        Read 4-bit PDB image.
      */
      unsigned int
        shift;

      for (y=0; y < image->rows; y++)
      {
        q=SetImagePixels(image,0,y,image->columns,1);
        if (q == (PixelPacket *) NULL)
          break;
        indexes=AccessMutableIndexes(image);
        shift = 8;
        for (x=0; x < image->columns; x++)
        {
          shift -= 4;
          index=(IndexPacket) (15-((*p >> shift) & 0x0f));
          VerifyColormapIndex(image,index);
          indexes[x]=index;
          *q++=image->colormap[index];
          if (shift == 0)
            {
              shift = 8;
              p++;
            }
        }
        if (!SyncImagePixels(image))
          break;
        if (QuantumTick(y,image->rows))
          if (!MagickMonitorFormatted(y,image->rows,exception,LoadImageText,
                                      image->filename,
                                      image->columns,image->rows))
            break;
      }
      break;
    }
    default:
      {
        ThrowPDBReaderException(CorruptImageError,ImproperImageHeader,image);
      }
  }
  MagickFreeResourceLimitedMemory(pixels);
  if (EOFBlob(image))
    ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,
      image->filename);
  if ((offset-TellBlob(image)) == 0)
    {
      char
        *comment;

      int
        c;

      size_t
        length;

      /*
        Read comment.
      */
      c=ReadBlobByte(image);
      length=MaxTextExtent;
      comment=MagickAllocateResourceLimitedMemory(char *,length+1);
      if (comment != (char *) NULL)
        {
          register char
            *p=comment;

          p[0]='\0';
          for ( ; c != EOF; p++)
            {
              if ((size_t) (p-comment) >= length)
                {
                  char
                    *new_comment;

                  length+=MaxTextExtent;
                  new_comment=MagickReallocateResourceLimitedMemory(char *,comment,length+1);
                  if (new_comment == (char *) NULL)
                    {
                      MagickFreeResourceLimitedMemory(comment);
                      break;
                    }
                  comment=new_comment;
                  p=comment+strlen(comment);
                }
              *p=c;
              *(p+1)='\0';
              c=ReadBlobByte(image);
            }
        }
      if (comment == (char *) NULL)
        ThrowPDBReaderException(ResourceLimitError,MemoryAllocationFailed,image);
      (void) SetImageAttribute(image,"comment",comment);
      MagickFreeResourceLimitedMemory(comment);
    }
  CloseBlob(image);
  StopTimer(&image->timer);
  return(image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r P D B I m a g e                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterPDBImage adds attributes for the PDB image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterPDBImage method is:
%
%      RegisterPDBImage(void)
%
*/
ModuleExport void RegisterPDBImage(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("PDB");
  entry->decoder=(DecoderHandler) ReadPDBImage;
  entry->encoder=(EncoderHandler) WritePDBImage;
  entry->magick=(MagickHandler) IsPDB;
  entry->description="Palm Database ImageViewer Format";
  entry->module="PDB";
  entry->coder_class=UnstableCoderClass;
  (void) RegisterMagickInfo(entry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r P D B I m a g e                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnregisterPDBImage removes format registrations made by the
%  PDB module from the list of supported formats.
%
%  The format of the UnregisterPDBImage method is:
%
%      UnregisterPDBImage(void)
%
*/
ModuleExport void UnregisterPDBImage(void)
{
  (void) UnregisterMagickInfo("PDB");
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e P D B I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method WritePDBImage writes an image
%
%  The format of the WritePDBImage method is:
%
%      unsigned int WritePDBImage(const ImageInfo *image_info,Image *image)
%
%  A description of each parameter follows.
%
%    o status: Method WritePDBImage return True if the image is written.
%      False is returned is there is a memory shortage or if the image file
%      fails to write.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o image:  A pointer to an Image structure.
%
%
*/

static unsigned char *EncodeRLE(unsigned char *destination,
  unsigned char *source,unsigned int literal,unsigned int repeat)
{
  if (literal != 0)
    *destination++=literal-1;
  (void) memcpy(destination,source,literal);
  destination+=literal;
  if (repeat != 0)
    {
      *destination++=0x80 | (repeat-1);
      *destination++=source[literal];
    }
  return(destination);
}

#define ThrowPDBWriterException(code_,reason_,image_) \
{ \
  MagickFreeResourceLimitedMemory(buffer);                     \
  MagickFreeResourceLimitedMemory(p);                          \
  MagickFreeResourceLimitedMemory(scanline);                   \
  ThrowWriterException(code_,reason_,image_); \
}

static unsigned int WritePDBImage(const ImageInfo *image_info,Image *image)
{
  int
    bits;

  unsigned long
    y;

  PDBImage
    pdb_image;

  PDBInfo
    pdb_info;

  register long
    x;

  unsigned char
    *buffer = (unsigned char *) NULL,
    *p = (unsigned char *) NULL,
    *q,
    *scanline = (unsigned char *) NULL;

  unsigned int
    bits_per_pixel,
    packet_size,
    status;

  size_t
    packets;

  unsigned long
    literal,
    repeat;

  const ImageAttribute
    *comment;

  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Dimensions: %lux%lu",
                          image->columns,image->rows);

  /*
    Open output image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,&image->exception);
  if (status == False)
    ThrowPDBWriterException(FileOpenError,UnableToOpenFile,image);
  (void) TransformColorspace(image,RGBColorspace);
  (void) SetImageType(image,GrayscaleType);
  bits_per_pixel=image->depth;
  if (GetImageType(image,&image->exception) == BilevelType)
    bits_per_pixel=1;
  if ((bits_per_pixel != 1) && (bits_per_pixel != 2))
    bits_per_pixel=4;
  (void) memset(&pdb_info,0,sizeof(pdb_info));
  (void) strlcpy(pdb_info.name,image_info->filename,sizeof(pdb_info.name));
  pdb_info.attributes=0;
  pdb_info.version=0;
  pdb_info.create_time=time(NULL);
  pdb_info.modify_time=pdb_info.create_time;
  pdb_info.archive_time=0;
  pdb_info.modify_number=0;
  pdb_info.application_info=0;
  pdb_info.sort_info=0;
  (void) memcpy(pdb_info.type,"vIMG",4);
  (void) memcpy(pdb_info.id,"View",4);
  pdb_info.seed=0;
  pdb_info.next_record=0;
  comment=GetImageAttribute(image,"comment");
  pdb_info.number_records=1;
  if ((comment != (ImageAttribute *) NULL) && (comment->value != (char *) NULL))
    pdb_info.number_records++;
  if (image->logging)
    LogPDPInfo(&pdb_info);
  (void) WriteBlob(image,32,pdb_info.name);
  (void) WriteBlobMSBShort(image,pdb_info.attributes);
  (void) WriteBlobMSBShort(image,pdb_info.version);
  (void) WriteBlobMSBLong(image,pdb_info.create_time);
  (void) WriteBlobMSBLong(image,pdb_info.modify_time);
  (void) WriteBlobMSBLong(image,pdb_info.archive_time);
  (void) WriteBlobMSBLong(image,pdb_info.modify_number);
  (void) WriteBlobMSBLong(image,pdb_info.application_info);
  (void) WriteBlobMSBLong(image,pdb_info.sort_info);
  (void) WriteBlob(image,4,pdb_info.type);
  (void) WriteBlob(image,4,pdb_info.id);
  (void) WriteBlobMSBLong(image,pdb_info.seed);
  (void) WriteBlobMSBLong(image,pdb_info.next_record);
  (void) WriteBlobMSBShort(image,pdb_info.number_records);
  (void) memset(&pdb_image,0,sizeof(pdb_image));
  (void) strlcpy(pdb_image.name,pdb_info.name,sizeof(pdb_image.name));
  pdb_image.version=1;  /* RLE Compressed */
  switch(bits_per_pixel)
  {
    case 1: pdb_image.type=0xffU; break;  /* monochrome */
    case 2: pdb_image.type=0x00U; break;  /* 2 bit gray */
    default: pdb_image.type=0x02U;        /* 4 bit gray */
  }
  pdb_image.reserved_1=0;
  pdb_image.note=0;
  pdb_image.x_last=0;
  pdb_image.y_last=0;
  pdb_image.reserved_2=0;
  pdb_image.x_anchor=(short) 0xffff;
  pdb_image.y_anchor=(short) 0xffff;
  pdb_image.width=(short) image->columns;
  if (image->columns % 16)
    pdb_image.width=(short) (16*(image->columns/16+1));
  pdb_image.height=(short) image->rows;
  if (image->logging)
    LogPDPImage(&pdb_image);
  if ((pdb_image.width < image->columns) ||
      (pdb_image.height != image->rows))
    ThrowPDBWriterException(CoderError,ImageColumnOrRowSizeIsNotSupported, image);
  packets=MagickArraySize(MagickArraySize(MagickArraySize(bits_per_pixel,
                                                          pdb_image.width)/8,
                                          pdb_image.height),2);
  p=MagickAllocateResourceLimitedMemory(unsigned char *,packets);
  if (p == (unsigned char *) NULL)
    ThrowPDBWriterException(ResourceLimitWarning,MemoryAllocationFailed,image);
  buffer=MagickAllocateResourceLimitedMemory(unsigned char *,512);
  if (buffer == (unsigned char *) NULL)
    ThrowPDBWriterException(ResourceLimitWarning,MemoryAllocationFailed,image);
  (void) memset(buffer,0,512);
  packet_size=bits_per_pixel > 8 ? 2: 1;
  scanline=MagickAllocateResourceLimitedArray(unsigned char *,image->columns,packet_size);
  if (scanline == (unsigned char *) NULL)
    ThrowPDBWriterException(ResourceLimitWarning,MemoryAllocationFailed,image);
  (void) TransformColorspace(image,RGBColorspace);
  /*
    Convert to GRAY raster scanline.
  */
  bits=8/(long) bits_per_pixel-1;  /* start at most significant bits */
  literal=0;
  repeat=0;
  q=p;
  buffer[0]=0x00;
  for (y=0; y < image->rows; y++)
  {
    if (!AcquireImagePixels(image,0,y,image->columns,1,&image->exception))
      break;
    (void) memset(scanline,0, (size_t) image->columns*packet_size); /* FIXME: remove */
    (void) ExportImagePixelArea(image,GrayQuantum,bits_per_pixel,scanline,0,0);
    for (x=0; x < pdb_image.width; x++)
    {
      if (x < (long) image->columns)
        buffer[literal+repeat]|=(0xff-scanline[x*packet_size]) >>
          (8-bits_per_pixel) << bits*bits_per_pixel;
      bits--;
      if (bits < 0)
        {
          if (((literal+repeat) > 0) &&
              (buffer[literal+repeat] == buffer[literal+repeat-1]))
            {
              if (repeat == 0)
                {
                  literal--;
                  repeat++;
                }
              repeat++;
              if (0x7f < repeat)
                {
                  q=EncodeRLE(q,buffer,literal,repeat);
                  literal=0;
                  repeat=0;
                }
            }
          else
            {
              if (repeat >= 2)
                literal+=repeat;
              else
                {
                  q=EncodeRLE(q,buffer,literal,repeat);
                  buffer[0]=buffer[literal+repeat];
                  literal=0;
                }
              literal++;
              repeat=0;
              if (0x7f < literal)
                {
                  q=EncodeRLE(q,buffer,(literal < 0x80 ? literal : 0x80),0);
                  (void) memmove(buffer,buffer+literal+repeat,0x80);
                  literal-=0x80;
                }
            }
        bits=8/(long) bits_per_pixel-1;
        buffer[literal+repeat]=0x00;
      }
    }
    if (QuantumTick(y,image->rows))
      if (!MagickMonitorFormatted(y,image->rows,&image->exception,
                                  SaveImageText,image->filename,
                                  image->columns,image->rows))
        break;
  }
  q=EncodeRLE(q,buffer,literal,repeat);
  MagickFreeResourceLimitedMemory(scanline);
  MagickFreeResourceLimitedMemory(buffer);
  /*
    Write the Image record header.
  */
  (void) WriteBlobMSBLong(image,(magick_uint32_t)
    (TellBlob(image)+(size_t)8*pdb_info.number_records));
  (void) WriteBlobByte(image,0x40);
  (void) WriteBlobByte(image,0x6f);
  (void) WriteBlobByte(image,0x80);
  (void) WriteBlobByte(image,0);
  if (pdb_info.number_records > 1)
    {
      /*
        Write the comment record header.
      */
      (void) WriteBlobMSBLong(image,TellBlob(image)+8+58+q-p);
      (void) WriteBlobByte(image,0x40);
      (void) WriteBlobByte(image,0x6f);
      (void) WriteBlobByte(image,0x80);
      (void) WriteBlobByte(image,1);
    }
  /*
    Write the Image data.
  */
  (void) WriteBlob(image,32,pdb_image.name);
  (void) WriteBlobByte(image,pdb_image.version);
  (void) WriteBlobByte(image,pdb_image.type);
  (void) WriteBlobMSBLong(image,pdb_image.reserved_1);
  (void) WriteBlobMSBLong(image,pdb_image.note);
  (void) WriteBlobMSBShort(image,pdb_image.x_last);
  (void) WriteBlobMSBShort(image,pdb_image.y_last);
  (void) WriteBlobMSBLong(image,pdb_image.reserved_2);
  (void) WriteBlobMSBShort(image,pdb_image.x_anchor);
  (void) WriteBlobMSBShort(image,pdb_image.y_anchor);
  (void) WriteBlobMSBShort(image,pdb_image.width);
  (void) WriteBlobMSBShort(image,pdb_image.height);
  (void) WriteBlob(image,q-p,p);
  MagickFreeResourceLimitedMemory(p);
  if ((comment != (ImageAttribute *) NULL) && (comment->value != (char *) NULL))
    (void) WriteBlobString(image,comment->value);
  status &= CloseBlob(image);
  return(status);
}
