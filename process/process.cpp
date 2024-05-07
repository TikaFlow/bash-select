//
// Created by tika on 5/2/24.
//

#include "process.h"

std::vector<std::string> split_string(const std::string &query, char delimiter) {
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

std::vector<std::string> split_string_by_spaces(const std::string &input) {
    const std::regex re("\\s+");

    std::sregex_token_iterator it(input.begin(), input.end(), re, -1);
    std::vector<std::string> tokens;

    for (const std::sregex_token_iterator end; it != end; ++it) {
        tokens.push_back(it->str());
    }

    tokens.erase(std::remove_if(tokens.begin(), tokens.end(), [](const std::string &s) {
        return s.empty();
    }), tokens.end());

    return tokens;
}

void prepare_data(const std::string &data, std::vector<std::vector<std::string>> &output, const char d) {
    val col_count = output[0].size();
    var rows = split_string(data, '\n');
    for (var &row: rows) {
        var cols = d == 0 ? split_string_by_spaces(row) : split_string(row, d);
        if (cols.size() <= col_count) {
            output.push_back(cols);
            continue;
        }
        std::vector<std::string> new_row(col_count);
        for (size_t i = 0; i < col_count; i++) {
            new_row[i] = cols[i];
        }
        for (size_t i = col_count; i < cols.size(); i++) {
            new_row[col_count - 1] += " " + cols[i];
        }
        output.push_back(new_row);
    }
}

int get_col_count(const ProgramOptions &options, const std::string &data) {
    if (options.columns > 0) {
        return options.columns;
    }

    val first_line = split_string(data, '\n')[0];
    val col_count = options.delimiter == 0
                    ? split_string_by_spaces(first_line).size()
                    : split_string(first_line, options.delimiter).size();
    return static_cast<int>(col_count);
}

std::vector<std::string> exec_select(const std::vector<std::string> &title, const std::vector<std::string> &row,
                                     const std::string &select) {
    std::vector<std::string> new_row;

    val cols = split_string(select, ',');
    for (val &col: cols) {
        if (col == "*") {
            for (val &col1: row) {
                new_row.push_back(col1);
            }
            continue;
        }
        val pos = col.rfind(" as ");
        val old_col = pos == std::string::npos ? trim(col) : trim(col.substr(0, pos));
        val idx= std::find(title.begin(), title.end(), old_col);
        val new_col = row[std::distance(title.begin(), idx)];
        new_row.push_back(new_col);
    }
    return new_row;
}

bool exec_where(const std::vector<std::string> &title, const std::vector<std::string> &row, const std::string &where) {
    // TODO
    return true;
}

std::vector<std::string> handle_title(const std::vector<std::string>& title, const std::string &select) {
    std::vector<std::string> new_title;

    val cols = split_string(select, ',');
    for (val &col: cols) {
        if (col == "*") {
            for (val &col1: title) {
                new_title.push_back(col1);
            }
            continue;
        }
        val pos = col.rfind(" as ");
        if (pos >= col.size() - 4) {
            show_error_exit("Syntax error near '" + col + "'");
        }
        val old_col = pos == std::string::npos ? trim(col) : trim(col.substr(0, pos));
        val idx= std::find(title.begin(), title.end(), old_col);
        if(idx == title.end()){
            show_error_exit("Column '" + old_col + "' not found");
        }
        val alias = pos == std::string::npos ? "" : trim(col.substr(pos + 4));
        val new_col = alias.empty() ? old_col : alias;

        std::for_each(new_title.begin(), new_title.end(), [&new_col](const std::string &s) {
            if (new_col == s) show_error_exit("Duplicate column name '" + new_col + "'");
        });

        new_title.push_back(new_col);
    }
    return new_title;
}

std::vector<std::vector<std::string>> process_query(const std::vector<std::vector<std::string>> &input,
                                                    const std::string &query) {
    // select xx as x1, xx as x2 where x1='test abc' and x1 is not null order by x1, x2 desc limit 20, 2
    const size_t wherePos = query.find(" where ");
    const size_t orderPos = query.find(" order by ");
    const size_t limitPos = query.find(" limit ");

    val limit = trim(limitPos != std::string::npos ? query.substr(limitPos + 7) : "");
    var rest = query.substr(0, limitPos);

    val order = trim(orderPos != std::string::npos ? rest.substr(orderPos + 10) : "");
    rest = rest.substr(0, orderPos);

    val where = trim(wherePos != std::string::npos ? rest.substr(wherePos + 7) : "");
    val select = trim(rest.substr(0, wherePos).substr(7));

    std::vector<std::vector<std::string>> output;
    val new_title = handle_title(input[0], select);
    output.push_back(new_title);
    for (int i = 1; i < input.size(); i++) {
        // 1. where 2. select
        if (exec_where(input[0], input[i], where)) {
            var new_row = exec_select(input[0], input[i], select);
            output.push_back(new_row);
        }
    }
    // 3. order 4. limit

    return output;
}

std::vector<std::vector<std::string>> process_data(const ProgramOptions &options) {
    std::string data;

    // get data string
    if (!options.data.empty())
        data = options.data;
    else if (!options.file.empty())
        data = readFileString(options.file);

    if (data.empty()) {
        // If input is empty, show error and exit
        // TODO - Only data-independent functions are available when no input is provided
        show_error_exit("No input data provided.");
    }

    // init column names
    val col_count = get_col_count(options, data);
    std::vector<std::string> col_names(col_count);
    for (int i = 0; i < col_count; i++) {
        col_names[i] = "col" + std::to_string(i + 1);
    }

    // prepare data to be processed
    std::vector<std::vector<std::string>> output;
    output.push_back(col_names);
    prepare_data(data, output, options.delimiter);
    // Split the query into multiple queries
    std::vector<std::string> queries = split_string(options.query, '|');

    for (val &query: queries) {
        output = process_query(output, query);
    }

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
