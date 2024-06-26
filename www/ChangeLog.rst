================================
GraphicsMagick ChangeLog
================================

2024-03-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/version.h.in: Copyright year is 2024!

2024-03-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/t/{read.t, write.t}: Update expected TGA signatures.

  - version.sh (PACKAGE\_VERSION): Update for the 1.3.43 release.

2024-03-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news.

  - www/index.rst: GraphicsMagick is released on March 23, 2024.

  - www/Changes.rst: 1.3.43 is released in 2024.

  - version.sh: Update library versioning in preparation for
    release.

2024-03-17  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/tests/runtest.bat: Enable additional logging
    with setting "set MAGICK\_DEBUG=exception".

2024-03-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - VisualMagick/tests/runtest.bat: Remove tests for format
    identifiers which are not even images, or require special add-on
    software, or could otherwise not work.

  - tests/constitute.c: Handle capital 'Y' and 'K' while checking if
    a CMYK map is specified.

  - VisualMagick/tests/run\_constitute.bat: Re-generate test script
    based on what current tests/constitute.tap does.

  - VisualMagick/bin/log-eventlog.mgk: Logger configuration suitable
    for non-console apps (was log.mgk).

  - VisualMagick/bin/log.mgk: Change default configuration to be
    suitable for 'console' apps with working 'stderr', such as used by
    the test suite.

2024-03-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news.

  - www/api/types.rst: Fix spelling errors and out-of-date
    information in types.rst.  Resolves SourceForge patch #80 "Update
    types.rst documentation".

2024-03-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/magick\_wand.c (MagickPingImage, MagickReadImage)
    (MagickReadImageBlob, MagickReadImageFile): AppendImageToList()
    now leaves the image pointer pointing to the end of the list.  The
    Wand implementation expects that wand->images points to the
    begining of the list.  Update wand->images to point to the
    beginning of the list.  Resolves SourceForge issue #735
    "[MagickWand] Potential regression when creating GIFs".

2024-03-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - utilities/Makefile.am: Give up on the attempt to selectively
    force C++ linkage by introducing a C++ file for components which
    should have C++ linkage.  A libtool bug, and an Automake weakness
    prevented this from working as expected.
    (UTILITIES\_CLEANFILES): Clean-up utilities/tests/composite\_tmp.msl.

2024-02-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/hrz.c (RegisterHRZImage): Remove defective comment.

2024-02-26  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/hrz.c: Seekable blob should not be needed.

2024-02-25  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Do not copy TIFFTAG\_ORIENTATION from EXIF.
    It is already handled by image->orientation variable.

  - coders/tga.c: Emit warning to logs when orientation is
    not supported.
    FIED: Need to research what case was expected to be
    tested here. This test case can never be true and so it
    is commented out for the moment.

2024-02-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tga.c (WriteTGAImage): Eliminate compiler warnings.

2024-02-24  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: Propagate orientation in TGA writer.
    The linescan order must be reverted.

2024-02-23  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/configure/configure.rc: Disable static single threaded
    runtime choice. This runtime is not suported in Visual Studio 2008
    and all newer versions.

2024-02-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/psd.c: If module gets built, but EnableBrokenCoders is
    not true, then include empty registration functions.

  - Makefile.am: Rename coders/acppfile.cpp to magick/acppfile.cpp
    and include some in-progress changes which are necessary for the
    build to still work.

2024-02-22  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/tests/runtest.bat: G,K and Y tests started to fail
    before several months without knowing why. Do not stop. Too bad.
    Added test for HRZ format.

2024-02-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/{rwblob.tap, rwfile.tap}: Add HRZ to sanity checks.

  - coders/hrz.c (RegisterHRZImage): Set 'seekable\_stream' and
    'adjoin' correctly.

2024-02-21  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/hrz.c: Provide writer.
  - coders/tga.c: 32 bit TGA colormap is expected to have a valid
    alpha channel.

2024-02-20  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: TGA reader seems to ignore image orientation,
    fixed now.

2024-02-18  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - jpeg/\*: Update JPEG builtin library to 9f.

2024-02-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c (FreeMagickClientData): Assure that jpeg\_pixels is
    non-NULL before dereferencing it. Resolves oss-fuzz issue 66666:
    "graphicsmagick:coder\_DCM\_fuzzer: Null-dereference READ in
    ReadJPEGImage".  This is an issue introduced by yesterday's
    submission.

2024-02-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/enum\_strings.c (StringToCompressionType): Recognize
    "LosslessJPEG" as indicating LosslessJPEGCompression.

  - coders/jpeg.c (WriteJPEGImage): Added support for writing lossy
    or lossless 12 bits, and lossless 16-bits using libjpeg-turbo-3.0.
    Added the -define options 'jpeg:data-precision',
    'jpeg:lossless-precision', and 'jpeg:lossless-predictor', to
    provide control over the parameters used.  Please note that most
    applications do not support lossless JPEG compression (and only
    support a sample size of 8) so take care not to use these features
    if it not known that all involved software can support them!

2024-02-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c (WriteJPEGImage): Do some preparation to implement
    support for libjpeg-turbo 3.X APIs while writing deep JPEG.

  - coders/tiff.c (AddIFDExifFields): Fix a compilation warning.

  - coders/jpeg.c (ReadJPEGImage): Support libjpeg-turbo 3.X APIs to
    read deep JPEG.

2024-02-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (AddIFDExifFields): Add casts to prevent signed vs
    unsigned char pointer warnings.

  - m4/ltversion.m4: Update to libtool 2.4.7.

2024-02-06  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Fix endianity problem related to string packed in a DWORD.

2024-02-05  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Ability to handle EXIF strings without zero termination.

2024-02-04  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Performance improvement for lo endian architecture.

2024-01-29  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Allow succesfull compilation for older libtiff.

2024-01-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news as of January 28, 2024.

  - scripts/changelog2rst.sh: Assure that generated ChangeLogs have a title.

  - ChangeLog\*: Tidy the ChangeLog syntax.

2024-01-28  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Fractional arrays needs either double[] or float[]
    depending on TIFFFieldSetGetSize(fip).

2024-01-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (AddIFDExifFields): Avoid signed/unsigned comparison warnings.

2024-01-27  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: EXIF GPS IFD tags are copied now.

2024-01-26  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - tiff/libtiff/tif\_dir.c: Apply Su Laus leak fix from:
    https://gitlab.com/libtiff/libtiff/-/commit/376916d25f39bab69a3ed16963fd3f186870942c

2024-01-26  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Refactor types to magick\_uint16\_t and
    magick\_uint32\_t.

2024-01-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): TIFFFreeDirectory() statements
    necessary to avoid memory leak in libtiff versions lacking merge
    request 563 "Avoiding memory leaks when using
    TIFFCreateDirectory()".

2024-01-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jxl.c: Directly include jxl/version.h rather than
    depending on it being implicitly included by other jxl headers.

2024-01-24  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Copy uint32\_t and uint8\_t EXIF arrays into a tiff.

2024-01-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/Hg.rst: Change from defunct OSDN to Heptpod.

2024-01-23  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Copy uint16\_t EXIF arrays into a tiff.

2024-01-20  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Do not copy TIFFTAG\_XRESOLUTION & TIFFTAG\_YRESOLUTION
    that are already handled by gm functionality.

2024-01-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - utilities/tests/common.sh, common.shi.in: Apply tight read and
    write file size limits during testing.

  - utilities/tests/hald-clut.tap (levels): Make messaging about
    levels more distinct during Hald CLUT testing.

  - fuzzing/utils.cc: Set a write resource limit during oss-fuzz
    testing.

  - magick/blob.c (ReadBlobByte): EOF detection requires reading
    past the end of the file, so allow for that.

2024-01-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Copyright.txt, scripts/html\_fragments.py, ChangeLog.2023: Rotate
    ChangeLog and update copyright statements for 2024.

2024-01-20  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Place string terminator for more code safety.

2024-01-19  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Temporary fix that supresses leak in tiff writer.

2024-01-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/symbols.h, wand/wand\_symbols.h: Update Gm-prefixed
    symbols.

  - coders/bmp.c: Eliminate 'TForeignFormatDesc' and 'StoreDescPNG'
    which were accidentally writeable globals.

  - Fix spelling errors in code and documentation.

2024-01-13  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Prevent sign expansion and bogus contents in upper 2
    bytes for TIFF\_SHORT.

2024-01-12  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Fixed TIFF\_RATIONAL extraction from EXIF.

2024-01-11  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Fix for multiple frames. Do not import
    TIFFTAG\_COMPRESSION, TIFFTAG\_IMAGELENGTH, TIFFTAG\_IMAGEWIDTH ...
    from EXIF.

2024-01-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (EXPERIMENTAL\_EXIF\_TAGS): Change
    EXPERIMENTAL\_EXIF\_TAGS to a simple boolean (rather than an ifdef)
    and default it to 0.  This needs to be in place until the TIFF
    writer no longer crashes.

  - fuzzing/oss-fuzz-build.sh: Skip missing libheif optional
    dependencies in oss-fuzz build.

2024-01-07  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Fix TIFF\_RATIONAL - Two LONGs: the first represents
    the numerator of a fraction, the second the denominator.

2024-01-06  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Extract EXIFIFD part from EXIF profile.

2024-01-03  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c: Make two functions "EnsureNextImage()" and
    "LoadPaletteRec()" static.

2024-01-02  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/tiff/LIBRARY.txt: Exclude more tiff/port files.

2024-01-01  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - tiff/libtiff/tiffconf.h: Fix path to webp/types.h.
