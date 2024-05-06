//
// Created by tika on 4/21/24.
//

#include "main.h"

int main(int argc, char *argv[]) {
    // parse command line options
    ProgramOptions options = parseCommandLine(argc, argv);

    // process data
    auto data = process_data(options);

    // output data - for now, just print it to the console
    // maybe formatted later
    // std::cout << data << std::endl;

    return 0;
}
