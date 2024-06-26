2008-12-28  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/fits.c: Ability to read extension blocks.

  - coders/fits.c: Fixed MaxTextExtent limitation of blocks.

2008-12-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/OpenMP.rst: Add results for Window Vista 64-bit / AMD Phenom
    X4 9550.

  - VisualMagick/installer/inc/body.isx: Revert yesterday's change
    regarding the placement of config files.  Place the config files
    in a `config` subdirectory just as before.

2008-12-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - VisualMagick/installer/inc/body.isx: They say that when in Rome
    you should do as the Roman's do.  Based on this philosophy, all of
    the coder and filter DLLs are now installed to the same directory
    as the executables and DLLs which depend on them.  This eases
    operation under Windows Vista.

2008-12-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c: First pass at supporting large file access under
    Windows.

2008-12-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/resource.c (InitializeMagickResources): Improve resource
    estimation for Microsoft Windows systems with large memory.

  - magick/segment.c: Added some code to dump histograms with
    `-verbose -verbose`.

  - coders/tiff.c: Support reading/writing 16 and 24 bit float TIFF
    files.

  - magick/constitute.c (ExportViewPixelArea): Support exporting 16
    and 24 bit short floats.  Relies on code developed for
    GraphicsMagick by Richard Nolde.
    (ImportViewPixelArea): Support importing 16 and 24 bit short
    floats.  Relies on code developed for GraphicsMagick by Richard
    Nolde.

2008-12-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/operator.h (enum QuantumOperator): Added LogQuantumOp,
    MaxQuantumOp, MinQuantumOp, and PowQuantumOp enumerations as well
    as "Log", "Max", "Min", and "Pow" options to -operator.

2008-12-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImage): The -write option was not
    implemented in a useful fashion and the +write option never worked
    at all.  Re-implement -write and eliminate +write from the
    documentation since +write is not needed.

2008-12-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage, WriteTIFFImage) Support reading
    and writing 64-bit integer TIFF.

  - magick/constitute.c (ImportViewPixelArea): Add support for
    importing 64-bit integer values.
    (ImportViewPixelArea): Add support for exporting 64-bit integer
    values.

2008-12-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Fix bug with reading one bit per
    sample RGB images.

2008-12-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.c (OpenCache): Fix a code ordering problem
    which results in `identify` throwing an assertion for PseudoClass
    image files.  This bug was added in the 1.3.2 release.

  - coders/tiff.c (ReadTIFFImage): Fix bug with `ping` mode.

2008-12-07  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/fits.c: Proper signed to unsigned conversion for 64 bit LSB images.

2008-12-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/Makefile.am: When X11 is disabled, don't compile the
    X11-specific source modules.  Don't ever install any X11-related
    header files.

2008-12-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/segment.c (SegmentImage): Use `double` rather than 64-bit
    integer to accumulate totalized values.  Make the cluster summary
    report more concise.

2008-12-06  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/fits.c: Fix for 64 bit images.

2008-12-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/segment.c (SegmentImage): Cluster threshold is expressed
    as a percentage of total cluster pixels.  Optimize for larger
    images.

2008-12-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/segment.c (SegmentImage): Accelerate using OpenMP.

2008-11-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/utility.c (ExpandFilenames): Remove some arbitrary
    argument length limits.  Pass -convolve argument without any
    additional checking.  Verify that strings are not truncated during
    copy.
    (ListFiles): Be more memory efficient.

  - magick/fx.c (ConvolveImage): Fix formatting problem when logging
    the convolution kernel used.

  - magick/utility.c (TranslateTextEx): Support formatting huge
    comment text.

2008-11-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/fx.c (ConvolveImage): Don`t process opacity channel
    unless image has one.

  - magick/effect.c (MotionBlurImage): Use
    AcquireOnePixelByReference() rather than AcquireImagePixels() to
    retrieve one pixel.  This is much more efficient.
    (AdaptiveThresholdImage): Don`t process opacity channel unless
    image has one.
    (BlurImage): Don`t process opacity channel unless image has one.

2008-11-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/profile.c (ProfileImage): +profile now supports a simple
    exclusion syntax.  For example, to strip all of the profiles
    except for the ICM profile use +profile '!icm,\*'.  The new syntax
    also allows multiple profile names to be listed at once.  The
    primary requirement is that all excluded profiles must be listed
    prior to those to be stripped.

2008-11-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/transform.c (RollImage): Remove image storage class
    alteration.
    (CompositeImageRegion): Ensure that the canvas image storage class
    is correct.

2008-11-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - config/delegates.mgk.in: Since we removed support for `spawn` a
    long time ago, and no longer execute using the Unix shell by
    default, we need to add an ampersand to the end of the two entries
    previously using `spawn` so that the display program does not hang
    when it invokes the external program.

  - utilities/Makefile.am (UTILITIES\_TESTS): Add preview-based
    tests.

  - coders/preview.c (WritePreviewImage): Solarize requires a
    threshold argument.

  - coders/vid.c (WriteVIDImage): Eliminate memory leak.

  - magick/montage.c (MontageImages): Fix continued use of freed
    memory.

2008-11-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/omp\_data\_view.c (AccessThreadViewDataById): New function
    to allow retrieving data via the index it was registered with.

  - magick/enhance.c (BuildChannelHistograms): EnhanceImage() and
    NormalizeImage() now share one common function for generating the
    histogram.

  - magick/enhance.c (ModulateImage): Improve performance a bit.
    (ContrastImage): Improve performance a bit.
    (GammaImage): Improve performance a bit.

2008-11-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/authors.rst: List Mark Mitchell as an author.

  - utilities/tests/msl\_composite.sh: Fix `rm -f` without a valid
    argument which annoyed NetBSD.

  - coders/fits.c: Impose a limit on the length of the row PDU.
    Make sure that GraphicsMagick version information does not
    overflow the length allowed by a row PDU.

2008-11-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c (WriteJPEGImage): Use DCT algorithm default from
    the library rather than the header file.

  - magick: Adjust OpenMP scheduling options based on observed
    behavior.

2008-11-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/shear.c (IntegralRotateImage): Added OpenMP acceleration
    for rotate by 90 and 270 degrees.

  - configure.ac: New --disable-openmp-slow configure for disabling
    use of OpenMP for algorithms which may run slower on operating
    systems with crummy thread libraries.  This still allows gaining
    the benefits from OpenMP for CPU hogs.  Verified to help with
    FreeBSD 7.0 and Apple OS-X Leopard.

  - magick/semaphore.c: Trimmed out the debug code in order to
    obtain a bit more performance.

2008-11-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c: Allow the user to specify the DCT method
    (jpeg:dct-method), or if huffman encoding should be enabled
    (jpeg:optimize-coding=true).  Default the DCT method to the
    libjpeg default rather than forcing it to JDCT\_FLOAT since float
    is slower on some systems.

2008-11-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jp2.c (BlobClose): Leak a little bit less memory when
    reading a JP2 file.

2008-11-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/wandtest.c: Eliminate memory leak.

  - wand/drawing\_wand.c (DestroyDrawingWand): Eliminate memory
    leaks.

  - coders/xwd.c (WriteXWDImage): Force colormapped images with more
    than 256 colors to DirectClass.

  - magick/enhance.c (ModulateImage): Improve progress message.

  - coders/msl.c: Eliminate memory leaks.

  - GraphicsMagick.spec.in: Apply RPM spec file fixes from Giacomo
    Tenaglia for Red Hat Linux 4.

2008-11-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/msl.c: Fix bug with attributes becoming appended to
    themselves.  Resolves SF issue 2255754. Reflowed code.

2008-11-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - version.sh: GraphicsMagick 1.3 released.
    Next release on head will be 1.4.

  - www/OpenMP.rst: Updated with latest measurement data.

  - www/benchmarks.rst: Updated with latest benchmark data.

  - coders/url.c (RegisterURLImage): Register HTTP and FTP URL
    support in the "unstable" category since these are capable of
    accessing the network and therefore represent a potential security
    issue.  Register the FILE URL support in the "stable" category
    since it is capable of incorporating local disk files, which may
    still represent a security security issue for server applications.
    Note that disabling these functions might cause some existing MSL,
    MVG and SVG scripts to stop working if they use external URLs.

2008-11-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pnm.c (ReadPNMImage): Sequential multi-thread the PNM raw
    format readers. Can improve read performance quite substantially
    for large PBM and PGM files, and less so for PPM.  There is most
    benefit for systems with more I/O than one CPU core will support.
    Systems with slow I/O and a relatively fast CPU may see somewhat
    diminished read performance with more CPU consumption.  As such,
    this is effectively a verification that multi-threading the reader
    is possible, and may be of benefit to power-users.

  - magick/omp\_data\_view.c (AllocateThreadViewDataArray): New
    function to allocate a thread view data array.  Updated modules
    using similar code to use this function in order eliminate
    useless redundancy.

2008-11-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.c: Incorporate OMP thread views into the
    pixel cache so usage is less invasive.  Update OMP-enhanced source
    modules to suit.
    (GetImagePixelsEx): New function similar to GetImagePixels()
    except that it reports exceptions to a user-provided structure.
    (SetImagePixelsEx): New function similar to SetImagePixels()
    except that it reports exceptions to a user-provided structure.
    (SyncImagePixelsEx): New function similar to SyncImagePixels()
    except that it reports exceptions to a user-provided structure.
    (AccessImmutableIndexes): New function to access read-only
    colormap indexes.
    (AccessMutableIndexes): New function to access writeable colormap
    indexes.
    (AccessMutablePixels): New function to access writeable pixels.
    (AccessDefaultCacheView): New function to access the default cache
    view.

2008-11-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (BenchmarkImageCommand): With no other
    arguments, the benchmark command now defaults to one iteration.

  - magick/effect.c (SpreadImage): Offsets array size is a prime
    number to help avoid beating.
    (SpreadImage): Ensure that spread loops are always terminal.

  - magick/utility.c (MagickRandReentrant): Fix bug where rand() was
    being continually re-seeded if rand\_r() was not available.

2008-11-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - utilities/tests/msl\_composite.sh: Replace SVG image generation
    with simpler approach which properly centers the text.  Use our
    own font so that tests will pass if the user does not have fonts
    installed.

  - magick/utility.c (GetMagickDimension): Extend to support parsing
    optional x and y offset values and use to fix parsing for
    -oil-paint and -unsharp when sscanf() is C'99 compliant.

2008-11-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.h (AcquireOneCacheViewPixel): Pass pixel to
    update by reference.
    (AcquireOnePixelByReference): New private inline method which
    passes pixel to update by reference.

  - magick/omp\_thread\_view.h (AcquireOneThreadViewPixel): Pass pixel
    to update by reference.

  - magick/alpha\_composite.h (BlendCompositePixel): Replace
    BlendComposite with BlendCompositePixel, which passes the
    composite pixel by reference.
    (AlphaCompositePixel): Replace AlphaComposite with
    AlphaCompositePixel, which passes the composite pixel by
    reference.
    (AtopCompositePixel): Replace AtopComposite with
    AtopCompositePixel, which passes the composite pixel by reference.

  - configure.ac: With excessive maintenance releases, the library
    age portion of MAGICK\_LIB\_VERSION was overflowing its allotted
    space.  This resulted in 1.1.X releases reporting the wrong
    MagickLibVersion as of 1.1.10.  Fix this by supporting up to 99
    values for each field.

2008-11-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Fix passing the --with-windows-font-dir option via
    DISTCHECK\_CONFIG\_FLAGS.

  - utilities/tests/msl\_composite.sh: Integrated MSL composition
    test script contributed by Max Hohenegger, Max at hohenegger.eu.

  - magick/command.c (ConjureImageCommand): Return status was
    inverted so one was returned for command success rather than zero.

2008-11-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - png: Updated libpng to 1.2.33 release.

  - magick/color.c (FuzzyColorMatch): If fuzz is zero then
    completely use the result of ColorMatch() rather than entering
    unnecessary expensive code.

2008-10-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/studio.h: Make sure we don't conflict with OpenMP
    implementation if it is active but we are not using it.

2008-10-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/studio.h (HAVE\_OPENMP): Add logic to make sure that
    OpenMP is only engaged for OpenMP 2.0 or later.

  - magick/command.c (VersionCommand): Report OpenMP version.

  - Makefile.am: The Magick++ build was supposed to be optional. Now
    it is.

  - Makefile.am: Eliminated .tar.bz2 and .zip packages from the
    distribution.  The .tar.bz2 package was hardly smaller than the
    .tar.gz package so it wasted 5.9MB with little benefit.  The
    compression ratio on the .zip archives is absolutely terrible so
    eliminating zip eliminates huge 9.6MB and 25MB files from the
    distribution equation.  Windows users can easily learn how to use
    the vastly more efficient 7-Zip format.

2008-10-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Rationalize OpenMP tests to make sure that OpenMP
    can not be enabled without thread support.

2008-10-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/composite.c (CompositeImageRegion): Add some minimal
    region limit checking.  Not completed yet.

  - magick/transform.c (RollImage): Accellerate using OpenMP.

2008-10-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/studio.h (omp\_get\_thread\_num): Remove spurious trailing
    `;`.

  - magick/render.c (DrawPrimitive): Make method private since
    nothing else is using it.

  - magick/omp\_thread\_view.h (AccessThreadView): Inline function for
    a bit more performance.
    (AcquireOneThreadViewPixel) Inline function for a bit more
    performance.

2008-10-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - pragma omp parallel for: Use consistent static scheduling
    throughout and ensure that 64 threads can be usefully engaged on a
    1024 row image.

  - magick/pixel\_iterator.c (SetRegionThreads): Implement logic so
    that pixel iterators execute single-threaded when invoked on tiny
    regions.

  - magick/pixel\_cache.c (SetNexus): Make staging buffer memset()
    conditional in order to dramatically diminish impact to small
    accesses.  This memset() only exists to make valgrind happy.

2008-10-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Fix progress monitor for the case
    of reading planar stripped images.

2008-10-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/effect.c (DespeckleImage): Accelerate using OpenMP.

  - magick/paint.c (OpaqueImage): Update to use pixel iterators.
    (TransparentImage): Update to use pixel iterators.

  - magick/decorate.c (FrameImage): Accelerate using OpenMP.
    (RaiseImage): Accelerate using OpenMP.

2008-10-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/composite.c (CompositeImageRegion): Start of new function
    to act as a lighter-weight yet more flexible image composition
    interface.

  - magick/transform.c (ChopImage): Accelerate using OpenMP.
    (CropImage): Accelerate using OpenMP.
    (FlipImage): Accelerate using OpenMP.
    (FlopImage): Accelerate using OpenMP.

  - magick/effect.c (ThresholdImage): Accelerate using OpenMP.

2008-10-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.c (AcquireOneCacheViewPixel): Optimize
    implementation.

  - magick/effect.c (MedianFilterImage): Accelerate using OpenMP.
    (ReduceNoiseImage): Accelerate using OpenMP.

2008-10-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/fx.c (WaveImage): Accelerate using OpenMP.
    (SwirlImage): Accelerate using OpenMP.
    (ImplodeImage): Accelerate using OpenMP.

2008-10-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.c (GetCacheViewRegion): New function to
    return the region bounded by a pixel cache view.

  - magick/constitute.c (ExportViewPixelArea): New function to
    support exporting the pixels from a pixel cache view.
    (ImportViewPixelArea): New function to support importing pixels
    to a pixel cache view.

  - magick/pixel\_cache.c (ReadStream): Eliminated function.
    (WriteStream): Eliminated function.
    (ClonePixelCacheMethods): Eliminated function.

  - magick/image.h: Eliminated StreamHandler call-back type.
    Eliminated ImageInfo stream member.

  - magick/pixel\_cache.c (GetCacheViewArea): New function to return
    the area of a cache view.
    (AccessCacheViewPixels): New function to access already selected
    cache view pixels.

2008-10-19  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/fits.c: Remove unused exponential data.

2008-10-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/omp\_thread\_view.c: Move OMP Thread View functions out of
    pixel cache module and put them in this new module.

  - coders/xtrn.c (ReadXTRNImage): XTRNSTREAM mode was never
    implemented so remove unfinished stub code.

2008-10-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (SetImageDepth): Needed to assign image depth
    attribute to user-specified depth rather than only altering the
    pixels.
    (SetImageOpacity): Reimplement using pixel iterators.
    (AverageImages): Accelerate using OpenMP.
    (GetImageBoundingBox): Accelerate using OpenMP.

2008-10-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/constitute.c (ConstituteTextureImage): Accelerate using
    OpenMP.

  - magick/image.c (TextureImage): Accelerate using OpenMP.

  - magick/render.c (DrawAffineImage): Accelerate using OpenMP.

2008-10-13  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/fits.c Fixed palette problem for >8 bit images.

2008-10-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImage): Using +page now resets image
    page offsets as documented for convert and mogrify.

2008-10-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (GradientImage): Re-do OpenMP accelleration based
    on new pixel cache interface for better performance.

  - coders/dpx.c (ReadDPXImage): Progress monitor needs to tick when
    row count is updated.

  - coders/fits.c (ReadFITSImage): Update to use
    MagickFindRawImageMinMax().
    (WriteFITSImage): Expand buffer size to MaxTextExtent.  Include
    GraphicsMagick version in FITS header.

  - coders/mat.c (ReadMATImage): Update to use
    MagickFindRawImageMinMax().

  - magick/constitute.c (MagickFindRawImageMinMax): New internal
    function to assist with finding the minimum and maximum data of
    raw image files.

2008-10-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.c (AcquireThreadViewPixels): Convert thread
    set view convenience methods into library methods because the
    inline methods were causing the Sun Studio compiler to produce
    thread unsafe code.  Due to likely beneficial inlining in the
    library, this is not expected to cause any performance impact.

2008-10-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/t/filter.t: Add a test for UnsharpMask.

  - magick/effect.c (UnsharpMaskImage): Use Blur rather than
    GaussianBlur to create blur image since it is faster.

  - magick/pixel\_cache.c (AllocateThreadViewDataSet): Add a
    destructor function in case data should not be destroyed, or needs
    something other than MagickFree().
    (AllocateThreadViewDataSet): Use user-provided destructor to free
    user data.

  - scripts/format\_c\_api\_doc.py: Improvements from Mark Mitchell to
    perform keyword/target substitions and wrap function prototypes.

  - coders/dpx.c (ReadDPXImage): Accellerate reader using OpenMP.

2008-10-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/api/types.rst: Convert types.html to reStructured text
    format.

2008-10-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/monitor.c (MagickMonitorFormatted): New method to support
    issuing a formatted progress monitor message.  Use it throughout
    so that file name is included in progress indication.

2008-10-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Bootstrap with autoconf 2.63.  Require autoconf
    2.62 to bootstrap.

2008-10-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www: Adopted improved web page design by Mark Mitchell.

2008-10-04  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/fits.c coders/mat.c Used a same piece of code to calculate
    min and max data value.

2008-09-30  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/fits.c Fixed 16 bit fits writer that wrote wrongly
    shaped unsigned ints.

2008-09-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - doc/conjure.imdoc: Applied patches from Max at hohenegger.eu to
    mention previously undocumented elements and to provide a
    composition example.

2008-09-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/shear.c (IntegralRotateImage): Accelerate rotation by 0
    and 180 degrees using OpenMP.
    (XShearImage): Accellerate using OpenMP (accellerates -rotate and
    -shear).
    (YShearImage): Accellerate using OpenMP (accellerates -rotate and
    -shear).

2008-09-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/effect.c (MotionBlurImage): Enable OpenMP now that pixel
    cache is re-entrant.

  - magick/pixel\_iterator.c: Updated to use thread view convenience
    inline methods as proof of principle.

  - magick/pixel\_cache.h: Added convenience inline methods to make
    use of thread views a bit more pleasant.

2008-09-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/effect.c (ShadeImage): Fix valgrind gripe.
    (MedianFilterImage): Fix valgrind gripe.

2008-09-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.c: Pixel cache is believed to be thread safe
    now.

  - magick/deprecate.c (AcquireCacheView): Deprecate this function.
    (GetCacheView): Deprecate this function.
    (SetCacheView): Deprecate this function.
    (SyncCacheView): Deprecate this function.

  - magick/pixel\_cache.c (AcquireCacheViewPixels): New function to
    replace AcquireCacheView().
    (GetCacheViewPixels): New function to replace GetCacheView().
    (SetCacheViewPixels): New function to replace SetCacheView().
    (SyncCacheViewPixels): New function to replace SyncCacheView().

  - coders/msl.c: Applied patches from Max at hohenegger.eu which
    fix a MSL parsing error related to gamma, and erroneous text
    comments which claim that elements can't have attributes.

2008-09-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/resize.c (ResizeImage): Move OpenMP instrumentation to
    outer loop so that eventually there can be more performance.

2008-09-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/resize.c (MinifyImage): Accelerate using OpenMP.

  - magick/command.c (ConvertImageCommand, MogrifyImageCommand):
    Accept -gaussian-blur as a synonym for -gaussian.
    (ConvertImageCommand, MogrifyImageCommand): Provide access to
    MinifyImage() via -minify.
    (ConvertImageCommand, MogrifyImageCommand): Provide access to
    Magnifyimage() via -magnify.

2008-09-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/channel.c (ImportImageChannelsMasked): New function to
    import all the channels from an image except for the channels
    specified.

  - magick/effect.c (AddNoiseImageChannel): New function to add
    noise to an image channel.
    (BlurImageChannel): New function to blur one image channel.
    (GaussianBlurImageChannel): New function to gaussian blur an image
    channel.
    (UnsharpMaskImageChannel): New function to unsharpmask an image
    channel.
    (SharpenImageChannel): New function to sharpen an image channel.

2008-09-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/effect.c (MotionBlurImage): Use GetOptimalKernelWidth1D()
    to estimate a reasonable convolution kernel size.  Prepare code
    for OpenMP but don't enable OpenMP until it runs faster.
    (AddNoiseImageChannel): New function to apply noise to a specified
    image channel.

2008-09-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (ConvertImageCommand): Provide `convert` access
    to MotionBlurImage() via -motion-blur option.
    (MogrifyImageCommand): Provide `mogrify` access to
    MotionBlurImage() via -motion-blur option.

2008-09-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/effect.c (SpreadImage): Accelerate using OpenMP.

  - coders/msl.c: Applied MSL patch from graphicsmagick-bugs list to
    correct handling of geometry x,y values by setting gravity
    attribute to ForgetGravity.

2008-09-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/effect.c (ShadeImage): Accelerate using OpenMP.

2008-09-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/effect.c (RandomChannelThresholdImage): Accelerate using
    OpenMP.  Support individual thresholding of the color channels.
    (BlurImage): Blur was failing for PseudoClass images.  This bug
    was added on 2008-09-08.

  - magick/pixel\_cache.c (AcquireOneCacheViewPixel): New function to
    return just one pixel from a cache view.

2008-09-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/effect.c (EnhanceImage): Accelerate using OpenMP.
    (BlurImageScanlines): Added optimizations.

  - magick/shear.c (IntegralRotateImage): Add missing progress
    indication for 90 and 270 degrees rotation.

  - www/perl.html: Fix formatting of examples.  Should address
    SourceForge issue [ 2100339 ] "Wrong format in example script on
    web page".

2008-09-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/effect.c (BlurImage): Accelerate using OpenMP.

2008-09-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/fx.c (ColorizeImage): Re-implement using pixel iterators.
    (MorphImages): Re-implement using pixel iterators.
    (OilPaintImage): Accelerate using OpenMP.
    (SolarizeImage): Re-implement using pixel iterators.

2008-09-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/fx.c (ConvolveImage): Accelerate using OpenMP.

  - magick/effect.c (AdaptiveThresholdImage): Accelerate using OpenMP.

2008-09-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.c: Exhuastive study of the pixel cache code
    reveals that it is inscrutable and not implemented in a fashion
    which enables useful multi-threading.  Therefore, the cache view
    interfaces are now made OpenMP-safe via a global critical section.

2008-09-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_iterator.c: Reduce use of critical sections around
    pixel cache to the bare minimum based on analysis and testing.
    Unfortunately, testing shows that the pixel cache views are still
    not 100% thread safe so the extra locking is still required.

  - magick/pixel\_cache.c (ModifyCache): Make implementation thread
    safe.  This required removing a thread-unsafe optimization from
    Bill Radcliffe.

  - magick/command.c (BenchmarkImageCommand): Restore original
    client name for each loop so that it is not extended further for
    each iteration.

  - magick/semaphore.c (UnlockSemaphoreInfo): Decrement lock depth
    under protection of the lock.

2008-09-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/effect.c (AddNoiseImagePixels): Update to pass per-thread
    `seed` value for more performance.

2008-08-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/gem.c (GenerateDifferentialNoise): Use
    MagickRandReentrant(). Added a `seed` argument so that we can pass
    a per-thread `seed` value.

  - magick/utility.c (MagickRandNewSeed): New function to produce a
    semi-random `seed` value.
    (MagickRandReentrant): New function which works like rand() but
    attempts to be re-entrant if possible by allowing a seed value to
    be passed.

2008-08-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/channel.c (SetImageChannelDepth): Re-implement using
    QuantumOperatorImage().

  - magick/image.c (SetImageDepth): Re-implement using
    QuantumOperatorImage().

  - magick/operator.h (QuantumOperator): Added DepthQuantumOp for
    setting the channel depth.

  - magick/command.c (BenchmarkImageCommand): Add CPU-based
    iteration rate metric to benchmark output.

  - magick/resource.c (ListMagickResourceInfo): Include quantum
    depth, bits per pixel, and process address size in resource
    output so that output is more complete.

2008-08-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (SyncImage): Re-implement using pixel iterators.
    (SortColormapByIntensity): Re-implement using pixel iterators.
    (ClipPathImage): Re-implement using pixel iterators.
    (CycleColormapImage): Re-implement using pixel iterators.
    (GetImageDepth): Re-implement using pixel iterators.
    (GradientImage): Parallize inner loop for speedup with larger
    images.
    (ReplaceImageColormap): Re-implement using pixel iterators.
    (SetImage): Re-implement using pixel iterators.

2008-08-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/operator.c (QuantumGamma): Removed unnecessary OpenMP
    request on inner loops.

  - magick/enhance.c (EqualizeImage,NormalizeImage): Execute
    histogram generation pixel iterator with just one thread to
    decrease contention for the histogram array.

  - magick/pixel\_iterator.c (InitializePixelIteratorOptions): New
    function to initialize PixelIteratorOptions with defaults.

  - magick/pixel\_iterator.h (PixelIteratorOptions): New structure to
    support passing pixel iterator execution options.

2008-08-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Updated for changes to date in 1.3 development code.

  - magick/pixel\_iterator.c: Execute pixel iterators in parallel via
    OpenMP.

  - magick/pixel\_cache.c (OpenCacheView): Ensure that pixel cache is
    open.
    (GetCacheInfo): Allocate semaphore immediately.

2008-08-16  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/fits.c Writer now creates valid images according to
    http://fits.gsfc.nasa.gov/fits\_verify.html
    Fixed problems: 1) zeros in HDU, 2) wrong padding. 3) possible
    strlen() overflow.

2008-08-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/{compare.c, channel.c, enhance.c, image.c, operator.c}:
    Update existing pixel iterator callback functions so that they are
    OpenMP safe.

2008-08-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/compare.c (InitializeDifferenceImageOptions): Renamed
    from DifferenceImageOptionsDefaults().
    (InitializeDifferenceStatistics): New function to initialize
    DifferenceStatistics.
    (ComputeAbsoluteError, ComputePeakAbsoluteError,
    ComputeSquaredError): Use local totalizing structure on stack and
    update cumulative statistics when the loop terminates.

2008-08-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www: Convert HTML pages to use a vibrant green theme rather than
    colors stolen from old GIMP web site.

2008-08-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - doc/{compare.imdoc, options.imdoc}: Added documentation for
    `compare`.

  - magick/compare.h (enum HighlightStyle): Added
    AssignHighlightStyle for simple color assignment.  `Annotate` is
    now `Tint`.

  - magick/command.c (CompareImageCommand): Useful options are now
    -metric, -highlight-color, and -hightlight-style.

2008-08-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/compare.c (DifferenceImagePixels): Fixed `Annotate`
    difference annotation algorithm.  Added `Threshold` and `Xor`
    difference annotation algorithms.
    (GetImageChannelDifference): New function for computing
    statistical image error using various metrics.  Inspired by
    `imgcmp` from Jasper.
    (GetImageChannelDistortion): New function for obtaining
    statistical image error using various metrics for a specified
    image channel.  Signature is compatible with similar ImageMagick
    function.
    (GetImageDistortion): New function for obtaining statistical image
    error using various metrics for all the active channels in the
    image.  Signature is compatible with similar ImageMagick function.

  - magick/command.c (CompareImageCommand): Added a `compare`
    subcommand which compares two images using various metrics, and/or
    generates a difference image using various difference annotation
    algorithms.  Documentation not yet updated.

2008-08-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_iterator.c: Split user context in all pixel
    iterator APIs into a mutable data part, and an immutable data
    part.  This required modification to all modules using the pixel
    iterator methods.

2008-07-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/magick\_wand.c (MagickCompareImageChannels): Use
    DifferenceImage().
    (MagickCompareImages): Implement by calling
    MagickCompareImageChannels().

  - magick/compare.c (DifferenceImage): The ImageMagick-compatible
    CompareImages() function signature was clearly an example of bad
    design so rename CompareImages() to DifferenceImage() with a
    signature which does not unnecessarily mix functionality and
    allows for ease of future expansion.

2008-07-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/Makefile.am (WAND\_TESTS): Added Wand drawtest and wandtest
    to automated test suite.

2008-07-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/effect.c (ThresholdImage): Don't read uninitialized pixel
    indexes (valgrind gripe).

  - coders/tiff.c (CompressionSupported): Use
    TIFFIsCODECConfigured() to test if a codec is supported.

  - tests/{rwblob.c, rwfile.c}: use DestroyImageList() rather than
    DestroyImage().

  - coders/psd.c (RegisterPSDImage): Fix module registration memory leak.

  - coders/jpeg.c (RegisterJPEGImage): Fix module registration memory leak.

2008-07-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/blob.c (DestroyBlob, DestroyBlobInfo): Implementation is
    a bit more robust.

2008-07-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c (ReadJPEGImage): Remove over-write of
    image->client\_data.  Resolves SourceForge issue [ 2018974 ]
    client\_data is not passed to streamhandler.

  - coders/png.c (WriteOnePNGImage): Fix crash when writing PNG
    images with transparency and either type Optimize is requested, or
    the image is colormapped.

2008-07-12  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/mat.c Fixed problem: "In this case, the referenced 
    images had previously been deallocated but are still being used.
    Since they are overwritten, their signatures are invalid.

2008-07-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dcm.c (ReadDCMImage): Report actual image depth.

  - magick/resource.c (InitializeMagickResources): Set default
    maximum memory limit to physical memory rather than 2X physical
    memory.  This decision is made since the system paging device is
    often slower than files in the filesystem, and so memory mapping
    is likely faster.

  - magick/blob.c (OpenBlob): The MAGICK\_IO\_FSYNC environment
    variable causes output files to be synchronized to disk when set
    to TRUE.

2008-07-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/GraphicsMagick.html: Improved formatting of documentation.

2008-07-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (SetImageInfo): Make use of the new
    `extension\_treatment` field.

  - coders/dcraw.c (ReadDCRAWImage): Added a coder module to proxy
    from various common RAW camera format extensions to the `dcraw`
    delegate.

  - magick/magick.h (MagickInfo): Add an extension\_treatment member
    to indicate how file extensions should be treated for this coder.

2008-06-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/{animate.c,quantize.c}: Replace !ColorMatch() with
    NotColorMatch().

  - utilities/Makefile.am (install-exec-local-utilities): Add back
    in support for --enable-magick-compat which was accidentally
    dropped in the new makefiles for GraphicsMagick 1.2.  Resolves
    SourceForge bug 2005883.

  - magick/color.h (NotColorMatch): New macro for testing that two
    colors are not the same.  Opposite from existing ColorMatch().

  - magick/command.c: Replaced the many duplicate enum conversion
    code fragments with calls to functions in enum\_strings.c.

  - magick/enum\_strings.c: Absorbed the many "ToString" and
    "StringTo" functions from other source modules.

  - magick/effect.c (ThresholdImage): Optimize for larger images.

  - magick/constitute.c (ConstituteTextureImage): New function to
    return a texture canvas image based on a tile image.  Similar to
    existing TextureImage() except better optimized for creating new
    images and inherits tile image properties.

  - magick/color.h (IsBlackPixel): New macro to test if a pixel is
    black.
    (IsWhitePixel): New macro to test if a pixel is white.

  - coders/tile.c (ReadTILEImage): Use new ConstituteTextureImage()
    function rather than TextureImage().  Also allow the user to
    request a particular image type.

  - coders/pdf.c (Huffman2DEncodeImage): Explicitly request a strip
    per page when writing Group4 TIFF.

  - coders/tiff.c (WriteTIFFImage): Place a generous default limit
    on rows-per-strip when using Group3 or Group4 FAX compression.
    The default limit is added since it is observed that the Group4
    compressor fails with extremely huge strips.  Added a define
    "tiff:rows-per-strip" to allow the user to explicitly set the rows
    per strip.  Added a define "tiff:strip-per-page=true" to allow the
    user to force one strip per page no matter what.  Added progress
    monitor support to tile writer.

2008-06-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - VisualMagick/configure/configure.cpp: The MAT coder now depends
    on zlib so add explicit dependencies for it.

  - wand/magick\_wand.c (MagickNegateImage): Implemented previously
    unimplemented Wand method.
    (MagickGammaImageChannel): Implemented previously unimplemented
    Wand method.

  - magick/operator.h (enum QuantumOperator): Added GammaQuantumOp
    and "gamma" operator.  Renamed InvertQuantumOp to NegateQuantumOp.

2008-06-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/operator.h (enum QuantumOperator): Added InvertQuantumOp
    and "invert" operator.

  - coders/xcf.c (GIMPBlendModeToCompositeOperator): For XCF format,
    we do support GIMP\_DIVIDE\_MODE composition now. Disable progress
    monitor during tile composition.

  - magick/composite.c (DivideCompositePixels): New Divide composite
    operator contributed by Michael Burian <michael.burian@sbg.at>.

  - magick/image.h (enum CompositeOperator): Added DivideCompositeOp.

  - magick/enum\_strings.c (CompositeOperatorToString): New function
    to convert a composite operator to a string.
    (StringToCompositeOperator): New function to convert a string to a
    composite operator.

2008-06-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/magick\_wand.c (MagickThresholdImageChannel): Implement
    previously unimplemented Wand function.
    (MagickGetImageExtrema): Implement previously unimplemented Wand
    function.
    (MagickGetImageChannelExtrema): Implement previously unimplemented
    Wand function.
    (MagickQueryFonts): Implement previously unimplemented Wand
    function.

2008-06-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - scripts/format\_c\_api\_docs: Scan compare.c for API definitions.

  - wand/magick\_wand.c (MagickCompareImageChannels): Enable use of
    this function.
    (MagickCompareImages): Enable use of this function.

  - magick/compare.c: New source file.
    (IsImagesEqual): Move here from magick/image.c.
    (CompareImageChannels): Initial implementation of function roughly
    similar to the one in ImageMagick.
    (CompareImages): Initial implementation of function roughly
    similar to the one in ImageMagick.

  - magick/pixel\_iterator.c (PixelIterateTripleModify): New pixel
    iterator function to access two images as read-only and one as
    read-write for updating existing pixels.
    (PixelIterateTripleNew): New pixel iterator function to access two
    images as read-only and one as read-write for creating new pixels.

2008-06-22  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - mat.c Added CloseBlob().

2008-06-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/magick\_wand.c (MagickSetImageFormat): Add method to support
    setting the image format.

2008-06-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/profile.c (ProfileImage): Convert to use pixel iterators.

2008-06-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/channel.c (ImportImageChannel): Convert to use pixel
    iterators.
    (SetImageChannelDepth): Convert to use pixel
    iterators.

  - Magick++/lib/Image.cpp (quantize): Error measurement support was
    being performed incorrectly.  SyncImage() is not needed here.

2008-06-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/channel.c (GetImageChannelDepth): Convert to use pixel
    iterators.

2008-06-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/mat.c (RegisterMATImage): Set blob support to false for
    MAT coder until bug related to blobs is fixed.

2008-06-16  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - mat.c Ability to read a new compressed MATLAB image format.

2008-06-15  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - mat.c, wpg.c: For empty images a message ImageFileDoesNotContainAnyImageData
    is returned.

2008-06-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/channel.c (ChannelImage): Convert to use pixel iterators.
    (ExportImageChannel): Convert to use pixel iterators.

  - coders/dpx.c (WriteDPXImage): As an experimental feature, when
    the environment variable MAGICK\_RESERVE\_STORAGE is set to "TRUE",
    then the DPX format writer will request the required storage from
    the filesystem in advance (if supported by the OS) or the full
    amount of memory required (when writing to an in-memory BLOB).

2008-06-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magic.c (InitializeMagicInfo): New function to initialize
    file format detection.
    (GetMagickFileFormat): New internal implementation function to
    detect file format based on file header.
    (GetMagicInfo): This internal implementation function is eliminated.
    (MagicInfo): MagickInfo structure is now private to the
    implementation.

2008-06-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magick.c (ListMagickInfo): Replace "blob support"
    indication with the coder stability classification.
    (RegisterMagickInfo): Pay attention to coder classification.

  - magick/magick.h (MagickInfo): Added a coder stability
    classification field as well as the MAGICK\_CODER\_STABILITY
    environment variable to choose which coders are enabled.

2008-06-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (GetImageCharacteristics): Don't access image
    pixels if they are not defined yet.

  - coders/{avi.c,avs.c,dcm.c,ept.c,fits.c,mtv.c,palm.c,rla.c,tga.c}:
    Readers are now much more robust when faced with reading random files.

2008-06-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (SetImageInfo): Exclude all virtual delegates and
    coders for pseudo-formats.

2008-06-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dcm.c (ReadDCMImage): Make DCM reader quit immediately on
    EOF condition.

  - coders/avi.c (ReadAVIImage): Make AVI reader more robust at
    rejecting bad files.

  - configure.ac: Eliminated --enable-delegate-build option that I
    have not used or tested for almost ten years so it probably did
    not work anyway.  Use --with-ttf=/prefix to specify the the
    installation prefix for freetype.  Use
    --with-ttf=/prefix/bin/freetype-config to specify the whole path
    to freetype-config.

2008-06-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImage): Add support for
    -black-threshold and -white-threshold.

  - magick/image.h (enum ChannelType): Added GrayChannel
    enumeration.

  - magick/operator.c (QuantumOperatorImageMultivalue): New
    implementation function to make creating legacy functions like
    black/white thresholding easier.

  - wand/magick\_wand.c (MagickBlackThresholdImage): Implemented.
    (MagickWhiteThresholdImage): Implemented.

  - magick/effect.c (BlackThresholdImage): Implemented a
    BlackThresholdImage() which is similar to (but not identical to)
    the one in ImageMagick.
    (WhiteThresholdImage): Implemented a WhiteThresholdImage() which
    is similar to (but not identical to) the one in ImageMagick.

2008-06-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/operator.c: Added support for additional channel
    operators (-operator) for applying noise to one or more channels.
    The additional operators are Noise-Gaussian, Noise-Impulse,
    Noise-Laplacian, Noise-Multiplicative, Noise-Poisson, and
    Noise-Uniform.  The amount of noise applied is controlled via the
    numeric argument, which can specify the percentage of noise to
    apply.

  - magick/enum\_strings.c: New source module to contain the various
    EnumToString() and StringToEnum() functions which seem to multiply
    like bunny-rabbits.

  - magick/gem.c (GenerateNoise): Poisson noise generation was
    taking excessively long and producing wrong results.  Noise
    generation was only producing the correct amount of noise in the
    Q8 build.       
    (GenerateDifferentialNoise): New function to return noise in a
    floating-point differential format.

2008-06-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_iterator.h: Removed x,y coordinate information from
    all of the callback definitions since a use for this information
    has yet to be found.

  - magick/composite.c (CompositeImage): Use individual callback
    functions for the composition operations.

  - coders/xcf.c (ReadXCFImage): Deal with grayscale images the
    GraphicsMagick-way.

2008-06-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/xcf.c (ReadXCFImage): Validate XCF file data so that
    corrupted files don't crash GraphicsMagick.

2008-05-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (ReadDPXImage): Incrementally read user data
    part and check for EOF so that bogus files are rejected quickly.

  - coders/cineon.c (ReadCINEONImage): Incrementally read user data
    part and check for EOF so that bogus files are rejected quickly.

2008-05-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pict.c (ReadPICTImage): Ensure that row\_bytes calculation
    does not overflow.  Verify that RLE decode does not overflow
    buffer.  Validate image frame dimensions.       

  - coders/palm.c (ReadPALMImage): Validate PALM bits per pixel and
    colormap indexes.

  - magick/resource.c (ListMagickResourceInfo): List controlling
    environment variable in `-list resource` output as a configuration
    usage reminder.

  - coders/pdf.c (ReadPDFImage): Properly deal with reading rotated
    PDFs.

2008-05-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - FAQ.txt: Added a FAQ for how to extract and combine CMYK image
    channels to individual files.

2008-05-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/fx.c (ConvolveImage): Eliminate unnecessary "range check"
    feature since range checking is not where the CPU time is going.

  - magick/effect.c (UnsharpMaskImage): Re-write implementation to
    use pixel iterators.

  - magick/pixel\_iterator.c: Decided that the old per-pixel
    iterations were not useful enough to keep since the region-based
    ones are working fine.  Moved pixel\_row\_iterator.c to
    pixel\_iterator.c and renamed functions to remove the `Row`
    designation.

  - magick/composite.c (CompositeImage): Automatically adjust
    colorspace of composite image so that it is compatible with canvas
    image.

  - magick/alpha\_composite.h (AlphaComposite): Fix alpha composite
    when both pixels contain transparency.

  - PerlMagick/demo/demo.pl: Use segmentation parameters which
    are more suitable for our image.

2008-05-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/composite.c (CompositeImage): CMYK copy composition
    operators automatically set the image colorspace to CMYK.

  - coders/tiff.c (WriteTIFFImage): CMYK must take precedence over
    JPEG compression.  We don't support JPEG compression in TIFF with
    CMYK.

2008-05-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/effect.c (ChannelThresholdImage): Re-implement using
    pixel iterators.  Support thresholding only the red channel by
    eliminating the switch to intensity thresholding if only one
    channel parameter is supplied.

  - coders/tiff.c (WriteTIFFImage): Don't accidentially convert CMYK
    images to RGB.

  - magick/composite.c (CompositePixels): Handle CopyBlack properly
    for CMYK images.

  - magick/command.c (CompositeImageCommand):  Support CopyCyan,
    CopyMagenta, CopyYellow, and CopyBlack.

  - magick/composite.c (CompositeImage): Preserve the canvas image
    colorspace.

  - doc/options.imdoc: Remove mention of thresholding at the channel
    level since this never worked in a useful fashion and now only
    simple intensity thresholding is available via -threshold.

  - magick/command.c (MogrifyImage): Revert to using ThresholdImage() rather
    than ChannelThresholdImage().

  - PerlMagick/Magick.xs: Revert to using ThresholdImage() rather
    than ChannelThresholdImage().

2008-05-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/effect.c (AddNoiseImage): Implemented using pixel
    iterators.

  - magick/pixel\_row\_iterator.c (PixelRowIterateDualNew): New pixel
    iterator.  Similar to existing PixelRowIterateDualModify except
    that this one is for when initializing a new image.

2008-05-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/composite.c (CompositeImage): Update image composition to
    use pixel iterator methods.

2008-05-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/enhance.c: Re-wrote all enhancement functions in this
    module to be based on the pixel iterator methods.

  - magick/command.c (ConvertImageCommand, MogrifyImageCommand,
    DisplayImageCommand): Gamma multiple channel syntax was broken.
    Now it is fixed.

2008-05-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/colorspace.c (RGBTransformImage): Optimized lookup table
    generation performance to the maximum extent possible.
    (TransformRGBImage): Optimized lookup table
    generation performance to the maximum extent possible.

  - magick/image.h (RoundDoubleToQuantum): New macro to explicitly
    safely round a `double` to a Quantum.
    (RoundFloatToQuantum): New macro to explicitly safely round a
    `float` to a Quantum.

  - configure.ac: Add OpenMP support library to LIBS so that
    dependent applications will pick up this dependency without
    themselves needing to enable OpenMP.

  - magick/command.c (CompositeImageList): Don't overwrite matte
    flag for CopyOpacity composition.

  - magick/composite.c (CompositeImage): CopyOpacity composition
    needs the opacity channel to be enabled.

  - PerlMagick/Magick.xs: Dissolve composition with Opacity was not
    working right.  Now it does.

2008-05-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/gem.c (HWBTransform): Hue value range was scaled wrong,
    leading to clipping.
    (TransformHWB): Hue value range was scaled wrong, leading to
    clipping.

2008-05-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/colorspace.c (RGBTransformImage): Re-implement transform
    loops using PixelRowIterateMonoModify() in order to simplify the
    code.

2008-05-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/colorspace.c (TransformRGBImage): Re-implement transform
    loops using PixelRowIterateMonoModify() in order to simplify the
    code.

  - magick/{pixel\_iterator.h, pixel\_row\_iterator.h}: Pass pixel
    colormap index/indexes to callback functions.  Dependent code is
    adjusted to match.

2008-05-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (ConvertImageCommand, MogrifyImageCommand,
    MogrifyImage): Add command access to the new channel operators.

  - magick/operator.c (QuantumOperatorRegionImage): Support the new
    channel operators.  Update to use PixelRowIterateMonoModify() for
    a bit more performance.

  - magick/operator.h (enum QuantumOperator): Added new operators
    AssignQuantumOp, ThresholdQuantumOp, ThresholdBlackQuantumOp, and
    ThresholdWhiteQuantumOp.

2008-05-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (VersionCommand): Report if OpenMP is supported
    by the build.

  - configure.ac, Makefile.am: Install documentation according to
    the conventions established by the configure script.  This
    installs the documentation under
    /usr/local/share/doc/GraphicsMagick by default.

2008-05-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - scripts/format\_c\_api\_docs: Add pixel\_iterator.c and
    pixel\_row\_iterator.c to API documentation formatter.

  - magick/api.h: Include pixel\_iterator.h and pixel\_row\_iterator.h.

  - magick/Makefile.am (MAGICK\_INCLUDE\_HDRS): Formally install
    pixel\_iterator.h and pixel\_row\_iterator.h.

  - magick/image.c (IsImagesEqual): Update to use
    PixelRowIterateDualRead().
    (GetImageStatistics): Update to use PixelRowIterateMonoRead().

  - magick/pixel\_row\_iterator.h: New interfaces which are similar to
    the already existing interfaces in pixel\_iterator.h except that
    they pass a row to the callback rather than one pixel.

  - magick/operator.c (QuantumOperatorRegionImage): Add progress
    monitor support.

  - magick/pixel\_iterator.c (PixelIterateMonoRead): Add a
    `description` argument and progress monitor support.
    (PixelIterateMonoModify): Add a
    `description` argument and progress monitor support.
    (PixelIterateDualRead): Add a
    `description` argument and progress monitor support.
    (PixelIterateDualModify): Add a
    `description` argument and progress monitor support.

  - magick/resize.c (HorizontalFilter, VerticalFilter): Switch back
    to RoundSignedToQuantum() since some pixels were experiencing
    underflow.  Localize some variables so that we don't have to
    declare them as private for OpenMP.

2008-05-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac, magick/resize.c, PerlMagick/Makefile.PL.in: Added
    OpenMP support for parallelizing a task across multiple cores.

2008-05-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac, magick/nt\_base.h: Fix using libbz2 under MinGW.

  - coders/{msl.c, svg.c, url.c}: Fix compilation with modern
    libxml2 under MinGW.

2008-05-08  Josue Andrade Gomes  <josuegomes@gmail.com>

  - magick/nt\_base.h, libxml/include/win32config.h (vsnprintf):
    Fixed compilation issue noticed with Visual C++ 2008.

2008-05-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magick.c (GetMagickInfo): Simplify implementation.
    (RegisterMagickInfo): Remove any existing entry since module
    loading may result in duplicate entries.

2008-05-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - libtool: Update to libtool 1.2.4.

  - magick/magick.h (MagickInfo): Store string attributes as `const
    char \*` to statically allocated data rather than as heap allocated
    strings.  THIS IS AN INTERFACE CHANGE.  Using a coder written to
    the old interface is non-fatal but may resemble a small memory
    leak.  The reason for the change is to avoid at least 880 needless
    malloc()/strlen()/strlcpy() operations at initialization time, and
    at least 880 free() calls at destruction time.  While these
    operations did not take long, they are still an unnecessary
    overhead, which is increased in thread-safe applications.

  - magick/module.c (OpenModule): Ignore requests to open modules
    which have already been opened.

  - GraphicsMagick.spec.in: Add --with-included-ltdl to the default
    options since this seems safest until the libltdl validation logic
    is fully robust.  This should be made user-configurable in the
    future.

  - magick/Makefile.am (magick\_libGraphicsMagick\_la\_LIBADD): Apply
    libltdl dependency argument as required for building.

  - configure.ac: Intuit if the GraphicsMagick library will depend
    on -lltdl.

  - Magick++/bin/GraphicsMagick++-config.in: Use substitutions
    rather than invoking GraphicsMagick-config in order to determine
    GraphicsMagick library usage requirements.  This avoids problems
    when GraphicsMagick-config is not in the executable search path.

2008-05-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - GraphicsMagick.spec.in: NEWS was renamed to NEWS.txt.  Enable
    libtool verbose output so it is possible to diagnose build
    failures.

2008-05-01  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - mat.c: gm convert -limit Pixels 1 input\_gray\_lsb\_16bit.mat crap.miff
    don't rotate partial image.

2008-04-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magick.c (DestroyMagickInfoList): Use DestroyMagickInfo().
    (UnregisterMagickInfo): Use DestroyMagickInfo().
    (RegisterMagickInfo): Simplify dramatically by adding to the front
    of the list rather than maintaining alpha order.

  - magick/image.c (DestroyImageInfo): Tidy up and simplify code.

  - magick/constitute.c (WriteImage): Comment out the "bi-modal
    delegate" execution code until we determine what value it offers.
    The test suite passes without it.

  - magick/magick.h (struct MagickInfo): There is no need for `name`
    to be allocated data so make it const.  
    (DestroyMagickInfo): Add a static function to destroy a MagickInfo
    structure.  Renamed previous DestroyMagickInfo to
    DestroyMagickInfoList and made it static.

2008-04-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - version.sh: GraphicsMagick 1.2 released.
    CVS head is now 1.3 development.

  - png: Updated libpng to 1.2.27.

2008-04-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (SetImageInfo): Ignore file extensions which
    match defined virtual delegate entries (including stealth
    entries).

2008-04-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - BENCHMARKS.txt: Added timings for -blur.

2008-04-27  Darko Kojic  <dkc@sf.net>

  - magick/effect.c (MedianFilterImage): Fixes to compile on ARM
    CPU.

2008-04-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magick.h (MagickInfo): Remove image\_info member since I
    can not find any purpose for it.

  - coders/tiff.c (WriteTIFFImage): Remove assertion check on
    scanline size since it has not caught anything.

  - magick/image.c (SetImageInfo): Ensure that the file extension
    does not trigger unwanted activity such as access to an X11
    server, printer, or the launch delegate.

  - config/Makefile.am (configshare\_DATA): Install colors.mgk in
    share path.

  - magick/blob.c (GetConfigureBlob): Search `share` config path
    prior to `lib` config path.

2008-04-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/png.c (WriteOnePNGImage): TrueColor RGB was usually
    written rather than the desired more compact format.  This is a
    first pass at fixing that.

2008-04-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - BENCHMARKS.txt: Added a benchmark summary.

2008-04-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - version.sh: Prepare 1.2beta1 release.

  - NEWS.txt: Updated with latest news.

2008-04-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - libtool: Update to 1.2965 2008-04-22

  - coders/png.c (ReadOneJNGImage): Deal with ReadImage() returning
    a NULL pointer when reading JPEG sub-image.

2008-04-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/channel.c (ExportImageChannel): Added progress monitor
    support.
    (SetImageChannelDepth): Added progress monitor support.
    (ChannelImage): Don't preserve matte channel when extracting
    channel.

  - magick/image.c (SetImageOpacity): Avoid integer overflow in Q32
    build.  Added progress monitor support.
    (SyncImage): Added progress monitor support.
    (SetImage): Added progress monitor support.
    (CycleColormapImage): Added progress monitor support.
    (GetImageBoundingBox): Added progress monitor support.
    (SortColormapByIntensity): Added progress monitor support.

2008-04-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac, magick/Makefile.am: Don't use libtdl unless we are
    supposed to be using it!

  - libtool: Updated to GNU libtool 1.2960 2008-04-19.

  - configure.ac, magick/delegate.h: It seems that the modern
    convention is to store ghostscript headers in a subdirectory
    called `ghostscript` rather than `ps`.
    We don't actually need Ghostscript errors.h and that is a good
    thing since it seems that some newer Ghostscript calls it ierrors.h

2008-04-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - VisualMagick/installer/inc/files-dlls.isx: Comment out inclusion
    of X11 support DLLs.

  - VisualMagick/magick/magick\_config.h.in: X11 is no longer in the
    default Windows build.

2008-04-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/nt\_base.c: Eliminate various annoying warnings noticed
    under MinGW.

  - magick/spinlock.h (\_spinlock\_release): Use `long` rather than
    `int` in order to eliminate warning under MinGW.

  - magick/semaphore.c (spinlock\_wait): Use `long` rather than `int`
    in order to eliminate warning under MinGW.

  - magick/log.c (LogMagickEventList): Eliminate warning under MinGW.

  - magick/compress.h: Clean up interface definitions to use
    magick\_uint8\_t for unsigned character data.

  - coders/jpeg.c (ReadJPEGImage): Don't use GetPixelCachePresent()
    since it is not DLL-exported.

2008-04-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/yuv.c (ReadYUVImage): Report exception info correctly.

  - coders/xpm.c (ReadXPMImage): Report exception info correctly.

  - coders/xc.c (ReadXCImage): Report exception info correctly.

  - coders/tiff.c (ReadTIFFImage): Report exception info correctly.

  - coders/null.c (ReadNULLImage): Report exception info correctly.

  - coders/jpeg.c (ReadJPEGImage): Report exception info correctly.
    Use of Huffman optimization is now based on available memory
    rather than a hard-coded image size.

  - coders/gif.c (ReadGIFImage): Report exception info correctly.

  - magick/utility.c (MagickSizeStrToInt64): New function to convert
    a size string with optional units suffix to a 64-bit integer.
    (MagickStrToInt64): New function to convert a string to a 64-bit
    integer, with error checking.

  - magick/image.c (SetImage): SetImage now returns error status.

  - magick/command.c: Eliminated the long-deprecated -cache resource
    limit option.

  - magick/resource.c: Complete re-write of the resource limit
    system.  Resource specifications are now absolute except that they
    support a binary metric suffix such as `K` to scale the value.
    Added the `Pixels` limit type to limit the maximum number of
    pixels allowed for each image.

2008-04-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jpeg.c (WriteJPEGImage): Output grayscale images more
    efficiently.

2008-04-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lcms: Updated lcms to 1.17.

  - png: Updated libpng to 1.2.26.

2008-04-09  Glenn Randers-Pehrson <glennrp@simple....>

  - coders/png.c (ReadOnePNGImage) Use the low bits of the PNG
    tRNS values instead of scaling them when reducing from 16-bits.

2008-04-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Updated to Autoconf 2.62.

2008-04-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImageCommand): New -create-directories
    option automatically creates subdirectories as needed when
    -output-directory option is used.  This is useful when one
    directory tree of files is being mogrified to a new tree.

2008-04-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/utility.c (MagickCreateDirectoryPath): New function to
    create a directory path.  Will be used later.
  - configure.ac: Tweaks to produce a successful MinGW cross-compile.

2008-04-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): Added a simple sentinel
    assertion to hopefully flush out any remaining cases where
    ExportImagePixelArea() writes past the end of its buffer.

  - magick/constitute.c (ExportImagePixelArea): GrayQuantum case for
    DirectClass pixels was sometimes writing a zero byte one past the
    end of the allocated buffer.  Thanks to Josue Gomes for reporting
    this bug.

2008-04-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/{pcd.c,pcx.c,pdb.c,pict.c,stegano.c,wpg.c,xcf.c}:
    Warnings reduction.     

  - magick/{channel.c,image.c,unix\_port.c,render.c}: Warnings
    reduction.

  - coders/mat.c: Convert C99 comments to C89 comments so code can
    compile with a C89 compiler.

  - coders/tiff.c (WriteTIFFImage): Add an assertion to enforce that
    the bytes output to the scanline is no more than the bytes
    allocated for the scanline.

  - NEWS.txt: Updated with latest NEWS.

2008-04-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pdf.c (WritePDFImage): Default to ZIP compression if
    available.  Ignore Image compression setting since the useful
    value (set by the user) usually comes from ImageInfo.

  - coders/png.c (WriteOnePNGImage): Fix progress monitor when
    writing PNG.

  - magick/channel.c (GetImageChannelDepth): Added progress monitor
    support.

  - magick/signature.c (SignatureImage): Added progress monitor support.

  - magick/image.c (GetImageDepth): Added progress monitor support.

2008-04-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - libtool:  Update to libtool 2.2.2.

  - coders/jpeg.c: Convert more code to use size\_t for sized values
    rather than long.

  - coders/wpg.c (InsertRow): Fix log format string specification.

  - coders/dpx.c (WriteDPXImage): Fix typo in casts.

  - coders/fpx.c (ReadFPXImage): Apply FreeBSD patch from Mikhail
    Teterin to allow FlashPIX to work better for 64-bit builds.
    Addresses SourceForge issue 1824658 "FPX should work again now".

  - magick/blob.c (ImageToBlob): Fix typo in cast.

2008-03-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - CONTRIBUTE.txt: Convert contribute.html to reStucturedText
    format and generate HTML version from it.

  - PROCESS.txt: Convert description of development process to
    reStucturedText format and generate HTML version from it.

  - INSTALL-windows.txt: Add instructions for how to install from
    setup.exe style installer.  Also add instructions for how the
    distribution package is built.

  - Copyright.txt: Reformat in reStucturedText format and generate
    HTML version from it.

  - VisualMagick/installer/inc/body.isx: No longer include
    development headers and libraries in the Windows DLL install
    package since they are large and they may only work with the
    version of Visual C++ used to perform the build.  It is much safer
    for the developer to build the package from source with his own
    compiler.

2008-03-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Fix compilation issues with Microsoft Visual Studio.

2008-03-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (ReadDPXImage, WriteDPXImage): Use lookup tables to
    speed up value conversion.

  - magick/memory.h (MagickAllocateArray): Renamed from
    MagickAllocateMemoryElements.

2008-03-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/Magick.xs: Use memory allocation macros like the rest
    of the code.

  - magick/memory.c (MagickMalloc): New function which behaves
    similar to malloc().
    (MagickMallocArray): New function for allocating an array.
    (MagickRealloc): New function which behaves similar to realloc().
    (MagickFree): New function which behaves similar to free().
    (MagickAllocFunctions): New function to allow the user to specify
    the memory allocation functions.

  - magick/memory.h: New header file to define memory allocation
    functions.

  - magick/deprecate.c (DeleteImageList, DestroyImages,
    GetImageList, GetImageListIndex, GetImageListSize, GetNextImage,
    GetNumberScenes, GetPreviousImage, ParseImageGeometry,
    PopImageList, PostscriptGeometry, PushImageList,
    SetCacheThreshold, SetImageList, ShiftImageList, SizeBlob,
    SpliceImageList, UnshiftImageList): Remove functions which were
    already deprecated in ImageMagick 5.5.2 or earlier.

2008-03-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (WriteDPXImage): Support writing image which is
    already in a YCbCr colorspace.
    (ReadDPXImage): Return YCbCr images in YCbCr colorspace unless
    they are also Cineon log encoded.

  - magick/image.c (CloneImage): Use CloneImageAttributes().

  - magick/attribute.c (CloneImageAttributes): New function for
    copying image attributes from one image to another.

  - magick/utility.c (TranslateTextEx): Check if the pixel cache is
    initialized before using a function which requires using it.
    Thanks to Michal Kowalczuk for bringing this issue to my
    attention.

  - magick/attribute.c (SetImageAttribute): Only apply
    transformations to "comment" and "label" attributes.

  - magick/pixel\_cache.c (GetPixelCachePresent): New function to
    test if the image pixel cache is present and initialized.

2008-03-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/colorspace.c (RGBTransformPacket): Rationalize casts for
    improved performance.

  - magick/image.c (GetImageDepth): Use table lookups to improve
    performance.

2008-03-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (AllocateImage): Transfer any attributes from
    ImageInfo to allocated image.
    (SetImageDepth): Use table lookups to improve performance.

2008-03-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (MogrifyImageCommand): Added an
    -output-directory option to `mogrify` to send output files to the
    specified directory.

2008-03-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/t/read.t: Add input\_logical\_lsb\_08bit.mat to
    PerlMagick tests.

  - magick/nt\_feature.c (CropImageToHBITMAP, ImageToHBITMAP): Use
    GlobalFree() to free bitmap handle.

2008-03-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/t/read.t: Added/adjusted WPG test files from Jaroslav
    Fojtik.

2008-03-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - AUTHORS.txt, BUGS.txt, FAQ.txt, NEWS.txt, PLATFORMS.txt,
    TODO.txt, INSTALL-unix.txt, INSTALL-windows.txt: Use
    reStructuredText format.

  - Makefile.am: Use reStructuredText for more files.

2008-02-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/constitute.c (ReadImage): Disable colorspace override
    code since it was being wrongly-triggered in X11 display commands.

2008-02-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/body.html: Update to mention 1.1.11 release.

2008-02-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/colorspace.c (RndToInt): Cast result to `unsigned int`
    rather than `int` in order to avoid possible value truncation with
    Q32 build.  Problem was reported by Kai-Uwe Behrmann.
    (TransformRGBImage): Fix loop iterator which was looping one past
    the end of the array.  Reported by Kai-Uwe Behrmann.

  - magick/command.c: Added a -set option to the composite, convert,
    display, mogrify, import commands in order to allow setting an
    image attribute.

2008-02-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - PerlMagick/Magick.xs: Use MagickAcquireMemory() rather than
    AquireMemory().

  - coders/xwd.c (ReadXWDImage): Eliminate integer overflow
    vulnerability (IDefense 09.19.07).

  - coders/xbm.c (ReadXBMImage): ditto

  - coders/xcf.c (ReadXCFImage): ditto

  - coders/dib.c (ReadDIBImage): ditto

  - coders/dcm.c (ReadDCMImage): ditto

2008-02-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): The RFC 3949 specification for
    Internet FAX recommends LSB2MSB fill order so document that.

2008-02-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): Use `-define
    tiff:fill-order={msb2lsb|lsb2msb}` to control TIFF bit fill order.

2008-02-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Updated to latest CVS libtool.

  - coders/tiff.c (CompressionSupported): Use
    TIFFGetConfiguredCODECs() to test if a requested compression type
    is supported by libtiff.  Based on advice from Frank Warmerdam.

  - configure.ac: Add test for TIFFGetConfiguredCODECs() in libtiff.

2008-02-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c: With libtiff 3.6.1, including tiff.h and tiffio.h
    is not sufficient to obtain the definitions from tiffconf.h so
    libtiff is assumed to not support any features, such as
    compression.  Avoid this problem by explicitly including
    tiffconf.h if it is found.  This resolves SourceForge issue
    [1883527] compression of tiff-file has no effect.

2008-02-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - VisualMagick/installer/inc/setup.isx: Set Inno Setup installer
    compression to "lzma/max".

  - PerlMagick/Magick.xs: Eliminate use of memory allocation macros
    since these failed miserably under Windows where it seems that
    malloc, free, and realloc are redefined via macros by the Perl
    build environment.  This reverts changes made on 2007-12-01.

  - magick/memory.c (MagickAcquireMemoryArray): Use implementation
    from the 1.1 branch.

  - magick/utility.h: Remove MagickSafeMultiplySize\_t since it seems
    that use of inline functions in Windows is a disaster area.

2008-02-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Makefile.am (windows-dist): Create a 7z compressed Windows
    comprehensive source package.  See http://www.7-zip.org/ for
    information on Windows 7-Zip and http://p7zip.sourceforge.net/ for
    information on portable 7-Zip (P7ZIP).

2008-02-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): Add logging for image resolution
    and resolution units.

  - magick/version.h.in: Update copyright year to 2008.

2008-02-01  Gary V. Vaughan  <gary@gnu.org>
    
  - configure.ac: Updated for libtool-2.1b.

  - bootstrap (libtoolize): Libtoolize can figure out the mode and
    directory for libltdl from configure.ac.

2008-01-28  Ralf Wildenhues  <Ralf.Wildenhues@gmx.de>

  - magick/Makefile.am: Update
    magick\_libGraphicsMagick\_la\_DEPENDENCIES to use LTDLDEPS.

2008-01-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (SetImageInfo): Successfully read existing file
    names in the form file[123] which were failing to read since they
    appear to be a valid sub-image specification.

2008-01-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/utility.c (ExpandFilenames): If a filename appears to
    contain a wildcard specification, first check to see if there is
    file matching the unexpanded wildcard prior to engaging in the
    slow task of wildcard expansion.  Without this fix, expanding the
    command line takes a very long time if there are a huge number of
    files in the directory, and some file names appear to contain
    wildcard specifications.  Inspired by SourceForge bug reports [
    1878992 ] "literal square brackets in file name cause large delay"
    and [ 1783209 ] "converting runs slowly when subimage is
    specified", but this might not be the complete fix for the
    problem.

2008-01-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Makefile.am: Update to Automake 1.10.1 and enable generation of
    an lzma compressed source package.

2008-01-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Added configure option --with-umem to enable use
    of the umem memory allocation library available in Solaris 9,
    Update 3 and later, or from
    https://labs.omniti.com/trac/portableumem/.  This library supports
    concurrency in multi-threaded programs and supports debugging
    memory issues.  See
    http://developers.sun.com/solaris/articles/libumem\_library.html
    for a description of how to use the library for debugging memory
    issues.

2008-01-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (VersionCommand): Include a "Large Memory" item
    in the Feature Support list.

  - coders/png.c (RegisterPNGImage): Remove reference to dead PNG
    ftp site.

  - VisualMagick/configure/configure.cpp (InitInstance): Remove
    project dependency on dxguid.lib (Direct-X).

2008-01-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Update libtool to latest CVS version.

2008-01-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (DisplayImageCommand): No longer default to
    reading standard input if stdin fails isatty() test.  This
    behavior was causing failure to launch from Gnome and it is
    difficult to work around the issue from within a .desktop file. 
    (AnimateImageCommand): No longer default to
    reading standard input if stdin fails isatty() test.

