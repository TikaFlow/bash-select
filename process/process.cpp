//
// Created by tika on 5/2/24.
//

#include "process.h"

void prepare_data(const String &data, Vector<Vector<String>> &output, const char d) {
    val col_count = output[0].size();
    var rows = split_string(data, '\n');
    for (var &row: rows) {
        var cols = d == 0 ? split_string_by_spaces(row) : split_string(row, d);
        if (cols.size() > col_count) {
            for (var i = col_count; i < cols.size(); i++) {
                cols[col_count - 1] += " " + cols[i];
            }
        }
        cols.resize(col_count);
        output.push_back(cols);
    }
}

int get_col_count(const ProgramOptions &options, const String &data) {
    if (options.columns > 0) {
        return options.columns;
    }

    val first_line = split_string(data, '\n')[0];
    val col_count = options.delimiter == 0
                    ? split_string_by_spaces(first_line).size()
                    : split_string(first_line, options.delimiter).size();
    return static_cast<int>(col_count);
}

Vector<String> exec_select(const Vector<String> &title, const Vector<String> &row,
                           const String &select) {
    Vector<String> new_row;

    val cols = split_string(select, ',');
    for (val &col: cols) {
        if (col == "*") {
            for (val &col1: row) {
                new_row.push_back(col1);
            }
            continue;
        }
        val pos = col.rfind(" as ");
        val old_col = pos == npos ? trim(col) : trim(col.substr(0, pos));
        val idx = std::find(title.begin(), title.end(), old_col);
        val new_col = row[std::distance(title.begin(), idx)];
        new_row.push_back(new_col);
    }
    return new_row;
}

bool exec_where(const Vector<String> &title, const Vector<String> &row, const String &where) {
    // TODO
    return true;
}

Vector<String> handle_title(const Vector<String> &title, const String &select) {
    Vector<String> new_title;

    val cols = split_string(select, ',');
    for (val &col: cols) {
        if (col == "*") {
            for (val &col1: title) {
                new_title.push_back(col1);
            }
            continue;
        }
        val pos = col.rfind(" as ");
        if (pos != npos && pos >= col.size() - 4) {
            show_error("Syntax error near '" + col + "'");
        }
        val old_col = pos == npos ? trim(col) : trim(col.substr(0, pos));
        val idx = std::find(title.begin(), title.end(), old_col);
        if (idx == title.end()) {
            show_error("Column '" + old_col + "' not found");
        }
        val alias = pos == npos ? "" : trim(col.substr(pos + 4));
        val new_col = alias.empty() ? old_col : alias;

        for_each(new_title.begin(), new_title.end(), [&new_col](const String &s) {
            if (new_col == s) show_error("Duplicate column name '" + new_col + "'");
        });

        new_title.push_back(new_col);
    }
    return new_title;
}

Vector<Vector<String>> process_query(const Vector<Vector<String>> &input,
                                     const String &query) {
    // select xx as x1, xx as x2 where x1='test abc' and x1 is not null order by x1, x2 desc limit 20, 2
    val where_pos = query.find(" where ");
    val order_pos = query.find(" order by ");
    val limits_pos = query.find(" limit ");

    val limits = trim(limits_pos != npos ? query.substr(limits_pos + 7) : "");
    var offset = 0, limit = 0;
    if (!limits.empty()) {
        val offset_pos = limits.find(',');
        offset = offset_pos != npos ? stoi(trim(limits.substr(0, offset_pos))) : 0;
        limit = stoi(trim(offset_pos != npos ? limits.substr(offset_pos + 1) : limits));
    }
    var rest = query.substr(0, limits_pos);

    val order = trim(order_pos != npos ? rest.substr(order_pos + 10) : "");
    rest = rest.substr(0, order_pos);

    val where = trim(where_pos != npos ? rest.substr(where_pos + 7) : "");
    val select = trim(rest.substr(0, where_pos).substr(7));

    Vector<Vector<String>> output;
    val new_title = handle_title(input[0], select);
    output.push_back(new_title);
    for (var i = 1 + offset; i < input.size(); i++) {
        // 1. where 2. select
        if (exec_where(input[0], input[i], where)) {
            var new_row = exec_select(input[0], input[i], select);
            output.push_back(new_row);
            // limit if no considered order by
            if (limit > 0 && output.size() >= limit + 1) {
                break;
            }
        }
    }
    // 3. order by 4. limit

    return output;
}

void verify_query(const String &query) {
    val pattern = "(SELECT|select)\\s+((([\\w][\\w\\d]+)(\\s+(AS|as)\\s+([\\w][\\w\\d]+))?)|\\*)"
                  "(\\s*,\\s*((([\\w][\\w\\d]+)(\\s+(AS|as)\\s+([\\w][\\w\\d]+))?)|\\*))*"
                  "(\\s+(WHERE|where)\\s+([\\w][\\w\\d]+)(\\s+(NOT|not))?\\s+((LIKE|like)\\s+[\\w\\d\\%\\_]+|(REG|reg)\\s+.+))?"
                  "(\\s+(ORDER|order)\\s+(BY|by)\\s+([\\w][\\w\\d]+)(\\s*,\\s*[\\w][\\w\\d]+)*(\\s+(ASC|asc|DESC|desc))?)?"
                  "(\\s+(LIMIT|limit)\\s+(\\d+)(\\s*,\\s*\\d+)?)?";
    Regex reg(pattern);
    if (!std::regex_match(trim(query), reg)) {
        show_error("Unrecognized query statement: '" + query + "'");
    }
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
        show_error("No input data provided.");
    }

    // init column names
    val col_count = get_col_count(options, data);
    Vector<String> col_names(col_count);
    for (var i = 0; i < col_count; i++) {
        col_names[i] = "col" + to_string(i + 1);
    }

    // prepare data to be processed
    Vector<Vector<String>> output;
    output.push_back(col_names);
    prepare_data(data, output, options.delimiter);
    // Split the query into multiple queries
    val queries = split_string(options.query, '|');

    for (val &query: queries) {
        verify_query(query);
        output = process_query(output, query);
    }

    return output;
}

String readFileString(const String &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        show_error("Unable to open file: " + filename);
    }

    String content{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
    return trim(content);
}
