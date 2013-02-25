#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "Plugin.h"

namespace JS {

class PluginAPI : public FB::JSAPIAuto
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// @fn PluginAPI::PluginAPI(const PluginPtr& plugin, const FB::BrowserHostPtr host)
    ///
    /// @brief  Constructor for your JSAPI object.
    ///         You should register your methods, properties, and events
    ///         that should be accessible to Javascript from here.
    ///
    /// @see FB::JSAPIAuto::registerMethod
    /// @see FB::JSAPIAuto::registerProperty
    /// @see FB::JSAPIAuto::registerEvent
    ////////////////////////////////////////////////////////////////////////////
    PluginAPI(const PluginPtr& plugin, const FB::BrowserHostPtr& host) :
        m_plugin(plugin), m_host(host)
    {
        registerMethod("parse", make_method(this, &PluginAPI::parse));
        
        // Read-only property
        registerProperty("version", make_property(this,
                                                  &PluginAPI::get_version));
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn PluginAPI::~PluginAPI()
    ///
    /// @brief  Destructor.  Remember that this object will not be released until
    ///         the browser is done with it; this will almost definitely be after
    ///         the plugin is released.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~PluginAPI() {};

    PluginPtr getPlugin();

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Create File object and return it through callback
    void parse(const std::vector<uint8_t>& data, const FB::JSObjectPtr& callback);

private:
    PluginWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

}
