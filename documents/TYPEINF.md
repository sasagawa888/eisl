# Type Inference
The compiler also includes a type inference feature. This document describes the specifications of the type inference.

# Type Inference in Lisp
Lisp is a dynamically typed language, which allows you to write code with ease. However, this also means that mistakes in the code may not be detected until runtime. Type inference predicts types without requiring explicit type declarations, similar to statically typed languages, and can detect inconsistencies. Additionally, it can sometimes lead to the generation of more efficient code

# Concrete Example
The following code contains a type inconsistency. The length function can only accept lists, strings, or vectors. On the other hand, the same variable x is passed to append, which can only accept lists.

```lisp
(defun test1 (x)
  (length x)
  (append x "asdf"))

```
When compiled, the type inference engine is activated to deduce types. It identifies inconsistencies and displays warnings.

```
> (compile-file "./tests/infer.lsp")
type inference
warning TEST1 subr type mismatch (APPEND X "asdf")
initialize
pass1
pass2
compiling TEST1 
finalize
invoke CC
T
> 

```

# Optimization
The following code is the Takeuchi function. Since there are no logical inconsistencies, the type inference engine does not issue any warnings.

```lisp
(defun tarai (x y z)
    (if (<= x y)
        y
          (tarai (tarai (- x 1) y z)
                 (tarai (- y 1) z x)
                 (tarai (- z 1) x y))))

```
The Takeuchi function performs an extremely large number of recursive calculations, so its practical computable range is limited to small integers. However, the compiler cannot determine this analytically. Therefore, type information can be added as follows.

```lisp
(defun tarai (x y z)
    (the <fixnum> x)(the <fixnum> y)(the <fixnum> z)
    (if (<= x y)
        y
          (tarai (tarai (- x 1) y z)
                 (tarai (- y 1) z x)
                 (tarai (- z 1) x y))))

```

# Benchmark

Performance was compared to SBCL, which is a popular Common Lisp compiler.
SBCL processes type declarations to speed it up.

```lisp
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

```lisp
> (load "./tests/infer.o")
T
> (time (tarai 12 6 0))
Elapsed Time(second)=0.031228
<undef>
> 
```

# In the Case of C Language Embedding
Using c-lang, it is possible to embed C code within function definitions. In this case, type information for the output can be provided. This allows type inference to be performed even for functions that include embedded C code.

```lisp
(defun baz ()
    (c-lang "res = Fmakeint(2);")
    (c-return <fixnum>))

(defun uoo (x)
    (append x (baz)))

> (compile-file "./tests/infer.lsp")
type inference
warning UOO subr type mismatch (APPEND X (BAZ))
initialize
pass1
pass2
compiling BAZ 
compiling UOO 
finalize
invoke CC
T

```