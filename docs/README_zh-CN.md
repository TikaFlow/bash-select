# Bash-SQL用法说明

```bash
sql [选项] [查询语句]
```

> 查询语句必须用双引号括起来。

## 选项

- `-h`, `--help`：显示此帮助信息并退出。
- `-v`, `--version`：输出版本信息并退出。
- `-t`, `--title`：输出标题。
- `-l`, `--line-no`：输出行号。
- `-f`, `--file=FILE`：从文件中读取数据。
- `-d`, `--delimiter=DELIMITER`：指定字符作为字段分隔符。
- `-c`, `--columns=COLUMNS`：指定数据源的列数。

## 查询语句

多条查询语句使用`|`分割，每条查询语句结构如下：

```
select COLUMNS [WHERE] [ORDER BY] [LIMITS]
```

> 查询语句的关键字大小写不敏感。

- `COLUMNS`：选择列的列表。使用`*`选择所有列。默认列名为`col1`,`col2`, ...。可以使用`as`进行列别名。
- `WHERE`：使用`like`或`reg`子句过滤行。使用`not`否定`like`或`reg`。
    - 当使用`like`时，支持`%`和`_`，与`MySQL`中的用法相同，可以使用`\`转义。
    - 当使用`reg`时，模式应为正则表达式。
- `ORDER BY`：根据列重新排序数据。指定一个或多个列。使用`asc`表示升序，使用`desc`表示降序。
- `LIMITS`：限制输出行数。可以使用`limit lines`或`limit offset, lines`。

## 示例

```bash
ps -aux | sql -tlc11 "select *, col1 as user, col2 as pid, col9 as start, col11 as command \
  where col2 not like PID | select * order by start desc limit 10"
```
