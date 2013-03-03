#pragma once
#include <sys/types.h>
#include <string>
#include "taglib/tiostream.h"

namespace JS {

class DataUrlStream : public TagLib::IOStream {
public:
	/*!
	 * Constructor.
	 * \param dataUrl data URL (RFC 2397) in base64 format
	 */
	DataUrlStream(std::string dataUrl);

    /*!
     * Destroys this Base64Stream instance.
     */
	virtual ~DataUrlStream();

    /*!
     * Returns the stream name in the local file system encoding.
     */
    virtual TagLib::FileName name() const;

    /*!
     * Reads a block of size \a length at the current get pointer.
     */
    virtual TagLib::ByteVector readBlock(TagLib::ulong length);

    /*!
     * Attempts to write the block \a data at the current get pointer.  If the
     * file is currently only opened read only -- i.e. readOnly() returns true --
     * this attempts to reopen the file in read/write mode.
     *
     * \note This should be used instead of using the streaming output operator
     * for a ByteVector.  And even this function is significantly slower than
     * doing output with a char[].
     */
    virtual void writeBlock(const TagLib::ByteVector &data);

    /*!
     * Insert \a data at position \a start in the file overwriting \a replace
     * bytes of the original content.
     *
     * \note This method is slow since it requires rewriting all of the file
     * after the insertion point.
     */
    virtual void insert(const TagLib::ByteVector &data, TagLib::ulong start = 0, TagLib::ulong replace = 0);

    /*!
     * Removes a block of the file starting a \a start and continuing for
     * \a length bytes.
     *
     * \note This method is slow since it involves rewriting all of the file
     * after the removed portion.
     */
    virtual void removeBlock(TagLib::ulong start = 0, TagLib::ulong length = 0);

    /*!
     * Returns true if the file is read only (or if the file can not be opened).
     */
    virtual bool readOnly() const;

    /*!
     * Since the file can currently only be opened as an argument to the
     * constructor (sort-of by design), this returns if that open succeeded.
     */
    virtual bool isOpen() const;

    /*!
     * Move the I/O pointer to \a offset in the stream from position \a p.  This
     * defaults to seeking from the beginning of the stream.
     *
     * \see Position
     */
    virtual void seek(long offset, Position p = Beginning);

    /*!
     * Returns the current offset within the stream.
     */
    virtual long tell() const;

    /*!
     * Returns the length of the stream.
     */
    virtual long length();

    /*!
     * Truncates the stream to a \a length.
     */
    virtual void truncate(long length);

private:
    std::string _name;
    std::string _base64string;
    TagLib::ulong _cur;
    TagLib::ulong _length;

    uint8_t asciiToBase64(uint8_t c);
};

} /* namespace JS */
