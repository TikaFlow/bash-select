//
// Created by tika on 4/21/24.
//

#include "main.h"

int main(int argc, char *argv[]) {
    // parse command line options
    val options = parseCommandLine(argc, argv);

    // process data
    var data = process_data(options);

    // print data
    print_data(data, options);

    return 0;
}
