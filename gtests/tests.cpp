#include <gtest/gtest.h>
#include "ipfilter.h" // Подключите ваш заголовочный файл с функциями



// Тесты для функции print_ip_tuple (тестируем вывод в stdout)
TEST(PrintIpTupleTest, PrintsCorrectFormat) {
    std::stringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    ip_tuple ip(192, 168, 0, 1);
    print_ip_tuple(ip);
    
    std::cout.rdbuf(oldCout); // Возвращаем стандартный вывод

    EXPECT_EQ(buffer.str(), "192.168.0.1\n"); // Проверяем вывод
}

// Тесты для функции sort_lex
TEST(SortLexTest, SortsCorrectly) {
    std::vector<ip_tuple> ip_pool = {
        ip_tuple(10, 10, 10, 10),
        ip_tuple(1, 1, 1, 1),
        ip_tuple(2, 2, 2, 2),
        ip_tuple(3, 3, 3, 3),
    };

    std::vector<ip_tuple> expected = {
        ip_tuple(10, 10, 10, 10),
        ip_tuple(3, 3, 3, 3),
        ip_tuple(2, 2, 2, 2),
        ip_tuple(1, 1, 1, 1),
    };

    sort_lex(ip_pool);
    EXPECT_EQ(ip_pool, expected);
}

// Тесты для функции sort_lex_2
TEST(SortLex2Test, SortsCorrectlyWithCustomRules) {
    std::vector<ip_tuple> ip_pool = {
        ip_tuple(2, 2, 2, 2),
        ip_tuple(1, 1, 1, 1),
        ip_tuple(46, 70, 1, 1),
        ip_tuple(46, 46, 1, 1),
        ip_tuple(46, 70, 2, 2),
        ip_tuple(46, 46, 46, 46),
    };

    std::vector<ip_tuple> expected = {
        ip_tuple(1, 1, 1, 1),
        ip_tuple(46, 70, 1, 1),
        ip_tuple(46, 70, 2, 2),
        ip_tuple(46, 46, 1, 1),
        ip_tuple(46, 46, 46, 46),
        ip_tuple(2, 2, 2, 2),
    };

    sort_lex_2(ip_pool);
    EXPECT_EQ(ip_pool, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}