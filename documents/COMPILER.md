# Compiler
I was developing a compiler for Easy-ISLisp (I called it "FAST" project).
I have released it in August 2017. 
I write down the specifications, problems, etc. 

# Basic idea
I refer to GCL created by Mr. Hagiya etc.
The compiler converts ISLisp code to equivalent C code and GCC generates an object file.
By dynamically linking object file, Easy-ISLisp(EISL) loads the compiled code.
The internal definition of the function uses GCC extensions.
Therefore, the scope of labels and flet syntax is limited. 

# Usage
EISL starts compiling with (compile-file filename).
The filename is given as a string. The compile-file function creates a C file based on a Lisp file.
It also launches GCC and creates a dynamic link object.
EISL loads it with the load function like a normal text Lisp file.
If the identifier is o, the load function handles dynamic linking. 

# Immediate value of small integer
The interpreter of EISL created cell objects for everything, including small integers.
For this reason, GC started immediately and it was difficult to speed up.
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
It doesn't consume the stack if it's next to it, and it's reasonably fast. 

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
The following functions have been uniquely extended for the compiler.

```
(subrp x) t if x is a built-in function, nil otherwise
(macrop x) t if x is a macro, nil otherwise
(system str) Str Executes the string on the OS. To start GCC
(freedll) Unlinks the last dynamically linked file.
(fixnump x) t for small integers, nil otherwise
(longnump x) t for LONGNUM, nil otherwise
(bignump x) t for BIGNUM, nil otherwise
(readed-array-list x) Convert an array of constants like # 2a ((1 2) (3 4)) to a list ((1 2) (3 4)).
(ignore-toplevel-check x) Passing t as an argument removes top-level checks such as defclass, and passing nil restores and checks.
(self-introduction) Returns the linux symbol for Linux and the windows symbol for Windows.
Because the compiler changes its behavior depending on the type of OS.

(get-method x) Get all methods of the inclusive function with name x.
(get-method-body x) Get the entity of method x.
(get-method-priority x) Gets the priority of method x.
It is an integer value and looks like this:
AROUND 11
BEFORE 12
PRIORITY 13
AFTER 14
```

These are used to compile generic functions.
The interpreter evaluates the gemeric function once organizes and saves all methods,
and compiler extracts methods and converts it to SUBR.

(format stream string)
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


# lambda constraints
You can nest lambda expressions up to triple.
Any more than that will result in an error.

Below is the quoted code from M.Hiroi's page.
This is the correct code that meets the ISLisp specification. 

```
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

The EISL compiler cannot compile this.
lambda is generated as a C function with a name at the top level. 
The locally defined function dfs is called in lambda.
The dfs generated as a C local definition function cannot be referenced from the C function corresponding to the generated lambda.

Therefore, in such a case, please write without using labels as shown below. 

```
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

# Constraints of generic function
Below is the quoted code from M. Hiroi's page.
This is the correct code that adapted the ISLisp specification. 

```
(defgeneric hash-func (k))

(defmethod hash-func ((s <string>))
  (for ((i 0 (+ i 1))
        (a 0))
       ((>= i (length s)) a)
       (setq a (+ (* a 8) (convert (elt s i) <integer>)))))
```

In the method definition, the argument name must work correctly even if you give it a different name intthe generic function.
The interpreter evaluates exactly that. 
But, the compiler has the restriction that the argument names must be the same for simplicity.
I think it can be done by α conversion, but I decided to do it easily. It should be written as follows. 

```
(defgeneric hash-func (k))

(defmethod hash-func ((k <string>))
  (for ((i 0 (+ i 1))
        (a 0))
       ((>= i (length k)) a)
       (setq a (+ (* a 8) (convert (elt k i) <integer>))

```

# Mixed with C language source
To insert C language source in the function,EISL is extended.
This is because you can easily use GCC's rich library from ISLisp.
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

```
(c-include x) Insert #include. e.g. (c-include "stdio.h")
(c-define x y) Insert #define. e.g. (c-define "MAXINT" "999999999")
(c-lang x) Insert a c language source. e.g. (c-lang "a = a + 1;")
(c-option x) Add a compile option. e.g. (c-option "-lwinmm")
```
These functions are ignored by the interpreter. 

