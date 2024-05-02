//
// Created by tika on 5/2/24.
//

#ifndef BASH_SQL_PROCESS_H
#define BASH_SQL_PROCESS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "getopt_util.h"

std::string processData(const ProgramOptions& options);
std::string readFileString(const std::string& filename);

#endif //BASH_SQL_PROCESS_H
