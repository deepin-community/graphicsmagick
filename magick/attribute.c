/*
% Copyright (C) 2003-2023 GraphicsMagick Group
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
%        AAA   TTTTT  TTTTT  RRRR   IIIII  BBBB   U   U  TTTTT  EEEEE         %
%       A   A    T      T    R   R    I    B   B  U   U    T    E             %
%       AAAAA    T      T    RRRR     I    BBBB   U   U    T    EEE           %
%       A   A    T      T    R R      I    B   B  U   U    T    E             %
%       A   A    T      T    R  R   IIIII  BBBB    UUU     T    EEEEE         %
%                                                                             %
%                                                                             %
%              Methods to Get/Set/Destroy Image Text Attributes               %
%                                                                             %
%                                                                             %
%                             Software Design                                 %
%                               John Cristy                                   %
%                              February 2000                                  %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  The Attributes methods gets, sets, or destroys attributes associated
%  with a particular image (e.g. comments, copyright, author, etc).
%
%
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/attribute.h"
#include "magick/blob.h"
#include "magick/log.h"
#include "magick/profile.h"
#include "magick/render.h"
#include "magick/tempfile.h"
#include "magick/utility.h"

/*
  Forward declarations.
*/
static void DestroyImageAttribute(ImageAttribute *attribute);

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   C l o n e I m a g e A t t r i b u t e s                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  CloneImageAttributes() copies the text attributes from one image to another.
%  Any text attributes in the destination image are preserved.
%  CloneImageAttributes returns MagickPass if all of the attribututes are
%  successfully cloned or MagickFail if there is a memory allocation error.
%
%  The format of the CloneImageAttributes method is:
%
%      MagickPassFail CloneImageAttributes(Image* clone_image,
%                                          const Image* original_image)
%
%  A description of each parameter follows:
%
%    o clone_image: The destination image.
%
%    o original_image: The source image.
%
%
*/
MagickExport MagickPassFail
CloneImageAttributes(Image* clone_image,
                     const Image* original_image)
{
  MagickPassFail
    status;

  ImageAttribute
    *cloned_attribute,
    *cloned_attributes;

  const ImageAttribute
    *attribute;

  status = MagickPass;

  /*
    Search for tail of list (if any)
  */
  if ((cloned_attributes=clone_image->attributes))
    {
      for( ;
          cloned_attributes->next != (ImageAttribute *) NULL;
          cloned_attributes=cloned_attributes->next);
    }

  attribute=GetImageAttribute(original_image,(char *) NULL);
  for ( ; attribute != (const ImageAttribute *) NULL;
        attribute=attribute->next)
    {
      /*
        Construct AttributeInfo to append.
      */
      cloned_attribute=MagickAllocateMemory(ImageAttribute *,
                                            sizeof(ImageAttribute));
      if (cloned_attribute == (ImageAttribute *) NULL)
        {
          status = MagickFail;
          break;
        }
      cloned_attribute->key=AcquireString(attribute->key);
      cloned_attribute->length=attribute->length;
      cloned_attribute->value=
        MagickAllocateMemory(char *,cloned_attribute->length+1);
      cloned_attribute->previous=(ImageAttribute *) NULL;
      cloned_attribute->next=(ImageAttribute *) NULL;
      if ((cloned_attribute->value == (char *) NULL) ||
          (cloned_attribute->key == (char *) NULL))
        {
          DestroyImageAttribute(cloned_attribute);
          status = MagickFail;
          break;
        }
      (void) strlcpy(cloned_attribute->value,attribute->value,cloned_attribute->length+1);

      if (cloned_attributes == (ImageAttribute *) NULL)
        {
          /*
            Start list
          */
          cloned_attributes=cloned_attribute;
          clone_image->attributes=cloned_attributes;
        }
      else
        {
          /*
            Append to list
          */
          cloned_attributes->next=cloned_attribute;
          cloned_attribute->previous=cloned_attributes;
          cloned_attributes=cloned_attribute;
        }
    }

  return status;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D e s t r o y I m a g e A t t r i b u t e s                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DestroyImageAttributes() deallocates memory associated with the image
%  attribute list.
%
%  The format of the DestroyImageAttributes method is:
%
%      DestroyImageAttributes(Image *image)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%
*/
static void
DestroyImageAttribute(ImageAttribute *attribute)
{
  if (attribute == (ImageAttribute *) NULL)
    return;
  MagickFreeMemory(attribute->value);
  MagickFreeMemory(attribute->key);
  (void) memset(attribute,0xbf,sizeof(ImageAttribute));
  MagickFreeMemory(attribute);
}
MagickExport void DestroyImageAttributes(Image *image)
{
  ImageAttribute
    *attribute;

  register ImageAttribute
    *p;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  for (p=image->attributes; p != (ImageAttribute *) NULL; )
    {
      attribute=p;
      p=p->next;
      DestroyImageAttribute(attribute);
    }
  image->attributes=(ImageAttribute *) NULL;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t I m a g e A t t r i b u t e                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetImageAttribute() searches the list of image attributes and returns
%  a pointer to the attribute if it exists otherwise NULL.
%
%  The format of the GetImageAttribute method is:
%
%      const ImageAttribute *GetImageAttribute(const Image *image,
%        const char *key)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%    o key:  These character strings are the name of an image attribute to
%      return.
%
%
*/

static unsigned int
GenerateIPTCAttribute(Image *image,const char *key)
{
#if 0
  static const struct
  {
    char *name;
    int   dataset;
    int   record;
  }
#define IPTC_ATTRIBUTE(dataset,record,name) {name,dataset,record}
  IPTCAttributes[] =
  {
    IPTC_ATTRIBUTE(2,5,"Image Name"),
    IPTC_ATTRIBUTE(2,7,"Edit Status"),
    IPTC_ATTRIBUTE(2,10,"Priority"),
    IPTC_ATTRIBUTE(2,15,"Category"),
    IPTC_ATTRIBUTE(2,20,"Supplemental Category"),
    IPTC_ATTRIBUTE(2,22,"Fixture Identifier"),
    IPTC_ATTRIBUTE(2,25,"Keyword"),
    IPTC_ATTRIBUTE(2,30,"Release Date"),
    IPTC_ATTRIBUTE(2,35,"Release Time"),
    IPTC_ATTRIBUTE(2,40,"Special Instructions"),
    IPTC_ATTRIBUTE(2,45,"Reference Service"),
    IPTC_ATTRIBUTE(2,47,"Reference Date"),
    IPTC_ATTRIBUTE(2,50,"Reference Number"),
    IPTC_ATTRIBUTE(2,55,"Created Date"),
    IPTC_ATTRIBUTE(2,60,"Created Time"),
    IPTC_ATTRIBUTE(2,65,"Originating Program"),
    IPTC_ATTRIBUTE(2,70,"Program Version"),
    IPTC_ATTRIBUTE(2,75,"Object Cycle"),
    IPTC_ATTRIBUTE(2,80,"Byline"),
    IPTC_ATTRIBUTE(2,85,"Byline Title"),
    IPTC_ATTRIBUTE(2,90,"City"),
    IPTC_ATTRIBUTE(2,95,"Province State"),
    IPTC_ATTRIBUTE(2,100,"Country Code"),
    IPTC_ATTRIBUTE(2,101,"Country"),
    IPTC_ATTRIBUTE(2,103,"Original Transmission Reference"),
    IPTC_ATTRIBUTE(2,105,"Headline"),
    IPTC_ATTRIBUTE(2,110,"Credit"),
    IPTC_ATTRIBUTE(2,115,"Source"),
    IPTC_ATTRIBUTE(2,116,"Copyright String"),
    IPTC_ATTRIBUTE(2,120,"Caption"),
    IPTC_ATTRIBUTE(2,121,"Local Caption"),
    IPTC_ATTRIBUTE(2,122,"Caption Writer"),
    IPTC_ATTRIBUTE(2,200,"Custom Field 1"),
    IPTC_ATTRIBUTE(2,201,"Custom Field 2"),
    IPTC_ATTRIBUTE(2,202,"Custom Field 3"),
    IPTC_ATTRIBUTE(2,203,"Custom Field 4"),
    IPTC_ATTRIBUTE(2,204,"Custom Field 5"),
    IPTC_ATTRIBUTE(2,205,"Custom Field 6"),
    IPTC_ATTRIBUTE(2,206,"Custom Field 7"),
    IPTC_ATTRIBUTE(2,207,"Custom Field 8"),
    IPTC_ATTRIBUTE(2,208,"Custom Field 9"),
    IPTC_ATTRIBUTE(2,209,"Custom Field 10"),
    IPTC_ATTRIBUTE(2,210,"Custom Field 11"),
    IPTC_ATTRIBUTE(2,211,"Custom Field 12"),
    IPTC_ATTRIBUTE(2,212,"Custom Field 13"),
    IPTC_ATTRIBUTE(2,213,"Custom Field 14"),
    IPTC_ATTRIBUTE(2,214,"Custom Field 15"),
    IPTC_ATTRIBUTE(2,215,"Custom Field 16"),
    IPTC_ATTRIBUTE(2,216,"Custom Field 17"),
    IPTC_ATTRIBUTE(2,217,"Custom Field 18"),
    IPTC_ATTRIBUTE(2,218,"Custom Field 19"),
    IPTC_ATTRIBUTE(2,219,"Custom Field 20")
  };
#endif

  char
    *attribute;

  int
    count,
    dataset,
    record;

  register long
    i;

  size_t
    length;

  const unsigned char
    *profile;

  size_t
    profile_length;

  if((profile=GetImageProfile(image,"IPTC",&profile_length)) == 0)
    return(False);
  count=sscanf(key,"IPTC:%d:%d",&dataset,&record);
  if (count != 2)
    return(False);
  for (i=0; i < (long) profile_length; i++)
    {
      if (profile[i] != 0x1cU)
        continue;
      if (profile[i+1] != dataset)
        {
          /* fprintf(stderr,"Skipping dataset %d\n",profile[i+1]); */
          continue;
        }
      if (profile[i+2] != record)
        {
          /* fprintf(stderr,"Skipping record %d\n",profile[i+2]); */
          continue;
        }
      length=(size_t) profile[i+3] << 8;
      length|=(size_t) profile[i+4];
      attribute=MagickAllocateMemory(char *,length+1);
      if (attribute == (char *) NULL)
        continue;
      (void) strlcpy(attribute,(char *) profile+i+5,length+1);
      (void) SetImageAttribute(image,key,(const char *) attribute);
      MagickFreeMemory(attribute);
      break;
    }
  return(i < (long) profile_length);
}

static unsigned char
ReadByte(unsigned char **p,size_t *length)
{
  unsigned char
    c;

  if (*length < 1)
    return(0xff);
  c=(*(*p)++);
  (*length)--;
  return(c);
}

static magick_int32_t
ReadMSBLong(unsigned char **p,size_t *length)
{
  int
    c;

  union
  {
    magick_uint32_t u;
    magick_int32_t s;
  } value;

  register unsigned int
    i;

  unsigned char
    buffer[4];

  if (*length < 4)
    return(-1);
  for (i=0; i < 4; i++)
  {
    c=(*(*p)++);
    (*length)--;
    buffer[i]=(unsigned char) c;
  }
  value.u=(magick_uint32_t) (buffer[0] & 0xff) << 24;
  value.u|=(magick_uint32_t) buffer[1] << 16;
  value.u|=(magick_uint32_t) buffer[2] << 8;
  value.u|=(magick_uint32_t) buffer[3];
  return(value.s);
}

static magick_int32_t
ReadMSBShort(unsigned char **p,size_t *length)
{
  int
    c;

  union
  {
    magick_uint32_t u;
    magick_int32_t s;
  } value;

  register unsigned int
    i;

  unsigned char
    buffer[2];

  if (*length < 2)
    return(-1);
  for (i=0; i < 2; i++)
  {
    c=(*(*p)++);
    (*length)--;
    buffer[i]=(unsigned char) c;
  }
  value.u=(magick_uint32_t) (buffer[0] & 0xff) << 8;
  value.u|=(magick_uint32_t) buffer[1];
  return(value.s);
}

/*
  Advance 'blob' by 'amount' or the amount remaining in 'length'.
  Decrement 'length' by 'amount' or to zero.
*/
static inline size_t AdvanceBlob(const size_t amount, size_t length, unsigned char **blob)
{
  if (length > amount)
    {
      *blob+=amount;
      length-=amount;
    }
  else
    {
      *blob+=length;
      length=0U;
    }
  return length;
}

static char *
TracePSClippingPath(unsigned char *blob,size_t length,
                    const unsigned long columns,
                    const unsigned long rows)
{
  char
    *path,
    *message;

  int
    knot_count,
    selector;

  long
    x,
    y;

  PointInfo
    first[3],       /* First Bezier knot in sub-path */
    last[3],        /* Last seen Bezier knot in sub-path */
    point[3];       /* Current Bezier knot in sub-path */

  register long
    i;

  unsigned int
    in_subpath;

  ARG_NOT_USED(columns);
  ARG_NOT_USED(rows);

  first[0].x=first[0].y=first[1].x=first[1].y=0;
  last[1].x=last[1].y=last[2].x=last[2].y=0;
  path=AllocateString((char *) NULL);
  if (path == (char *) NULL)
    return((char *) NULL);
  message=AllocateString((char *) NULL);

  FormatString(message,"/ClipImage {\n");
  (void) ConcatenateString(&path,message);
  FormatString(message,"/c {curveto} bind def\n");
  (void) ConcatenateString(&path,message);
  FormatString(message,"/l {lineto} bind def\n");
  (void) ConcatenateString(&path,message);
  FormatString(message,"/m {moveto} bind def\n");
  (void) ConcatenateString(&path,message);
  FormatString(message,"/v {currentpoint 6 2 roll curveto} bind def\n");
  (void) ConcatenateString(&path,message);
  FormatString(message,"/y {2 copy curveto} bind def\n");
  (void) ConcatenateString(&path,message);
  FormatString(message,"/z {closepath} bind def\n");
  (void) ConcatenateString(&path,message);
  FormatString(message,"newpath\n");
  (void) ConcatenateString(&path,message);

  knot_count=0;
  in_subpath=False;

  /*
    Open and closed subpaths are all closed in the following
    parser loop as there's no way for the polygon renderer
    to render an open path to a masking image.

    The clipping path format is defined in "Adobe Photoshop File
    Formats Specification" version 6.0 downloadable from adobe.com.
  */
  while (length > 0)
    {
      selector=ReadMSBShort(&blob,&length);
      switch (selector)
        {
        case 0:
        case 3:
          {
            if (knot_count == 0)
              {
                /*
                  Expected subpath length record
                */
                knot_count=ReadMSBShort(&blob,&length);
                length=AdvanceBlob(22U,length,&blob);
              }
            else
              {
                length=AdvanceBlob(24U,length,&blob);
              }
            break;
          }
        case 1:
        case 2:
        case 4:
        case 5:
          {
            if (knot_count == 0)
              {
                /*
                  Unexpected subpath knot
                */
                length=AdvanceBlob(24U,length,&blob);
              }
            else
              {
                /*
                  Add sub-path knot
                */
                for (i=0; i < 3; i++)
                  {
                    y=ReadMSBLong(&blob,&length);
                    x=ReadMSBLong(&blob,&length);
                    point[i].x=(double) x/4096/4096;
                    point[i].y=1.0-(double) y/4096/4096;
                  }
                if (!in_subpath)
                  {
                    FormatString(message,"%.6f %.6f m\n",
                                 point[1].x,point[1].y);
                    for (i=0; i < 3; i++)
                      {
                        first[i]=point[i];
                        last[i]=point[i];
                      }
                  }
                else
                  {
                    /*
                      Handle special cases when Bezier curves are used
                      to describe corners and straight lines. This
                      special handling is desirable to bring down the
                      size in bytes of the clipping path data.
                    */
                    if ((last[1].x == last[2].x) &&
                        (last[1].y == last[2].y) &&
                        (point[0].x == point[1].x) &&
                        (point[0].y == point[1].y))
                      {
                        /*
                          First control point equals first anchor
                          point and last control point equals last
                          anchor point. Straight line between anchor
                          points.
                        */
                        FormatString(message,"%.6f %.6f l\n",
                                     point[1].x,point[1].y);
                      }
                    else if ((last[1].x == last[2].x) &&
                             (last[1].y == last[2].y))
                      {
                        /* First control point equals first anchor point */
                        FormatString(message,"%.6f %.6f %.6f %.6f v\n",
                                     point[0].x,point[0].y,
                                     point[1].x,point[1].y);
                      }
                    else if ((point[0].x == point[1].x) &&
                             (point[0].y == point[1].y))
                      {
                        /* Last control point equals last anchor point. */
                        FormatString(message,"%.6f %.6f %.6f %.6f y\n",
                                     last[2].x,last[2].y,
                                     point[1].x,point[1].y);
                      }
                    else
                      {
                        /* The full monty */
                        FormatString(message,
                                     "%.6f %.6f %.6f %.6f %.6f %.6f c\n",
                                     last[2].x,last[2].y,point[0].x,
                                     point[0].y,point[1].x,
                                     point[1].y);
                      }
                    for (i=0; i < 3; i++)
                      last[i]=point[i];
                  }
                (void) ConcatenateString(&path,message);
                in_subpath=True;
                knot_count--;
                /*
                  Close the subpath if there are no more knots.
                */
                if (knot_count == 0)
                  {
                    /*
                      Same special handling as above except we compare
                      to the first point in the path and close the
                      path.
                    */
                    if ((last[1].x == last[2].x) &&
                        (last[1].y == last[2].y) &&
                        (first[0].x == first[1].x) &&
                        (first[0].y == first[1].y))
                      {
                        FormatString(message,"%.6f %.6f l z\n",
                                     first[1].x,first[1].y);
                      }
                    else if ((last[1].x == last[2].x) &&
                             (last[1].y == last[2].y))
                      {
                        FormatString(message,"%.6f %.6f %.6f %.6f v z\n",
                                     first[0].x,first[0].y,
                                     first[1].x,first[1].y);
                      }
                    else if ((first[0].x == first[1].x) &&
                             (first[0].y == first[1].y))
                      {
                        FormatString(message,"%.6f %.6f %.6f %.6f y z\n",
                                     last[2].x,last[2].y,
                                     first[1].x,first[1].y);
                      }
                    else
                      {
                        FormatString(message,
                                     "%.6f %.6f %.6f %.6f %.6f %.6f c z\n",
                                     last[2].x,last[2].y,
                                     first[0].x,first[0].y,
                                     first[1].x,first[1].y);
                      }
                    (void) ConcatenateString(&path,message);
                    in_subpath=False;
                  }
              }
            break;
          }
        case 6:
        case 7:
        case 8:
        default:
          {
            length=AdvanceBlob(24U,length,&blob);
            break;
          }
        }
    }
  /*
    Returns an empty PS path if the path has no knots.
  */
  FormatString(message,"eoclip\n");
  (void) ConcatenateString(&path,message);
  FormatString(message,"} bind def");
  (void) ConcatenateString(&path,message);
  MagickFreeMemory(message);
  return(path);
}

static char *
TraceSVGClippingPath(unsigned char *blob,
                     size_t length,
                     const unsigned long columns,
                     const unsigned long rows)
{
  char
    *path,
    *message;

  int
    knot_count,
    selector;

  long
    x,
    y;

  PointInfo
    first[3],
    last[3],
    point[3];

  register long
    i;

  unsigned int
    in_subpath;

  first[0].x=first[0].y=first[1].x=first[1].y=0;
  last[1].x=last[1].y=last[2].x=last[2].y=0;
  path=AllocateString((char *) NULL);
  if (path == (char *) NULL)
    return((char *) NULL);
  message=AllocateString((char *) NULL);

  FormatString(message,"<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n");
  (void) ConcatenateString(&path,message);
  FormatString(message,"<svg width=\"%lu\" height=\"%lu\">\n",columns,rows);
  (void) ConcatenateString(&path,message);
  FormatString(message,"<g>\n");
  (void) ConcatenateString(&path,message);
  FormatString(message,"<path style=\"fill:#00000000;stroke:#00000000;");
  (void) ConcatenateString(&path,message);
  FormatString(message,"stroke-width:0;stroke-antialiasing:false\" d=\"\n");
  (void) ConcatenateString(&path,message);

  knot_count=0;
  in_subpath=False;

  /*
    Open and closed subpaths are all closed in the following parser
    loop as there's no way for the polygon renderer to render an open
    path to a masking image.

    The clipping path format is defined in "Adobe Photoshop File
    Formats Specification" version 6.0 downloadable from adobe.com.
  */
  while (length > 0)
    {
      selector=ReadMSBShort(&blob,&length);
      switch (selector)
        {
        case 0:
        case 3:
          {
            if (knot_count == 0)
              {
                /*
                  Expected subpath length record
                */
                knot_count=ReadMSBShort(&blob,&length);
                length=AdvanceBlob(22U,length,&blob);
              }
            else
              {
                length=AdvanceBlob(24U,length,&blob);
              }
            break;
          }
        case 1:
        case 2:
        case 4:
        case 5:
          {
            if (knot_count == 0)
              {
                /*
                  Unexpected subpath knot
                */
                length=AdvanceBlob(24U,length,&blob);
              }
            else
              {
                /*
                  Add sub-path knot
                */
                for (i=0; i < 3; i++)
                  {
                    y=ReadMSBLong(&blob,&length);
                    x=ReadMSBLong(&blob,&length);
                    point[i].x=(double) x*columns/4096.0/4096.0;
                    point[i].y=(double) y*rows/4096.0/4096.0;
                  }
                if (!in_subpath)
                  {
                    FormatString(message,"M %.6f,%.6f\n",
                                 point[1].x,point[1].y);
                    for (i=0; i < 3; i++)
                      {
                        first[i]=point[i];
                        last[i]=point[i];
                      }
                  }
                else
                  {
                    /*
                      Handle special case when Bezier curves are used
                      to describe straight lines.
                    */
                    if ((last[1].x == last[2].x) &&
                        (last[1].y == last[2].y) &&
                        (point[0].x == point[1].x) &&
                        (point[0].y == point[1].y))
                      {
                        /*
                          First control point equals first anchor
                          point and last control point equals last
                          anchor point. Straight line between anchor
                          points.
                        */
                        FormatString(message,"L %.6f,%.6f\n",
                                     point[1].x,point[1].y);
                      }
                    else
                      {
                        FormatString(message,
                                     "C %.6f,%.6f %.6f,%.6f %.6f,%.6f\n",
                                     last[2].x,last[2].y,
                                     point[0].x,point[0].y,
                                     point[1].x,point[1].y);
                      }
                    for (i=0; i < 3; i++)
                      last[i]=point[i];
                  }
                (void) ConcatenateString(&path,message);
                in_subpath=True;
                knot_count--;
                /*
                  Close the subpath if there are no more knots.
                */
                if (knot_count == 0)
                  {
                    /*
                      Same special handling as above except we compare
                      to the first point in the path and close the
                      path.
                    */
                    if ((last[1].x == last[2].x) &&
                        (last[1].y == last[2].y) &&
                        (first[0].x == first[1].x) &&
                        (first[0].y == first[1].y))
                      {
                        FormatString(message,
                                     "L %.6f,%.6f Z\n",first[1].x,first[1].y);
                      }
                    else
                      {
                        FormatString(message,
                                     "C %.6f,%.6f %.6f,%.6f %.6f,%.6f Z\n",
                                     last[2].x,last[2].y,
                                     first[0].x,first[0].y,
                                     first[1].x,first[1].y);
                        (void) ConcatenateString(&path,message);
                      }
                    in_subpath=False;
                  }
              }
            break;
          }
        case 6:
        case 7:
        case 8:
        default:
          {
            length=AdvanceBlob(24U,length,&blob);
            break;
          }
        }
    }
  /*
    Returns an empty SVG image if the path has no knots.
  */
  FormatString(message,"\"/>\n");
  (void) ConcatenateString(&path,message);
  FormatString(message,"</g>\n");
  (void) ConcatenateString(&path,message);
  FormatString(message,"</svg>\n");
  (void) ConcatenateString(&path,message);
  MagickFreeMemory(message);
  return(path);
}

static int
Generate8BIMAttribute(Image *image,const char *key)
{
  char
    *attribute,
    name[MaxTextExtent],
    format[MaxTextExtent],
    *resource;

  int
    id,
    start,
    stop,
    sub_number;

  register long
    i;

  size_t
    length;

  unsigned char
    *info;

  unsigned int
    status;

  long
    count;

  const unsigned char
    *profile;

  size_t
    profile_length;

  if ((profile=GetImageProfile(image,"IPTC",&profile_length)) == 0)
    return(False);

  /*
    There may be spaces in resource names, but there are no newlines,
    so use a newline as terminator to get the full name.
  */
  count=sscanf(key,"8BIM:%d,%d:%[^\n]\n%[^\n]",&start,&stop,name,format);
  if ((count != 2) && (count != 3) && (count != 4))
    return(False);
  if (count < 4)
    (void)strlcpy(format,"SVG",sizeof(format));
  if (count < 3)
    *name='\0';
  sub_number=1;
  if (*name == '#')
    sub_number=MagickAtoL(&name[1]);
  sub_number=Max(sub_number,1);
  resource=(char *) NULL;

  status=False;
  length=profile_length;
  /*
    FIXME: following cast should not be necessary but info can't be
    const due to odd function design.
  */
  info=(unsigned char *) profile;

  while ((length > 0) && (status == False))
    {
      if (ReadByte(&info,&length) != '8')
        continue;
      if (ReadByte(&info,&length) != 'B')
        continue;
      if (ReadByte(&info,&length) != 'I')
        continue;
      if (ReadByte(&info,&length) != 'M')
        continue;
      id=ReadMSBShort(&info,&length);
      if (id < start)
        continue;
      if (id > stop)
        continue;
      if (resource != (char *)NULL)
        MagickFreeMemory(resource);
      count=ReadByte(&info,&length);
      if ((count > 0) && ((size_t) count <= length))
        {
          resource=(char *) MagickAllocateMemory(char *,
                                                 (size_t) count+MaxTextExtent);
          if (resource != (char *) NULL)
            {
              for (i=0; i < count; i++)
                resource[i]=(char) ReadByte(&info,&length);
              resource[count]='\0';
            }
        }
      if (!(count & 0x01))
        (void) ReadByte(&info,&length);
      count=ReadMSBLong(&info,&length);
      /*
        ReadMSBLong() can return negative values such as -1 or any
        other negative value.  Make sure that it is in range.
      */
      if ((count < 0) || ((size_t) count > length))
        {
          length=0; /* Quit loop */
          continue;
        }
      if ((*name != '\0') && (*name != '#'))
        {
          if ((resource == (char *) NULL) ||
              (LocaleCompare(name,resource) != 0))
            {
              /*
                No name match, scroll forward and try next resource.
              */
              info+=count;
              length-=count;
              continue;
            }
        }
      if ((*name == '#') && (sub_number != 1))
        {
          /*
            No numbered match, scroll forward and try next resource.
          */
          sub_number--;
          info+=count;
          length-=count;
          continue;
        }
      /*
        We have the resource of interest.
      */
      attribute=(char *) MagickAllocateMemory(char *,
                                              (size_t) count+MaxTextExtent);
      if (attribute != (char *) NULL)
        {
          (void) memcpy(attribute,(char *) info,(size_t) count);
          attribute[count]='\0';
          info+=count;
          length-=count;
          if ((id <= 1999) || (id >= 2999))
            {
              (void) SetImageAttribute(image,key,(const char *) attribute);
            }
          else
            {
              char
                *path;
              if (LocaleCompare("SVG",format) == 0)
                path=TraceSVGClippingPath((unsigned char *) attribute,count,
                                          image->columns,image->rows);
              else
                path=TracePSClippingPath((unsigned char *) attribute,count,
                                         image->columns,image->rows);
              (void) SetImageAttribute(image,key,(const char *) path);
              MagickFreeMemory(path);
            }
          MagickFreeMemory(attribute);
          status=True;
        }
    }
  if (resource != (char *)NULL)
    MagickFreeMemory(resource);
  return(status);
}

#define DE_STACK_SIZE  16
#define EXIF_DELIMITER  "\n"
#define EXIF_NUM_FORMATS  12
#define EXIF_FMT_BYTE  1
#define EXIF_FMT_STRING  2
#define EXIF_FMT_USHORT  3
#define EXIF_FMT_ULONG  4
#define EXIF_FMT_URATIONAL  5
#define EXIF_FMT_SBYTE  6
#define EXIF_FMT_UNDEFINED  7
#define EXIF_FMT_SSHORT  8
#define EXIF_FMT_SLONG  9
#define EXIF_FMT_SRATIONAL  10
#define EXIF_FMT_SINGLE  11
#define EXIF_FMT_DOUBLE  12
#define EXIF_TAG_START  0x0100
#define EXIF_TAG_STOP  0xFFFF
#define TAG_EXIF_OFFSET  0x8769
#define TAG_INTEROP_OFFSET  0xa005
#define GPS_TAG_START 0x01
#define GPS_TAG_STOP  0x1D
#define GPS_OFFSET 0x8825
#define GPS_LATITUDE 0x0002
#define GPS_LONGITUDE 0x0004
#define GPS_TIMESTAMP 0x0007
#define MAX_TAGS_PER_IFD 1024 /* Maximum tags allowed per IFD */
#define EXIF_ORIENTATION 0x0112

static const struct
{
  unsigned short
    tag;

  const char
    description[30];

}
tag_table[] =
  {
#define TAG_INFO(tag,description) {tag,description}
    TAG_INFO(0x01, "GPSLatitudeRef"),
    TAG_INFO(0x02, "GPSLatitude"),
    TAG_INFO(0x03, "GPSLongitudeRef"),
    TAG_INFO(0x04, "GPSLongitude"),
    TAG_INFO(0x05, "GPSAltitudeRef"),
    TAG_INFO(0x06, "GPSAltitude"),
    TAG_INFO(0x07, "GPSTimeStamp"),
    TAG_INFO(0x08, "GPSSatellites"),
    TAG_INFO(0x09, "GPSStatus"),
    TAG_INFO(0x0A, "GPSMeasureMode"),
    TAG_INFO(0x0B, "GPSDOP"),
    TAG_INFO(0x0C, "GPSSpeedRef"),
    TAG_INFO(0x0D, "GPSSpeed"),
    TAG_INFO(0x0E, "GPSTrackRef"),
    TAG_INFO(0x0F, "GPSTrack"),
    TAG_INFO(0x10, "GPSImgDirectionRef"),
    TAG_INFO(0x11, "GPSImgDirection"),
    TAG_INFO(0x12, "GPSMapDatum"),
    TAG_INFO(0x13, "GPSDestLatitudeRef"),
    TAG_INFO(0x14, "GPSDestLatitude"),
    TAG_INFO(0x15, "GPSDestLongitudeRef"),
    TAG_INFO(0x16, "GPSDestLongitude"),
    TAG_INFO(0x17, "GPSDestBearingRef"),
    TAG_INFO(0x18, "GPSDestBearing"),
    TAG_INFO(0x19, "GPSDestDistanceRef"),
    TAG_INFO(0x1A, "GPSDestDistance"),
    TAG_INFO(0x1D, "GPSDateStamp"),
    TAG_INFO(0x100, "ImageWidth"),
    TAG_INFO(0x101, "ImageLength"),
    TAG_INFO(0x102, "BitsPerSample"),
    TAG_INFO(0x103, "Compression"),
    TAG_INFO(0x106, "PhotometricInterpretation"),
    TAG_INFO(0x10A, "FillOrder"),
    TAG_INFO(0x10D, "DocumentName"),
    TAG_INFO(0x10E, "ImageDescription"),
    TAG_INFO(0x10F, "Make"),
    TAG_INFO(0x110, "Model"),
    TAG_INFO(0x111, "StripOffsets"),
    TAG_INFO(0x112, "Orientation"),
    TAG_INFO(0x115, "SamplesPerPixel"),
    TAG_INFO(0x116, "RowsPerStrip"),
    TAG_INFO(0x117, "StripByteCounts"),
    TAG_INFO(0x118, "MinSampleValue"),
    TAG_INFO(0x119, "MaxSampleValue"),
    TAG_INFO(0x11A, "XResolution"),
    TAG_INFO(0x11B, "YResolution"),
    TAG_INFO(0x11C, "PlanarConfiguration"),
    TAG_INFO(0x11D, "PageName"),
    TAG_INFO(0x11E, "XPosition"),
    TAG_INFO(0x11F, "YPosition"),
    TAG_INFO(0x120, "FreeOffsets"),
    TAG_INFO(0x121, "FreeByteCounts"),
    TAG_INFO(0x122, "GrayResponseUnit"),
    TAG_INFO(0x123, "GrayResponseCurve"),
    TAG_INFO(0x124, "T4Options"),
    TAG_INFO(0x125, "T6Options"),
    TAG_INFO(0x128, "ResolutionUnit"),
    TAG_INFO(0x12D, "TransferFunction"),
    TAG_INFO(0x131, "Software"),
    TAG_INFO(0x132, "DateTime"),
    TAG_INFO(0x13B, "Artist"),
    TAG_INFO(0x13C, "HostComputer"),
    TAG_INFO(0x13D, "Predictor"),
    TAG_INFO(0x13E, "WhitePoint"),
    TAG_INFO(0x13F, "PrimaryChromaticities"),
    TAG_INFO(0x140, "ColorMap"),
    TAG_INFO(0x141, "HalfToneHints"),
    TAG_INFO(0x142, "TileWidth"),
    TAG_INFO(0x143, "TileLength"),
    TAG_INFO(0x144, "TileOffsets"),
    TAG_INFO(0x145, "TileByteCounts"),
    TAG_INFO(0x14A, "SubIFD"),
    TAG_INFO(0x14C, "InkSet"),
    TAG_INFO(0x14D, "InkNames"),
    TAG_INFO(0x14E, "NumberOfInks"),
    TAG_INFO(0x150, "DotRange"),
    TAG_INFO(0x151, "TargetPrinter"),
    TAG_INFO(0x152, "ExtraSample"),
    TAG_INFO(0x153, "SampleFormat"),
    TAG_INFO(0x154, "SMinSampleValue"),
    TAG_INFO(0x155, "SMaxSampleValue"),
    TAG_INFO(0x156, "TransferRange"),
    TAG_INFO(0x157, "ClipPath"),
    TAG_INFO(0x158, "XClipPathUnits"),
    TAG_INFO(0x159, "YClipPathUnits"),
    TAG_INFO(0x15A, "Indexed"),
    TAG_INFO(0x15B, "JPEGTables"),
    TAG_INFO(0x15F, "OPIProxy"),
    TAG_INFO(0x200, "JPEGProc"),
    TAG_INFO(0x201, "JPEGInterchangeFormat"),
    TAG_INFO(0x202, "JPEGInterchangeFormatLength"),
    TAG_INFO(0x203, "JPEGRestartInterval"),
    TAG_INFO(0x205, "JPEGLosslessPredictors"),
    TAG_INFO(0x206, "JPEGPointTransforms"),
    TAG_INFO(0x207, "JPEGQTables"),
    TAG_INFO(0x208, "JPEGDCTables"),
    TAG_INFO(0x209, "JPEGACTables"),
    TAG_INFO(0x211, "YCbCrCoefficients"),
    TAG_INFO(0x212, "YCbCrSubSampling"),
    TAG_INFO(0x213, "YCbCrPositioning"),
    TAG_INFO(0x214, "ReferenceBlackWhite"),
    TAG_INFO(0x2BC, "ExtensibleMetadataPlatform"),
    TAG_INFO(0x301, "Gamma"),
    TAG_INFO(0x302, "ICCProfileDescriptor"),
    TAG_INFO(0x303, "SRGBRenderingIntent"),
    TAG_INFO(0x320, "ImageTitle"),
    TAG_INFO(0x5001, "ResolutionXUnit"),
    TAG_INFO(0x5002, "ResolutionYUnit"),
    TAG_INFO(0x5003, "ResolutionXLengthUnit"),
    TAG_INFO(0x5004, "ResolutionYLengthUnit"),
    TAG_INFO(0x5005, "PrintFlags"),
    TAG_INFO(0x5006, "PrintFlagsVersion"),
    TAG_INFO(0x5007, "PrintFlagsCrop"),
    TAG_INFO(0x5008, "PrintFlagsBleedWidth"),
    TAG_INFO(0x5009, "PrintFlagsBleedWidthScale"),
    TAG_INFO(0x500A, "HalftoneLPI"),
    TAG_INFO(0x500B, "HalftoneLPIUnit"),
    TAG_INFO(0x500C, "HalftoneDegree"),
    TAG_INFO(0x500D, "HalftoneShape"),
    TAG_INFO(0x500E, "HalftoneMisc"),
    TAG_INFO(0x500F, "HalftoneScreen"),
    TAG_INFO(0x5010, "JPEGQuality"),
    TAG_INFO(0x5011, "GridSize"),
    TAG_INFO(0x5012, "ThumbnailFormat"),
    TAG_INFO(0x5013, "ThumbnailWidth"),
    TAG_INFO(0x5014, "ThumbnailHeight"),
    TAG_INFO(0x5015, "ThumbnailColorDepth"),
    TAG_INFO(0x5016, "ThumbnailPlanes"),
    TAG_INFO(0x5017, "ThumbnailRawBytes"),
    TAG_INFO(0x5018, "ThumbnailSize"),
    TAG_INFO(0x5019, "ThumbnailCompressedSize"),
    TAG_INFO(0x501A, "ColorTransferFunction"),
    TAG_INFO(0x501B, "ThumbnailData"),
    TAG_INFO(0x5020, "ThumbnailImageWidth"),
    TAG_INFO(0x5021, "ThumbnailImageHeight"),
    TAG_INFO(0x5022, "ThumbnailBitsPerSample"),
    TAG_INFO(0x5023, "ThumbnailCompression"),
    TAG_INFO(0x5024, "ThumbnailPhotometricInterp"),
    TAG_INFO(0x5025, "ThumbnailImageDescription"),
    TAG_INFO(0x5026, "ThumbnailEquipMake"),
    TAG_INFO(0x5027, "ThumbnailEquipModel"),
    TAG_INFO(0x5028, "ThumbnailStripOffsets"),
    TAG_INFO(0x5029, "ThumbnailOrientation"),
    TAG_INFO(0x502A, "ThumbnailSamplesPerPixel"),
    TAG_INFO(0x502B, "ThumbnailRowsPerStrip"),
    TAG_INFO(0x502C, "ThumbnailStripBytesCount"),
    TAG_INFO(0x502D, "ThumbnailResolutionX"),
    TAG_INFO(0x502E, "ThumbnailResolutionY"),
    TAG_INFO(0x502F, "ThumbnailPlanarConfig"),
    TAG_INFO(0x5030, "ThumbnailResolutionUnit"),
    TAG_INFO(0x5031, "ThumbnailTransferFunction"),
    TAG_INFO(0x5032, "ThumbnailSoftwareUsed"),
    TAG_INFO(0x5033, "ThumbnailDateTime"),
    TAG_INFO(0x5034, "ThumbnailArtist"),
    TAG_INFO(0x5035, "ThumbnailWhitePoint"),
    TAG_INFO(0x5036, "ThumbnailPrimaryChromaticities"),
    TAG_INFO(0x5037, "ThumbnailYCbCrCoefficients"),
    TAG_INFO(0x5038, "ThumbnailYCbCrSubsampling"),
    TAG_INFO(0x5039, "ThumbnailYCbCrPositioning"),
    TAG_INFO(0x503A, "ThumbnailRefBlackWhite"),
    TAG_INFO(0x503B, "ThumbnailCopyRight"),
    TAG_INFO(0x5090, "LuminanceTable"),
    TAG_INFO(0x5091, "ChrominanceTable"),
    TAG_INFO(0x5100, "FrameDelay"),
    TAG_INFO(0x5101, "LoopCount"),
    TAG_INFO(0x5110, "PixelUnit"),
    TAG_INFO(0x5111, "PixelPerUnitX"),
    TAG_INFO(0x5112, "PixelPerUnitY"),
    TAG_INFO(0x5113, "PaletteHistogram"),
    TAG_INFO(0x1000, "RelatedImageFileFormat"),
    TAG_INFO(0x800D, "ImageID"),
    TAG_INFO(0x80E3, "Matteing"),
    TAG_INFO(0x80E4, "DataType"),
    TAG_INFO(0x80E5, "ImageDepth"),
    TAG_INFO(0x80E6, "TileDepth"),
    TAG_INFO(0x828D, "CFARepeatPatternDim"),
    TAG_INFO(0x828E, "CFAPattern"),
    TAG_INFO(0x828F, "BatteryLevel"),
    TAG_INFO(0x8298, "Copyright"),
    TAG_INFO(0x829A, "ExposureTime"),
    TAG_INFO(0x829D, "FNumber"),
    TAG_INFO(0x83BB, "IPTC/NAA"),
    TAG_INFO(0x84E3, "IT8RasterPadding"),
    TAG_INFO(0x84E5, "IT8ColorTable"),
    TAG_INFO(0x8649, "ImageResourceInformation"),
    TAG_INFO(0x8769, "ExifOffset"),
    TAG_INFO(0x8773, "InterColorProfile"),
    TAG_INFO(0x8822, "ExposureProgram"),
    TAG_INFO(0x8824, "SpectralSensitivity"),
    TAG_INFO(0x8825, "GPSInfo"),
    TAG_INFO(0x8827, "ISOSpeedRatings"),
    TAG_INFO(0x8828, "OECF"),
    TAG_INFO(0x9000, "ExifVersion"),
    TAG_INFO(0x9003, "DateTimeOriginal"),
    TAG_INFO(0x9004, "DateTimeDigitized"),
    TAG_INFO(0x9101, "ComponentsConfiguration"),
    TAG_INFO(0x9102, "CompressedBitsPerPixel"),
    TAG_INFO(0x9201, "ShutterSpeedValue"),
    TAG_INFO(0x9202, "ApertureValue"),
    TAG_INFO(0x9203, "BrightnessValue"),
    TAG_INFO(0x9204, "ExposureBiasValue"),
    TAG_INFO(0x9205, "MaxApertureValue"),
    TAG_INFO(0x9206, "SubjectDistance"),
    TAG_INFO(0x9207, "MeteringMode"),
    TAG_INFO(0x9208, "LightSource"),
    TAG_INFO(0x9209, "Flash"),
    TAG_INFO(0x920A, "FocalLength"),
    TAG_INFO(0x9214, "SubjectArea"),
    TAG_INFO(0x927C, "MakerNote"),
    TAG_INFO(0x9286, "UserComment"),
    TAG_INFO(0x9290, "SubSecTime"),
    TAG_INFO(0x9291, "SubSecTimeOriginal"),
    TAG_INFO(0x9292, "SubSecTimeDigitized"),
    TAG_INFO(0x9C9B, "WinXP-Title"),     /* Win XP specific, UTF-16 Unicode */
    TAG_INFO(0x9C9C, "WinXP-Comments"),  /* Win XP specific, UTF-16 Unicode */
    TAG_INFO(0x9C9D, "WinXP-Author"),    /* Win XP specific, UTF-16 Unicode */
    TAG_INFO(0x9C9E, "WinXP-Keywords"),  /* Win XP specific, UTF-16 Unicode */
    TAG_INFO(0x9C9F, "WinXP-Subject"),   /* Win XP specific, UTF-16 Unicode */
    TAG_INFO(0xA000, "FlashPixVersion"),
    TAG_INFO(0xA001, "ColorSpace"),
    TAG_INFO(0xA002, "ExifImageWidth"),
    TAG_INFO(0xA003, "ExifImageLength"),
    TAG_INFO(0xA005, "InteroperabilityOffset"),
    TAG_INFO(0xA20B, "FlashEnergy"),
    TAG_INFO(0xA20C, "SpatialFrequencyResponse"),
    TAG_INFO(0xA20D, "Noise"),
    TAG_INFO(0xA20E, "FocalPlaneXResolution"),
    TAG_INFO(0xA20F, "FocalPlaneYResolution"),
    TAG_INFO(0xA210, "FocalPlaneResolutionUnit"),
    TAG_INFO(0xA211, "ImageNumber"),
    TAG_INFO(0xA212, "SecurityClassification"),
    TAG_INFO(0xA213, "ImageHistory"),
    TAG_INFO(0xA214, "SubjectLocation"),
    TAG_INFO(0xA215, "ExposureIndex"),
    TAG_INFO(0xA216, "TIFF_EPStandardID"),
    TAG_INFO(0xA217, "SensingMethod"),
    TAG_INFO(0xA300, "FileSource"),
    TAG_INFO(0xA301, "SceneType"),
    TAG_INFO(0xA302, "CFAPattern"),
    TAG_INFO(0xA401, "CustomRendered"),
    TAG_INFO(0xA402, "ExposureMode"),
    TAG_INFO(0xA403, "WhiteBalance"),
    TAG_INFO(0xA404, "DigitalZoomRatio"),
    TAG_INFO(0xA405, "FocalLengthIn35mmFilm"),
    TAG_INFO(0xA406, "SceneCaptureType"),
    TAG_INFO(0xA407, "GainControl"),
    TAG_INFO(0xA408, "Contrast"),
    TAG_INFO(0xA409, "Saturation"),
    TAG_INFO(0xA40A, "Sharpness"),
    TAG_INFO(0xA40B, "DeviceSettingDescription"),
    TAG_INFO(0xA40C, "SubjectDistanceRange"),
    TAG_INFO(0xA420, "ImageUniqueID")
  };

/*
  Convert an EXIF tag ID to a tag description

  An EXIF tag value to be translated, and a buffer of at least
  MaxTextExtent length are passed as arguments.  For convenience, the
  converted string is returned.
*/

static const char *
EXIFTagToDescription(unsigned int t, char *tag_description)
{
  unsigned int
    i;

  for (i=0; i < ArraySize(tag_table); i++)
    {
      if (tag_table[i].tag == t)
        {
          (void) strlcpy(tag_description,tag_table[i].description,
                         MaxTextExtent);
          return tag_description;
        }
    }

  FormatString(tag_description,"0x%04X",t);
  return tag_description;
}

/*
  Convert an EXIF tag description to a tag ID.
*/
static int
EXIFDescriptionToTag(const char *description)
{
  unsigned int
    i;

  for (i=0; i < sizeof(tag_table)/sizeof(tag_table[0]); i++)
    if (LocaleCompare(tag_table[i].description,description) == 0)
      return tag_table[i].tag;

  return -1;
}

static const char *
EXIFFormatToDescription(unsigned int f)
{
  const char
    *description;

  description="unknown";

  switch (f)
    {
    case EXIF_FMT_BYTE:
      description="BYTE";
      break;
    case EXIF_FMT_STRING:
      description="STRING";
      break;
    case EXIF_FMT_USHORT:
      description="USHORT";
      break;
    case EXIF_FMT_ULONG:
      description="ULONG";
      break;
    case EXIF_FMT_URATIONAL:
      description="URATIONAL";
      break;
    case EXIF_FMT_SBYTE:
      description="SBYTE";
      break;
    case EXIF_FMT_UNDEFINED:
      description="UNDEFINED";
      break;
    case EXIF_FMT_SSHORT:
      description="SSHORT";
      break;
    case EXIF_FMT_SLONG:
      description="SLONG";
      break;
    case EXIF_FMT_SRATIONAL:
      description="SRATIONAL";
      break;
    case EXIF_FMT_SINGLE:
      description="SINGLE";
      break;
    case EXIF_FMT_DOUBLE:
      description="DOUBLE";
      break;
    }

  return description;
}

static const unsigned int
  format_bytes[] =
  {
    0,
    1, /* BYTE */
    1, /* STRING / ASCII */
    2, /* USHORT */
    4, /* ULONG */
    8, /* URATIONAL */
    1, /* SBYTE */
    1, /* UNDEFINED */
    2, /* SSHORT */
    4, /* SLONG */
    8, /* SRATIONAL */
    4, /* SINGLE / FLOAT */
    8  /* DOUBLE */
  };

static magick_int16_t
Read16s(int morder,unsigned char *ishort)
{
  union
  {
    magick_uint16_t u;
    magick_int16_t s;
  } value;

  if (morder)
    value.u=((magick_uint16_t) ishort[0] << 8) | ishort[1];
  else
    value.u=((magick_uint16_t) ishort[1] << 8) | ishort[0];
  return(value.s);
}

static magick_uint16_t
Read16u(int morder,unsigned char *ishort)
{
  magick_uint16_t
    value;

  if (morder)
    value=((magick_uint16_t) ishort[0] << 8)
      | (magick_uint16_t) ishort[1];
  else
    value=((magick_uint16_t) ishort[1] << 8)
      | (magick_uint16_t) ishort[0];
  return(value);
}

static magick_int32_t
Read32s(int morder,unsigned char *ilong)
{
  union
  {
    magick_uint32_t u;
    magick_int32_t s;
  } value;

  if (morder)
    value.u=((magick_uint32_t) ilong[0] << 24)
      | ((magick_uint32_t) ilong[1] << 16)
      | ((magick_uint32_t) ilong[2] << 8)
      | ((magick_uint32_t) ilong[3]);
  else
    value.u=((magick_uint32_t) ilong[3] << 24)
      | ((magick_uint32_t) ilong[2] << 16)
      | ((magick_uint32_t) ilong[1] << 8 )
      | ((magick_uint32_t) ilong[0]);
  return(value.s);
}

static magick_uint32_t
Read32u(int morder, unsigned char *ilong)
{
  magick_uint32_t
    value;

  if (morder)
    value=((magick_uint32_t) ilong[0] << 24)
      | ((magick_uint32_t) ilong[1] << 16)
      | ((magick_uint32_t) ilong[2] << 8)
      | ((magick_uint32_t) ilong[3]);
  else
    value=((magick_uint32_t) ilong[3] << 24)
      | ((magick_uint32_t) ilong[2] << 16)
      | ((magick_uint32_t) ilong[1] << 8 )
      | ((magick_uint32_t) ilong[0]);

  return value;
}

static void
Write16u(int morder, void *location, magick_uint16_t value)
{
  char
    *pval;

  pval = (char *)location;
  if (morder)
    {
      *pval++ = (char)((value >> 8) & 0xff);
      *pval++ = (char)(value & 0xff);
    }
  else
    {
      *pval++ = (char)(value & 0xff);
      *pval++ = (char)((value >> 8) & 0xff);
    }
}

static int
GenerateEXIFAttribute(Image *image,const char *specification)
{
  char
    *final,
    *key,
    tag_description[MaxTextExtent],
    *value;

  int
    id,
    morder,
    all;

  int
    tag;

  register size_t
    i;

  size_t
    length;

  unsigned int
    level,
    offset;

  unsigned int
    gpsoffset;

  unsigned char
    *tiffp,
    *tiffp_max,
    *ifdstack[DE_STACK_SIZE],
    *ifdp,
    *info;

  unsigned int
    de,
    destack[DE_STACK_SIZE],
    nde;

  const unsigned char
    *profile_info;

  size_t
    profile_length;

  MagickBool
    logging,
    gpsfoundstack[DE_STACK_SIZE],
    gpsfound;

  MagickBool
    debug=MagickFalse;

  assert((ArraySize(format_bytes)-1) == EXIF_NUM_FORMATS);
  logging=IsEventLogged(TransformEvent);
  {
    const char *
      env_value;

    /*
      Allow enabling debug of EXIF tags
    */
    if ((env_value=getenv("MAGICK_DEBUG_EXIF")))
      {
        if (LocaleCompare(env_value,"TRUE") == 0)
          debug=MagickTrue;
      }
  }
  gpsfound=MagickFalse;
  gpsoffset=0;
  /*
    Determine if there is any EXIF data available in the image.
  */
  value=(char *) NULL;
  final=AllocateString("");
  profile_info=GetImageProfile(image,"EXIF",&profile_length);
  if (profile_info == 0)
    {
      if (logging)
        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                      "No EXIF profile present");
      goto generate_attribute_failure;
    }
  if (logging && debug)
        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                              "EXIF: profile_info=%p, profile_length=%"MAGICK_SIZE_T_F"u",
                              profile_info, (MAGICK_SIZE_T) profile_length);
  /*
    If EXIF data exists, then try to parse the request for a tag in
    the form "EXIF:key".
  */
  key=(char *) NULL;
  if (strlen(specification) > 5)
    {
      key=(char *) &specification[5]; /* "EXIF:key" */
    }
  else
    {
      if (logging)
        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                              "No EXIF:key found");
      goto generate_attribute_failure;
    }
  while (isspace((int) (*key)))
    key++;
  all=0;
  tag=(-1);
  switch(*key)
    {
      /*
        Caller has asked for all the tags in the EXIF data.
      */
    case '*':
      {
        tag=0;
        all=1; /* return the data in description=value format */
        break;
      }
    case '!':
      {
        tag=0;
        all=2; /* return the data in tageid=value format */
        break;
      }
      /*
        Check for a hex based tag specification first.
      */
    case '#':
      {
        char
          c;

        size_t
          n;

        tag=0;
        key++;
        n=strlen(key);
        if (n != 4)
          {
            if (logging)
              (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                    "EXIF: Hex tag not 4 bytes");
            goto generate_attribute_failure;
          }
        else
          {
            /*
              Parse tag specification as a hex number.
            */
            n/=4;
            do
              {
                for (i=n; i > 0; i--)
                  {
                    c=(*key++);
                    tag<<=4;
                    if ((c >= '0') && (c <= '9'))
                      tag|=c-'0';
                    else
                      if ((c >= 'A') && (c <= 'F'))
                        tag|=c-('A'-10);
                      else
                        if ((c >= 'a') && (c <= 'f'))
                          tag|=c-('a'-10);
                        else
                          {
                            if (logging)
                              (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                    "EXIF: Failed to parse hex tag");
                            goto generate_attribute_failure;
                          }
                  }
              } while (*key != '\0');
          }
        break;
      }
    default:
      {
        /*
          Try to match the text with a tag name instead.
        */
        tag=EXIFDescriptionToTag(key);
        if (logging && debug)
          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                "EXIF: Found tag %d for key \"%s\"",tag,key);
        break;
      }
    }
  if (tag < 0)
    {
      if (logging)
        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                              "EXIF: Negative tag value!");
      goto generate_attribute_failure;;
    }
  length=profile_length;
  info=(unsigned char *) profile_info;
  while (length != 0)
    {
      if (ReadByte(&info,&length) != 0x45)
        continue;
      if (ReadByte(&info,&length) != 0x78)
        continue;
      if (ReadByte(&info,&length) != 0x69)
        continue;
      if (ReadByte(&info,&length) != 0x66)
        continue;
      if (ReadByte(&info,&length) != 0x00)
        continue;
      if (ReadByte(&info,&length) != 0x00)
        continue;
      break;
    }
  if (length < 16)
    {
      if (logging)
        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                              "EXIF: Tag length length < 16 (have %"MAGICK_SIZE_T_F"u )",
                              (MAGICK_SIZE_T)length);
      goto generate_attribute_failure;
    }
  tiffp=info;
  tiffp_max=tiffp+length;
  id=Read16u(0,tiffp);
  morder=0;
  if (id == 0x4949) /* LSB */
    morder=0;
  else
    if (id == 0x4D4D) /* MSB */
      morder=1;
    else
      {
        if (logging)
          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                "EXIF: Unknown byte order (%04x)",
                                morder);
        goto generate_attribute_failure;
      }
  if (Read16u(morder,tiffp+2) != 0x002a)
    {
      if (logging)
          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                "EXIF: Expected 0x002a!");
      goto generate_attribute_failure;
    }
  /*
    This is the offset to the first IFD.
  */
  offset=Read32u(morder,tiffp+4);
  if (offset >= length)
    {
      if (logging)
        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                              "EXIF: Offset (%u) is > length (%"MAGICK_SIZE_T_F"u)!",
                              offset, (MAGICK_SIZE_T) length);
      goto generate_attribute_failure;
    }
  /*
    Set the pointer to the first IFD and follow it were it leads.
  */
  ifdp=tiffp+offset;
  level=0;
  de=0U;
  do
    {
      /*
        If there is anything on the stack then pop it off.
      */
      if (level > 0)
        {
          level--;
          ifdp=ifdstack[level];
          de=destack[level];
          gpsfound=gpsfoundstack[level];
        }
      /*
        Determine how many entries there are in the current IFD.
        Limit the number of entries parsed to MAX_TAGS_PER_IFD.
      */
      if ((ifdp < tiffp) || (ifdp+2 > tiffp_max))
        {
          if (logging)
            (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                  "EXIF: ifdp out of range!");
          goto generate_attribute_failure;
        }
      nde=Read16u(morder,ifdp);
      if (logging && debug)
            (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                  "EXIF: IFD at offset %"MAGICK_SSIZE_T_F"d has %u tags", (MAGICK_SSIZE_T) (ifdp-tiffp), nde);
      if (nde > MAX_TAGS_PER_IFD)
        {
          nde=MAX_TAGS_PER_IFD;
          if (logging && debug)
            (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                  "EXIF: Limiting IFD at offset %"MAGICK_SSIZE_T_F"d to %u tags!", (MAGICK_SSIZE_T) (ifdp-tiffp), nde);
        }
      for (; de < nde; de++)
        {
          size_t
            n;

          unsigned int
            c,
            f,
            t;

          unsigned char
            *pde,
            *pval;

          pde=(unsigned char *) (ifdp+2+(12*(size_t) de));
          if (logging && debug)
            (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                  "EXIF: PDE offset %"MAGICK_SSIZE_T_F"d", (MAGICK_SSIZE_T) (pde-ifdp));
          if ((pde < tiffp) || (pde + 12 > tiffp_max))
            {
              if (logging)
                (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                      "EXIF: Invalid Exif, entry is beyond metadata limit.");
              goto generate_attribute_failure;
            }
          t=Read16u(morder,pde); /* get tag value */
          f=Read16u(morder,pde+2); /* get the format */
          if (logging && debug)
            (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                  "EXIF: Tag %u, Format %u", t, f);
          if (((size_t) f >= ArraySize(format_bytes)) || (format_bytes[f] == 0))
            {
              if (logging)
                (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                      "EXIF: Invalid Exif, unsupported format %u.",(unsigned) f);
              break;
            }
          c=Read32u(morder,pde+4); /* get number of components */
          n=MagickArraySize(c,format_bytes[f]);
          if (logging && debug)
            {
              (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                    "EXIF: %u components, %u bytes per component", c,format_bytes[f]);
            }
          if ((c > length) || (n > length) || ((n == 0) && (c != 0) && (format_bytes[f] != 0)))
            {
              if (logging)
                (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                      "EXIF: Invalid Exif, too many components (%u components).",c);
              goto generate_attribute_failure;
            }
          if (n <= 4)
            {
              pval=(unsigned char *) pde+8;
            }
          else
            {
              size_t
                oval;

              /*
                The directory entry contains an offset.
              */
              oval=Read32u(morder,pde+8);
              if ((oval > length) || ((oval+n) > length)) /* Impossibly long! */
                {
                  if (logging && debug)
                    (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                          "EXIF: Invalid Exif directory entry!"
                                          " (offset %"MAGICK_SIZE_T_F"u, %"MAGICK_SIZE_T_F"u components)",
                                          (MAGICK_SIZE_T) oval, (MAGICK_SIZE_T) n);
                  continue;
                }
              pval=(unsigned char *)(tiffp+oval);
            }

          if (logging && debug)
            {
              (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                    "EXIF: TagVal=%d  TagDescr=\"%s\" Format=%d  "
                                    "FormatDescr=\"%s\"  Components=%u",t,
                                    EXIFTagToDescription(t,tag_description),f,
                                    EXIFFormatToDescription(f),c);
            }
          if ((pval < tiffp) || (pval > tiffp_max))
            {
              if (logging)
                (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                      "EXIF: Offset %"MAGICK_SSIZE_T_F"d out of valid range!",
                                      (MAGICK_SSIZE_T) (pval-tiffp));
              goto generate_attribute_failure;
            }

          if (gpsfound)
            {
              if ((t < GPS_TAG_START) || (t > GPS_TAG_STOP))
                {
                  if (logging & debug)
                    (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                          "EXIF: Skipping bogus GPS IFD tag %d ...",t);
                  continue;
                }
            }
          else
            {
              if ((t < EXIF_TAG_START) || ( t > EXIF_TAG_STOP))
                {
                  if (logging & debug)
                    (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                          "EXIF: Skipping bogus EXIF IFD tag %d ...",t);
                  continue;
                }
            }

          /*
            Return values for all the tags, or for a specific requested tag.

            Tags from the GPS sub-IFD are in a bit of a chicken and
            egg situation in that the tag for the GPS sub-IFD will not
            be seen unless we pass that tag through so it can be
            processed.  So we pass the GPS_OFFSET tag through, but if
            it was not requested, then we don't return a string value
            for it.
          */
          if (all || (tag == (int) t) || (GPS_OFFSET == t))
            {
              char
                s[MaxTextExtent];

              switch (f)
                {
                case EXIF_FMT_SBYTE:
                  {
                    /* 8-bit signed integer */
                    FormatString(s,"%d",(int) (*(char *) pval));
                    value=AllocateString(s);
                    break;
                  }
                case EXIF_FMT_BYTE:
                  {
                    /* 8-bit unsigned integer */
                    value=MagickAllocateMemory(char *,n+1);
                    if (value != (char *) NULL)
                      {
                        unsigned int
                          a;

                        for (a=0; a < n; a++)
                          {
                            value[a]='.';
                            if (isprint((int) pval[a]))
                              value[a]=pval[a];
                          }
                        value[a]='\0';
                        break;
                      }
#if 0
                    printf("format %u, length %u\n",f,n);
                    FormatString(s,"%ld",(long) (*(unsigned char *) pval));
                    value=AllocateString(s);
#endif
                    break;
                  }
                case EXIF_FMT_SSHORT:
                  {
                    /* 16-bit signed integer */
                    if (((pval < tiffp) || (pval+sizeof(magick_uint16_t)) > tiffp_max))
                      {
                        if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: Offset %"MAGICK_SSIZE_T_F"d out of valid range!",
                                                (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    FormatString(s,"%hd",Read16u(morder,pval));
                    value=AllocateString(s);
                    break;
                  }
                case EXIF_FMT_USHORT:
                  {
                    /* 16-bit unsigned integer */
                    if ((pval < tiffp) || ((pval+sizeof(magick_uint16_t)) > tiffp_max))
                      {
                        if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: Offset %"MAGICK_SSIZE_T_F"d out of valid range!",
                                                (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    FormatString(s,"%hu",Read16s(morder,pval));
                    value=AllocateString(s);
                    break;
                  }
                case EXIF_FMT_ULONG:
                  {
                    if ((pval < tiffp) || ((pval+sizeof(magick_uint32_t)) > tiffp_max))
                      {
                        if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: Offset %"MAGICK_SSIZE_T_F"d out of valid range!",
                                                (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    offset=Read32u(morder,pval);
                    /*
                      Only report value if this tag was requested.
                    */
                    if (all || (tag == (int) t))
                      {
                        FormatString(s,"%u",offset);
                        value=AllocateString(s);
                      }
                    if (GPS_OFFSET == t)
                      {
                        gpsoffset=offset;
                     }
                    break;
                  }
                case EXIF_FMT_SLONG:
                  {
                    if ((pval < tiffp) || ((pval+sizeof(magick_uint32_t)) > tiffp_max))
                      {
                        if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: Offset %"MAGICK_SSIZE_T_F"d out of valid range!",
                                                (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    FormatString(s,"%d",(int) Read32s(morder,pval));
                    value=AllocateString(s);
                    break;
                  }
                case EXIF_FMT_URATIONAL:
                  {
                    if (gpsfound &&
                        (t == GPS_LATITUDE ||
                         t == GPS_LONGITUDE ||
                         t == GPS_TIMESTAMP))
                      {
                        if ((pval < tiffp) || ((pval+6*sizeof(magick_uint32_t)) > tiffp_max))
                          {
                            if (logging)
                              (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                    "EXIF: Offset %"MAGICK_SSIZE_T_F"d out of valid range!",
                                                    (MAGICK_SSIZE_T) (pval-tiffp));
                            goto generate_attribute_failure;
                          }
                        FormatString(s,"%u/%u,%u/%u,%u/%u"
                                     ,(unsigned) Read32u(morder,pval),
                                     (unsigned) Read32u(morder,4+pval)
                                     ,(unsigned) Read32u(morder,8+pval),
                                     (unsigned) Read32u(morder,12+pval)
                                     ,(unsigned) Read32u(morder,16+pval),
                                     (unsigned) Read32u(morder,20+pval)
                                     );
                      }
                    else
                      {
                        if ((pval < tiffp) || ((pval+2*sizeof(magick_uint32_t)) > tiffp_max))
                          {
                            if (logging)
                              (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                    "EXIF: Offset %"MAGICK_SSIZE_T_F"d out of valid range!",
                                                    (MAGICK_SSIZE_T) (pval-tiffp));
                            goto generate_attribute_failure;
                          }
                        FormatString(s,"%u/%u"
                                     ,(unsigned) Read32u(morder,pval),
                                     (unsigned) Read32u(morder,4+pval)
                                     );
                      }
                    value=AllocateString(s);
                    break;
                  }
                case EXIF_FMT_SRATIONAL:
                  {
                    if ((pval < tiffp) || ((pval+2*sizeof(magick_uint32_t)) > tiffp_max))
                      {
                        if (logging)
                              (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                    "EXIF: Offset %"MAGICK_SSIZE_T_F"d out of valid range!",
                                                    (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    FormatString(s,"%d/%d",(int) Read32s(morder,pval),
                                 (int) Read32s(morder,4+pval));
                    value=AllocateString(s);
                    break;
                  }
                case EXIF_FMT_SINGLE:
                  {
                    float fval;
                    if ((pval < tiffp) || ((pval+sizeof(float)) > tiffp_max))
                      {
                        if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: Offset %"MAGICK_SSIZE_T_F"d out of valid range!",
                                                (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    (void) memcpy(&fval,pval,sizeof(fval));
                    FormatString(s,"%f",(double) fval);
                    value=AllocateString(s);
                    break;
                  }
                case EXIF_FMT_DOUBLE:
                  {
                    double dval;
                    if ((pval < tiffp) || ((pval+sizeof(double)) > tiffp_max))
                      {
                        if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: Offset %"MAGICK_SSIZE_T_F"d out of valid range!",
                                                (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    (void) memcpy(&dval,pval,sizeof(dval));
                    FormatString(s,"%f",dval);
                    value=AllocateString(s);
                    break;
                  }
                default:
                case EXIF_FMT_UNDEFINED:
                case EXIF_FMT_STRING:
                  {
                    unsigned int
                      a;

                    size_t
                      allocation_size;

                    MagickBool
                      binary=MagickFalse;

                    if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: pval=%p (offset=%"MAGICK_SSIZE_T_F"d), n=%"MAGICK_SIZE_T_F"u",
                                                pval, (MAGICK_SSIZE_T) (pval-tiffp), (MAGICK_SIZE_T) n);

                    if ((pval < tiffp) || (pval+n) > tiffp_max)
                      {
                        if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: Offset %"MAGICK_SSIZE_T_F"d out of valid range!",
                                                (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    allocation_size=n+1;
                    for (a=0; a < n; a++)
                      {
                        if (!(isprint((int) pval[a])))
                          allocation_size += 3;
                      }

                    value=MagickAllocateMemory(char *,allocation_size);
                    if (value != (char *) NULL)
                      {
                        i=0;
                        for (a=0; a < n; a++)
                          {
                            if ((f == EXIF_FMT_STRING) && (pval[a] == '\0'))
                              break;
                            if ((isprint((int) pval[a])) ||
                                ((pval[a] == '\0') &&
                                 (a == (n-1) && (!binary))))
                              {
                                value[i++]=pval[a];
                              }
                            else
                              {
                                i += snprintf(&value[i],(allocation_size-i),"\\%03o",
                                             (unsigned int) pval[a]);
                                binary |= MagickTrue;
                              }
                          }
                        value[i]='\0';
                      }
                    break;
                  }
                }
              if (value != (char *) NULL)
                {
                  const char
                    *description;

                  if (strlen(final) != 0)
                    (void) ConcatenateString(&final,EXIF_DELIMITER);
                  description=(const char *) NULL;
                  switch (all)
                    {
                    case 1:
                      {
                        description=EXIFTagToDescription(t,tag_description);
                        FormatString(s,"%.1024s=",description);
                        (void) ConcatenateString(&final,s);
                        break;
                      }
                    case 2:
                      {
                        FormatString(s,"#%04x=",t);
                        (void) ConcatenateString(&final,s);
                        break;
                      }
                    }
                  (void) ConcatenateString(&final,value);
                  MagickFreeMemory(value);
                }
            }
          if (t == GPS_OFFSET && (gpsoffset != 0))
            {
              if ((gpsoffset < length) && (level < (DE_STACK_SIZE-2)))
                {
                  /*
                    Push our current directory state onto the stack.
                  */
                  ifdstack[level]=ifdp;
                  de++; /* bump to the next entry */
                  destack[level]=de;
                  gpsfoundstack[level]=gpsfound;
                  level++;
                  /*
                    Push new state onto of stack to cause a jump.
                  */
                  ifdstack[level]=tiffp+gpsoffset;
                  destack[level]=0;
                  gpsfoundstack[level]=MagickTrue;
                  level++;
                }
              gpsoffset=0;
              break; /* break out of the for loop */
            }

          if ((t == TAG_EXIF_OFFSET) || (t == TAG_INTEROP_OFFSET))
            {
              offset=Read32u(morder,pval);
              if (logging & debug)
                (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                      "EXIF: %s at offset %u",
                                      t == TAG_EXIF_OFFSET ? "TAG_EXIF_OFFSET" :
                                      "TAG_INTEROP_OFFSET", offset);
              if ((offset < length) && (level < (DE_STACK_SIZE-2)))
                {
                  /*
                    Check that we are not being directed to read an
                    IFD that we are already parsing and quit in order
                    to avoid a loop.
                  */
                  unsigned char *new_ifdp = tiffp+offset;
                  MagickBool dup_ifd = MagickFalse;

                  if (new_ifdp == ifdp)
                    {
                      dup_ifd = MagickTrue;
                    }
                  else
                    {
                      for (i=0; i < level; i++)
                        {
                          if (ifdstack[i] == new_ifdp)
                            {
                              dup_ifd = MagickTrue;
                              break;
                            }
                        }
                    }
                  if (dup_ifd)
                    {
                       if (logging)
                         (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                               "EXIF: Duplicate IFD detected, quitting to avoid loop!");
                                               goto generate_attribute_failure;
                    }

                  /*
                    Push our current directory state onto the stack.
                  */
                  if (logging & debug)
                    (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                          "ifdstack[%u]=%p", level, ifdp);
                  ifdstack[level]=ifdp;
                  de++; /* bump to the next entry */
                  destack[level]=de;
                  gpsfoundstack[level]=gpsfound;
                  level++;
                  /*
                    Push new state onto of stack to cause a jump.
                  */
                  ifdstack[level]=tiffp+offset;
                  if (logging & debug)
                    (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                          "ifdstack[%u]=%p", level, ifdp);
                  destack[level]=0;
                  gpsfoundstack[level]=MagickFalse;
                  level++;
                }
              break; /* break out of the for loop */
            }
        }
    } while (level > 0);
  if (strlen(final) == 0)
    (void) ConcatenateString(&final,"unknown");

  (void) SetImageAttribute(image,specification,(const char *) NULL);
  (void) SetImageAttribute(image,specification,(const char *) final);
  MagickFreeMemory(final);
  return(True);
 generate_attribute_failure:
  MagickFreeMemory(final);
  return False;
}

/*
  Generate an aggregate attribute result based on a wildcard
  specification like "foo:*".
*/
static int
GenerateWildcardAttribute(Image *image,const char *key)
{
  char
    *result=NULL;

  size_t
    key_length=0;

  register ImageAttribute
    *p = (ImageAttribute *) NULL;

  MagickPassFail
    status=MagickFail;

  /*
    Support a full "*" wildcard.
  */
  if (strcmp("*",key) == 0)
    {
      (void) GenerateIPTCAttribute((Image *) image,"IPTC:*");
      (void) Generate8BIMAttribute((Image *) image,"8BIM:*");
      (void) GenerateEXIFAttribute((Image *) image,"EXIF:*");
    }

  key_length=strlen(key)-1;
  for (p=image->attributes; p != (ImageAttribute *) NULL; p=p->next)
    if (LocaleNCompare(key,p->key,key_length) == 0)
      {
        char
          s[MaxTextExtent];

        if (result != NULL)
          (void) ConcatenateString(&result,"\n");
        FormatString(s,"%.512s=%.1024s",p->key,p->value);
        (void) ConcatenateString(&result,s);
      }

  if (result != NULL)
    {
      status=SetImageAttribute(image,key,result);
      MagickFreeMemory(result);
    }
  return status;
}

MagickExport const ImageAttribute *
GetImageAttribute(const Image *image,const char *key)
{
  register ImageAttribute
    *p = (ImageAttribute *) NULL;

  size_t
    key_length=0;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);

  /*
    If key is null, then return a pointer to the attribute list.
  */
  if (key == (char *) NULL)
    return(image->attributes);

  key_length=strlen(key);

  for (p=image->attributes; p != (ImageAttribute *) NULL; p=p->next)
    if (LocaleCompare(key,p->key) == 0)
      return(p);

  if (LocaleNCompare("IPTC:",key,5) == 0)
    {
      /*
        Create an attribute named "IPTC:*" with all matching
        key=values and return it.
      */
      if (GenerateIPTCAttribute((Image *) image,key) == True)
        return(GetImageAttribute(image,key));
    }
  else if (LocaleNCompare("8BIM:",key,5) == 0)
    {
      /*
        Create an attribute named "8BIM:*" with all matching
        key=values and return it.
      */
      if (Generate8BIMAttribute((Image *) image,key) == True)
        return(GetImageAttribute(image,key));
    }
  else if (LocaleNCompare("EXIF:",key,5) == 0)
    {
      /*
        Create an attribute named "EXIF:*" with all matching
        key=values and return it.
      */
      if (GenerateEXIFAttribute((Image *) image,key) == True)
        return(GetImageAttribute(image,key));
    }
  else if ((key_length >=2) && (key[key_length-1] == '*'))
    {
      /*
        Create an attribute named "foo:*" with all matching
        key=values and return it.
      */
      if (GenerateWildcardAttribute((Image *) image,key) == True)
        return(GetImageAttribute(image,key));
    }
  else if ((key_length ==1) && (key[0] == '*'))
    {
      /*
        Create an attribute named "*" with all key=values and return
        it.
      */
      if (GenerateWildcardAttribute((Image *) image,key) == True)
        return(GetImageAttribute(image,key));
    }
  return(p);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t I m a g e C l i p p i n g P a t h A t t r i b u t e                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method GetImageClippingPathAttribute searches the list of image attributes
%  and returns a pointer to a clipping path if it exists otherwise NULL.
%
%  The format of the GetImageClippingPathAttribute method is:
%
%      const ImageAttribute *GetImageClippingPathAttribute(const Image *image)
%
%  A description of each parameter follows:
%
%    o attribute:  Method GetImageClippingPathAttribute returns the clipping
%      path if it exists otherwise NULL.
%
%    o image: The image.
%
%
*/
MagickExport const ImageAttribute *
GetImageClippingPathAttribute(const Image *image)
{
  /* Get the name of the clipping path, if any.  The clipping path
     length is indicated by the first character of the Pascal
     string. */
  const ImageAttribute *path_name = GetImageAttribute(image, "8BIM:2999,2999");
  if ((path_name != (const ImageAttribute *) NULL) &&
      (path_name->length > 2) &&
      ((size_t) path_name->value[0] < path_name->length))
    {
      static const char clip_prefix[] = "8BIM:1999,2998";
      char attr_name[271];
      /*sprintf(attr_name, "%s:%.255s", clip_prefix, path_name->value+1);*/
      sprintf(attr_name, "%s:%.*s", clip_prefix, Min(255,(int) path_name->length-1),
              path_name->value+1);
      return GetImageAttribute(image, attr_name);
    }
  return NULL;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   G e t I m a g e I n f o A t t r i b u t e                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetImageInfoAttribute() returns a "fake" attribute based on data in the
%  image info or image structures.
%
%  The format of the GetImageInfoAttribute method is:
%
%      const ImageAttribute *GetImageAttribute(const ImageInfo *image_info,
%        const Image *image,const char *key)
%
%  A description of each parameter follows:
%
%    o attribute:  Method GetImageInfoAttribute returns the attribute if it
%      exists otherwise NULL.
%
%    o image_info: The imageInfo.
%
%    o image: The image.
%
%    o key:  These character strings are the name of an image attribute to
%      return.
%
*/
MagickExport const ImageAttribute *
GetImageInfoAttribute(const ImageInfo *image_info,const Image *image,
                      const char *key)
{
  char
    attribute[MaxTextExtent],
    filename[MaxTextExtent];

  attribute[0]='\0';
  switch(*(key))
    {
    case 'b':
      {
        if (LocaleNCompare("base",key,2) == 0)
          {
            GetPathComponent(image->magick_filename,BasePath,filename);
            (void) strlcpy(attribute,filename,MaxTextExtent);
            break;
          }
        break;
      }
    case 'd':
      {
        if (LocaleNCompare("depth",key,2) == 0)
          {
            FormatString(attribute,"%u",image->depth);
            break;
          }
        if (LocaleNCompare("directory",key,2) == 0)
          {
            GetPathComponent(image->magick_filename,HeadPath,filename);
            (void) strlcpy(attribute,filename,MaxTextExtent);
            break;
          }
        break;
      }
    case 'e':
      {
        if (LocaleNCompare("extension",key,2) == 0)
          {
            GetPathComponent(image->magick_filename,ExtensionPath,filename);
            (void) strlcpy(attribute,filename,MaxTextExtent);
            break;
          }
        break;
      }
    case 'g':
      {
        if (LocaleNCompare("group",key,2) == 0)
          {
            FormatString(attribute,"0x%lx",image_info->group);
            break;
          }
        break;
      }
    case 'h':
      {
        if (LocaleNCompare("height",key,2) == 0)
          {
            FormatString(attribute,"%lu",
                         image->magick_rows ? image->magick_rows : 256L);
            break;
          }
        break;
      }
    case 'i':
      {
        if (LocaleNCompare("input",key,2) == 0)
          {
            (void) strlcpy(attribute,image->filename,MaxTextExtent);
            break;
          }
        break;
      }
    case 'm':
      {
        if (LocaleNCompare("magick",key,2) == 0)
          {
            (void) strlcpy(attribute,image->magick,MaxTextExtent);
            break;
          }
        break;
      }
    case 'n':
      {
        if (LocaleNCompare("name",key,2) == 0)
          {
            /* What should this really be? */
            GetPathComponent(image->magick_filename,BasePath,filename);
            (void) strlcpy(attribute,filename,MaxTextExtent);
            break;
          }
        break;
      }
    case 's':
      {
        if (LocaleNCompare("size",key,2) == 0)
          {
            char
              format[MaxTextExtent];

            FormatSize(GetBlobSize(image),format);
            FormatString(attribute,"%.1024s",format);
            break;
          }
        if (LocaleNCompare("scene",key,2) == 0)
          {
            FormatString(attribute,"%lu",image->scene);
            if (image_info->subrange != 0)
              FormatString(attribute,"%lu",image_info->subimage);
            break;
          }
        if (LocaleNCompare("scenes",key,6) == 0)
          {
            FormatString(attribute,"%lu",
                         (unsigned long) GetImageListLength(image));
            break;
          }
        break;
      }
    case 'o':
      {
        if (LocaleNCompare("output",key,2) == 0)
          {
            (void) strlcpy(attribute,image_info->filename,MaxTextExtent);
            break;
          }
        break;
      }
    case 'p':
      {
        if (LocaleNCompare("page",key,2) == 0)
          {
            register const Image
              *p;

            unsigned int
              page;

            p=image;
            for (page=1; p->previous != (Image *) NULL; page++)
              p=p->previous;
            FormatString(attribute,"%u",page);
            break;
          }
        break;
      }
    case 'u':
      {
        if (LocaleNCompare("unique",key,2) == 0)
          {
            (void) strlcpy(filename,image_info->unique,MaxTextExtent);
            if (*filename == '\0')
              if(!AcquireTemporaryFileName(filename))
                return((ImageAttribute *) NULL);
            (void) strlcpy(attribute,filename,MaxTextExtent);
            break;
          }
        break;
      }
    case 'w':
      {
        if (LocaleNCompare("width",key,2) == 0)
          {
            FormatString(attribute,"%lu",
                         image->magick_columns ? image->magick_columns : 256L);
            break;
          }
        break;
      }
    case 'x':
      {
        if (LocaleNCompare("xresolution",key,2) == 0)
          {
            FormatString(attribute,"%g",image->x_resolution);
            break;
          }
        break;
      }
    case 'y':
      {
        if (LocaleNCompare("yresolution",key,2) == 0)
          {
            FormatString(attribute,"%g",image->y_resolution);
            break;
          }
        break;
      }
    case 'z':
      {
        if (LocaleNCompare("zero",key,2) == 0)
          {
            (void) strlcpy(filename,image_info->zero,MaxTextExtent);
            if (*filename == '\0')
              if(!AcquireTemporaryFileName(filename))
                return((ImageAttribute *) NULL);
            (void) strlcpy(attribute,filename,MaxTextExtent);
            break;
          }
        break;
      }
    }
  if (strlen(image->magick_filename) != 0)
    return(GetImageAttribute(image,key));
  return((ImageAttribute *) NULL);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S e t I m a g e A t t r i b u t e                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SetImageAttribute() searches the list of image attributes and replaces the
%  attribute value.  If it is not found in the list, the attribute name
%  and value is added to the list.   If the attribute exists in the list,
%  the value is concatenated to the attribute.  SetImageAttribute returns
%  True if the attribute is successfully concatenated or added to the list,
%  otherwise False.  If the value is NULL, the matching key is deleted
%  from the list.
%
%  There is special handling for the EXIF:Orientation attribute. Setting this
%  attribute will also update the EXIF tag in the image's EXIF profile to the
%  given value provided an EXIF profile exists and has an existing EXIF
%  orientation tag and the attribute value is a valid orientation
%  (see orientationType). The attribute value will be set regardless of
%  whether the EXIF profile was successfully updated. The new
%  EXIF:Orientation attribute replaces the existing value rather than
%  being concatenated to it as when setting other attributes.
%
%  The 'comment' and 'label' attributes are treated specially in that
%  embedded format specifications are translated according to the formatting
%  rules of TranslateText().
%
%  The format of the SetImageAttribute method is:
%
%      unsigned int SetImageAttribute(Image *image,const char *key,
%        const char *value)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%    o key,value:  These character strings are the name and value of an image
%      attribute to replace or add to the list.
%
%
*/

/*
  Find the location of an EXIF attribute in an EXIF profile. The EXIF attribute
  to be found is specified as its numeric tag value (see tag_table). Returns
  a pointer to the attribute in the EXIF profile or NULL if missing or there
  is an error parsing the profile. Returns the EXIF profile byte order if the
  morderp parameter is not NULL.
*/

static unsigned char *
FindEXIFAttribute(const unsigned char *profile_info,
                  const size_t profile_length,
                  const unsigned short tag, int *morderp)
{
  char
    tag_description[MaxTextExtent];

  int
    id,
    level,
    morder;

  size_t
    length;

  unsigned long
    offset;

  unsigned char
    *tiffp,
    *tiffp_max,
    *ifdstack[DE_STACK_SIZE],
    *ifdp,
    *info,
    *attribp;

  unsigned int
    de,
    destack[DE_STACK_SIZE],
    nde;

  MagickBool
    gpsfoundstack[DE_STACK_SIZE],
    gpsfound;

  MagickBool
    debug=MagickFalse;

  attribp = (unsigned char *)NULL;

  assert((ArraySize(format_bytes)-1) == EXIF_NUM_FORMATS);

  {
    const char *
      env_value;

    /*
      Allow enabling debug of EXIF tags
    */
    if ((env_value=getenv("MAGICK_DEBUG_EXIF")))
      {
        if (LocaleCompare(env_value,"TRUE") == 0)
          debug=MagickTrue;
      }
  }
  gpsfound=MagickFalse;
  length=profile_length;
  info=(unsigned char *) profile_info;
  while (length != 0)
    {
      if (ReadByte(&info,&length) != 0x45)
    continue;
      if (ReadByte(&info,&length) != 0x78)
    continue;
      if (ReadByte(&info,&length) != 0x69)
    continue;
      if (ReadByte(&info,&length) != 0x66)
    continue;
      if (ReadByte(&info,&length) != 0x00)
    continue;
      if (ReadByte(&info,&length) != 0x00)
    continue;
      break;
    }
  if (length < 16)
    goto find_attribute_failure;
  tiffp=info;
  tiffp_max=tiffp+length;
  id=Read16u(0,tiffp);
  morder=0;
  if (id == 0x4949) /* LSB */
    morder=0;
  else
    if (id == 0x4D4D) /* MSB */
      morder=1;
    else
      goto find_attribute_failure;
  if (morderp)
    *morderp = morder;
  if (Read16u(morder,tiffp+2) != 0x002a)
    goto find_attribute_failure;
  /*
    This is the offset to the first IFD.
  */
  offset=Read32u(morder,tiffp+4);
  if (offset >= length)
    goto find_attribute_failure;
  /*
    Set the pointer to the first IFD and follow it were it leads.
  */
  ifdp=tiffp+offset;
  level=0;
  de=0U;
  do
    {
      /*
        If there is anything on the stack then pop it off.
      */
      if (level > 0)
        {
          level--;
          ifdp=ifdstack[level];
          de=destack[level];
          gpsfound=gpsfoundstack[level];
        }
      /*
        Determine how many entries there are in the current IFD.
        Limit the number of entries parsed to MAX_TAGS_PER_IFD.
      */
      if ((ifdp < tiffp) || (ifdp+2 > tiffp_max))
        goto find_attribute_failure;
      nde=Read16u(morder,ifdp);
      if (nde > MAX_TAGS_PER_IFD)
        nde=MAX_TAGS_PER_IFD;
      for (; de < nde; de++)
        {
          size_t
            n;

          unsigned int
            c,
            f,
            t;

          unsigned char
            *pde,
            *pval;


          pde=(unsigned char *) (ifdp+2+(12*(size_t) de));
          if (pde + 12 > tiffp + length)
            {
              if (debug)
                fprintf(stderr, "EXIF: Invalid Exif, entry is beyond metadata limit.\n");
              goto find_attribute_failure;
            }
          t=Read16u(morder,pde); /* get tag value */
          f=Read16u(morder,pde+2); /* get the format */
          if ((size_t) f >= ArraySize(format_bytes))
            break;
          c=Read32u(morder,pde+4); /* get number of components */
          n=MagickArraySize(c,format_bytes[f]);
          if ((n == 0) && (c != 0) && (format_bytes[f] != 0))
            {
              if (debug)
                fprintf(stderr, "EXIF: Invalid Exif, too many components (%u).\n",c);
              goto find_attribute_failure;
            }
          if (n <= 4)
            pval=(unsigned char *) pde+8;
          else
            {
              unsigned long
              oval;

              /*
                The directory entry contains an offset.
              */
              oval=Read32u(morder,pde+8);
              if ((oval+n) > length)
                continue;
              pval=(unsigned char *)(tiffp+oval);
            }

          if (debug)
            {
              fprintf(stderr,
                  "EXIF: TagVal=%d  TagDescr=\"%s\" Format=%d  "
                  "FormatDescr=\"%s\"  Components=%u\n",t,
                  EXIFTagToDescription(t,tag_description),f,
                  EXIFFormatToDescription(f),c);
            }

          if (gpsfound)
            {
              if ((t < GPS_TAG_START) || (t > GPS_TAG_STOP))
                {
                  if (debug)
                    fprintf(stderr,
                        "EXIF: Skipping bogus GPS IFD tag %d ...\n",t);
                  continue;
                }
            }
          else
            {
              if ((t < EXIF_TAG_START) || ( t > EXIF_TAG_STOP))
                {
                  if (debug)
                    fprintf(stderr,
                        "EXIF: Skipping bogus EXIF IFD tag %d ...\n",t);
                  continue;
                }
            }

          /*
            Return values for all the tags, or for a specific requested tag.

            Tags from the GPS sub-IFD are in a bit of a chicken and
            egg situation in that the tag for the GPS sub-IFD will not
            be seen unless we pass that tag through so it can be
            processed.  So we pass the GPS_OFFSET tag through, but if
            it was not requested, then we don't return a string value
            for it.
          */
          if (tag == t)
            {
              attribp = pde;
              break;
            }

          if (t == GPS_OFFSET)
            {
              offset=Read32u(morder,pval);
              if ((offset < length) && (level < (DE_STACK_SIZE-2)))
                {
                  /*
                    Push our current directory state onto the stack.
                  */
                  ifdstack[level]=ifdp;
                  de++; /* bump to the next entry */
                  destack[level]=de;
                  gpsfoundstack[level]=gpsfound;
                  level++;
                  /*
                    Push new state onto of stack to cause a jump.
                  */
                  ifdstack[level]=tiffp+offset;
                  destack[level]=0;
                  gpsfoundstack[level]=MagickTrue;
                  level++;
                }
              break; /* break out of the for loop */
            }

          if ((t == TAG_EXIF_OFFSET) || (t == TAG_INTEROP_OFFSET))
            {
              offset=Read32u(morder,pval);
              if ((offset < length) && (level < (DE_STACK_SIZE-2)))
                {
                  /*
                    Push our current directory state onto the stack.
                  */
                  ifdstack[level]=ifdp;
                  de++; /* bump to the next entry */
                  destack[level]=de;
                  gpsfoundstack[level]=gpsfound;
                  level++;
                  /*
                    Push new state onto of stack to cause a jump.
                  */
                  ifdstack[level]=tiffp+offset;
                  destack[level]=0;
                  gpsfoundstack[level]=MagickFalse;
                  level++;
                }
              break; /* break out of the for loop */
            }
        }
    } while (!attribp && (level > 0));
  return attribp;
 find_attribute_failure:
  return (unsigned char *)NULL;
}

/*
  SetEXIFOrientation() updates the EXIF orientation tag in the image's EXIF
  profile to the value provided. Returns MagickPass on success or MagickFail
  if either there is no EXIF profile in the image, there was an error parsing
  the EXIF profile, there was no existing EXIF orientation attribute in
  the EXIF profile or there was a memory allocation error.
*/

static MagickPassFail
SetEXIFOrientation(Image *image, const int orientation)
{
  MagickPassFail
    result;

  const unsigned char
    *current_profile;

  size_t
    profile_length;

  unsigned char
    *orientp,
    *pval,
    *new_profile;

  int
    morder,
    current_orientation;

  unsigned short
    f;

  unsigned long
    c;

  if (orientation < TopLeftOrientation || orientation > LeftBottomOrientation)
    return(MagickFail);

  current_profile=GetImageProfile(image,"EXIF",&profile_length);
  if (current_profile == 0)
    return(MagickFail);

  /* Clone profile so orientation can be set */
  new_profile = MagickAllocateMemory(unsigned char *,profile_length);
  if (new_profile == 0)
    return(MagickFail);

  result = MagickFail;
  memcpy(new_profile, current_profile, profile_length);
  orientp = FindEXIFAttribute(new_profile, profile_length,
                              (unsigned short)EXIF_ORIENTATION, &morder);
  if (orientp)
    {
      /* Make sure EXIF orientation attribute is valid */
      f=Read16u(morder,orientp+2); /* get the format */
      c=Read32u(morder,orientp+4); /* get number of components */
      if ((f == EXIF_FMT_USHORT) && (c == 1))
        {
          pval=(unsigned char *) orientp+8;
          current_orientation=(int)Read16u(morder, pval);
          if (current_orientation != (unsigned short)orientation)
            {
              Write16u(morder, pval, orientation);
              Write16u(morder, pval+2, 0);
              result=SetImageProfile(image,"EXIF",new_profile,profile_length);
            }
          else
            result = MagickPass;
        }
    }
  MagickFreeMemory(new_profile);

  return result;
}

MagickExport MagickPassFail
SetImageAttribute(Image *image,const char *key,const char *value)
{
  ImageAttribute
    *attribute;

  register ImageAttribute
    *p;

  /*
    Initialize new attribute.
  */
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  if ((key == (const char *) NULL) || (*key == '\0'))
    return(MagickFail);

  if (value == (const char *) NULL)
    {
      /*
        Delete attribute from the image attributes list.
      */
      for (p=image->attributes; p != (ImageAttribute *) NULL; p=p->next)
        if (LocaleCompare(key,p->key) == 0)
          break;
      if (p == (ImageAttribute *) NULL)
        return(False);
      if (p->previous != (ImageAttribute *) NULL)
        p->previous->next=p->next;
      else
        {
          image->attributes=p->next;
          if (p->next != (ImageAttribute *) NULL)
            p->next->previous=(ImageAttribute *) NULL;
        }
      if (p->next != (ImageAttribute *) NULL)
        p->next->previous=p->previous;
      attribute=p;
      DestroyImageAttribute(attribute);
      return(MagickPass);
    }
  attribute=MagickAllocateMemory(ImageAttribute *,sizeof(ImageAttribute));
  if (attribute == (ImageAttribute *) NULL)
    return(MagickFail);
  attribute->key=AllocateString(key);
  attribute->length=0;
  if (!GetBlobIsOpen(image) &&
      ((LocaleNCompare(key,"comment",7) == 0) ||
       (LocaleNCompare(key,"label",5) == 0)))
    {
      /*
        Translate format requests in attribute text when the blob is
        not open.

        This is really gross since it is assumed that the attribute is
        supplied by the user and the user intends for translation to
        occur.  However, 'comment' and 'label' attributes may also
        come from an image file and may contain arbitrary text.  As a
        crude-workaround, translations are only performed when the
        blob is not open.
      */
      attribute->value=TranslateText((ImageInfo *) NULL,image,value);
      if (attribute->value != (char *) NULL)
        attribute->length=strlen(attribute->value);
    }
  else
    {
      /*
        Use attribute text as is.
      */
      attribute->length=strlen(value);
      attribute->value=MagickAllocateMemory(char *,attribute->length+1);
      if (attribute->value != (char *) NULL)
        (void) strlcpy(attribute->value,value,attribute->length+1);
    }
  if ((attribute->value == (char *) NULL) ||
      (attribute->key == (char *) NULL))
    {
      DestroyImageAttribute(attribute);
      return(MagickFail);
    }

  attribute->previous=(ImageAttribute *) NULL;
  attribute->next=(ImageAttribute *) NULL;
  if (image->attributes == (ImageAttribute *) NULL)
    {
      image->attributes=attribute;
      return(MagickPass);
    }
  for (p=image->attributes; p != (ImageAttribute *) NULL; p=p->next)
    {
      if (LocaleCompare(attribute->key,p->key) == 0)
        {
          size_t
            min_l,
            realloc_l;

          if (LocaleCompare(attribute->key,"EXIF:Orientation") == 0)
            {
              int
                orientation = 0;

              /*
                Special handling for EXIF orientation tag.
                If new value differs from existing value,
                EXIF profile is updated as well if it exists and
                is valid. Don't append new value to existing value,
                replace it instead.
              */
              if ((MagickAtoIChk(value, &orientation) == MagickPass) &&
                  (orientation > 0 || orientation <= (int)LeftBottomOrientation))
                {
                  SetEXIFOrientation(image, orientation);
                }
              /* Assign changed value to attribute in list */
              if (LocaleCompare(p->value, attribute->value) != 0)
                {
                  MagickFreeMemory(p->value);
                  p->value=attribute->value;
                  attribute->value = (char *) NULL;
                }
              DestroyImageAttribute(attribute);
              return(MagickPass);
            }
          else
            {
              /*
                Extend existing text string.
              */
              min_l=p->length+attribute->length+1;
              for (realloc_l=2; realloc_l <= min_l; realloc_l *= 2)
                    { /* nada */};
              MagickReallocMemory(char *,p->value,realloc_l);
              if (p->value != (char *) NULL)
                {
                  (void) memcpy(p->value+p->length,attribute->value,min_l-p->length-1);
                  p->length += attribute->length;
                  p->value[p->length] = '\0';
                }
              DestroyImageAttribute(attribute);
            }
          if (p->value != (char *) NULL)
            return(MagickPass);
          (void) SetImageAttribute(image,key,NULL);
          return(MagickFail);
        }
      if (p->next == (ImageAttribute *) NULL)
        break;
    }
  /*
    Place new attribute at the end of the attribute list.
  */
  attribute->previous=p;
  p->next=attribute;
  return(MagickPass);
}
