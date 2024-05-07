//
// Created by tika on 4/21/24.
//

#include "main.h"

int main(int argc, char *argv[]) {
    // parse command line options
    ProgramOptions options = parseCommandLine(argc, argv);

    // process data
    auto data = process_data(options);

    // DEBUG - print
     for (const auto& row : data) {
         std::cout << "row: ";
         for (const auto& col : row) {
             std::cout << col << "\t";
         }
         std::cout << std::endl;
     }
     std::cout << "====================" << std::endl;
    // DEBUG - print END

    // maybe formatted later

    return 0;
}
