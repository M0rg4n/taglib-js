#pragma once
#include <sys/types.h>
#include "JSAPIAuto.h"
#include "taglib/tag.h"
#include "taglib/tfile.h"
#include "String.h"

namespace JS {

class Tag : public FB::JSAPIAuto {
public:
	Tag(boost::shared_ptr<TagLib::File> file);

	virtual ~Tag();

    /*!
     * Returns the track name; if no track name is present in the tag
     * String::null will be returned.
     */
    String title() const;

    /*!
     * Returns the artist name; if no artist name is present in the tag
     * String::null will be returned.
     */
    String artist() const;

    /*!
     * Returns the album name; if no album name is present in the tag
     * String::null will be returned.
     */
    String album() const;

    /*!
     * Returns the track comment; if no comment is present in the tag
     * String::null will be returned.
     */
    String comment() const;

    /*!
     * Returns the genre name; if no genre is present in the tag String::null
     * will be returned.
     */
    String genre() const;

    /*!
     * Returns the year; if there is no year set, this will return 0.
     */
    uint year() const;

    /*!
     * Returns the track number; if there is no track number set, this will
     * return 0.
     */
    uint track() const;

    /*!
     * Sets the title to \a s.  If \a s is String::null then this value will be
     * cleared.
     */
    void setTitle(const String &s);

    /*!
     * Sets the artist to \a s.  If \a s is String::null then this value will be
     * cleared.
     */
    void setArtist(const String &s);

    /*!
     * Sets the album to \a s.  If \a s is String::null then this value will be
     * cleared.
     */
    void setAlbum(const String &s);

    /*!
     * Sets the comment to \a s.  If \a s is String::null then this value will be
     * cleared.
     */
    void setComment(const String &s);

    /*!
     * Sets the genre to \a s.  If \a s is String::null then this value will be
     * cleared.  For tag formats that use a fixed set of genres, the appropriate
     * value will be selected based on a string comparison.  A list of available
     * genres for those formats should be available in that type's
     * implementation.
     */
    void setGenre(const String &s);

    /*!
     * Sets the year to \a i.  If \a s is 0 then this value will be cleared.
     */
    void setYear(uint i);

    /*!
     * Sets the track to \a i.  If \a s is 0 then this value will be cleared.
     */
    void setTrack(uint i);

    /*!
     * Returns true if the tag does not contain any data.  This should be
     * reimplemented in subclasses that provide more than the basic tagging
     * abilities in this class.
     */
    bool isEmpty() const;

private:
    boost::shared_ptr<TagLib::File> _file;
    TagLib::Tag* _tag;
};

}
