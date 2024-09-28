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
        std::vector<std::vector<std::string> > ip_pool;
        std::vector<ip_tuple> ip_pool_int;
        std::vector<ip_tuple> ip_pool_int_2;
	    std::ifstream inFile;
        inFile.open("C:/Users/user/Desktop/2laba/ip_filter.tsv");
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
    return 0;
}
