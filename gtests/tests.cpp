#include <gtest/gtest.h>
#include <vector>
#include "ipfilter.h"

TEST(SplitTest, EmptyString) {
    std::vector<std::string> expected = {""};
    std::vector<std::string> result = split("", '.');
    ASSERT_EQ(result, expected);
}

TEST(SplitTest, SingleNumber) {
    std::vector<std::string> expected = {"11"};
    std::vector<std::string> result = split("11", '.');
    ASSERT_EQ(result, expected);
}

TEST(SplitTest, MultipleDots) {
    std::vector<std::string> expected = {"", "", ""};
    std::vector<std::string> result = split("..", '.');
    ASSERT_EQ(result, expected);
}

TEST(SplitTest, DotAtEnd) {
    std::vector<std::string> expected = {"11", ""};
    std::vector<std::string> result = split("11.", '.');
    ASSERT_EQ(result, expected);
}

TEST(SplitTest, DotAtBeginning) {
    std::vector<std::string> expected = {"", "11"};
    std::vector<std::string> result = split(".11", '.');
    ASSERT_EQ(result, expected);
}

TEST(SplitTest, MultipleNumbers) {
    std::vector<std::string> expected = {"11", "22"};
    std::vector<std::string> result = split("11.22", '.');
    ASSERT_EQ(result, expected);
}

TEST(SortLexTest, SimpleSort) {
    std::vector<ip_tuple> ip_pool = {
        {1, 2, 3, 4},
        {2, 1, 4, 3},
        {3, 4, 1, 2},
    };

    std::vector<ip_tuple> expected = {
        {3, 4, 1, 2},
        {2, 1, 4, 3},
        {1, 2, 3, 4},
    };

    sort_lex(ip_pool);
    ASSERT_EQ(ip_pool, expected);
}

TEST(SortLexTest, SpecialCase) {
    std::vector<ip_tuple> ip_pool = {
        {1, 1, 1, 1},
        {1, 2, 3, 4},
        {2, 1, 4, 3},
        {3, 4, 1, 2},
        {46, 70, 1, 2},
        {46, 46, 1, 1},
        {46, 46, 1, 2},
        {46, 46, 1, 3},
        {46, 46, 2, 1},
    };

    std::vector<ip_tuple> expected = {
        {46, 70, 1, 2},
        {46, 46, 1, 1},
        {46, 46, 1, 2},
        {46, 46, 1, 3},
        {46, 46, 2, 1},
        {3, 4, 1, 2},
        {2, 1, 4, 3},
        {1, 2, 3, 4},
        {1, 1, 1, 1},
    };

    sort_lex_2(ip_pool);
    ASSERT_EQ(ip_pool, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}