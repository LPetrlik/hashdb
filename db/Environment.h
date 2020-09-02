/* Copyright (c) 2015 Kerio Technologies s.r.o.
 * Copyright (c) 2020 Lukas Petrlik
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

// Environment.h - environment for accessing the database.
#pragma once
#include <kerio/hashdb/HashDB.h>
#include "utils/Noncopyable.h"
#include "Interfaces.h"
#include "PageId.h"

namespace kerio {
namespace hashdb {

#define HASHDB_LOG_DEBUG(fmt, ...)							\
	do {													\
		if (environment_.isDebugLogEnabled()) {				\
			const std::string logMessage = formatMessage(fmt, ## __VA_ARGS__);	\
			environment_.logDebug(logMessage);				\
		}													\
	} while (false)

#define HASHDB_LOG_DEBUG_DETAIL(fmt, ...)	HASHDB_LOG_DEBUG(fmt, ## __VA_ARGS__)

	class Environment : Noncopyable
	{
	public:
		Environment(const Options& options);

		// Accessors.
		IPageAllocator* pageAllocator();
		IPageAllocator* headerPageAllocator();
		ILockManager* lockManager();

		// Logging.
		bool isDebugLogEnabled();
		void logDebug(const std::string& logMessage);

	private:
		std::shared_ptr<ILogger> logger_;
		std::unique_ptr<ILockManager> lockManager_;
        std::unique_ptr<IPageAllocator> pageAllocator_;
        std::unique_ptr<IPageAllocator> headerPageAllocator_;
	};

}; // namespace hashdb
}; // namespace kerio
