//
// Created by tika on 5/2/24.
//

#include "process.h"

void prepare_data(const String &data, Vector<Vector<String>> &output, const char d) {
    val col_count = output[0].size();
    var rows = Util::split_string(data, '\n');
    for (var &row: rows) {
        var cols = d == 0 ? Util::Util::split_string_by_spaces(row) : Util::split_string(row, d);
        if (cols.size() <= col_count) {
            output.push_back(cols);
            continue;
        }
        Vector<String> new_row(col_count);
        for (var i = 0; i < col_count; i++) {
            new_row[i] = cols[i];
        }
        for (var i = col_count; i < cols.size(); i++) {
            new_row[col_count - 1] += " " + cols[i];
        }
        output.push_back(new_row);
    }
}

int get_col_count(const ProgramOptions &options, const String &data) {
    if (options.columns > 0) {
        return options.columns;
    }

    val first_line = Util::Util::split_string(data, '\n')[0];
    val col_count = options.delimiter == 0
                    ? Util::Util::split_string_by_spaces(first_line).size()
                    : Util::split_string(first_line, options.delimiter).size();
    return static_cast<int>(col_count);
}

Vector<String> exec_select(const Vector<String> &title, const Vector<String> &row,
                                     const String &select) {
    Vector<String> new_row;

    val cols = Util::split_string(select, ',');
    for (val &col: cols) {
        if (col == "*") {
            for (val &col1: row) {
                new_row.push_back(col1);
            }
            continue;
        }
        val pos = col.rfind(" as ");
        val old_col = pos == String::npos ? Util::trim(col) : Util::trim(col.substr(0, pos));
        val idx= std::find(title.begin(), title.end(), old_col);
        val new_col = row[std::distance(title.begin(), idx)];
        new_row.push_back(new_col);
    }
    return new_row;
}

bool exec_where(const Vector<String> &title, const Vector<String> &row, const String &where) {
    // TODO
    return true;
}

Vector<String> handle_title(const Vector<String>& title, const String &select) {
    Vector<String> new_title;

    val cols = Util::split_string(select, ',');
    for (val &col: cols) {
        if (col == "*") {
            for (val &col1: title) {
                new_title.push_back(col1);
            }
            continue;
        }
        val pos = col.rfind(" as ");
        if (pos != String::npos && pos >= col.size() - 4) {
            Util::show_error("Syntax error near '" + col + "'");
        }
        val old_col = pos == String::npos ? Util::trim(col) : Util::trim(col.substr(0, pos));
        val idx= std::find(title.begin(), title.end(), old_col);
        if(idx == title.end()){
            Util::show_error("Column '" + old_col + "' not found");
        }
        val alias = pos == String::npos ? "" : Util::trim(col.substr(pos + 4));
        val new_col = alias.empty() ? old_col : alias;

        std::for_each(new_title.begin(), new_title.end(), [&new_col](const String &s) {
            if (new_col == s) Util::show_error("Duplicate column name '" + new_col + "'");
        });

        new_title.push_back(new_col);
    }
    return new_title;
}

Vector<Vector<String>> process_query(const Vector<Vector<String>> &input,
                                                    const String &query) {
    // select xx as x1, xx as x2 where x1='test abc' and x1 is not null order by x1, x2 desc limit 20, 2
    val wherePos = query.find(" where ");
    val orderPos = query.find(" order by ");
    val limitPos = query.find(" limit ");

    val limit = Util::trim(limitPos != String::npos ? query.substr(limitPos + 7) : "");
    var rest = query.substr(0, limitPos);

    val order = Util::trim(orderPos != String::npos ? rest.substr(orderPos + 10) : "");
    rest = rest.substr(0, orderPos);

    val where = Util::trim(wherePos != String::npos ? rest.substr(wherePos + 7) : "");
    val select = Util::trim(rest.substr(0, wherePos).substr(7));

    Vector<Vector<String>> output;
    val new_title = handle_title(input[0], select);
    output.push_back(new_title);
    for (var i = 1; i < input.size(); i++) {
        // 1. where 2. select
        if (exec_where(input[0], input[i], where)) {
            var new_row = exec_select(input[0], input[i], select);
            output.push_back(new_row);
        }
    }
    // 3. order 4. limit

    return output;
}

Vector<Vector<String>> process_data(const ProgramOptions &options) {
    String data;

    // get data string
    if (!options.data.empty())
        data = options.data;
    else if (!options.file.empty())
        data = readFileString(options.file);

    if (data.empty()) {
        // If input is empty, show error and exit
        // TODO - Only data-independent functions are available when no input is provided
        Util::show_error("No input data provided.");
    }

    // init column names
    val col_count = get_col_count(options, data);
    Vector<String> col_names(col_count);
    for (var i = 0; i < col_count; i++) {
        col_names[i] = "col" + std::to_string(i + 1);
    }

    // prepare data to be processed
    Vector<Vector<String>> output;
    output.push_back(col_names);
    prepare_data(data, output, options.delimiter);
    // Split the query into multiple queries
    val queries = Util::split_string(options.query, '|');

    for (val &query: queries) {
        output = process_query(output, query);
    }

    return output;
}

String readFileString(const String &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        Util::show_error("Unable to open file: " + filename);
    }

    String content{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
    return Util::rtrim(content);
}
