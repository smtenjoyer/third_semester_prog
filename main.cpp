#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <fstream> 
#include <tuple>
#include "ipfilter.h"


int main()
{
    // try
    // {
        std::vector<std::vector<std::string> > ip_pool;
        std::vector<ip_tuple> ip_pool_int;
        std::vector<ip_tuple> ip_pool_int_2;
	    std::ifstream inFile;
        inFile.open("ip_filter.tsv");
        std::string line; 

        while(std::getline(inFile, line))
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        // std::sort(ip_pool.begin(), ip_pool.end(), [](std::vector<std::string> a, std::vector<std::string> b)
        // {
        //     return std::stoi(a[0]) > std::stoi(b[0]);
        // });

        for (std::vector<ip_tuple>::size_type ip = 0; ip < ip_pool.size(); ip++)
        {
            ip_tuple new_tuple(std::stoi(ip_pool[ip][0]),std::stoi(ip_pool[ip][1]),std::stoi(ip_pool[ip][2]),std::stoi(ip_pool[ip][3]));
            ip_pool_int.push_back(new_tuple);
        }
        ip_pool_int_2 = ip_pool_int;

        
        sort_lex(ip_pool_int);
        for (std::vector<ip_tuple>::size_type i = 0; i < ip_pool_int.size(); i++)
        {
            print_ip_tuple(ip_pool_int[i]);
        }

        sort_lex_2(ip_pool_int_2);

        for (std::vector<ip_tuple>::size_type i = 0; i < ip_pool_int.size(); i++)
        {
            if (std::get<0>(ip_pool_int_2[i]) == 1 || (std::get<0>(ip_pool_int_2[i]) == 46 && std::get<1>(ip_pool_int_2[i]) == 70) || (std::get<0>(ip_pool_int_2[i]) == 46 || std::get<1>(ip_pool_int_2[i]) == 46 ||std::get<2>(ip_pool_int_2[i]) == 46 ||std::get<3>(ip_pool_int_2[i]) == 46))
            {
                print_ip_tuple(ip_pool_int_2[i]);
            }
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    // }
    // catch(const std::exception &e)
    // {
    //     std::cerr << "e.what()" << std::endl;
    // }

    return 0;
}
