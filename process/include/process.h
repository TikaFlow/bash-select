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

std::vector<std::string> handle_title(const std::vector<std::string>& title, const std::string& select);
std::vector<std::string> exec_select(const std::vector<std::string>& title, const std::vector<std::string>& row,
                                     const std::string& select);
bool exec_where(const std::vector<std::string>& title, const std::vector<std::string>& row, const std::string& where);
std::vector<std::vector<std::string>> process_query(const std::vector<std::vector<std::string>>& input,
                                                    const std::string& query);
int get_col_count(const ProgramOptions& options, const std::string& data);
std::vector<std::string> split_string(const std::string& query, char delimiter);
std::vector<std::string> split_string_by_spaces(const std::string& input);
void prepare_data(const std::string& data, std::vector<std::vector<std::string>>& output, char d);
std::vector<std::vector<std::string>> process_data(const ProgramOptions& options);
std::string readFileString(const std::string& filename);

#endif //BASH_SQL_PROCESS_H
