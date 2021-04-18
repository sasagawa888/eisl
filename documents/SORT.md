# Sort
Sort library,
written by M.Hiroi.

# Acknowledgement
Thanks to Mr. Hiroi.

# Functions

```lisp
(quick-sort ls)
(insert-sort ls)
(select-sort ls)
```

# Usage
If you need speed, compile first.

```lisp
(import "compiler")
(compile-file "library/sort.lsp)
```

```
> (import "sort")
T
> (quick-sort '(3 2 3 1 9 0 8 3 4 7))
(0 1 2 3 3 3 4 7 8 9)
> (insert-sort '(3 2 3 1 9 0 8 3 4 7))
(0 1 2 3 3 3 4 7 8 9)
> (select-sort '(3 2 3 1 9 0 8 3 4 7))
(0 1 2 3 3 3 4 7 8 9)
> 
```
