#include "ArrayBufferStream.h"

using namespace JS;

ArrayBufferStream::ArrayBufferStream(boost::shared_ptr<FB::JSObject> arrayBufferStream)
	: _arrayBufferStream(arrayBufferStream)
	, _curr(0)
{
	FB::variant variant = _arrayBufferStream->Invoke("length", FB::variant_list_of());
	_length = variant.cast<int>();
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
	FB::variant variant = _arrayBufferStream->Invoke("readBlock", FB::variant_list_of(_curr)(_curr + length));
	std::vector<char> block = variant.convert_cast<std::vector<char> >();
	_curr += block.size();
	return TagLib::ByteVector(block.data(), block.size());
}

void ArrayBufferStream::writeBlock(const TagLib::ByteVector& data)
{
	throw std::exception();
}

void ArrayBufferStream::insert(const TagLib::ByteVector& data,
		TagLib::ulong start, TagLib::ulong replace)
{
	throw std::exception();
}

void ArrayBufferStream::removeBlock(TagLib::ulong start, TagLib::ulong length)
{
	throw std::exception();
}

bool ArrayBufferStream::readOnly() const
{
	return true;
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
	throw std::exception();
}
