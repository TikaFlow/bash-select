//
// Created by tika on 5/2/24.
//

#include "process.h"

std::vector<std::string> split_string(const std::string& query, char delimiter) {
    std::vector<std::string> res;
    size_t pos = 0;
    size_t found = query.find(delimiter);
    while (found != std::string::npos) {
        res.push_back(query.substr(pos, found - pos));
        pos = found + 1;
        found = query.find(delimiter, pos);
    }
    res.push_back(query.substr(pos));
    return res;
}

std::vector<std::string> split_string_by_spaces(const std::string& input) {
    const std::regex re("\\s+");

    std::sregex_token_iterator it(input.begin(), input.end(), re, -1);
    std::vector<std::string> tokens;

    for (const std::sregex_token_iterator end; it != end; ++it) {
        tokens.push_back(it->str());
    }

    tokens.erase(std::remove_if(tokens.begin(), tokens.end(), [](const std::string& s) {
        return s.empty();
    }), tokens.end());

    return tokens;
}

std::vector<std::vector<std::string>> prepare_data(const std::string& data, int col_count, char i) {
    std::vector<std::vector<std::string>> output;

    auto rows = split_string(data, '\n');
    for (auto& row : rows) {
        auto cols = i == 0 ? split_string_by_spaces(row) : split_string(row, i);
        output.push_back(cols);
    }

    return output;
}

int get_col_count(const ProgramOptions& options, const std::string& data) {
    if (options.columns > 0) {
        return options.columns;
    }

    const auto first_line = split_string(data, '\n')[0];
    const auto col_count = options.delimiter == 0
                               ? split_string_by_spaces(first_line).size()
                               : split_string(first_line, options.delimiter).size();
    return static_cast<int>(col_count);
}

std::vector<std::vector<std::string>> process_query(const std::vector<std::vector<std::string>>& input,
                                                    const std::string& query) {
    // DEBUG - print
    std::cout << "executing query: " << query << std::endl;
    std::cout << "rowid\t\t";
    for (int i = 0; i < 9; i++) {
        std::cout << "col" << std::to_string(i + 1) << "\t";
    }
    std::cout << std::endl;
    for (const auto& row : input) {
        std::cout << "row: ";
        for (const auto& col : row) {
            std::cout << col << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << "====================" << std::endl;
    // DEBUG - print END

    return input;
}

std::vector<std::vector<std::string>> process_data(const ProgramOptions& options) {
    std::string data;

    // get data string
    if (!options.data.empty())
        data = options.data;
    else if (!options.file.empty())
        data = readFileString(options.file);

    if (data.empty()) {
        // If input is empty, show error and exit
        // TODO - use dual when no input is provided
        show_error_exit("No input data provided.");
    }

    // init column names
    const auto col_count = get_col_count(options, data);
    std::vector<std::string> col_names(col_count);
    for (int i = 0; i < col_count; i++) {
        col_names.push_back("col" + std::to_string(i + 1));
    }

    // prepare data to be processed
    std::vector<std::vector<std::string>> output = prepare_data(data, col_count, options.delimiter);

    // Split the query into multiple queries
    std::vector<std::string> queries = split_string(options.query, '|');


    for (const auto& query : queries) {
        const auto *input = &output;
        // TODO - process the query here
        // Process the input data here
        output = process_query(*input, query);
    }

    return output;
}

std::string readFileString(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        show_error_exit("Unable to open file: " + filename);
    }

    std::string content{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
    return content;
}
