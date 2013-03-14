#pragma once
#include "JSAPIAuto.h"
#include "taglib/tfile.h"
#include "Tag.h"

namespace JS {
    
class File : public FB::JSAPIAuto
{
public:
    File(FB::JSObjectPtr arrayBufferStream);

    virtual ~File();

    boost::shared_ptr<Tag> tag();

    void save(const FB::JSObjectPtr &callback);

    /* TODO
    boost::shared_ptr<std::map<String, boost::shared_ptr<StringList>>> properties() const;

    boost::shared_ptr<StringList> unsupportedData();

    boost::shared_ptr<AudioProperties> audioProperties() const;

    boost::shared_ptr<std::vector<uint8_t>> toByteArray() const;
    */

private:
    boost::shared_ptr<TagLib::IOStream> _stream;
    boost::shared_ptr<TagLib::File> _file;

    void saving(const FB::JSObjectPtr &callback);
};
    
}
