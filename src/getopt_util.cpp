//
// Created by tika on 4/21/24.
//

#include "getopt_util.h"

void argError(const String &error) {
    Util::show_error(error + "\nUse -h for help.");
}

ProgramOptions parseCommandLine(int argc, char *argv[]) {
    ProgramOptions options = {false, "", "", '\0', 0, ""};

    var help = false;
    var version = false;
    var data = false;
    var file = false;

    static option long_options[] = {
            {"help",      no_argument,       null, 'h'},
            {"version",   no_argument,       null, 'v'},
            {"title",     no_argument,       null, 't'},
            {"file",      required_argument, null, 'f'},
            {"delimiter", required_argument, null, 'd'},
            {"columns",   required_argument, null, 'c'},
            {null, 0,                     null, 0}
    };

    // 检查是否有标准输入
    if (isatty(STDIN_FILENO) == 0) {
        data = true;
        String line;
        while (std::getline(cin, line)) {
            options.data += line + "\n";
        }
        if (!options.data.empty()) {
            options.data.pop_back();
        }
    }

    int c;
    while ((c = getopt_long(argc, argv, "hvtd:f:c:", long_options, null)) != -1) {
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
                options.columns = std::stoi(optarg);
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
        // show help information
        exit(0);
    }

    // 打印版本信息
    if (version) {
        // show version information
        exit(0);
    }

    // 如果不是显示帮助信息和版本信息，则检查必选参数
    if (options.query.empty()) {
        argError("Query is required.");
    }

    return options;
}