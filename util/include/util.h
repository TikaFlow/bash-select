//
// Created by tika on 4/21/24.
//

#ifndef BASH_SQL_UTIL_H
#define BASH_SQL_UTIL_H

#include <string>
#include <iostream>
#include <regex>
#include "global.h"

class Util {
public:
    static String ltrim(const String &str);

    static String rtrim(const String &str);

    static String trim(const String &str);

    static Vector<String> split_string(const String &query, char delimiter);

    static Vector<String> split_string_by_spaces(const String &input);

    static void show_error(const String &msg);

};

#endif //BASH_SQL_UTIL_H
