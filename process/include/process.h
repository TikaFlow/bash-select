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

void verify_query(const String &query);
Vector<String> handle_title(const Vector<String>& title, const String& select);
Vector<String> exec_select(const Vector<String>& title, const Vector<String>& row,
                                     const String& select);
bool exec_where(const Vector<String>& title, const Vector<String>& row, const String& where);
Vector<Vector<String>> process_query(const Vector<Vector<String>>& input,
                                                    const String& query);
int get_col_count(const ProgramOptions& options, const String& data);
void prepare_data(const String& data, Vector<Vector<String>>& output, char d);
Vector<Vector<String>> process_data(const ProgramOptions& options);
String readFileString(const String& filename);

#endif //BASH_SQL_PROCESS_H
