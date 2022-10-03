# Elixir
Elixir-like syntax extension.

# Usage
Compile the library elixir.lsp beforehand if you need speed.

```lisp
(import "elixir")
```

# Example

## Pattern matching

```
(import "elixir")

(defpattern deriv
    (((^ _x _n) _x) `(* ,_n (^ ,_x ,(- _n 1)))))

> (deriv '(^ x 3) 'x)
(* 3 (^ X 2))
> 

(defpattern fib
    ((0) 1)
    ((1) 1)
    ((_n) (+ (fib (- _n 1)) (fib (- _n 2)))))

> (fib 20)
10946
> 

(defpattern sum
    ((empty) 0)
    (((_a :rest _b)) (+ _a (sum _b))))

> (sum '(1 2 3))
6

```

## Specification

```
(defpattern fname
   case1
   case2
   ...
   casen)

case
  (pattern sexp1 sexp2 ... sexpn)

pattern
(arg1 arg2 ... argn)

argument
variable e.g. _a _z 
variable symbol has prifix "_"

anonymous
_ means anonymous variable. It matches any element.

:rest or &rest match rest parameter

else symbol match every argument 
empty symbol match '() (empty-list) 

e.g. 


(defpattern talk
    (((I love _a)) (list _a 'love 'me))
    (((hello _a)) (list 'good-bye _a))
    (else (list 'I 'do 'not 'know)))

> (talk '(I love hanako))
(HANAKO LOVE ME)
> (talk '(hello world))
(GOOD-BYE WORLD)
> (talk 10)
(I DO NOT KNOW)
> 

(element var elt1 elt2 ... eltn) 
when elt1 ... eltn are element , match and bind var the argument.

elt is simple symbol and (n symbol).

e.g.

> (defpattern foo (((element _x a b)) _x) (else 'no))
FOO
> (foo '(a b c))
(A B C)
> (foo '(a  c))
NO
> 

in body part you can use modify function
(modify var elt1 elt2 ... eltn)

e.g.
> (modify '(a b c) '(- a))
(B C)
> (modify '(a b c) '(+ a))
(A A B C)
> (modify '(a b b c) '(- (2 b)))
(A C)
> 

```

## Match syntax

```
(match x
    case1
    ...
    casen)

case
  (pattern sexp1 sexp2 ... sexpn)
  or
  (parren when sexp1 sexp3 ... sexpn)

pattern

variable e.g. _a _z 
variable symbol has prifix "_"

anoymous e.g. _
anoymous matches every argument.

:rest or &rest match rest parameter

else symbol matches every argument 

when
Add constraints for each element.
e.g. _k must be an integer 
(((+ 1 _k _l)) (when (integerp _k)(floatp _l)) ...)
see example/derive.lsp

e.g.    
(defun uoo (x y)
    (match x
        (nil y)
        ((0 :rest _x) (uoo _x (+ y 1)))
        ((1 :rest _x) (uoo _x (+ y 2)))))

> (uoo '(0 1 0 1 0 0) 0)
8
> 
```

## Pipe operator

```
(import "elixir")

(defun foo (x y)
    (+ x y) )

(defun bar (x y)
    (* x y) )

(defun boo (x y)
    (- x y) )

(defun uoo (x)
    (pipe x |> (foo 1) |> (bar 2) |> (boo 3)))

> (uoo 3)
5
> 
```

## Specification
pipe is defined by a macro. The above example expands to the following function:

```
(pipe x |> (foo 1) |> (bar 2) |> (boo 3)))

(boo (bar (foo x 1) 2) 3)
```

The first argument receives the result of the previous calculation. 
