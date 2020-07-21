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

#include "utl/list"

TEST(ListTests, IntPushBack)
{
	utl::list<int, 10> test_list;
	test_list.push_back(10);
	EXPECT_EQ(1, test_list.size());
	EXPECT_EQ(10, test_list.front());
	EXPECT_EQ(10, test_list.back());
	test_list.push_back(11);
	EXPECT_EQ(2, test_list.size());
	EXPECT_EQ(10, test_list.front());
	EXPECT_EQ(11, test_list.back());
	test_list.clear();
	EXPECT_EQ(0, test_list.size());
}

TEST(ListTests, IntPushPop)
{
	utl::list<int, 10> test_list;
	test_list.push_back(10);
	test_list.push_front(14);
	test_list.push_back(12);
	test_list.push_front(13);
	test_list.push_back(11);
	EXPECT_EQ(5, test_list.size());

	EXPECT_EQ(11, test_list.back());
	test_list.pop_back();
	EXPECT_EQ(13, test_list.front());
	test_list.pop_front();
	EXPECT_EQ(12, test_list.back());
	test_list.pop_back();
	EXPECT_EQ(14, test_list.front());
	test_list.pop_front();
	EXPECT_EQ(10, test_list.back());
	test_list.pop_back();
}

TEST(ListTests, ClassEmplaceBack)
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

	utl::list<TestClass, 10> test_list;
	test_list.emplace_back(10);
	EXPECT_EQ(1, test_list.size());
	EXPECT_EQ(11, test_list.front().value);
	test_list.emplace_back(11);
	EXPECT_EQ(2, test_list.size());
	EXPECT_EQ(11, test_list.front().value);
	EXPECT_EQ(12, test_list.back().value);
	test_list.clear();
	EXPECT_EQ(0, test_list.size());
}

TEST(ListTests, ClassCopy)
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

	utl::list<TestClass, 10> test_list;
	test_list.emplace_back(10);
	EXPECT_EQ(1, test_list.size());
	EXPECT_EQ(11, test_list.front().value);
	test_list.emplace_back(11);
	EXPECT_EQ(2, test_list.size());
	EXPECT_EQ(11, test_list.front().value);
	EXPECT_EQ(12, test_list.back().value);

	utl::list<TestClass, 10> copy_vector;
	copy_vector = test_list;

	EXPECT_EQ(test_list.size(), copy_vector.size());
	utl::list<TestClass, 10>::iterator test_iter = test_list.begin();
	utl::list<TestClass, 10>::iterator copy_iter = copy_vector.begin();
	for (size_t i = 0; i < copy_vector.size(); i++) {
		EXPECT_EQ(test_iter->value, copy_iter->value);
		test_iter++;
		copy_iter++;
	}

	test_list.clear();
	EXPECT_EQ(0, test_list.size());
}

TEST(ListTests, IntSort)
{
	utl::list<int, 10> test_list;
	test_list.push_back(10);
	test_list.push_back(14);
	test_list.push_back(12);
	test_list.push_back(13);
	test_list.push_back(11);
	EXPECT_EQ(5, test_list.size());

	// Ascending sort
	utl::list<int, 10>::iterator prev;
	test_list.sort([](const int& lhs, const int& rhs) { return lhs < rhs; });
	for (auto iter = test_list.begin(); iter != test_list.end(); ++iter) {
		if (iter != test_list.begin())
		{
			EXPECT_LE(*prev, *iter);
		}
		prev = iter;
	}

	// Descending sort
	test_list.sort([](const int& lhs, const int& rhs) { return lhs > rhs; });
	for (auto iter = test_list.begin(); iter != test_list.end(); ++iter) {
		if (iter != test_list.begin())
		{
			EXPECT_GE(*prev, *iter);
		}
		prev = iter;
	}
}