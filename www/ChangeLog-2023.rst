================================
GraphicsMagick ChangeLog - 2023
================================

2023-12-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news as of December 30, 2023.

  - magick/resource.c (\_UpdateMagickResourceHighwater): New private
    function to support updating highwater values where it otherwise
    does not naturally happen.  The highwater values represent the
    result of successful requests so they may be used to evaluate the
    resource limit requirements of a particular request.

  - magick/resource-private.h: New header file to contain private
    definitions pertaining to resource allocation.

2023-12-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/resource.c: Add a resource 'highwater' value which is
    updated to the maximum resources used for that resource type.
    This value is currently only reliably updated for SummationLimit
    LimitType.  Trace the highwater values when resource tracing is
    enabled.

2023-12-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news as of December 28, 2023.

  - configure.ac: fixup LFS check for autoconf-2.72. Patch by Sam
    James <sam@gentoo.org>.

    For the 'other' case, we were using the value of
    ac\_cv\_sys\_file\_offset\_bits for -D\_FILE\_OFFSET\_BITS to pass down
    into the Perl module build, but autoconf-2.72 drops the use of
    ac\_cv\_sys\_file\_offset\_bits in
    cf09f48841b66fe76f606dd6018bb3a93242a7c9, so this ends up defining
    '-D\_FILE\_OFFSET\_BITS=' which then breaks the build.

    I've just added a hack to preserve the old behaviour to avoid
    passing a blank value.

2023-12-27  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - tiff/: Update libtiff to 4.5.1.

2023-12-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/heif.c (ReadHEIFImage): Support setting image width
    limit.

  - configure.ac: Check libheif for
    heif\_context\_set\_maximum\_image\_size\_limit().

  - coders/jxl.c: Improve JXL reader/writer exception information.

2023-12-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update with news since the last release.

  - coders/tiff.c: Disable new EXIF code which is not working
    correctly yet.  Enable using EXPERIMENTAL\_EXIF\_TAGS.

  - fuzzing/oss-fuzz-build.sh: Remove unnecessary space in include
    path argument.

  - coders/jxl.c (RegisterJXLImage): Fix version identification.
    (ReadJXLImage): Add error tracing.
    (WriteJXLImage): Add error tracing.

2023-12-18  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Check for NULL in EXIF tag name being logged.

2023-12-17  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c Check recipe compatibility for TIFFSetField().
    Improved optional log record:
    Extracted tag from EXIF 213h, Field 3, Long2 1, val 2 YCbCrPositioning

2023-12-16  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Attempt to store EXIF inside TIFF image.

2023-12-11  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c: Fix for oss-fuzz issue 64935:
    "graphicsmagick:enhance\_fuzzer: Heap-buffer-overflow in ReadBlob".

2023-12-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jbig.c (ReadJBIGImage): Attempt to set maximum image
    dimensions based on resource limits before calling jbg\_dec\_in() so
    it will quit on excessively large images.  This often works, but
    not all the time.

2023-12-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Add -DJPEGXL\_ENABLE\_SKCMS=false to
    libjxl build since skcms is not working with static linkage.

  - configure.ac: Try really hard to configure everything, even if
    pkg-config is not present or misbehaves. If pkg-config is not
    present, it may be necessary to manually set CPPFLAGs in order to
    find the FreeType and libxml2 headers.  Also print any error
    information that pkg-config produces.  jxl\_threads is not a hard
    requirement.  Do not search for TRIO by default.  The user needs
    to specify --with-trio=yes in order to enable searching for TRIO.

2023-12-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/miff.c (ReadMIFFImage): Handle unexpected EOF in version
    0 bzip2 compressed MIFF.  Addresses oss-fuzz "Issue 64851:
    graphicsmagick:coder\_MIFF\_fuzzer: Timeout in coder\_MIFF\_fuzzer".

  - coders/jbig.c (ReadJBIGImage): Add error detection. Addresses
    oss-fuzz "Issue 64781: graphicsmagick:coder\_JBIG\_fuzzer:
    Null-dereference READ in jbg\_dec\_getimage".

  - magick/export.c (ExportGrayQuantumType): Only use 'Special
    "fast" support for two-color PsudeoClass.' case when image has two
    colors.  Otherwise output image is not correct!

2023-12-07  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c Deallocate palette when image load fails.

2023-12-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: If doing oss-fuzz CI testing, then
    only include primary-class coders to improve chances of success

  - coders/jbig.c (RegisterJBIGImage): Reduce to 'unstable' coder
    class given that 'JBIG-Kit' is not yet proven to survive fuzz
    testing.

  - coders/dcraw.c (RegisterDCRAWImage): Reduce to 'unstable' coder
    class given that 'dcraw' is not fuzz tested at all.

2023-12-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/coder\_list.cc: Exclude format names depending on an
    external 'dcraw' program.

2023-12-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Print data returned from PKG\_CHECK\_MODULES if
    VERBOSE is defined to some value.

  - fuzzing/oss-fuzz-build.sh: Add LIBS=-lc++ until GM's static
    linking with C++ libraries is perfected.  Enable JXL and HEIF in
    the oss-fuzz build.

  - fuzzing/coder\_list.cc: Exclude more formats.

2023-11-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Add bzip2 and libjbig to the oss-fuzz
    build.

2023-11-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Build zlib and zstd as static.
    
  - coders/Makefile.am: Heif library is also C++ so link with C++.

  - configure.ac: Report in the configure summary if OpenMP is
    supported, as well as the OpenMP link library selected.

  - coders/heif.c (ReadHEIFImage): heif\_init() expects an argument.

  - configure.ac: Fix typo when testing for \_OPENMP which caused the
    test to always pass.  Remove forced LIB\_MATH=-lm.

2023-11-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Continued work on the oss-fuzz build
    script.  Still not there yet, but closer.

  - configure.ac: Fix many bugs related to building library
    dependency list.  Much thanks to Tobias Mark for a patch to fix
    the library dependency order.

2023-11-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Eliminate redundant check for HEIF library.

  - www/INSTALL-unix.rst: Document how to get a maximally-static
    build using `PKG\_CONFIG='pkg-config --static' ./configure`.

  - fuzzing/oss-fuzz-build.sh: Continued work to try to accomplish a
    static oss-fuzz build. Not quite successful yet.

  - magick/GraphicsMagick.pc.in (Description): Added project URL.

  - configure.ac: Major change to require/trust pkg-config much more
    than before.  Deleted outdated code.

2023-11-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/GraphicsMagick.pc.in: Add OpenMP runtime library as a
    private dependency.

  - coders/Makefile.am: If JXL is enabled, then link the JXL module
    with C++ (if modules are enabled), or the GraphicsMagick library
    with C++ (if modules are not enabled).

  - configure.ac: Fix detection of if OpenMP is enabled. Add the
    OpenMP runtime as an explicit library dependency.

  - coders/acppfile.cpp: An example useless C++ file.

2023-11-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/Makefile.am: When linking JXL or FlashPIX, use the C++
    linker.

2023-11-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: libbrotlidec and liblbrotlienc depend on
    libbrotlicommon.

  - fuzzing/oss-fuzz-build.sh: Build script improvements.  Change
    'freetype2' to 'freetype'. Add libde265, libheif, and libjxl to
    build.

2023-11-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/thanks.rst: Provide attributions expected by
    https://foss.heptapod.net/

  - www/Hg.rst: Replace OSDN with foss.heptapod.net.

  - README.txt: Replace OSDN with foss.heptapod.net.

  - LICENSE: Provide a license file at an expected location.

2023-11-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/{rwfile.c, rwblob.c} (DescribeFrames): Add a 'ping' option
    in case this function is activated on an image read with the
    'ping' flag set.

2023-11-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Use CPPFLAGS delivered by pkg-config for
    libheif. Applied patch
    configure-libheif-cppflags-deduplicated2.patch from SourceForge
    patch #79 "Use CPPFLAGS delivered by pkg-config".

  - coders/tiff.c (WriteTIFFImage): Call TIFFFlush() to detect any
    errors which might otherwise be lost by TIFFClose().  Restore
    broken file deletion code.

2023-11-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/rwfile.c, tests/rwblob.c: Print reproducible test
    information.

2023-11-13  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/tests/runtest.bat Summarize and display total
    amount of problems during testing.

2023-11-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/resource.c, magick/blob.c: Add support for a per-file
    write limit.  This imposes a limit on the number of uncompressed
    bytes written.  The behavior when the limit is hit is similar to
    an unexpected write error, as if the disk is full.
  - coders/: Updated the many coders to behave correctly when faced
    with an unexpected write error.
  - magick/blob.c: If the write limit is hit, then the truncated
    output file is automatically removed.

2023-11-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - config/delegates.mgk.in, VisualMagick/bin/delegates.mgk:
    Re-direct Ghostscript stdout to stderr to avoid output corruption
    when GM stdout is redirected to a file.  Addresses SourceForge
    issue #729 "GhostScript warnings in files on stdout".

2023-11-08  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/jnx.c JNX decoder is also vulnerable against size injection.

2023-11-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/colorspace.c (RGBTransformImage): Move cast in
    primary\_info.x and primary\_info.y calcuation.  Addresses concern
    expressed in SourceForge issue #730 "Recent colorspace conversion
    change".

2023-11-07  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c: Revert
  - coders/mat.c: Prevent against geometry injection.

2023-11-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/wpg.c (ExtractPostscript): Restore previous
    implementation.

2023-11-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/utility.c (ExpandFilenames): Fix memory leak of existing
    allocations if realloc() fails.

  - magick/memory.c (MagickReallocStd): Added function to expose
    standard realloc() functionality to allow cleanup of original
    object.

  - magick/list.c (AppendImageToList): Added image could itself be a
    list, so seek again for the end of the list.
    (GetImageListLength): Count value should be unsigned long.

  - coders/wpg.c (ReadWPGImage): Reset image rows and columns to
    zero.
    (ExtractPostscript): Pass original image pointer storage.

  - coders/fits.c (ReadFITSImage): Reset image rows and columns to
    zero.

  - coders/bmp.c (ExtractNestedBlob): Reset image rows and columns
    to zero.

  - PerlMagick/t/subroutines.pl (testRead): Remove request for size
    512x512.

  - PerlMagick/t/read.t: Fix checksums for FITS tests.

  - PerlMagick/t/png/read.t: Fix checksum for PNG in BMP format.

  - PerlMagick/Makefile.am (perl-check): Enable verbose PerlMagick
    tests using TEST\_VERBOSE=1.

2023-11-05  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - PerlMagick/t/input1\_PS.wpg PerlMagick/t/input2\_PS.wpg: Add 2
    samples of WPG that really contain embedded EPS.

2023-11-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/bmp.c (ExtractNestedBlob): Always need to remove image
    which is being replaced.

2023-10-21  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c: Do not touch to image structure from palette reader.
    "RecordLength" is a 32bit variable, it should not be long that expands
    to 64bits.

2023-10-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (CommandAccessMonitor): Add "Access Request: "
    to the printed access request message.

  - magick/effect.c (AddNodeMedianList): Make sure that 'update' is
    initialized.

  - magick/colorspace.c: primary\_info x,z are float so use floating
    point math to compute them.

  - coders/wpg.c: Avoid signed/unsigned compare warning

  - Many files: Add casts to prevent unnecessary value truncation in
    WIN64 build.

2023-10-21  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c: Remove code duplicity for loading WPG1 and WPG2 palette.

2023-10-20  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c Fix loop end to 256 insert "Palette" chunk header
    to debug log.

2023-10-19  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c: Fix for potential access to uninitialised object
    "Palette".

2023-10-18  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c: Do not store palette into image structure before
    a raster chunk is found. Implemented for WPG l1 only.

2023-10-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/wpg.c (ReadWPGImage): If a colormap is provided, make
    sure that PsuedoClass indexes are initialized before promoting
    image to PseudoClass. Addresses oss-fuzz issue 63335:
    "graphicsmagick:coder\_WPG\_fuzzer: Use-of-uninitialized-value in
    GrayscalePseudoClassImage".  This is a stop-gap fix until the
    WPG reader supports a colormap independent of the image, to be
    used when needed.

2023-10-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): Remove safe-guards against use
    of incorrect PHOTOMETRIC\_MINISWHITE or PHOTOMETRIC\_MINISBLACK
    photometic for Group3 and Group4 compression.  Other photometrics
    are rejected when using Group3 or Group4 compression.  The user is
    responsible for providing the correct parameters.  This is to
    address discussion on the graphicsmagick-help list on October 16,
    2023 under the topic "tiff:photometric and CCITT compression".

2023-10-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/wpg.c (ReadWPGImage): If a colormap is provided, make
    sure that PsuedoClass indexes are initialized before promoting
    image to PseudoClass. Addresses oss-fuzz issue 61394:
    "graphicsmagick:coder\_WPG\_fuzzer: Use-of-uninitialized-value in
    GrayscalePseudoClassImage".
    (ReadWPGImage): If pixel cache was not initialized at all, then
    set DirectClass pixels as well.

2023-10-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/heif.c (ReadHEIFImage): Call heif\_init() and
    heif\_deinit() if they are available.

2023-10-02  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Emit error when ExportImagePixelArea fails.
    This should fix oss-fuzz-63096 issue.

2023-10-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/wpg.c (ReadWPGImage): Add a FIXME comment for a bug yet
    to be fixed.

  - PerlMagick/t/png/read.t: Add a test case for BMP with embedded
    PNG.  Something is still wrong given that reading using PerlMagick
    is returning two frames rather than one.

  - magick/pixel\_cache.c: Update documentation to reflect that
    GetImagePixels() has been deprecated since 2008, and update
    mention of it to document use of AccessMutableIndexes() or
    AccessImmutableIndexes().

  - coders/pnm.c (ReadPNMImage): Add traces prior to each decoding
    loop to identify the sub-format being decoded.

  - coders/bmp.c (ExtractNestedBlob): Pass pointer to image list to
    satisfy requirements of AppendImageToList() and
    DeleteImageFromList().

2023-10-02  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Attempt to read BMP with 48bpp.

    Use more aggresive image rewind algorithm pasted from mat.c

2023-10-01  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Fix BMP 64bpp reader. See this URL:
    https://stackoverflow.com/questions/20778227/get-64bpp-image-color

2023-09-30  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Attempt to read BMP with 64bpp.

  - coders/bmp.c: Remove code duplicity. 1bpp, 2bpp and 4bpp is
    using a same code.

2023-09-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/bmp.c (StoreAlienBlob): Fix compilation warning in log
    statement.

2023-09-28  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - PerlMagick/t/png/input\_PNG.bmp: Add a BMP sample with BI\_PNG
    compression.

2023-09-27  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Writer for BI\_PNG compression.

2023-09-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - version.sh : Updates for the 1.3.42 release.

  - NEWS.txt: Update the news for the 1.3.42 release.

  - VisualMagick/installer/redist/VC2013/note.txt: Add note about
    where to get Visual Studio 2013 redistributables.  File also
    serves to create the needed directory.

2023-09-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/Makefile.am (coders\_bmp\_la\_LIBADD): Extra modules are not
    needed because the dependencies are taken care of by loading other
    modules.

2023-09-23  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Emit error when OS/2 bitmap with compression
    BI\_JPEG or BI\_PNG is detected. Read files compressed with BI\_PNG.

2023-09-22  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Display bitmasks into optional log.

2023-09-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/t/jpeg/read.t: Add test for JPEG-compressed BMP.
    Moved input reference file to PerlMagick/t/jpeg/input\_JPEG.bmp and
    reference output file is
    PerlMagick/t/reference/jpeg/input\_JPEG.bmp.miff.

2023-09-21  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - PerlMagick/t/input\_JPEG.bmp: Added BMP sample with JPEG encoding.

  - coders/bmp.c: Only 16bpp and 32bpp is supported for BI\_BITFIELDS
    compression type. 8bpp is not implemented.  This fixes oss-fuzz
    issue 62519: "graphicsmagick:coder\_BMP\_fuzzer:
    Use-of-uninitialized-value in WriteBMPImage".

2023-09-20  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Remove duplicity, same information has been logged
    twice.
    
    22:54:49 0:0.002746  0.000u 9688 bmp.c/ReadBMPImage/750/Coder:
    File size: Claimed=8, Actual=1129

    22:54:49 0:0.002906  0.000u 9688 bmp.c/ReadBMPImage/1105/Coder:
    File size: Claimed=8, Actual=1129

2023-09-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/{constitute.c, drawtest.c, rwblob.c, rwfile.c}: Fix GCC 13
    warning.

2023-09-19  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/tests/runtest.bat: VID is not a regular image format.
    Do not use batch test for it.

2023-09-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/Makefile.am (coders\_bmp\_la\_LIBADD): The BMP coder module
    now optionally depends on libjpeg.

2023-09-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - doc/options.imdoc: Add documentation for -define bmp:allow-jpeg.

2023-09-18  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Ability to write JPG encoded image.
    Using a new command line switch: -define bmp:allow-jpeg

2023-09-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jp2.c (BlobRead): For old libJasper, return 0 for size
    value if the actual value does not fit in an 'int'.
  - coders/jp2.c (BlobWrite): For old libJasper, return 0 for size
    value if the actual value does not fit in an 'int'.

  - magick/command.c (MagickCommand): Eliminate duplicate utility
    name output in error messages when utility is executed via a
    magick compatibility link.  For example via symbolic link from
    'convert' to 'gm'.  This problem was added when the initial batch
    mode implementation was submitted.  Addresses SourceForge issue
    #727 "convert convert" in error messages.

  - VisualMagick/configure/welcome\_page.cpp: Update configure
    welcome text based on my current understanding.

2023-09-17  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/configure/welcome\_page.cpp: Notify user that MSVC
    older than 2008 is not supported.

  - VisualMagick/magick/magick\_config.h.in Expose ENABLE\_SVG\_WRITER.
    For debugging purpose this should be always enabled. Only for
    final release you can disable it.

2023-09-16  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/mat.c: Cleanup one unneeded warning.

2023-09-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - VisualMagick/magick/magick\_config.h.in: Update the copyright
    year range.

  - Copyright.txt: Update the copyright year.

2023-09-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/wmf.c (ipa\_bmp\_draw): Print bmp.data as the pointer it is
    rather than casting to a 'long'.

  - coders/pnm.c (PNMReadThreads): Fix compiler warning regarding
    overflow.

  - coders/sun.c (WriteSUNImage): Test for sun\_info.length overflow
    in a way which should not provoke a compiler warning.

2023-09-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - VisualMagick/magick/magick\_config.h.in: Block building the XTRN
    coder unless the user enables EnableXTRNCoder.  The XTRN coder is
    primarily used by the optional contributed ImageMagickObject COM+
    DLL object, but it might be used for a similar purpose.  The XTRN
    coder serves no purpose unless invoked from the address space of a
    program using GraphicsMagick.

2023-09-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/{constitute.c, drawtest.c, rwblob.c, rwfile.c}: Initialize
    locale settings the same as the 'gm' utility.

  - magick/{drawing\_wand.c, drawtest.c, magick\_wand.c, pixel\_wand.c,
    wandtest.c}: Initialize locale settings the same as the 'gm'
    utility.

2023-09-09  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/xtrn.c: Fixed crash on dereferenced NULL pointer.

2023-09-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/attribute.c (SetImageAttribute): Remove
    SetImageAttribute() Extending attribute value text code entirely.

2023-09-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Updated the News.

  - magick/attribute.c (SetImageAttribute): Disable attribute
    extension deprecation warning printf.  It may be that eliminating
    support for attribute value extension will never happen due to
    subtly entrenched internal usage.

  - coders/pnm.c (ReadPNMImage): Fix reading comments from PAM
    format.

2023-09-06  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Reverting to BI\_BITFIELD. BI\_ALPHABITFIELDS seems
    to be very rare.

2023-09-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/wmf.c (ipa\_draw\_text): Treat pointer inputs as if they
    may be NULL.  Change live printfs to traces.  Adjust white-space
    in whole module to current conventions.  Addresses SourceForge
    issue #724 "Old WMF display: assert fails in draw.c", although I
    am unable to reproduce it.

2023-09-05  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Sorry for a previous commit. After some
    investigations it seems that bit field masks are behind header
    when BI\_SIZE=40.

2023-09-04  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Default bit split for older BMPs with 32bpp and
    BI\_BITFIELDS set is crazy. Verified against IrFanView and
    bmpsuite-2.7.zip - image g/rgb32bf.bmp.

2023-09-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/resize.c (ResizeImage): Restore vertical/horizontal
    filter order decision logic which was in place before the 1.3.41
    release since it may result in tiny changes to low order bits in
    16-bit/sample images, which may be concerning to some.  Resolves
    SourceForge issue #723 "montage result differ between 1.3.40 and
    1.3.41". The provided test-case showed that the filter filter
    order changed from "Vertical/Horizontal" to "Horizontal/Vertical".

2023-09-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImage): Use MaxRGBDouble double
    constant rather than integral MaxRGB as argument to
    StringToDouble().

2023-09-01  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c Bitmap header with size 52 bytes is also valid.

2023-08-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/module\_aliases.h: Add missing module aliases "PNG00",
    "PNG48", "PNG64".

2023-08-31  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: BMP with 2bpp is a legal BMP variant.
    https://en.wikipedia.org/wiki/BMP\_file\_format Quote: "The 2-bit
    per pixel (2bpp) format supports 4 distinct colors and stores 4
    pixels per 1 byte, the left-most pixel being in the two most
    significant bits (Windows CE only)."

    Partial revert: BITMAPV2INFOHEADER: RGB bit field masks,
    BITMAPV3INFOHEADER+: RGBA
    The opacity channel handling is even more complex.

2023-08-29  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: First attempt to read BMP with BI\_JPEG compression
    inside.

2023-08-28  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Remove code duplicity and evaluate BiCompression
    only on one place.

2023-08-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/attribute.c (GetImageInfoAttribute): For the "name" key,
    return the input file base name, until reason is found to do
    otherwise.

  - magick/utility.c (TranslateTextEx): Restore previous
    functionality in which a NULL pointer is returned instead of an
    empty string. Some algorithms are depending on this!  Addresses
    SourceForge issue #722 v1.3.41 "PerlMagick montage.t fails
    completely".

2023-08-23  Fojtik Jaroslav  <JaFojtik@yandex.com>
    
  - VisualMagick\installer\inc\files-dlls.isx
  - VisualMagick\installer\inc\body.isx
    
    Prepare installation script for MSVC2013 runtime.

2023-08-22  Fojtik Jaroslav  <JaFojtik@yandex.com>
    
  - VisualMagick\installer\inc\files-dlls.isx
  - VisualMagick\installer\inc\body.isx
    
    Prepare installation script for MSVC2010 runtime.

2023-08-21  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: When alpha is to be used, writer must not use
    BI\_BITFIELDS compression that instructs to strip alpha.

2023-08-20  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - tiff/libtiff/stdbool2.h MSVC2010 does not have stdbool.h nor inttypes.h

  - coders/bmp.c: Added support for BI\_ALPHABITFIELDS compression.
    https://learn.microsoft.com/en-us/previous-versions/windows/embedded/aa452885(v=msdn.10)
    Remove unwanted duplicite check condition of biCompression.

2023-08-19  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c Reveal a contents of OS22XBITMAPHEADER.

2023-08-17  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Do not throttle on native low endian systems.

2023-08-16  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Populate upper byte to lower byte even for lower
    bpp than 8. It overcomes quantum scalling error in gm. Code should
    be redesigned, but it is better than previous state.

    Enforce default color masks when bmp\_info.compression==BI\_RGB
    Existing masks will be ignored.

2023-08-17  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c:  Enforce default matte for 40 byte header & 32bpp.

2023-08-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): For common formats with the
    required number of channels, but one is an 'unspecified' channel,
    promote unspecified alpha to unassociated alpha so that the alpha
    channel is not ignored. Addresses the remainder of SourceForge
    issue #718 "Set reasonable defaults when writing TIFF with
    transparency".

2023-08-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Makefile.am (CHANGELOGS): Changelogs ChangeLog.2021 and
    ChangeLog.2022 where missing from the distribution.

2023-08-15  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c:  Fix reading corruption 16bpp.

2023-08-15  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c:  Fix compilation problem in MSVC.

2023-08-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): Default the alpha channel to
    type EXTRASAMPLE\_UNASSALPHA(2).  The default was
    EXTRASAMPLE\_UNSPECIFIED(0), which is particularly unfortunate
    given that GraphicsMagick 1.3.41 now silently ignores such
    channels. Patch by Markus Mützel.  Addresses SourceForge issue
    #718 "Set reasonable defaults when writing TIFF with
    transparency".

2023-08-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Updated for 1.3.41 release.

  - version.sh: Updated for 1.3.41 release.

2023-08-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/index.rst: Update Coverity metrics.

  - coders/tiff.c (ReadTIFFImage): Fix garbled logic pertaining to
    photometric checks.  Addresses Coverity 393177 "Structurally dead
    code".

  - coders/heif.c (ReadHEIFImage): For libheif versions <
    0x01090000, ignore\_transformations is always 1. Add a conditional
    check to avoid Coverity 384803 "Logically dead code" for old
    versions.

  - coders/identity.c (ReadIdentityImage): Check the return value
    from AllocateImageColormap().  Addresses Coverity 384802
    "Unchecked return value".

  - magick/utility.c (ExpandFilename): sysconf() can return a
    negative value (e.g. -1).  Verify that the value is greater than 0
    before using it.  Addresses Coverity 384798 "Out-of-bounds
    access".

2023-08-09  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: 64 bytes for BMP header is reserved for OS/2
    https://www.fileformat.info/format/os2bmp/egff.htm

2023-08-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/bmp.c (ReadBMPImage): Re-indent/format for consistency.
    (ReadBMPImage): Adjust expected bmp\_info.size (change 64 to 120).

2023-08-08  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: Data behind declared BMP header should not be read.
    It could poison newly converted image with garbage.

2023-08-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/cineon.c (GenerateCineonTimeStamp): Correct strlcpy()
    length arguments so they are based on the actual destination
    buffer size.  Based on a report from Dirk Müller
    <dmueller@suse.de> that the test suite does not pass with the new
    glibc 2.38 (which finally provides strlcpy()/strlcat()) due to a
    fortify assertion.

2023-08-08  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/bmp.c: CI chunk must have biSize only 12 or 40.

2023-08-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Default field pass count to 1
    since "Unsupported" tags return two arguments.

2023-08-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - jp2/src/libjasper/include/jasper/jas\_types.h: MSVC 17.6.5 needs
    the \_PFX\_PTR definition.

  - coders/bmp.c (ReadBMPImage): Fix GCC 13.1.0 warning about
    quantum\_bits being possibly used while uninitialized.  I don't see
    how that is possible based on current logic, but avoid the
    warning.

  - magick/gem.c (ExpandAffine): Mark as a pure function.

2023-07-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/xcf.c (ReadXCFImage): Limit the maximum number of layers
    to the range of 'long'.  Adjust arithmetic/cast to avoid undefined
    behavior warning. Resolves SourceForge issue #713
    "coders/xcf.c:1926:53: warning: iteration 9223372036854775806
    invokes undefined behavior".

2023-07-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news!

  - Magick++/bin/GraphicsMagick++-config.in: Remember the name of
    the C++ compiler used, and suggest it in the usage message, as
    well as reproduce it via the '--cxx' option.

  - magick/GraphicsMagick-config.in: Remember the name of the C
    compiler used, and suggest it in the usage message, as well as
    reproduce it via the '--cc' option.

2023-07-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c (ReadIPTCProfile): Fix malformed IPTC data
    parsing.  SourceForge patch #78 "JPEG: fix malformed IPTC data
    parsing" by Przemysław Sobala.

2023-07-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Fix typo which breaks oss-fuzz build.

  - coders/jxl.c (WriteJXLImage): Port forward to latest development
    0.9.0 API, which removes unused pixel\_format from
    JxlDecoderGetColorAsEncodedProfile(),
    JxlDecoderGetICCProfileSize(), JxlDecoderGetColorAsICCProfile()
    and silently drops JXL\_ENC\_NOT\_SUPPORTED.

2023-07-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Add --disable-ifunc to xz build
    options to avoid segmentation violation, matching options
    successfully used by ImageMagick's oss-fuzz build.

2023-07-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/attribute.c: In GetImageClippingPathAttribute(), check
    for the presence of the clipping path name (ID=2999). If that's
    found, it searches for a path with that name. Otherwise, it
    returns NULL.  Based (in spirit) on SourceForge #62 "Fix for
    GetImageClippingPathAttribute".

  - configure.ac (LIB\_HEIF): SourceForge patch #71 "Use pkg-config
    for libheif in configure".

  - TclMagick/{configure.ac, generic/Makefile.am,
    generic/pkgIndex.tcl.in, pkgIndex.tcl}: SourceForge patch #74
    "TclMagick: generate generic/pkgIndex.tcl automatically and change
    pkgIndex.tcl".

  - TclMagick/generic/Makefile.am: SourceForge patch #73 "TclMagick:
    remove lib prefix from library files".

  - TclMagick/unix/m4/tcl.m4: SourceForge patch #72 "TclMagick: fix
    install for unix".

2023-06-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magick.c: Add some documentation regarding OpenMP.

  - coders/tga.c (LogTGAInfo): Avoid compiler warning about
    orientation possibly being undefined.  Update source code to
    conform to common style.

  - fuzzing/oss-fuzz-build.sh: Produce more build information in
    fuzzing build.

2023-06-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac, coders/Makefile.am: Jasper is now optionally
    dependent on libheif.

2023-06-27  Przemysław Sobala  <przemyslaw.sobala@gmail.com>

  - magick/GraphicsMagick.pc.in (Libs.private): Fix pkg-config files
    for static build.

2023-06-21  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/topol.c: Fix tile positioning.

2023-06-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/webp.c (ReadWEBPImage): SourceForge patch #77 "Don't
    prepend Exif APP1 header indiscriminately for WebP" by Milos
    Komarcevic.

2023-06-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/heif.c (ReadMetadata): Retrieve image orientation from
    EXIF and store in image.

2023-06-18  Przemysław Sobala  <przemyslaw.sobala@gmail.com>

  - coders/png.c (ReadOnePNGImage): Retrieve image orientation from
    EXIF (if present) and store in image.

  - coders/webp.c (ReadWEBPImage): Retrieve image orientation from
    EXIF (if present) and store in image.

2023-06-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Add --no-po4a --no-doxygen to 'xz'
    build to hopefully get it building again in the oss-fuzz builds.

2023-06-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/operator.c (QuantumDepthCB): Fix compilation failure in
    Q32 build.

2023-06-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (TIFFReadErrors): Mask "Internal error, unknown
    tag" errors from TIFFFieldWithTag() which block working with
    anything but development libtiff.

2023-06-04  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/topol.c: More strict check of proper blob data size.
    
2023-06-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (ConvertImageCommand): Skip MogrifyImages() if
    in ping mode.  Addresses Sourceforge issue #704 "heap overflow in
    gm (magick/effect.c:4417 in SpreadImage)".
    
  - magick/effect.c (SpreadImage): Assure that offsets\_index is in
    valid range.  Reject request if radius is larger than image.
    Addresses SourceForge issue #705 "heap overflow in gm #2
    (magick/effect.c:4405 in SpreadImage)".

2023-06-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/effect.c (GetBlurKernel): Use resource limited memory
    allocator for blur kernel.  This plus MagickStrToD() updates
    addresses #703 "allocation-size-too-big in gm (magick/effect.c:797
    in GetBlurKernel)".

  - magick/utility.c (MagickStrToD): Add infinity and nan checks.

  - magick/command.c (MogrifyImage): Assure that -set has arguments.
    Addresses SourceForge issue #701 "Segmentation Violation in gm
    (magick/attribute.c:324 in SetImageAttribute)".

  - magick/analyze.c (AllocateDepthMap): Use resource-limited memory
    allocator.

  - magick/operator.c (QuantumDepthCB): Janitorial cleanups.

2023-06-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImage): Validate the number of
    '-random-threshold' arguments.  Addresses SourceForge issue #700
    Segmentation Violation in gm (magick/utility.c:3399 in
    LocaleCompare)".

  - magick/montage.c (MontageImages): Report exception if tile
    geometry component is zero. Addresses SourceForge issue #699
    "Floating Point Exception in gm (magick/montage.c:514 in
    MontageImages)".

2023-05-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/transform.c (ChopImage): Assure that chop image has valid
    dimensions.  Addresses SourceForge issue #697 "Assertion
    'image->columns != 0' failed in gm (RollImage at
    magick/transform.c:1532)" and issue #698 "Assertion 'image->rows
    != 0' failed (magick/transform.c:1533 at RollImage)".

2023-05-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Require that TIFFTAG\_EXTRASAMPLES
    be used appropriately to indicate the intention of extra channels.
    Otherwise extra samples beyond what is required by the photometric
    will be ignored.

2023-05-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Stop promoting RGB image to
    associated alpha due to 4 channels until a solution is found which
    does not cause issues.

2023-05-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Automate the collection of TIFF
    attributes. Fixes oss-fuzz issue 58754
    "graphicsmagick:coder\_BIGTIFF\_fuzzer: Stack-buffer-overflow in
    \_TIFFVGetField" and 58758 "graphicsmagick:coder\_PTIF\_fuzzer:
    Stack-buffer-overflow in \_TIFFVGetField" which occur with the
    development version of libtiff.

2023-05-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (RegisterTIFFImage): Provide a note regarding
    supported compressions for this libtiff build.

  - utilities/tests/gen-tiff-images/genimages: Add support for
    writing uncompressed ("none"), rle, lzw, zip, zstd, and lzma
    compressed variants since these compressors do not have peculiar
    requirements.  With this change 5568 files are generated!

  - coders/png.c (ReadMNGImage): Can not use interpolation for first
    pixel in MNG X\_method 5.  Fixes oss-fuzz issue 31109
    "graphicsmagick:coder\_MNG\_fuzzer: Heap-buffer-overflow in
    ReadMNGImage" and oss-fuzz issue 58381
    "graphicsmagick:coder\_MNG\_fuzzer: Heap-buffer-overflow in
    ReadMNGImage".

2023-05-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Verify that the bits per sample,
    samples per pixel, and photometric are suitable for the claimed
    compressor.

  - coders/bmp.c (ReadBMPImage): Do not decode primaries or gamma
    unless colorspace is LCS\_CALIBRATED\_RGB.

2023-05-13  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/png.c: Expose gama value to the optional log.

2023-05-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - utilities/tests/gen-tiff-images/genimages: Write one-bit grey
    (monochrome) images.  Write miniswhite images.

  - coders/tiff.c (WriteTIFFImage): Support '-define
    tiff:photometric=minisblack' and '-define
    tiff:photometric=miniswhite' to be able to adjust the sense used
    when writing bilevel TIFF images.  Adjust the heuristics used to
    select 'miniswhite' to hopefully preserve the user's intent as
    much as possible, while obeying codec requirements.

2023-05-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/rwfile.tap: Add TopoL to rwfile tests.

2023-05-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/topol.c (RegisterTOPOLImage): Set adjoin to MagickFalse.

2023-05-06  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/topol.c: Fix situation when GetBlobSize returns negative value.

2023-05-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/heif.c (ReadHEIFImage): Implemented Tobias Mark's idea
    for how ignore\_transformations should be supported for older
    libheif versions.

  - coders/topol.c: Eliminate warnings and add some more error
    checks.

2023-05-05  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/topol.c: Fix memory leak.

2023-05-04  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/topol.c: Provide function IsTopoL.

2023-05-03  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/tests/runtest.bat Added checking for TopoL.
  - coders/topol.c: Added extension checking to function.

2023-05-02  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/topol.c: Fix a problem when filename contains garbage only.
    Reported as oss-fuzz-58544.

2023-04-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/heif.c (ReadHEIFImage): Change comments to C99
    syntax. Try to fix compilation with version of libheif prior to
    version 1.9.  Change to use -define heif:ignore-transformations to
    use same naming strategy as the other existing defines.

2023-04-30  Tobias Mark  <tbsmark86@gmail.com>

  - coders/heif.c (ReadHEIFImage): HEIF: Fix reading images with
    rotation/transformation; added option to ignore them. SourceForge
    patch #70 "Fix Heif image with transformations".

  - doc/options.imdoc: Add documentation for -define
    heic:ignore-transformations.

2023-04-30  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/topol.c: Deallocate 'pixels' correctly, fix MEZ reindexing.

2023-04-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/download.rst: More properly describe how to use 'gpg
    --verify'.

2023-04-29  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/topol.c: First attempt to make a writer.
  - magick/blob.h magick/blob.c: New function WriteBlobLSBDouble.

2023-04-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.h (RoundDoubleToQuantumN): New macro to address NaN
    issues when converting a double to a Quantum.  Use it where
    needed.

  - magick/import.c (ImportGrayQuantumType): If value is nan, then
    use 0.0. Addresses SourceForge issue #706 "Integer overflow,
    floating-point exception, pointer overflow in gm".

  - coders/viff.c (ReadVIFFImage): If value is nan, then use 0.0.
    Addresses SourceForge issue #706 "Integer overflow, floating-point
    exception, pointer overflow in gm".

  - coders/mat.c (InsertComplexDoubleRow): If computed f is nan,
    then use 0.0.  Addresses SourceForge issue #708 "Undefined
    behavior while converting negative infinity to integer".
    (InsertComplexFloatRow):  If computed f is nan, then use 0.0.

  - magick/attribute.c (GenerateEXIFAttribute): Assure that float
    and double values are suitably alligned.  Addresses SourceForge
    issue #709 "Undefined behavior while loading a value of type float
    from an unaligned address".

  - coders/tiff.c (ReadTIFFImage): Validate that TIFFGetField() did
    return count and text rather than just relying on its return
    status.  Addresses SourceForge issue #710 "Undefined behavior
    while passing a null pointer as an argument to a nonnull
    function.".

2023-04-26  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/tests/runtest.bat: Added new tests for all possible
    fileformats. XTRNIMAGE causes segfault - this should be fixed.

2023-04-25  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/tests/runtest.bat: Apply only filetests to MPC.

2023-04-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (BatchCommand): Implement simple Test Anything
    Protocol (TAP) test counting and "ok N"/"not ok N" messaging for
    'gm batch' via the '-tap-mode on' option.  This is still a work in
    progress, but is already useful.

2023-04-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - utilities/tests/convert-batch.tap: Added a TAP-like test script
    which is similar to convert.tap, but is not really a TAP test
    yet. This is to explore the concept of using 'gm batch' as part of
    TAP testing.

  - utilities/tests/convert-cmds.txt: Backslash-escape double-quoted
    filename.

2023-04-16 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/CMakeLists.txt: Add posibility to use CMake for
    configure.exe
  - VisualMagick/README.txt: Update description for building
    configure.exe
  - VisualMagick/configure/CStringEx.cpp:
  - VisualMagick/configure/CStringEx.h:
    removed useless code.

2023-04-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/attribute.c (SetImageAttribute): Eliminate memory leak
    when handling attribute with key "EXIF:Orientation".  (SourceForge
    issue #707 "memory leaks in gm").

2023-04-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c (WriteJPEGImage): Do not set image resolution if
    the values provided are outside of the valid range (SourceForge
    issue #706 test case 'bug4').

  - coders/rle.c (ReadRLEImage): Eliminate a unsigned offset
    overflow runtime error from UBSAN (SourceForge issue #706 test
    case 'bug5').

  - coders/png.c (WriteOnePNGImage): Address undefined behavior
    while converting floating point resolution to unsigned integer.
    (SourceForge issue #706 test case 'bug19').

  - magick/utility.c (GetGeometry): Improve geometry parser to
    validate that parsed double values do not underflow or overflow
    when cast to 'unsigned long' or 'long' types. (SourceForge issue
    #706 test case 'bug11').

  - coders/mpc.c (ReadMPCImage): If an attribute appears multiple
    times in the MPC header, only set it once.

  - coders/miff.c (ReadMIFFImage): If an attribute appears multiple
    times in the MIFF header, only set it once.

  - magick/attribute.c (SetImageAttribute): Fix bounds issue when
    concatenating string (SourceForge issue #706 test case 'bug11').

2023-04-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - utilities/tests/gen-tiff-images/genimages: Added a script to
    produce a large number of TIFF files (736 files!) using various
    sample depths and great many other permutations supportable by
    libtiff.  This is both a technology demo of GraphicsMagick (and
    libtiff) as well as a way to generate interesting test inputs for
    other software.  While much of this work existed previously, it is
    included with GraphicsMagick in response to Sebastian Rasmussen's
    post to the GM-help mailing list on March 24 regarding "A set of
    old TIFF sample files..?".

2023-04-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/profile-private.h: Added a new private implementation
    header file.

  - coders/png.c: EXIF header implementation details/refinements.

  - coders/webp.c: Add/remove the internally expected 6-byte JPEG
    APP1 "Exif\0\0" header to/from the pristine Exif blob. Addresses
    SourceForge #696 "WebP Exif handling bug.

2023-03-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jxl.c (ReadJXLImage): Fix JXL EXIF offset handling, and
    deal with any EOI marker. (From SourceForge patch #69 submitted by
    Milos Komarcevic).

  - coders/heif.c (ReadHEIFImage): Fix HEIF EXIF offset handling,
    and deal with any EOI marker.  Also fix HEIF XMP parsing. (From
    SourceForge patch #69 submitted by Milos Komarcevic).

2023-03-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/identity.c (ReadIdentityImage): Return a PseudoClass
    image if possible.

  - coders/miff.c (ReadMIFFImage): With depth == 32, the range of
    image->colors is 1 to 65536.

2023-03-26  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - magick/nt\_base.h: Improve compatibility witholder versions of
    MSVC.

  - VisualMagick/configure/configure.rc Disable checkbox for MSVC6
    format - it is not workable.

2023-03-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/resize.c (ResizeImage): Clarify
    HorizontalFilter()/VerticalFilter() loops.

2023-03-18  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/png.c: There were 2 defects that prevented eXIf chunk to
    be read.

2023-03-18  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/png.c: Variable "png\_byte unused\_chunks" should be const
    and not be placed on a stack.

2023-03-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (ConjureImageCommand): Properly check argument
    list when handling options.  Addresses SourceForge issue #693
    "Segmentation Violation in gm - SetImageAttribute function".
    (MogrifyImage): Improve operator parameter validation.  Addresses
    SourceForge issue #694 "Segmentation Violation in gm (MagickStrToD
    function)".
    (MogrifyImage): Improve ordered-dither parameter
    validation. Addresses SourceForge issue #695 "Segmentation
    Violation in gm (LocaleCompare).

  - magick/error.c (DefaultFatalErrorHandler): Perform printf
    substitutions similar to DefaultErrorHandler.

  - magick/error.h: Add parameter names to prototypes.

  - magick/command.c (CompositeImageCommand): Properly deal with
    -noop when the user has not provided any images.  Addresses
    SourceForge issue #691 "Segmentation Violation in gm
    (magick/command.c:3054)".
    (MogrifyImageCommand): Properly check argument list when
    validating "resample".  Addresses SourceForge issue #692
    "Segmentation Violation in gm (GetGeometry function)".

2023-03-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c: Make "operator" parameter checking more
    robust. Addresses SourceForge issue #690 "Segmentation Violations
    in gm (magick/utility.c:3397)".

  - coders/msl.c (ProcessMSLScript): Fix use of memory just freed.
    Addresses SourceForge issue #689 "Heap UAF in gm
    (magick/utility.c:3792)"

  - coders/identity.c (ReadIdentityImage): Limit 'order' to a
    maximum of 40, and change to unsigned type in order to avoid
    undefined arithmetic overflow.

  - magick/command.c (MogrifyImage): Handle the case where image and
    region\_image are the same.  Addresses SourceForge issue #688 "Heap
    UAF in gm (magick/command.c:11427)".

  - coders/pict.c (WritePICTImage): Fix use of
    MagickFreeResourceLimitedMemory() on non-managed memory. Addresses
    SourceForge issue #687 "Heap Overflow in gm
    (magick/memory.c:728)".

  - magick/command.c (MogrifyImage): Validate that -lat argument is
    correctly formed, and that width and height are not zero.

  - magick/effect.c (AdaptiveThresholdImage): Validate that width
    and height are not zero.  Addresses SourceForge issue #686
    "Floating Point Exception in gm (magick/effect.c:379)".

  - magick/command.c (MogrifyImage): Report a draw argument error if
    drawing primitive is NULL.  Addresses SourceForge issue #684
    "Assertion bug in gm (magick/render.c:2715)"
    (MogrifyImage): Validate colorspace argument.  Addresses
    SourceForge issue #685 Assertion bug in gm
    (magick/colorspace.c:1045)".

  - magick/utility.c (TranslateTextEx): An empty string argument
    should return an empty string rather than a NULL string.

2023-02-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Makefile.am: Stop producing BZip, Gzip, Lzip, and Zstandard
    compressed archives so the only tar option is XZ compressed.  See
    if anyone complains.

  - www/download.rst: Add summary documentation regarding archive formats.

2023-02-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c (ReadJPEGImage): Replace
    MagickAllocateResourceLimitedArray() with
    MagickAllocateResourceLimitedClearedArray() and eliminate explicit
    memset().

2023-02-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c (ImageToBlob): Immediately reject attempts to
    write blobs to formats which can not support blobs.

2023-02-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/mpc.c (RegisterMPCImage): Set seekable\_stream and
    blob\_support to false.

2023-02-05  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/configure/configure.rc: Changed "Configure.EXE" to "configure.exe"
  - VisualMagick/configure/configure.exe:
    Configure.exe has been blacklisted with 6 antiviruses.
    https://www.virustotal.com/gui/file/3a0e54c8439200faf666b5680e0608e93fd67b5cda0d72dc32f54f0308574aba

2023-02-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Test for interesting libjpeg-turbo 3.0 functions
    (which may also appear in other JPEG libraries).

  - coders/jpeg.c: Block out existing code for C\_LOSSLESS\_SUPPORTED
    and D\_LOSSLESS\_SUPPORTED when compiling with JPEG-Turbo 3.0 since
    it is not compatible with it.

  - coders/wpg.c (ApproveFormatForWPG): Pass in existing
    ExceptionInfo pointer.

2023-01-31  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c: Do not approve any format from "META" module
    for embedding.

2023-01-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/wpg.c (WriteWPGImage): image->colors is only valid for
    storage\_class == PseudoClass.

2023-01-25  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c: Format "8BIMTEXT" cannot be embedded inside WPG.

2023-01-24  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/tests/runtest.bat: Add missing tests of fileformats.

2023-01-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/rwblob.tap: Add sanity test for WPG format.

  - tests/rwfile.tap: Add sanity test for WPG format.

  - coders/wpg.c: Change line terminations back to ISO standard
    format.

  - (RegisterWPGImage): WPG currently only supports one frame.

  - Makefile.am: No longer produce ".sig" files since the ".asc"
    files can do everything that the ".sig" files can do.

2023-01-15  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/tests/runtest.bat

  - coders/wpg.c: Added WPG writer ... cross your fingers.

2023-01-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/MANIFEST: Update PerlMagick manifest.

  - version.sh: Updated for 1.3.40 release.

  - NEWS.txt: Updated the news.

2023-01-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jxl.c (ReadJXLImage): Cache and trace extra channel info.

2023-01-11  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c: Fixed Monochromatic bilevel WPG should answer to
    gm identify file.wpg ..... PseudoClass 2c 8-bit

2023-01-08  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c: Fixed deffect in WPG header reading.

2023-01-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (WriteOnePNGImage): Use lower-case raw profile
    identifiers (e.g. 'Raw profile type xmp') because exiftool expects
    that.  Partially addresses concerns raised by SourceForge bug #682
    "Invalid storage of XMP in PNGs".

  - www/INSTALL-unix.rst: Add notes about required libjxl versions.

  - README.txt: Add notes about required libjxl versions.

2023-01-08 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/tests/runtest.bat: Added new tests for WEBP, BMP2 & BMP3.
    These tests are passing.

2023-01-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Updated the news.

  - It is 2023 now!  Update copyrights, rotate changelogs, etc.

  - magick/blob.c (OpenBlob): Zlib has never supported opening Unix
    'compress' .Z files (although gzip does).  So don't open such
    files using zlib.

  - coders/sun.c: Add IM1, IM8, and IM24 magick aliases for Sun
    Raster format since those are the historically correct extensions.

2023-01-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/sun.c (ReadSUNImage): Address oss-fuzz 54810
    "graphicsmagick:coder\_SUN\_fuzzer: Heap-buffer-overflow in
    ReadSUNImage".

  - coders/pict.c (WritePICTImage): Fix use of logical operator
    where binary operator is needed.

2023-01-05 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/installer/inc/body.isx: 64 bit distribution MUST NOT
    be installed on pure 32 bit system. Sanity check added.

2023-01-05 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/installer/inc/body.isx:
  - VisualMagick/installer/inc/files-dlls.isx:
    (VisualMagick/installer/redist/VC2008SP1/vcredist\_x64.exe must be downloaded from www).
    (VisualMagick/installer/redist/VC2008SP1/vcredist\_x86.exe must be downloaded from www).
    Fix graphics magick installer for Windows.

2023-01-04 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/tests/runtest.bat: Added new tests for PGX (jp2),
    MAT, uncommented test for EPDF and PICON.

2023-01-03 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/jp2/src/appl/UTILITY.txt: removed fuzz.c.

2023-01-03 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/jp2/src/libjasper/pgx/LIBRARY.txt,
    jp2/src/libjasper/include/jasper/jas\_config.h: PGX codec was not
    compiled into gm, now added.

2023-01-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pict.c: Add more tracing.

2023-01-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pcd.c (WritePCDTile): Handle writing image with a
    dimension of 1.

2023-01-02 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - jp2/\*: Update lib jasper to 2.0.33. Code cleanly compilles, but
    there is still some problem. Will be solved later.
  - jp2/src/lib/jasper/include/jasper/stdbool2.h: No longer needed.

2023-01-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/utility.c (GetMagickGeometry): Assure that width and
    height are not scaled down to zero since it is an invalid value.

  - coders/sun.c (ReadSUNImage): Enlarge RLE output buffer in order
    to avoid buffer overflow.  Addresses oss-fuzz 54716
    "graphicsmagick:coder\_RAS\_fuzzer: Heap-buffer-overflow in
    ReadSUNImage", which is due to a new problem added since the
    1.3.39 release.

2023-01-01 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - jp2/\*: Update lib jasper to 2.0.0.
