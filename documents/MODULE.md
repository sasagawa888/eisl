# Modules
The
[ISLisp standard](minejima.jp/ISLispHyperDraft/islisp-v23.html)
has no modules.
I tried to extend ISLisp with reference to the Elixir module system.
The compiler for Easy-ISLisp, which has thousands of lines, has also been changed to be managed by this module. 
For the time being, name conflicts are avoided.

# Specification

## defmodule

`(defmodule module-name main body)`
gives a symbol to the module name.
Everything specified by ISLisp can be described in the main body, defun, defglobal, defmacro, defgeneric, etc.
You can define a function using `defpublic` *only* in a module. This is a function definition, but it can be referenced externally.
Other function names, etc., are converted like module-name::function-name.
For example, if you define a function called bar in a module called foo, the function name is foo::bar.

## import

`(import library-name fn1 fn2 ... fnN)`
The library name is given as a character string.
Save the library defined using `defmodule` in the library folder beforehand.
If there is a compiled version, this will be read in preference.

if using import in module, require fn1 fn2 ... fnN.  they are imported function name.

e.g. 

```
(defmodule foo
   (import "formula" infix->prefix)

   (defpublic bar (x)
       (infix-prefix x))
)

```

## defpublic
Only functions defined using defpublic can be referenced from outside the module, e.g.:

```
(defmodule foo
    (defglobal a 3)

    (defpublic bar (x)
        (+ (boo x) (gfib x)))

    (defun boo (x)
        (+ x a))

    (defpublic baz (x)
        (uoo x))

    (defmacro uoo (x)
        `(+ ,x ,x))

    (defgeneric gfib (n)
        (:method ((n <integer>)) (cond ((= n 1) 1)
                                       ((= n 2) 1)
                                       (t (+ (gfib (- n 1)) (gfib (- n 2)))) )))

    (defpublic fact (n)
        (if (= n 0)
            1
            (* n (fact (- n 1)))))
)

Easy-ISLisp Ver1.72
> (load "tests/module.lsp")
T
> (bar 10)
68
> (baz 10)
20
> (uoo 2)
Unbound function at eval UOO
debug mode ?(help)
>>:q
Easy-ISLisp Ver1.72
> (fact 10)
3628800
> 
```

Function `boo` is private. The global variable declaration, `(defglobal a 3)`, is private and cannot be referenced from outside the module.
The same applies to dynamic variables like `(defdynamic x n)`.
