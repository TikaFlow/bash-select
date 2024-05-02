//
// Created by tika on 4/21/24.
//

#ifndef BASH_SQL_UTIL_H
#define BASH_SQL_UTIL_H

#include <string>
#include <iostream>

enum class MsgType {
    INFO,
    ERROR
};

void alert(MsgType type, const std::string &msg);
void show_info(const std::string &msg);
void show_error_exit(const std::string &msg);
void show_error_no_exit(const std::string &msg);
void exit_on_error();

#endif //BASH_SQL_UTIL_H
