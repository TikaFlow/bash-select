//
// Created by tika on 4/21/24.
//

#ifndef BASH_SQL_UTIL_H
#define BASH_SQL_UTIL_H

#include <string>
#include <iostream>
#include <algorithm>
#include "global.h"

namespace util {
    String ltrim(const String &str);

    String rtrim(const String &str);

    String trim(const String &str);

    Vector<String> split_string(const String &query, char delimiter);

    Vector<String> split_string_by_spaces(const String &input);

    String &replaceAll(String &str, const String &src, const String &dst);

    void show_error(const String &msg);

    void show_warn(const String &msg);
}

using namespace util;

#endif //BASH_SQL_UTIL_H
