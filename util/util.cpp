//
// Created by tika on 4/21/24.
//

#include "util.h"

String Util::ltrim(const String &str) {
    val start = str.find_first_not_of(" \t\n\r\f\v");
    return start == String::npos ? "" : str.substr(start);
}

String Util::rtrim(const String &str) {
    val end = str.find_last_not_of(" \t\n\r\f\v");
    return end == String::npos ? "" : str.substr(0, end + 1);
}

String Util::trim(const String &str) {
    return Util::rtrim(Util::ltrim(str));
}


Vector<String> Util::split_string(const String &query, char delimiter) {
    Vector<String> res;
    size_t pos = 0;
    var found = query.find(delimiter);
    while (found != String::npos) {
        res.push_back(query.substr(pos, found - pos));
        pos = found + 1;
        found = query.find(delimiter, pos);
    }
    res.push_back(query.substr(pos));
    return res;
}

Vector<String> Util::split_string_by_spaces(const String &input) {
    const std::regex re("\\s+");

    std::sregex_token_iterator it(input.begin(), input.end(), re, -1);
    Vector<String> tokens;

    for (const std::sregex_token_iterator end; it != end; ++it) {
        tokens.push_back(it->str());
    }

    tokens.erase(std::remove_if(tokens.begin(), tokens.end(), [](const String &s) {
        return s.empty();
    }), tokens.end());

    return tokens;
}

void Util::show_error(const String &msg) {
    cerr << "ERROR: " << msg << endl;
    exit(1);
}