English | [简体中文](README_zh-CN.md)

# Bash-SQL

Using SQL-like languages to process lightweight data in bash.

# Installation

## #1. download the source code by `git clone` or any way you like

## #2. enter the extracted directory and create and enter the `build` directory

```bash
cd bash-sql
mkdir build && cd build
```

## #3. run the `configure` script, and specify the installation directory

```bash
../configure --prefix=/usr/local
```

## #4. compile and install the program

```bash
make
make install
```

# Usage

```bash
# Ensure using double quotes to wrap query statements to avoid bash expanding * or any characters
$ ll | sql "select *"
```