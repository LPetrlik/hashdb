/* Copyright (c) 2015 Kerio Technologies s.r.o.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE BE
 * LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Except as contained in this notice, the name of a copyright holder shall not
 * be used in advertising or otherwise to promote the sale, use or other
 * dealings in this Software without prior written authorization of the
 * copyright holder.
 */

// IteratorImpl.h - implementation of the IIterator interface.
#pragma once
#include <kerio/hashdb/Iterator.h>
#include "IteratorPosition.h"
#include "OpenDatabase.h"

namespace kerio {
namespace hashdb {

	class IteratorImpl : public IIterator, Noncopyable
	{
	public:
		IteratorImpl(std::shared_ptr<OpenDatabase>& openDatabase);
		virtual ~IteratorImpl();

		virtual bool isValid() const;
		virtual std::string key() const;
		virtual partNum_t partNum() const;
		virtual std::string value() const;
		virtual size_t valueSize() const;
		virtual void next();

	private:
		bool isValid_;

		std::string key_;
		partNum_t partNum_;
		std::string value_;

		IteratorPosition position_;

		boost::weak_ptr<OpenDatabase> openDatabaseWeakPtr_;
	};

}; // namespace hashdb
}; // namespace kerio
