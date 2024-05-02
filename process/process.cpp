//
// Created by tika on 5/2/24.
//

#include "process.h"

std::vector<std::string> splitQueries(const std::string &query) {
    std::vector<std::string> queries;
    size_t pos = 0;
    size_t found = query.find('|');
    while (found != std::string::npos) {
        queries.push_back(query.substr(pos, found - pos));
        pos = found + 1;
        found = query.find('|', pos);
    }
    queries.push_back(query.substr(pos)); // 添加最后一个查询
    return queries;
}

std::string processData(const ProgramOptions &options) {
    std::string input, output;
    if (!options.data.empty()) input = options.data;
    else if (!options.file.empty()) input = readFileString(options.file);

    if (input.empty()) {
        // If input is empty, show error and exit
        // TODO - use dual when no input is provided
        show_error_exit("No input data provided.");
    }

    // Split the query into multiple queries
    std::vector<std::string> queries = splitQueries(options.query);


    for (const auto &q: queries) {
        // DEBUG - print query
        std::cout << "Query: ";
        std::cout << q << std::endl;
        // TODO - process the query here

    }

    // Process the input data here

    output = input;

    return output;
}

std::string readFileString(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        show_error_exit("Unable to open file: " + filename);
    }

    std::string content{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
    return content;
}