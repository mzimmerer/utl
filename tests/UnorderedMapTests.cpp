/**
 *  Micro template library
 *  Copyright (C) 2020, Matt Zimmerer, mzimmere@gmail.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 **/

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#include <gtest/gtest.h>
#pragma GCC diagnostic pop

#include <utl/string>
#include <utl/unordered_map>

struct hash {
	std::size_t operator()(const utl::string<16>& key) const
	{
		size_t result = 0;
		for (const auto chr : key) {

			result += static_cast<size_t>(chr);
			result <<= 1;
			result *= static_cast<size_t>(chr) * 7;
			result <<= 1;
			result ^= static_cast<size_t>(chr) * 11;
		}
		return result;
	}
};

struct key_equal {
	bool operator()(const utl::string<16>& lhs, const utl::string<16>& rhs) const
	{
		return lhs == rhs;
	}
};

TEST(UnorderedMapTests, Insertions)
{
	utl::unordered_map<utl::string<16>, utl::string<16>, 16, 4, hash, key_equal> string_map;
	string_map.insert("abc", "alphabet");
	string_map.emplace("123", "numbers");

	utl::string<16>& alphabet = string_map["abc"];
	EXPECT_EQ(utl::string<16>("alphabet"), alphabet);
	utl::string<16>& numbers = string_map["123"];
	EXPECT_EQ(utl::string<16>("numbers"), numbers);
}

TEST(UnorderedMapTests, Iterators)
{
	utl::unordered_map<utl::string<16>, utl::string<16>, 16, 4, hash, key_equal> string_map;
	string_map.emplace("abc", "alphabet");
	string_map.emplace("123", "numbers");
	string_map.emplace("$^*", "symbols");


	utl::string<16>& alphabet = string_map["abc"];
	EXPECT_EQ(utl::string<16>("alphabet"), alphabet);
	utl::string<16>& numbers = string_map["123"];
	EXPECT_EQ(utl::string<16>("numbers"), numbers);
	utl::string<16>& symbols = string_map["$^*"];
	EXPECT_EQ(utl::string<16>("symbols"), symbols);

	bool abc_found = false;
	bool num_found = false;
	bool sym_found = false;
	for (auto iter = string_map.begin(); iter != string_map.end(); ++iter) {
		if (iter->first == utl::string<16>("abc"))
		{
			EXPECT_EQ(false, abc_found);
			EXPECT_EQ(utl::string<16>("alphabet"), iter->second);
			abc_found = true;
		}
		if (iter->first == utl::string<16>("123"))
		{
			EXPECT_EQ(false, num_found);
			EXPECT_EQ(utl::string<16>("numbers"), iter->second);
			num_found = true;
		}
		if (iter->first == utl::string<16>("$^*"))
		{
			EXPECT_EQ(false, sym_found);
			EXPECT_EQ(utl::string<16>("symbols"), iter->second);
			sym_found = true;
		}
	}
	EXPECT_EQ(true, abc_found);
	EXPECT_EQ(true, num_found);
	EXPECT_EQ(true, sym_found);

}