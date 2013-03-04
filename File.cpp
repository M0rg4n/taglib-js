#include "File.h"
#include "taglib/tbytevectorstream.h"
#include "taglib/mpegfile.h"
#include "taglib/id3v2framefactory.h"
#include "ArrayBufferStream.h"

using namespace JS;

File::File(FB::JSObjectPtr arrayBufferStream)
	: _stream(boost::static_pointer_cast<TagLib::IOStream>(boost::make_shared<ArrayBufferStream>(arrayBufferStream)))
	, _file(boost::make_shared<TagLib::MPEG::File>(_stream.get(), TagLib::ID3v2::FrameFactory::instance()))
{
    registerMethod("tag", make_method(this, &File::tag));
}

File::~File()
{

}

boost::shared_ptr<Tag> File::tag()
{
	return boost::make_shared<Tag>(_file);
}
