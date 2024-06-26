
2009-12-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/unix\_port.c (MagickSpawnVP): Remove unneeded new line
    character in error message format.

  - Magick++/Makefile.am: Allow Magick++ to be built as a shared
    library under MinGW and Cygwin.  This requires a modern GCC in
    order for C++ exceptions to work.

  - utilities/tests/annotate.sh: MSYS is garbeling up draw command
    so use a command file rather than using command line.

  - coders/{fits.c,meta.c,locale.c}: Fix benign warnings noticed
    under Cygwin 1.7.

  - magick/{constitute.c,resource.c,utility.c}: Fix benign warnings
    noticed under Cygwin 1.7.

2009-12-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/module.c (DestroyModuleInfo): If the Jasper library is
    used, then we can't invoke lt\_dlexit() because this unloads the
    Jasper library and Jasper sometimes registers an atexit() cleanup
    handler.  Unfortunately, this may annoy memory leak checkers.

  - coders/jp2.c: Defer Jasper initialization to point of use.

2009-12-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/magick\_wand.c (MagickCdlImage): New method to apply the ASC
    CDL to an image.
    (MagickHaldClutImage): New method to apply a Hald CLUT to an image.

2009-12-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/studio.h atof(), atoi(), and atol() are legacy functions
    which might not be thread safe, might not enforce reasonable
    limits, and should not be used for new code.  So we implement them
    via strtod() and strtol().

2009-12-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/magick\_wand.c (MagickGetImageBoundingBox): New method to
    return the crop bounding box required to remove any solid-color
    border from the image.
    (MagickGetImageFuzz/MagickSetImageFuzz): New methods to get and
    set the color comparison fuzz factor

  - wand/pixel\_wand.c (ClonePixelWand): New method to deep-copy an
    existing pixel wand.
    (ClonePixelWands): New method to deep-copy an array of existing
    pixel wands.

  - wand/magick\_wand.c (MagickSetResolution): New method to set the
    wand resolution.  This one also works before the image has been
    read (unlike MagickSetImageResolution()).
    (MagickSetResolutionUnits): New method to set the wand resolution
    units.  Use in conjunction with MagickSetResolution().  This one
    also works before the image has been read (unlike
    MagickSetImageUnits()).

2009-12-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Magick++/demo/demo.cpp (main): Stop using deprecated functions.

  - wand/drawtest.c: Stop using deprecated functions.

2009-12-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/module.c (ModuleAliases): J2C is supported by the JP2
    coder.

  - coders/jp2.c: JP2 is now an alias for JPC since many files use
    that extension.  Problem reported by Stefano Acerbetti.

2009-12-09  Glenn Randers-Pehrson <glennrp@simple....>

  - coders/png.c: The png8 encoder would fail when trying to write
    a 1-color image.  Problem reported by Bob Clark.

2009-12-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Define \_GNU\_SOURCE and \_NETBSD\_SOURCE so that
    pwrite() and pread() prototypes are available under GNU Linux and
    NetBSD.

  - coders/tiff.c: Warnings reduction.

  - magick/widget.c: Warnings reduction.

  - magick/segment.c (Classify): Warnings reduction.

  - magick/magic.c (struct StaticMagic): Length and offset can never
    be negative so use an unsigned type rather than size\_t.

  - magick/render.c (TracePath): Fix access one beyond the end of
    the points array.

2009-11-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/gem.c (GetOptimalKernelWidth1D, GetOptimalKernelWidth2D):
    In the Q32 build, convolution kernel size was estimated
    incorrectly for large sigmas on 32-bit systems due to arithmetic
    overflow.

2009-11-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/effect.c (ConvolveImage): Moved here from fx.c since this
    is a more suitable place for it to be.

  - magick/enhance.c (GammaImage): Improve performance a bit.
    Preserve full precision in Q32 build.

2009-11-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/{channel.c,constitute.c,nt\_base.h}: Start using the C'99
    `restrict` keyword.

2009-11-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/magick\_wand.c (MagickGetImageAttribute): New method to get
    an image attribute.  Patch contributed by Mikko Koppanen.
    (MagickSetImageAttribute): New method to set an image attribute.
    Patch contributed by Mikko Koppanen.

  - magick/constitute.c (ReadImage): Log subimage and subrange.

  - configure: Update to Autoconf 2.65.

  - magick/attribute.c (GenerateIPTCAttribute): Returned IPTC string
    values were one character too short.

2009-11-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (AllocateImage): The documented shorthand for
    specifying image size via filename[WIDTHxHEIGHT] was not working
    for raw formats which use the image tile\_info data.

2009-11-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (ParseSubImageSpecification): Try to match
    behavior of previous sub-image specification parser.  Some
    incantations did not produce the same results.

  - win2k/IMDisplay/res/{IMDisplay.ico, IMDisplayDoc.ico}: Replaced
    with GraphicsMagick icon prepared by Jaroslav Fojtik.

  - coders/svg.c (ReadSVGImage): Use runtime initialization of
    SAXModules rather than static initialization.

  - magick/command.c: Commands now support reading an image from
    stdin in conjunction with a subrange specification (e.g. "-[1]").
    Problem was reported by Mario Becroft.

  - magick/common.h: New header file to incorporate the common bits
    shared by studio.h and api.h.

  - ltdl/ltdl.c: Update libltdl to 2.2.6b in order to fix security
    issue.  Resolves CVE-2009-3736 as it pertains to GraphicsMagick.

2009-11-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/constitute.c (ConstituteImage, DispatchImage): `A` and
    `T` should indicate transparency and `O` should indicate opacity.
    Behavior was inconsistent.  In some cases `O` meant transparency
    while in other cases it meant opacity. Also, in a few cases, matte
    was not getting enabled in the image as it should.  Problems were
    reported by Scott Kuhl.

2009-11-10  Glenn Randers-Pehrson <glennrp@simple....>

  - coders/png.c: Also suppress new pedantic warnings from most
    older libpng-1.4.0 betas.

  - coders/png.c: Added a warning when attempting to use libpng-1.4beta
    older than 1.4.0beta67.

2009-11-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImage): Only invoke ProfileImage() if
    an ICC CMS transform is to be performed.  Otherwise invoke
    SetImageProfile() to add the new profile.

  - magick/profile.c (ProfileImage): Improve logging messages.

  - coders/tiff.c (ReadTIFFImage): Allow CIELAB TIFF to be read.

  - coders/jpeg.c (ReadJPEGImage): Detect and apply colorspaces
    appropriately for ITU FAX JPEG.

2009-11-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tiff: Updated to libtiff 3.9.2.

2009-11-08  Glenn Randers-Pehrson <glennrp@simple....>

  - coders/png.c: Suppress new pedantic warnings from libpng
    version 1.2.41 and 1.4.0 and later.

2009-11-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - doc/options.imdoc: Document difference between -recolor and
    Adobe Flash color matrix.

2009-11-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImageCommand): Convolve does not accept
    an argument which looks like a geometry.  Resolves SourceForge
    issue #2890923 "Different handling of -convolve between convert
    and mogrify".
    (MogrifyImage): Validate that user-provided matrix is square when
    parsing -convolve and -recolor commands in order to avoid a core
    dump.

  - coders/tiff.c (ReadTIFFImage): Improved/added more coder logging
    statements.

  - magick/xwindow.c: Reflowed some code and comments.

  - magick/utility.c (SetClientName): Default client name does need
    to be "Magick", so original value is restored.

  - coders/mpc.c (ReadMPCImage): is\_monochrome and is\_grayscale
    flags were not managed properly for the MPC coder.

2009-10-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c (ReadJPEGImage): Added jpeg:block-smoothing and
    jpeg:fancy-upsampling defines to control these JPEG library
    options.

  - magick/image.c (SetImageInfo): Fix lockup due to hanging in loop
    while parsing malformed sub-image specification (SourceForge issue
    2886560).  Also fixes the ability to pass the image size via the
    filename specification like "myfile.jpg[640x480]" rather than
    needing to use -size.

  - coders/jpeg.c (ReadJPEGImage): Fix image scaling when used with
    IJG JPEG library version 7.

2009-10-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/resource.c: Added support for a "Threads" limit, which
    specifies how many threads may be used.  Note that if
    omp\_set\_nested(true) is used, GCC's GOMP seems to replicate this
    number of threads for each level of threading rather than sharing
    the specified number of threads across all teams.  For example,
    specifying four threads leads to sixteen active threads with
    omp\_set\_nested(true) and nested threading.  This GOMP behavior
    does not seem to cause any harm.
    (GetMagickResourceLimit): New accessor function to retrieve the
    maximum limit for a resource.

  - magick/module.c (ReadModuleConfigureFile): Default set of module
    aliases is now statically initialized.  The modules.mgk file is
    now optional and can be used to support adding more modules, or
    diverting existing format support to a user-provided module.

  - magick/magick.c (DestroyMagick): Document that this function
    should be invoked from the program's primary thread after any
    threads using GraphicsMagick have terminated.
    (GetMagickInfo): Was thread safe for access but not properly
    thread safe during initialization.  Is now fully thread safe.
    (InitializeMagick): Fully initialize everything needed to
    read/write files.  Document that this function MUST be invoked
    from the program's primary thread prior to using any other
    GraphicsMagick functions.

  - magick/color\_lookup.c (ReadColorConfigureFile): The colors.mgk
    is now optional so don't throw an exception if it is not found.

  - magick/semaphore.c (AcquireSemaphoreInfo): Deprecated this
    internal function.  Use AllocateSemaphoreInfo() and
    LockSemaphoreInfo() instead.
    (LiberateSemaphoreInfo): Deprecated this internal function.  Use
    UnlockSemaphoreInfo() instead.

2009-10-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - config/colors.mgk: Colors.mkg is now empty since it is used to
    modify or extend the built-in color lookup table.

  - magick/{constitute.c,delegate.c,log.c,magic.c,magick.c,tempfile.c}:
    Explicitly initialize semaphores via InitializeMagick().

  - magick/type.h: New header file to contain types and function
    prototypes for functions in type.c.

  - magick/color\_lookup.c (ReadColorConfigureFile): Store RGB color
    table in a static struct.  Entries in the colors.mgk file are now
    used to modify statically-defined entries, or add new definitions
    to the color table.

2009-10-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: --enable-libtool-verbose configure option is no
    longer needed now that we have silent build capability.

2009-10-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/attribute.c (GenerateEXIFAttribute): Add support for
    retrieving GPS EXIF attributes.  Based on work contributed by
    Jukka Manner.

  - Magick++/lib/STL.cpp, Magick++/lib/Magick++/STL.h (shadeImage):
    ShadeImage was the result of a botched cut-and-paste.  Corrected
    now.  Thanks to Jukka Manner for making me aware of this.

2009-10-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/analyze.c: New source file to contain image analysis
    functions.  Moved functions from image.c and color.c to this file.

  - magick/color\_lookup.c: New source file to contain color lookup
    functions.  Moved associated functions from color.c to this file.

  - magick/ImageMagick.rc: Remove inclusion of magic.mgk.

  - magick/utility.c (MagickRoundUpStringLength): Use a bit less
    memory.

  - magick/color.c: Use most efficient string allocation function.

  - config/Makefile.am: Eliminate use of magic.mgk.

  - magick/magic.c: Store file header magic data in a static struct.

2009-10-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/describe.c (DescribeImage): Include composition operator
    in verbose output.  Also use CompressionTypeToString() to convert
    a compression enum to a string.

2009-10-11  Toby Thain  <qu1j0t3@users.sourceforge.net>

  - coders/psd.c: Further fix for 2783535 reported by Daniel Kirsch.
    Omit 0x0 layers from the image list, or they break compositing.

2009-10-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/xwindow.c: Check for overflow on all array allocations.

  - magick/command.c (MogrifyImages): If there is only one image in
    the list, then -flatten does nothing at all.

  - magick/transform.c (FlattenImages): If the user provides only
    one image then return a clone of that image rather than reporting
    an error.

  - magick/texture.c (TextureImage): If an under-texture is applied,
    then remove the matte channel.

  - magick/xwindow.c (MagickXMakeImage): Apply a checkerboard
    pattern when displaying non-opaque TrueColor images.  Fix a second
    integer overflow issue related to CVE-2009-1882.

2009-10-10  Toby Thain  <qu1j0t3@users.sourceforge.net>

  - coders/psd.c: Fix for 2783535 reported by Daniel Kirsch. PSD
    parser was confused by 0x0 pixel layers, resulting in image data
    corruption of all following layers.

2009-10-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/xwindow.c (MagickXMakeImage): Fix for CVE-2009-1882
    "Integer overflow in the XMakeImage function".  The problem is
    that the shared memory segment allocated may be smaller than the
    image size requires due to integer overflow.  On some systems it
    may be possible to crash GraphicsMagick (while displaying an image
    file) but not likely to overwrite the heap since shared memory
    segments are outside of the heap allocation.

  - magick/memory.c (MagickMallocArray): Use MagickArraySize().

  - magick/memory.c (MagickArraySize): New private function to
    compute the size of an array and return zero if it overflows the
    size\_t type.

2009-10-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dcm.c (ReadDCMImage): Handle (UN)known type VRs correctly
    and interpret the transfer syntax correctly.  Added define
    "dcm:avoid-scaling" to request that the coder should not scale
    image samples unless necessary (i.e. when bits used > quantum
    depth or maximum colormap depth, depending on image type).  Work
    is contributed by John Sergeant.

2009-10-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/Makefile.am (CHECK\_PDF\_FILE\_COMPRESS): Add PDF tests with
    the various compression options.

  - coders/pdf.c (WritePDFImage): If the input file used JPEG
    compression and has not been converted to a bilevel or palette
    image, then use JPEG compression with original settings.  Problem
    was reported by Marco Atzeri.

2009-10-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - config/modules.mgk: DCRAW module entries were missing.

  - coders/tiff.c (WriteGROUP4RAWImage): Was not working properly on
    big-endian CPUs with libtiff 1.4.

  - coders/ps2.c (WritePS2Image): Use ImageToJPEGBlob().

  - coders/ps3.c (WritePS3Image): Use ImageToJPEGBlob().

  - coders/pdf.c (WritePDFImage): Decouple from libtiff.  Use ImageToJPEGBlob().

  - coders/dcraw.c (RegisterDCRAWImage): Needed to register module
    name.

  - coders/cals.c (ReadCALSImage): Fix bug in CALS reader which
    caused reading images taller than the image width to fail with an
    error.

  - magick/utility.c (AcquireString): Minor optimizations.
    (AllocateString): Minor optimizations.
    (CloneString): Minor optimizations.
    (LocaleCompare): Minor optimizations.
    (SubstituteString): Re-implemented in a more compact way which
    might avoid some reallocations.

  - magick/magick.c (ListModuleMap): Don't crash if `module` was not
    set.

  - magick/delegate.c (ListDelegateInfo): Fix insignificant memory
    leak.

  - magick/compress.c (ImageToJPEGBlob): Preserve JPEG settings if
    feasable.

2009-09-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pdf.c (WritePDFImage): Use ImageToHuffman2DBlob() and
    ImageToJPEGBlob().

  - coders/cals.c (WriteCALSImage): Use ImageToHuffman2DBlob().

  - magick/compress.c (ImageToHuffman2DBlob): New private
    convenience function to produce a CCIT Group4 blob.
    (ImageToJPEGBlob): New private convenience function to produce a
    JPEG blob.

2009-09-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jp2.c (ReadJP2Image): Fix scaling problem noticed when
    reading 12-bit JP2 format.  Problem was reported by Steve Shaw.
    (WriteJP2Image): Support writing JP2 files with arbitrary depth
    ranging from 2 to 16 rather than just 8 or 16.

2009-09-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/unix\_port.c (MagickGetMMUPageSize): Cache returned page
    size to eliminated repeated system calls.

  - magick/operator.c (QuantumOperatorRegionImage): Fix missing
    percent in progress monitor message.

2009-09-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/meta.c (GetIPTCStream): Should return IPTC block length
    rather than remaining blob length.  Patch submitted by John
    Sergeant.

2009-09-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/meta.c (GetIPTCStream): IPTC blobs should be padded to an
    even size.  Patch submitted by John Sergeant.

2009-09-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteGROUP4RAWImage): Added a GROUP4RAW encoder.

  - coders/cals.c (Huffman2DEncodeImage): Fix test failures when
    doing I/O to an in-memory blob.

  - coders/pcl.c (WritePCLImage): Use a different control code to
    (hopefully) eject the page.  Patch submitted by John Sergeant.

2009-09-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/Makefile.am: Add CALS tests.  Skip testing deep images for
    most formats which don't support deep images.

  - coders/cals.c: CALS module was not being built under Windows
    with MSVC.  Now it is.

  - VisualMagick/configure/configure.cpp (process\_library): CALS
    module is dependent on TIFF library.

  - coders/cals.c (WriteCALSImage): Allow CALS writing at any time,
    but only enable CALS reader if libtiff is present at build time.

  - coders/{cals.c,pdf.c,ps2.c,ps3.c} (Huffman2DEncodeImage): Force
    TIFF image type to bilevel type.

  - config/modules.mgk, VisualMagick/bin/modules.mkg: CAL-->CALS
    rather than CALS-->CAL.

2009-09-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/benchmarks.rst: Updated GraphicsMagick vs ImageMagick
    benchmark results.

2009-09-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/cals.c (WriteCALSImage): Initial CALS Type 1 writer
    implementation.  Contributed by John Sergeant.

  - coders/png.c (ReadOnePNGImage): Fresh pixels should be set using
    SetImagePixels().

2009-09-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/msl.c, doc/conjure.imdoc: Add support for a new `profile`
    command in MSL/conjure which applies, adds, or removes one or more
    IPTC, ICC or generic profiles from a file.  Work contributed by
    John Sergeant.

2009-09-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/nt\_base.c (NTGhostscriptFind): Make sure we close the
    registry key.  Log any Windows error messages.

  - magick/profile.c (AppendImageProfile): New function to add or
    append a profile.  If the profile already exists, then the data
    provided is appended to it.

  - coders/jpeg.c (ReadGenericProfile,ReadICCProfile,ReadIPTCProfile):
    Profile chunks need to be concatenated.  Otherwise "chunked"
    profiles become corrupted.

2009-09-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/average.c (AverageImages): Moved from image.c to new
    average.c file.

  - magick/colormap.h (VerifyColormapIndex): Moved here from color.h

  - magick/colormap.c (AllocateImageColormap): Moved from image.c to
    new colormap.c source file.
    (CycleColormapImage): Moved from image.c.
    (ReplaceImageColormap): Moved from image.c.
    (SortColormapByIntensity): Moved from image.c.
    (MagickConstrainColormapIndex): Moved here from color.c.

  - magick/describe.c (DescribeImage): Moved from image.c to new
    describe.c source file.

  - magick/plasma.c (PlasmaImage): Moved from image.c to new
    plasma.c source file.

  - magick/statistics.c (GetImageStatistics): Moved from image.c to
    new statistics.c source file.

  - magick/gradient.c (GradientImage): Moved from image.c to new
    gradient.c source file.

  - magick/texture.c (ConstituteTextureImage,TextureImage): Moved to
    new texture.c source file.

  - coders/svg.c (ENABLE\_SVG\_WRITER): Disable SVG writer by default
    since it usually does not work correctly and is unlikely to work
    correctly any time soon.

2009-09-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/profile.c (ProfileImage): GlobExpression is case
    sensitive so assure that its glob strings are always upper-cased.
    Without this fix, lower-cased arguments like "icm" would fail to
    be removed.  This would not be much of a problem except that the
    documentation claims that lower-case works.
    (SetImageProfile): Assure that profile names are upper-cased.

  - magick/fx.c (ColorMatrixImage): Add opaque opacity channel if
    image currently lacks an opacity channel but the matrix updates
    the opacity channel.  Requested by Kerry Panchoo.

2009-09-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/meta.c (GetIPTCStream): Updates from John.Sergeant to fix
    issues with IPTC record 2 blocks and to deal better with IPTC
    embedded in an 8BIM profile.

  - PerlMagick/t/read.t: Added tests for Topol format.

2009-09-12 Fojtik Jaroslav  <JaFojtik@seznam.cz>
  - coders/topol.c: Pallette overflow fixed for subtype 3.

2009-09-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - utilities/tests/msl\_composite.sh: Use a draw command file for
    this test script too.

  - utilities/tests/{black-threshold.sh,draw.sh,recolor.sh,
    white-threshold.sh}: MSYS is sometimes wreaking havoc on arguments
    with spaces in them so use work-arounds.

2009-09-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/nt\_base.c (NTGhostscriptFind): Improve logging messages
    when searching for Ghostscript.

2009-09-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.c (CacheInfo): Add read\_only member to
    indicate if cache is allowed to be modified.
    (ModifyCache): Clone cache if origin cache is read only.
    (PersistCache): Persistent caches which are attached are treated
    as read-only.  This avoids crash with MPC images which are read
    and subsequently modified.
    Reverted pixel cache locking changes which were made yesterday
    since I decided that they were too risky until file handle
    management is addressed.

2009-09-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/resource.c (InitializeMagickResources): Increase
    operating system file handle limits if necessary.

  - magick/pixel\_cache.c: Pixel cache file locking is now done at
    point of access.

  - magick/nt\_base.c (NTGhostscriptFind): New function to find
    Ghostscript under Windows, replacing previous Ghostgum
    implementation.

  - Copyright.txt: License is now based on MIT license exactly,
    without extra edits.  Ghostgum code has been eliminated so it is
    no longer necessary to include its license.

2009-09-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/delegate.c (GetPostscriptDelegateInfo): Add a gs-palette
    delegate entry in order to force Ghostscript to output a
    colormapped image if `-type palette` is specified prior to the
    input filename.  Ghostscript's dithering is much courser than
    GraphicsMagick's -colors default (more similar to
    -ordered-dither), but it is fast and produces smaller intermediate
    files.

  - coders/ps.c (ReadPSImage): Eliminate use of NULL pointer when
    progress monitor is enabled.  Was referring to image->filename
    rather than image\_info->filename as it should have.

  - magick/delegate.c (InvokePostscriptDelegate): Added an
    `exception` argument so that failure details can be returned.
    Tried to reorganize the code so that it is more tolerant of errors
    such as a dynamically-loadable DLL failing to load.  On POSIX
    systems, Ghostscript was not being invoked as securely as
    expected.

  - coders/Makefile.am: Only build the DPS module if the Display
    Postscript library is available.

  - coders/ept.c (ReadEPTImage): If we don`t have the Display
    Postscript library, then don't try to use it as a fallback.

  - coders/ps.c (ReadPSImage): If we don't have the Display
    Postscript library, then don't try to use it as a fallback.

  - magick/blob.c (CloseBlob): If blob was never allocated, then
    don't try to close it.

2009-09-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/index.rst: Mention 1.2.8 release.

2009-09-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Magick++: New Image methods cdl(), colorMatrix(), and haldClut()
    added.

2009-09-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/shear.c (IntegralRotateImage): Select tile sizes in a
    more intelligent fashion.

  - magick/pixel\_cache.c (GetPixelCacheInCore): New private pixel
    cache method to see if image pixels are in core.

2009-09-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/constitute.c (ReadImage): No longer clear the exception
    at the start of ReadImage() and other similar functions.  If the
    user of the function cares, she can clear the exception in
    advance.  It is not right to overwrite exceptions which might not
    have been reported/handled yet.

  - magick/shear.c (IntegralRotateImage): Rotate by zero degrees
    does not need to do any work.

  - coders/\*.c, magick/\*.c: Include image dimensions in progress
    monitor output when loading or saving a file.  Eliminate redundant
    text from progress messages.

2009-08-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/wmf.c: Eliminate memory leaks.

  - magick/render.c (DrawDashPolygon): Avoid access beyond end of
    array.  Resolves SourceForge issue 2832125 "Crash on SVG
    conversion".

  - coders/png.c (ReadOnePNGImage): Ensure that opacity channel is
    properly initialized.  Resolves SourceForge issue 2831240
    "Possible alpha channel issue with PNG w/palette and tRNS".

2009-08-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/nt\_base.h (HAVE\_TIFFSWABARRAYOFTRIPLES): Need to define
    this since libtiff includes this function now.

  - VisualMagick/tiff/libtiff/tiffconf.h.in: Enable all the options
    by default.

  - tiff: Updated to libtiff 3.9.1.  3.9.0 was broken.

2009-08-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/profile.c (MagickFreeCMSTransform): Add a CMS transform
    destructor since otherwise Visual Studio does not like it.

  - tiff: Updated to libtiff 3.9.0.

2009-08-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (TimeImageCommand): Add a simple `time`
    sub-command to time the execution of any other GraphicsMagick
    sub-command.  Similar in concept to the `benchmark` sub-command
    but produces output similar to the `time` command offered by the
    zsh command shell.  Handy for when `time` is not available, or
    consistent output is desired.

  - magick/magick.c (MagickGetFileSystemBlockSize): New private
    function to allow getting desired filesystem block size.
    (MagickSetFileSystemBlockSize): New private function to allow
    setting desired filesystem block size.

  - magick/pixel\_cache.c (WriteCacheIndexes, WriteCachePixels):
    Temporarily disable pixel cache row coalescing when writing to
    disk until we come up with a good way to optimize write sizes.

  - coders/meta.c (ReadMETAImage): Fix memory leak of profile blob.

2009-08-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - utilities/tests/icc-transform.sh: Add a sanity-test for applying
    ICC profiles.

  - magick/profile.c (ProfileImage): Improve OpenMP performance.

2009-08-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (DrawPolygonPrimitive): Drawing of points,
    lines, and polygons is now accelerated using OpenMP with good
    speed-up.

2009-08-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/drawing\_wand.c (DrawClearException): New function to clear
    drawing wand exception.
    (DrawGetException): New function to retrieve information regarding
    the last drawing wand exception (if any).
    (DrawRender): DrawRender() is now deprecated since it requires an
    Image pointer to be embedded in the drawing wand.  The image
    passed is subsequently lost by CloneDrawingWand() since it must
    clone the image using copy-on-write.  Subsequent use of
    DrawRender() on a cloned wand scribbles on an image the user does
    not have access to.  Use existing Wand function MagickDrawImage()
    instead.
    (DrawAllocateWand): DrawAllocateWand() is now deprecated since it
    requires passing an Image pointer into the drawing wand.  Use
    existing DrawingWand function NewDrawingWand() instead.

2009-08-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/drawing\_wand.c (CloneDrawingWand): New function to
    deep-copy a drawing wand.
    (NewDrawingWand): Use a boolean flag to track if image is
    allocated by the wand, or by the user.  Most of the previous
    DrawAllocateWand() code is moved into NewDrawingWand() so that the
    boolean flag is easy to manage.

2009-08-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): Support writing grayscale
    JPEG-compressed TIFF.

2009-08-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Don't override the photometric
    for grayscale JPEG-compressed TIFF.

2009-08-08  Glenn Randers-Pehrson <glennrp@simple....>

  - coders/png.c: Made compatible with libpng-1.4.0beta74 and later
    (won't work with libpng-1.4.0beta35 through beta73) due to change
    in names of png\_struct members "trans" and "trans\_values"). 

2009-08-08 Fojtik Jaroslav  <JaFojtik@seznam.cz>
  - coders/topol.c: Pallette is ignored for subtype 5 (RGB).

2009-08-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/{cineon.c, dpx.c, locale.c, svg.c}, magick/{attribute.c,
    effect.c, utility.c}: Eliminate warnings reported by GCC 4.4.0.

2009-07-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Try to be more insistent about compilation failure
    if libjpeg version is less than 6b.  IRIX compiler only warns
    about #error preprocessor statement.

2009-07-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/magick\_wand.c (MagickSetCompressionQuality): New Wand
    method to allow setting the compression quality.

2009-07-29 Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/topol.c: Fixed missing break. Added response to ping.

2009-07-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pcx.c (ReadPCXImage): Detect improper rows, columns, or
    depth.  Fixes CVE-2008-1097 "Memory corruption in ImageMagick's
    PCX coder".

  - configure.ac: Update to Autoconf 2.64.

2009-07-25 Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/topol.c: Fixed several issues. Added possibility to read
    TopoL level 2 images.

2009-07-25 Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - VisualMagick\configure\configure.cpp: Fixed library absolute path issue.

2009-07-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/random.c (DestroyMagickRandomGenerator): Trick to free
    thread specific random kernel contexts simply locks up with MSVC's
    OpenMP, so remove this functionality.

2009-07-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/random.c (DestroyMagickRandomGenerator): Cleanup thread
    specific random kernel data.

  - magick/tsd.c (MagickTsdKeyCreate): Fix glitch when built without
    any threads support.

2009-07-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/benchmarks.rst: Update GraphicsMagick vs ImageMagick image
    processing benchmark results.

2009-07-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/OpenMP.rst: Update performance measurements for readily
    available systems.

  - NEWS.txt: Updated to reflect latest changes.

2009-07-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - png: Updated libpng to 1.2.38.

2009-07-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (GetImageInfo): Default interlace for ImageInfo
    is now UndefinedInterlace so that it is possible to preserve the
    original interlace setting for the image file.  Code depending on
    the previous default setting of NoInterlace is adjusted to suit.
    This is a potentially risky change given the brittle nature of
    some of the legacy code.

  - coders/tiff.c (ReadTIFFImage): Stripped reader needs to read
    planar TIFF plane-wise in order to work with libtiff's internal
    buffering.
    (ReadTIFFImage): Tiled reader needs to read planar TIFF plane-wise
    in order to work with libtiff's internal buffering.
    (WriteTIFFImage): Tiled writer needs to output planar TIFF
    plane-wise in order to work with libtiff's internal buffering.

2009-07-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MontageUsage): Reconcile montage help output
    with actual montage options.

2009-07-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): Allow the user to be able to
    specify rows\_per\_strip when using JPEG compression.  The
    rows\_per\_strip value rounded up to the nearest multiple of 16.

2009-07-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): Add the ability for the user to
    manually specify the predictor using syntax like `-define
    tiff:predictor=2`.

2009-07-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/quantize.c (QuantizeImages): Avoid crash when using
    -monitor +map on an image list.

  - magick/command.c (BenchmarkImageCommand): Send benchmark report
    to stderr so that it does not interfer with pipes.

  - magick/cdl.c (CdlQuantum): Add range limiting of value before
    applying power function.

  - coders/dpx.c (ReadDPXImage, WriteDPXImage): Using floating point
    calculations when building sample value lookup tables in order to
    decrease error.  In particular input values were being scaled too
    low, resulting in improperly rounding down during processing of
    the image.

2009-07-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pdf.c (WritePDFImage): Incorporated updates from John
    Sergeant to remove the font and thumbnail objects from PDF output.

2009-07-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/cdl.c (CdlImage): New function to apply an ASC CDL
    transform to the image.  Original implementation by Clément Follet
    from Workflowers but considerably re-worked by Bob Friesenhahn.
    Available as -asc-cdl via the `convert` and `mogrify` subcommands.

2009-07-04 Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - www/formats.rst: MAT module can read compressed files.
    Remove warning about unsupported compression.

2009-07-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dcm.c: Eliminate compiler warnings.

2009-07-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dcm.c: Significant re-write of the DICOM reader.  Work
    contributed by John Sergeant.

2009-07-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c (OpenBlob): Subsequent research shows that Direct
    I/O will not be useful to ordinary file I/O due to specific
    requirements for buffer alignments and I/O sizes.  Support for
    requesting it is removed.

2009-07-01  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - www/formats.rst: ART module has writer for more than year.
    So mark this here.

2009-06-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac, magick/blob.c: Add experimental Solaris direct I/O
    support which is enabled by setting the environment variable
    MAGICK\_DIRECTIO to TRUE.  Direct I/O bypasses the filesystem
    cache.  Only works for NFS and UFS, and not for ZFS.

2009-06-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - rungm.sh.in: Fix environment variable issues noticed while
    running the test suite under MinGW.

  - Makefile.am (TESTS\_ENVIRONMENT): Fix environment variable issues
    noticed while running the test suite under MinGW.

  - magick/hclut.c (HaldClutImage): Don't convert Cineon Log to RGB.

2009-06-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImageCommand): Cache mogrify argument
    images so that they are only loaded once when mogrify is used to
    process multiple image files.

  - coders/dpx.c (WriteDPXImage): Fix leak of chroma image when
    subsampling to 4:2:2.

2009-06-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/utility.c (ExpandFilenames): Expand @filename to a list
    of arguments.

2009-06-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImageCommand): Fix memory leak of
    output\_directory string buffer, if it was used.

  - magick/utility.c (ExpandFilenames): Input wildcard file
    specifications with a subdirectory component such as
    "subdir/\*.dpx" were not working.

2009-06-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magick.c (InitializeMagick): Invoke InitializeMagickRegistry().

  - magick/registry.c (RegistryInfo): There is no reason to expose
    the RegistryInfo structure in the public interface so it is moved
    to registry.c.
    (InitializeMagickRegistry): Add a function for initializing the
    magick registry.

2009-06-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (CompareImageCommand): Report full error rather
    than rounded error in error reports since sometimes the value
    reported was rounded down to zero.

  - utilities/tests/hald-clut-transform.sh: New test to verify that
    Hald CLUT interpolation is working perfectly.

  - utilities/tests/hald-clut-identity.sh: Renamed from
    hald-clut.sh.

2009-06-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c (RegisterJPEGImage): Fix typo which caused IJG
    library version to be shown for "JPG" format but not for "JPEG".
    Also use a more descriptive name for JPEG library.

  - magick/image.c (DescribeImage): Filter out spurious EXIF
    attributes which already exist because we previously accessed
    them.  We do a full EXIF dump later.

2009-06-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/FAQ.rst: Add a FAQ about how to process many files at once.

2009-06-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Reduce usage of deprecated Autoconf macros.

  - coders/jpeg.c (ReadJPEGImage): Set image orientation from EXIF
    Orientation tag if it is present.

  - www/formats.rst: Add TopoL format as per Jaroslav Fojtik.

2009-06-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: User provided LDFLAGS was being overwritten under
    Solaris.
  - Many files: Additional reduction of shadowing warnings.

2009-06-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImage): Fix leak of the entire mask
    image supplied via -mask.

  - utilities/tests/mask.sh: Add a test for applying a mask image
    with -mask.

2009-06-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/attribute.c (GenerateEXIFAttribute): Identify unknown
    tags via their four-character hex value.

  - magick/colorspace.c (CMYKToRGBTransform): Use symbolic notation
    to access pixel quantum values.

  - utilities/tests/identify.sh: Added a test for `identify
    -verbose` on a well-populated JPEG file.

  - PerlMagick/t/{jpeg/write.t, jng/read.t, jng/write.t}: Relax
    allowed error for JPEG-related tests.

  - magick/attribute.c (GenerateEXIFAttribute): Attribute allocation
    size was too small causing overrun of memory buffer.  Problem was
    added on 2009-06-08.

  - magick/image.c (AllocateDepthMap): Allocation size was one
    element too small.
    (GetImageDepth): Forgot to free depth map.  Memory leak of 64K
    bytes per iteration.

2009-06-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/{mat.c, miff.c, pdf.c, ps3.c}: Have Zlib use our memory
    allocators.

  - magick/memory.c (MagickMallocCleared): New memory allocation
    interface which is similar to MagickMalloc() except that returned
    memory has been cleared first.

  - magick/hclut.c (HaldClutImagePixels): Fix wrong accesses
    detected by valgrind.  Also improve execution performance.

  - coders/xwd.c (WriteXWDImage): Fixed valgrind memcheck complaint
    about access to uninitialized data.

2009-06-09  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/txt.c Handle alpha channel for ImageMagick's alternative .txt

2009-06-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (WriteDPXImage): Fixed valgrind memcheck complaint
    about access to uninitialized data.

  - magick/attribute.c (GenerateEXIFAttribute): For EXIF STRING,
    output unprintable characters using three-digit octal notation.

  - coders/dpx.c (WriteDPXImage): Assure that offset count is
    correct according to reported bytes written.

  - utilities/tests/hald-clut.sh: Add a simple identity test for the
    Hald CLUT support.

2009-06-07  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/txt.c Handle alpha channel for ImageMagick's .txt

2009-06-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/hclut.c (HaldClutImage): Add a Hald CLUT capability as
    described at http://www.quelsolaar.com/technology/clut.html.  This
    allows a color transformation to be easily created and replicated
    on any number of images.  The algorithm is accessed by the
    -hald-clut option of `convert` and `mogrify`.  The original
    algorithm is by Eskil Steenberg and was adapted for GraphicsMagick
    by Clément Follet from Workflowers with support from Cédric
    Lejeune of Workflowers.

2009-06-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/utility.c (GetMagickGeometry): Support `^` modifier to
    geometry specification which indicates that specified size is a
    minimum bounding box rather than a maximum bounding box while
    preserving the image aspect ratio.

2009-06-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/resource.c (ListMagickResourceInfo): If supporting
    OpenMP, then include a "Threads" limit in the output of `-list
    resource`.

  - coders/pnm.c (ReadPNMImage): Fix multi-thread issue detected by
    valgrind's helgrind tool.  Diminish compilation warnings.

  - coders/dpx.c (ReadDPXImage): Diminish compilation warnings.

  - magick/random.c (AcquireMagickRandomKernel): Fix potential
    multi-thread issue detected by valgrind's helgrind tool.

  - magick/magick.c (InitializeMagick): Semaphore subsystem needs to be
    initialized before anything which uses it.

  - magick/semaphore.c (InitializeSemaphore): Since we are using
    PTHREAD\_MUTEX\_INITIALIZER to initialize primary POSIX mutex in the
    semaphore subsystem, we should not explicitly initialize the
    semaphore a second time.

  - magick/segment.c (Classify): Fix multi-thread issue detected by
    valgrind's helgrind tool.

  - magick/render.c (DrawAffineImage): Use InterpolateViewColor() to
    evalute a bi-linear interpolated point rather than obtaining a
    pixel value from a close pixel.  This provides better results.

2009-06-02  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/txt.c Attempt to handle alpha channel.

2009-06-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.c (InterpolateViewColor, InterpolateColor):
    Moved from gem.c.  Gem functions should not be accessing the pixel
    cache.

2009-06-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (CompareImageCommand): Add a -maximum-error
    option to `compare` so that it can easily be used in boolean logic
    when comparing images.

2009-05-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/Makefile.am (TESTS\_XFAIL\_TESTS): If Ghostscript is not
    available then XFAIL the tests which depend on it.

  - magick/pixel\_cache.c (GetCacheInfo): Assure that allocated
    stuctures do not occupy the same cache lines.

2009-05-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/studio.h (MAGICK\_CACHE\_LINE\_SIZE): Allow cache line size
    to be set in one place in case we want to configure for it later.

  - magick/effect.c (AllocateMedianList): Assure that allocated
    stuctures do not occupy the same cache lines.

  - magick/random.c (AcquireMagickRandomKernel): Assure that
    allocated random kernels do not occupy the same cache lines.

  - magick/gem.c (GenerateDifferentialNoise): User is required to
    supply random kernel.

  - doc/options.imdoc: Document -format "%p".  Problem was reported
    by Stijn Sanders.

2009-05-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/Makefile.am (coders\_tiff\_la\_LIBADD): Libtiff may now also
    depend on libjbig and the math library.

  - doc/gmdoc2html: Fix link to ball.png.  Problem was reported by
    Wes Fox.

  - VisualMagick/installer/inc/files-documentation.isx: Include Wand
    API documentation.

  - VisualMagick/installer/inc/icons-associate.isx: Fix Windows
    Start menu link to web pages.

  - configure.ac: --with-perl is changed to --without-perl since
    building PerlMagick is no longer the default.  Building PerlMagick
    automatically has caused too many problems.

  - PerlMagick/Makefile.am: GraphicsMagick no longer automatically
    installs PerlMagick.  Use the procedure described by
    PerlMagick/README.txt to build and install PerlMagick.

2009-05-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Debian stores Ghostscript fonts under
    /usr/share/fonts/type1/gsfonts so check there for fonts.  Issue
    reported by Ralf Wildenhues.

2009-05-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/Magick.xs: Fix Ping of blob.

  - PerlMagick/t/ping.t: Added tests for pinging files and blobs.

  - www/perl.rst: Ping blob syntax is like $image->Ping(blob=>@blob).

  - PerlMagick/Makefile.PL.in: Increase the probability of
    PerlMagick build success by using the user-specified C compiler as
    the linker if the C compiler was already used as the linker.  This
    helps if the C compiler used to build GraphicsMagick is a more
    recent vintage than the one used to build Perl.

  - PerlMagick/t/wmf/read.t: Test needs to be more lenient for
    Linux.

  - Makefile.am (TESTS\_ENVIRONMENT): Pass a complete text
    environment so that we don't need to execute rungm.sh in order to
    run the test suite.

2009-05-25  Ralf Wildenhues  <Ralf.Wildenhues@gmx.de>

  - version.sh: Define PACKAGE\_STRING.

2009-05-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/tempfile.c (ComposeTemporaryFileName): Use new random
    number generator.

  - magick/random.c: Implement a random number generation system
    based on George Marsaglia's multiply-with-carry generator.
    Somewhat slower than rand() but produces better random numbers
    with a period >2^60.  Suggested by Mark Mitchell.

2009-05-24  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/txt.c Small optimization:

    Before: 2000 iter 34.08s user 34.24s total 58.420 iter/s

    After: 2000 iter 21.55s user 21.76s total 91.891 iter/s

2009-05-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Makefile.am (XFAIL\_TESTS): Handle the case where FreeType is not
    available by marking tests dependent on FreeType as XFAIL.
    (TESTS): Reorder TESTS so that there will be no trailing spaces
    since this confuses certain older versions of GNU make.

2009-05-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/tempfile.c (ComposeTemporaryFileName): Use simpler code
    (suggested by Mark Mitchell) to compute the substitution index.
    (AcquireTemporaryFileDescriptor): Try harder to generate a
    successful temporary file and fall through to alternative
    implementations if the first does not succeed.

  - magick/magick.c (InitializeMagick): Use MagickRandNewSeed() to
    seed the default random number generator.

  - magick/utility.c (MagickRandNewSeed): Include PID in random
    number seed generation.

2009-05-22  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/txt.c Fixed char vs int parameter problem.
    Better detection of too dark 16bit or 32bit images.

2009-05-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Makefile.am (AUTOMAKE\_OPTIONS): Enable parallel-tests and
    color-tests options.  Parallel test execution does not pass tests
    yet.

  - PerlMagick/PerlMagickCheck.sh.in: Run PerlMagick tests via a
    normal check script rather than a check hook.

  - coders/identity.c (ReadIdentityImage): Fix compilation with Sun
    compiler.

2009-05-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/rwfile.c: Allow the user to specify the basename for
    temporary files.

  - tests/Makefile.am: Add a set of TXT read/write tests.  Pass the
    file name specification to use for the rwfile-based tests.

2009-05-21  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/txt.c Fixed endian set to native endian.

2009-05-20  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/txt.c Faster read ImageMagick files.
    Removed BImgBuff=NULL;

2009-05-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/txt.c (WriteTXTImage): Ensure that image depth is 8, 16,
    or 32.

  - www/formats.rst: Add CALS to formats list.

  - coders/cals.c (RegisterCALSImage): Consolidate duplicate text
    strings.

2009-05-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/cals.c: Add support for reading CALS type 1 format.
    Contributed by John Sergeant.

  - coders/identity.c: New coder to return a Hald identity CLUT
    image.

2009-05-19  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/txt.c Ability to read back Q32 txt files.

2009-05-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Support Linux style silent build rules.

2009-05-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Makefile.am: Updated to Automake 1.11.

2009-05-17  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/txt.c First attempt to read back txt file.
    It is amazingly ineffective, but it seems to work.

2009-05-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/resize.c (HorizontalFilter, VerticalFilter): When
    resizing a non-opaque image, attenuate the influence of
    surrounding colors based on their degree of transparency in order
    to avoid "halos" around objects caused by colors which are
    transparent and therefore not part of the visible image.  Patch
    contributed by Pavel Merdin via SourceForge Tracker #2792322.
    (VerticalFilter, VerticalFilter): Additional clean-up and
    optimizations.

2009-05-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImage): Added a -recolor command option
    to provide access to ColorMatrixImage().

  - magick/fx.c (ColorMatrixImage): New function to apply a color
    matrix similar to Adobe Flash Flash.filters.colorMatrixFilter(),
    and Windows GDI+ ColorMatrix class, (order up to 5x5) to the image
    pixels.

2009-05-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/perl.rst: Add missing PerlMagick debug event types.

  - coders/pcl.c: Major improvements from John Sergeant.  These
    include: 1) Fixed 2 bit output where Max=BLACK - this always
    produced negative images even when -negate was passed as a
    parameter. The code now uses a two element palette to handle this
    situation.  2) Added support for 8 bit pseudoclass images.  3)
    Changed the coder to allow adjoin, placing each sub-image on a new
    page.  4) Added support for compression. Any compression other
    than "None" will cause the coder to to try to calculate and pick
    the best out of the PCL set of RLE, Tiff RLE or delta compression
    on a per row basis, as well as handling repeated rows and zero
    rows intelligently.

2009-05-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - utilities/Makefile.am (MAGICKPROGRAMS): Add a `compare`
    ImageMagick compatibility link.

  - INSTALL-unix.txt: Apply patch regarding GnuWin32 from John Wye,
    SourceForge #2779009.

2009-05-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Add the LDFLAGS option -Wl,-zlazyload when using
    the Solaris linker.

2009-05-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/url.c (ReadURLImage): Fix typos.

2009-05-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/utility.c (SystemCommand): Added access confirmation
    checks for external commands.

  - magick/unix\_port.c (MagickSpawnVP): Added access confirmation
    checks for external commands.

  - coders/url.c (ReadURLImage): Added access confirmation checks
    for URLs.

  - magick/blob.c: Added access confirmation checks for files.

  - magick/confirm\_access.c (MagickConfirmAccess): Added an access
    confirmation facility to allow the API user to monitor and/or
    block access to files and URLs.  This allows the API user to
    implement a security policy based on actual accesses.

2009-05-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - png: Updated libpng to 1.2.35.

  - lcms: Updated lcms to 1.18a.

2009-05-01  Glenn Randers-Pehrson <glennrp@simple....>

  - coders/png.c (WriteOnePNGImage and WriteOneJNGImage): Changed
    internal attribute png\_bit\_depth to png:bit-depth-written to avoid
    confusion with planned new public png:bit-depth attribute.

2009-04-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImages): Deal slightly better with the
    case when MogrifyImage() expands one image into several.  Still
    don't know of a sane way to deal with -crop WIDTHxHEIGHT.

  - magick/transform.c (TransformImage): Image which is updated may
    be a list so account for that.

  - configure.ac: Add a test for the `restrict` keyword so that
    eventually we can use it.

  - coders/jpeg.c (ReadJPEGImage): Tidy JPEG reader by moving JPEG
    properties analysis code into subroutines.

2009-04-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - doc/display.imdoc: Fix documentation for crop and chop keyboard
    accelerators.  Fixes SourceForge bug #2593388 "error in the
    documentation/Keyboard accelarators".

2009-04-20  Glenn Randers-Pehrson <glennrp@simple....>

  - coders/png.c: Cosmetic-only, change `True` to `MagickTrue` or
    `MagickPass` and `False` to `MagickFalse` or `MagickFail`.

2009-04-20  Glenn Randers-Pehrson <glennrp@simple....>

  - coders/png.c: Check error return from CompressColormapTransFirst()

2009-04-20  Glenn Randers-Pehrson <glennrp@simple....>

  - coders/png.c: Refrain from modifying image struct members
    (matte, colors, depth) while writing a PNG.

2009-04-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - doc/options.imdoc: Document the direction of rotation.

2009-04-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/log.c (LogMagickEventList): Use MagickPackageName from
    version.h rather than hard-coding `GraphicsMagick`.

2009-04-18  Glenn Randers-Pehrson <glennrp@simple....>

  - coders/jpeg.c: Fixed a warning about `shadowed` variables.

2009-04-17  Glenn Randers-Pehrson <glennrp@simple....>

  - coders/png.c: Fixed some warnings about `shadowed` variables.

2009-04-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Add tests for some reentrant versions of functions
    where we are still using the non-rentrant versions.

  - magick/composite.c (CompositeImage): Fix problem with
    compositing images where the change image overlaps off the left
    side of the canvas.  Should fix SourceForge issue #2766200 `memory
    allocation error when compositing small images`.

2009-04-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/semaphore.c: Re-arrange ifdefs so that it is possible to
    use pthreads under the WIN32 API.

2009-04-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/bit\_stream.c: Bitstream functions were often not inlining
    and inline functions which don't inline are not much use.
    Bitstream functions are now normal library functions.

2009-03-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - VisualMagick/bin/delegates.mgk: Remove bounding box option (-g) from
    Postscript delegate specifications.

  - config/delegates.mgk.in: Remove bounding box option (-g) from
    Postscript delegate specifications.

  - coders/{ept.c, pdf.c, ps.c} : PDF bounding box is sometimes
    incorrect or not globally applicable so don't specify bounding box
    when reading PDF files.  Postscript files do need the bounding box
    so make sure that it is still supplied.  Resolves SF tracker issue
    2487651 `convert from pdf chops off rhs`.

2009-03-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/Magick++/Image.rst: Translate Image.html to reStructuredText
    format for easier maintenance.

2009-03-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/rgb.c: Compute the quantum type rather than using a
    recurring conditional statement.  It turns out that the -endian
    option is working as it should.

2009-03-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/{gray.c, rgb.c, cymk.c}: Work toward supporting the
    -endian option.  Not working properly yet.

  - magick/enum\_strings.c (EndianTypeToString): New function.
    (InterlaceTypeToString): New function.

2009-03-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/drawing\_wand.c: Stripped out unused code.

  - www/wand: Added formatted Wand API documentation.

  - scripts/format\_c\_api\_doc.py: Now supports --include-rst option.

2009-03-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (GetImageBoundingBox): If we fail to find a
    smaller bounding box, then the returned bounding box is the entire
    image.

2009-02-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - VisualMagick/magick/magick\_config.h.in: Provide configuration
    access to the DisableSlowOpenMP define.

  - PerlMagick/t/read.t: Add a test for HRZ Slow scan TV.

  - magick/pixel\_cache.c (ModifyCache): Set image `taint` flag and
    clear monochrome and grayscale flags when pixels are accessed
    read/write rather than at sync.

  - coders/Makefile.am (MAGICK\_CODER\_SRCS): Add coders/hrz.c to
    build.

2009-01-27  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/hrz.c: New HRZ reader for slow scan TV.

2009-02-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/resize.c (ResizeImage): Make error handling more robust.

  - magick/pixel\_cache.c (SetNexus): Return a run-time error to
    invoking code rather than exiting the program if the pixel staging
    buffer fails to be allocated.

2009-02-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Allow the user to force the
    returned image to be TrueColor type for min-is-white and
    min-is-black TIFF files.  Previous to this, bilevel TIFF files
    were always returned as PseudoClass.

2009-01-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.c, coders/pnm.c: Fix several race conditions
    reported by Julian Seward.
    (OpenCache): Restore conservative pre-allocation of pixel indexes
    since a glitch was encountered that needs to be resolved.

  - magick/{channel.c,compare.c,constitute.c,decorate.c,effect.c,fx.c,
    image.c,operator.c,pixel\_iterator.c,render.c,resize.c,segment.c,
    shear.c,transform.c}: Use explicit OpenMP critical sections to
    avoid possible cross-contention.

  - coders/{dpx.c, pnm.c} Use explicit OpenMP critical sections to
    avoid possible cross-contention.

2009-01-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.c (OpenCache): Remove conservative
    pre-allocation of pixel indexes.

2009-01-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/index.rst: Reduce the amount of text on the front page.

2009-01-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - GraphicsMagick.spec.in: The module .la files need to be
    installed as part of the base install or else the modules will
    fail to load.

2009-01-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dib.c (ReadDIBImage): Fix assertion thrown for DIB files
    with negative image height values.

2009-01-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/bmp.c (ReadBMPImage): Fix assertion thrown for BMP files
    with negative image height values.  Resolves SF issue 2523536 `bug
    in bmp coder`.

  - Makefile.am: Don't install Magick++ headers if Magick++ is
    disabled.

  - GraphicsMagick.spec.in: --enable-lzw option is no longer used.

2009-01-17  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/fits.c: More robust fits parsing.

2009-01-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Updated news.

2009-01-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/colorspace.c (XYZTransformPackets): Fix arithmetic
    overflow problem noticed for Q32 build when using GCC on
    big-endian systems.

  - magick/constitute.c: Update Richard Nolde's float 16 and 24
    functions.

  - magick/command.c (VersionCommand): Print some build information
    for MSVC builds.

2009-01-10  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/fits.c: Ability to skip unsupported multidimensional object.

2009-01-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c (GetBlobSize): It seems that under Windows, the
    zip stream is not usable as a file handle.  Switch back to using
    stat instead, but use \_stati64 if available.

2009-01-04  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/fits.c: Fixed bug in scene count in extension block.
  - coders/fits.c: Supported logging.

2009-01-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Produce sprintf scaling strings for
    platform-specific types.

  - magick/magick\_types.h.in: Include sprintf scaling strings for
    platform-specific types.

  - magick/constitute.c (WriteImage): If output stream is not
    seekable and coder needs to use seek, then divert output to
    temporary file, and then send file to stream.

  - magick/blob.c (GetBlobSize): Simplify implementation.
    (OpenBlob): Don't attempt to test header magic on file we are
    writing.  Silly benign bug in obtuse code.

  - coders/tiff.c (ReadTIFFImage,WriteTIFFImage): Strip out use of
    temporary file.  Use TIFFClientOpen() for writing.

