English | [简体中文](README_zh-CN.md)

### Bash-SQL Usage

```bash
sql [OPTION] [QUERIES]
```

> Query statements must be enclosed in double quotes.

## Options

- `-h`, `--help`: Display this help and exit.
- `-v`, `--version`: Output version information and exit.
- `-t`, `--title`: Print table title.
- `-l`, `--line-no`: Print line number.
- `-f`, `--file=FILE`: Read data from FILE.
- `-d`, `--delimiter=DELIMITER`: Use DELIMITER as field delimiter.
- `-c`, `--columns=COLUMNS`: Use COLUMNS as number of columns.

## Queries

Queries are SQL-like select statements separated by `|`:

```
select COLUMNS [WHERE] [ORDER BY] [LIMITS]
```

> Keywords are case-insensitive.

- `COLUMNS`: List columns to select. Use `*` to select all columns. Default column names are `col1`, `col2`, .... Use `as` for aliasing columns.
- `WHERE`: Filter rows with `like` clause or `reg` clause. Use 'column like pattern' or 'column reg pattern' to filter. Add `not` before `like` or `reg` to reverse.
    - When using `like`, `%` and `_` are supported like in MySQL, and escape them by `\`.
    - When using `reg`, pattern should be a regular expression.
    - Pattern needs no quotes.
- `ORDER BY`: Reorder data after selecting. Specify one or more columns to order by. Use `asc` for ascending, `desc` for descending. `asc` can be omitted.
- `LIMITS`: Limit output lines. Use 'limit lines' or 'limit offset, lines'.

## Example

```bash
ps -aux | sql -tlc11 "select *, col1 as user, col2 as pid, col9 as start, col11 as command \
  where col2 not like PID | select * order by start desc limit 10"
```
