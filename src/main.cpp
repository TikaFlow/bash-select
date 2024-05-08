//
// Created by tika on 4/21/24.
//

#include "main.h"

int main(int argc, char *argv[]) {
    // parse command line options
    val options = parseCommandLine(argc, argv);

    // process data
    var data = process_data(options);

    // DEBUG
    for (int i = 0; i < data.size(); ++i) {
        if (i == 1)
            cout << "===============================" << endl;
        if (i == 0)
            cout << "ID";
        else
            cout << i;
        cout << "\t";
        for (val &col: data[i]) {
            cout << col << "\t";
        }
        cout << endl;
    }
    // DEBUG END

    // maybe formatted later

    return 0;
}
