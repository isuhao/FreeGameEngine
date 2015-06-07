﻿#ifndef RAPIDJSON_FILEREADSTREAM_H_
#define RAPIDJSON_FILEREADSTREAM_H_

#include "rapidjson.h"
#include <cstdio>

namespace rapidjson {

//! File byte stream for input using fread().
/*!
	\implements Stream
*/
class FileReadStream {
public:
	typedef char Ch;	//!< Character type (byte).

	//! Constructor.
	/*!
		\param fp File pointer opened for read.
		\param buffer user-supplied buffer.
		\param bufferSize size of buffer in bytes. Must >=4 bytes.
	*/
	FileReadStream(FILE* fp, char* buffer, size_t bufferSize) : fp_(fp), buffer_(buffer), bufferSize_(bufferSize), bufferLast_(0), current_(buffer_), readCount_(0), count_(0), eof_(false) { 
		RAPIDJSON_ASSERT(fp_ != 0);
		RAPIDJSON_ASSERT(bufferSize >= 4);
		Read();
	}

	Ch Peek() const { return *current_; }
	Ch Take() { Ch c = *current_; Read(); return c; }
	size_t Tell() const { return count_ + (current_ - buffer_); }

	// Not implemented
	void Put(Ch) { RAPIDJSON_ASSERT(false); }
	void Flush() { RAPIDJSON_ASSERT(false); } 
	Ch* PutBegin() { RAPIDJSON_ASSERT(false); return 0; }
	size_t PutEnd(Ch*) { RAPIDJSON_ASSERT(false); return 0; }

	// For encoding detection only.
	const Ch* Peek4() const {
		return (current_ + 4 <= bufferLast_) ? current_ : 0;
	}

private:
	void Read() {
		if (current_ < bufferLast_)
			++current_;
		else if (!eof_) {
			count_ += readCount_;
			readCount_ = fread(buffer_, 1, bufferSize_, fp_);
			bufferLast_ = buffer_ + readCount_ - 1;
			current_ = buffer_;

			if (readCount_ < bufferSize_) {
				buffer_[readCount_] = '\0';
				++bufferLast_;
				eof_ = true;
			}
		}
	}

	FILE* fp_;
	Ch *buffer_;
	size_t bufferSize_;
	Ch *bufferLast_;
	Ch *current_;
	size_t readCount_;
	size_t count_;	//!< Number of characters read
	bool eof_;
};

} // namespace rapidjson

#endif // RAPIDJSON_FILESTREAM_H_
