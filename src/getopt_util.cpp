//
// Created by tika on 4/21/24.
//

#include "getopt_util.h"

void argError(const String &error) {
    show_error(error + "\nUse -h for help.");
}

void show_version() {
    cout << "Bash-sql V" << VERSION << " by " << AUTHOR << endl;
}

void show_help() {
    cout << "Using SQL-like languages to process lightweight data in bash." << endl;
    cout << endl;

    cout << "Usage: sql [OPTION] [QUERIES]" << endl;
    cout << endl;

    cout << "Options:" << endl;
    cout << "  -h, --help                   display this help and exit." << endl;
    cout << "  -v, --version                output version information and exit." << endl;
    cout << "  -t, --title                  print table title." << endl;
    cout << "  -l, --line-no                print line number." << endl;
    cout << "  -f, --file=FILE              read data from FILE." << endl;
    cout << "  -d, --delimiter=DELIMITER    use DELIMITER as field delimiter." << endl;
    cout << "  -c, --columns=COLUMNS        use COLUMNS as number of columns." << endl;
    cout << endl;

    cout << "Queries:" << endl;
    cout << "  QUERY [ | QUERY2 [...] ]" << endl;
    cout << "       each query is a sql-like select statement separated by `|`:" << endl;
    cout << endl;
    cout << "       select COLUMNS [WHERE] [ORDER BY] [LIMITS]" << endl;
    cout << endl;
    cout << "       keywords are case-insensitive." << endl;
    cout << "  COLUMNS      list columns to select" << endl;
    cout << "       use '*' to select all columns." << endl;
    cout << "       default column names are col1, col2, ..." << endl;
    cout << "       aliasing column by using 'as'." << endl;
    cout << "  WHERE        filter rows with like clause or reg clause." << endl;
    cout << "       use 'column like pattern' or 'column reg pattern' to filter." << endl;
    cout << "       add 'not' before 'like' or 'reg' to reverse." << endl;
    cout << "       when 'like', % and _ are supported just like in mysql, and escape them by \\." << endl;
    cout << "       when 'reg', pattern should be a regular expression." << endl;
    cout << "       pattern needs no quotes." << endl;
    cout << "  ORDER BY     reorder data after selecting." << endl;
    cout << "       specify one or more columns to order by." << endl;
    cout << "       use 'asc' for ascending, 'desc' for descending." << endl;
    cout << "       'asc' can be omitted." << endl;
    cout << "  LIMITS       limit output lines." << endl;
    cout << "       either 'limit lines' or 'limit offset, lines' are supported." << endl;
    cout << endl;

    cout << "Example:" << endl;
    cout << "  ps -aux | sql -tlc11 \"select *, col1 as user, col2 as pid, col9 as start, col11 as command \\" << endl;
    cout << "  where col2 not like PID | select * order by start desc limit 10\"" << endl;
    cout << endl;
}

ProgramOptions parseCommandLine(int argc, char *argv[]) {
    ProgramOptions options = {false, false, "", "", '\0', 0, ""};

    var help = false;
    var version = false;
    var data = false;
    var file = false;

    static option long_options[] = {
            {"help",      no_argument,       null, 'h'},
            {"version",   no_argument,       null, 'v'},
            {"title",     no_argument,       null, 't'},
            {"line-no",   no_argument,       null, 'l'},
            {"file",      required_argument, null, 'f'},
            {"delimiter", required_argument, null, 'd'},
            {"columns",   required_argument, null, 'c'},
            {null, 0,                        null, 0}
    };

    // 检查是否有标准输入
    if (isatty(STDIN_FILENO) == 0) {
        data = true;
        String line;
        while (getline(cin, line)) {
            options.data += line + "\n";
        }
        if (!options.data.empty()) {
            options.data.pop_back();
        }
    }

    int c;
    while ((c = getopt_long(argc, argv, "hvtld:f:c:", long_options, null)) != -1) {
        switch (c) {
            case 'h':
                help = true;
                break;
            case 'v':
                version = true;
                break;
            case 't':
                options.title = true;
                break;
            case 'l':
                options.line_no = true;
                break;
            case 'f':
                // 判断文件是否存在
                if (access(optarg, F_OK)) {
                    argError("File not found: " + String(optarg));
                }
                file = true;
                options.file = optarg;
                break;
            case 'd':
                options.delimiter = optarg[0];
                break;
            case 'c':
                options.columns = stoi(optarg);
                break;
            case '?':
                argError("Unknown option.");
                break;
            default:
                argError("Unknown error.");
                break;
        }
    }

    // 处理非选项参数
    for (int i = optind; i < argc; ++i) {
        options.query += argv[i];
        if (i < argc - 1) {
            options.query += " ";
        }
    }

    // 检查帮助和版本信息选项
    if (help || version) {
        if (options.title || !options.data.empty() || !options.file.empty() || options.delimiter != '\0' ||
            options.columns != 0 || !options.query.empty()) {
            if (help) argError("Help option cannot be used with other options.");
            if (version) argError("Version option cannot be used with other options.");
        }
    } else {
        // 检查互斥参数
        if (data && file) {
            argError("Only file or standard input should be specified.");
        }
    }

    // 打印帮助信息
    if (help) {
        show_version();

        show_help();

        exit(0);
    }

    // 打印版本信息
    if (version) {
        show_version();
        exit(0);
    }

    // 如果不是显示帮助信息和版本信息，则检查必选参数
    if (options.query.empty()) {
        // argError("Query is required.");
    }

    return options;
}