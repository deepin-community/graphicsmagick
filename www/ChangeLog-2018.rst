2018-12-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c (ReadJPEGImage): Move return point for 'ping' mode
    until after jpeg\_start\_decompress() and after JPEG compression
    properties have been estimated.  Fixes SourceForge issue #578 "gm
    identify with format "%[JPEG-Colorspace-Name]" does not work" and
    #586 "Identify returning wrong compression values".

2018-12-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/gif.c (ReadGIFImage): Don't throw an error if opacity is
    outside of the range of the image colors.  Fix suggested by 莫红波
    <hongbo.mo@upai.com> on the graphicsmagick-bugs mailinb list on
    Fri, 9 Oct 2015.

  - magick/memory.h (MagickAllocateClearedArray): New macro for
    allocating a cleared array.

  - magick/resize.c (ScaleImage): Patch by Troy Patteson which
    resolves SourceForge issue #381 "Artifacts when scaling a PNG with
    semi-transparent pixels".

    ScaleImage() suffers from two problems related to the blending of
    fully transparent pixels with non-fully transparent pixels during
    the scaling operation.

    The first is that the colour values for fully transparent pixels
    are contributing to the colour values of the blended pixels when
    they should not.

    The second is that the colour values of pixels blended with fully
    and non-fully transparent pixels are scaled as though the fully
    transparent pixels contribute to the blended pixels' colour values
    when they should not. For example, if blending 10% of a fully
    opaque white pixel with 90% of a fully transparent black pixel one
    would expect the blended pixel RGBA values to be 255,255,255,25.5
    assuming 8 bit colour but they are in fact 25.5,25.5,25.5,25.5.

    The provided patch solves the first issue by treating the colour
    values of fully transparent pixels as zero and the second issue by
    recording the volume of each blended pixel made up of pxiels that
    are not fully transparent (0.1 in the above example) and then
    scaling the blended pixel RGB values by dividing by that
    amount. In the above example, 25.5/0.1 = 255.

2018-12-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dib.c (ReadDIBImage): DIB images claiming more than
    8-bits per pixel are not colormapped.  Reject such files.  Fixes
    SourceForge issue #585 "Assertion Failure in coders/png.c:7503".
    The problem is in the DIB reader rather than PNG.

  - coders/miff.c (ReadMIFFImage): Detect and reject zero-length
    deflate-encoded row in MIFF version 0.  Fixes oss-fuzz 11876
    "graphicsmagick/coder\_MIFF\_fuzzer: Use-of-uninitialized-value in
    deflate\_slow". (Credit to OSS-Fuzz)

  - configure.ac: Improve search for true Microsoft Windows fonts
    and provide better indication of results.  Fix a typo which caused
    DcrawExtraOptions not to be evaluated correctly.

2018-12-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (QuantumTransferMode): Be more strict about the
    requirements for CIE Log2(L) and LOGLUV images.
    (ReadTIFFImage): Apply memory resource limits to strip and tile
    allocations.
    (ReadTIFFImage): Rationalize tile width/height to reject large
    tile sizes which are much larger than the image dimensions.  Fixes
    oss-fuzz 11824 "graphicsmagick/coder\_BIGTIFF\_fuzzer: Out-of-memory
    in graphicsmagick\_coder\_BIGTIFF\_fuzzer". (Credit to OSS-Fuzz)
    (ReadTIFFImage): Return with error if TIFFClientOpen() reports
    errors yet still returns a TIFF handle.

2018-12-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tga.c (WriteTGAImage): Image rows/columns must not be
    larger than 65535. Fixes SourceForge #583 "heap-buffer-overflow in
    WriteTGAImage of tga.c".

2018-12-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/bmp.c (ReadBMPImage): Fix heap overflow in 32-bit build
    due to arithmetic overflow.  Only happens if limits are changed
    from defaults. Fixes SourceForge #582 "heap-buffer-overflow in
    ReadBMPImage of bmp.c".

2018-12-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - common.shi.in (MAGICK\_FONT): The test suite must pass even on
    systems where we don't find any fonts.

2018-12-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/miff.c (ReadMIFFImage): Sanitize claimed profile size
    before allocating memory for it.  Fixes oss-fuzz 11781
    "graphicsmagick/coder\_MIFF\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_MIFF\_fuzzer". (Credit to OSS-Fuzz)

2018-12-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (ReadMNGImage): Fix non-terminal MNG looping.
    Fixes oss-fuzz 11596 "graphicsmagick/coder\_MNG\_fuzzer: Timeout in
    graphicsmagick\_coder\_MNG\_fuzzer". (Credit to OSS-Fuzz)

2018-12-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/xpm.c (WriteXPMImage): Assure that added colormap entry
    for transparent XPM is initialized. Fixes oss-fuzz 11617
    "graphicsmagick/coder\_XPM\_fuzzer: Use-of-uninitialized-value in
    QueryColorname". (Credit to OSS-Fuzz)

  - coders/miff.c (ReadMIFFImage): Fix memory leak of profiles
    'name' when claimed length is zero.  Fixes oss-fuzz 11710
    "graphicsmagick/coder\_MIFF\_fuzzer: Direct-leak in AllocateString".
    and oss-fuzz 11688 "graphicsmagick/coder\_MIFF\_fuzzer:
    Out-of-memory in graphicsmagick\_coder\_MIFF\_fuzzer". (Credit to
    OSS-Fuzz)

2018-12-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Apply patch from Alex Gaynor to add
    Zstd to the oss-fuzz build.

2018-12-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac (DcrawExtraOptions): For QuantumDepth > 8 pass -6
    option to dcraw.  Fixes SourceForge issue #568 "dcraw not
    returning 16 bit image even though quantum depth is set to 16".

  - fuzzing/oss-fuzz-build.sh (PKG\_CONFIG\_PATH): Build WebP prior to
    libtiff so that libtiff has a chance to find it.

2018-11-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (TimeImageCommand): Time command now shows 6
    digits of elapsed time indication since this precision is often
    now available and it is useful to see.

2018-11-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Magick++/lib/Magick++/Drawable.h: Fix use of clang diagnostic
    syntax. Addresses SourceForge bug #579 "'diagnostic pop' pragma
    without 'diagnostic push' in Drawable.h.".

2018-11-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/constitute.c (WriteImage): Eliminate use of just-freed
    memory in clone\_info->magick when throwing exception due to no
    support for format.  Fixes SourceForge issue #576 "heap
    use-after-freee when convert one format into another format".

  - magick/command.c (BenchmarkImageCommand): Benchmark command now
    shows 6 digits of elapsed time indication since this precision is
    often now available and it is useful to see.

2018-11-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/wand\_api.h ("C"): magick/api.h should be included prior to
    wand/wand\_symbols.h.  Change made due to report by yzh杨振宏 on
    Wed, 21 Nov 2018 via the graphicsmagick-bugs mailing list.

2018-11-20  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - magick/nt\_base.c Fix a bug when OS does not support performance counter.

2018-11-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/nt\_base.c (NTElapsedTime): Use
    QueryPerformanceFrequency() and QueryPerformanceCounter() to
    measure elapsed time for Windows.

2018-11-19  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - tiff/port/snprintf.c Fix for older Microsoft Visual Studio

2018-11-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/index.rst: Update in preparation for 1.3.31 release.

  - version.sh: Update library versioning in preparation for
    1.3.31 release.

  - NEWS.txt: Update news in preparation for 1.3.31 release.

2018-11-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (BenchmarkUsage): Document the benchmark
    command better.

2018-11-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/resize.c (HorizontalFilter, VerticalFilter): quantum is a
    pointer so it's value can not be usefully flushed.  Use a local
    variable and then update quantum pointer when done.

2018-11-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/\*: Changed row\_count tallying to use 'omp atomic' and
    status update to use 'omp flush' for progress and error
    indication.  This replaces most use of 'omp critical' for this
    purpose.  Changed some lumpy algorithms which were using 'static'
    scheduling to 'guided' scheduling due to observing better results.
    Also added prolific 'restrict' annotations where they were
    missing.

  - www/security.rst: Documented a PGP private key for file signing
    or private correspondence.

2018-11-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/authors.rst: Moved "Glenn Randers-Pehrson" and "Gregory J
    Wolfe" to the "Former Contributor" category.

2018-11-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Added many GCC function annotations in the libraries and coders.

2018-11-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Use printf rather than echo to portably expand tab
    requests in configuration summary.

2018-11-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Use pkg-config data as the initial choice when
    configuring for FreeType 2.0 and libxml-2.0.  Only fall back to
    invoking an external script (and then traditional methods) if
    pkg-config fails.

  - coders/msl.c (ProcessMSLScript): Release msl\_image if OpenBlob
    fails.  Similar to ImageMagick CVE-2018-18544.  Problem was
    reported to us via email from Petr Gajdos on Thu, 1 Nov 2018.

2018-10-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/miff.c (WriteMIFFImage): Only run
    strlen(attribute->value) once per attribute since the length won't
    change.  May address oss-fuzz 11158
    "graphicsmagick/coder\_MIFF\_fuzzer: Timeout in
    graphicsmagick\_coder\_MIFF\_fuzzer". (Credit to OSS-Fuzz)

  - Fix compilation warnings observed with GCC 8.2.0.

2018-10-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_iterator.c (PixelIterateMonoModifyImplementation):
    Use atomic and flush rather than critical construct for a small
    speedup.

  - magick/monitor.c (MagickMonitorFormatted): Serialize calls to
    the progress monitor so that the caller does not need to perform
    this serialization.
    (MagickMonitor): Serialize calls to the progress monitor so that
    the caller does not need to perform this serialization.  This
    function is now marked as deprecated.
    (InitializeMagickMonitor): New private function to initialize
    monitor functionality.
    (DestroyMagickMonitor): New private function to destroy monitor
    functionality.

2018-10-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/gif.c (ReadGIFImage): Improve the efficiency of storing a
    GIF comment in order to avoid a DOS opportunity.  Fixes oss-fuzz
    11096 "graphicsmagick/coder\_GIF\_fuzzer: Timeout in
    graphicsmagick\_coder\_GIF\_fuzzer". (Credit to OSS-Fuzz)

2018-10-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/Makefile.PL.in: Use MAGICK\_API\_LIBS to obtain the
    list of libraries to use when linking.

  - configure.ac: OpenMP library is normally supplied due to a
    CFLAGS option so only supply it in cases where the CFLAGS option
    may be lost or it might not be used.  Otherwise the compiler may
    apply the library twice when linking.

2018-10-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Remove Ghostscript library support (--with-gslib)
    from configure script.  The 'HasGS' pre-processor defines which
    were enabled by this remain in the source code so it is still
    possible to use this library if absolutely necessary
    (e.g. CPPFLAGS=-DHasGS LIBS=-lgs).

  - tests/rwfile.tap: Test TIFF format with all supported
    compression options.

  - tests/{rwblob.c, rwfile.c} (main): Use StringToCompressionType()
    to parse compression option. Also consider requested compression
    algorithm when deciding if format is lossy.

  - coders/tiff.c (WriteTIFFImage): WebP compression needs
    PHOTOMETRIC\_RGB. Fix wrong rows-per-strip calculation when using
    LZMA compression.

  - tests/rwblob.tap: Added a rwblob test to verify that lower-case
    magick works.

  - magick/static.c (OpenModule): Upper case magick string before
    searching static modules list.  Fixes Debian bug 911386
    "libgraphicsmagick-q16-3: graphicsmagick 1.3.30 has made formats
    case-sensitive at the API level".

  - filters/analyze.c (AnalyzeImage): X and y should be unsigned
    long to match image rows/columns type.  Calculate total pixels by
    simple multiplication rather than counting.

2018-10-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): Support WebP compression in
    TIFF. This requires a libtiff release after 4.0.9.

  - magick/image.h ("C"): WebPCompression added to CompressionType
    enumeration.

2018-10-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Configure for the Zstd library.  Use
    --without-zstd to disable searching for this library.  Libtiff may
    require this library to successfully link so static linkage could
    fail if searching for libzstd is disabled.

  - magick/image.h ("C"): ZSTDCompression added to CompressionType
    enumeration.

  - coders/tiff.c (WriteTIFFImage): Support Zstd compression in
    TIFF.  This requires a libtiff release after 4.0.9.

2018-10-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (GMCommandSingle): Add 'compare' to the list of
    command names that gm will support as a command if copied to or
    linked from that name.  There was already a 'compare' link
    installed when the '--enable-magick-compat' configure option is
    used, but it could not possibly function without being blessed by
    this list.  Related to Debian bug #910652
    "graphicsmagick-imagemagick-compat: Doesn't ship a compare tool".

2018-09-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Magick++/lib/Magick++/Drawable.h: Block unused-private-field
    warnings from Clang due to \_dummy members which were intentionally
    included in some parent class definitions.

  - magick/widget.c (XEditText): Fix compilation warnings about
    cases which fall-through.

  - magick/display.c (MagickXAnnotateEditImage): Fix compilation
    warnings about cases which fall-through.

  - coders/pict.c (WritePICTImage): Add more checks to memory
    allocation calculations.

  - magick/pixel\_cache.c (DestroyCacheInfo): Eliminate intentional
    fall-through logic in switch statement which results in compiler
    warnings.  Eliminate switch statements entirely and split
    unrelated logic.

  - coders/txt.c (ReadTXTImage): Fix comparison between pointer and
    '\0' rather than NULL as was obviously intended.

  - coders/msl.c (MSLStartElement): Add missing 'break' statements
    after ThrowException() calls.  Otherwise execution falls through
    into unrelated switch cases and throws a redundant exception.

2018-09-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/meta.c (parse8BIM): Eliminate repeated use of strlen()
    which scans the entire remaining string on each cycle.  Fixes
    oss-fuzz 10667 "graphicsmagick/coder\_IPTCTEXT\_fuzzer: Timeout in
    graphicsmagick\_coder\_IPTCTEXT\_fuzzer". (Credit to OSS-Fuzz)

2018-09-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/utility.c (MagickGetToken): Fix possible read up to four
    bytes beyond end of stack allocated token buffer.  Fixes oss-fuzz
    10653 "graphicsmagick/coder\_MVG\_fuzzer: Stack-buffer-overflow in
    MagickGetToken". (Credit to OSS-Fuzz)

2018-09-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/coder\_fuzzer.cc (LLVMFuzzerTestOneInput): Limit the
    maximum number of JPEG progressive scans to 50.

  - coders/jpeg.c (ReadJPEGImage): Apply a default limit of 100
    progressive scans before the reader quits with an error.  This
    limit may be adjusted using the -define mechanism like -define
    JPEG:max-scan-number=500.  Also respond more quickly to files
    which exceed the maximum image dimensions.  Fixes oss-fuzz 10258
    "graphicsmagick/coder\_JPEG\_fuzzer: Timeout in
    graphicsmagick\_coder\_JPEG\_fuzzer". (Credit to OSS-Fuzz)

2018-09-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (ReadMNGImage): mng\_LOOP chunk must be at least 5
    bytes long.  Fixes oss-fuzz 10455
    "graphicsmagick/coder\_MNG\_fuzzer: Use-of-uninitialized-value in
    ReadMNGImage". (Credit to OSS-Fuzz)

2018-09-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (TraceEllipse): Detect arithmetic overflow when
    computing the number of points to allocate for an ellipse.  Fixes
    oss-fuzz 10306 "graphicsmagick/coder\_MVG\_fuzzer:
    Heap-buffer-overflow in TracePoint". (Credit to OSS-Fuzz)

2018-09-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/attribute.c (GenerateEXIFAttribute): Eliminate undefined
    shift.  Also right-sized involved data types.  Fixes oss-fuzz
    10309 "graphicsmagick/coder\_JPG\_fuzzer: Undefined-shift in
    Read32s". (Credit to OSS-Fuzz)

2018-09-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (DrawClipPath): Fix Coverity 319663 "Null
    pointer dereferences".  Totally insignificant.

  - coders/wpg.c (ReadWPGImage): Mask/fix Coverity 319664 "Error
    handling issues".

  - magick/attribute.c (FindEXIFAttribute): Change size types from
    signed to unsigned and check for unsigned overflow.
    (GenerateEXIFAttribute): Change size types from signed to unsigned
    and check for unsigned overflow. Fixes oss-fuzz 10283
    "graphicsmagick/coder\_JPG\_fuzzer: Integer-overflow in
    GenerateEXIFAttribute". (Credit to OSS-Fuzz)

  - coders/sfw.c (ReadSFWImage): Enforce that file is read using the
    JPEG reader. (Credit to OSS-Fuzz)

  - coders/miff.c (ReadMIFFImage): Fix leak of 'values' buffer due
    to change made yesterday.

  - coders/mpc.c (ReadMPCImage): Fix leak of 'values' buffer due to
    change made yesterday.  Fixes oss-fuzz 10277
    "graphicsmagick/coder\_MPC\_fuzzer: Direct-leak in
    ReadMPCImage". (Credit to OSS-Fuzz)

2018-09-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/miff.c (ReadMIFFImage): Support legacy keyword
    'color-profile' for ICC color profile as was used by ImageMagick
    4.2.9.

  - coders/mpc.c (ReadMPCImage): Require that first keyword/value be
    id=MagickCache

  - coders/miff.c (ReadMIFFImage): Require that first keyword/value
    be id=ImageMagick.

2018-09-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dcm.c (DCM\_ReadElement): Add more size checks.

  - coders/jnx.c (ExtractTileJPG): Enforce that JPEG tiles are read
    by the JPEG coder.  Fixes oss-fuzz 10147
    "graphicsmagick/coder\_JNX\_fuzzer: Use-of-uninitialized-value in
    funcDCM\_PhotometricInterpretation". (Credit to OSS-Fuzz)

2018-09-10  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/wpg.c Zero fill raster error recovery.

2018-08-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (ConvertPrimitiveToPath): Second attempt to
    prevent heap write overflow of PathInfo array.  Fixes oss-fuzz
    10096 "Heap-buffer-overflow in ConvertPrimitiveToPath". (Credit to
    OSS-Fuzz)

2018-08-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c ("QuantumTransferMode"): CIE Log images with an
    alpha channel are not supported.  Fixes oss-fuzz 10013
    "graphicsmagick/coder\_TIFF\_fuzzer: Use-of-uninitialized-value in
    DisassociateAlphaRegion". (Credit to OSS-Fuzz)

  - magick/render.c (DrawImage): SetImageAttribute() appends new
    text to any existing value, leading to every increasing memory
    consumption if the existing value is not deleted first by the
    unwary.  Fixes oss-fuzz 9983 "graphicsmagick/coder\_MVG\_fuzzer:
    Timeout in graphicsmagick\_coder\_MVG\_fuzzer" and oss-fuzz 10016
    "graphicsmagick/coder\_MVG\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_MVG\_fuzzer". (Credit to OSS-Fuzz)

  - magick/utility.c (TranslateTextEx): Fix off-by-one in loop
    bounds check which allowed a one-byte stack write overflow.  Fixes
    oss-fuzz 10055 "graphicsmagick/coder\_MVG\_fuzzer:
    Stack-buffer-overflow in TranslateTextEx". (Credit to OSS-Fuzz)

  - magick/render.c (DrawImage): Be more precise about error
    detection and reporting, and return from an error more quickly.
    Also added MAX\_DRAWIMAGE\_RECURSION pre-processor definition to
    allow adjusting the drawing recursion limit.  The drawing
    recursion limit is still 100, which seems exceptionally generous.

  - magick/constitute.c (WriteImage): Produce a more useful error
    message if an encoding delegate is not available.

  - magick/nt\_base.h (isnan): Try adding a MSVC replacement for
    missing isnan() function.  Not yet tested.

2018-08-25  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/wpg.c This should fix intentional 64 bit file offset
    overflow as depictedin OSS-fuzz-9936. Thanks to OSS-Fuzz.

2018-08-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (ConvertPrimitiveToPath): Need to enlarge
    PathInfo array allocation to avoid possible heap write overflow.
    Fixes oss-fuzz 9651 "graphicsmagick/coder\_MVG\_fuzzer:
    Heap-buffer-overflow in ConvertPrimitiveToPath". (Credit to
    OSS-Fuzz)

2018-08-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/mpc.c (ReadMPCImage): Insist that the format be
    identified prior to any comment, and that there is only one
    comment.

  - coders/miff.c (ReadMIFFImage): Insist that the format be
    identified prior to any comment, and that there is only one
    comment.  Fixes oss-fuzz 9979 "graphicsmagick/coder\_MIFF\_fuzzer:
    Timeout in graphicsmagick\_coder\_MIFF\_fuzzer".  This is not a
    serious issue, but the code runs slowly under UBSAN.  (Credit to
    OSS-Fuzz)

2018-08-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/utility.c (MagickAtoFChk): Add additional validation
    checks for floating point values.  NAN and +/- INFINITY values
    also map to 0.0. Fixes oss-fuzz 9630
    "graphicsmagick/coder\_MVG\_fuzzer: Integer-overflow in
    IsNexusInCore" and oss-fuzz 9612 "graphicsmagick/coder\_MVG\_fuzzer:
    Integer-overflow in SetCacheNexus". (Credit to OSS-Fuzz)

  - magick/render.c (DrawImage): Add missing error-reporting logic
    to return immediately upon memory reallocation failure.  Apply
    memory resource limits to PrimitiveInfo array allocation.  Fixes
    oss-fuzz 9576 "graphicsmagick/coder\_MVG\_fuzzer: Null-dereference
    READ in DrawImage", oss-fuzz 9593
    "graphicsmagick/coder\_MVG\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_MVG\_fuzzer", oss-fuzz 9648
    "graphicsmagick/coder\_MVG\_fuzzer: Unknown signal in
    DrawImage". (Credit to OSS-Fuzz)

2018-08-16  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coder/mat.c Explicitly reject non-seekable streams.

2018-08-15  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coder/mat.c Correctly check GetBlobSize(image) even for zipstreams.

2018-08-14  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c More aggresive data corruption checking.

2018-08-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/xbm.c (XBMInteger): Limit the number of hex digits parsed
    to avoid signed integer overflow.  Fixes oss-fuzz 9746
    "graphicsmagick/coder\_XBM\_fuzzer: Undefined-shift in
    XBMInteger". (Credit to OSS-Fuzz)

2018-08-07  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c Typecast difference to quantum.

2018-08-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/mat.c (InsertComplexFloatRow): Avoid signed
    overflow. Fixes oss-fuzz 9667 "graphicsmagick/coder\_MAT\_fuzzer:
    Integer-overflow in InsertComplexFloatRow". (Credit to OSS-Fuzz)

  - coders/xbm.c (ReadXBMImage): Add validations for row and column
    dimensions.  Fixes oss-fuzz 9736 "graphicsmagick/coder\_XBM\_fuzzer:
    Out-of-memory in graphicsmagick\_coder\_XBM\_fuzzer". (Credit to
    OSS-Fuzz)

2018-08-04  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/wpg.c Add mechanism to approve embedded subformats in
    WPG.  This should mute oss-fuzz 9559.  (Credit to OSS-Fuzz)

2018-07-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/mvg.c (ReadMVGImage): Fix memory leak added on
    2018-07-21.  Fixes oss-fuzz 9548 "graphicsmagick/coder\_MVG\_fuzzer:
    Direct-leak in CloneDrawInfo". (Credit to OSS-Fuzz)

2018-07-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/cineon.c (ReadCINEONImage): Fix SourceForge issue 571
    "Unexpected hang on a crafted Cineon image" by detecting and
    quitting on EOF appropriately, and verifying that file size is
    sufficient for claimed pixel dimensions when possible.

  - fuzzing/oss-fuzz-build.sh, fuzzing/dictionaries/MVG.dict: Added
    MVG fuzzing dictionary by Alex Gaynor.

2018-07-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.c (SetNexus): For requests one pixel tall,
    SetNexus() was wrongly using pixels in-core rather than using a
    staging area for the case where the nexus rows extend beyond the
    image raster boundary, leading to heap overflow.  This can happen
    when virtual pixels outside the image bounds are accessed.  Fixes
    oss-fuzz 9512 "graphicsmagick/graphicsmagick\_coder\_MVG\_fuzzer:
    Heap-buffer-overflow in AcquireCacheNexus". (Credit to OSS-Fuzz)

  - magick/render.c (ExtractTokensBetweenPushPop):
    ExtractTokensBetweenPushPop() needs to always return a valid
    pointer into the primitive string.  Fixes oss-fuzz 9511
    "graphicsmagick/graphicsmagick\_coder\_MVG\_fuzzer: Null-dereference
    READ in DrawImage". (Credit to OSS-Fuzz)
    (DrawPolygonPrimitive): Fix leak of polygon set when object is
    completely outside image.  Fixes oss-fuzz 9513
    "graphicsmagick/graphicsmagick\_coder\_MVG\_fuzzer: Direct-leak in
    AllocateThreadViewDataSet". (Credit to OSS-Fuzz)

2018-07-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c (FileToBlob): Use confirm access APIs to verify
    that read access to this path is allowed by policy.  Check that
    file is a regular file before proceeding to open and read from it.

  - coders/mvg.c (ReadMVGImage): Don't allow MVG files to side-load
    a file as the drawing primitive using '@' syntax.  Fixes oss-fuzz
    9494 "graphicsmagick/coder\_MVG\_fuzzer: Sanitizer CHECK failure in
    "((0)) != (0)" (0x0, 0x0)". (Credit to OSS-Fuzz)

2018-07-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/mvg.c (ReadMVGImage): Don't assume that in-memory MVG
    blob is a null-terminated C string. Fixes oss-fuzz 9469
    "graphicsmagick/coder\_MVG\_fuzzer: Heap-buffer-overflow in
    AllocateString". (Credit to OSS-Fuzz)

2018-07-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/miff.c (ReadMIFFImage): Detect EOF when reading using
    ReadBlobZC() and avoid subsequent heap read overflow.  Fixes
    oss-fuzz 9357 "graphicsmagick/coder\_MIFF\_fuzzer:
    Heap-buffer-overflow in ImportRGBQuantumType". (Credit to
    OSS-Fuzz)

2018-07-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh (CFLAGS): Try disabling SIMD
    instructions in libjpeg-turbo build.

2018-07-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (WriteOnePNGImage): Free png\_pixels as soon as
    possible.  This might help with oss-fuzz 9334
    "graphicsmagick/coder\_PNG8\_fuzzer: Direct-leak in
    WriteOnePNGImage", which we have yet to reproduce.  It is not
    clear if png\_pixels is being clobbered by longjmp or if something
    else is going on.

2018-06-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c (ReadJPEGImage): Provide a memory resource limit
    (of 1/5th the memory resource limit for Graphicsmagick) to libjpeg
    to limit how much memory it might consume for itself while reading
    a file.  Fixes oss-fuzz 9096 "graphicsmagick/coder\_JPEG\_fuzzer:
    Timeout in graphicsmagick\_coder\_JPEG\_fuzzer".  (Credit to
    OSS-Fuzz)
    (ReadJPEGImage): Make sure that JPEG pixels array is initialized
    in case libjpeg fails to completely initialize it.  May fix
    oss-fuzz 9115 "graphicsmagick/coder\_JPEG\_fuzzer:
    Use-of-uninitialized-value in ReadJPEGImage".  We are not sure
    since the problem was not reproduced.  (Credit to OSS-Fuzz)

2018-06-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - version.sh: Update library versioning for 1.3.30 release.

  - NEWS.txt: Update news for 1.3.30 release.

2018-06-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (ReadDPXImage): Report exception on EOF file
    reading DPX pixel data. Fixes oss-fuzz 8104
    "graphicsmagick/coder\_DPX\_fuzzer: Use-of-uninitialized-value in
    WriteDPXImage", oss-fuzz 8297 "graphicsmagick/enhance\_fuzzer:
    Use-of-uninitialized-value in EnhanceImage", and oss-fuzz 8133
    "graphicsmagick/coder\_DPX\_fuzzer: Use-of-uninitialized-value in
    RGBTransformPackets". (Credit to OSS-Fuzz)

2018-06-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/cmyk.c (ReadCMYKImage): Free scanline buffer in error
    path. Fixes SourceForge issue #567 "small memory leak in rgb.c,
    gray.c and cmyk.c" reported by Petr Gajdos.

  - coders/gray.c (ReadGRAYImage): Free scanline buffer in error
    path. Fixes SourceForge issue #567 "small memory leak in rgb.c,
    gray.c and cmyk.c" reported by Petr Gajdos.

  - coders/rgb.c (ReadRGBImage): Free scanline buffer in error
    path. Fixes SourceForge issue #567 "small memory leak in rgb.c,
    gray.c and cmyk.c" reported by Petr Gajdos.

  - coders/jpeg.c (ReadJPEGImage): Avoid memory leak of profile
    buffer when longjmp-based exception is thrown while reading a
    profile. Fixes oss-fuzz 8957 "graphicsmagick/enhance\_fuzzer:
    Direct-leak in ReadGenericProfile". (Credit to OSS-Fuzz)

2018-06-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/xcf.c (load\_level): Make sure to free 'tile\_image' before
    returning exception.  Fixes oss-fuzz 8935
    "graphicsmagick/coder\_XCF\_fuzzer: Indirect-leak in
    CloneImage". (Credit to OSS-Fuzz)

  - coders/jpeg.c (ReadJPEGImage): Allow three warnings of any given
    type before promoting the next warning of the same type to a hard
    error.  The warning limit may be adjusted by the user using
    -define jpeg:max-warnings=<value>.  Fixes oss-fuzz 8704
    "graphicsmagick/coder\_JPG\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_JPG\_fuzzer". (Credit to OSS-Fuzz)

  - coders/png.c (ReadPNGImage): Detect EOF when reading
    magic\_number.  Fixes oss-fuzz 8944
    "graphicsmagick/coder\_PNG\_fuzzer: Use-of-uninitialized-value in
    ReadPNGImage".  (Credit to OSS-Fuzz)
    (ReadPNGImage, ReadJNGImage): Makes sure that return value of
    ReadBlob() is always checked to detect EOF.

2018-06-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Re-structure exception reporting
    so that QuantumTransferMode() exceptions thrown for
    PLANARCONFIG\_SEPARATE images are handled immediately.  Fixes
    oss-fuzz 8896 "graphicsmagick/coder\_BIGTIFF\_fuzzer:
    Use-of-uninitialized-value in DisassociateAlphaRegion". (Credit to
    OSS-Fuzz)
    (ReadTIFFImage): tsize\_t is a signed type so be prepared for
    unexpected negative values produced by libtiff size functions.
    Fixes oss-fuzz 8934 "graphicsmagick/coder\_TIFF\_fuzzer: Sanitizer
    CHECK failure in "((0)) != (0)" (0x0, 0x0)". (Credit to OSS-Fuzz)

2018-06-16  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/wpg.c Fix oss-fuzz 7735 "graphicsmagick/coder\_WPG\_fuzzer:
    Use-of-uninitialized-value in ReadWPGImage".  (Credit to OSS-Fuzz)

2018-06-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (ReadMNGImage): ENDL chunk must be at least one
    byte in size. Fixes oss-fuzz 8832
    "graphicsmagick/coder\_MNG\_fuzzer: Null-dereference READ in
    ReadMNGImage". (Credit to OSS-Fuzz)
    (ReadMNGImage): Length of DISC chunk must be evenly divisible by
    2.  Fixes oss-fuzz 8834 "graphicsmagick/coder\_MNG\_fuzzer:
    Heap-buffer-overflow in ReadMNGImage". (Credit to OSS-Fuzz)

2018-06-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/mpc.c (ReadMPCImage): Detect end of file while reading
    image directory.  Similar to MIFF fixes for ImageMagick
    CVE-2017-18272.
    (RegisterMPCImage): Require seekable stream since MPC is strictly
    a file-based format and so GetBlobSize() is assured to work.
    Similar to MIFF behavior.  Claimed to be part of the resolution
    for ImageMagick CVE CVE-2017-11449. Suggested by Petr Gajdos via
    email on January 3, 2018.

2018-06-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/miff.c (ReadMIFFImage): Detect end of file while reading
    image directory. Fixes SourceForge issue 565 "ImageMagick
    CVE-2017-18272 applies to GraphicsMagick".  Thanks to Petr Gajdos
    for reporting this issue to us.

  - magick/import.c (ImportViewPixelArea): Use appropriate
    bits\_per\_sample validations for FloatQuantumSampleType. Fixes
    oss-fuzz 8780 "graphicsmagick/coder\_PTIF\_fuzzer:
    Use-of-uninitialized-value in HorizontalFilter". (Credit to
    OSS-Fuzz)

2018-06-09  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c More than 4GiB are not supported in MAT!

2018-06-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/mat.c (ReadMATImage): Add casts to avoid arithmetic
    overflow when computing size and offsets.  Fixes oss-fuzz 8801
    "graphicsmagick/coder\_MAT\_fuzzer: Timeout in
    graphicsmagick\_coder\_MAT\_fuzzer". (Credit to OSS-Fuzz)

  - magick/blob.c (ReadBlobLSBDoubles, ReadBlobMSBDoubles): Only
    byte-swap doubles or test doubles for NAN if we have read enough
    bytes for at least one double value.
    (ReadBlob): Add an assertion to enforce that ReadBlob() will never
    report reading more bytes than requested due to some
    implementation issue.

2018-06-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c (ReadBlob, WriteBlob): gzread(), BZ2\_bzread(),
    gzwrite(), BZ2\_bzwrite() return type 'int' rather than 'size\_t'
    like their stdio equivalents.  Use correct signed type to avoid
    returning a negative value into an unsigned type, forming a huge
    positive value.  Fixes oss-fuzz 8600
    "graphicsmagick/coder\_MAT\_fuzzer: Heap-buffer-overflow in
    ReadBlobLSBDoubles". (Credit to OSS-Fuzz)

2018-06-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (png\_read\_raw\_profile): Try to shore up parsing of
    raw profile reading to avoid heap read overruns.  Fixes oss-fuzz
    8763 "graphicsmagick/coder\_PNG32\_fuzzer: Heap-buffer-overflow in
    png\_read\_raw\_profile". (Credit to OSS-Fuzz)

2018-06-07  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c Reduce stack usage for 64 bit architecture.

2018-06-06  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/wpg.c Check return values of SeekBlob for more safety.

2018-06-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (ReadOneJNGImage): Use DestroyImageList() rather
    than DestroyImage() on returned Image from supposed read of JPEG
    data, in case multiple frames were unexpectedly returned.  Also
    add "JPEG:" prefix to filename when reading from temporary file to
    force that it can only be read as a JPEG file, disabling format
    auto-detection based on file header.  Fixes oss-fuzz 8755
    "graphicsmagick/coder\_JNG\_fuzzer: Indirect-leak in
    AllocateImage". (Credit to OSS-Fuzz)

2018-06-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c (EOFBlob): Implement EOF detection for ZipStream.
    Does some archaic zlib not provide gzeof()?  Fixes oss-fuzz 8550
    "graphicsmagick/coder\_MAT\_fuzzer: Timeout in
    graphicsmagick\_coder\_MAT\_fuzzer". (Credit to OSS-Fuzz)

2018-06-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (ReadOnePNGImage): Skip adding empty raw profile.
    Fixes oss-fuzz "graphicsmagick/coder\_PNG\_fuzzer:
    Heap-buffer-overflow in png\_read\_raw\_profile". (Credit to
    OSS-Fuzz)

2018-06-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update NEWS with latest changes.

  - coders/dcm.c (DCM\_ReadRGBImage): Force the image to DirectClass
    to avoid later use of uninitialized indexes.  Fixes oss-fuzz 8602
    "graphicsmagick/coder\_DCM\_fuzzer: Use-of-uninitialized-value in
    DCM\_PostRescaleImage". (Credit to OSS-Fuzz)
    (DCM\_ReadPlanarRGBImage): Force the image to DirectClass to avoid
    later use of uninitialized indexes.

  - coders/png.c (ReadMNGImage): Free chunk memory in error
    reporting path to avoid leak.  Fixes oss-fuzz 8721
    "graphicsmagick/coder\_MNG\_fuzzer: Direct-leak in
    ReadMNGImage". (Credit to OSS-Fuzz)

2018-06-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/constitute.c (ReadImage): Assure that an error exception
    is thrown if coder returns null without properly reporting an
    exception.

  - magick/blob.c (BlobToImage): Assure that an error exception is
    thrown if coder returns null without properly reporting an
    exception.

  - coders/png.c (ReadMNGImage): Disable mystery "linked list is
    corrupted" code.  Assure that exceptions are reported to the
    correct place so they are not lost.  Fixes oss-fuzz 8710
    "graphicsmagick/coder\_MNG\_fuzzer: Indirect-leak in
    AllocateImage". (Credit to OSS-Fuzz)

  - coders/tiff.c (ReadTIFFImage): Initialize allocated scanline,
    strip, or tile to zero in order to avoid complaint about use of
    uninitialized data if libtiff fails to write all the bytes.  Fixes
    oss-fuzz 8551 "graphicsmagick/coder\_TIFF\_fuzzer:
    Use-of-uninitialized-value in ImportGrayQuantumType". (Credit to
    OSS-Fuzz)

  - magick/annotate.c (RenderFreetype): Throw an exception if
    DrawInfo font is null.  Should fix oss-fuzz 8557
    "graphicsmagick/coder\_PCD\_fuzzer: Unknown signal in
    RenderFreetype" and may fix oss-fuzz 8544
    "graphicsmagick/coder\_PCD\_fuzzer: Null-dereference READ in
    RenderFreetype". (Credit to OSS-Fuzz)

  - coders/jpeg.c (ReadGenericProfile): Add/improve tracing for
    profile size and when JPEG header is being read.

2018-06-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (ReadOneJNGImage): Report a useful exception for
    the case when the JNG file fails to provide the necessary image
    chunks to allocate the color image.  Inspired by oss-fuzz 8666
    "graphicsmagick/coder\_JNG\_fuzzer: ASSERT: data != (const char \*)
    NULL" although the reported issue was not reproduced.

2018-05-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (ReadMNGImage): Fix off-by-one in length validation
    for TERM chunk which allowed one byte heap read overflow.  Fixes
    oss-fuzz 8615 "graphicsmagick/coder\_MNG\_fuzzer:
    Heap-buffer-overflow in mng\_get\_long". (Credit to OSS-Fuzz)
    (ReadMNGImage): Fix leak of MngInfo in error reporting path.
    Fixes oss-fuzz 8604 "graphicsmagick/coder\_MNG\_fuzzer: Direct-leak
    in ReadMNGImage". (Credit to OSS-Fuzz)
    (ReadMNGImage): Verify that claimed chunk size does not exceed
    input size.  Fixes oss-fuzz 8564 "graphicsmagick/coder\_MNG\_fuzzer:
    Out-of-memory in graphicsmagick\_coder\_MNG\_fuzzer". (Credit to
    OSS-Fuzz)

  - coders/tiff.c (ReadTIFFImage): Reject files with excessive
    samples-per-pixel or extra-samples. Avoids potential issues
    observed in oss-fuzz 8634 "graphicsmagick/coder\_BIGTIFF\_fuzzer:
    Undefined-shift in ImportAlphaQuantumType". (Credit to OSS-Fuzz)

2018-05-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (ReadMNGImage): Assure that object id index is
    always less than MNG\_MAX\_OBJECTS to avoid overflow.  Fixes
    oss-fuzz 8596 "graphicsmagick/coder\_MNG\_fuzzer:
    Index-out-of-bounds in ReadMNGImage" and likely other issues yet
    to be reported. (Credit to OSS-Fuzz)

2018-05-30  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (CompareEdges): Per ticket #562,
    function CompareEdges() did not conform to the qsort()
    requirement that if CompareEdges(edge0,edge1) returns
    -1 (i.e., edge0 "less than" edge1), then
    CompareEdges(edge1,edge0) should return 1 (edge1
    "greater than" edge0).  This has been fixed.

2018-05-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (ReadOneJNGImage): Deal with JDAA JNG chunk with
    length zero.  Fixes oss-fuzz 8562
    "graphicsmagick/coder\_JNG\_fuzzer: ASSERT: data != (const char \*)
    NULL". (Credit to OSS-Fuzz)

  - coders/tiff.c (ReadTIFFImage): Check that the bits-per-sample is
    supported by the implementation before attempting to decode the
    image. Fixes oss-fuzz 8554 "graphicsmagick/coder\_BIGTIFF\_fuzzer:
    Undefined-shift in MagickBitStreamMSBWrite". (Credit to OSS-Fuzz)

  - coders/png.c (ReadMNGImage): Eliminate use of uninitialized
    header magic data by checking for EOF first.  Fixes oss-fuzz 8597
    "graphicsmagick/coder\_MNG\_fuzzer: Use-of-uninitialized-value in
    ReadMNGImage". (Credit to OSS-Fuzz)

2018-05-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: More fixes based on what is observed
    in oss-fuzz build log.

2018-05-24  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/jnx.c The attribute should belong to only one scene and
    not to whole image list.

2018-05-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Changes to add CPPFLAGS to configure
    executions to hopefully get oss-fuzz build closer to success.

2018-05-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/t/jpeg/read.t: Add a JNX reader test case.

  - coders/jnx.c (ReadJNXImage): JNX image depth should be 8.

  - fuzzing/oss-fuzz-build.sh: Apply patch from Alex Gaynor to
    switch libpng to autotools build system, as well as configure
    GraphicsMagick with '--with-quantum-depth=16'.

2018-05-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Validate tile memory requests for
    the TIFFReadRGBATile() case in the same way as the TIFFReadTile()
    case.  Fixes oss-fuzz 8434 "graphicsmagick/coder\_BIGTIFF\_fuzzer:
    Out-of-memory in graphicsmagick\_coder\_BIGTIFF\_fuzzer". (Credit to
    OSS-Fuzz)

2018-05-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tile.c (ReadTILEImage): Remove any existing size request
    when while image to tile.  This avoids size being used for both
    the input image size and the tile image size.  Fixes SourceForge
    issue #563 "tile:<image> appears to blow image up by 100% before
    applying tiling".

2018-05-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Patch from Paul Kehrer to disable
    libpng test programs and binaries while building libpng in support
    of oss-fuzz testing.

  - coders/dcm.c (DCM\_ReadGrayscaleImage): If a palette was
    provided, the image may be in PseudoClass but we need DirectClass
    for gray image when GRAYSCALE\_USES\_PALETTE is not defined.  Fixes
    oss-fuzz 7550 "graphicsmagick/coder\_DCM\_fuzzer:
    Use-of-uninitialized-value in SyncImageCallBack". (Credit to
    OSS-Fuzz)
    (ReadDCMImage): Restore use of DCM\_PostRescaleImage() in order to
    obtain suitably scaled DICOM again.  Hopefully it is more robust
    now.
    (DCM\_ReadPaletteImage): Assure that DirectClass pixels are
    initialized.

2018-05-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Remove strange addition of
    image->columns to pixel buffer offsets which now causes a heap
    overflow since the buffer has been right-sized.  Perhaps the extra
    offset plus the over-sized allocation was some attempt to avoid
    buffer over/underflows due to bugs in libtiff. Fixes oss-fuzz 8384
    "graphicsmagick/coder\_BIGTIFF\_fuzzer: Heap-buffer-overflow in
    put1bitbwtile" which is described to be a regression. (Credit to
    OSS-Fuzz)

  - magick/render.c (DrawImage): Fix wrong range checks which caused
    spurious "Parsing of SVG images fail with "Non-conforming drawing
    primitive definition (push)" failure.  Fixes SourceForge issue 561
    "Parsing of SVG images fail with "Non-conforming drawing primitive
    definition (push)"" which is due to problems caused by the fix for
    SourceForge issue 517.

  - coders/tiff.c (WritePTIFImage): Use '-define
    ptif:minimum-geometry=<geometry>' to specify the smallest
    subresolution frame which is produced by the PTIF (Pyramid TIFF)
    writer.

2018-05-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WritePTIFImage): Allow 1x1 input image to be
    supported.

  - coders/png.c (ReadOneJNGImage): Unconditionally free JDAT chunk
    memory.  Fixes oss-fuzz 8366 "graphicsmagick/coder\_JNG\_fuzzer:
    Direct-leak in ReadOneJNGImage". (Credit to OSS-Fuzz)

  - coders/tiff.c (WritePTIFImage): Fix leak of pyramid Image list
    if ResizeImage() fails.  Fixes oss-fuzz 8364
    "graphicsmagick/coder\_PTIF\_fuzzer: Indirect-leak in
    CloneImage". (Credit to OSS-Fuzz)

2018-05-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): Add and use
    ThrowTIFFWriterException() macro to consistently clean-up when
    throwing writer exception.  May fix oss-fuzz 8321
    "graphicsmagick/coder\_EPT\_fuzzer: Direct-leak in
    TIFFClientOpen". (Credit to OSS-Fuzz)
    (ReadTIFFImage): Add and use ThrowTIFFReaderException() macro to
    consistently clean-up when throwing reader exception.

2018-05-16  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/alpha\_composite.h (AlphaCompositePixel): The
    macro definition for MagickAlphaCompositeQuantum in
    alpha\_composite.h computes an expression of the form:

    a \* b + c \* d \* e

    Code in function AlphaCompositePixel() (also in
    alpha\_composite.h) multiplies the result of this macro
    by variable "delta" as follows:

    delta \* a \* b + c \* d \* e

    However, the intended result is actually:

    delta \* ( a \* b + c \* d \* e )

    The macro definition has been modified to enclose the
    entire expression in parentheses.

    The effects of this bug were particularly evident at the
    boundary between a stroked polygon and a transparent
    black region. More generally, an incorrect composited
    pixel value was being computed by AlphaCompositePixel()
    whenever the output alpha value was not 100% opaque.

2018-05-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/rwblob.tap: Add a test for PTIF format.

  - coders/tiff.c (WritePTIFImage): Fix Image blob referencing in
    order to avoid double-free when writing PTIF to memory BLOB. Fixes
    oss-fuzz 8280 "graphicsmagick/coder\_PTIF\_fuzzer: Heap-double-free
    in Magick::BlobRef::~BlobRef". (Credit to OSS-Fuzz)

2018-05-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): Use libtiff's
    TIFFDefaultStripSize() function rather than an old porting macro
    required by some defunct libtiff version.  Expected to fix
    oss-fuzz 8248 "graphicsmagick/coder\_EPT\_fuzzer:
    Floating-point-exception in WriteTIFFImage". (Credit to OSS-Fuzz)

2018-05-13  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c Fix potentional leak when compressed object is
    corrupted. Fixes oss-fuzz 8251 (Credit to OSS-Fuzz)

2018-05-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Fix leak of Image when
    TIFFReadRGBAImage() reports failure.  Also harden buffer
    allocation calculation.  Fixes oss-fuzz 8275
    "graphicsmagick/coder\_BIGTIFF\_fuzzer: Indirect-leak in
    AllocateImage". (Credit to OSS-Fuzz)

  - coders/ept.c (ReadEPTImage): Add validations of 'count' and
    'filesize' read from EPT file. In response to oss-fuzz 8248
    "graphicsmagick/coder\_EPT\_fuzzer: Floating-point-exception in
    WriteTIFFImage" but we are unable to recreate the oss-fuzz issue
    since the EPT reader already immediately reports an EOF exception.

2018-05-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Apply SourceForge patch #57 "Add
    fuzzing support for jpeg + freetype delegates" by Alex Gaynor.

  - coders/png.c (read\_user\_chunk\_callback): Fix memory leak and use
    of uninitialized memory when handling eXIf chunk. Fixes oss-fuzz
    8247 "graphicsmagick/coder\_PNG24\_fuzzer: Direct-leak in
    png\_malloc". (Credit to OSS-Fuzz)

2018-05-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Apply SourceForge patch #56 "Use a
    few delegate libraries in fuzzing" by Alex Gaynor.

2018-05-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/rwfile.tap: MIFF zip and bzip compression tests do not
    fail if zlib and bzlib are not available because the compression
    request is silently changed to no compression.

2018-05-07  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (DrawImage, InsertAttributeIntoInputStream):
    For a reference such as 'class="classname"', the "classname"
    is now allowed to be undefined.

  - coders.svg.c (ProcessStyleClassDefs): Class definitions
    defined within a <style> block may now be empty.

  - These relaxed conditions are not specifically called out in
    the SVG spec as being either acceptable or unacceptable, but
    other SVG renderers (e.g., Chrome) handle them this way. These
    changes do not resolve, but are related to, ticket #307.

2018-05-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - utilities/Makefile.am (utilities/tests/montage.log): Fix
    dependency rule so that effects.tap is fully executed before
    execution of montage.tap starts.

2018-05-04  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (DrawImage, TraceXXX): The PrimitiveInfo
    array used to store points generated by TraceEllipse(), the
    other TraceXXX() functions, and DrawImage() was not always
    being expanded when needed, resulting in writes beyond the
    end of the currently allocated storage. To fix this problem,
    a new data structure PrimitiveInfoMgr, and an associated
    function, PrimtiveInfoRealloc(), were written to handle
    expanding the PrimitiveInfo array as needed. DrawImage() and
    the TraceXXX() functions were modified to prevent the out of
    bounds writes to memory. This fixes ticket #516.

2018-05-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (ReadOneJNGImage): Add more JNG chunk
    validations. Fixes an issue reported by "Trace Probe" via a
    follow-up post to SourceForge issue 437 "assertion failure in
    WriteBlob", although the issue described was not reproduced.

  - coders/meta.c (ReadMETAImage): Detect and report 8BIMTEXT and
    8BIMWTEXT decoding problems.  Fixes oss-fuzz 8125
    "graphicsmagick/coder\_8BIMTEXT\_fuzzer: Use-of-uninitialized-value
    in format8BIM". (Credit to OSS-Fuzz)

2018-05-02  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (TraceStrokePolygon): Excessively
    large values of stroke-width were cascading through
    other computations, causing the function to write beyond
    the end of it's array of points when the stroke-linejoin
    attribute value was "round". Code was added to reallocate
    the array of points as needed, and to limit the size of
    stroke-width (for computational purposes) to no more than
    approximately twice the diagonal size of the output image.
    Fixes ticket #515.

  - The same limit on stroke-width was applied to all other
    instances of the same computation in render.c.

2018-05-01  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - This change set fixes ticket #471.

  - magick/render.c (DrawImage): Polylines with fewer
    than two points were being flagged as an error. The
    SVG spec has no such restriction (fixed).

  - coders/svg.c (SVGStartElement) Inner <svg> elements
    could modify the output image dimensions if a geometry
    string was supplied. Now the output image dimensions
    are determined by the outermost <svg> only.

2018-05-01  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (TraceEllipse, TraceRectangle,
    TraceRoundRectangle): Per the SVG spec, rectangles and
    round rectangles having a width or height of zero are
    not rendered. Also per the spec, ellipses having an x
    or y radius of zero are not rendered.  Fixes ticket #457.

2018-04-30  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.h, (PrimitiveInfo), magick/render.c: Added
    member "flags" to PrimitiveInfo to support indicating closed
    shapes (e.g., rectangle, circle, path closed using 'z' or 'Z').
    Updated code in render.c (functions TraceXXX) to indicate
    closed shapes.  This replaces the previous policy of detecing
    closed shapes by comparing the first and last points to see if
    they are identical (within MagickEpsilon). The old policy
    prevented open subpaths with the same first and last point from
    being rendered properly (per the SVG spec) when round or square
    endcaps were enabled.  Part of the fix for ticket #322.

  - magick/render.c (ConvertPrimitiveToPath): Modified duplicate
    point elimination code so that the first and last points of
    a subpath are always preserved.  Consequences: (1) Allows
    for the correct rendering of the sequence "move x1 y1 line
    x1 y1" with round or square endcaps.  Part of the fix for
    ticket #322. (2) Fixes a bug in which eliminating the last
    point as a duplicate caused a closed shape to no longer be
    closed. This would manifest itself, for example, as a small
    "nub" on the boundary of a filled circle.

  - magick/render.c (GetPixelOpacity): Fixed a bug in the
    code that computed the distance between a point and a
    segment (polygon edge).  Prior to this fix, for zero length
    segments this code would generate a divide-by-zero and
    incorrect output. Part of the fix for ticket #322.

  - magick/render.c (DrawPolygonPrimitive): Polygons/paths with
    zero or one points are no longer rendered per the SVG spec.

  - magick/render.c (DrawStrokePolygon): Per the SVG spec, a
    polygon consisting of a single move-to command is not stroked.

  - magick/render.c (TracePath): Per the SVG spec, if the
    endpoints (x1, y1) and (x2, y2) of an arc subpath are identical,
    then this is equivalent to omitting the elliptical arc segment
    entirely.  For rendering purposes the zero length arc is
    treated like a zero length "line to" command to the current
    point.

  - magick/render.c (TraceStrokePolygon): Added code to detect
    zero length open subpaths and return a stroked polygon containing
    no points when round or square endcaps are not enabled.  This
    satisfies the SVG spec requirement that zero length subpaths are
    only stroked if the 'stroke-linecap' property has a value of
    round or square.

  - magick/render.c (TracePath): Fixed a bug in which if a "move to"
    command was followed by additional pairs of points, indicating
    implied "line to" commands, each point was added twice.

2018-04-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pcx.c (ReadPCXImage): Colormap from PCX header is only
    used if colors <= 16. Determination of DirectClass image was
    wrong.  Fixes oss-fuzz 8093 "graphicsmagick/coder\_PCX\_fuzzer:
    Use-of-uninitialized-value in IsMonochromeImage". (Credit to
    OSS-Fuzz)

2018-04-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - version.sh: Updates to prepare for the 1.3.29 release.

  - coders/pict.c (DecodeImage): Assure that scanline is initialized
    to avoid use of uninitialized data.  Fixes oss-fuzz 8063
    "graphicsmagick/coder\_WPG\_fuzzer: Use-of-uninitialized-value in
    ReadPICTImage". (Credit to OSS-Fuzz)

  - coders/dpx.c (ReadDPXImage): Assure that NULL pixels is not
    used.  Fixes oss-fuzz 8078 "graphicsmagick/coder\_DPX\_fuzzer:
    Null-dereference WRITE in ReadDPXImage". (Credit to OSS-Fuzz)

  - NEWS.txt: Update NEWS file with information about changes since
    last release.

2018-04-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dib.c (ReadDIBImage): Disable EOF tests for "ICODIB"
    subformat due to icon file provided by SourceForge issue #557
    "ErrorCorruptImage: Magick: Unexpected end-of-file ()" where an
    EOF error was reported due to no mask data being supplied.

  - coders/png.c (ReadOneJNGImage): The embedded JPEG image is
    required to have the same dimensions as the JNG image as provided
    by JHDR.  Fixes SourceForge bug 555 "heap-buffer-overflow in
    AcquireCacheNexus when processing jng file".  It is likely that
    this issue is precipitated by using 'montage' which seems to set a
    default non-zero image size.
    (ReadMNGImage): By default limit the maximum loops specifiable by
    the MNG LOOP chunk to 512 loops, but allow this to be modified by
    '-define mng:maximum-loops=value'.  Also assure that the value is
    in the range of 0-2147483647 as per the MNG specification.  This
    is to address the denial of service issue described by
    CVE-2018-10177.  This problem was reported to us by Petr Gajdos
    via email on Fri, 20 Apr 2018.

  - coders/dpx.c (ReadDPXImage): Move misplaced channel validation
    code.  Fixes oss-fuzz 8041 "graphicsmagick/coder\_DPX\_fuzzer:
    Use-of-uninitialized-value in WriteDPXImage" and oss-fuzz 8055
    "graphicsmagick/enhance\_fuzzer: Use-of-uninitialized-value in
    EnhanceImage". (Credit to OSS-Fuzz)

2018-04-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/xpm.c (StringToListMod): Algorithm fixes to fix use of
    uninitialized data.  Fixes oss-fuzz 8046
    "graphicsmagick/coder\_XPM\_fuzzer: Use-of-uninitialized-value in
    StringToListMod". (Credit to OSS-Fuzz)

2018-04-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/xpm.c (ReadXPMImage): Reduce memory consumption further.
    Hopefully fixes oss-fuzz 8013 "graphicsmagick/coder\_XPM\_fuzzer:
    Out-of-memory in graphicsmagick\_coder\_XPM\_fuzzer". (Credit to
    OSS-Fuzz)

  - magick/utility.c (StringToList): Only allocate the memory
    required when converting string to an ASCII list.  May or may not
    fix oss-fuzz 8013 "graphicsmagick/coder\_XPM\_fuzzer: Out-of-memory
    in graphicsmagick\_coder\_XPM\_fuzzer". (Credit to OSS-Fuzz)

2018-04-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/bmp.c (ReadBMPImage): Fix benign use of uninitialized
    data when testing header magick.  Fixes oss-fuzz 7980
    "graphicsmagick/coder\_BMP\_fuzzer: Use-of-uninitialized-value in
    LocaleNCompare". (Credit to OSS-Fuzz)

  - coders/dpx.c (ReadDPXImage): ColorDifferenceCbCr does require
    even image width. Fixes oss-fuzz 7966
    "graphicsmagick/coder\_DPX\_fuzzer: Unknown signal in
    TentUpsampleChroma". (Credit to OSS-Fuzz)

2018-04-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (ReadDPXImage): ColorDifferenceCbCr element
    requires two samples/pixel, not one. Fixes oss-fuzz 7951
    "graphicsmagick/coder\_DPX\_fuzzer: Heap-buffer-overflow in
    ReadDPXImage". (Credit to OSS-Fuzz)

2018-04-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pdb.c (ReadPDBImage): Assure that pixels buffer is
    initialized.  Fixes oss-fuzz 7937
    "graphicsmagick/coder\_PDB\_fuzzer: Use-of-uninitialized-value in
    ReadPDBImage". (Credit to OSS-Fuzz)

  - coders/mvg.c (ReadMVGImage): Assure that MVG viewbox parameters
    were supplied.  Fixes oss-fuzz 7936
    "graphicsmagick/coder\_MVG\_fuzzer: Use-of-uninitialized-value in
    ReadMVGImage". (Credit to OSS-Fuzz)

  - coders/dpx.c (ReadDPXImage): Element descriptors CbYCrY422 and
    CbYACrYA4224 require that the image width be evenly divisible by 2
    so enforce that.  Fixes oss-fuzz 7935
    "graphicsmagick/coder\_DPX\_fuzzer: Heap-buffer-overflow in
    ReadDPXImage". (Credit to OSS-Fuzz)

2018-04-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (ReadDPXImage): Reject DPX files which claim to use
    signed data.  Fixes oss-fuzz 7758
    "graphicsmagick/coder\_DPX\_fuzzer: Use-of-uninitialized-value in
    WriteDPXImage". (Credit to OSS-Fuzz)
    (ReadDPXImage): Validate that the image elements do update all of
    the channels, including the alpha channel.  Now report an error if
    a color channel is missing.  Fixes oss-fuzz 7758
    "graphicsmagick/coder\_DPX\_fuzzer: Use-of-uninitialized-value in
    WriteDPXImage".

  - coders/gif.c (DecodeImage): Finally fix oss-fuzz 7732
    "graphicsmagick/coder\_GIF\_fuzzer: Heap-buffer-overflow in
    DecodeImage" which was not actually fixed with previous
    changes. (Credit to OSS-Fuzz)

2018-04-21  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/topol.c Emit error when tile storage overflows image data;
        fixes oss-fuzz 7769 thanks to oss-fuzz.

2018-04-20  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (ConvertPrimitiveToPath):  Fixed a bug
    in which SVG paths containing multiple open subpaths were
    not being processed correctly, resulting in incorrect
    output.  This fixes ticket #94.

2018-04-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/gif.c (DecodeImage): Fix use of uninitialized memory
    during error condition in decoder. Fixes oss-fuzz 7732
    "graphicsmagick/coder\_GIF\_fuzzer: Heap-buffer-overflow in
    DecodeImage". (Credit to OSS-Fuzz)

  - coders/txt.c (ReadTXTImage): Assure that all image pixels are
    initialized to black.

  - Magick++/demo/zoom.cpp (main): Add a -read-blob option to read
    input file into a Blob so that it is read by the Blob reader
    rather than the file reader.  Default the output Geometry to the
    input image geometry in case the user does not specify a resize
    resolution or geometry.

  - Magick++/tests/readWriteBlob.cpp (main): Improve the quality of
    code which reads a file into memory for Blob testing.

  - magick/blob.c (BlobToImage): Add exception reports for the cases
    where 'magick' was not set and the file format could not be
    deduced from its header.  Previously a null Image pointer was
    being returned without any exception being thrown.

2018-04-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (ReadDPXImage): Assure that CbCr layer initializes
    all channels if it is the first element of a planar DPX.  Fixes
    oss-fuzz 7703 "graphicsmagick/coder\_DPX\_fuzzer:
    Use-of-uninitialized-value in WriteDPXImage". (Credit to OSS-Fuzz)

  - coders/pict.c (ReadPICTImage): Don't refer to filename member of
    ImageInfo which was just destroyed. Much thanks to Alex Gaynor for
    finding this.  Should fix oss-fuzz 6867
    "graphicsmagick/coder\_PCT\_fuzzer: Heap-use-after-free in
    GetLocaleExceptionMessage". (Credit to OSS-Fuzz).

2018-04-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/sgi.c (ReadSGIImage): Assure that iris pixels are fully
    initialized.  Fixes oss-fuzz 7543
    "graphicsmagick/coder\_SGI\_fuzzer: Use-of-uninitialized-value in
    SGIEncode". (Credit to OSS-Fuzz).

  - coders/xcf.c (ReadXCFImage): Restore SetImage() which was
    previously commented out.  This is needed to assure initialized
    pixels.  Fixes oss-fuzz 7430 "graphicsmagick/coder\_XCF\_fuzzer:
    Use-of-uninitialized-value in AlphaCompositePixel". (Credit to
    OSS-Fuzz).

  - coders/pict.c (ReadPICTImage): Properly initialize "black
    canvas" that tiles may be composed on.  Fixes oss-fuzz 7574
    "graphicsmagick/enhance\_fuzzer: Use-of-uninitialized-value in
    EnhanceImage". (Credit to OSS-Fuzz).

  - coders/rle.c (ReadRLEImage): Check for EOF when reading comment.
    Fixes oss-fuzz 7667 "graphicsmagick/coder\_RLE\_fuzzer:
    Use-of-uninitialized-value in ReadRLEImage". (Credit to OSS-Fuzz).

  - coders/pdb.c (WritePDBImage): Avoid use of uninitialized
    bytes. Fixes oss-fuzz 7638 "graphicsmagick/coder\_PDB\_fuzzer:
    Use-of-uninitialized-value in WritePDBImage". (Credit to
    OSS-Fuzz).

  - coders/rla.c (ReadRLAImage): Add many more validations,
    including scanline offsets and number of channels.  Fixes oss-fuzz
    7653 "graphicsmagick/coder\_RLA\_fuzzer: Timeout in
    graphicsmagick\_coder\_RLA\_fuzzer". (Credit to OSS-Fuzz).

  - coders/txt.c (ReadTXTImage): Implement missing subrange logic to
    read only the specified range of frames.  Limits frames read from
    oss-fuzz test case
    clusterfuzz-testcase-minimized-coder\_TEXT\_fuzzer-6061076048248832
    "graphicsmagick/coder\_TEXT\_fuzzer: Timeout in
    graphicsmagick\_coder\_TEXT\_fuzzer". (Credit to OSS-Fuzz).

  - Magick++/lib/Image.cpp (read): Set subrange = 1 since this
    interface is intended to read just one frame from the input file.
    Use the STL-based interfaces to read multiple frames.

  - coders/fits.c (ReadFITSImage): Verify FITS header before reading
    further.  Rejects file from oss-fuzz 7650
    "graphicsmagick/coder\_FITS\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_FITS\_fuzzer".  (Credit to OSS-Fuzz).

  - PerlMagick/Magick.xs (Get): Fix PerlMagick compilation problem
    due to rename/repurposing of image->clip\_mask.

2018-04-13  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/image.c, magick/image.h:  In order to be able to
    support SVG masks, and to be able to further extend the
    Image data structure without changing its size, new data
    structure ImageExtra (struct \_ImageExtra) has been added.
    Header file image.h contains only a forward declaration;
    the members of ImageExtra are defined in file image.c.
    Image member variable Image \* clip\_mask has been replaced
    by ImageExtra \* extra, and function prototypes that enable
    access to ImageExtra have been added to image.h.  The
    clip\_mask member variable now resides in ImageExtra.  All
    references to Image::clip\_mask in the GraphicsMagick
    source code have either been replaced with direct references
    to ImageExtra::clip\_mask (image.c), or have been replaced
    with calls to access function ImageGetClipMask().

  - magick/render.c, magick/render.h:  In order to be able to
    support SVG masks, and to be able to further extend the
    DrawInfo data structure without changing its size, new data
    structure DrawInfoExtra (struct \_DrawInfoExtra) has been added.
    Header file render.h contains only a forward declaration;
    the members of DrawInfoExtra are defined in file render.c.
    DrawInfo member variable char \* clip\_path has been replaced by
    DrawInfoExtra \* extra, and function prototypes that enable
    access to DrawInfoExtra have been added to render.h.  The
    clip\_path member variable now resides in ImageExtra.  All
    references to DrawInfo::clip\_path in the GraphicsMagick
    source code have either been replaced with direct references
    to DrawInfoExtra::clip\_path (render.c), or have been
    replaced with calls to access function DrawInfoGetClipPath().

  - magick/image.c (new functions CompositePathImage,
    CompositeMaskImage, GetImageCompositeMask,
    SetImageCompositeMask):  Defined new data structure ImageExtra,
    added create/destroy logic, and implemented associated access
    functions.  Implemented SVG masks.

  - magick/render.c (DrawImage, new function DrawCompositeMask):
    Defined new data structure DrawInfoExtra, added create/destroy
    logic, and implemented associated access functions.  Impemented
    SVG masks.

  - magick/pixel\_cache.c (SyncCacheNexus, new function
    CompositeCacheNexus):  Fixed references to Image::clip\_mask.
    Implemented SVG masks.

  - coders/svg.c (SVGStartElement, SVGEndElement): Implemented
    SVG masks.

  - locale/c.mgk, magick/gm\_messages.mc, magick/local\_c.h:
    Added new error codes to support SVG masks.

  - coders/ps3.c, magick/enhance.c: Fixed references to
    Image::clip\_mask.

  - magick/draw.c, wand/drawing\_wand.c: Fixed references to
    DrawInfo::clip\_path.

2018-04-13  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/wpg.c Crash on row overflow fixed oss-fuzz 7639 thanks to oss-fuzz.

2018-04-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (ReadDPXImage): Add more header validations.
    Always assure that scanline is initialized for Luma channel. Fixes
    oss-fuzz 7544 "graphicsmagick/coder\_DPX\_fuzzer:
    Use-of-uninitialized-value in WriteDPXImage". (Credit to OSS-Fuzz)

  - coders/pdb.c (ReadPDBImage): Add more EOF checks to avoid benign
    use of uninitialized data.  Fixes oss-fuzz 7545
    "graphicsmagick/coder\_PDB\_fuzzer: Use-of-uninitialized-value in
    ReadPDBImage".

  - coders/wpg.c (InsertRow, UnpackWPGRaster): x & y should be
    'unsigned long' to match type used by pixel cache APIs and image
    rows/columns.

2018-04-08  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/wpg.c Stop reading when last row is reached.
    This should stop oss-fuzz 7528 thanks to oss-fuzz.


2018-04-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/xcf.c (ReadXCFImage): Fix use of uninitialized data in
    magick header string for runt file.  Fixes oss-fuzz 7521
    "graphicsmagick/coder\_XCF\_fuzzer: Use-of-uninitialized-value in
    LocaleNCompare". (Credit to OSS-Fuzz).

2018-04-09  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - OVERVIEW: Change set 9aaeeca0224c modified the drawing
    of clipping paths to conform to the SVG spec.  This change
    set restores the previous behavior for non-SVG clients of
    render.c, while still satisfying the SVG spec for SVG clients.

  - magick/render.h (DrawInfo): Added a bit field in member
    "flags" to indicate that drawing should be SVG compliant.

  - magick/render.c (DrawImage): Now recognizes keyword
    "svg-compliant", and tags DrawInfo accordingly.  This
    allows for existing features in render.c to be changed
    to comply with the SVG spec without impacting the previous
    behavior expected by non-SVG clients.

  - magick/render.c (DrawImage): Now uses DrawInfo "flags"
    bit for SVG compliance in conjunction with "flags" bit
    for "clipping path" to determine when to ignore changes
    to fill color, stroke color, etc.  This restores the
    previous behavior for clipping paths for non-SVG clients.

  - coders/svg.c (SVGStartElement): The initial set of
    MVG commands for rendering an SVG file now includes
    new keyword "svg-compliant" (to indicate that certain
    graphical elements should be drawn according to the
    SVG spec), and includes an intialization of the SVG
    "fill-rule" to "nonzero" (the SVG default) instead of
    the internally initialized value of "evenodd".

  - coders/wpg.c: Fixed C99 "//" comments.

2018-04-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pict.c (ReadPICTImage): Copy tile exception info to main
    image and don't composite tile if it has a problem.  Fixes
    oss-fuzz 7169 "graphicsmagick/enhance\_fuzzer:
    Use-of-uninitialized-value in EnhanceImage". (Credit to OSS-Fuzz)

  - coders/dib.c (ReadDIBImage): Do not increase decode bits/pixel
    if compression=2, but use it to increase pixel packet size when
    estimating bytes per line for decode buffer.  Fixes oss-fuzz issue
    7324 "graphicsmagick/coder\_WPG\_fuzzer: Use-of-uninitialized-value
    in ReadDIBImage". (Credit to OSS-Fuzz)

  - coders/dpx.c (ReadDPXImage): When handling the first element of
    a planar DPX, assure that the other channels are
    initialized. Fixes oss-fuzz 7841 "graphicsmagick/coder\_DPX\_fuzzer:
    Use-of-uninitialized-value in WriteDPXImage". (Credit to OSS-Fuzz)

  - coders/tim.c (ReadTIMImage): Only 4 and 8 bit TIM requires a
    colormap. For other depths, force reading as DirectClass even if
    the TIM file provides a colormap.  Fixes oss-fuzz 7407
    "graphicsmagick/coder\_TIM\_fuzzer: Use-of-uninitialized-value in
    SyncImageCallBack". (Credit to OSS-Fuzz)

2018-04-08  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c The unread data contains crap in memory,
    erase current image data. This should mute oss-fuzz 6604.

  - coders/wpg.c - condition "if(y<1) continue;" is redundant
    and could be removed completely.
    Allow logging in MatlabV4 module.

  - coders/svg.c - Do not use C++ syntax in C code - removed.

2018-04-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/wpg.c (UnpackWPGRaster): Fix uninitialized row 0 when
    row-based RLE is used.  Fixes oss-fuzz 6603
    "graphicsmagick/enhance\_fuzzer: Use-of-uninitialized-value in
    BlendCompositePixel". (Credit to OSS-Fuzz)

  - coders/pcd.c: Fix many issues, including oss-fuzz 6016
    "graphicsmagick/coder\_PCD\_fuzzer: Heap-double-free in
    MagickRealloc" and oss-fuzz 6108 "graphicsmagick/coder\_PCD\_fuzzer:
    Unknown signal in AllocateThreadViewDataSet". (Credit to OSS-Fuzz)

2018-04-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dcm.c (funcDCM\_BitsStored): Limit DICOM significant bits
    to 16.  Otherwise rescale map code blows up.  Fixes oss-fuzz 7435
    "graphicsmagick/coder\_DCM\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_DCM\_fuzzer". (Credit to OSS-Fuzz)

  - coders/pix.c (ReadPIXImage): Detect EOF.  Reject RLE lenth of
    zero.  Fixes oss-fuzz 7440 "graphicsmagick/coder\_PIX\_fuzzer:
    Out-of-memory in graphicsmagick\_coder\_PIX\_fuzzer". (Credit to
    OSS-Fuzz)

2018-04-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (ReadDPXImage): Insist on having an element
    descriptor we understand since otherwise we can not decode the
    image.  Fixes oss-fuzz 7410 "graphicsmagick/coder\_DPX\_fuzzer:
    Use-of-uninitialized-value in WriteDPXImage". (Credit to OSS-Fuzz)

  - coders/avs.c, etc... (WriteAVSImage): Cache image list length
    before writing image sequence so that progress monitor is
    scalable.  Helps with oss-fuzz 7404
    "graphicsmagick/coder\_AVS\_fuzzer: Timeout in
    graphicsmagick\_coder\_AVS\_fuzzer". (Credit to OSS-Fuzz)

2018-04-05  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - coders/svg.c (SVGStartElement, SVGEndElement),
    magick/render.c (DrawImage): The current text position
    is now maintained by DrawImage() instead of by
    SVGStartElement() and SVGEndElement().  This change was
    made to support the recently implmemented "use" and
    "class" elements, which may make changes to the font
    size that are not visible to the code in svg.c.

  - coders/svg.c (GetStyleTokens, SVGStartElement): The
    list of SVG attributes is now reordered so that
    "font-size", "class", and "style" are processed first.
    This ensures that a change to the font size will be
    processed before any dimensional attribute whose value
    may depend on the font size (e.g., a width value
    specified in "em" units).

  - coders/svg.c (ProcessStyleClassDefs): Fixed two memory
    leaks associated with making an early return when
    malformed input is detected.

  - magick/render.c (ExtractTokensBetweenPushPop): Fixed
    an uninitialized variable condition which can occur when
    malformed input is detected.

  - magick/render.h (DrawInfo), magick/render.c: DrawInfo
    member "unused1" has been renamed "flags".  It is now
    used to tag a DrawInfo as being a clipping path or a
    compositing mask.

2018-04-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pdb.c (ReadPDBImage): Update DirectClass pixels to avoid
    use of uninitialized memory for 2 bits/pixel.  Fixes oss-fuzz 7350
    "graphicsmagick/coder\_PDB\_fuzzer: Use-of-uninitialized-value in
    WritePDBImage".  (Credit to OSS-Fuzz)

  - coders/palm.c (ReadPALMImage): Fix use of uninitialized memory.
    Fixes oss-fuzz 7325 "graphicsmagick/coder\_PALM\_fuzzer:
    Use-of-uninitialized-value in TransparentImageCallBack". (Credit
    to OSS-Fuzz)

  - coders/dcm.c (DCM\_ReadNonNativeImages): Break out of reading
    loop on EOF and properly report exception.  Fixes oss-fuzz 7349
    "graphicsmagick/coder\_DCM\_fuzzer: Timeout in
    graphicsmagick\_coder\_DCM\_fuzzer". (Credit to OSS-Fuzz)

2018-04-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/xcf.c (ReadXCFImage): Require that XCF file offsets be in
    ascending order to avoid DOS.  Fixes oss-fuzz 7333
    "graphicsmagick/coder\_XCF\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_XCF\_fuzzer". (Credit to OSS-Fuzz)

  - coders/wpg.c (UnpackWPGRaster): Fix memory leak in error return
    path. Fixes oss-fuzz 7338 "graphicsmagick/enhance\_fuzzer:
    Direct-leak in UnpackWPGRaster". (Credit to OSS-Fuzz)

2018-04-03  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - coders/svg.c (SVGStartElement): This changeset adds
    support for SVG geometric transforms specified using the
    style="transform: ..." syntax.  This syntax is sometimes
    used when exporting SVG files from Adobe Illustrator.

2018-04-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (ReadDPXImage): Validate DPX packing method.  Fixes
    oss-fuzz 7296 "graphicsmagick/coder\_DPX\_fuzzer:
    Use-of-uninitialized-value in WriteDPXImage". (Credit to OSS-Fuzz)

2018-04-02  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - coders/svg.c (SVGStartElement, SVGEndElement),
    magick/render.c (DrawImage): This changeset adds support for
    "class" styling attributes within a <style> section within
    the <defs> section, and the ability to reference them from
    other SVG elements by class="classname".  SVG files exported
    from Adobe Illustrator make extensive use of "class" definitions.

2018-04-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pict.c (ReadPICTImage): Fix leak of tile image on EOF.
    This is a recent regression.  Fixes oss-fuzz 7287
    "graphicsmagick/coder\_PCT\_fuzzer: Indirect-leak in
    CloneImage". (Credit to OSS-Fuzz)

  - magick/pixel\_cache.c (OpenCache): Use image->scene rather than
    GetImageIndexInList(image) for scene-id part of cache info file
    name.

  - coders/txt.c (WriteTXTImage): Optimize the progress indicator
    since it is very inefficient with a large number of scenes and
    oss-fuzz 7090 "graphicsmagick/coder\_TEXT\_fuzzer: Timeout in
    graphicsmagick\_coder\_TEXT\_fuzzer" consistently shows
    GetImageListLength() in its stack traces.

  - coders/dcm.c (ReadDCMImage): DICOM reader was no longer
    immediately quitting with excessive samples per pixel.  This
    caused spinning for a very long time when reading planar images
    with large samples per pixel.  This is a regression due to recent
    changes.  Fixes oss-fuzz 7269 "graphicsmagick/coder\_DCM\_fuzzer:
    Timeout in graphicsmagick\_coder\_DCM\_fuzzer". (Credit to OSS-Fuzz)

  - coders/xcf.c (ReadXCFImage): Destroy layer info before returning
    due to exception.  This is a new regression due to adding more
    checks. Fixes oss-fuzz 7277 "graphicsmagick/coder\_XCF\_fuzzer:
    Direct-leak in ReadXCFImage". (Credit to OSS-Fuzz)

  - coders/pdb.c (ReadPDBImage): Assure that all bytes of scanline
    are initialized while decoding.  Fixes oss-fuzz 7051
    "graphicsmagick/coder\_PDB\_fuzzer: Use-of-uninitialized-value in
    WritePDBImage". (Credit to OSS-Fuzz)

2018-03-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pcx.c (ReadPCXImage): Assure that scanline is
    initialized.  Fixes oss-fuzz 6612
    "graphicsmagick/coder\_PCX\_fuzzer: Use-of-uninitialized-value in
    WriteRLEPixels". (Credit to OSS-Fuzz)

  - coders/wpg.c (ReadWPGImage): Detect unexpected EOF and avoid use
    of uninitialized data.  Fixes oss-fuzz 6601
    "graphicsmagick/enhance\_fuzzer: Use-of-uninitialized-value in
    ImportIndexQuantumType". (Credit to OSS-Fuzz)

  - coders/sgi.c (ReadSGIImage): Assure that RLE decode buffer is
    initialized.  Fixes oss-fuzz 6599
    "graphicsmagick/coder\_SGI\_fuzzer: Use-of-uninitialized-value in
    SyncImageCallBack" and oss-fuzz 6600
    "graphicsmagick/coder\_SGI\_fuzzer: Use-of-uninitialized-value in
    SGIEncode". (Credit to OSS-Fuzz)

  - coders/viff.c (ReadVIFFImage): Fix blob I/O size validation to
    avoid use of uninitialized data. Fixes oss-fuzz 6597
    "graphicsmagick/coder\_VIFF\_fuzzer: Use-of-uninitialized-value in
    ThresholdImage". (Credit to OSS-Fuzz)
    (ReadVIFFImage): Don't execute SetImageType(image,BilevelType) on
    an image which has no pixels yet in order to avoid use of
    uninitialized data. Fixes oss-fuzz 6597.  (Credit to OSS-Fuzz)

  - coders/wbmp.c (ReadWBMPImage): Fix blob I/O size validation to
    avoid use of uninitialized data. Fixes oss-fuzz 7047
    "graphicsmagick/coder\_WBMP\_fuzzer: Use-of-uninitialized-value in
    ReadWBMPImage". (Credit to OSS-Fuzz)

  - coders/wpg.c (ExtractPostscript): Allow non-Postscript content
    but force reading using the magick we already detected.  Also log
    the format that we detected.

  - coders/xcf.c (ReadOneLayer): Reject layer size of 0x0.  Fixes
    oss-fuzz 6636 "graphicsmagick/coder\_XCF\_fuzzer: Direct-leak in
    MagickMallocAligned". (Credit to OSS-Fuzz)
    (ReadXCFImage): Verify that seek offsets are within the bounds of
    the file data. Fixes oss-fuzz 6682
    "graphicsmagick/coder\_XCF\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_XCF\_fuzzer". (Credit to OSS-Fuzz)

  - magick/pixel\_cache.c (ModifyCache): Destroy CacheInfo if
    OpenCache() fails so it is not leaked.

  - coders/wpg.c (ExtractPostscript): Enforce that embedded file is
    a Postscript file.  Fixes oss-fuzz 7235
    "graphicsmagick/coder\_WPG\_fuzzer: Indirect-leak in MagickRealloc".
    This is indicated to be a regression. (Credit to OSS-Fuzz)

2018-03-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pict.c (ReadPICTImage): Check image pixel limits before
    allocating memory for tile.  Fixes oss-fuzz 7217
    "graphicsmagick/coder\_PICT\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_PICT\_fuzzer".

2018-03-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pcd.c (ReadPCDImage): Add checks for EOF. Fixes oss-fuzz
    issue 7180 "graphicsmagick/coder\_PCDS\_fuzzer: Timeout in
    graphicsmagick\_coder\_PCDS\_fuzzer".  (Credit to OSS-Fuzz)

2018-03-29  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - coders/svg.c (SVGStartElement, SVGEndElement),
    magick/render.c (DrawImage): This changeset implements the SVG
    "use" element.  Graphical elements (e.g., "rect", "text", etc.)
    can be tagged with an identifier using 'id="identifier"' when
    defined within the "defs" section.  They can then be referenced
    elsewhere in the SVG file using:

    <use xlink:href="#identifier" ... />

    When referencing a graphical element by its identifier, the
    following syntaxes are now treated as being the same:

    href="#identifier"
    href="url(#identifier)"
    xlink:href="#identifier"
    xlink:href="url(#identifier)"

2018-03-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tim.c (ReadTIMImage): Reader was not observing subimage
    and subrange to quit after the specified frame range.  Inspired by
    oss-fuzz 7132 "graphicsmagick/coder\_TIM\_fuzzer: Timeout in
    graphicsmagick\_coder\_TIM\_fuzzer" (Credit to OSS-Fuzz)

2018-03-27  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - coders/svg.c (SVGStartElement): Enable setting the
    background color from the SVG file when the client
    specifies style="background:color" inside the <svg>
    ... </svg> element.

2018-03-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/mtv.c (ReadMTVImage): Add some elementary tracing to MTV
    reader.

  - coders/png.c (ReadMNGImage): Fix SourceForge issue 554
    "Divide-by-zero in ReadMNGImage (coders/png.c)".  (Credit to Trace
    Probe)

  - coders/bmp.c (ReadBMPImage): Assure that start position always
    advances to avoid looping BMPs.  Fixes oss-fuzz 7045
    "graphicsmagick/coder\_BMP\_fuzzer: Timeout in
    graphicsmagick\_coder\_BMP\_fuzzer". (Credit to OSS-Fuzz)

  - coders/pict.c (DecodeImage): Verify that sufficient backing data
    exists before allocating memory to read it.  Fixes oss-fuzz 6629
    "graphicsmagick/coder\_PCT\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_PCT\_fuzzer".
    (ReadPICTImage): Destroy tile\_image in ThrowPICTReaderException()
    macro to simplify logic.

2018-03-25  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c Check whether datablock is really read.
    Fixes oss-fuzz 7056 (Credit to OSS-Fuzz)

  - coders/txt.c Duplicate image check for data with fixed geometry
    previous check is skipped. Fixes oss-fuzz 7090.

2018-03-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dcm.c (ReadDCMImage): Validate that samples per pixel is
    in valid range.  Fixes oss-fuzz 6260
    "graphicsmagick/coder\_DCM\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_DCM\_fuzzer". (Credit to OSS-Fuzz)

  - coders/meta.c (format8BIM): Allocate space for null termination
    and null terminate string.  Fixes oss-fuzz 5985
    "graphicsmagick/coder\_8BIMTEXT\_fuzzer: Heap-buffer-overflow in
    formatIPTCfromBuffer". (Credit to OSS-Fuzz)

  - coders/fits.c (ReadFITSImage): Include number of FITS scenes in
    file size validations.  Fixes oss-fuzz 6781
    "graphicsmagick/coder\_FITS\_fuzzer: Timeout in
    graphicsmagick\_coder\_FITS\_fuzzer". (Credit to OSS-Fuzz)

2018-03-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/meta.c (format8BIM): Validate size request prior to
    allocation. Fixes oss-fuzz issue 5974
    "graphicsmagick/coder\_8BIMTEXT\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_8BIMTEXT\_fuzzer". (Credit to OSS-Fuzz)

2018-03-23  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c Fix forged amount of frames 7076. (Credit to OSS-Fuzz)

        \* coders/topol.c Check for forged image that overflows file size
        (fuzz 6836).

2018-03-23  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c, render.h (DrawInfo, CloneDrawInfo,
    DrawClipPath, DrawImage, GetDrawInfo): According to the SVG
    spec, a clipping path is defined only by the geometry of its
    constituent elements, and is not dependent on fill color/opacity,
    stroke color/opacity, or stroke width.  To ensure conformity
    with the spec, when a clipping path is created, these SVG
    elements are set to appropriate values, and any attempt to
    modify them is ignored.

    Also, whenever a clipping path is drawn, the associated image
    attributes are now updated from the parent image structure.
    This ensures that any added or modified attributes are up to
    date.

2018-03-22  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/topol.c Use rather MagickSwabArrayOfUInt32() to
        flip all array elements at once.

        \* magick/annotate.c Compilation issue - using C++ syntax in C code.

2018-03-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (ReadDPXImage): Validate header length and offset
    properties.  Fixes oss-fuzz "graphicsmagick/coder\_DPX\_fuzzer:
    Use-of-uninitialized-value in WriteDPXImage". (Credit to OSS-Fuzz)

2018-03-20  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/annotate.c (RenderType): According to the SVG
    spec, the 'font-family' element can be a comma-separated
    list of one or more font family names.  Function RenderType
    in file annotate.c has been modified to support multiple
    font family names as follows.  The comma-separated list is
    processed until the first available font family is found.
    If no font family is found, or if font substitution occurred,
    then the entire font family string is tested to see if it
    exactly matches a font name, or if the font family string
    with blanks changed to hypens exactly matches a font name.
    If a font name match is found, the matched font overrides
    the font substution.  The font name matching functionality
    is beyond what's in the SVG spec and is provided as a
    convenience to the user.

2018-03-20  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c Fix forged amount of frames 6755. (Credit to OSS-Fuzz)

2018-03-20  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/topol.c Redesign ReadBlobDwordLSB() to be more effective.

2018-03-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/xpm.c (ReadXPMImage): Reject XPM if its condensed version
    contains non-whitespace control characters.  Fixes oss-fuzz 7027
    "graphicsmagick/coder\_XPM\_fuzzer: Timeout in
    graphicsmagick\_coder\_XPM\_fuzzer". (Credit to OSS-Fuzz)

2018-03-19  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/topol.c Fix tile index overflow fuzz 6634. (Credit to OSS-Fuzz)

2018-03-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dcm.c (DCM\_ReadGrayscaleImage): Don't use rescale map if
    it was not allocated.  This issue was induced in this development
    cycle due to disabling generating the rescale map.  Fixes oss-fuzz
    7021 "graphicsmagick/coder\_DCM\_fuzzer: Null-dereference READ in
    DCM\_ReadGrayscaleImage". (Credit to OSS-Fuzz)

2018-03-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/color\_lookup.c (QueryColorDatabase): Defend against
    partial scanf() expression matching, resulting in use of
    uninitialized data.  Likely fixes oss-fuzz 6596
    "graphicsmagick/coder\_XPM\_fuzzer: Use-of-uninitialized-value in
    IsMonochromeImage". (Credit to OSS-Fuzz)

  - coders/rle.c (ReadRLEImage): Validate number of colormap bits to
    avoid undefined shift behavior.  Fixes oss-fuzz 6630
    "graphicsmagick/enhance\_fuzzer: Undefined-shift in
    ReadRLEImage". (Credit to OSS-Fuzz)

  - coders/dcm.c (DCM\_ReadRGBImage): Don't use rescale map if it was
    not allocated.  This issue was induced in this development cycle
    due to disabling generating the rescale map.  Fixes oss-fuzz 6995
    "graphicsmagick/coder\_DCM\_fuzzer: Null-dereference READ in
    DCM\_ReadRGBImage". (Credit to OSS-Fuzz)

  - coders/dib.c (DecodeImage): Report failure to decode to expected
    amount of pixel data as an error.  Fixes oss-fuzz 7007
    "graphicsmagick/enhance\_fuzzer: Use-of-uninitialized-value in
    EnhanceImage". (Credit to OSS-Fuzz)

  - coders/bmp.c (ReadBMPImage): Add file size and offset/seek
    validations.  Fixes oss-fuzz 6623
    "graphicsmagick/coder\_BMP\_fuzzer: Timeout in
    graphicsmagick\_coder\_BMP\_fuzzer". (Credit to OSS-Fuzz)

2018-03-17  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - dcraw/dcraw.c Updated to version 9.27

2018-03-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/gif.c (ReadGIFImage): Fix botched fixes for use of
    uninitialized data when reading GIF extension blocks.  Hopefully
    ok now.

2018-03-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/gif.c (ReadGIFImage): Fix use of uninitialized data when
    reading GIF extension blocks.  Fixes oss-fuzz 6609
    "graphicsmagick/coder\_GIF\_fuzzer: Use-of-uninitialized-value in
    MagickArraySize". This seems to be a totally benign issue. (Credit
    to OSS-Fuzz)

  - magick/magick.c (MagickSignal): Use an alternate signal stack,
    if available.  This is required for Go lang C language extensions
    since Go lang requests an alternate signal sack, and uses small
    stacks for its threads.  If the library user has not allocated an
    alternate signal stack, then behavior should be just as before.
    Issue was originally reported by yzh杨振宏 on March 1, 2018 via
    the graphicsmagick-help SourceForge mailing list.

2018-02-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.c (AcquireCacheNexus): Add a check that the
    pixel cache is compatible with the image dimensions.  Fixes
    oss-fuzz issues 5978 5988 5989 5990 5993 6016, and 6056, which are
    all related to the PICT writer. (Credit to OSS-Fuzz)

  - magick/draw.c (DrawGetStrokeDashArray): Check for failure to
    allocate memory.  Patch submited by Petr Gajdos via email on
    February 28, 2018.

2018-02-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/fits.c (ReadFITSImage): Fix signed integer overflow when
    computing pixels size.  Fixes oss-fuzz 6586
    "graphicsmagick/coder\_FITS\_fuzzer: Integer-overflow in
    ReadFITSImage". (Credit to OSS-Fuzz)

2018-02-27  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - coders/svg.c (SVGStartElement, SVGEndElement): From the
    SVG spec:  "The 'foreignObject' element allows for inclusion
    of a foreign namespace which has its graphical content drawn
    by a different user agent."  Code has been added to consume
    and discard the 'foreignObject' element and any settings (e.g.,
    fill color) internal to it.  Previously, settings internal
    to the 'foreignObject' element would persist and "leak" into
    the graphic elements that followed it, resulting in undesired
    side effects (e.g., fill color other than the expected default).

2018-02-27  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (DrawPolygonPrimitive): Fixed a bug
    introduced by changeset 39102dd1d456.  For SVG, this
    changeset applied both the group AND the fill opacity
    values to fill patterns (similarly for stroke).  For WMF,
    however, this caused the fill pattern to be rendered as
    100% transparent.  A closer reading of the SVG spec does
    NOT show that the fill opacity should be applied to the
    fill pattern, so as of this latest changeset only the group
    opacity value is applied to fill and stroke patterns.

2018-02-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/bmp.c (ReadBMPImage): Fix divide by zero regression added
    by latest fixes.  Fixes oss-fuzz 6583
    "graphicsmagick/coder\_BMP\_fuzzer: Divide-by-zero in ReadBMPImage".
    (Credit to OSS-Fuzz)

2018-02-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pict.c (ReadPICTImage): Validate that PICT rectangles do
    not have zero dimensions.  Specify expected file type when reading
    from a temporary file.  Trace PICT rectangle dimensions.  More
    detection of blob EOF and more error handling.  Fixes oss-fuzz
    issue 6193 "graphicsmagick/coder\_PCT\_fuzzer: Unknown signal in
    AllocateImageColormap" and likely many oss-fuzz ASAN/UBSAN issues
    reported against "PCT" and "PICT" since this one problem appears
    to be causing a spew of reports.

  - coders/png.c (ReadMNGImage): Detect and handle failure to
    allocate global PLTE.  Problem was reported via email from Petr
    Gajdos on February 26, 2018.

2018-02-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c (ReadBlobLSBDouble): Make sure imported double is
    a normal value.
    (ReadBlobLSBDoubles): Make sure imported doubles are normal
    values.
    (ReadBlobLSBFloat): Make sure imported float is a normal value.
    (ReadBlobLSBFloats): Make sure imported floats are normal values.
    (ReadBlobMSBFloat): Make sure imported float is a normal value.
    (ReadBlobMSBFloats): Make sure imported floats are normal values.
    (ReadBlobMSBDouble): Make sure imported double is a normal value.
    (ReadBlobMSBDoubles): Make sure imported doubles are normal
    values.

  - magick/import.c (ImportFloat32Quantum): Make sure imported float
    is a normal value.
    (ImportFloat64Quantum): Make sure imported double is a normal
    value.

  - magick/image.h (RoundDoubleToQuantum): Restore previous behavior
    (from earlier today).
    (RoundFloatToQuantum): Restore previous behavior (from earlier
    today).

  - coders/bmp.c (ReadBMPImage): Fix UBSAN runtime error: left shift
    of 205 by 24 places cannot be represented in type 'int'.

  - coders/ept.c (ReadEPTImage): Fix dereference of NULL pointer
    which was detected by UBSAN in the test suite.

  - magick/image.h (RoundDoubleToQuantum): Check double value for
    NaN and infinity in order to avoid undefined behavior.
    (RoundFloatToQuantum): Check float value for NaN and infinity in
    order to avoid undefined behavior.

  - magick/common.h (MAGICK\_ISNAN): Add a isnan() wrapper macro.
    (MAGICK\_ISINF): Add a isinf() wrapper macro.

2018-02-25  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c Fix oss-fuzz issue 6273 - Heap-use-after-free in
    GetLocaleExceptionMessage. (Credit to OSS-Fuzz)

2018-02-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dcm.c (DCM\_PostRescaleImage): Remove use of
    DCM\_PostRescaleImage() since its implementation is wrong and
    accesses non-allocated heap memory.  Problem was reported by Petr
    Gajdos via email on February 8, 2018.

  - coders/jp2.c (ReadJP2Image): Use a ThrowJP2ReaderException macro
    to automatically clean up when throwing an exception.

  - coders/bmp.c (ReadBMPImage): Report an error if RLE decode does
    not produce the expected number of bytes.  Fixes oss-fuzz issue
    6015 "graphicsmagick/coder\_BMP\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_BMP\_fuzzer". (Credit to OSS-Fuzz)

2018-02-23  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (DrawImage): Fixed a bug in which graphical
    elements defined within <defs> ... </defs> were being rendered,
    contrary to the SVG spec.

2018-02-23  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (DrawPolygonPrimitive): When filling or
    stroking a polygon using a pattern, the fill (or stroke)
    and group/object opacity values were not being applied to
    the pattern (fixed).

2018-02-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/bmp.c (ReadBMPImage): Fix SeekBlob() return value checks.
    Add more EOF checks.  Require that a provided ba\_offset be a
    forward seek in order to avoid the possibility of endless looping.

2018-02-23  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c Fix oss-fuzz issue 6301. (Credit to OSS-Fuzz)

2018-02-22  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/alpha\_composite.c (BlendQuantumOpacity): The
    pixel compositing equation used when compositing an
    image into the output was incorrect and has been fixed.

  - magick/render.c (DrawPolygonPrimitive): When
    compositing polygon edge pixels over a transparent
    black background, the code would composite as if the
    background were opaque black, resulting in the edge
    pixels being too dark (fixed).

2018-02-21  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (DrawImage): Per the SVG spec, opacity,
    fill-opacity, and stroke-opacity values are now clamped
    to [0,1].

    Also fixed two bugs introduced by changeset 91de8039f27d
    (dated 2018-02-12): (1) a group/object opacity value
    specified using a percentage was not being converted to a
    value in [0,1]; (2) if fill-opacity or stroke-opacity was
    1, and the group/object opacity value was set to 1, the
    resulting fill-opacity or stroke-opacity value would be
    set to 0 instead of 1.
    
2018-02-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/viff.c (ReadVIFFImage): Fix excessive memory usage.
    Fixes oss-fuzz 6006 "graphicsmagick/coder\_XV\_fuzzer: Out-of-memory
    in graphicsmagick\_coder\_XV\_fuzzer". (Credit to OSS-Fuzz)

  - coders/txt.c (ReadInt): Avoid benign signed integer overflow due
    to accepting an arbitrary number of digits.  Fixes oss-fuzz 6002
    "graphicsmagick/coder\_TEXT\_fuzzer: Integer-overflow in
    ReadInt". (Credit to OSS-Fuzz)

  - coders/viff.c (ReadVIFFImage): Verify that there is sufficient
    data to back up colormap allocation request.  Fixes oss-fuzz 5986
    "graphicsmagick/coder\_VIFF\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_VIFF\_fuzzer". (Credit to OSS-Fuzz)

  - magick/memory.c: Define MAGICK\_MEMORY\_HARD\_LIMIT=value to abort
    when memory request exceeds value.  Useful to find location of
    excessive memory requests.

2018-02-19  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - coders/svg.c (SVGStartElement): Per the SVG spec, the
    SVG coder now initializes the MVG coder (which renders
    SVG graphical elements) with the the SVG defaults for
    fill color, fill-opacity, stroke color, stroke-opacity,
    and stroke-width.  This makes the SVG coder independent
    of the MVG coder intial state.

2018-02-19  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - coders/svg.c (SVGStartElement): Fixed initialization of
    x and y attributes per the SVG spec:  for graphical elements
    "image", "pattern", "text", "rect", and "use", if the x or y
    attribute is not specified, the effect is as if a value of
    "0" were specified.

2018-02-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/sun.c (ReadSUNImage): Fix edge case which broke file-size
    validation logic.  Fixes oss-fuzz issue 5981
    "graphicsmagick/coder\_SUN\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_SUN\_fuzzer". (Credit to OSS-Fuzz)

  - coders/txt.c (ReadTXTImage): Validate that file size is
    sufficient for claimed image properties.  Fixes oss-fuzz issue
    5960 "graphicsmagick/coder\_TXT\_fuzzer: Out-of-memory in
    graphicsmagick\_coder\_TXT\_fuzzer". (Credit to OSS-Fuzz)

  - coders/tga.c (ReadTGAImage): Only allow 1 and 8 bit
    colormapped/grey images. Fixes oss-fuzz issue 6314
    "graphicsmagick/coder\_ICB\_fuzzer: Undefined-shift in
    ReadTGAImage". (Credit to OSS-Fuzz)

  - coders/bmp.c (ReadBMPImage): Detect and report when BMP height
    value is out of range (too negative). Fixes oss-fuzz issue 6394
    "graphicsmagick/coder\_BMP\_fuzzer: Integer-overflow in
    ReadBMPImage". (Credit to OSS-Fuzz)

  - coders/rla.c (ReadRLAImage): Detect when RLE decoding is
    producing too many samples and report as an error.  Fixes oss-fuzz
    issue 6312 "graphicsmagick/coder\_RLA\_fuzzer: Timeout in
    graphicsmagick\_coder\_RLA\_fuzzer". (Credit to OSS-Fuzz)

  - coders/fits.c (ReadFITSImage): Validate that file size is
    sufficient for claimed image properties.  Fixes oss-fuzz issue
    6429 "graphicsmagick/coder\_FITS\_fuzzer: Timeout in
    graphicsmagick\_coder\_FITS\_fuzzer". (Credit to OSS-Fuzz)

  - magick/image.c (CloneImage): Check image pixel limits in
    CloneImage() when it is used to change the image dimensions.  This
    avoids depending on the using code to detect and report such
    issues.

  - coders/xcf.c (ReadXCFImage): Check image pixel limits after each
    CloneImage() to assure that image is within specified resource
    limits.  Fixes oss-fuzz issue 6399 "graphicsmagick/enhance\_fuzzer:
    Timeout in graphicsmagick\_enhance\_fuzzer". (Credit to OSS-Fuzz)

2018-02-16  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (TracePath): TracePath() was not
    correctly processing multiple sets of cubic or quadratic
    Bezier coordinates when the previous path data command was
    not a cubic or quadratic Bezier command.  This would result
    in the first control point being equal to the current path
    point instead of being computed using the current path
    point and the second control point of the previous Bezier
    command.

2018-02-15  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (TracePath): TracePath() was not
    consuming commas (if present) at the end of a set of
    points when multiple sets of points were specified for
    various path commands (e.g., line, Bezier). This
    resulted in the remaining sets of points being ignored
    (fixed).

2018-02-15  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (TraceArcPath): No points are generated
    by TraceArcPath() if the starting and ending arc points
    are the same.  For this case, the coordinate count was not
    being set to zero before returning (fixed).

2018-02-15  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (DrawImage): Clipping of polygons in
    DrawImage() would sometime result in a starting pixel
    location that was greater than the ending pixel location,
    causing a subsequent call to GetImagePixelsEx() to fail
    due a column count <= 0.  Modified the clipping code to
    eliminate this condition, and also to return early if
    the polygon lies completely outside the image boundaries.
    Also fixed variable declarations from a previous commit
    that were causing problems for the C89 compiler.

2018-02-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/topol.c (ReadTOPOLImage): Detect EOF immediately rather
    than spinning.  Fixes oss-fuzz issue 6303
    "graphicsmagick/coder\_TOPOL\_fuzzer: Timeout in
    graphicsmagick\_coder\_TOPOL\_fuzzer". (Credit to OSS-Fuzz)

  - coders/dcm.c (DCM\_SetupRescaleMap): Avoid excessive left shift.
    Fixes oss-fuzz issue 6256 "graphicsmagick/coder\_DCM\_fuzzer:
    Undefined-shift in DCM\_SetupRescaleMap". (Credit to OSS-Fuzz)

2018-02-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/wpg.c (ExtractPostscript): Detect EOF on input while
    transferring bytes to Postscript file.  Fixes oss-fuzz issue 6087
    "graphicsmagick/coder\_WPG\_fuzzer: NULL".  Later identified to be
    CVE-2017-17682 as previously discovered in ImageMagick.  (Credit to
    OSS-Fuzz)

  - coders/pdb.c (ReadPDBImage): Quit attempting to read image data
    immediately at EOF. Fixes oss-fuzz issue 6252
    "graphicsmagick/coder\_PDB\_fuzzer: Timeout in
    graphicsmagick\_coder\_PDB\_fuzzer".  (Credit to OSS-Fuzz)

2018-02-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/topol.c (ReadTOPOLImage): Avoid index out of bounds when
    input filename does not use a file extension. Fixes oss-fuzz issue
    6237 "graphicsmagick/coder\_TOPOL\_fuzzer: Index-out-of-bounds in
    ReadTOPOLImage".  (Credit to OSS-Fuzz)

2018-02-12  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (DrawImage): Object/group opacity,
    when set in DrawImage(), would overwrite the fill
    and stroke opacities. This has been fixed so that
    the object opacity is now combined with the fill
    and stroke opacities per the SVG spec.

2018-02-12  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c Fix oss-fuzz issue 6021. (Credit to OSS-Fuzz)

2018-02-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dcm.c (ReadDCMImage): Avoid undefined left shift of
    short.  Fix memory leaks in error reporting paths.  Fixes oss-fuzz
    issue 6217 "graphicsmagick/coder\_DCM\_fuzzer: Undefined-shift in
    ReadDCMImage". (Credit to OSS-Fuzz)

  - coders/dpx.c (ReadDPXImage): Avoid divide by zero exception in
    the case where reference high equals reference low. Fixes oss-fuzz
    issue 6215 "graphicsmagick/coder\_DPX\_fuzzer: Divide-by-zero in
    ReadDPXImage". (Credit to OSS-Fuzz)

  - coders/topol.c (ReadTOPOLImage): Avoid index out of bounds when
    input filename does not use a file extension.

  - coders/cut.c (ReadCUTImage): Avoid index out of bounds when
    input filename does not use a file extension. Fixes oss-fuzz issue
    6218 "graphicsmagick/coder\_CUT\_fuzzer: Index-out-of-bounds in
    ReadCUTImage".  (Credit to OSS-Fuzz)

  - coders/pwp.c (ReadPWPImage): Force temporary file to be read as
    a SFW file rather than autodetecting the format.  Fixes oss-fuzz
    issue 6220 "graphicsmagick/coder\_PWP\_fuzzer: Indirect-leak in
    AllocateImage".  (Credit to OSS-Fuzz)

2018-02-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pdf.c (WritePDFImage): Assure that xref memory is not
    leaked if an exception is thrown.  Fixes oss-fuzz issue 5968
    "graphicsmagick/coder\_EPDF\_fuzzer: Direct-leak in MagickRealloc".
    (Credit to OSS-Fuzz)

  - coders/tim.c (ReadTIMImage): Verify that 4/8 bit PSX TIM
    provides a CLUT and verify indexes.  Fixes oss-fuzz issue 5972
    "graphicsmagick/coder\_TIM\_fuzzer: Null-dereference WRITE in
    ReadTIMImage".  (Credit to OSS-Fuzz)

  - coders/topol.c (ReadTOPOLImage): Add additional header
    validations.  Fixes oss-fuzz issue 5975
    "graphicsmagick/coder\_TOPOL\_fuzzer: Floating-point-exception in
    ReadTOPOLImage".  (Credit to OSS-Fuzz)

  - coders/bmp.c (ReadBMPImage): Avoid possible division by zero
    when decoding CIE primary values. (Credit to OSS-Fuzz)

  - magick/export.c (ExportViewPixelArea): Only compute
    unsigned\_maxvalue if sample\_bits <= 32.

  - magick/import.c (ImportViewPixelArea): Assure that
    double\_maxvalue minus double\_minvalue is not zero, or excessively
    close to zero to avoid divide by zero exception or impossible
    scaling factor. (Credit to OSS-Fuzz)
    (ImportViewPixelArea): Only compute unsigned\_maxvalue if
    sample\_bits <= 32.

2018-02-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dib.c (ReadDIBImage): Validate that image width is not
    too negative such that it's absolute value can not fit in 32-bit
    unsigned width. Resolves oss-fuzz issue 6179
    "graphicsmagick/coder\_ICO\_fuzzer: Integer-overflow in
    ReadDIBImage". (Credit to OSS-Fuzz)

  - coders/dcm.c (funcDCM\_BitsStored): Validate DICOM datum size.
    Use a different means to determine the maximum value which does
    not use excessive shifting.  Resolves oss-fuzz issue 6165
    "graphicsmagick/coder\_DCM\_fuzzer: Undefined-shift in
    funcDCM\_BitsStored". (Credit to OSS-Fuzz)

2018-02-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (ReadWordU32BE): Add casts to avoid default type
    promotion from unsigned char to 'int' leading to undefined
    behavior for 24 bit shift. Fixes oss-fuzz issue 6058
    "graphicsmagick/coder\_DPX\_fuzzer: Undefined-shift in
    ReadWordU32BE". (Credit to OSS-Fuzz)
    (ReadDPXImage): Require that the file has at least one element.
    Add bountiful casts for values which are left-shifted.  Fixes
    oss-fuzz issue 5962 "graphicsmagick/coder\_DPX\_fuzzer:
    Undefined-shift in ReadDPXImage". (Credit to OSS-Fuzz)

  - coders/dcm.c (DCM\_ReadOffsetTable): Add casts Add casts to avoid
    default type promotion from unsigned char to 'int' leading to
    undefined behavior for 16 bit shift. Fixes oss-fuzz issue 5980
    "graphicsmagick/coder\_DCM\_fuzzer: Undefined-shift in
    DCM\_ReadOffsetTable". (Credit to OSS-Fuzz)

  - magick/module\_aliases.h (ModuleAliases): Add missing mapping
    from "ICODIB" format to "DIB" module.

  - magick/import.c (ImportUInt32Quantum): Add casts to avoid
    default type promotion from unsigned char to 'int' leading to
    undefined behavior for 24 bit shift.  Fixes oss-fuzz
    "graphicsmagick/coder\_P7\_fuzzer: Undefined-shift in
    ImportRGBQuantumType". (Credit to OSS-Fuzz)

2018-02-07  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/wpg.c Fix oss-fuzz issue 5964
    "graphicsmagick/coder\_MAT\_fuzzer: Heap-use-after-free in
    GetLocaleExceptionMessage". (Credit to OSS-Fuzz)

2018-02-07    Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/render.c (IsPoint): Fixed a bug in which
    IsPoint() would reject as a valid coordinate value
    strings that did not begin with an integer: e.g.,
    "0.25" would be accepted, but ".25" would not.

2018-02-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/cut.c (ReadCUTImage): Fix DestroyImageInfo() of NULL
    pointer leading to assertion.  Fixes oss-fuzz issue 6067
    "graphicsmagick/coder\_CUT\_fuzzer: Unknown signal in
    DestroyImageInfo".

  - coders/tga.c (ReadTGAImage): Throw exception rather than
    assertion for unexpected comment size.  Fixes oss-fuzz issue 5961
    "graphicsmagick/coder\_ICB\_fuzzer: ASSERT: (size\_t)
    (tga\_info.id\_length+1) == commentsize".

2018-02-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pdf.c (WritePDFImage): Free 'xref' allocation before
    error return.  Fixes oss-fuzz issue 5968
    "graphicsmagick/coder\_EPDF\_fuzzer: Direct-leak in MagickRealloc".

2018-02-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pdb.c (ReadPDBImage): Fix heap buffer overflow if blob is
    already at EOF when comment is read.  Fixes oss-fuzz issue 5997
    "graphicsmagick/coder\_PDB\_fuzzer: Heap-buffer-overflow in
    SetImageAttribute".

  - coders/dpx.c (ReadDPXImage): Fix memory leak of user data if
    user data is truncated.  Fix consumption of one uninitialized
    stack bytes.  Fixes oss-fuzz issue 5973:
    graphicsmagick/enhance\_fuzzer: Direct-leak in ReadDPXImage.

  - coders/pnm.c (ReadPNMImage): Detect and avoid division by zero.
    Fixes Issue 5959 in oss-fuzz: graphicsmagick/coder\_P7\_fuzzer:
    Divide-by-zero in ReadPNMImage

  - magick/xwindow.c (MagickXClientMessage): Eliminate valgrind
    gripe about use of uninitialized stack data by clearing allocation
    to zero.
    (MagickXMakeImage): Eliminate valgrind gripe about use of
    uninitialized heap data by clearing allocation to zero.

  - coders/pwp.c (ReadPWPImage): Remove bogus EOF test on an image
    with a closed blob.  Fixes Issue 5957 in oss-fuzz:
    graphicsmagick/coder\_PWP\_fuzzer: ASSERT: image->blob->type !=
    UndefinedStream.

  - www/Changes.rst: Fix typo with spelling "ChangeLog-2017.html".
    Resolves SourceForge issue #544 "dead link 2017 changelog page on
    GraphicsMagick web site".

2018-02-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/static.c (OpenModule): Assure that status is initialized.
    Resolves Coverity 261207 "Uninitialized scalar variable".

  - wand/magick\_wand.c (MagickHasColormap): New function to test if
    the image has a colormap.
    (MagickIsGrayImage): New function to test if the image uses only
    gray pixels.
    (MagickIsMonochromeImage): New function to test if the image uses
    only monochrome pixels.
    (MagickIsOpaqueImage): New function to test if the image uses only
    opaque pixels.
    (MagickIsPaletteImage): New function to test if the image is based
    on a color palette.  Above functions are written by Troy Patteson
    and submitted via SourceForge patch #54 "Wand API patches: has
    colormap, is gray image, is monochrome image, is opaque image, is
    palette image".

  - fuzzing: Added initial OSS-Fuzz integration by Alex Gaynor.
    From SourceForge patch #55 "OSS-Fuzz integration"

  - coders/png.c (ReadMNGImage): Fix free using possibly unallocated
    pointer value.

  - magick/blob.c (SeekBlob): Remove implicit extension of blob
    allocation size based on seek offset.  Besides making an
    assumption about how the blob memory was allocated, this
    reallocation feature provides a memory DOS opportunity.  Resolves
    issue reported by Alex Gaynor via email entitled "Security issue
    with memory management in Magick++" to the graphicsmagick-security
    list on 31 Jan 2018.
    (SeekBlob):

  - coders/jpeg.c (ReadIPTCProfile): Revert inadvertent wrong return
    codes added by change on December 9, 2017.  Fixes SourceForge bug
    542 "Improper call to JPEG library in state 201" since 1.3.28.

2018-02-01  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/annotate.c (RenderFreetype): Fixed the text
    opacity computation in RenderFreeType(). This bug caused
    the text fill color to bleed into the character cell when
    the SVG "fill-opacity" is less than 1.0.

2018-02-01  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - magick/attribute.c (CloneImageAttributes): Fixed a bug
    in which the source image attributes would always replace
    the destination image attributes instead of being appended
    to them, and the destination image attributes would become
    a memory leak.

2018-01-31  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - coders/svg.c (SVGStartElement): Fixed a bug in which the
    x,y location values for a <text> or <tspan> were overwritten
    by the x,y values for the next <tspan> before the previous
    values were used.  This caused the text associated with the
    previous <text> or <tspan> to appear at the location
    specified for the next <tspan>.

2018-01-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/static.c: Use !defined(SupportMagickModules) to enable
    static module loader.  Fixes SourceForge bug #543 "Multiple
    definition of "OpenModule" (etc) when cross-compiling shared".

2018-01-29  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - coders/svg.c (SVGStartElement): A terminating '>' in
    a geometry string is interpreted to mean that the dimensions
    of an image should only be changed if its width or height
    exceeds the geometry specification.  For an unapparent and
    undocumented reason, a terminating '>', if present, was
    being nulled out, making this feature unusable for SVG files
    (now fixed).

2018-01-29  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - coders/svg.c (ReadSVGImage): If there is a geometry string
    in image\_info->size (e.g., gm convert -size "50x50%" in.svg
    out.png), AllocateImage() sets image->columns and image->rows
    to the width and height values from the size string.  However,
    this makes no sense if the size string was something like
    "50x50%" (we'll get columns = rows = 50).  So we set columns
    and rows to 0 after AllocateImage(), which is the same as if
    no size string was supplied by the client.  This also results
    in svg\_info.bounds to be set to 0,0 (i.e., unknown), so that
    svg\_info.bounds will later be set using the image size
    information from either the svg "canvas" width/height or from
    the viewbox.  Later, variable "page" is set from
    svg\_info->bounds. Then the geometry string in image\_info->size
    gets applied to the (now known) "page" width and height when
    SvgStartElement() calls GetMagickGeometry(), and the intended
    result is obtained.


2018-01-24  Greg Wolfe  <gregory.wolfe@kodakalaris.com>

  - coders/svg.c (SVGStartElement): When the density (DPI)
    is specified using the ImageInfo::density member, the derived
    scale factor is incorrectly applied a second time to the
    width and height members of variable RectangleInfo page.
    Fixes SourceForge ticket #451.

2018-01-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/static.c: Use a lazy-loader for static modules with the
    same external interface as the lazy-loader for dynamic modules.

2018-01-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Prepare for 1.3.28 release.

2018-01-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update with changes since previous release.

2018-01-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/Magick.xs: Compiler warnings reduction.

  - magick/pixel\_cache.h: Mark GetPixels(), GetIndexes(), and
    GetOnePixel() as deprecated.  Compilers may produce a warning if
    these functions are used.

  - magick/pixel\_cache.c (InterpolateColor): Return black pixel if
    InterpolateViewColor() reports failure.

  - coders/png.c (ReadMNGImage): Fix memory leak of chunk and
    mng\_info in error path.

  - coders/gif.c (ReadGIFImage): Fix memory leak of global colormap.

2018-01-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/symbols.h: Fix SourceForge issue #538 "13 symbols in
    common with ImageMagick despite --enable-symbol-prefix".

  - coders/bmp.c (ReadBMPImage): Fix non-terminal loop due to
    unexpected bit-field mask value.  Fixes SourceForge issue #541
    "Infinite Loop in ReadBMPImage (coders/bmp.c)".

  - coders/jpeg.c (JPEGMessageHandler): Revert code added on
    2017-07-08 to promote certain warnings from libjpeg to errors.
    Add code to rationalize claimed image dimensions based on file
    size.  Resolves SourceForge issue #539 "Images with libjpeg
    warnings result in error".

2018-01-11  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/wpg.c Recursive ReadImage could return multiple scenes
          fixed.

2018-01-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (ReadOnePNGImage): Quit 'passes' loop if we
    encountered an error

  - magick/pixel\_cache.c (SetNexus): Fix heap overwrite in
    AcquireCacheNexus() due to SetNexus() not using an allocated
    staging area for the pixels like it should.  This problem impacts
    all 1.3.X releases.  Resolves SourceForge issues 532
    "heap-buffer-overflow bug in ReadWPGImage" and #531
    "heap-buffer-overflow in AcquireCacheNexus".

  - magick/pixel\_cache.c (InterpolateViewColor): Now returns
    MagickPassFail rather than void.  Code using this function is
    updated to check the return status.

2018-01-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/describe.c (DescribeImage): Discriminate between
    AcquireImagePixels() returning NULL or finding a transparent
    pixel.  This avoids use of a null pointer in the case where
    AcquireImagePixels() returns NULL.

2017-12-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/static.c: Change static module initialization to be based
    on an initialized list rather than a squence of function calls in
    order to simplify maintenance and possibly address future
    requirements.

2017-12-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Copyright.txt: Bump copyright years and rotate ChangeLog.
