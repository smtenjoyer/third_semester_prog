#ifndef IPFILTER_H
#define IPFILTER_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <fstream> 
#include <tuple>

std::vector<std::string> split(const std::string &str, char d);
typedef std::tuple<int, int, int, int> ip_tuple;
void print_ip_tuple(const ip_tuple& i);
void print_ip_tuple(const ip_tuple& i);
void sort_lex(std::vector<ip_tuple>& ip_pool);
void sort_lex_2(std::vector<ip_tuple>& ip_pool);

#endif
