#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <fstream> 
#include <tuple>


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back((str.substr(start)));

    return r;
}

typedef std::tuple<int, int, int, int> ip_tuple;


void print_ip_tuple(const ip_tuple& i)
{
    std::cout 
        << std::get<0>(i) << "."
        << std::get<1>(i) << "."
        << std::get<2>(i) << "."
        << std::get<3>(i) << std::endl;
}

void sort_lex(std::vector<ip_tuple>& ip_pool) {
    std::sort(ip_pool.begin(), ip_pool.end(), [](const auto& a, decltype(a) b){
        return a > b;
    });
}

void sort_lex_2(std::vector<ip_tuple>& ip_pool) {
    std::stable_sort(ip_pool.begin(), ip_pool.end(), [](const auto& a, const auto& b) {
        // Условия сортировки
        if (std::get<0>(a) == 1 && std::get<0>(b) != 1) {
            return true; // a идет первым
        } else if (std::get<0>(a) != 1 && std::get<0>(b) == 1) {
            return false; // b идет первым
        }

        else if (std::get<0>(a) == 46 && std::get<1>(a) == 70 && (std::get<0>(b) != 46 || std::get<1>(b) != 70)) {
            return true; // a идет первым
        } else if ((std::get<0>(a) != 46 || std::get<1>(a) != 70) && std::get<0>(b) == 46 && std::get<1>(b) == 70) {
            return false; // b идет первым
        }

        else if ((std::get<0>(a) == 46 || std::get<1>(a) == 46 ||std::get<2>(a) == 46 ||std::get<3>(a) == 46) && (std::get<0>(b) != 46 && std::get<1>(b) != 46 && std::get<2>(b) != 46 && std::get<3>(b) != 46)) {
            return true; // a идет первым
        } else if ((std::get<0>(b) == 46 || std::get<1>(b) == 46 ||std::get<2>(b) == 46 ||std::get<3>(b) == 46) && (std::get<0>(a) != 46 && std::get<1>(a) != 46 && std::get<2>(a) != 46 && std::get<3>(a) != 46)) {
            return false; // b идет первым
        }
        // Стандартная сортировка по возрастанию, если не выполняются вышеперечисленные условия
        return a > b;
        
    });
}

