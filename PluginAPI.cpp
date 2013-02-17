#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"
#include "PluginAPI.h"

using namespace JS;

///////////////////////////////////////////////////////////////////////////////
/// @fn FB::variant PluginAPI::echo(const FB::variant& msg)
///
/// @brief  Echos whatever is passed from Javascript.
///         Go ahead and change it. See what happens!
///////////////////////////////////////////////////////////////////////////////
FB::variant PluginAPI::echo(const FB::variant& msg)
{
    return msg;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn PluginPtr PluginAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
PluginPtr PluginAPI::getPlugin()
{
    PluginPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

// Read-only property version
std::string PluginAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}
