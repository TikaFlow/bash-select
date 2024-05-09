//
// Created by tika on 4/21/24.
//

#ifndef BASH_SQL_UTIL_H
#define BASH_SQL_UTIL_H

#include <string>
#include <iostream>
#include "global.h"

namespace util {
    String ltrim(const String &str);

    String rtrim(const String &str);

    String trim(const String &str);

    Vector<String> split_string(const String &query, char delimiter);

    Vector<String> split_string_by_spaces(const String &input);

    void show_error(const String &msg);
}

using namespace util;

#endif //BASH_SQL_UTIL_H
