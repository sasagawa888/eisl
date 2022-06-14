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

# Constraints of labels and flet
In C language, it is not possible to define a local function inside a function. 
GCC makes this possible with extensions. I used this extension to gain speed while ensuring static scope operation. 
However, the scope is different from that of Lisp. 
Note that clang does not support this feature at all.

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

# Constraint on tag of catch
The catch tag is supposed to be evaluated dynamically. The interpreter evaluates dynamically. However, it is difficult for the compiler to dynamically evaluate tags. In the compiler, it is limited to symbols with quotes.


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

# Type inference

The EISL compiler has a type inferencer. This was introduced experimentally in ver0.85.

# Examples

### ex1

In this example, the function foo gives a number to length, which causes an error at runtime.
This is checked by type inference and a warning message is issued.
The code is generated because it can be compiled.

```
(defun foo (x)
  (length (+ x 1)))

> (compile-file "tarai.lsp" 'type)
initialize
pass1
inferencing FOO
("subr type mismatch" ((LENGTH (+ X 1))))
pass2
compiling FOO 
finalize
invoke GCC
T
> 
```

### ex2
Takeuchi function code. 
Even if you use type inference, it  can only infer that the argument and return value are integers. This is a limitation of the type inferencer.
Since the Takeuchi function requires a huge amount of recursive calculation
it can be calculated in a  practical time only when the argument is a small integer.
Therefore, you can generate efficient code by telling the compiler that compiler should generate code for small integers and not consider that it will become a BIGNUM. 
"the" syntax has no effect on the interpreter, but the compiler executes type inferences based on this additional data. 

```
(defun tarai(x y z)
  (the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
  (if (<= x y)
      y
      (tarai (tarai (- x 1) y z)
             (tarai (- y 1) z x)
             (tarai (- z 1) x y))))

> (compile-file "tarai.lsp" 'type)
initialize
pass1
inferencing TARAI
pass2
compiling TARAI 
finalize
invoke GCC
T
> 

```

### ex3
The Ackermann function also requires a huge amount of recursive calculations and produces large numbers.
However, I think that the limit of calculation on a personal computer within practical time is about ack(4, 1). 
In this case, the calculation is possible within the small integer range.
Specifying this is also possible by adding type information using "the" syntax. 

```lisp
(defun ack (m n)
  (the <fixnum> m)(the <fixnum> n)
  (cond ((= m 0)(+ n 1))
        ((= n 0)(ack (- m 1) 1))
        (t (ack (- m 1) (ack m (- n 1))))))

```

### ex4
The Fibonacci number is an integer, but here is an example of calculating with a floating point number.
The type inferencer predicts that the arguments and return values are floating point numbers from constants such as 1.0.
The compiler produces code that is specific to floating point numbers.
No additional information about types is needed in this case.

```lisp
(defun fib* (n)
  (cond ((= n 1.0) 1.0)
        ((= n 2.0) 1.0)
        (t (+ (fib* (- n 1.0)) (fib* (- n 2.0))))))
```

# Benchmark

Performance was compared to SBCL, which is a popular Common Lisp compiler.
SBCL processes type declarations to speed it up.

### ex1 
Takeuchi function

#### SBCL

```
(declaim (ftype (function (fixnum fixnum fixnum) fixnum) tarai))
(defun tarai(x y z)
  (declare (optimize (speed 3) (debug 0) (safety 0))
    (type fixnum x)(type fixnum y)(type fixnum z))
  (if (<= x y)
      y
      (tarai (tarai (- x 1) y z)
             (tarai (- y 1) z x)
             (tarai (- z 1) x y))))

* (time (tarai 12 6 0))

Evaluation took:
  0.028 seconds of real time
  0.031250 seconds of total run time (0.031250 user, 0.000000 system)
  110.71% CPU
  79,247,451 processor cycles
  0 bytes consed

12
```

#### EISL

```
> (load "tarai.o")
T
> (tarai 12 6 0)
12
> (time (tarai 12 6 0))
Elapsed Time(second)=0.019982
<undef>
> 
```

### ex2
Ackermann function

#### SBCL

```
(declaim (ftype (function (fixnum fixnum) fixnum) ack))
(defun ack (m n)
  (declare (optimize (speed 3) (debug 0) (safety 0))
    (type fixnum m)(type fixnum n))
  (cond ((= m 0)(+ n 1))
        ((= n 0)(ack (- m 1) 1))
        (t (ack (- m 1) (ack m (- n 1))))))


* (time (ack 4 1))

Evaluation took:
  4.558 seconds of real time
  4.531250 seconds of total run time (4.531250 user, 0.000000 system)
  99.41% CPU
  14,552,407,668 processor cycles
  0 bytes consed

65533
* 
```

#### EISL

```
> (load "tarai.o")
T
> (ack 4 1)
65533
> (time (ack 4 1))
Elapsed Time(second)=2.382881
<undef>
> 
```

### ex3
Fibonacci function (float number)

#### SBCL

```
(declaim (ftype (function (float) float) fib*))
(defun fib* (n)
  (declare (optimize (speed 3) (debug 0) (safety 0)) (type float n))
  (if (< n 2.0)
    n
    (+ (fib* (- n 2.0)) (fib* (- n 1.0)))))

* (time (fib* 40.0))

Evaluation took:
  6.479 seconds of real time
  6.468750 seconds of total run time (6.406250 user, 0.062500 system)
  [ Run times consist of 0.156 seconds GC time, and 6.313 seconds non-GC time. ]
  99.85% CPU
  20,682,846,107 processor cycles
  3,973,926,912 bytes consed

1.0233415e8
* 
```

#### EISL

```
> (fib* 40.0)
102334155.0
> (time (fib* 40.0))
Elapsed Time(second)=0.479320
<undef>
> 
```
