# Prolog library
Prolog interpreter in ISLisp

# import
(import "prolog")

# usage as Prolog intepreter

## invoke 
```
> (prolog)
```

## builtin predicate

| Lisp-Prolog                         | Edinburgh-Prolog    |
|-------------------------------------|---------------------|
| (assert x)                          | assert(x)           |
| (consult filename)                  | consult(filename)   |
| (reconsult filename)                | reconsult(filename) |
| (load filename) load lisp code      |  -                  |
| (halt)                              | halt                |
| (is x y)                            | x is y              |
| (= x y)                             | x = y               |
| (== x y)                            | x == y              |
| (/= x y)                            | x /= y              |
| (> x y)                             | x > y               |
| (>= x y)                            | x => y              |
| (< x y)                             | x < y               |
| (<= x y)                            | x =< y              |
| (write x)                           | write(x)            |
| (nl)                                | nl                  |
| (system x) call bash                |  -                  |
| (trace)                             | trace               |
| (notrace)                           | notrace             |
| (defun ...)                         |  -                  |
| (defgeneric ...)                    |  -                  |
| (defmethod ...)                     |  -                  |
| (findall x y z)                     | findall(x,y,z)      |
| (length x y)                        | length(x,y)         |
| (member x y)                        | member(x,y)         |



# usage as embedded Prolog in Lisp

### assert
(assert predicate/clause)

e.g. (assert '(human jhon))

### prove
(-? predicate)

e.g. (-? '(human jhon))

### deref
(~? variable environment)

e.g. 
```
(let ((env (~? '(human _x))))
   (~? '_x env))
```

see example/prolog-test.lsp