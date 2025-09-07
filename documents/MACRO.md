# Macro
Common-Lisp like convenient macro library,
written by M.Hiroi.

# Acknowledgement
Thanks to Mr. Hiroi.

# Macros

```lisp
(when test body)
(unless test body)
(prog1 body)
(prog2 body)
(incf place [delta])
(decf place [delta])
(push item place)
(push-end item place)
(pop place)
(loop body ...)
(return result)
(dotimes (var limit [result]) body ...)
(dolist (var init-form [result]) body ...)
```

# Usage
If you need speed, compile first. 

```lisp
make lisp

(import "compiler")
```

```
> (import "macro")
T

>(when (< 1 2) 1 2 3 4 5)
5
>(when (> 1 2) 1 2 3 4 5)
NIL
>(unless (< 1 2) 1 2 3 4 5)
NIL
>(unless (> 1 2) 1 2 3 4 5)
5
>(prog1 1 2 3 4 5)
1
>(prog2 1 2 3 4 5)
2
>(defglobal a '(1 2 3 4 5))
A
>(prog1 (car a) (setq a (cdr a)))
1
>a
(2 3 4 5)

>(defglobal a 10)
A
>(incf a)
11
>a
11
>(decf a)
10
>a
10
>(incf a 10)
20
>(decf a (+ 1 2 3))
14

>(defglobal b '(1 2 3 4 5))
B
>(incf (car b))
2
>b
(2 2 3 4 5)
>(decf (car (cdr (cdr b))))
2
>b
(2 2 2 4 5)
>(defglobal c #(1 2 3 4 5))
C
>(incf (aref c 4))
6
>c
#(1 2 3 4 6)
>(decf (elt c 1))
1
>c
#(1 1 3 4 6)


>(defglobal xs nil)
XS
>(push 1 xs)
(1)
>(push 2 xs)
(2 1)
>(push 3 xs)
(3 2 1)
>(pop xs)
3
>xs
(2 1)
>(pop xs)
2
>xs
(1)
>(pop xs)
1
>xs
NIL

>(defglobal ys '(nil nil nil))
YS
>(push 1 (car ys))
(1)
>ys
((1) NIL NIL)
>(push 2 (car (cdr (cdr ys))))
(2)
>ys
((1) NIL (2))
>(pop (car (cdr (cdr ys))))
2
>ys
((1) NIL NIL)
>(pop (car ys))
1
>ys
(NIL NIL NIL)

>(defun display (x) (format (standard-output) "~A~%" x))
DISPLAY
>(let ((x 0)) (loop (display x) (if (< 5 x) (return) (incf x))))
0
1
2
3
4
5
6
NIL
>(let ((x 0)) (loop (display x) (if (< 5 x) (return 'oops) (incf x))))
0
1
2
3
4
5
6
OOPS

>(dotimes (x 5) (display x))
0
1
2
3
4
NIL
>(dotimes (x 5 'oops) (display x))
0
1
2
3
4
OOPS
>(dotimes (x 5 'oops) (display x) (if (< 2 x) (return)))
0
1
2
3
NIL
>(dotimes (x 5 'oops) (display x) (if (< 2 x) (return 'oops1)))
0
1
2
3
OOPS1
>(dolist (x '(1 2 3 4 5)) (display x))
1
2
3
4
5
NIL
>(dolist (x '(1 2 3 4 5) 'oops) (display x))
1
2
3
4
5
OOPS
>(dolist (x '(1 2 3 4 5) 'oops) (display x) (if (< 2 x) (return)))
1
2
3
NIL
>(dolist (x '(1 2 3 4 5) 'oops) (display x) (if (< 2 x) (return 'oops2)))
1
2
3
OOPS2
```
