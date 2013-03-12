#include "ArrayBufferStream.h"

using namespace JS;

ArrayBufferStream::ArrayBufferStream(boost::shared_ptr<FB::JSObject> arrayBufferStream)
	: _arrayBufferStream(arrayBufferStream)
	, _curr(0)
{
	FB::variant variant = _arrayBufferStream->Invoke("length", FB::variant_list_of());
	_length = variant.convert_cast<long>();
}

ArrayBufferStream::~ArrayBufferStream()
{
}

TagLib::FileName ArrayBufferStream::name() const
{
	return TagLib::FileName(""); // XXX do we need a name?
}

TagLib::ByteVector ArrayBufferStream::readBlock(TagLib::ulong length)
{
	FB::variant variant = _arrayBufferStream->Invoke("readBlock", FB::variant_list_of
			(static_cast<int>(length))
			(static_cast<int>(_curr)));
	std::vector<char> block = variant.convert_cast<std::vector<char> >();
	_curr += block.size();
	return TagLib::ByteVector(block.data(), block.size());
}

void ArrayBufferStream::writeBlock(const TagLib::ByteVector& data)
{
	_arrayBufferStream->Invoke("writeBlock", FB::variant_list_of
			(std::vector<char>(data.begin(), data.end()))
			(static_cast<int>(_curr)));
	_curr += data.size();
}

void ArrayBufferStream::insert(const TagLib::ByteVector& data,
		TagLib::ulong start, TagLib::ulong replace)
{
	_arrayBufferStream->Invoke("insert", FB::variant_list_of
			(std::vector<char>(data.begin(), data.end()))
			(static_cast<int>(start))
			(static_cast<int>(replace)));
	_length += data.size() - replace;
	_curr = start + data.size();
}

void ArrayBufferStream::removeBlock(TagLib::ulong start, TagLib::ulong length)
{
	_arrayBufferStream->Invoke("removeBlock", FB::variant_list_of
			(static_cast<int>(start))
			(static_cast<int>(length)));
	_length -= length;
	_curr = _length;
}

bool ArrayBufferStream::readOnly() const
{
	return false;
}

bool ArrayBufferStream::isOpen() const
{
	return true;
}

void ArrayBufferStream::seek(long offset, Position p)
{
	switch (p) {
	case Beginning:
		_curr = offset;
		break;
	case Current:
		_curr += offset;
		break;
	case End:
		_curr = _length - offset;
		break;
	}
}

long ArrayBufferStream::tell() const
{
	return _curr;
}

long ArrayBufferStream::length()
{
	return _length;
}

void ArrayBufferStream::truncate(long length)
{
	_arrayBufferStream->Invoke("truncate", FB::variant_list_of(static_cast<int>(length)));
	_length = length;
}
