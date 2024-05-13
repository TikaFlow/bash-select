//
// Created by tika on 24-5-7.
//

#ifndef BASH_SQL_GLOBAL_H
#define BASH_SQL_GLOBAL_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <iomanip>

// version and copyright
#define VERSION "1.0.1"
#define AUTHOR "Tika Flow"

// keyword
#define var auto
#define val const auto

// type
using String = std::string;
template<typename T>
using Vector = std::vector<T>;
using Regex = std::regex;

// function
using std::stoi;
using std::stol;
using std::stof;
using std::stod;
using std::to_string;
using std::for_each;
using std::getline;
using std::endl;
using std::setw;
using std::setfill;

// object
using std::cin;
using std::cout;
using std::cerr;
val null = nullptr;
val npos = String::npos;

#endif //BASH_SQL_GLOBAL_H
