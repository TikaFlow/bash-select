//
// Created by tika on 4/21/24.
//

#ifndef BASH_SQL_UTIL_H
#define BASH_SQL_UTIL_H

#include <string>
#include <iostream>
#include "global.h"

enum class MsgType {
    INFO,
    ERROR
};

std::string ltrim(const std::string& str);
std::string rtrim(const std::string& str);
std::string trim(const std::string& str);
void alert(MsgType type, const std::string &msg);
void show_info(const std::string &msg);
void show_error_exit(const std::string &msg);
void show_error_no_exit(const std::string &msg);
void exit_on_error();

#endif //BASH_SQL_UTIL_H
