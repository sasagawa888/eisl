# Pipe
Elixir like pipe operator 

# Usage
Compile the library pipe.lsp before if you need speed. 

```
(import "pipe")
```

# Example

```
(import "pipe")

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

# Specification
pipe is described by macro. The above example expands to the following function: 

```
(pipe x |> (foo 1) |> (bar 2) |> (boo 3)))

(boo (bar (foo 1) 2) 3)

```

The first argument receives the result of the previous calculation. 
