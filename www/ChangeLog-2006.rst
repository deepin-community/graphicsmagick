2006-11-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/Magick++/Image.html: Fix documentation regarding retrieving
    EXIF attribute.

  - magick/command.c: Fix typo in usage messages.

2006-11-02  Daniel Kobras  <kobras@debian.org>

  - coders/dcm.c: (ReadDCMImage) Prevent buffer overflow of
    `photometric` array in DCM coder. Original patch thanks to
    M Joonas Pihlaja. (CVE-2006-5456)

  - coders/palm.c: (ReadPALMImage) Fix heap overflows of `one\_row`
    array in PALM coder. Original patch thanks to M Joonas Pihlaja.
    (CVE-2006-5456)

2006-10-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Updated libtool to latest CVS head version (1.2352 2006/10/24)
    in order to fix a bootstrap nit.

2006-10-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Updated autoconf to version 2.60, automake to version 1.10, and
    libtool to latest CVS head version (1.2348 2006/10/22).

2006-09-11  Daniel Kobras  <kobras@debian.org>

  - coders/xcf.c (ReadBlobStringWithLongSize): Add new parameter `max`
    to prevent overflowing the `string` array. (CVE-2006-3743)
    (ReadOneLayer): Adjust callers of ReadBlobStringWithLongSize(), and
    guard against infinite loops on premature end-of-file.
    (ReadXCFImage): Adjust callers of ReadBlobStringWithLongSize(), and
    guard against infinite loops on premature end-of-file.

2006-09-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/sgi.c (ReadSGIImage): Mostly applied Debian patch for
    CVE-2006-4144 security issue related to RLE decoding.  Also added
    complete verification of file header.

  - magick/image.c (ComputePixelError): Add progress monitor.
    (GetImageStatisticsMean): Call progress monitor less often.
    (GetImageStatisticsVariance): Call progress monitor less often.

2006-08-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): ImageInfo `endian` option now
    controls TIFF byte-order rather than bit-order when writing.

  - coders/png.c (ReadOnePNGImage): Fix compilation problem.  Patch
    submitted by Aron Stansvik.

2006-07-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c (WriteJPEGImage): Clear the JPEG library
    structures in order to ensure a completely clean slate.

2006-06-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (ConvertImageCommand): Fix memory leaks which
    occured when an image was not returned.

  - magick/command.c (IdentifyImageCommand): Ditto.

  - magick/command.c (MogrifyImageCommand): Ditto.

2006-06-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c: Add mention of -resample to convert and
    mogrify usage messages.

2006-05-31  Ralf Wildenhues  <Ralf.Wildenhues@gmx.de>

  - configure.ac: Fix arguments to AC\_CHECK\_HEADER.

2006-05-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): -define tiff:alpha= override was
    only working if the TIFFTAG\_EXTRASAMPLES tag was present.  Now it
    is always available when an alpha channel is present.

2006-05-11  JH  <jh@ops.everybox.com>

  - GraphicsMagick.spec.in (files devel): Include
    %{\_libdir}/lib%{name}Wand.so.

2006-05-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/nt\_base.c (NTGhostscriptEnumerateVersions): Recent GNU
    Ghostscript identifies itself as "GPL Ghostscript".

2006-04-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tiff: Updated bundled libtiff to version 3.8.2.

2006-04-05  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c: Sets image is\_grayscale flag as well as added more
    symbolic constants.

2006-04-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (IMAGE\_DATA\_ROUNDING): Thanks to Steve Sloan for
    noticing that 8K is 8192 rather than 8092.  Added a define to
    allow tailoring the pixel data alignment boundary in case 8K is
    not the right answer for some reason.

2006-03-20  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c: Ensure that unusued opacity channel is set to opaque.

  - PerlMagick/t/input.art: New ART test image.

  - PerlMagick/t/input8.mat: New MATLAB test image (8-bit indexed).

  - PerlMagick/t/input\_dbl.mat: New MATLAB test image (double grey)

  - PerlMagick/t/input\_rgb.mat: New MATLAB test image (8-bit RGB)

2006-03-19  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c: Use symbolic constants rather than plain numbers
    so the module is more maintainable.  Correct the format for the
    day of the week.

2006-03-13  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c (WriteMATLABImage): Add RGB writer support for
    MATLAB format.

2006-03-11  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c (ReadMATImage): RGB support for MAT reader.

2006-03-02  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c: Fixes for observed crash.  Byte and word formats
    are working.

2006-02-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - doc/environment.imdoc: MAGICK\_FONT\_PATH has not been supported
    since 1.1.  Remove mention of it!

2006-02-23  Mike Chiarappa  <mikechiarappa@libero.it>

  - BCBMagick: Updated to latest changes

2006-02-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/sgi.c (ReadSGIImage): Properly compute image depth for
    16-bit SGI image files.

2006-01-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/utility.c (GetExecutionPathUsingName): Search executable
    search path for binary.

2006-01-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (ReadDPXImage, WriteDPXImage): Alpha channel in DPX
    uses zero, or reference black, to represent an opaque pixel.

2006-01-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/semaphore.c (AllocateSemaphoreInfo): Allow semaphores to
    recurse on POSIX systems which support recursive semaphores but
    also warn if the semaphore recurses.

  - magick/log.c (SetLogEventMask): Avoid deadlock if invoked before
    log.mgk has been loaded.

  - magick/attribute.c (GenerateEXIFAttribute): Fix memory leak on
    error which was reported by Michal Kowalczuk.

2006-01-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/constitute.c (ReadImage): Avoid crash if delegate fails
    to return image.

2006-01-03  Daniel Kobras  <kobras@debian.org>

  - magick/attribute.c (GenerateEXIFAttribute): Fix EXIF IFD stack
    overflow vulnerability.

  - configure.ac: Fix typo in HTMLDecodeDelegate.

