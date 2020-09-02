/* Copyright (c) 2015 Kerio Technologies s.r.o.
 * * Copyright (c) 2020 Lukas Petrlik
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

// StringUtils.h - string utilities.
#pragma once
#include <stdarg.h>
#include <kerio/hashdb/Types.h>

namespace kerio {
namespace hashdb {

	std::string toHex(uint32_t num);

    template<typename ... Args>
    std::string formatMessage(const char* format, Args... args)
    {
        if constexpr (sizeof... (Args) == 0) {
            return format;
        }
        else {
            const auto size = std::snprintf(nullptr, 0, format, args...);
            std::string formatted(size + 1, '\0');

            std::snprintf(formatted.data(), formatted.size(), format, args...);
            formatted.resize(size);

            return formatted;
        }
    }

	void printJsonString(std::ostream& os, const std::string_view& s);
	void printJsonNameValue(std::ostream& os, const std::string_view& name, const std::string_view& value);
	void printJsonNameValue(std::ostream& os, const std::string_view& name, int value);

}; // namespace hashdb
}; // namespace kerio
