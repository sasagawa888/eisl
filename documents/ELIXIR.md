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

(defpattern fib
    (0 1)
    (1 1)
    (_n (+ (fib (- _n 1)) (fib (- _n 2)))))

> (fib 20)
10946
> 
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

variable e.g. _a _z 
variable symbol has prifix "_"

:rest or &rest match rest parameter

else symbol match every argument 

e.g. 

(defpattern boo
    ((* (* _a _b) _c) (list _a _b _c))
    ((e 1 :rest _a) (list _a))
    (else 1))

> (boo '(e 1 2 3))
((2 3))
> (boo 3)
1
> 

(defpattern talk
    ((I love _a) (list _a 'love 'me))
    ((hello _a) (list 'good-bye _a))
    (else (list 'I 'do 'not 'know)))

> (talk '(I love hanako))
(HANAKO LOVE ME)
> (talk '(hello world))
(GOOD-BYE WORLD)
> (talk 10)
(I DO NOT KNOW)
> 

(defpattern sum
    (nil 0)
    ((_a :rest _b) (+ _a (sum _b))))

> (sum '(1 2 3))
6
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

pattern

variable e.g. _a _z 
variable symbol has prifix "_"

:rest or &rest match rest parameter

else symbol match every argument 

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
