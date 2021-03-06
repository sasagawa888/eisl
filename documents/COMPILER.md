# Compiler

I developed a compiler for Easy-ISLisp (called the "FAST" project).
I released it in August 2017.
Here I describe the specifications, constraints, problems, etc. 

# Basic idea

I referred to GCL (GNU Common Lisp) created by Mr. Hagiya, Mr. Yuasa and others.
The Easy-ISLisp(EISL) compiler converts ISLisp code to equivalent C code and GCC generates an object file.
By dynamically linking an object file, EISL loads the compiled code.
The internal definitions of functions use GCC/clang extensions.
Therefore, the scope of labels and flet syntax is limited. 

# Usage
EISL starts compiling with (compile-file filename).
The filename is given as a string. The compile-file function creates a C file based on a Lisp file.
It also launches GCC/clang and creates a shared object.
EISL loads it with the load function like a normal text Lisp file.
If the file extension is ".o", the load function handles dynamic linking.

# Immediate value of small integer
The interpreter of EISL created cell objects for everything, including small integers.
For this reason, GC starts soon and it was difficult to speed up.
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
| (self-introduction)       | Returns the symbol depending the kind of OS                                                              |
|                           | Because the compiler changes its behavior depending on the type of OS.                                   |
| (get-method x)            | Get all methods of the generic function with name x. |
| (get-method-body x)       | Get the entity of method x. |
| (get-method-priority x)   | Gets the priority of method x. |
|                           | It is an integer value and looks like this: |
|                           | AROUND 11 |
|                           | BEFORE 12 |
|                           | PRIORITY 13 |
|                           | AFTER 14 |

These are used to compile generic functions.
The interpreter evaluates the generic function once organizes and saves all methods,
and compiler extracts methods and converts it to SUBR.

```lisp
(format stream string)
```
It has its own behavior when there are two single quotes in a string.
Ignores special character controls such as ~% for strings between consecutive single quotes.
Also, two consecutive single quotes are converted to one double quote.
This is necessary because it converts Lisp code to C code, pools it in a string stream, and finally outputs it to a file. 

```
> (format (standard-output) "''hello~% world~A ''")
"hello~% world~A "NIL
> 
```

# Constraints of labels and flet
In C language, it is not possible to define a local function inside a function. 
GCC makes this possible with extensions. I used this extension to gain speed while ensuring static scope operation. 
However, the scope is different from that of Lisp. 

# Implementation of lambda
lambda is originally an anonymous function, but I dared to name it to make it a C function.
The name is the file name of compile-file + natural number.
Free variables must be retained for static scope.
This was inspired by the GCL method. 
A list of free variables that must be retained is linked to the function name symbol of lambda. 
When accessing with the lambda body, it is done with nth function. 


# Constraints of lambda
You can nest lambda expressions up to triple.
Any more than that will result in an error.

Below is the quoted code from M.Hiroi's page.
This is the correct code that adapts the ISLisp specification. 

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
lambda is generated as a C function with a name at the top level. 
The locally defined function dfs function is called in lambda.
The dfs function generated as a C local definition function cannot be referenced from the C function corresponding to the generated lambda.

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

# Constraints on generic functions

Below is the quoted code from M. Hiroi's page.
This is the correct code that adapts the ISLisp specification. 

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
I think it can be done by α conversion, but I decided to do it easily. It should be written as follows. 

```lisp
(defgeneric hash-func (k))

(defmethod hash-func ((k <string>))
  (for ((i 0 (+ i 1))
        (a 0))
       ((>= i (length k)) a)
       (setq a (+ (* a 8) (convert (elt k i) <integer>))

```

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
| (c-include x)  | Insert #include. e.g. (c-include "stdio.h")            |
| (c-define x y) | Insert #define. e.g. (c-define "MAXINT" "999999999")   |
| (c-lang x)     | Insert a c language source. e.g. (c-lang "a = a + 1;") |
| (c-option x)   | Add a compile option. e.g. (c-option "-lwinmm")        |

These functions are ignored by the interpreter. 

# Further explanation

* All variables have been converted to uppercase. Therefore, the n and m variables are N and M in C language.
* Small integers are immediate values for efficiency.
  By setting the second bit from the most significant bit, it is internally recognized as a small integer.
  When using C operators wi must remove this bit. By operation AND with INT_MASK, this bit is removed.
  When the operation in C is completed, it must be returned to the immediate value. 
  By openration OR with INT_FLAG, the second bit is 1. 
  the values INT_MASK and INT_FLAG are described in fast.h.
* The return value of an S-expression is held by a variable "res" in C language.
  We assign a value to res. 

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

EISL compiler has a type inferencer. This was introduced experimentally in ver0.85.

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
Even if you use type inference, it  can only infer that the argument and return value are integers. This is the limitation of type inferencer.
Since the Takeuchi function requires a huge amount of recursive calculation.
It can be calculated within practical time only when the argument is a small integer.
Therefore, you can generate efficient code by telling the compiler that compiler should generate code for small integers and not consider that it will become BIGNUM. 
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
However, I think that the limit of calculation on a personal computer within practical time is about ack(4,1). 
In this case, the calculation is possible within small integer. 
This is also possible by adding type information using "the" syntax. 

```
(defun ack (m n)
  (the <fixnum> m)(the <fixnum> n)
  (cond ((= m 0)(+ n 1))
        ((= n 0)(ack (- m 1) 1))
        (t (ack (- m 1) (ack m (- n 1))))))

```

### ex4
The Fibonacci number is an integer, but it is an example of calculating with a floating point number.
Type inferencer predicts that the arguments and return values are floating point numbers from constants such as 1.0.
The compiler produces code that is specific to floating point numbers.
No additional information about the type is needed in this case. 

```
(defun fib* (n)
  (cond ((= n 1.0) 1.0)
        ((= n 2.0) 1.0)
        (t (+ (fib* (- n 1.0)) (fib* (- n 2.0))))))
```

# Benchmark

Performance was compared to SBCL, which is a popular Common Lisp compiler.
SBCL has a type declaration to speed it up.

### ex1 
Takeuchi function

```
SBCL
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


EISL
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

```
SBCL
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

EISL
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

```
SBCL
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

EISL
> (fib* 40.0)
102334155.0
> (time (fib* 40.0))
Elapsed Time(second)=0.479320
<undef>
> 
```
