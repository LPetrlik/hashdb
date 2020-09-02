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

// StringOrReference.h - a sequence of bytes optionally managed by the class.
#pragma once
#include <string>
#include <string_view>
#include <variant>
#include <kerio/hashdb/Types.h>

namespace kerio {
namespace hashdb {

	class StringOrReference  { // intentionally copyable
	public:
		std::string_view getRef() const
		{
            return std::visit([](const auto& arg) -> std::string_view {
                    return arg;
            }, value_);
		}

		size_type size() const
		{
			return getRef().size();
		}

		int which() const
		{
			return value_.index();
		}

		// Copy the value.
		static StringOrReference copy(const std::string& str)
		{
			return StringOrReference(str);
		}

        static StringOrReference copy(std::string &&str)
        {
            return StringOrReference(std::move(str));
        }

		// Reference the value.
		static StringOrReference reference(const std::string_view& ref)
		{
			return StringOrReference(ref);
		}

	private:
		const std::variant<const std::string_view, const std::string> value_;

		explicit StringOrReference(const std::string& str) : value_(str) { }

        explicit StringOrReference(std::string &&str) : value_(std::move(str)) { }

        explicit StringOrReference(const std::string_view& ref) : value_(ref) { }
	};

}; // hashdb
}; // kerio
