================================
GraphicsMagick ChangeLog - 2022
================================

2022-12-30  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/pcx.c (WritePCXImage): Make default RLE compression.
    Uncompressed PCX is more rare.

2022-12-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Updated the news.

  - coders/pcx.c (WritePCXImage): Support writing uncompressed PCX
    by default.  Use -compress RLE to enable RLE compression.

  - coders/sun.c (ReadSUNImage): Sense of monochrome images was
    inverted.  Fix scanline size calculation.
    (WriteSUNImage): Sense of monochrome images was inverted.

2022-12-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pcx.c (WritePCXImage): Fix heap overflow when writing
    more than 1023 scenes, and also eliminate use of uninitialized
    memory.

  - coders/pnm.c (ReadPNMImage): Compute the number of threads to
    use.

  - NEWS.txt: Update the news.

  - magick/command.c: Add use of GetFirstImageInList() where needed
    to assure that the list pointer is to the first image.

  - magick/constitute.c (ReadImage): Only perform subimage
    processing when required.

  - magick/command.c (MogrifyImages): Restore mogrify\_images as
    first image in list since the rest of the code expects that.

2022-12-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/mat.c (ReadMATImageV4): Use ReplaceImageInList().
    (ReadMATImage): Use ReplaceImageInList().

  - magick/command.c (MogrifyImages): Remove band-aid.

  - magick/list.c (AppendImageToList): Image list is updated to be
    new image.

  - magick/image.c (AllocateImage): Initialize colors directly.
    (GetImageInfo): Initialize colors directly.

  - utilities/tests/convert-cmds.txt: Add more convert command
    permutations.

2022-12-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - version.sh: Update shared library versioning in preparation for
    1.3.39 release.

  - NEWS.txt: Updated the news.

2022-12-26 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - jp2/src/appl/jasper.c: Link problem with jasper utility fixed.

2022-12-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/gem.c (Contrast): Visual Studio 17.4.3 does not like
    initializing a static constant with "0.5+MagickEpsilon" in
    /precise mode.

  - magick/enhance.c (ContrastImagePixels): Visual Studio 17.4.3
    does not like initializing a static constant with
    "0.5+MagickEpsilon" in /precise mode.

2022-12-25 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - webp/src/webp/types.h: Need to include inttypes.h
  - jp2/src/libjasper/include/jasper/jas\_types.h:
    Fix missing \_PFX\_PTR in newer MSVC.

2022-12-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/symbols.h: Update symbol remappings which are enabled by
    PREFIX\_MAGICK\_SYMBOLS.  The only new symbol since the last release
    is IsEventLogged().

  - NEWS.txt: Updated the news.

2022-12-25 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - jp2/\*: Update lib jasper to 1.900.16.

2022-12-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Updated the news.

  - coders/jxl.c (ReadJXLImage): Request that libjxl take care of
    any pre-multiplied alpha for us so we don't need to do it

2022-12-24 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - jp2/\*: Update lib jasper to 1.900.5.

2022-12-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jxl.c: Support reading and writing ICC, EXIF, and XMP
    profiles.  Lots of code cleanup.
  - PerlMagick/t/jxl: Created some JXL sanity-test files.

2022-12-22 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/tests/runtest.bat: Make binary directory
    configurable on one place. Report error when rwblob.exe does not
    exist.

2022-12-22 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - jp2/\*: Update lib jasper from 1.900.1 to 1.900.2.

2022-12-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jxl.c (ReadJXLImage): Now based on
    ImportImagePixelArea().
    (WriteJXLImage): Now based on ExportImagePixelArea();

2022-12-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/msl.c (MSLEntityDeclaration): Report an error if
    xmlAddDocEntity() or xmlAddDtdEntity() fails.

  - coders/svg.c (SVGEntityDeclaration): Report an error if
    xmlAddDocEntity() or xmlAddDtdEntity() fails.

2022-12-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Updated the news.

  - magick/image.c (SetImageDepth): Restore is\_monochrome and
    is\_grayscale image flags.  Changing depth should not change the
    nature of 'gray'.

  - coders/jxl.c: Support reading and writing 32-bit 'float'
    images. Need a Q32 build in order to write 32-bit 'float' images.

  - fuzzing/oss-fuzz-build.sh: Remove xz --with-pic=yes option which
    now seems to annoy oss-fuzz build.

2022-12-17 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/magick/magick\_types.h.in:
    Reverting from 16859. The change in 16860 completelly breaks
    compillation.

2022-12-17 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - tiff/port/libport\_config.h: Added missing file
    Documentation of libtiff upgraded.
    Upgraded libtiff to 4.5.0.

2022-12-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/rwfile\_deep.tap: Add JXL tests for deep images.

  - coders/jxl.c: Fix grayscale writer error.  Eliminate use of
    deprecated functions.  Support 16-bits/sample.

2022-12-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pnm.c (ReadPNMImage): Do not promote gray images to
    PseudoClass unless the image dimensions make it worthwhile.

  - coders/gif.c (ReadGIFImage): Allocate cleared memory.  Remove
    two redundant memsets.

2022-12-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImages): Fix performance anomaly
    noticed with large image list.

  - coders/tiff.c (ReadTIFFImage): Move monitor for list to a better
    spot so that rows and columns are valid.

2022-12-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (png\_error): Use a macro to report exceptions
    (rather than calling libpng's png\_error()) for exceptions thrown
    from this module. This provides useful file/line information as
    well as allowing code analyzers to have a more accurate idea of
    what is going on.

  - magick/widget.c (MagickXFileBrowserWidget): Fix Coverity 382252
    "Wrong sizeof argument (SIZEOF\_MISMATCH)".

  - coders/meta.c (parse8BIM): Fix Coverity 382245 "Incorrect
    expression (SIZEOF\_MISMATCH)".
    (parse8BIMW): Fix Coverity 382250 "Incorrect expression
    (SIZEOF\_MISMATCH)".

  - magick/widget.c (MagickXNoticeWidget): Fix Coverity 382254
    "Incorrect expression (SIZEOF\_MISMATCH)."
    (MagickXFontBrowserWidget): Fix Coverity 382253 "Incorrect
    expression (SIZEOF\_MISMATCH)".
    (MagickXFileBrowserWidget): Fix Coverity 382252 "Incorrect
    expression (SIZEOF\_MISMATCH)".
    (MagickXPreferencesWidget): Fix Coverity 382251 "Incorrect
    expression (SIZEOF\_MISMATCH)".
    (MagickXConfirmWidget): Fix Coverity 382249 "Incorrect expression
    (SIZEOF\_MISMATCH)".
    (MagickXListBrowserWidget): Fix Coverity 382248 "Incorrect
    expression (SIZEOF\_MISMATCH)".
    (MagickXDialogWidget): Fix Coverity 382247 "Incorrect expression
    (SIZEOF\_MISMATCH)".
    (MagickXColorBrowserWidget): Fix Coverity 382246
    "(SIZEOF\_MISMATCH)".

  - coders/jpeg.c (WriteICCProfile): Fix Coverity 382255 "Incorrect
    expression (SIZEOF\_MISMATCH)".

  - Makefile.am (clean-local): Added a clean-local target to remove
    Coverity subdirectory ('cov-int').  Building with 'coverity'
    target leaves Coverity subdirectory in place for inspection.

  - NEWS.txt: Updated the news.

2022-12-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - utilities/tests/convert.tap: Produce more interesting 'info'
    output to 'convert.log'.

2022-12-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac (top\_srcdir\_native): Produce a substituted value
    representing the top source directory expressed suitable for the
    native operating system.  This is to support MinGW.

  - utilities/tests/convert.tap: Use ';' rather than '/' as sed
    delimiter character since '/' is a directory separator..

  - winpath.sh: Use printf rather than echo.  If an escape level is
    not provided, then output an unescaped Windows path using
    forward-slashes.

  - Magick++/lib/Color.cpp: Add Quantum casts to Color() arguments
    to solve error with unidentified compiler.  SourceForge issue #160
    "Add Quantum casts for 16-bit to Image.cpp and Color.cpp".

  - Magick++/lib/Image.cpp: Add Quantum casts to Color() arguments
    to solve error with unidentified compiler.  SourceForge issue #160
    "Add Quantum casts for 16-bit to Image.cpp and Color.cpp".

2022-12-01 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/ps2.c, coders/ps3.c, coders/tiff.c, webp/src/webp/types.h
    tiff/libtiff/: Upgraded libtiff to libtiff-4.4.0 But code is still
    compilable with MSVC2008!

2022-11-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Magick++/lib/Image.cpp: Don't just blindly return DisposeMethod
    as an 'int'.

  - Magick++/tests/attributes.cpp (main): Test with a valid GIF
    disposal method.

  - coders/msl.c (MSLStartElement): Eliminate 'undefined behavior'
    issues.

  - magick/colorspace.c (XYZTransformPackets): Use 'double' when
    performing summation and eliminate 'undefined behavior' issues.
    (RGBTransformPackets): Use 'double' when performing summation and
    eliminate 'undefined behavior' issues.

  - magick/constitute.c (ConstituteImage): Eliminate 'undefined
    behavior' issues.

  - magick/fx.c (SolarizeImage): Eliminate 'undefined behavior'
    issues.

  - magick/gem.c (Hull): Eliminate 'undefined behavior' issues.

  - configure.ac, magick/magick\_types.h.in: Added some support for
    deducing magick\_uintptr\_t and magick\_ptrdiff\_t types.

  - utilities/tests/convert-cmds.txt: Added more command
    permutations to execute.

2022-11-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/constitute.c (ConstituteImage): Fix undefined behavior:
    runtime error: applying non-zero offset 2 to null pointer

  - coders/logo.c (RegisterLOGOImage): Logo image subformats do not
    have an image extension.

  - utilities/tests/convert-cmds.txt: Add more convert tests.

  - magick/render.c (DrawPrimitive): Fix for SourceForge issue #679
    "Using "0,0" for image size throws an error in v1.3.38, worked
    previously".  This bug was added in GraphicsMagick 1.3.36.

2022-11-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c (ReadJPEGImage): Eliminate Clang Analyzer
    diagnostic. Add support for reading deep gray images.

  - magick/xwindow.c (MagickXDitherImage): Update documentation to
    add a link to an article about the HP Color Recovery algorithm.

  - coders/topol.c (ReadTOPOLImage): Eliminate Clang Analyzer
    diagnostic.

2022-11-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c (WriteJPEGImage): Useful data\_precision range is 8
    to 16.

  - magick/profile.c (ProfileImagePixels): Make sure not to use
    indexes if it is NULL.

  - magick/xwindow.c (MagickXDitherImage): Eliminate use of
    undefined behavior.  Make sure to deallocate memory upon error.

  - magick/widget.c (MagickXCommandWidget): Assure that prerequisite
    'number\_selections' is satisfied.

  - magick/xwindow.c (MagickXGetWindowImage): Assure that
    prereqisite 'colors' table for PseudoClass case is satisifed.

  - coders/png.c (ReadOnePNGImage): Make sure that background index
    is initialized.

  - magick/profile.c (ProfileImagePixels): Don't de-reference
    indexes if they were not supplied.

  - magick/widget.c (MagickXColorBrowserWidget): If mode\_info.text
    is NULL, ignore event due to user pushing mode button.

  - coders/heif.c (ReadMetadata): Also guard against profile name
    being null.

2022-11-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/wpg.c (ReadWPGImage): Fix wrong use of
    LogWPGBitmapType2() macro, and resore previous definitions.

  - VisualMagick/magick/magick\_types.h.in: Declare a ssize\_t typedef
    in VisualStudio's <magick/magick\_types.h> due to the unfortunate
    accidental use of ssize\_t in Wand's MagickExtentImage()
    declaration.  This should address SourceForge issue #673 "visual
    studio include error ssize\_t redefinition".

    Replace use of ReallocColormap() with previously existing
    ReallocateImageColormap(), which does the same thing.

  - coders/heif.c (ReadColorProfile): Support reading ICC color
    profile.

2022-11-20 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c: Reveal more internal info to optional log.

2022-11-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/t/wmf/read.t: Change reference images from MIFF
    format to GIF format to reduce wasted space.

  - PerlMagick/t/cgm/read.t: Change from read.miff to read.gif to
    reduce wasted space.

  - PerlMagick/t/x/write.t: Change from congrats.miff to
    congrats.gif to reduce wasted space.

  - coders/heif.c (ReadMetadata): If
    heif\_image\_handle\_get\_metadata\_size() returns 0, then carrying on
    with reading image data. Addresses SourceForge issue 677 "Memory
    allocation failed - HEIF" but does not discover/address why
    libheif returns a zero metadata size.

  - PerlMagick/t/subroutines.pl (testRead): Support read-options in
    order to be more flexible.

  - PerlMagick/t/read.t: Change as many tests to be signature-based
    as possible and remove now unneeded reference files.

2022-11-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/t/jpeg/read.t: Use JPEG image as reference image
    while doing Seattle FilmWorks test.

  - PerlMagick/t/read.t: Reduced distribution size by using
    signature test method for some tests.

  - PerlMagick/t/tiff/read.t: Added test for old JPEG.

2022-11-17 Fojtik Jaroslav  <JaFojtik@yandex.com>

    PerlMagick/t/input\_JPG\_old.tif: Added JPG embedded into TIFF using
    old Adobe's embedding style.

    2022-11-17 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - tiff/libtiff/tif\_ojpeg.c: Backported from 4.4.0 to 4.1.0

2022-11-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/nt\_base.h (snprintf): Add missing comma in macro.

2022-11-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/nt\_base.c (NTsnprintf): New function intended to emulate
    C'99 snprintf for MSVC older than 2015.

  - magick/nt\_base.h (snprintf): For MSVC older than 2015, fall back
    to using sprintf for the moment.

  - coders/msl.c (ProcessMSLScript): Handle parser creation failure.

  - coders/meta.c (GetIPTCStream): Assure that offset is initialized.

  - magick/floats.c (\_Gm\_convert\_fp32\_to\_fp16): Fix Clang Analyzer
    complaints.

  - magick/xwindow.c (MagickXGetWindowColor): Assure that crop\_info
    is initialized.

  - Makefile.am (scan-build): Added a scan-build target to help run
    Clang Analyzer.

  - coders/locale.c (WriteLOCALEImage): Fix Clang Analyzer
    complaints.

  - ALL: Replace strcpy() with strlcpy(), replace strcat() with
    strlcat(), replace sprintf() with snprintf().  Prefer using
    bounded string functions.

2022-11-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (ReadOnePNGImage): Change ping\_file\_depth to
    unsigned and add verifications for ping\_bit\_depth.

2022-11-09 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/fits.c: Store multiple scenes into one file.

2022-11-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (ReadOnePNGImage): More work on Coverity issue 381864.

  - magick/image-private.h (MaxValueGivenBits): Move to private header.

  - coders/xpm.c (ReadXPMImage): More work on Coverity issue 381862
    "(DEADCODE)".

  - magick/operator.c (QuantumLogCB): Fix Coverity issue 381861
    "Control flow issues (DEADCODE)".

  - coders/xpm.c (ReadXPMImage): Fix Coverity issue 381862
    "(DEADCODE)".

  - magick/operator.c (QuantumGammaCB): Fix Coverity issue 381863
    "Control flow issues (DEADCODE)".

  - coders/png.c (ReadOnePNGImage): Fix Coverity issue 381864
    "BAD\_SHIFT".

  - magick/operator.c (QuantumDepthCB): Fix Coverity issue 381867
    "Control flow issues (DEADCODE)".
    (QuantumPowCB): Fix Coverity issue 381865 "Control flow issues
    (DEADCODE)".

  - magick/import.c (ImportViewPixelArea): Fix Coverity issue 381868
    "Control flow issues (DEADCODE)".

  - magick/blob.c (DetachBlob): Do not dereference blob\_info->data
    if it is null.  Addresses Coverity issue 381869 "Null pointer
    dereferences (FORWARD\_NULL)"and issue 381866 "Null pointer
    dereferences (FORWARD\_NULL)".

  - coders/jpeg.c (FreeMagickClientData): Fix Coverity issue 381870
    and 381860 "Null pointer dereferences".

  - magick/export.c (ExportViewPixelArea): Fix Coverity issue 381871
    "Control flow issues (DEADCODE)" for the case where QuantumDepth =
    32.

2022-11-05 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c: Shrink amount of colors when palette is bigger than
    raster could store.

2022-11-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c (ReadBlobString): Fix oss-fuzz issue 53001
    "graphicsmagick:coder\_TXT\_fuzzer: Use-of-uninitialized-value in
    ReadBlobString", which occurs due a bug remaining in recent
    changes.

2022-11-04 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: Remove junk \n from log after printing footer contents.

2022-11-03  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - PerlMagick/t/input\_3chars.xpm: New testcase
    with 3 bytes encoding per one pixel.
  - PerlMagick/t/reference/read/input\_3chars\_xpm.miff,
    PerlMagick/t/read.t: Added input\_xpm\_pal16.miff to PerlMagick test
    suite.

2022-11-03 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/xpm.c: Allow to read pallete that contains more colors
    than MaxColormapSize.

2022-11-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (SetImageInfo): Avoid creating temporary files
    when reading files with .bz2, .gz, .svgz, and .Z extensions if the
    format is non-ambiguous based on the file extension, and the
    reader does not require seeking.

  - magick/magick.c (MagickToMime): Add MIME mappings for apng,
    avif, bmp, ico, and webp.

2022-10-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/xpm.c (ReadXPMImage): coders/xpm.c (ReadXPMImage): Use
    qsort+bsearch to improve performance of color-lookups.

2022-11-01  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/wpg.c: Bilevel image must be allways monochrome.
    Discard palette if exists.
  - PerlMagick/t/input1\_1.wpg,
    PerlMagick/t/reference/read/input1\_1.wpg.miff New testcase with
    bilevel monochrome image.
  - PerlMagick/t/read.t: Added input1\_1.wpg to PerlMagick test suite.

2022-10-31  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/xpm.c (ReadXPMImage): Output intelligent messag when colormap 
    exceeds limit.

2022-10-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c (ReadBlobString): Fix oss-fuzz issue 52917
    "graphicsmagick:coder\_TXT\_fuzzer: Stack-buffer-overflow in
    ReadBlobString", which occurs due to a bug added in yesterday's
    ReadBlobString() changes.

2022-10-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c (ReadBlobString): Use fgets() in order to get much
    better performance.

2022-10-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/xpm.c (ReadXPMImage): Improve read performance by using
    integer keys.  Trace the colormap.

2022-10-29  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/xpm.c (ReadXPMImage): Replace strcmp with faster memcmp.
    It improves 21% performance on my test image.

2022-10-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/xpm.c (ReadXPMImage): Eliminate unnecessary strlen() upon
    memory reallocation for better performance.

2022-10-29  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - PerlMagick/t/input\_bilevel.xpm,
    PerlMagick/t/reference/read/input\_xpm\_bilevel.miff: New testcase
    with bilevel monochrome image.
  - PerlMagick/t/read.t: Added input\_xpm\_pal16.miff to PerlMagick test
    suite.

2022-10-28  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - PerlMagick/t/input\_pal16.xpm,
    PerlMagick/t/reference/read/input\_xpm\_pal16.miff New testcase with
    16 bit palette.
  - PerlMagick/t/read.t: Added input\_xpm\_pal16.miff to PerlMagick test
    suite.

2022-10-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Updated the news.

2022-10-20  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: Remove "optimisation" that has negligible or negative
    effect to overall performance.

2022-10-19  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: Cleanup GCC compile warnings.

2022-10-17  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: Do not consider whole image to be invalid when a second
    chunk header contains invalid data.

2022-10-16  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: Renamed image attribute "comment" from extended area to
    "TGA:file.comment" to prevent mix of these 2 comments.
    (Now TGA can produce both "comment" and "TGA:file.comment").

2022-10-14  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - PerlMagick/t/read.t: Add new tests for TGA files.

2022-10-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c: Revert undocumented change to 'DPX:file.creator'
    attribute.

2022-10-13  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: Block alpha channel depending on value "AttributesType".

2022-10-12  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: New attributes "comment", "creator", "software", "TGA:file.JobName"
  - coders/gpx.c: Renamed attribute "DPX:file.creator" to "creator"

2022-10-10  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: TGA developper area is read.

2022-10-09  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: Check return code of seek blob operation.

2022-10-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c (SeekBlob): Fix SEEK\_END validation.  Addresses
    oss-fuzz 52133 "graphicsmagick:coder\_ICB\_fuzzer:
    Heap-buffer-overflow in ReadBlob".

2022-10-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - scripts/changelog2rst.sh: Try to deal with the crazy mix of
    spaces and hard tabs which are now appearing in the ChangeLog file.

2022-10-04  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: Fixed oss-fuzz-52084.
  - PerlMagick/t/input.tga: renamed to PerlMagick\t\input\_8\_CC.tga
  - PerlMagick/t/reference/read/input\_tga\_8\_BW.miff: New testcase.
  - PerlMagick/t/read.t: Added input\_tga\_8\_BW.miff to PerlMagick test
    suite.

2022-10-03  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: TGA footer is read, currently used for logs only.

2022-10-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - scripts/rst2html5.py: Fix from Mark Mitchell to deal with RST
    file local include statements when invoked from a different
    directory.  Also fix requested character set encoding.

2022-10-02 Fojtik Jaroslav  <JaFojtik@yandex.com>

  - PerlMagick/t/{input\_8\_BW\_rle.tga, input\_8\_CC\_rle.tga,
    input\_8\_BW.tga}: Added 8 bit TGA samples.

2022-10-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - scripts/rst2html5.py: Applied patch by Mark Mitchell which
    replaces rst2htmldeco.py with rst2html5.py. rst2html5.py does
    essentially the same job as rst2htmldeco.py, but in a different
    way.  docutils\_htmldeco\_writer.py is no longer used or needed.

    Also fixed thanks.rst file which had non-utf8 characters, as well
    as ChangeLog.2006, ChangeLog.2008 and ChangeLog.2012.

  - PerlMagick/t/read.t: Added input\_mono.tga to PerlMagick test
    suite.

  - coders/tga.c: White-space normalization.  Eliminate compilation
    warning about unused indexes variable.

2022-10-01  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: Monochromatic bilevel TGA could be written.

2022-09-29  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/tga.c: Monochromatic bilevel TGA could be read.

2022-09-28  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - PerlMagick/t/input\_mono.tga: Added monochromatic TGA sample generated
    by Graphics Workshop.

2022-09-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - scripts, www/Makefile.am: Fixes pertaining to use of Docutils to
    generate the HTML documentation.

2022-09-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Search for a usable Python program, and then use
    it to execute Python scripts. This avoids depending on a default
    name.

  - magick/common.h (MAGICK\_FUNC\_MALLOC\_2ARG): Add macros to support
    GCC malloc attributes which accept arguments.

2022-09-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/formats.rst: Add AVIF image file format to the list.

2022-09-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/formats.rst: Add JPEG XL to the list.

  - utilities/tests/icc-transform.tap: Preserve output files from
    icc-transform.tap until 'make clean' in order to allow inspection.

2022-09-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Disable using libxml2 in oss-fuzz
    build due to it being arbitrarily broken in the oss-fuzz build for
    several weeks with no solution offered.  Nobody seems to care any
    more.

  - coders/svg.c: Re-enable support for XML internal subset.

2022-09-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Magick++/lib/Image.cpp (Magick::Image::colorMapSize): Restore
    non-const Image::colorMapSize() since it caused an ABI change.
    Debian bug 1019158: "graphicsmagick breaks gnudatalanguage
    autopkgtest: undefined symbol: \_ZN6Magick5Image12colorMapSizeEv".

2022-09-04  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - jpeg/\*: Upgraded jpeg library to Version 9e 16-Jan-2022.

2022-09-04  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/jpeg/LIBRARY.txt: Exclude files cjpegalt.c and
    djpegalt.c; cjpeg.c and djpeg.c are already excluded.

2022-08-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Add messaging regarding building
    libxml2 and jasper.

2022-08-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Makefile.am (release): Generate ASCII armored ".asc" files
    directly since this seems to be prefered over converting from
    ".bin" files.

2022-08-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Makefile.am: Some people prefer GPG signature files in ASCII
    armored ".asc" format rather than the OpenPGP binary ".bin"
    format, so produce both.

2022-08-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Fix UTF-8 encoding errors in some text and source files.  A few
    more issues remain.  Assistance is appreciated.

2022-08-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/svg.c (ReadSVGImage): Address concern from SourceForge
    issue #669 "Segmentation fault caused by null pointer dereference
    by checking return from xmlCreatePushParserCtxt().  Address
    oss-fuzz 48340 "graphicsmagick:coder\_SVG\_fuzzer:
    Heap-use-after-free in xmlParseInternalSubset" by disabling
    internal subset handling until the parser context handling is
    fixed.

2022-08-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Updated the news.

2022-08-10  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick/configure/stdafx.h: Added define WIN32\_LEAN\_AND\_MEAN
  - VisualMagick/configure/configure.exe: New rebuild.

2022-08-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh (MAGICK\_LIBS): Add libsharpyuv.a to
    the list of libraries to check for.

2022-08-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: When checking for libwmf, add a test for
    libsharpyuv.  Not yet tested but maybe it will work.

2022-08-07  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - VisualMagick\configure\configure.cpp: The /MACHINE:x86
    should never be placed to DLL dependency list.

2022-08-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tga.c: Enhance 'coder' level trace information.
    Normalize on 'unsigned int' as much as possible in order to use
    natural types and likely help with function inligning.

2022-08-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tga.c (ReadTGAImage): Remove a defective validation of
    comment length, which blocked reading some sample TGA files from
    the "Encyclopedia Of Graphics File Formats" book.

2022-07-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/heif.c: If module is compiled, but HasHEIF is not
    defined, then RegisterHEIFImage/UnregisterHEIFImage
    implementations are empty.

  - coders/jxl.c: If module is compiled, but HasJXL is not defined,
    then RegisterJXLImage/UnregisterJXLImage implementations are
    empty.

2022-07-30  Sam James        <sam@gentoo.org>

  - configure.ac: Fix Bashism in maintainer-mode check.

2022-07-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/miff.c (ImportRLEPixels): Add missing type cast for
    consistency with other similar code.  However, I do not believe
    this is an actual bug.  Addresses GraphicsMagick bug 670 "Missing
    cast".

2022-07-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magic.c: Auto-detect JXL format based on file header.
    Much thanks to Quyen Pham Ngoc for noticing that this was missing.

2022-06-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update with news since last release.

2022-05-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Magick++/lib/Image.cpp: colorMapSize() method for returning the
    number of colormap entries should be a const method.  Change is
    due to an email from Miro Kropáček on May 29, 2022.

2022-05-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/Magick++/Image.rst: Update getIndexes() and
    getConstIndexes() documention to mention that the selected region
    is defined by a prior getPixels(), getConstPixels(), or
    setPixels() call.  This is inspired by private email from Miro
    Kropáček on May 8, 2022.

  - coders/jpeg.c (WriteJPEGImage): Change "arithmetic" to
    "arithmetic-coding" in order to match ImageMagick's previously
    existing syntax.

  - coders/png.c (ReadOnePNGImage): Assure that entire image list is
    freed. Addresses oss-fuzz 46997 "graphicsmagick:coder\_MNG\_fuzzer:
    Indirect-leak in MagickMallocCleared".  This is a new issue due to
    incrementally seeking the complete correct error-handling cleanup.

2022-05-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - doc/options.imdoc: Add documentation for -define
    jpeg:arithmetic.

2022-04-30  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - coders/jpeg.c: Optionally enable arithmetic coder in JPG images.
    gm convert -define jpeg:arithmetic=true testimg.jpg arith.jpg

2022-04-27  Fojtik Jaroslav  <JaFojtik@yandex.com>

  - jpeg/: Update aged JPG library to version 9d.

2022-04-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/ps.c (ReadPSImage): Assure that 'bounds' structure is
    initialized.

  - coders/ept.c (ReadEPTImage): Assure that 'bounds' structure is
    initialized.

  - magick/log.c (IsEventLogged): New function to report if a
    particular event will be logged.  Us this as much as possible
    throughout the software to replace use of IsEventLogging().

  - coders/png.c (ReadMNGImage): Address oss-fuzz 46913
    "graphicsmagick:coder\_WPG\_fuzzer: Indirect-leak in
    MagickMallocCleared" which was partially pre-existing and
    partially due to a botched fix for oss-fuzz 46843.

2022-04-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (ReadMNGImage): Address oss-fuzz 46843
    "graphicsmagick:enhance\_fuzzer: Heap-use-after-free in CloseBlob".

2022-04-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/{msl.c, svg.c, url.c}: When \_\_MINGW32\_\_ is defined, then
    only define \_MSC\_VER if it is not already defined.  Also define
    \_MSC\_VER with a somewhat useful value.  This change is prompted by
    a posting by "LM" to the graphicsmagick-core list on April 17,
    2022.

2022-04-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (ReadOnePNGImage): Make sure that ping\_num\_trans is
    initialized.  Fixes oss-fuzz 46760 "Use-of-uninitialized-value -
    ReadOnePNGImage".

2022-04-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c (OpenBlob): Allocate setvbuf() buffer externally
    rather than implicitly.  I am hoping that the several oss-fuzz
    reports about using uninitalized memory from glibc's
    \_IO\_file\_doallocate() go away.

2022-04-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/heif.c (RegisterHEIFImage): Support reading AVIF via
    libheif if it supports decoding AVIF.

2022-04-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/index.rst: Update the Coverity Analysis Metrics.

  - magick/display.c (MagickXAnnotateEditImage): Quiet Coverity
    376901 "Identical code for different branches
    (IDENTICAL\_BRANCHES)".

  - coders/svg.c (ReadSVGImage): Default to not allowing external
    entity substitution.  Quiets Coverity 376905
    "unsafe\_xml\_parse\_config (UNSAFE\_XML\_PARSE\_CONFIG)".

  - coders/msl.c (ProcessMSLScript): Default to not allowing
    external entity substitution.  Quiets Coverity 376913
    "unsafe\_xml\_parse\_config (UNSAFE\_XML\_PARSE\_CONFIG)".

  - magick/error.c (ThrowLoggedException): Silence Coverity 376912
    "Dereference after null check (FORWARD\_NULL)".

  - coders/jp2.c (ReadJP2Image): Silence Coverity 264883 "Division
    or modulo by float zero (DIVIDE\_BY\_ZERO)".
    (ReadJP2Image): Fix Coverity 376911 "Improper use of negative
    value (NEGATIVE\_RETURNS)".

  - magick/xwindow.c (MagickXMakeMagnifyImage): Fix Coverity 376906
    "Division or modulo by zero (DIVIDE\_BY\_ZERO)".

  - magick/resize.c (ScaleImage): Fix Coverity 376908 "Resource leak
    (RESOURCE\_LEAK)".

  - magick/locale.c (GetLocaleMessageFromTag): Fix Coverity 376907
    "Out-of-bounds read (OVERRUN)".

  - magick/render.c (DrawPrimitive): Fix Coverity 376904
    "Out-of-bounds access (OVERRUN)".

2022-03-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - version.sh: Prepare for 1.3.38 release.

  - Makefile.am (release, snapshot): Generate SHA-256 checksums as a
    by-product of 'make snapshot' or 'make release'.

  - www/download.rst: Add documentation regaring SHA-256 checksums.

  - NEWS.txt: Update the news again.

  - coders/miff.c (ReadMIFFImage): Validate claimed bzip2-compressed
    row length prior to reading data into fixed size buffer.
    Addresses SourceForge bug #664 "[bug]Heap buffer overflow when
    parsing MIFF".  This severe bug only impacts builds with BZLIB
    support.

2022-03-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jxl.c (ReadJXLImage): Added patch from Tobias Mark to
    optimize EOF detection if the input file size is known.  Avoids
    waiting for ReadBlob() to report EOF.

2022-03-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Magick++/lib/Magick++/Include.h: Support 'ReadResource'.

2022-03-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jxl.c: Added some debug logging instrumentation so we can
    see the information the JXL reader is provided by libjxl.

  - configure.ac: JXL is working well enough to enable it by
    default.

2022-03-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jxl.c (WriteJXLImage): Call JxlEncoderCloseInput() so
    that encoder output is not corrupt.  JXL passes testsuite tests
    now!

  - magick/command.c (CompareImageCommand): Add -auto-orient support
    to 'compare'.  This tries to assure that the two images are right
    side up before comparing.

2022-03-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jxl.c (WriteJXLImage): Work to update JXL writer code to
    compile clean with libjxl v0.7.0.  Still not working!

2022-02-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/heif.c (ReadHEIFImage): Pass decode options to
    heif\_decode\_image().  Include rough implementation of progress
    monitor support but leave it disabled since libheif does not
    currently invoke the callbacks.

  - coders/jpeg.c (ReadJPEGImage): Store embedded profiles in image,
    even if in 'ping' mode.  This addresses a problem discovered when
    interfacing with minimagick (Debian bug #1006374 "graphicsmagick
    breaks ruby-mini-magick").

  - coders/url.c (ReadURLImage): Deal with libxml2 not offering HTTP
    or FTP capabilities.  It seems that support for FTP has now been
    removed by default.

2022-02-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - README.txt: Recomend using JasPer 3.0.0 (or later).

  - VisualMagick/magick/magick\_config.h.in: Disable building with
    bundled JasPer sources by default since the bundled sources are
    archaic.

  - coders/jp2.c: Fix compilation with JasPer 3.0.0 (which is now
    released).

2022-02-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/fx.c (ColorizeImagePixelsCB): Apply clipping and rounding
    to handle out of range values and provide the most accurate
    result.  Addresses SourceForge bug #662 "Broken -colorize".

2022-01-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jp2.c (ReadJP2Image): Jasper 3.0.0 hid the functions we
    were using so switch back to using jas\_image\_decode(), but in a
    more secure way than before.

2022-01-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/download.rst: Document how to retrieve the PGP signing key
    from a key server.

2022-01-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jp2.c (ReadJP2Image): Always use
    ThrowJP2ReaderException().  Should address oss-fuzz Issue 43979:
    "graphicsmagick:enhance\_fuzzer: ASSERT: jas\_get\_ctx() ==
    jas\_global.ctx".

2022-01-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - utilities/tests: Write compressed MIFF files to reduce disk
    space usage.

  - magick/command.c (CompareImageCommand): Support '-compress'
    option.

  - coders/mpc.c: Fix warnings from GCC 11.

  - coders/miff.c: Fix warnings from GCC 11.

2022-01-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jp2.c: Adaptations to work with Jasper 3.0.0's
    jas\_init\_library() and other related functions.  Add missing
    jas\_cleanup\_thread().  Do not request a higher memory limit than
    JasPer's own limit in order to avoid a warning.

2022-01-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/miff.c (ReadMIFFImage): Do not proceed to next image in
    sequence unless the character read is the expected 'i' character.
    Inspired by GraphicsMagick bug #659 "Can not escape $0 in a batch
    command".

  - coders/heif.c (ReadHEIFImage): Take row stride into account when
    reading pixel rows. Add support for 'ping' mode.  Add header magic
    detection.  Add module aliases.  Add useful traces.

2022-01-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jxl.c: Added preliminary JPEG XL support written by
    Tobias Mark.  From Code Merge Request #14: "Added (basic) jpeg-xl
    support".  The writer is not working properly at this time.

  - www/formats.rst: Add HEIF to the list of supported formats.

  - README.txt: Expand the text regarding support for HEIF/HVEC
    support.

2022-01-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/heif.c: HEIF reader written by Tobias Mark.  From
    SourceForge Code Merge Request #15: "Added minimal heif support".

  - magick/blob.c (ReadBlobStream): Fix EOF logic similar to
    ReadBlob. Addresses oss-fuzz 43617
    "graphicsmagick:coder\_P7\_fuzzer: Use-of-uninitialized-value in
    WritePNMImage".

2022-01-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c (ReadBlob): Fix EOF logic. Addresses oss-fuzz
    43490 "graphicsmagick:coder\_PNM\_fuzzer: Use-of-uninitialized-value
    in SyncImageCallBack".

  - coders/pnm.c (ReadPNMImage): Make sure that we don't lose the
    image exception.

2022-01-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c: Throw a user-friendly exception when the read
    limit has been exceeded.

  - coders/jpeg.c: Add tracing and fallback for longjmp().

  - coders/pict.c (DecodeImage): Assure that the claimed scanline
    length is within the bounds of the scanline allocation to avoid
    possible heap overflow.

2022-01-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c: Make sure that read resource limiting can support
    very large files.

2022-01-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/resource.c: Add support for setting a read resource limit
    via the MAGICK\_LIMIT\_READ environment variable, or similar to
    '-limit read 5mb'.

  - magick/resource.h: Added a ReadResource limit, which is a limit
    on how many uncompressed file bytes may be read while decoding an
    input file.

2022-01-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - ChangeLog.2021: Rotate ChangeLog for 2022.  Happy New Year!
