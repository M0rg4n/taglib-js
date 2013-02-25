#include "Tag.h"

using namespace JS;

Tag::Tag(boost::shared_ptr<TagLib::File> file)
	: _file(file)
{
	_tag = _file->tag();

	registerProperty("title", make_property(this, &Tag::title, &Tag::setTitle));
	registerProperty("artist", make_property(this, &Tag::artist, &Tag::setArtist));
	registerProperty("album", make_property(this, &Tag::album, &Tag::setAlbum));
	registerProperty("comment", make_property(this, &Tag::comment, &Tag::setComment));
	registerProperty("genre", make_property(this, &Tag::genre, &Tag::setGenre));
	registerProperty("year", make_property(this, &Tag::year, &Tag::setYear));
	registerProperty("track", make_property(this, &Tag::track, &Tag::setTrack));
	registerMethod("isEmpty", make_method(this, &Tag::isEmpty));
}

Tag::~Tag()
{

}

String Tag::title() const
{
	return _tag->title().to8Bit();
}

String Tag::artist() const
{
	return _tag->artist().to8Bit();
}

String Tag::album() const
{
	return _tag->album().to8Bit();
}

String Tag::comment() const
{
	return _tag->comment().to8Bit();
}

String Tag::genre() const
{
	return _tag->genre().to8Bit();
}

uint Tag::year() const
{
	return _tag->year();
}

uint Tag::track() const
{
	return _tag->track();
}

void Tag::setTitle(const String &s)
{
	_tag->setTitle(TagLib::String(s));
}

void Tag::setArtist(const String &s)
{
	_tag->setArtist(TagLib::String(s));
}

void Tag::setAlbum(const String &s)
{
	_tag->setAlbum(TagLib::String(s));
}

void Tag::setComment(const String &s)
{
	_tag->setComment(TagLib::String(s));
}

void Tag::setGenre(const String &s)
{
	_tag->setGenre(TagLib::String(s));
}

void Tag::setYear(uint i)
{
	_tag->setYear(i);
}

void Tag::setTrack(uint i)
{
	_tag->setTrack(i);
}

bool Tag::isEmpty() const
{
	return _tag->isEmpty();
}
