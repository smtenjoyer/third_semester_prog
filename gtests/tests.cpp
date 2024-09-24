#include <gtest/gtest.h>
#include "ip_filter.h"


// TEST(SplitTest, BasicCases) {
//     ASSERT_EQ(split("", '.'), std::vector<std::string>{""});
//     ASSERT_EQ(split("11", '.'), std::vector<std::string>{"11"});
//     ASSERT_EQ(split("..", '.'), std::vector<std::string>{"", "", ""});
//     ASSERT_EQ(split("11.", '.'), std::vector<std::string>{"11", ""});
//     ASSERT_EQ(split(".11", '.'), std::vector<std::string>{"", "11"});
//     ASSERT_EQ(split("11.22", '.'), std::vector<std::string>{"11", "22"});
//     ASSERT_EQ(split("11.22.33", '.'), std::vector<std::string>{"11", "22", "33"});
//     ASSERT_EQ(split("11.22.33.44", '.'), std::vector<std::string>{"11", "22", "33", "44"});
//     ASSERT_EQ(split("11.22.33.44.", '.'), std::vector<std::string>{"11", "22", "33", "44", ""});
// }

// Тестовый набор для функции sort_lex
TEST(IPAddressTest, SortLexTest) {
    std::vector<ip_tuple> ip_pool = {
        ip_tuple(10, 10, 10, 10),
        ip_tuple(1, 1, 1, 1),
        ip_tuple(2, 2, 2, 2),
        ip_tuple(3, 3, 3, 3),
    };
    std::vector<ip_tuple> test_sort_tuple{
        ip_tuple(10, 10, 10, 10),
        ip_tuple(3, 3, 3, 3),
        ip_tuple(2, 2, 2, 2),
        ip_tuple(1, 1, 1, 1),
    };
    sort_lex(ip_pool);
    EXPECT_EQ(ip_pool, test_sort_tuple);
}

// Тестовый набор для функции sort_lex_2
TEST(IPAddressTest, BasicCases) {
    std::vector<ip_tuple> ip_pool = {
        ip_tuple(1, 1, 1, 1),
        ip_tuple(46, 70, 1, 1),
        ip_tuple(46, 46, 1, 1),
        ip_tuple(46, 46, 46, 46),
        ip_tuple(2, 2, 2, 2),
        ip_tuple(46, 46, 1, 1),
        ip_tuple(46, 70, 2, 2),
    };

std::vector<ip_tuple> test_sort_lex_2{
        ip_tuple(1, 1, 1, 1),
        ip_tuple(46, 70, 1, 1),
        ip_tuple(46, 70, 2, 2),
        ip_tuple(46, 46, 1, 1),
        ip_tuple(46, 46, 1, 1),
        ip_tuple(46, 46, 46, 46),
        ip_tuple(2, 2, 2, 2),
    };
    sort_lex_2(ip_pool);
    EXPECT_EQ(ip_pool, test_sort_lex_2);
}
