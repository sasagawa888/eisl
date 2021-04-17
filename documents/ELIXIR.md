# Elixir
Elixir like syntax extension 

# Usage
Compile the library elixir.lsp before if you need speed. 

```
(import "elixir")
```

# Example

## Pattern match 

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
pipe is described by macro. The above example expands to the following function: 

```
(pipe x |> (foo 1) |> (bar 2) |> (boo 3)))

(boo (bar (foo x 1) 2) 3)

```

The first argument receives the result of the previous calculation. 
