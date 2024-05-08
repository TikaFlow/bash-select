//
// Created by tika on 4/21/24.
//

#ifndef BASH_SQL_GETOPT_UTIL_H
#define BASH_SQL_GETOPT_UTIL_H

#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <getopt.h>
#include "util.h"

// 定义参数结构体
struct ProgramOptions {
    bool title;
    String data;
    String file;
    char delimiter;
    int columns;
    String query;
};

// 解析命令行参数
ProgramOptions parseCommandLine(int argc, char* argv[]);


#endif //BASH_SQL_GETOPT_UTIL_H
