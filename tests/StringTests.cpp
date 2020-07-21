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

#include "utl/string"

TEST(StringTests, Constructors)
{
    utl::string<10> trivial;
    EXPECT_EQ(0, trivial.size());

    utl::string<10> cstring("cstring");
    EXPECT_EQ(7, cstring.size());
    EXPECT_EQ(std::string("cstring"), std::string(cstring.c_str()));

    utl::string<10> cstring_hint("cstring", 7);
    EXPECT_EQ(7, cstring_hint.size());
    EXPECT_EQ(std::string("cstring"), std::string(cstring_hint.c_str()));

    utl::string<10> copyconstructor(cstring_hint);
    EXPECT_EQ(7, copyconstructor.size());
    EXPECT_EQ(std::string("cstring"), std::string(copyconstructor.c_str()));

    utl::string<10> copybyiterator(cstring.begin(), cstring.end());
    EXPECT_EQ(7, copybyiterator.size());
    EXPECT_EQ(std::string("cstring"), std::string(copybyiterator.c_str()));
}

TEST(StringTests, Copy)
{
    utl::string<10> cstring("cstring", 7);
    utl::string<10> other = cstring;

    EXPECT_EQ(7, cstring.size());
    EXPECT_EQ(7, other.size());
    EXPECT_EQ(std::string("cstring"), std::string(cstring.c_str()));
    EXPECT_EQ(std::string("cstring"), std::string(other.c_str()));
}

TEST(StringTests, ToString)
{
    utl::string<10> result = utl::to_string<10>(12345);
    EXPECT_EQ(std::string("12345"), std::string(result.c_str()));

}

TEST(StringTests, SizeConversions)
{
    utl::string<5> src("dst");
    utl::string<10> copy_dest;
    utl::string<10> add_dest("src");
    utl::string<10> copy_construct_dest(src);

    copy_dest = src;
    add_dest += src;

    EXPECT_EQ(3, src.size());
    EXPECT_EQ(3, copy_dest.size());
    EXPECT_EQ(6, add_dest.size());
    EXPECT_EQ(3, copy_construct_dest.size());
    EXPECT_EQ(std::string("dst"), std::string(src.c_str()));
    EXPECT_EQ(std::string("dst"), std::string(copy_dest.c_str()));
    EXPECT_EQ(std::string("srcdst"), std::string(add_dest.c_str()));
    EXPECT_EQ(std::string("dst"), std::string(copy_construct_dest.c_str()));
}