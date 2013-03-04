#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"
#include <boost/make_shared.hpp>
#include "PluginAPI.h"
#include "File.h"
#include <boost/lexical_cast.hpp>

using namespace JS;

void PluginAPI::parse(FB::JSObjectPtr arrayBufferStream, const FB::JSObjectPtr &callback)
{
	boost::shared_ptr<File> file = boost::make_shared<File>(arrayBufferStream);
    callback->InvokeAsync("", FB::variant_list_of(file));
}

PluginPtr PluginAPI::getPlugin()
{
    PluginPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

std::string PluginAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}
