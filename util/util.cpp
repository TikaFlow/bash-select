//
// Created by tika on 4/21/24.
//

#include "../include/util.h"

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
