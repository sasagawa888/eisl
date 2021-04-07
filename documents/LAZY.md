# Lazy
  Lazy evalution 

  written by M.Hiroi

# Usage 
  (import "lazy")

# Example1

> (import "lazy")
T
> (defglobal a (delay (+ 10 20)))
A
> a
<function>
> (force a)
30
> (defglobal b (delay (progn (print "oops!") (+ 10 20))))
B
> (force b)
"oops!"
30
> (force b)
30
> 

# Example2

```
(import "lazy")

(defun intgen (low high)
  (if (> low high)
      nil
    (stream-cons low (intgen (+ low 1) high))))

```

```
> (defglobal s (intgen 1 4))
S
> (stream-car s)
1
> (setq s (stream-cdr s))
(2 . <function>)
> (setq s (stream-cdr s))
(3 . <function>)
> (setq s (stream-cdr s))
(4 . <function>)
> (setq s (stream-cdr s))
NIL
> 

```