# Compiler

I developed a compiler for Easy-ISLisp (called the "FAST" project).
I released it in August 2017.
Here I describe the specifications, constraints, problems, etc. 

# Basic idea

I referred to GCL (GNU Common Lisp) created by Mr. Hagiya, Mr. Yuasa and others.
The Easy-ISLisp (EISL) compiler converts ISLisp code to equivalent C code and gcc or clang generate an object file.
By dynamically linking this object file, EISL loads the compiled code.
The internal definitions of functions use GCC/clang extensions.
Therefore, the scope of labels and flet syntax is limited. 

# Usage
EISL starts compiling with (compile-file filename).
The filename is given as a string. The compile-file function creates a C file based on a Lisp file.
It also launches GCC/clang and creates a shared object.
EISL loads this with the load function like a normal text Lisp file.
If the file extension is ".o", the load function handles dynamic linking.

### option
- (compile-file filename nil)
for debug. not remove compiled C codes.

- (compmile-file filename t)
for installer. remove compiled C codes with sudo command.

# Immediate value of small integer
The interpreter of EISL created cell objects for everything, including small integers.
For this reason, GC started soon and it was difficult to speed up.
The compiler instantiates integers from -999999999 to 999999999 to prevent cell consumption.
As a result, the calculation of the Takeuchi function and the Fibonacci sequence can be considerably speeded up. 

```
> (load "tarai.o")
T
> (time (tarai 12 6 0))
Elapsed Time(second)=0.068000
<undef>
> (time (fib 40))
Elapsed Time(second)=1.194000
<undef>
> 
```

# Tail recursive optimization
The ISLisp standard does not require tail-recursive optimization.
However, like Scheme, EISL generates code that replaces tail recursion with repetition. 
It doesn't consume the stack in following code, and it's reasonably fast. 

```
(defun foo (n)
  (if (= n 0)
      t
      (foo (- n 1))))

> (load "test.o")
T
> (foo 1000000000)
T
> (time (foo 1000000000))
Elapsed Time(second)=1.789000
<undef>
> 
```

# Extensions for the compiler

The following non-standard functions have been implemented for use by the compiler:

| Function                  | Description |
| ------------------------- | ----------- |
| (subrp x)                 | t if x is a built-in function, nil otherwise                                                             |
| (macrop x)                | t if x is a macro, nil otherwise                                                                         |
| (system str)              | Str Executes the string on the OS. This is for starting GCC.                                             |
| (freedll)                 | Unlinks the last dynamically linked file.                                                                |
| (fixnump x)               | t for small integers, nil otherwise                                                                      |
| (longnump x)              | t for LONGNUM, nil otherwise |
| (bignump x)               | t for BIGNUM, nil otherwise |
| (readed-array-list x)     | Convert an array of constants like # 2a((1 2) (3 4)) to a list ((1 2) (3 4)). |
| (ignore-toplevel-check x) | Passing t as an argument removes top-level checks such as defclass, and passing nil restores and checks. |
| (self-introduction)       | Returns the symbol depending the kind of OS, because the compiler changes its behavior depending on the type of OS. |
| (macroexpand-1 x)         | Expand macro once. |
| (macrexpand-all x)        | Expand macro all. |
| (get-method x)            | Get all methods of the generic function with name x. |
| (get-method-body x)       | Get the entity of method x. |
| (get-method-priority x)   | Gets the priority of method x. This is an integer value and one of AROUND=11, BEFORE=12, PRIORITY=13, AFTER=14. |

These are used to compile generic functions.
The interpreter evaluates the generic function once organizes and saves all methods,
and compiler extracts methods and converts it to SUBR.

```lisp
(format stream string)
```
has extended behavior when there are two single quotes in a string.
Special character controls such as ~% between consecutive single quotes are ignored.
Also, two consecutive single quotes are converted to one double quote.
This is useful for converting Lisp code to C code by pooling into a string stream and outputting to a file. 

```
> (format (standard-output) "''hello~% world~A ''")
"hello~% world~A "NIL
> 
```

# Implementation of lambda
`lambda` is supposed to define an anonymous function, but C functions must have a name.
The name is the file name supplied to compile-file + a natural number.
Free variables must be retained for static scope.
This was inspired by the GCL method.
A list of free variables that must be retained is linked to the function name symbol of lambda. 
Access from the lambda body, is done with the `nth` function.

# Constraints of lambda
You can nest lambda expressions up to three deep.
Any more than that will result in an error.

Below is the quoted code from M.Hiroi's page.
This is correct code that conforms to the ISLisp specification. 

```lisp
(defun id-search (start goal)
  (labels ((dfs (limit path)
             (if (= limit (length path))
                 (if (eq (car path) goal)
                     (print (reverse path)))
               (for-each
                (lambda (x)
                  (if (not (member x path))
                      (dfs limit (cons x path))))
                (cdr (assoc (car path) adjacent))))))
    (for ((limit 1 (+ limit 1)))
         ((= limit 7))
         (format (standard-output) "----- ~D -----~%" limit)
         (dfs limit (list start)))))
```

The EISL compiler cannot compile this code.
`lambda` generates a C function with a name at the top level.
The locally defined function `dfs` function is called from the lambda.
The `dfs` function generated as a C local definition function cannot be referenced from the C function corresponding to the generated lambda.

Therefore, in such a case, please write without using labels as shown below. 

```lisp
(defun id-search (start goal)
  (for ((limit 1 (+ limit 1)))
       ((= limit 7))
       (format (standard-output) "----- ~D -----~%" limit)
       (dfs limit (list start))))

(defun dfs (limit path)
  (if (= limit (length path))
      (if (eq (car path) goal)
          (print (reverse path)))
      (for-each
        (lambda (x)
          (if (not (member x path))
              (dfs limit (cons x path))))
        (cdr (assoc (car path) adjacent)))))
```

# Constraint on generic functions
### This constraint has been removed from ver2.0. 

Below is the quoted code from M. Hiroi's page.
This is correct code that conforms to the ISLisp specification. 

```lisp
(defgeneric hash-func (k))

(defmethod hash-func ((s <string>))
  (for ((i 0 (+ i 1))
        (a 0))
       ((>= i (length s)) a)
       (setq a (+ (* a 8) (convert (elt s i) <integer>)))))
```

In the method definition, the argument name must work correctly even if you give it a different name in the generic function.
The interpreter evaluates this correctly.
But the compiler has the restriction that the argument names must be the same for simplicity.
I think it can be done by α conversion, but I decided to take a short-cut. It should be written as follows. 

```lisp
(defgeneric hash-func (k))

(defmethod hash-func ((k <string>))
  (for ((i 0 (+ i 1))
        (a 0))
       ((>= i (length k)) a)
       (setq a (+ (* a 8) (convert (elt k i) <integer>))

```

# Constraint on tag of catch,throw
The catch tag is supposed to be evaluated dynamically. The interpreter evaluates dynamically. However, it is difficult for the compiler to dynamically evaluate tags. In the compiler, it is limited to symbols with quotes.


# Constraint on tag of block,return-from
The block tag must be different from function name. If use same symbol, compiled code may occur segmentation fault.

# Some More Limitations

There are a few tickets that were logged for compiler limitations, but the outcome was that it was better to have such a limitation and a simpler system.
In particular:

* Issue #121. Memory consumption is significant, but modern computers can afford it. This was trying to figure out what the lower limit was. From cursory testing, a heap size of 5M (rather than the default 20M) cells was enough to run the benchmark suite at least. This is configured by `CELLSIZE` in *ffi.h*. However, reducing this could lead to weird failures. Using the "DEBUG=1" build might help debug these quicker.
* Issue #123. The compiler is not able to handle some of subtleties of generic functions. It may be simpler to rely on functional interfaces to compiled code and have a Lispier interface in an interpreted file (e.g. the split between *ndbm.lsp* and *persist.lsp*).

None of this should take away from the compiler's usefulness.
For some applications, it may even be more useful to gain access to C libraries rather than any speed-up.

# Calling C from Lisp

This is only possible in compiled code.
EISL extends the ISLisp standard to allow insertion of C statements into the compiler output.
In this way you can use the many libraries that present a C interface.
Below is a simple sample. 

```
(c-include "<stdio.h>")

(defun 1+ (n)
  (c-lang "res=N+1"))

> (compile-file "test.lsp")
initialize
pass1
pass2
compiling 1+ 
finalize
invoke GCC
T
> (load "test.o")
T
> (1+ 3)
4
> 
```

In this way, the description in C can be mixed.
You can use this to call the Wiring PI of Raspberry Pi or write a function that calls socket as a Lisp function.
It does not rely on CFFI, so it can be easily linked to C.

The prepared functions are as follows.

| Function       | Description                                            |
| -------------- | ------------------------------------------------------ |
| (c-include x [platform])  | Insert #include. e.g. (c-include "stdio.h"). Optional `platform` only inserts for a particular platform. |
| (c-define x y) | Insert #define. e.g. (c-define "MAXINT" "999999999")   |
| (c-lang x)     | Insert a c language source. e.g. (c-lang "a = a + 1;") |
| (c-option x [platform])   | Add a compile option. e.g. (c-option "-lwinmm"). Optional `platform` only adds for a particular platform. |
| (c-return class) | By appending it at the end of a defun, you indicate to the type inference system the class of the result returned by a function implemented in C.  e.g. (c-return <string>)|

`platform` above is an unquoted bareword linux, macos or openbsd.
It does not have be quoted.

These functions are ignored by the interpreter. 

# Further explanation

* All variable names are converted to uppercase. Therefore, the n and m variables are N and M in C code.
* Small integers are immediate values for efficiency.
  Setting the second from most significant bit internally tags a value as a small integer.
  In C code we must remove this bit using bitwise `& INT_MASK`.
  When the C code is completed, you can return an immediate value
  using bitwise `| INT_FLAG` which sets the second from most significant bit to 1.
  The values INT_MASK and INT_FLAG are defined in fast.h.
* The return value of an S-expression is a variable "res" in C.
  A value should be assigned to res.

e.g. 

```lisp
(c-include "<stdio.h>")

(defun ash (n m)
  (if (>= m 0)
      (c-lang "res = INT_FLAG | ((INT_MASK & N) << (INT_MASK & M));")
      (let ((m1 (- m)))
        (c-lang "res = INT_FLAG | ((INT_MASK & N) >> (INT_MASK & M1));"))))
```

