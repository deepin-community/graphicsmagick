================================
GraphicsMagick ChangeLog
================================

2025-03-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news.

2025-03-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jxl.c (ReadJXLImage): pixel\_format.num\_channels needs to
    be 2 for grayscale matte.  Addresses oss-fuzz 406320404
    "graphicsmagick:coder\_JXL\_fuzzer: Heap-buffer-overflow in
    ImportViewPixelArea".

2025-03-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (AddIFDExifFields): Check for overflow of computed
    unsigned value. Code is only active if EXPERIMENTAL\_EXIF\_TAGS is
    true.  Addresses oss-fuzz 403696329
    "graphicsmagick:coder\_TIFF\_any\_fuzzer: Crash in LD\_UINT16\_HI".

    Reflow code to match the conventions used by the rest of the
    project.

2025-03-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Updated the news.

  - fuzzing/oss-fuzz-build.sh (CPPFLAGS): Continue to enable
    EXPERIMENTAL\_EXIF\_TAGS in oss-fuzz build in order to continue
    testing writing EXIF in TIFF format.

  - coders/tiff.c (EXPERIMENTAL\_EXIF\_TAGS): Disable
    EXPERIMENTAL\_EXIF\_TAGS by default until libtiff API weaknesses are
    resolved.

2025-03-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jp2.c (ReadJP2Image): Add casts in order to avoid
    compilation warnings with old Jasper.

2025-03-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - README.txt: Refresh README text.

2025-02-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/magick\_wand.c: Fix comment indentation issue which was
    causing some functions to not appear in the formatted
    documentation.  Thanks to Robert C. <robgcs@users.sourceforge.net>
    for reporting that documentation for some functions were missing.

2025-02-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/nt\_base.h: Update notes regarding `\_MSC\_VER` values and
    Visual C++ versions.

  - www/index.rst: Promote the Mercurial repository at
    https://foss.heptapod.net/graphicsmagick/graphicsmagick since it
    seems to work better.

2025-02-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magic.c: Make the magic-based format descriptions more
    detailed and helpful.

2025-02-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magic.c (ListMagicInfo): Include a format description in
    the output of 'gm convert -list magic'.

2025-02-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magic.c: Add a Magic description field in order to help
    identify and document format variants based on header magic.
    (GetMagickFileFormat): Trace the format description at Coder
    level.

2025-01-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (WriteOnePNGImage): Ignore exessively short ICM
    profiles.  Should address oss-fuzz 392927700
    "graphicsmagick:coder\_PNG64\_fuzzer: Heap-buffer-overflow in
    png\_write\_iCCP".

  - magick/magic.c (StaticMagic): Identify some more HEIF
    sub-formats.

  - coders/heif.c (ReadHEIFImage): Request the primary image handle
    from libheif. Do not throw an error if there is more than one
    image in the heif.  Patch by Kevin Clauson and submitted via
    SourceForge patch #84 "Patch: use primary image for heic even when
    have multiple image".

2025-01-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/heif.c (ReadMetadata): Only apply Exif orientation if
    ignore-transformations is true since HEIF native transformations
    will handle orientation otherwise.  Patch by Kevin Clauson via
    GraphicsMagick SourceForge patch #83 "Patch: Fix HEIC Orientation
    Issue".

2025-01-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/magick\_wand.c (MagickSetImagePixels): If update image has
    matte, then promote canvas image to have matte.  Support composing
    individual channels 'R', 'G', 'B', 'A', 'O', 'T', 'C', 'M', 'Y',
    'K'. Intended to address SourceForge issue #752
    "MagickResizeImage() discarding alpha values".

2025-01-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/rwfile.c: Fix another GCC warning.

2025-01-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news.

  - coders/jpeg.c (WriteJPEGImage): Properly invert CMYK components
    when writing.  Addresses SourceForge bug #751 "all CMYK colorspace
    image become black-white inverted".  This bug was introduced in
    GraphicsMagick 1.3.43. Existing files which appear "corrupt" due
    to this issue may be salvaged by using the -negate command like
    "gm convert bad-cmyk.jpg -negate good-cmyk.jpg".

  - www/INSTALL-unix.rst: Document the Docutils version necessary to
    format reStructuredText files to HTML format.

2025-01-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/wand/Makefile.am ($(WWWWANDAPIDIR)/%.apirst): Pass an
    absolute path to format\_c\_api\_doc.py --include-rst argument.

  - magick/magick\_endian.c (MagickReverseBits): Function has never
    been used for anything.  Mark it as deprecated.
    MagickGetBitRevTable(): Function has never been used for anything.
    Mark it as deprecated.

2025-01-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news.

  - Update copyright year and rotate ChangeLog.
