# Sort
  sort library 
  written by M.Hiroi

# functions

```
(quick-sort ls)

(insert-sort ls)

(select-sort ls)

```

# usage
If you need speed, compile before that.

```
(import "compiler")
(compile-file "library/sort.lsp)

```

```
(import "sort")

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