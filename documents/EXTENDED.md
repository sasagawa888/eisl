# Extended functions


| Function              | Description                                    |
| --------------------- | ---------------------------------------------- |
| (atom x)              | is x not cons? return T or NIL                 |
| (eval x)              | evaluate s-expression x                        |
| (nconc x y)           | append list x and list y  destructively        |
| (random n)            | random-integer from 0 to n                     |
| (random-real)         | random-float-number from 0 to 1                |
| (set-random n)        | set random seed to non-negative number n       |
| (gbc)                 | invoke garbage collection.                     |
| (gbc t)               | display message when invoke GC.                |
| (gbc nil)             | not display message when invoke GC.            |
| (heapdump n)          | display cell dump list from nth address        |
| (instance n)          | display instance of nth address                |
| (defmodule name body) | see tests/module.lsp                           |
| (import x)            | import library. e.g. (import "compiler")       |
| (quit)                | quit from interpreter                          |
| (load filename)       | load code from file e.g. (load "foo.lsp")      |
| (getenv var)          | get environment-var e.g. (getenv "EASY_ISLISP")|
| (line-argument n)     | get nth argument from OS. n is zero base       |
| (line-argument)       | get all arguments from OS.                     |
| (print obj)           | print obj to standard-stream                   |
| (system cmd)          | send bash command e.g. (system "ls")           |
| (funcp x)             | is x user-defined-function? return T or NIL    |
| (subrp x)             | is x subr? return T or NIL                     |
| (macrop x)            | is x macros? return T or NIL                   |
| (fixnump x)           | is x fixnum?(32bit) return T or NIL            |
| (longnump x)          | is x longnum?(64bit) return T or NIL           |
| (bignump x)           | is x bignum? return T or NIL                   |
| (macroexpand-1 x)     | macroexpand x only once                        |
| (macroexpand-all x)   | macroexpand x completely                       |
