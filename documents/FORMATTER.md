# Formatter

## Usage

`(import "formatter")` or invoke eisl with the -f option (`eisl -f`).

```lisp
(formatter "filename")
```

The original file is saved as *filename.org*.


if you give argument symbol `stdio`, formatter read from standard-input and output to standard-output.

```lisp
(formatter 'stdio)
```