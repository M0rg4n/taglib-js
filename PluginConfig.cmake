#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for TagLib Audio Meta-Data Library
#
#\**********************************************************/

set(PLUGIN_NAME "TagLib")
set(PLUGIN_PREFIX "TLAML")
set(COMPANY_NAME "VSarychev")

# ActiveX constants:
set(FBTYPELIB_NAME TagLibLib)
set(FBTYPELIB_DESC "TagLib 1.0 Type Library")
set(IFBControl_DESC "TagLib Control Interface")
set(FBControl_DESC "TagLib Control Class")
set(IFBComJavascriptObject_DESC "TagLib IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "TagLib ComJavascriptObject Class")
set(IFBComEventSource_DESC "TagLib IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID d12af5cc-bd0c-5e6b-a07b-0bf517d725fb)
set(IFBControl_GUID f6629d68-a6c9-5fa4-a6a3-ee1f121117d6)
set(FBControl_GUID 4d9a3576-401d-5bde-927a-30e578dabc10)
set(IFBComJavascriptObject_GUID 991725d3-89f5-5b14-84bb-49f21013a9ae)
set(FBComJavascriptObject_GUID b9c33144-fbb2-5407-86e9-7a2822ecffe5)
set(IFBComEventSource_GUID 15210a17-35d2-5486-b68e-7d87a5b5d6fb)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 51488a94-ec0b-520c-8593-c542af3111e2)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 88f69229-f7cf-5cca-a46b-4b468f46096b)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "VSarychev.TagLib")
set(MOZILLA_PLUGINID "vsarychev.ru/TagLib")

# strings
set(FBSTRING_CompanyName "Valentin Sarychev")
set(FBSTRING_PluginDescription "TagLib Audio Meta-Data Library port for web browsers")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2013 Valentin Sarychev")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
set(FBSTRING_ProductName "TagLib Audio Meta-Data Library")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "TagLib Audio Meta-Data Library")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "TagLib Audio Meta-Data Library_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-taglib")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 0)
set(FBMAC_USE_COCOA 0)
set(FBMAC_USE_COREGRAPHICS 0)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
