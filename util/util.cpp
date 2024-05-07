//
// Created by tika on 4/21/24.
//

#include "util.h"

std::string ltrim(const std::string& str) {
    const size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start != std::string::npos) {
        return str.substr(start);
    }
    return {};
}

std::string rtrim(const std::string& str) {
    const size_t end = str.find_last_not_of(" \t\n\r\f\v");
    if (end != std::string::npos) {
        return str.substr(0, end + 1);
    }
    return {};
}

std::string trim(const std::string& str) {
    return rtrim(ltrim(str));
}

void show_info(const std::string &msg) {
    alert(MsgType::INFO, msg);
}

void show_error_exit(const std::string &msg) {
    alert(MsgType::ERROR, msg);
    exit_on_error();
}

void show_error_no_exit(const std::string &msg) {
    alert(MsgType::ERROR, msg);
}

void exit_on_error() {
    std::cout << std::endl;
    exit(1);
}

void alert(MsgType type, const std::string &msg) {
    if (type == MsgType::ERROR) {
        std::cout << "ERROR: " << msg << std::endl;
    } else if (type == MsgType::INFO) {
        std::cout << msg << std::endl;
    }
}
