#include <stack.hpp>

#include <gtest/gtest.h>

TEST(StackTest, EmptyConstructor)
{
    Stack<int> s;
    EXPECT_EQ(s.size(), 0);
    EXPECT_EQ(s.capacity(), 2);
}

TEST(StackTest, Push)
{
    Stack<int> s;
    s.push(1);
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.top(), 1);
}

TEST(StackTest, Pop)
{
    Stack<int> s;
    s.push(1);
    s.pop();
    EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, Top)
{
    Stack<int> s;
    s.push(1);
    EXPECT_EQ(s.top(), 1);
}

TEST(StackTest, Size)
{
    Stack<int> s;
    s.push(1);
    s.push(2);
    EXPECT_EQ(s.size(), 2);
}

TEST(StackTest, Capacity)
{
    Stack<int> s;
    for (int i = 0; i < 10; ++i)
    {
        s.push(i);
    }
    EXPECT_GE(s.capacity(), 10);
}
TEST(StackTest, Emplace)
{
    Stack<std::pair<int, std::string>> s;
    s.emplace(1, "one");
    EXPECT_EQ(s.top().first, 1);
    EXPECT_EQ(s.top().second, "one");
}

TEST(StackTest, CopyConstructor)
{
    Stack<int> s1;
    s1.push(1);
    Stack<int> s2(s1);
    EXPECT_EQ(s2.top(), 1);
}

TEST(StackTest, CopyAssignment)
{
    Stack<int> s1;
    s1.push(1);
    Stack<int> s2;
    s2 = s1;
    EXPECT_EQ(s2.top(), 1);
}