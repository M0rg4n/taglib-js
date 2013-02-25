#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"
#include <boost/make_shared.hpp>
#include "PluginAPI.h"
#include "File.h"

using namespace JS;

void PluginAPI::parse(const std::vector<uint8_t> &data, const FB::JSObjectPtr &callback)
{
    callback->InvokeAsync("", FB::variant_list_of(boost::make_shared<File>(data.data(), data.size())));
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
