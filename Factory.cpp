#include "FactoryBase.h"
#include "Plugin.h"
#include <boost/make_shared.hpp>

namespace JS {

class PluginFactory : public FB::FactoryBase
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// @fn FB::PluginCorePtr createPlugin(const std::string& mimetype)
    ///
    /// @brief  Creates a plugin object matching the provided mimetype
    ///         If mimetype is empty, returns the default plugin
    ///////////////////////////////////////////////////////////////////////////////
    FB::PluginCorePtr createPlugin(const std::string& mimetype)
    {
        return boost::make_shared<Plugin>();
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    /// @see FB::FactoryBase::globalPluginInitialize
    ///////////////////////////////////////////////////////////////////////////////
    void globalPluginInitialize()
    {
        Plugin::StaticInitialize();
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    /// @see FB::FactoryBase::globalPluginDeinitialize
    ///////////////////////////////////////////////////////////////////////////////
    void globalPluginDeinitialize()
    {
        Plugin::StaticDeinitialize();
    }

    void getLoggingMethods(FB::Log::LogMethodList& outMethods)
    {
        // The next line will enable logging to the console (think: printf).
        outMethods.push_back(std::make_pair(FB::Log::LogMethod_Console, std::string()));

        // The next line will enable logging to a logfile.
        //outMethods.push_back(std::make_pair(FB::Log::LogMethod_File, "/foo/bar/baz.log"));

        // Obviously, if you use both lines, you will get output on both sinks.
    }

    FB::Log::LogLevel getLogLevel(){
        return FB::Log::LogLevel_Debug; // Now Debug and above is logged.
    }
};
    
}

///////////////////////////////////////////////////////////////////////////////
/// @fn getFactoryInstance()
///
/// @brief  Returns the factory instance for this plugin module
///////////////////////////////////////////////////////////////////////////////
FB::FactoryBasePtr getFactoryInstance()
{
    static boost::shared_ptr<JS::PluginFactory> factory = boost::make_shared<JS::PluginFactory>();
    return factory;
}
