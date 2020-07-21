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

#include <utl/fifo>
#include <utl/string>

TEST(FifoTests, Trivial)
{
    utl::fifo<int, 10> integers;
    for (int i = 0; i < 10; ++i)
        integers.push(i);

    EXPECT_EQ(10, integers.size());

    int result;
    for (int i = 0; i < 10; ++i)
        EXPECT_EQ(i, result = integers.pop());
}

TEST(FifoTests, Iterators)
{
    utl::fifo<int, 3> fifo;

    EXPECT_EQ(true, fifo.empty());
    EXPECT_EQ(false, fifo.full());

    fifo.push(1);

    auto iter = fifo.begin();
    EXPECT_EQ(1, fifo.size());
    EXPECT_EQ(1, *iter);

    fifo.push(2);
    iter = ++fifo.begin();
    EXPECT_EQ(2, fifo.size());
    EXPECT_EQ(2, *iter);

    fifo.push(3);
    iter = ++fifo.begin();
    ++iter;
    EXPECT_EQ(3, fifo.size());
    EXPECT_EQ(3, *iter);

    EXPECT_EQ(false, fifo.empty());
    EXPECT_EQ(true, fifo.full());

    int result = fifo.pop();
    EXPECT_EQ(1, result);
    EXPECT_EQ(2, fifo.size());

    result = fifo.pop();
    EXPECT_EQ(2, result);
    EXPECT_EQ(1, fifo.size());

    fifo.push(4);
    iter = ++fifo.begin();
    EXPECT_EQ(2, fifo.size());
    EXPECT_EQ(4, *iter);

    result = fifo.pop();
    EXPECT_EQ(3, result);

    result = fifo.pop();
    EXPECT_EQ(4, result);

    EXPECT_EQ(true, fifo.empty());
    EXPECT_EQ(false, fifo.full());

    EXPECT_EQ(0, fifo.size());
}

TEST(FifoTests, FifoOfStrings)
{
    static utl::fifo<utl::string<32>, 4> line_fifo;

    EXPECT_EQ(true, line_fifo.empty());
}