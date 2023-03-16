# Interface between Lisp and C

## Overview
Easy-ISLisp's compiler translates Lisp code into C code. This makes it possible to embed C code into ISLisp code and call C functions and access C variables.


## Simple example
Below is an example of bit manipulation in C code.

```
;;bit shift
(defun ash (n m)
  (if (>= m 0)
      (c-lang "res = INT_FLAG | ((INT_MASK & N) << (INT_MASK & M));")
      (if (>= n 0)
          (let ((m1 (- m)))
            (c-lang "res = INT_FLAG | ((INT_MASK & N) >> (INT_MASK & M1));"))
          (let ((m1 (- m)))
            (c-lang "res = INT_FLAG | (N >> (INT_MASK & M1));")))))
          
```

### (c-lang str)
Embeds the C code string in `str` into the compiler generated C code. This C code can access ISLisp variables, however, the ISLisp varible names must be converted into upper case when referenced in the C code. For example: a variable with the name `foo` in ISLisp will be `FOO` in the C code. The value returned in this S-expression is equal to the value of the C variable `res`.

### Handling small integers
Small integers in Easy-ISLisp are handled as immediate values. In order to import a small integer into C code, it is necessary to apply the bit mask `INT_MASK`. This sets the immediate integer flag bit to 0. This flag bit is the second most significant bit in a C `int` type.

```
INT_MASK & N
```

As described above, integer arguments `n` and `m` of the `ash` function must be converted to upper case to be used in C code. In this example, the C variables would be `N` and `M`. The values of these variables are converted to integers of `int` type in the C language by performing a bitwise AND operation with `INT_MASK`.

```
INT_FLAG | ...

```
Before we can pass a small integer value into Easy-ISLisp, we must suppress the cell consumption of small integers. To convert a small C integer to an immediate Easy-ISLisp integer, perfom the bitwise OR operation with `INT_FLAG`. This sets the immediate integer flag bit to 1 and it can thus be treated as an immediate small integer in Easy-ISLisp.

```
res = ...

```

The value of an expression in C should be assigned to a C variable named `res`. This is the return value of the ISLisp S-expression.

## Other extension functions


### (c-include str)
This includes a C file into the Easy-ISLisp compiler generated C code. It allows you to refrence code in the included file in the `c-lang` expressions.

```
;; example
(c-include "stdio.h")  
```

This is translated to the following C code, which is then embedded into the compiler generated C code:

```
#include stdio.h
```

### (c-option str)

This is used to specify C compiler options. This is useful for specifying which libraries to link to the binary created when the generated C code is compiled to machine code.

```
(c-option "-lglut -lGLU -lGL -L/usr/local/include/")

```

The example above is from the beginning of the OpenGL library code.
