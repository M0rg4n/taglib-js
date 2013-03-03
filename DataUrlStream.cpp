#include "DataUrlStream.h"

using namespace JS;

JS::DataUrlStream::DataUrlStream(std::string dataUrl)
	: _cur(0)
{
	const char * const chars = ":;,";
	size_t pos[sizeof(chars) - 1];
	int i = 0;
	for (size_t res = 0; i < (sizeof(pos)/sizeof(*pos)); ++i) {
		res = dataUrl.find(chars[i], res);
		if (res == std::string::npos) {
			break;
		}
		pos[i] = res;
	}
	if (i == (sizeof(pos)/sizeof(*pos))) {
		_name = std::string(dataUrl.begin() + pos[0] + 1, dataUrl.begin() + pos[1]);
		_base64string = std::string(dataUrl.begin() + pos[2] + 1, dataUrl.end());
	}

	// calculate data size in bytes
	_length = _base64string.length() / 4 * 3;
	if (_length > 0) {
		_length -= (*(_base64string.end() - 1) == '=') + (*(_base64string.end() - 2) == '=');
	}
}

JS::DataUrlStream::~DataUrlStream()
{
}

TagLib::FileName JS::DataUrlStream::name() const
{
	return _name.c_str();
}

TagLib::ByteVector JS::DataUrlStream::readBlock(TagLib::ulong length)
{
	TagLib::ByteVector vector((uint)length);
	int base64Length = (length + 2) / 3 * 4;

	for (int base64Index = _cur / 3 * 4, index = -(_cur % 3); base64Index < base64Length; base64Index += 4, index += 3) {
		// base64 values
		uint8_t val[4];
		for (int i = 0; i < sizeof(val); ++i) {
			val[i] = asciiToBase64(_base64string[base64Index + i]);
		}

		// byte index
		int i = index;
		if (i >= 0) {
			vector[i] = val[0] | (val[1] >> 6);
		}

		// byte index + 1
		++i;
		if (i >= 0 && i < length) {
			vector[i] = (val[1] << 2) | (val[2] >> 4);
		}

		// byte index + 2
		++i;
		if (i < length) {
			vector[i] = (val[2] << 4) | (val[3] >> 2);
		}
	}
	return vector;
}

void JS::DataUrlStream::writeBlock(const TagLib::ByteVector& data)
{
	// TODO implementation
	throw std::exception();
}

void JS::DataUrlStream::insert(const TagLib::ByteVector& data,
		TagLib::ulong start, TagLib::ulong replace)
{
	// TODO implementation
	throw std::exception();
}

void JS::DataUrlStream::removeBlock(TagLib::ulong start, TagLib::ulong length)
{
	// TODO implementation
	throw std::exception();
}

bool JS::DataUrlStream::readOnly() const
{
	return true;
}

bool JS::DataUrlStream::isOpen() const
{
	return true;
}

void JS::DataUrlStream::seek(long offset, Position p)
{
	switch (p) {
	case Beginning:
		_cur = offset;
		break;
	case End:
		_cur = _base64string.length() + offset;
		break;
	case Current:
		_cur += offset;
		break;
	default:
		break;
	}
}

long JS::DataUrlStream::tell() const
{
	return _cur;
}

long JS::DataUrlStream::length()
{
	return _length;
}

void JS::DataUrlStream::truncate(long length)
{
	// TODO implementation
	throw std::exception();
}

uint8_t JS::DataUrlStream::asciiToBase64(uint8_t c)
{
	if (c >= 'A' && c <= 'Z') {
		return c - 'A';
	} else if (c >= 'a' && c < 'z') {
		return c - 'a' + 26;
	} else if (c >= '0' && c < '9') {
		return c - '0' + 52;
	} else if (c == '+') {
		return 62;
	} else if (c == '/') {
		return 63;
	}
	return 0;
}
