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

// SimplePageAllocator.cpp - a page allocator based on malloc.
#include "stdafx.h"
#include "utils/ExceptionCreator.h"
#include "SimplePageAllocator.h"

namespace kerio {
namespace hashdb {

	IPageAllocator::PageMemoryPtr SimplePageAllocator::allocate(size_type size)
	{
		RAISE_INTERNAL_ERROR_IF_ARG(size == 0);

		value_type* pageMemory = static_cast<value_type*>(malloc(size));
		counter_type* counterMemory = static_cast<counter_type*>(malloc(sizeof(counter_type)));

		if (pageMemory == NULL || counterMemory == NULL) {
			free(pageMemory);
			free(counterMemory);

			RAISE_INTERNAL_ERROR("Out of memory");
		}

		return PageMemoryPtr(this, pageMemory, counterMemory);
	}

	void SimplePageAllocator::deallocate(value_type* pageMemory, counter_type* counterMemory)
	{
		RAISE_INTERNAL_ERROR_IF_ARG(pageMemory == NULL || counterMemory == NULL);

		free(pageMemory);
		free(counterMemory);
	}

	void SimplePageAllocator::freeSomeMemory()
	{

	}

	kerio::hashdb::size_type SimplePageAllocator::heldPages()
	{
		return 0;
	}

}; // namespace hashdb
}; // namespace kerio
