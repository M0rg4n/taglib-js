#include "File.h"
#include "taglib/tbytevectorstream.h"
#include "taglib/mpegfile.h"
#include "taglib/id3v2framefactory.h"

using namespace JS;

File::File(const uint8_t* data, uint length)
	: _stream(boost::make_shared<TagLib::ByteVectorStream>(TagLib::ByteVector((const char *)data, length)))
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
