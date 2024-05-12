# Bash-Select

在bash中使用类似SQL的语言处理轻量级数据。

# 安装

## 环境需求

- cmake
- make
- g++

## #1. 通过克隆项目或其他方式下载源代码

## #2. 进入解压后的根目录，并创建进入`build`目录

```bash
cd bash-sql
mkdir build && cd build
```

## #3. 生成Makefile

```bash
cmake -DCMAKE_INSTALL_PREFIX=/your/custom/prefix ..
```

## #4. 编译并安装

```bash
make
make install
```

# 使用方法

```bash
# 确保使用双引号来包裹query语句以免bash对*或任何字符进行扩展
$ ll | sql -tlc9 "select col3 as user, col5 as size, col9 as filename"
```

> 详细用法请参考[文档](docs/README_zh-CN.md)。