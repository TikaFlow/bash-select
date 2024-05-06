//
// Created by tika on 5/2/24.
//

#ifndef BASH_SQL_PROCESS_H
#define BASH_SQL_PROCESS_H

#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include "getopt_util.h"

std::vector<std::vector<std::string>> process_query(const std::vector<std::vector<std::string>>& input,
                                                    const std::string& query);
int get_col_count(const ProgramOptions& options, const std::string& data);
std::vector<std::string> split_string(const std::string& query, char delimiter);
std::vector<std::string> split_string_by_spaces(const std::string& input);
std::vector<std::vector<std::string>> prepare_data(const std::string& data, int col_count, char i);
std::vector<std::vector<std::string>> process_data(const ProgramOptions& options);
std::string readFileString(const std::string& filename);

#endif //BASH_SQL_PROCESS_H
