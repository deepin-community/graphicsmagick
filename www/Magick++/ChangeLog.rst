================================
Magick++ ChangeLog
================================

2017-03-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (orientation): Update orientation in EXIF profile,
    if it exists.
    (attribute): Added Image attribute method which accepts a 'char \*'
    argument, and will remove the attribute if the value argument is
    NULL.

2014-11-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Geometry.h (Magick::Geometry): Add and document
    limitPixels() and fillArea() methods to support '@' and '^'
    geometry qualifiers.  Fill area contributed by Long Ho and
    limitPixels() by Bob Friesenhahn.

  - ../www/Magick++/Image.rst: Document extent and resize methods.

  - lib/STL.cpp (extentImage): New function object to invoke image
    extent method. Original implementation contributed by Long Ho.
    Subsequently modified by Bob Friesenhahn.
    (resizeImage): New function object to invoke image resize
    method. Contributed by Long Ho.

  - lib/Image.cpp (extent): New method to place image on sized
    canvas of constant color using gravity.  Contributed by Long Ho.
    (resize): New method to resize image specifying geometry, filter,
    and blur.  Original implementation contributed by Long Ho.
    Subsequently modified by Bob Friesenhahn.

2014-01-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (thumbnail): New method for fast image resizing,
    particularly to make thumbnails.

2013-12-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableDashArray): DrawableDashArray now uses
    C++ memory allocation rather than from GraphicsMagick library.
    Also, implement direct copy constructor and assignment operator
    rather than using dasyarray() method.

2012-11-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - COPYING: Change Magick++ usage license to be exactly the MIT
    license without the additional sentence about retention of
    copyright (which was already legally implicit).

2012-04-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (defineValue): Use AddDefinition() rather than
    AddDefinitions().

2012-03-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h (Magick): Added support for RandomNoise.

2012-03-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/STL.cpp (stripImage): New unary function to to remove all
    profiles and text attributes from the image.

  - lib/Image.cpp (strip): New method to remove all profiles and
    text attributes from the image.

2011-12-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h: Explicitly DLL import/export Magick++
    symbols when building under MinGW GCC.

2010-12-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h (Magick): Add LZMACompression

2010-12-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (InitializeMagick): Don't use atexit().  C++
    destructures are sufficient.

2010-09-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (backgroundColor, borderColor, matteColor):
    Opacity part of user-specified color needs to be preserved.
    Problem was reported by Alexander Zheltov.

2010-04-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/CoderInfo.h: Add default constructor, copy
    constructor, and assignment operator.

2010-01-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (Magick): Fix potential memory leak.

2010-01-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - demo/shapes.cpp (main): Floodfill shape more aggressively and
    scale fuzz factor so that it provides the same results across
    quantum depths.

2009-10-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/STL.cpp, lib/Magick++/STL.h (shadeImage): ShadeImage was the
    result of a botched cut-and-paste.  Corrected now.  Thanks to
    Jukka Manner for making me aware of this.

2009-09-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (cdl): New method to apply the ASC CDL.
    (colorMatrix): New method to apply a color matrix to the image
    channels.
    (haldClut): New method to apply a color lookup table (Hald CLUT)
    to the image.

2009-07-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (attribute): Invoke modifyImage() to assure
    exclusive access to image when updating attributes.

2009-03-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (quantumOperator): New variant of method which
    takes a 'double' argument, as it originally should.  Previous
    method taking a Quantum argument is still supported but marked
    deprecated.

2009-01-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h: If the user defines STATIC\_MAGICK in his
    project, then the Windows DLL decorations are ignored.  Without
    this, Windows DLL-based code can't use a static GraphicsMagick.
    This is recommended by SourceForge bug 2537627.

  - lib/Magick++/Drawable.h: Apparently the only STL container which
    may be DLL-exported is <vector> but we are using <list> so disable
    DLL-export of list-based template objects.

2008-10-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Color.cpp: Added an \_isValid boolean to represent an invalid
    color.  Transparent black is no longer special and can be used in
    drawing.
  - lib/Pixels.cpp: Update to use new cache view interfaces provided
    by GraphicsMagick 1.3.

2008-09-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (addNoiseChannel): New method to add noise to a
    specified channel.
    (blurChannel): New method to blur a specified channel.
    (gaussianBlurChannel): New method to gaussian blur a specified
    channel.
    (motionBlur): New method to motion blur the image.
    (randomThresholdChannel): New method to apply random thresholding
    or ordered dithering to the image.
    (randomThresholdChannel): New method to apply random thresholding
    or ordered dithering to the specified image channels.
    (sharpenChannel): New method to sharpen a specified image channel.
    (unsharpmaskChannel): New method to unsharpmask a specified image
    channel.

2008-06-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (quantize): Error measurement support was being
    performed incorrectly.  SyncImage() is not needed here.

2008-05-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - demo/demo.cpp (main): Fix segmentation parameters so they are
    more suitable for our image.

2008-04-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (depth): Remove 8/16/32 restriction on depth
    value.

2008-03-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Geometry.cpp, lib/Image.cpp: Include <strings.h> since it is
    needed in order to use strcpy().

2007-12-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/{Drawable.cpp, Geometry.cpp, BlobRef.cpp, Blob.cpp,
    Montage.cpp, Options.cpp, Image.cpp}: Eliminate use of deprecated
    GraphicsMagick functions.

  - lib/Magick++/{STL.h, Include.h}: Eliminate use of deprecated
    GraphicsMagick functions.

2007-07-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp: Include <cstdlib>

2006-10-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (pixelColor): Don't enforce color "validity" when
    setting the pixel color.

2005-10-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (orientation): New accessor method to support
    image orientation.

2005-04-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/STL.cpp (levelImage): New function object for leveling the
    image channels.
    (levelChannelImage): New function object for leveling a specific
    image channel.

  - lib/Image.cpp (level): New method for leveling the image
    channels.
    (levelChannel): New method for leveling a specific image channel.

2005-04-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h (Magick): Import CineonLogRGBColorspace
    into Magick namespace.

2005-04-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h: Import Rec601LumaColorspace (was called
    GRAYColorspace) and Rec709LumaColorspace into Magick
    namespace. Use of GRAYColorspace is mapped via a macro into
    Rec601LumaColorspace in order to avoid a user-visible API change.

2004-08-17  Volker Lukas  <vlukas@gmx.de>

  - lib/Drawable.cpp: Fixes to ensure that drawable objects remain
    coherent even if an exception is thrown within the assignment
    operator.

2004-07-22  Bob Friesenhahn <bfriesen@simple.dallas.tx.us>  <bfriesen@simple.dallas.tx.us>

  - demo/Makefile.am (AUTOMAKE\_OPTIONS): Added nostdinc in order to
    avoid accidentally using magick/list.h when including <list>.

  - tests/Makefile.am (AUTOMAKE\_OPTIONS): Added nostdinc in order to
    avoid accidentally using magick/list.h when including <list>.

  - tests/readWriteBlob.cpp: If MISSING\_STD\_IOS\_BINARY is defined,
    then ios::binary is not used.  Use simple ifstream rather than
    std::ifstream since we are already using the std namespace.

2004-06-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h: Disable unavoidable warnings under
    Visual C++ when instantiating STL templates within DLL
    code. Consensus from postings on the net is that as long as the
    same C++ compiler is used throughout, these warnings are of no
    concern.

2004-05-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (coderInfoList): Make error reporting a bit
    more lenient so that if an error occurs while loading a module it
    is not reported as an exception unless no coders were found at
    all.

2004-05-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (clipMask): Use GetImageClipMask.

2004-04-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/CoderInfo.cpp (CoderInfo): Sense of isReadable() and
    isWritable() was inverted.

2004-04-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h: <inttypes.h> is not used. Inclusion
    removed.

2004-03-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Thread.cpp (lock): Have not been successful with using
    MsgWaitForMultipleObjects() reliably, so back out usage of it for
    now.

2004-03-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Thread.cpp (lock): For MsgWaitForMultipleObjects, monitor
    state change only.  Otherwise lock may deadlock.

2004-03-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (statistics): New method to obtain image
    statistics (minimum, maximum, mean, variance, and standard
    deviation).

2004-03-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (quantumOperator): New image method to apply an
    arithmetic or bitwise operator to the pixel quantums in an image.
    Still needs documentation.
    (quantumOperator): New image method to apply an arithmetic or
    bitwise operator to the pixel quantums in an image region.

2004-03-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Makefile.am (../www/Magick++/ChangeLog.html): Fix execution of
    txt2html.

  - lib/STL.cpp (composeImage): Added a function object to set/get
    the Image composition option.

  - lib/Image.cpp (compose): Added a method to set/get the Image
    composition option.

2004-03-06  Vladimir Lukianov  <lvm@integrum.ru>

  - lib/Thread.cpp (lock): Use MsgWaitForMultipleObjects() rather
    than WaitForSingleObject() in order to avoid possible deadlock
    when application code directly or indirectly creates windows.

2004-02-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (interlaceType): Retrieve interlace setting from
    Image rather than ImageInfo.

2004-02-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (Image): Delete the allocated image reference
    object if a Magick::Error is thrown by the Image constructor.
    Otherwise the image reference object becomes a memory leak.

2004-01-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (WriteImages): Pass Blob::MallocAllocator to
    updateNoCopy() in order to ensure that correct deallocator is
    used.

  - tests/readWriteBlob.cpp (main): Needed to delete character array
    using array [] reference.

2004-01-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - demo/analyze.cpp (main): Fix a GNU C++ library portability
    problem noticed under MinGW. The 'left' iostream manipulator seems
    to be missing.

2004-01-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/Makefile.am: coderInfo test is expected to fail for moby
    builds when the package is not yet installed since a .la file
    exists in the coders directory, but there is no associated .so
    file.  Therefore failures of the coderInfo test are now ignored.

2003-12-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (defineValue): New method to support setting
    format-specific defines.
    (defineSet): New method to support setting or testing for
    format-specific flags.

2003-12-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (iccColorProfile): Implementation now uses the
    profile method with profile name "ICM".  Note that this now
    invokes the color profile if the image already has one.
    (iccColorProfile): Reimplement using new GetImageProfile function.
    (iptcProfile): Reimplement using the new GetImageProfile and
    SetImageProfile functions.
    (profile): Reimplement using new GetImageProfile function.

2003-12-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Makefile.am (pkglibdir): Improve header file
    install location logic.

2003-12-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - demo/analyze.cpp (main): New program to demonstrate using the
    'analyze' process module.

  - demo/Makefile.am: Add rules to build analyze program.

  - lib/Image.cpp (process): New method to execute process modules.

  - lib/Image.cpp (attribute): New method to get and set named image
    attributes.

2003-10-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Color.cpp: Ensure that all non-default constructors set
    opacity to opaque.

2003-09-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (colorHistogram): If map key is not const,
    then implicit type conversion occurs.  Sun's C++ compiler doesn't
    seem to handle that.  The map key is now defined as const in the
    insert arguments.

2003-09-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/Makefile.am: Add build support for colorHistogram.cpp.

  - tests/colorHistogram.cpp: New test program to test retrieving
    color histograms from the image using colorHistogram().

  - lib/Magick++/STL.h (colorHistogram): Added new template function
    to retrieve a color histogram into a user-provided container.
    Verified to work when using STL <vector> and <map> as the target
    container types.  When <map> is used, a user-specified color may
    be used to perform lookups in the map to obtain the usage count
    for that color.

  - lib/Color.cpp (operator >=): Insufficient resolution was being
    provided in order to reliably sort color objects in STL
    containers.  The updated algorithm should be fail-safe.

2003-08-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (channelDepth): New method to set or get the
    modulus depth for a specified channel.

2003-08-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h (Magick): Added support for
    CopyCyanCompositeOp, CopyMagentaCompositeOp,
    CopyYellowCompositeOp, and CopyBlackCompositeOp, composition
    operators.

2003-08-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (depth): Method now only updates the
    Image/ImageInfo depth member and retrieves the value of the Image
    depth member.
    (modulusDepth): New method to inspect the pixels for actual
    modulus depth, or update/reduce the pixels to a specified modulus
    depth.  The depth method was performing this function so any code
    which depended on the depth method to compute or set the modulus
    depth should be updated to use modulusDepth() instead.

2003-08-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (matte): If a new matte channel is created,
    initialize it to opaque.  Likewise, if the matte channel is
    eliminated, initialize the unused channel to opaque.

2003-07-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - demo/demo.cpp (main): Don't crop logo image.

  - \*.h, \*.cpp: Include "Magick++/Include.h" before including any
    compiler or system header in order to ensure that LFS defines are
    properly applied. Inspired by patch from Albert Chin-A-Young.

2003-06-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h: Needed to import ThrowLoggedException.

  - lib/Exception.cpp (throwException): Add originating source
    module, source line, and function name (if available) to exception
    report. This is useful in order to determine the exact conditions
    that lead to the exception being thrown.
    
  - lib/Magick++/Exception.h: Added ErrorCoder, WarningCoder,
    ErrorConfigure, WarningConfigure, ErrorDraw, WarningDraw,
    ErrorImage, WarningImage, ErrorMonitor, WarningMonitor,
    ErrorRegistry, WarningRegistry, ErrorStream, WarningStream,
    ErrorType, and WarningType, exception classes to support the full
    set of exceptions that GraphicsMagick can throw.

2003-06-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/CoderInfo.cpp (CoderInfo): Applied compilation fix from Mike
    Chiarappa to compile using Borland C++.

2003-06-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Geometry.cpp (string): Throw an exception if a string is
    requested from an invalid geometry object.

2003-06-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Geometry.cpp (operator =): If GetGeometry returns NoValue,
    then assign an invalid geometry object to cause an exception if
    the geometry is then used.

2003-06-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Exception.h (ErrorModule): Added class to handle
    module errors.

  - lib/Magick++/Exception.h (WarningModule) Added class to handle
    module warnings.

2003-05-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (coderInfoList): Use GetMagickInfoArray to
    access coder list.

2003-05-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (affineTransformImage): Add function object
    contributed by Vladimir Lukianov to apply an affine transform to
    the image.

  - lib/Image.cpp (affineTransform): Added method contributed by
    Vladimir Lukianov to apply an affine transform to the image.

2003-05-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h: Decided to back out change which used
    the \_VISUALC\_ define to trigger inclusion of <sys/types.h>.

2003-05-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h: If \_VISUALC\_ is defined, include
    <sys/types.h>. This ensures that this necessary header is included
    even if HAVE\_SYS\_TYPES\_H is not defined in magick\_config.h.

2003-05-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (InitializeMagick): InitializeMagick is now a C++
    function rather than a namespace inclusion.  An atexit() handler
    is registered to invoke DestroyMagick when the program
    exits. Relying on static deconstruction to invoke DestroyMagick
    proved to be unreliable due to translation unit destruction
    uncertainty.

2003-04-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (Image::Image (MagickLib::Image\* image\_)):
    Incorporated recommended fix from Jukka Manner to avoid
    a scenario which leaks an Options object.

  - tests/coalesceImages.cpp: Updated to use modified
    coalesceImages() interface.

  - lib/Magick++/STL.h (coalesceImages): Replaced implementation
    with one from Felix Heimbrecht. The template signature has changed
    to return a new image sequence. This template API silently ceased
    to function due to an ImageMagick CoalesceImages API change.

2003-03-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/readWriteBlob.cpp (main): Added check for stream read
    failure when reading blob data.
    (class myBlob): Use get rather than read.

2003-03-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/attributes.cpp : Change in the way that Magick++ retrieves
    density caused tests to fail.  Density now defaults to 72x72
    (GraphicsMagick default) rather than invalid.

2003-03-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - demo/Makefile.am (CLEANFILES): Fix clean target to
    remove \*\_out.mvg output files as well.
    
  - demo/zoom.cpp: Added a command-line parser for dash arguments as
    well as an image "resample" capability.

  - lib/Image.cpp (density): Obtain density from Image rather than
    ImageInfo if the Image is valid.

2003-03-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Makefile.am : Added rules to install GraphicsMagick++.pc.

  - lib/GraphicsMagick++.pc.in : Added pkgconfig file for
    -lGraphicsMagick++.

2003-02-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (colorSpace): Pass image->colorspace to
    TransformRGBColorspace.

2003-01-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (writeImages): Should have been invoking
    WriteImages rather than WriteImage!

2003-01-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h: Add HSL and HWB colorspace
    transformation support.

2003-01-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (colorSpace): Support colorspace transforms other
    than to and from RGB by translating to RGB as an intermediate
    step.

2002-11-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp: Added DrawablePushClipPath,
    DrawablePopClipPath, and DrawableClipPath.  Implementation
    contributed by Vladimir <lvm@integrum.ru>.

2002-11-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (colorMapSize): New method to set, or return the
    colormap size.

2002-11-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (adaptiveThreshold): New method.

2002-10-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (coderInfoList): Intentionally ignore missing
    delegate exceptions.

2002-09-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Options.cpp (textEncoding): Had forgotten to implement
    textEncoding!

2002-09-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Color.cpp (Color): Use of 'new' and 'delete' in inlines was
    causing memory allocation/deallocation problems for users of the
    DLL build.  Problem was identified by Marc Iwan.

2002-09-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (compare): New method to compare current image
    with a reference image.

2002-08-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (textEncoding): New method to allow setting the
    default text encoding (e.g. "UTF-8").

  - lib/Drawable.cpp (DrawableText): Added an alternate constructor
    to allow specifying the text encoding (e.g. "UTF-8").

2002-08-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Overall: Now compiles as a DLL using Visual C++.

2002-07-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (profile): Added method to store, delete, or
    retrieve named application profiles.

2002-07-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (type): Set the ImageInfo type attribute when
    setting the image type.  If the type attribute is set to something
    other than UndefinedType (implying that the user has set a desired
    output image type), then return that as the image type, otherwise
    use GetImageType() to evaluate the image type.

2002-05-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableTextUnderColor): New class to set the
    text undercolor.  When text undercolor is set, a rectangle of the
    specified color is rendered under text annotations.

2002-05-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Magick++ library no longer depends on iostreams at all.

2002-04-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (throwImageException): ExceptionInfo was not being
    properly initialized.  This could cause some errors to cause an
    abort in error.c rather than throwing an exception.

2002-04-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (draw): Use draw.h drawing APIs to draw on image.
    This means that MVG output no longer comes from code in
    Drawable.cpp.

2002-04-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/STL.cpp: Moved function object implementations from STL.h to
    STL.cpp.

2002-04-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (getConstPixels): Changed offset parameter type
    from 'unsigned int' to 'int'.
    (getPixels): Changed offset parameter type from 'unsigned int' to
    'int'.
    (setPixels): Changed offset parameter type from 'unsigned int' to
    'int'.
    (cacheThreshold): Changed argument type from 'const long' to
    'const int'.
    (matteFloodfill): Changed offset parameter type from 'const long'
    to 'const int'.

  - lib/Pixels.cpp (getConst): New method to return read-only
    pixels.
    (get): Offset parameter types changed from 'unsigned int' to
    'int'.

2002-04-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Drawable.h (DrawableDashOffset): Change dashoffset
    type to 'double' rather than 'unsigned int' in order to match
    ImageMagick.

  - lib/Drawable.cpp (DrawableDashArray): Change dasharray type to
    'double' rather than 'unsigned int' in order to match
    ImageMagick. Previous 'unsigned int' methods remain for
    compatibility reasons.

2002-04-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableCompositeImage): Always output
    composite images as inlined Base64.

2002-04-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableCompositeImage): If magick attribute
    string is specified, then composite image is supplied to
    ImageMagick as inlined Base64 rather than by MPRI reference.

  - lib/Blob.cpp (base64): Added methods to update Blob with data
    from Base64-encoded string, or to return a Base64-encoded string
    from Blob.  Still needs documentation.

2002-04-09  Dom Lachowicz    <cinamod@hotmail.com>

  - lib/Image.cpp (Image::ping): Added PingBlob function
    
2002-04-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableDashArray::operator=): Added missing
    assignment operator (fixes a bug).
    (DrawableDashArray::DrawableDashArray): Added missing copy
    constructor (fixes a bug).

  - lib/Image.cpp (oilPaint): Changed argument type from unsigned
    int to double.
    (chromaBluePrimary): Changed argument type from float to double.
    (chromaGreenPrimary): Changed argument type from float to double.
    (chromaRedPrimary): Changed argument type from float to double.
    (chromaWhitePoint): Changed argument type from float to double.
    (getConstPixels): Changed argument type of x\_ & \_y from 'int' to
    'unsigned int'.
    (getPixels): Changed argument type of x\_ & \_y from 'int' to
    'unsigned int'.

2002-04-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (debug): Added method to set ImageMagick debug
    flag so that it prints debugging information while it runs.

2002-04-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp: Fixed a bunch of bugs related to
    DrawableCompositeImage, DrawableFont, and inconsistencies
    discovered by Gimpel lint.

2002-04-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (draw): Properly delimit individual drawing
    commands so that MVG output is correct.

2002-03-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableViewbox): MVG syntax wasn't correct.

  - lib/Image.cpp (draw): Fix algorithm used to append newlines to
    MVG commands so that draw() may be invoked multiple times while
    still producing valid MVG.

2002-03-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableViewbox): New class to allow setting
    the MVG output size.

2002-03-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (print): Changed "mpr:" to "mpri:" in order to
    finally get DrawableCompositeImage to work as intended.

  - lib/Image.cpp (registerId): Bugfix. Register using
    sizeof(MagickLib::Image) rather than sizeof(Image).

2002-03-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableCompositeImage): Had failed to
    initialize width and height in object to image width and height.

2002-02-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (endianImage): New class to specify the
    endian option for formats which support this notion (e.g. TIFF).

  - lib/Image.cpp (endian): New method to specify the endian option
    for formats which support this notion (e.g. TIFF).

2002-02-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableFont): Support specifying a font via
    font-family, font-style, font-weight, and font-stretch. Wildcard
    matches are supported.

2002-02-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (charcoal): Replace Magick++'s charcoal effect
    with the output of ImageMagick's CharcoalImage function in order
    to ensure consistency.

  - lib/Magick++/CoderInfo.h (MatchType): Scope the MatchType
    enumeration to the CoderInfo class so these enumeration names can
    be re-used elsewhere without conflict.  This results in a minor
    API change to the coderInfoList() templated function since
    enumerations must be specified like "CoderInfo::TrueMatch" rather
    than just "TrueMatch".  Hopefully not a problem since this
    function and class were not documented outside of the headers
    until this release.

2002-02-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (coderInfoList): Finally wrote some
    documentation.

2002-01-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Options.cpp : Use DestroyImageList() rather than
    DestroyImage().

  - lib/Geometry.cpp (operator =): Use GetPageGeometry() rather than
    PostscriptGeometry() to parse geometry specifications containing a
    page size.

2002-01-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Remove bogus cast of blob data in readImages().

2002-01-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (throwImageException): Throwing exceptions was
    leaking memory.

  - lib/Exception.cpp (throwException): Throwing exceptions was
    leaking memory.

  - lib/Image.cpp (replaceImage): Updated to properly handle
    registration ids.
    (modifyImage): Updated to properly handle registration ids.

2002-01-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (Magick::DrawableGravity::print):
    Bugfix. Remove "Gravity" from the end of each gravity
    specification string.  Reported as PR#1084 by stefan@dotify.com.

2002-01-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp, Magick++/Include.h: Use DestroyImageList() rather
    than DestroyImages().

2002-01-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Options.h (antiAlias): Bugfix, set
    drawInfo->text\_antialias to control text antialiasing.

2002-01-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h : Imported new composition operators to
    namespace: NoCompositeOp, DarkenCompositeOp, LightenCompositeOp,
    HueCompositeOp, SaturateCompositeOp, ValueCompositeOp,
    ColorizeCompositeOp, LuminizeCompositeOp, ScreenCompositeOp,
    OverlayCompositeOp.

2001-12-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (strokePattern): New method to specify image to
    use as pattern while drawing stroked-outlines of drawn objects.
    (fillPattern): New method to specify image to use as pattern while
    filling drawn objects.
    (penTexture): Method is officially deprecated.  Don't use anymore.
    (penColor): Method is officially deprecated. Don't use anymore.

  - lib/Drawable.cpp (DrawablePushPattern): Support pushing
    (starting) pattern definition.
    (DrawablePopPattern): Support popping (terminating) pattern
    definition.

2001-12-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableCompositeImage): Read image
    immediately if provided by filename, register with persistent
    registry, and pass as perisistant image type.
    (DrawableCompositeImage): Support specifying Image in memory.
    Passed as perisistant image type.

2001-12-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Color.cpp (operator std::string): Color string buffer was
    one character too short!

2001-12-20  Bob Friesenhahn  <bfriesen@sun1107.ssd.usa.alcatel.com>

  - lib/TypeMetric.cpp (characterWidth): Eliminate method.
    (characterHeight): Eliminate method.
    (all remaining methods): Change return type to 'double'.  Fix
    documentation in source files to reflect that units are in pixels
    rather than points.
    (descent): Renamed method from 'decent' to 'descent'.

2001-11-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (Magick): Invoke DestroyMagick() to clean up
    ImageMagick allocations.

  - lib/Magick++/Include.h (ImageType): Added some missing enums to
    Magick namespace.

2001-11-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/CoderInfo.h (CoderInfo): Syntax fix.
    ImageMagick bug #975.

  - lib/Image.cpp (draw): Delete ostrstream data when it is no
    longer needed.  ImageMagick bug #988.

2001-11-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (pixelColor): Implementation didn't handle pixels
    indexes correctly.  Now it does.

2001-11-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (matteFloodfill): Coordinates are long values.
    (floodFillOpacity): New method to floodfill opacity across pixels
    matching color (within fuzz-factor) at point. Similar to
    matteFloodfill except that color is selected from starting point.

2001-10-29  Bob Friesenhahn  <bfriesen@sun1107.ssd.usa.alcatel.com>

  - lib/Image.cpp (strokeDashArray): Change to type double.
    (strokeDashOffset): Change to type double.

2001-10-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Geometry.cpp (Geometry): Add constructor from
    MagickLib::RectangleInfo.

  - lib/Image.cpp (boundingBox): Method to return smallest bounding
    box enclosing non-border pixels.

2001-10-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (getConstIndexes): Add method to obtain read-only
    pixel indexes.
    (getIndexes): Add method to obtain read-write pixel indexes.
    (Image::Image): Send warnings from Image constructor to cerr
    rather than throwing.

  - lib/Color.cpp (Color(PixelPacket&)): Change argument to const
    PixelPacket& as it should have been from the beginning.

  - lib/Image.cpp (pixelColor): Reimplemented to be a const method.

2001-10-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (getConstPixels): New method for returning a
    read-only pixel view.  Still requires documentation.

  - lib/Magick++/STL.h (coderInfoList): Fixed compilation problem
    when compiling with Visual C++.

2001-10-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Color.h (scaleQuantumToDouble): Add polymorphic
    version that accepts double to avoid downconversion error.

2001-10-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Color.h (scaleQuantumToDouble): Cast Quantum to
    double prior to division.  Hopefully fix bug.

2001-10-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Color.h (Color(const std::string)): Pass argument by reference.

  - (operator=): Pass argument by const reference.
    
2001-09-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (coderInfoList): New function to support
    obtaining format coder information (as a list of type CoderInfo).

  - lib/CoderInfo.cpp (CoderInfo): New class to support obtaining
    format coder information.

2001-09-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (depth): Use GetImageDepth and SetImageDepth
    rather than just getting/setting depth attributes.

  - lib/Magick++/STL.h (opacityImage): New unary function object to
    set, or attenuate, image pixel opacity throughout the image.

  - lib/Image.cpp (opacity): New method to set, or attenuate, image
    pixel opacity throughout the image.

  - lib/Magick++/STL.h (typeImage): New unary function object to set
    image type.

  - lib/Image.cpp (type): Added ability to set image type.

2001-09-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (write(Blob)): Tell blob to use malloc allocator.

  - lib/Blob.cpp (updateNoCopy): Added parameter so that user can
    specify the allocation system (malloc or new) the memory came
    from.  Defaults to C++ memory allocator.

2001-09-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (fileSize): Decided to change return type to off\_t
    for increased range and portability.

2001-09-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (fileSize): Changed return value to double.

2001-09-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (colorMap): Allocate a colormap if it does not
    already exist.

  - lib/Pixels.cpp (indexes): Don't attempt to validate image type.

  - lib/Image.cpp (colorMap): Optimized more for performance.

2001-09-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (fontTypeMetrics): New method to support
    retrieving font metrics.

  - lib/TypeMetric.cpp : New class to support font metrics
    information.

2001-09-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Color.h (scaleDoubleToQuantum): Inline static
    method made from previous ScaleDoubleToQuantum #define.
    (scaleQuantumToDouble): Inline static method made from previous
    ScaleQuantumToDouble #define. Helps avoid possibility of clash
    with user code.

2001-08-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (colorMap): Automatically extend colormap if
    specified index is past end of current colormap.  Colormap is
    limited to a maximum depth of MaxRGB entries.

2001-08-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (clipMask): New method to add a clip mask to the
    image.  Adds clipping to any image operation wherever the clip
    mask image is transparent.

2001-08-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (print): Add single quotes around file names
    and font specifications.

2001-07-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (read): Ensure that only a single image frame is
    read.

2001-07-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (flattenImages): New function to flatten a
    layered image.

  - lib/Montage.cpp (Montage): Montage initial defaults are no
    longer drawn from ImageInfo.  MontageInfo structure is entirely
    filled out by updateMontageInfo();

2001-07-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Montage.cpp (updateMontageInfo): Bugfix; colors which were
    intentionally specified as invalid (unset) were being ignored.
    This produced unattractive label text when doing a montage.

2001-07-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (medianFilterImage): Changed argument from
    unsigned int to const double.
    (fillColorImage): New method.
    (strokeColorImage): New method.
    (isValidImage): New method.

  - lib/Magick++/Image.h (edge): Change argument from unsigned int
    to double.
    (medianFilter): Changed argument from unsigned int to const
    double.

  - lib/Magick++/STL.h (edgeImage): Change argument from unsigned
    int to double.

  - demo/demo.cpp (main): Updated to match PerlMagick demo.

2001-06-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (shaveImage): New function to shave edges
    from image.

  - lib/Image.cpp (shave): New method to shave edges from image.

2001-06-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (quantize): Remove conditions on whether
    quantization should be done.  Now quantization is always done.

2001-06-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Image.h (blur,charcoal,emboss,sharpen): Changed
    radius and sigma parameters to match current ImageMagick defaults.

2001-02-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Options.cpp (updateDrawInfo): The updateDrawInfo() method
    was no longer needed.  Due to ImageMagick changes, calling it was
    causing some options to be lost.

2001-01-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (fillRule): New method to specify the rule to use
    when filling drawn objects.

2001-01-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (erase): New method to reset image to background
    color.
    (strokeAntiAlias): New method to control antialiasing of stroked
    objects.

2001-01-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (channel): Renamed method from 'layer' to match
    equivalent change in ImageMagick (ChannelImage).  Enumeration
    names \*Layer renamed to \*Channel.

2001-01-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Montage.h (strokeColor): New method.
    (fillColor): New method.

  - lib/Image.cpp (replaceImage): Revised logic so that an inValid
    image should be returned if a NULL pointer is passed.  Before this
    change the existing image was preserved.
    (label): Work-around ImageMagick SetImageAttribute bug.

2001-01-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp : Adjusted to ImageMagick animation parameter API
    change.

2000-12-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableCompositeImage): Support specifying
    composition rule.

2000-12-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (draw): Bugfix - the primitive string was not
    properly null terminated. It is a wonder that the code usually
    worked at all.  Thanks to afatela@marktest.pt for reporting it.

2000-12-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (deconstructImages): New STL function for
    deconstructing an image list to assist with creating an animation.
    (mosaicImages): New STL function for inlaying an image list to
    form a single coherent picture.

2000-12-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (convolve): New method to convolve image using
    user-supplied convolution matrix.
    (unsharpmask): New method to replace image with a sharpened
    version of the original image using the unsharp mask algorithm.

2000-12-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - : Adapted to ImageMagick API change which eliminates
    AnnotateInfo.

2000-12-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (annotateImage): Brought into sync with
    annotate methods in Image.

2000-12-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (annotate): Usage of Geometry parameter was
    incorrect. Geometry parameter is used to specify bounding
    area. This changes the interpretation for two of the annotate
    methods (which probably weren't usable before).

2000-11-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Color.h (alphaQuantum): Bugfix.  Due to change in
    treatment of opacity member, alphaQuantum() was not allowing value
    to be set.

2000-11-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableFillRule): New class to specify fill
    rule (see SVG's fill-rule).
    (DrawableDashOffset): New class to specify initial offset in dash
    array.
    (DrawableDashArray): New class to specify a stroke dash pattern.
    (DrawableStrokeLineCap): New class to specify the shape to be used
    at the end of open subpaths when they are stroked.
    (DrawableStrokeLineJoin): New class to specify the shape to be
    used at the corners of paths (or other vector shapes) when they
    are stroked.
    (DrawableMiterLimit): New class to specify extension limit for
    miter joins.

2000-11-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (annotate): Reimplement text rotation using affine
    member of AnnotateInfo.
    (strokeDashOffset): New method for specifying the dash offset to
    use for drawing vector objects. Similar to SVG stroke-dashoffset.
    (strokeDashArray): New method for specifying the dash pattern to
    use for drawing vector objects.  Similar to SVG stroke-dasharray
    (strokeLineCap): New method to specify the shape to be used at the
    end of open subpaths when they are stroked. Similar to SVG
    stroke-linecap.
    (strokLineJoin): New method to specify the shape to be used at the
    corners of paths (or other vector shapes) when they are
    stroked. Similar to SVG stroke-linejoin.
    (strokeMiterLimit): New method to specify the miter limit when
    joining lines using MiterJoin. Similar to SVG stroke-miterlimit.
    (strokeWidth): Renamed lineWidth method to strokeWidth.

2000-10-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Drawable.h (DrawableCompositeImage): Add a
    short-form constructor to support specifying image location and
    name, but without specifying rendered size (use existing image
    size).

2000-10-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Drawable.h (DrawablePopGraphicContext): New class
    to pop graphic context.
    (DrawablePushGraphicContext): New class to push graphic context.

  - lib/Drawable.cpp (DrawableStrokeAntialias): New class to set
    stroke antialiasing.
    (DrawableTextAntialias): New class to set text antialiasing.

2000-10-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (transformOrigin): New method to set origin of
    coordinate system for use when annotating with text or drawing
    (transformRotation): New method to set rotation for use when
    annotating with text or drawing
    (transformScale): New method to set scale for use when annotating
    with text or drawing.
    (transformSkewX): New method to set skew for use in X axis when
    annotating with text or drawing.
    (transformSkewY): New method to set skew for use in Y axis when
    annotating with text or drawing.
    (transformReset): New method to reset transformation to default.

  - lib/Drawable.cpp (DrawablePath): New class for drawing SVG-style
    vector paths.
    (PathArcArgs): New class. Argument for PathArcArgs & PathArcAbs.
    (PathArcAbs): New class. Draw arc using absolute coordinates.
    (PathArcRel): New class. Draw arc using relative coordinates.
    (PathClosePath): New class. Close drawing path.
    (PathCurvetoArgs): New class. Argument class for PathCurvetoAbs &
    PathCurvetoRel.
    (PathCurvetoAbs): New class. Cubic bezier, absolute coordinates
    (PathCurvetoRel): New class. Cubic bezier, relative coordinates
    (PathSmoothCurvetoAbs): New class. Cubic bezier, absolute
    coordinates
    (PathSmoothCurvetoRel): New class. Cubic bezier, relative
    coordinates
    (PathQuadraticCurvetoArgs): New class. Argument class for
    PathQuadraticCurvetoAbs and PathQuadraticCurvetoRel.
    (PathQuadraticCurvetoAbs): New class. Quadratic bezier, absolute
    coordinates
    (PathQuadraticCurvetoRel): New class. Quadratic bezier, relative
    coordinates
    (PathSmoothQuadraticCurvetoAbs): New class. Quadratic bezier,
    absolute coordinates
    (PathSmoothQuadraticCurvetoRel): New class. Quadratic bezier,
    relative coordinates
    (PathLinetoAbs): New class. Line to, absolute coordinates
    (PathLinetoRel): New class. Line to, relative coordinates
    (PathLinetoHorizontalAbs): New class. Horizontal lineto, absolute
    coordinates
    (PathLinetoHorizontalRel): New class. Horizontal lineto, relative
    coordinates
    (PathLinetoVerticalAbs): New class. Vertical lineto, absolute
    coordinates.
    (PathLinetoVerticalRel): New class. Vertical lineto, relative
    coordinates.
    (PathMovetoAbs): New class. Moveto, absolute coordinates
    (PathMovetoRel): New class. Moveto, relative coordinates
    
2000-10-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableSkewX): New object to apply skew in X
    direction.
    (DrawableSkewY): New object to apply skew in Y direction.

2000-10-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (edge): Change argument from 'unsigned int' to
    'double' in order to match ImageMagick API.

2000-10-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableCompositeImage): Renamed from
    DrawableImage.
    (DrawableTextDecoration): Renamed form DrawableDecoration.
    (all-classes): Complete re-write to write the drawing command to a
    stream when draw() is invoked rather than at object construction
    time. This may be somewhat slower for individual draw operations
    but but should be at least as fast for lists of drawing commands,
    and is more flexible going into the future. Drawable classes now
    inherit from DrawableBase but are passed into STL lists and Image
    draw() methods via the surrogate class Drawable.  The upshot of
    all this is that the existing published API has not been altered
    but things work much differently under the covers.

2000-10-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableStrokeColor): Renamed from
    DrawableStroke
    (DrawableFillColor): Renamed from DrawableFill
    (DrawableRotation): New class to influence object rotation.
    (DrawableScaling): New class to influence object scaling.
    (DrawableTranslation): New class to influence object translation.

2000-10-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableAffine): New class to influence object
    scaling, rotation, and translation (as defined by SVG XML).
    (DrawableAngle): New class to influence drawing angle.
    (DrawableDecoration): New class to influence text decoration such
    as underline.
    (DrawableFill): New class to set object filling color.
    (DrawableFillOpacity): New class to set opacity to use when
    filling object.
    (DrawableFont::): New class to set font.
    (DrawableGravity): New class to set text placement gravity.
    (DrawablePointSize): New class to set font point size.
    (DrawableStroke): New class to set drawing stroke color.
    (DrawableStrokeOpacity): New class to set drawing stroke opacity.
    (DrawableStrokeWidth): New class to set drawing stroke width.

2000-10-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableImage): Added width and height
    parameters to specify size to scale rendered image to.  This is
    actually a bug-fix since it seems that the correct drawing command
    was no longer being generated.

2000-09-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (read): New overloaded method to read an image
    based on an array of raw pixels, of specified type and mapping, in
    memory.
    (write): New overloaded method to write image to an array of
    pixels, of specified type and mapping.
    (Image): New overloaded constructor to construct an image based on
    an array of raw pixels, of specified type and mapping, in memory.

2000-09-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (colorize): API change to match change in
    ImageMagick.  Now accepts percentage of red, green, and blue to
    colorize with using specified pen color.

2000-09-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Drawable.h: Reverted Coordinate implementation back
    from and STL pair based implementation to a simple class.  Maybe
    this will improve portability.  It is more understandable anyway.

2000-09-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Options.cpp : Bugfix.  Some DrawInfo attributes were not
    being updated.  This lead to options like fontPointsize not
    changing the font.

2000-08-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (blurImage, charcoalImage, embossImage,
    sharpenImage): Expand order\_ argument to radius\_ & sigma\_
    arguments for more control (matches ImageMagick API change).

  - lib/Image.cpp (blur, charcoal, emboss, sharpen): Expand order\_
    argument to radius\_ & sigma\_ arguments for more control (matches
    ImageMagick API change).

2000-08-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (read): Check returned Image for embedded
    exception, as well as the existing parameter check.  This fixes
    the bug that warnings are not reported.

2000-07-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - test/\*.cpp demo/\*.cpp: Added call to MagickIncarnate() to set
    ImageMagick install location for Windows.  Hopefully this hack can
    be removed someday.

2000-07-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (colorFuzz): Changed type to 'double' from
    'unsigned int' to match change in ImageMagick.

  - lib/Color.cpp (Color\*): Added copy constructor from base class.
    (operator =): Added assignment operator from base class.

2000-06-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h : Changed enumeration FilterType to
    FilterTypes, and QuantumTypes to QuantumType in order to match
    last-minute API change in ImageMagick.

2000-06-22  Bob Friesenhahn <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Pixels.cpp (indexes): Bugfix, use
    GetCacheViewIndexes() rather than GetIndexes().

2000-05-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Montage.h (gravity): Type of gravity\_ argument, and
    return value changed from 'unsigned int' to GravityType.

2000-04-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (DrawableArc, DrawableBezier, DrawablePolyline,
    RoundRectangle): Added support for new drawing objects.

2000-04-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp: Removed all public methods which accept
    Coordinate arguments except those that accept lists of
    Coordinates.  Converted remaining drawable object methods into
    individual classes which inherit from Drawable (e.g. "circle"
    becomes "DrawableCircle"). The constructor for each class is
    compatible with the original method. This results in annoying
    changes to user code but provides more implementation flexibility.

2000-04-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp
    (fillEllipse,fillRectangle,fillCircle,fillPolygon): Removed
    methods.  Object filling is now based on whether fillColor or
    penTexture are valid or not.  This reflects ImageMagick internal
    changes.

  - lib/Image.cpp (fillColor): New method to specify fill color when
    drawing objects.
    (strokeColor): New method to specify outline color when drawing
    objects.
    (penColor): Setting penColor now sets fillColor and
    strokeColor. Getting penColor retrieves the value of
    strokeColor. This supports backwards compatibility.

2000-03-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (lineWidth): Type changed from unsigned int to
    double.

2000-03-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (Magick): 

2000-03-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h
    (blurImage,charcoalImage,edgeImage,embossImage,
    reduceNoiseImage,sharpenImage): Modified to support order of the
    pixel neighborhood. Backward compatible function objects
    constructors are provided for embossImage, and reduceNoiseImage.

  - lib/Image.cpp (blur,charcoal,edge,emboss,reduceNoise,sharpen):
    Now accept unsigned int argument which represents the order of the
    pixel neighborhood (e.g. 3).  This is not a backwards compatible
    change, however, backward compatible methods are provided for
    emboss, and reduceNoise.

2000-03-02  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Pixels.h (Pixels): Moved Image pixel methods to
    Pixels class.

2000-02-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (annotate): Re-wrote to improve performance.
    (draw): Re-wrote to improve performance.

2000-02-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Drawable.cpp (text): Bugfix: support spaces in annotation
    text.

2000-02-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (gaussianBlurImage): New function object to
    Gaussian blur image.

  - lib/Image.cpp (gaussianBlur): New method to Gaussian blur image.

2000-02-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp : Call-back based LastError class is eliminated in
    favor of ImageMagick 5.2's re-entrant ExceptionInfo reporting.
    This should make Magick++ thread safe under Win32.

2000-02-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (floodFillTexture): Fixed bug due to pixel pointer
    becoming invalid in ImageMagick function.

2000-01-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp : Added locking to reference counting to ensure
    thread (pthread) safety.

  - lib/Blob.cpp : Added locking to reference counting to ensure
    thread (pthread) safety.

  - lib/LastError.cpp: Added support for thread specific data
    (pthreads) so that error reporting is thread safe.

  - lib/Magick++/Thread.h: Added thread wrapper class to provide
    thread-safe locking (pthreads) to Magick++.

2000-01-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp: Added methods getPixels, setPixels, syncPixels,
    readPixels, and writePixels, in order to provide low-level access
    to Image pixels.  This approach (direct wrapper around ImageMagick
    functions) does not mean that the planned object-oriented wrapper
    has been forgotten, only that this wrapper is not ready yet, and
    users need to manipulate pixels \*now\*.

2000-01-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/LastError.cpp: Complete re-implementation of LastError so
    that it hides its implementation.  Also assures that all memory is
    explicitly deallocated at program exit to avoid the appearance of
    a leak.

2000-01-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (size): Bug-fix. Set image columns and rows as
    well as image options columns and rows.

  - lib/Image.cpp :Depth parameters are now all unsigned in for
    consistency.

  - lib/Image.cpp (write): Parameters for writing Blobs re-arranged
    again to hopefully be more sensible.

  - lib/Magick++/STL.h: Bug-fix. Re-number scenes from zero when
    linking image range in container into a list. This provides
    expected results.

1999-12-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp
    (write): Additional overloaded methods for BLOBs.
    (read): Additional overloaded methods for BLOBs. Re-ordered
    parameters for one existing method.
    (Image): Additional overloaded methods for BLOBs.  Re-ordered
    parameters for one existing method.

1999-12-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (floodFillTexture): Changed coordinates to
    unsigned.

1999-12-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (medianFilter): New method.

1999-12-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (density): Bug fix. Was not setting image x & y
    density.

1999-11-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (page): psPageSize() is renamed to page() and now
    properly returns the attribute from the image.

1999-11-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp: Rename transformColorSpace() to colorSpace().
    Added colorSpace() accessor method.

1999-11-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Color.cpp: Re-implemented PixelPacket pointer so that it is
    never NULL and added a 'valid' field for tracking object validity.

1999-11-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (quantizeError): Eliminated method.

1999-11-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (annotate & draw): Changed implementation to
    reflect change to the way AnnotateInfo is managed by ImageMagick.

1999-11-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (cacheThreshold): New method to set the pixel
    cache threshold.

  - lib/Magick++/Include.h (Magick): Added new enumerations from
    classify.h.

1999-10-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Options.h (fontPointsize): Argument is now a double
    to match change in ImageMagick.

  - lib/Image.cpp (fontPointsize): Argument is now a double to match
    change in ImageMagick.

1999-10-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Blob.cpp (BlobRef): Bugfix -- start blob reference count at
    one rather than zero.

1999-10-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (Image): Fixed Image constructors from Blob.  The
    image reference was not being instantiated as it should have been,
    causing a crash.

1999-10-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Blob.cpp: All blob length parameters are now of type size\_t.

  - lib/Image.cpp (write): Length estimate is now of type size\_t.

1999-09-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (rotate): No longer accepts a crop option since
    ImageMagick no longer supports this.
    (shear): No longer accepts a crop option since ImageMagick no
    longer supports this.

1999-09-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp:
    (rotate): No longer accepts sharpen argument.  User must sharpen
    separately if desired.  This change is due to a similar change in
    ImageMagick 5.0.
    (condense): Removed method.
    (uncondense): Removed method.
    (condensed): Removed method.
    (pixelColor): Adapted to 5.0.

  - lib/Magick++/Color.h : Rewrote to efficiently use ImageMagick
    5.0's PixelPacket color representation.

  - lib/Color.cpp : Rewrote to efficiently use ImageMagick 5.0's
    PixelPacket color representation.

1999-09-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (condensed): Bug fix.  The condensed() method was
    returning the opposite bool value than it should.  Oops!

1999-09-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Include.h (MagickLib): Eliminated requirement for
    including <magick/define.h>.

1999-08-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp: Added accessor methods for other key ImageMagick
    structs.

  - lib/Options.cpp (penTexture): Fixed bug with removing texture
    caused by change in Image constructor.

  - lib/Image.cpp: Changed strategy such that an Image containing a
    null MagickLib::Image pointer is never constructed except for
    under error conditions.  Removed existing checks for null image
    pointer on attribute methods.
    Use image() and constImage() accessor methods as part of Image
    implementation in order to clean-up code and ensure
    const-correctness.
    
1999-08-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/STL.h (Magick): Added STL function readImages().
    Not tested yet.
    (Magick): Added STL function writeImages(). Not tested yet.

  - lib/Image.cpp: Removed support for 'text' attribute as this is
    no longer present in ImageMagick as of 4.2.8.

1999-07-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Image.cpp (condense): Skip condensing image if already
    condensed.
    (uncondense): Skip uncondensing image if not condensed.
    (condensed): New method to test if image is condensed.
    (classType): New method which supports conversion of the image
    storage class. May result in loss of color information
    (quantization is used) if a DirectClass image is converted to
    PseudoClass.

1999-07-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Magick++/Color.h (Magick::Color): Color parameters are now
    stored in a MagickLib::RunlengthPacket structure which is
    referenced via a pointer.  This structure is either allocated by a
    Magick::Color constructor or passed as an argument to a
    Magick::Color constructor so that it may refer to to a
    MagickLib::Image pixel. The owner of the structure is managed so
    that the structure is only deleted if it was allocated by
    Magick::Color.

1999-07-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - overall : Removed 'Magick' prefix from all source file
    names. Moved class headers to Magick++ subdirectory.  This should
    not break any code using the documented interface (via
    Magick++.h).

1999-07-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickImage.cpp (composite): Support composition placement
    by gravity like PerlMagick does.

1999-07-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickImage.cpp (Image): Added constructors to construct an
    Image from a BLOB.

1999-07-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/manipulate.cpp (main): Wrote a basic sanity test for
    reading and writing BLOBS.

1999-06-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickImage.cpp (read): Added support for reading an encoded
    image stored in a BLOB.  Uses new ImageMagick APIs introduced on
    July 21, 1999.
    (write): Added support for writing an encoded image to a BLOB.

1999-06-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickInclude.h : Use new <magick/api.h> interface to
    ImageMagick to avoid namespace-induced problems.

  - configure.in : CPPFLAGS and LDFLAGS specified via the
    environment take precedence over flags from Magick-config.

1999-05-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickSTL.h (mapImages): New algorithm to map the sequence
    of images to the color map of a provided image.
    (quantizeImages): New algorithm to quantize a sequence of images
    to a common color map.

1999-05-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickBlob.cpp (updateNoCopy): New method to allow derived
    classes to insert data into the base class without making a copy
    of the data. This represents a transfer of ownership of the data
    from the derived class to the base class.

1999-05-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickColor.cpp (operator =): Adapted to new ImageMagick
    4.2.6 as of 5/23/99 which removes X11 compatibility functions.

  - lib/MagickGeometry.cpp (operator =): Adapted to new ImageMagick
    4.2.6 as of 5/23/99 which removes X11 compatibility functions.

1999-05-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickBlob.cpp (Blob): Support default constructor for Blob.

1999-05-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickSTL.h (transformColorSpaceImage): New unary function
    object to invoke transformColorSpace on STL container object.

  - lib/MagickImage.cpp (transformColorSpace): New method to
    transform the image data to a new colorspace.

1999-05-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickImage.cpp (ping): Re-implemented to match (requested)
    API change in ImageMagick 4.2.5. Method signature has changed to
    be like 'read'.
    (annotate): Added two new overloaded methods for text annotation
    in order to support the new rotated text capability in ImageMagick
    4.2.5.  To accomplish this, the default for gravity had to be
    removed from several methods. This may impact existing code.
    Still not sure if this is the best set of method signatures.

1999-05-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickImage.cpp (ping): New method to obtain image size in
    bytes and geometry without the overhead of reading the complete
    image.
    (uncondense): New method to uncompress run-length encoded pixels
    into a simple array to make them easy to operate on.

1999-05-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickImage.cpp (comment): Passing an empty string as the
    comment results in no comment at all rather than a comment with no
    data.

1999-05-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickImage.cpp (iccColorProfile): Implemented method to set
    ICC color profile from opaque object in memory (must be formatted
    outside of Magick++).
    (iptcProfile): Implemented method to set IPTC profile from opaque
    object in memory (must be formatted outside of Magick++).

  - lib/MagickBlob.cpp: New class to support managing user-supplied
    opaque Binary Large OBjects (BLOBS) in the API. Reference counted
    to improve semantics and to possibly reduce memory consumption.

1999-05-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/Makefile.am (libMagick): Updated to use libtool 1.3 so that
    shared library can be built.

1999-04-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickImage.cpp (montageGeometry): Return Magick::Geometry
    rather than std::string.

1999-04-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickColor.cpp (alpha): Added support for setting alpha via
    scaled-double to the Color class.  The new method name is 'alpha'.

1999-04-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - lib/MagickColor.cpp: Added support for setting an alpha value
    (unscaled Quantum only) for use on DirectColor images that have
    matte enabled.  This requires ImageMagick 4.2.2 dated April 13,
    1999 or later to compile since Cristy added a special flag to
    allow testing to see if the user has specified an opacity value:
    "I added XColorFlags to magick/classify.h.  If DoMatte is set in
    color->flags then the opacity value is valid in color->pixel."

1999-04-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - demo/flip.cpp (main): New file.  Demonstrates use of flipImage
    function object as well as morphImages algorithm.

1999-04-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - tests/color.cpp : New file to support testing the Magick::Color
    classes.

  - lib/MagickOptions.cpp: The ImageInfo filter member is now
    ignored by ImageMagick (as of ImageMagick 4.2.2 April 10, 1998) so
    support for setting it is removed. The Image filter member is
    still updated. According to Cristy, this ImageMagick version
    removes automatic sharpening of resized images.  The blur member
    is added to the Image structure. A blur value < 1 causes the image
    to be sharpened when resizing while a value > 1 leaves the image
    blurry.  Magick++ does not yet support the blur member.


