.. -*- mode: rst -*-
.. This text is in reStucturedText format, so it may look a bit odd.
.. See http://docutils.sourceforge.net/rst.html for details.

=======================================
GraphicsMagick Programming Interfaces
=======================================

.. meta::
   :description: GraphicsMagick is a robust collection of tools and libraries to read,
                 write, and manipulate an image in any of the more popular
                 image formats including GIF, JPEG, PNG, PDF, and Photo CD.
                 With GraphicsMagick you can create GIFs dynamically making it
                 suitable for Web applications.  You can also resize, rotate,
                 sharpen, color reduce, or add special effects to an image and
                 save your completed work in the same or differing image format.

   :keywords: GraphicsMagick, Image Magick, Image Magic, PerlMagick, Perl Magick,
              Perl Magic, image processing, software development, image, software,
              Magick++


.. _`C Core` : api/api.html
.. _`C Wand` : wand/wand.html
.. _C++ : Magick++/index.html
.. _Go : https://github.com/gographics/gmagick
.. _`node.js` : https://github.com/aheckmann/gm
.. _`Lua` : https://github.com/arcapos/luagraphicsmagick
.. _PHP : https://github.com/vitoc/gmagick
.. _Perl : perl.html
.. _Python: https://github.com/hhatto/pgmagick
.. _`Redis Module` : https://github.com/RedisLabsModules/graphicsmagick
.. _`Ruby (RMagick)` : https://github.com/rmagick-temp/rmagick
.. _`Ruby (MiniMagick)` : https://github.com/minimagick/minimagick
.. _Tcl/Tk : http://www.graphicsmagick.org/TclMagick/doc/
.. _Windows OLE : ImageMagickObject.html
.. _`GraphicsMagick .NET` : https://github.com/dlemstra/GraphicsMagick.NET



GraphicsMagick capabilities may be accessed from many languages and scripting
environments via programming APIs as shown in the following table:

======================  ====================================================================
Language                Description
======================  ====================================================================
`C Core`_               C language API for the lowest-level core programming interface.
`C Wand`_               C language API for the mid-level Wand API programming interface.
`C++`_                  Magick++ provides an abstract object-oriented C++ interface.
`Go`_                   Native Go binding to GraphicsMagick's MagickWand C API
`Lua`_                  GraphicsMagick for Lua interfaces to GraphicsMagick's Wand API.
`node.js`_              Graphicsmagick for node.js provides server-side support for
                        Javascript programming with node.js.
PHP_                    Gmagick provides a small and fast extension for PHP.
Perl_                   PerlMagick provides an object-oriented Perl interface.
Python_                 PgMagick provides the power and ease of the C++ API, but in Python.
`Redis Module`_         Image processing via redis APIs
`Ruby (RMagick)`_       RMagick provides a native Ruby language extension
`Ruby (MiniMagick)`_    MiniMagick provides a Ruby language extension via a command line
                        wrapper.
`Tcl/Tk`_               TclMagick provides a scripting environment based on Tcl or Tcl/Tk.
`GraphicsMagick .NET`_  GraphicsMagick.NET by Dirk Lemstra provides a Windows .NET
                        programming interface, allowing use of GraphicsMagick features
                        via a stand-alone package.
`Windows OLE`_          The ImageMagickObject OLE control supports utility-style access via
                        a COM+ object.
======================  ====================================================================

*Some of these languages and scripting environments are supported by the
GraphicsMagick Group while others are developed and supported by third parties.*
