# Bash-Select

在bash中使用类似SQL的语言处理轻量级数据。

# 安装

## #1. 通过克隆项目或其他方式下载源代码

## #2. 进入解压后的根目录，并创建进入`build`目录

```bash
cd bash-sql
mkdir build && cd build
```

## #3. 运行`configure`脚本，并指定安装目录

```bash
../configure --prefix=/usr/local
```

## #4. 编译并安装

```bash
make
make install
```

# 使用方法

```bash
$ ll | sql select *
```