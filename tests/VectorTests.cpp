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

#include "utl/vector"

TEST(VectorTests, IntPushBack)
{
    utl::vector<int, 10> test_vector;
    test_vector.push_back(10);
    EXPECT_EQ(1, test_vector.size());
    EXPECT_EQ(10, test_vector[0]);
    test_vector.push_back(11);
    EXPECT_EQ(2, test_vector.size());
    EXPECT_EQ(10, test_vector[0]);
    EXPECT_EQ(11, test_vector[1]);
    test_vector.clear();
    EXPECT_EQ(0, test_vector.size());
}

TEST(VectorTests, ClassEmplaceBack)
{
    class TestClass {
    public:
        TestClass() : value(0) {}
        TestClass(int input) : value(input)
        {
            this->value++;
        }
        ~TestClass()
        {
            this->value = 0;
        }
        int value;
    };

    utl::vector<TestClass, 10> test_vector;
    test_vector.emplace_back(10);
    EXPECT_EQ(1, test_vector.size());
    EXPECT_EQ(11, test_vector[0].value);
    test_vector.emplace_back(11);
    EXPECT_EQ(2, test_vector.size());
    EXPECT_EQ(11, test_vector[0].value);
    EXPECT_EQ(12, test_vector[1].value);
    test_vector.clear();
    EXPECT_EQ(0, test_vector.size());
}

TEST(VectorTests, ClassCopy)
{
    class TestClass {
    public:
        TestClass() : value(0) {}
        TestClass(int input) : value(input)
        {
            this->value++;
        }
        ~TestClass()
        {
            this->value = 0;
        }
        TestClass& operator=(const TestClass& other)
        {
            this->value = other.value;
            return *this;
        }
        int value;
    };

    utl::vector<TestClass, 10> test_vector;
    test_vector.emplace_back(10);
    EXPECT_EQ(1, test_vector.size());
    EXPECT_EQ(11, test_vector[0].value);
    test_vector.emplace_back(11);
    EXPECT_EQ(2, test_vector.size());
    EXPECT_EQ(11, test_vector[0].value);
    EXPECT_EQ(12, test_vector[1].value);

    utl::vector<TestClass, 10> copy_vector;
    copy_vector = test_vector;

    EXPECT_EQ(test_vector.size(), copy_vector.size());
    for (size_t i = 0; i < copy_vector.size(); i++)
        EXPECT_EQ(test_vector[i].value, copy_vector[i].value);

    test_vector.clear();
    EXPECT_EQ(0, test_vector.size());
}