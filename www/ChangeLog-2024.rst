================================
GraphicsMagick ChangeLog - 2024
================================

2024-12-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/wpg.c (ReadWPGImage): Assure that palette buffer is
    allocated and the current size. Addresses SourceForge bug #750
    "heap-buffer-overflow in ReadBlob".
    Reformat white-space to be more similar to conventions used in
    the rest of the software.

2024-12-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - config/delegates.mgk.in: Use XML predefined entities
    substitutions for '&' and '<' so that the file syntax is valid
    XML.  Older/existing files using "invalid" XML continue to be
    accepted.

  - magick/delegate.c (ReadConfigureFile): Support XML predefined
    entities substitutions.

  - magick/utility.c (SubstituteString): Fix off-by-one error which
    caused back-to-back substitions to not work correctly.

2024-12-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Remove duplicate request.

  - coders/heif.c (ReadHEIFImage): Trace the top level number of
    images.

  - fuzzing/README.txt: Add notes about building libheif
    dependencies.

2024-12-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Enable 'uncompressed' in libheif
    build.

  - fuzzing/dictionaries/HEIF.dict: Add HEIF dictionary.  From
    libheif fuzzing/data/dictionary.txt.

2024-11-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Add openh264 and openjpeg for use by
    libheif.

  - magick/static.c (StaticModules): Skip registration of CMYK
    static module, which is not not useful for oss-fuzz build when
    FUZZING\_BUILD\_MODE\_UNSAFE\_FOR\_PRODUCTION is defined.  CMYK, RGB,
    and GRAY raw format coders require that image dimensions+depth are
    specified, or else they immediately return an error.  This defeats
    fuzzing given the current fuzzing driver.

2024-11-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/static.c (StaticModules): Skip registration of static
    modules which are not useful for oss-fuzz build when
    FUZZING\_BUILD\_MODE\_UNSAFE\_FOR\_PRODUCTION is defined.

  - coders/dib.c (RegisterDIBImage): Admit to supporting a "DIB"
    format in oss-fuzz build so it will be tested by oss-fuzz.  DIB is
    normally hidden from the user given that it is normally an
    embedded blob in legacy formats like WMF.

2024-11-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news.

2024-11-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - config/ltmain.sh, m4/libtool.m4, m4/ltversion.m4: Update to
    libtool 2.5.4.

  - Magick++/demo/analyze.cpp: Analyze module identifies as
    "Analyze", not "analyze". It seems that symbol resolution must
    have allowed mixed-case, but this is not supported any more under
    Ubuntu 22.04 LTS.

2024-11-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Move libheif build towards the end
    since it keeps adding more dependencies.

2024-11-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/README.txt: Add more fuzzing notes.

  - fuzzing/oss-fuzz-build.sh: Add a hack so that libx265 installs
    x265.pc.

2024-11-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/rwfile.c: Fix appending file extension.

  - coders/bmp.c (ReadBMPImage): Assure that opacity channel is
    initialized, even if matte is not true.  May help regarding
    GraphicsMagick discussion thread "Opacity of whole Magick::image
    is set to the value 205 after reading a 24-bit-bmp".

  - coders/svg.c (ReadSVGImage): Added comments.

  - magick/render.c (DrawImage): Added comments.

  - tests/rwfile.c: More fixes for GCC warnings.

2024-11-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/bitstream.c: Tidy printfs and exit status.

  - tests/bitstream.tap: Add a simple bitstream test to test suite.

2024-10-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (DrawImage): Add more validity checks for color
    database lookup requests.

2024-10-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jp2.c (ReadJP2Image): Trace JPEG 2000 component
    parameters.

  - fuzzing/oss-fuzz-build.sh: Skip re-bootstrap of GraphicsMagick
    since it sometimes fails due to network issues.
    (enable\_x265): Enable x265 in oss-fuzz build (and re-enable de265,
    which was accidentally disabled).

2024-10-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/heif.c (ReadMetadata): Address oss-fuzz issue 376100386
    "graphicsmagick:coder\_AVIF\_fuzzer: Undefined-shift in
    ReadMetadata", which is due to an unsigned char being promoted to
    a signed int prior to shifting.  The sample input file is valid.

  - TclMagick/Makefile.am (EXTRA\_DIST): Assure that all source files
    are included by 'make dist'.

2024-10-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - TclMagick/Makefile.am: Name installed TclMagick/TkMagick
    libraries similar to names generated by the TEA tcl.m4 module.
    For example, name as TclMagick0.46.so and TkMagick0.46.so.

2024-10-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/{constitute.c, rwblob.c, rwfile.c}: Eliminate ugly
    "directive output may be truncated" warnings from GCC.

  - tests/bitstream.c: Fixes so that 'test' mode allocates the
    correct amount of memory for 31 and 32 bit depth.

  - Makefile.am (coverity): Added tests programs to Coverity
    analysis.
    (scan-build): Added tests programs to Clang scan-build.

  - Magick++/lib/Image.cpp (Magick::Image::formatExpressionRef): New
    method which works the same as formatExpression, except that it
    passes the argument by reference.

  - wand/wandtest.c: Use secure buffer management.

  - tests/constitute.c: Use secure buffer management.

  - tests/rwfile.c: Use secure buffer management.

  - tests/rwblob.c: Use secure buffer management.

  - Magick++/lib/Magick++/STL.h (coderInfoList): Assure that
    exception is always thrown when 'coder\_list' is NULL.  Coverity
    446809 "Dereference after null check".

  - Magick++/lib/Exception.cpp (Magick::throwExceptionAlways): New
    exception throwing helper function which always throws an
    exception.

  - tests/bitstream.c: Check range of arguments. Coverity 446805
    "Untrusted loop bound".

  - Magick++/tests/readWriteImages.cpp (main): Report columns()
    rather than rows(). Coverity 446803 "Copy-paste error.

  - Magick++/tests/attributes.cpp: Use new
    formatExpressionRef(). Coverity 446808.

  - Magick++/lib/Image.cpp (Magick::Image::formatExpressionRef): New
    method to replace use of formatExpression(). The declaration of
    formatExpression() should have passed the argument by reference.
    Coverity 446808.

2024-10-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Magick++/tests/\*: Updated to use InitializeMagickSentinel.

  - Magick++/demo/\*: Updated to use InitializeMagickSentinel.

  - Magick++/lib/Magick++/Image.h (InitializeMagickSentinel): Added
    InitializeMagickSentinel class, which performs the function of
    InitializeMagick() and invokes DestroyMagick() when an object
    created based on it goes out of scope.

  - Magick++/lib/Image.cpp: Disable use of 'MagickCleanUp' static
    object by default because it may cause race conditions

  - fuzzing/oss-fuzz-build.sh: Set libheif
    ENABLE\_MULTITHREADING\_SUPPORT back to on.

2024-10-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Set libheif
    ENABLE\_MULTITHREADING\_SUPPORT to off to see if it causes an abort
    in std::terminate to go away.

2024-10-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/gem.c (Hull): More fixes for regression created by
    Mercurial changeset 16913:78aa63677935 "Add casts to prevent
    unnecessary value truncation in WIN64 build" on Saturday, October
    21, 2023.

  - TclMagick/generic/TclMagickAppInit.c: Refresh implementation
    based on latest code from reference tcl/unix/tclAppInit.c.

2024-10-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - TclMagick/Makefile.am: Eliminate the libttkcommon "shim" library
    which allowed TkMagick to work and use a different approach.
    TclMagick is not dependent on libtk.  Only TkMagick is dependent
    on libtk.

2024-09-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/links.rst: Update oss-fuzz bug tracker URL.

2024-09-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/gem.c (Hull): Fix regression created by Mercurial
    changeset 16913:78aa63677935 "Add casts to prevent unnecessary
    value truncation in WIN64 build" on Saturday, October 21, 2023.

  - m4, TclMagick/unix/m4: Update to libtool 2.5.3.

2024-09-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - TclMagick/Makefile.am: 'make test' does something.  Not sure yet
    what it should be.

  - TclMagick/tests/test-wand.tcl: Fix memory leak of $img and $seq.

  - TclMagick/tests/test-draw.tcl: Fix memory leak of $img.

  - generic/TclMagickAppInit.c: Add a TclMagick test program.

  - TclMagick/generic/TkMagick.c: Fix memory leak of 'fonts' and
    'formats' lists members.

2024-09-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - TclMagick/Makefile.am: Now uses non-recursive build and produces
    xz tarball.  The make 'distcheck' target is not working properly
    yet.
    (AM\_DISTCHECK\_CONFIGURE\_FLAGS): Change the argument to
    --exec-prefix so that 'make distcheck' now passes.

2024-09-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/display.c (MagickXROIImage): ThresholdCommand was missing
    from EffectsCommands list. In the Region of Interest mode the
    button command array is missing a command corresponding to
    "Threshold...", and that is also messing up all buttons further
    below.  SourceForge patch #82 "Add missing Threshold to command
    array of Region of Interest mode" by Alex Barsky.

  - TclMagick/generic/config.h.in, TclMagick/generic/libttkcommon.h:
    Support a configuration header.

  - TclMagick/configure.ac: Modernize Autoconf files.

  - TclMagick/Makefile.am: Modernize Automake files.

2024-09-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - TclMagick/generic/TclMagick.c: Fix several typos which will
    produce wrong results, as well as quieting fallthrough warnings.

2024-09-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - config/type-urw-base35-t1.mgk.in: Add a template file for the
    newer Artifex urw-base35-fonts, but for the Postscript Type 1
    fonts.  This is not integrated into the build and no substitutions
    are performed on it.

2024-09-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - config/type-urw-base35-otf.mgk.in: Changes for the newer Artifex
    urw-base35-fonts, which now support OpenType fonts, and use long
    file names.  Specifically configure the location using the
    --with-urwbase35otf-font-dir configure option.  This is in
    response to Debian bug 1019717 "Display of an SVG file broken due
    to gsfonts transition",
    https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=1019717.

2024-09-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Validate legacy Ghostscript font file in
    Ghostscript install directory before deciding to use it as the
    Ghostscript font directory.

2024-09-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jxl.c (ReadJXLImage): Apply image dimension resource
    limits. Addresses oss-fuzz Issue 69728:
    "graphicsmagick:coder\_TIFF\_any\_fuzzer: Out-of-memory in
    coder\_TIFF\_any\_fuzzer".

2024-09-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - doc/options.imdoc: Further updates to color specification
    documentation, based on what the current code is
    doing. Unfortunately, current behavior deviates from CSS3 in some
    aspects.

  - fuzzing/oss-fuzz-build.sh: Libtiff build now requires
    autoconf-archive

2024-09-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - doc/options.imdoc: Remove mention of RRRRGGGGBBBBAAAA due to an
    interpretation conflict which causes it to not be supported.  Add
    documentation for 32-bit variants.  Addresses SourceForge issue
    #747 "#RRRGGGBBBAAA and #RRRRGGGGBBBB color names conflict".

2024-09-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - TclMagick/: White-space clean-up and consistent indentation.

2024-09-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - TclMagick/unix/m4/tcl.m4: Update tcl.m4 to TEA\_VERSION 3.10.
    The TEA\_INSTALLER Autoconf macro oddly does not use the settings
    set by AC\_CONFIG\_AUX\_DIR to find install-sh.  Instead it
    hard-codes $(srcdir)/tclconfig/install-sh.  Change that hard-coded
    path to $(top\_srcdir)/unix/config/install-sh.

  - TclMagick/generic/pkgIndex.tcl: Remove generated file.

  - TclMagick/generic: Regenerate Autotool's generated files with
    autoconf 2.71 and automake 1.16.5.

2024-08-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/index.rst, www/Changes.rst: 1.3.45 is released in 2024.

  - version.sh: Updates in preparation for the 1.3.45 release.

2024-08-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news.

2024-08-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/fpx.c: Coverity fixes for "dead code" and an integer
    overflow issue.

  - magick/image.c (MagickParseSubImageSpecification): Fix
    SourceForge issue "#746 Off-by-one-error when converting PDF with
    multiple pages". Also add additional sanity checking.
    Unfortunately, this is a regression added in the 1.3.44 release.

2024-08-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/Changes.rst: 1.3.44 is released in 2024.

  - version.sh: Updates in preparation for the 1.3.44 release.

  - magick/symbols.h: Update 'Gm' prefixed symbols.

2024-08-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news.

2024-08-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (GetImageInfo): Change the default for ImageInfo
    'progress' to False.  This parameter is used by 'animate' and
    'display'.  It was discovered that under Ubuntu 22.04 LTS, the
    progress indication in 'animate' and 'display' has changed from
    almost no cost, to taking vastly more time than the work to be
    performed!  As a result, there will be no graphical progress
    indication in the X11 commands unless this resource is set to
    True.  ImageMagick had already removed this progress indication.
    The -monitor option will cause progress output to stderr.

2024-08-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/docutils-articles.css: reStructuredText style sheet
    adjustments to work with HTML 4 and 5 synax, by Mark Mitchell.

  - www/docutils-api.css: reStructuredText style sheet adjustments
    for HTML 5, by Mark Mitchell.

  - tests/rwfile.tap: Adjustments for FlashPIX tests.

  - coders/fpx.c: Add tracing and attempt to reduce the amount of
    memory which is leaked by the defective library.

  - coders/hrz.c: Tidy and clarify code.

2024-08-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac, coders/dps.c: Display Postscript stopped being
    available after Sun Solaris 10 (if legacy Xsun was used rather
    than Xorg) and has been substantially gone from the world for a
    long time already since Oracle stopped supporting desktop systems
    not long after acquiring Sun in 2010.  Remove support for Display
    Postscript. Ghostscript works better since it supports multiple
    pages whereas Display Postscript only supported one page.

  - config/{config.guess,config.sub}: Re-bootstrap with latest
    config.guess and config.sub.

2024-08-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news.

  - www/index.rst (https): Update Coverity statistics.  Add mention
    of how ImageMagick has now removed classic utilities such as
    'convert'.

  - www/INSTALL-windows.rst: Add a note regarding problems building
    UTIL\_IMDisplay in some free Visual Studio versions, and how to fix
    it.

  - www/contribute.rst: Add another idea for contributing to
    GraphicsMagick.

2024-07-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Remove defunct LIB\_GS variable.

  - coders/dib.c (ReadDIBImage): Eliminate GCC 14 warning.

  - coders/bmp.c (ReadBMPImage): Eliminate GCC 14 warning.

2024-07-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Add LIB\_FPX and LIB\_GS back into the LIBS
    list. LIB\_FPX was commented out long ago, but it seems that LIB\_GS
    was accidentally dropped within the past year during the big
    re-write to depend more on pkg-config.  These changes are due to
    SourceForge issue #745 "missing fpx library during linking".

2024-07-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c (MagickMaxFileSystemBlockSize): Place an artibrary
    limit on maximum filesystem block size.

  - coders/Makefile.am (MAGICK\_ORA\_MODULES): ORA module is dependent
    on HasLIBZIP.

2024-07-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImage): Change utility '-depth N' to a
    simple image depth attribute assignment rather than also being an
    image processing operation.  Obtain the previous result (which
    immediately modified the image pixels) using '-operator All Depth
    N'.  Most users use -depth in order to influence the bits/sample
    of the file being written rather than as an intermediate image
    processing operation.

  - magick/floats.c (\_Gm\_convert\_fp32\_to\_fp24): Coverity fixes for
    arithmetic overflow in mantissa related code.

2024-07-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Added support for building libzip.

2024-07-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/display.c (MagickXROIImage): Fix clang-analyzer issue.

  - magick/delegate.c (ListDelegateInfo): Fix clang-analyzer issue.

  - magick/command.c (TimeImageCommand): Fix clang-analyzer issue.

2024-07-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (MagickParseSubImageSpecification): Quiet
    Coverity 427451 "Overflowed constant".

  - magick/analyze.c (MinimumDepthForValue): Fix loop bounds and
    avoid overflow of the return value.  Addresses Coverity 427448
    "Overflowed constant".

2024-07-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/drawing\_wand.c (DrawGetStrokeDashArray): Avoid integer
    underflow in loop. Addresses Coverity 427450 "Overflowed
    constant."

  - magick/draw.c (DrawGetStrokeDashArray): Avoid integer underflow
    in loop. Addresses Coverity 427460 "Overflowed constant".

2024-07-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (InitializeImageColormap): Verify that
    TIFFTAG\_BITSPERSAMPLE is within a rational range.

  - coders/gif.c (ReadGIFImage): Don't evaluate background color if
    image->colors == 0.  Coverity did not detect that previous error
    handling would already have caught this issue.

  - coders/pnm.c (PNMInteger): Code simplification, and convince
    Coverity that value returned by ReadBlobByte() is positive if it
    is not EOF.

  - coders/txt.c (ReadInt): Convince Coverity that value returned by
    ReadBlobByte() is positive if it is not EOF.

  - coders/sct.c (ReadSCTImage): Convince Coverity that value
    returned by ReadBlobByte() is positive if it is not EOF.

  - coders/png.c (ReadMNGImage): Eliminate warning: variable
    'loops\_active' set but not used".

  - coders/pcd.c (DecodeImage): Eliminate "warning: variable 'count'
    set but not used".

  - magick/color.c (IsPaletteImage): Eliminate "warning: variable
    'index' set but not used".

2024-07-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/fits.c (ReadFITSImage): Report an error if FITS frames
    have zero dimensions or contain no pixels.  Addresses core issue
    which resulted in oss-fuzz issue 69925:
    "graphicsmagick:coder\_TIFF\_any\_fuzzer: Floating-point-exception in
    WriteTIFFImage".

  - www/INSTALL-unix.rst: Remove mention of the original MinGW which
    became dead and unusable at OSDN a couple of years ago.  It is not
    even possible to download the installer program.  The old version
    at SourceForge is all which remains working.

2024-07-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Assume that targets matching \*-w64-mingw\* are
    capable of supporting 'C99 printf syntax.
    (INT64\_F, UINT64\_F, MAGICK\_SIZE\_T\_F, MAGICK\_SSIZE\_T\_F): Try to
    intuit better MinGW printf syntax based on host\_vendor setting.

  - wand/pixel\_wand.c (ClonePixelWands): Eliminate GCC 14
    warning about MagickAllocateArray() argument order.

  - magick/magick.c (GetMagickInfoArray): Eliminate GCC 14
    warning about MagickAllocateArray() argument order.

  - magick/colormap.c (ReplaceImageColormap): Eliminate GCC 14
    warning about MagickAllocateArray() argument order.

  - wand/pixel\_wand.c (PixelSetQuantumColor): Color argument is now
    a const pointer.
  - wand/pixel\_wand.c Tidy and correct errors in the documentation
    text.

2024-06-28 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - magick/tiff.c: Possible division by 0 fixed.

2024-06-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/INSTALL-unix.rst: Add mention of --without-libzip.

  - README.txt: Add a section for libzip.

  - configure.ac: Add pkg-config support for libzip.

  - coders/tiff.c (WriteTIFFImage): Report an error if input image
    is not valid.

  - www/formats.rst: Add an entry for HRZ format.

2024-06-26  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - configure.ac: Typo fixed in library name.

2024-06-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/wpg.c (ReadWPGImage): Quiet Coverity 427434 "Overflowed
    constant".

  - magick/blob.c (CloseBlob): Quiet Coverity 427439 "Data race
    condition".

  - coders/topol.c (CheckFName): Addess Coverity 427449 "Overflowed
    array index read".

  - magick/blob.c (DetachBlob): Fix location of assert.  Quiet
    Coverity 427429 "Data race condition".
    (DestroyBlob): Quiet Coverity 427446 "Data race condition".

  - magick/magick.c (GetMagickInfoArray): Address Coverity 427435
    "Data race condition".

2024-06-24  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/configure/configure.exe: Needs to be updated,
    because header files are hardcoded in it :(.
  - VisualMagick/configure/configure.cpp: dependency to core\_rl\_zlib\_.lib
    is also configured in C source code - too bad!

  - coders/ora.c: Remove library include hack. Configure.exe should
    do the job.

2024-06-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/static.c: Also need to enable ORA for HasLIBZIP

  - coders/ora.c: Change back to POSIX file format. Fix syntax
    errors so code compiles with libzip.

2024-06-23  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - zlib/contrib/minizip/unzip.c
    zlib/contrib/minizip/unzip.h: Export unzip API
    to DLL calls.

  - coders/Makefile.am: Add dependency to zlib for
    ORA DLL module.

  - coders/ora.c: This version is prepared for Linux
    using libzip.lib.

  - configure.ac: Look for presence of libzip.

  - VisualMagick/configure/configure.cpp: dependency
    to zlib is configured in C source code - too bad!

  - coders/Makefile.am: Missing reference to ora.c.

2024-06-22  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/zlib/LIBRARY.txt: Remove unwanted
    source files from DLL build ioapi.c, iowin32.c,
    miniunz.c, minizip.c, mztools.c, zip.c.

2024-06-16  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/aai.c: Misleading typo fix.

2024-06-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: When testing for libxml2, also test
    libxml/xmlversion.h and libxml/xmlmemory.h.

  - coders/url.c: Depend on <libxml/xmlversion.h>. Use
    LIBXML\_HTTP\_ENABLED and LIBXML\_FTP\_ENABLED.

2024-06-15  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/magick/magick\_config.h.in: Add HasUNZIP.
  - coders/ora.c: Include "contrib/minizip/unzip.h" only
    when HasUNZIP is defined.

2024-06-14  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/ora.c: Add dependency to HasUNZIP.

  - VisualMagick/zlib/contrib/minizip/LIBRARY.txt:

  - VisualMagick/zlib/contrib/LIBRARY.txt:
    Add zlib/contrib/minizip/unzip.c to build.

2024-06-13  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/ora.c: Add a new ORA format reader.
  - PerlMagick/t/input.ora: Added input sample of Open Raster.
    https://en.wikipedia.org/wiki/OpenRaster

2024-06-12  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/tests/runtest.bat: Added test for AAI,
    removed duplicate test for AVS.

2024-06-11  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Log occurancy of SRATIONAL.

2024-06-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/Makefile.am: Add support for building AAI module.

  - coders/aai.c: Tidy.

2024-06-10  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/aai.c coders/avs.c: Both width and height variables
    should be unsigned.

2024-06-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/formats.rst: Add AAI to the list of formats.

  - tests/rwblob.tap: Add sanity tests for AAI format.

  - tests/rwfile.tap: Add sanity tests for AAI format.

  - coders/Makefile.am (MAGICK\_CODER\_SRCS): Add coders/aai.c.

2024-06-10  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/aai.c: Documentation lies, the format is not RGBA,
    but BGRA: https://dune-hd.com/support/misc/AAImageGen-README.txt

  - magick/symbols.h: Add symbols for AAI module.

2024-06-09  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/aai.c: Add implementation of AAI reader.

  - PerlMagick/t/input.aai: Added a new image sample.
    Verified with https://www.vertopal.com/

2024-06-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jxl.c (ReadJXLImage): Require that color channel depth
    and alpha channel depth be the same since we don't support the
    case where they are different.  Should address oss-fuzz issue
    69469: "graphicsmagick:coder\_JXL\_fuzzer: Heap-buffer-overflow in
    ImportViewPixelArea".

2024-06-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Add a coder\_TIFF\_any\_fuzzer which
    auto-detects the input format but writes to TIFF.

  - fuzzing/coder\_fuzzer.cc (LLVMFuzzerTestOneInput): Update to be
    able to disable forced read format.

2024-06-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Assure that oss-fuzz provided CFLAGS
    and CXXFLAGS are used, avoiding excess optimization.

  - coders/jpeg.c (FormatJPEGSamplingFactors): Properly handle the
    number of samples for each colorspace. Addresses oss-fuzz 68737:
    "graphicsmagick:coder\_DCM\_fuzzer: Use-of-uninitialized-value in
    ReadJPEGImage".

2024-05-26  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: Set affinity of UndefinedOrientation to
    TopLeftOrientation as recommended from Alex Kent Hajnal.

2024-05-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/Magick.xs, PerlMagick/t/subroutines.pl, www/perl.rst:
    Add AccessDefinition(), AddDefinition(), AddDefinitions(), and
    RemoveDefinitions() methods to supporting adding, updating,
    removing definitions.  SourceForge patch #81 "Adds PerlMagick
    support for AddDefinition(), et al." authored by Alex Kent Hajnal.

2024-05-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh (EXTRA\_LIBS): Assure that the
    EXTRA\_LIBS shell variable is initialized.

2024-05-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Fix 'undefined' sanitizer linkage
    error. Disable building libx265 until the problem that its package
    config file has now gone missing is addressed.

2024-05-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/{bmp.c,jxl.c,mat.c,tga.c,tiff.c,topol.c,wpg.c}: Remove
    C++ comments from C code and change whitespace to use only spaces.

2024-05-16  Fojtik Jaroslav  <JaFojtik@yandex.com>
  - coders/tiff.c: TIFFTAG\_INKNAMES should have a first parameter of
    the type uint16\_t.
    profile\_lenght has been incorrectly decreased.

2024-05-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/utility.c (ExpandFilenames): Address Coverity 425853:
    "Resource leaks (RESOURCE\_LEAK) Variable "filelist" going out of
    scope leaks the storage it points to.".

2024-05-15  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tiff.c: Fixed problem with overflowing IFD.
    https://sourceforge.net/p/graphicsmagick/bugs/738/
    Fixed another parameter need for TIFFSetField/TIFFTAG\_INKNAMES.
    https://sourceforge.net/p/graphicsmagick/bugs/739/

2024-05-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jbig.c (ReadJBIGImage): Coder log when creating colormap.

  - fuzzing/oss-fuzz-build.sh: Disable assembler code when building
    xz in order to avoid false issues.

2024-05-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/txt.c (ReadTXTImage): Assure that row array allocation is
    initialized since it may not be completely filled. Should address
    oss-fuzz 68716: "graphicsmagick:coder\_TXT\_fuzzer:
    Use-of-uninitialized-value in GetColorTuple".

2024-05-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Magick++/lib/Magick++/STL.h: I changed my mind and have decided
    to stop using the deprecated std::unary\_function in C++'11.
    Hopefully this does not cause any ABI or other usage issues.
    Please make me aware of any side-effects resulting from this
    change.

2024-04-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/contribute.rst: Remove mention of needing a formal
    maintainer for the Gentoo Linux GraphicsMagick ebuild, since there
    has been an excellent maintainer for a long time already.

  - configure.ac: Remove use of wrong == syntax. Much thanks to Sam
    James for the patch.

2024-04-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - doc/options.imdoc: Update the documentation regarding WebP exact
    mode, and the new --version option.

  - coders/webp.c (WriteWEBPImage): Add support for '-define
    webp:exact=true' to preserve exact RGB values under transparent
    areas while writing WebP format.  Enable this automatically when
    lossless is enabled.  If lossless is enabled, this option may be
    used to disable exact mode.  Addresses SourceForge issue #737
    "WebP: Colors not preserved in fully-transparent areas".

2024-04-12  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/png.c: Reveal opacity presence.

  - magick/describe.c: Reveal opacity presence.

2024-04-11  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: Write correctly TGA with opacity values in palette.

2024-04-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/module\_aliases.h: Only include module alias when there
    is a module to support it.

  - magick/deprecate.c: Add a comment about magick monitor constant
    string specification deprecations.

  - magick/command.c: Reduce relocations.

2024-04-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tga.c: Fix Coverity issues 424688 and 424689, which are
    due to inconsistent use of LogMagickEvent().

2024-03-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - utilities/tests/version.tap: New test script to exercise version
    output.

  - utilities/tests/help.tap: Skip 'batch' help since its help
    output contains TAP syntax, which confuses the test.

  - magick/command.c: Add support for a --version option, which
    produces GNU style summary version output.

2024-03-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/version.h.in: Copyright year is 2024!

2024-03-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/t/{read.t, write.t}: Update expected TGA signatures.

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
