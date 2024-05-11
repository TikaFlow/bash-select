English | [简体中文](README_zh-CN.md)

# Bash-SQL

Using SQL-like languages to process lightweight data in bash.

# Installation

## 环境需求

- make
- g++

## #1. download the source code by `git clone` or any way you like

## #2. enter the extracted directory and create and enter the `build` directory

```bash
cd bash-sql
mkdir build && cd build
```

## #3. generate Makefile

> Use the configure script **OR** the cmake command.

```bash
# 使用configure
../configure --prefix=/you/custom/prefix

# 使用cmake
cmake -DCMAKE_INSTALL_PREFIX=/your/custom/prefix ..
```

## #4. compile and install the program

```bash
make
make install
```

# Usage

```bash
# Ensure using double quotes to wrap query statements to avoid bash expanding * or any characters
$ ll | sql -tlc9 "select col3 as user, col5 as size, col9 as filename"
```

> Please refer to the [documentation](docs) for detailed usage.