# Interface between Lisp and C

## overview
Easy-ISLisp's compiler depends on how it translates Lisp code into C code.
You can embed C code in Lisp code. It allows you to call C code from Lisp.


## simple example
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
Embeds the string in str into the compiler-generated C code.

### immediate
Small integers in Easy-ISLisp are immediate values. This makes it possible to suppress the cell consumption of small integers. In order to import this small integer into C language, it is necessary to apply a mask.

```
INT_MASK & N
```

The arguments n and m of the ash function are converted to upper case. In C language, it is a variable called N. This variable is int type of C language. It is converted to an integer that can be handled in C language by taking the AND with INT_MASK.

```
INT_FLAG | ...

```
To convert a C integer to a Lisp number, OR it with INT_FLAG. As a result, the specified bit becomes 1 and can be treated as a small integer in Easy-ISLisp.

```
res = ...

```

The value of the function converted to C should be assigned to a C variable called res. This is the return value of the Lisp function.

## Other extension functions


### (c-include str)

```
;; example
(c-include "stdio.h")  

This is translated and embedded into the following C code:

```
#include stdio.h
```

### (c-option str)

This is in addition to the options you give to the C compiler.

```
(c-option "-lglut -lGLU -lGL -L/usr/local/include/")

```

The example above is from the beginning of the OpenGL library code.
