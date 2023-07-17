# Lazy

Lazy evalution,
written by M.Hiroi.

# Acknowledgement
Thanks to Mr. Hiroi.

# Usage 

```lisp
(import "lazy")
```

# Example 

```
> (import "lazy.lsp")
T
> (defglobal a (delay (progn (print "oops!") (+ 10 20))))
A
> a
<function>
> (force a)
"oops!"
30
> (force a)
30
> (setq a (lcons 1 (lcons 2 (lcons 3 nil))))
(1 . <function>)
> (lcar a)
1
> (lcar (lcdr a) )
2
> (lcar (lcdr (lcdr a)))
3
> (lcdr (lcdr (lcdr a)))
NIL
> (setq a (llist 1 2 3 4 5))
(1 . <function>)
> (tolist a)
(1 2 3 4 5)
> (setq a (fromlist '(1 2 3 4 5)))
(1 . <function>)
> (tolist a)
(1 2 3 4 5)
> (setq a (liota 1 10))
(1 . <function>)
> (tolist a)
(1 2 3 4 5 6 7 8 9 10)
> (setq a (ltabulate (lambda (x) (* x x)) 1 10))
(1 . <function>)
> (tolist a)
(1 4 9 16 25 36 49 64 81 100)
> (setq a (lunfold (lambda (x) (> x 10)) #'identity (lambda (x) (+ x 1)) 1))
(1 . <function>)
> (tolist a)
(1 2 3 4 5 6 7 8 9 10)
> (setq  a (lunfold (lambda (xs) (> (car xs) 3000000)) 
                    #'car
                    (lambda (xs) (cons (cdr xs) (+ (car xs) (cdr xs))))
                    '(0 . 1)))
(0 . <function>)
> (tolist a)
(0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181 6765 10946 17711 28657 
46368 75025 121393 196418 317811 514229 832040 1346269 2178309)
> (setq a (liota 1 nil))
(1 . <function>)
> (dotimes (x 10) (print (lnth x a)))
1
2
3
4
5
6
7
8
9
10
NIL
> (setq a (llist 1 2 3 4 5))
(1 . <function>)
> (llength a)
5
> (setq a (lappend (llist 1 2 3 4) (llist 5 6 7 8)))
(1 . <function>)
> (tolist a)
(1 2 3 4 5 6 7 8)
> (setq a (lappend-delay (llist 1 2 3 4) (delay (llist 5 6 7 8))))
(1 . <function>)
> (tolist a)
(1 2 3 4 5 6 7 8)
> (setq a (lzip (llist 1 2 3 4) (llist 5 6 7 8)))
((1 5) . <function>)
> (tolist a)
((1 5) (2 6) (3 7) (4 8))
> (setq a (liota 0 nil))
(0 . <function>)
> (defglobal b (ltake a 10))
B
> b
(0 . <function>)
> (tolist b)
(0 1 2 3 4 5 6 7 8 9)
> (tolist (ltake (ldrop a 10) 10))
(10 11 12 13 14 15 16 17 18 19)
> (setq a (liota 0 nil))
(0 . <function>)
> (setq b (lmap (lambda (x) (* x x)) a))
(0 . <function>)
> (tolist (ltake b 10))
(0 1 4 9 16 25 36 49 64 81)
> (setq b (flatlmap (lambda (x) (list x x)) a))
(0 . <function>)
> (tolist (ltake b 10))
(0 0 1 1 2 2 3 3 4 4)
> (tolist (ltake b 20))
(0 0 1 1 2 2 3 3 4 4 5 5 6 6 7 7 8 8 9 9)
> (setq b (lfilter (lambda (x) (= (mod x 2) 0)) a))
(0 . <function>)
> (tolist (ltake b 20))
(0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38)
> (lfold-left #'+ 0 (llist 1 2 3 4 5))
15
> (lfold-right #'+ 0 (llist 1 2 3 4 5))
15
> (lfold-left #'cons nil (llist 1 2 3 4 5))
(((((NIL . 1) . 2) . 3) . 4) . 5)
> (lfold-right #'cons nil (llist 1 2 3 4 5))
(1 2 3 4 5)

> (setq a (liota 1 nil))
(1 . <function>)
> (tolist (ltake a 20))
(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20)
> (setq b (lscan-left #'* 1 a))
(1 . <function>)
> (tolist (ltake b 20))
(1 1 2 6 24 120 720 5040 40320 362880 3628800 39916800 479001600 6227020800 87178291200 
1307674368000 20922789888000 355687428096000 6402373705728000 121645100408832000)
> (setq a (liota 2 nil))
(2 . <function>)
> (tolist (ltake a 20))
(2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21)
> (setq b (lscan-left #'+ 1 a))
(1 . <function>)
> (tolist (ltake b 20))
(1 3 6 10 15 21 28 36 45 55 66 78 91 105 120 136 153 171 190 210)
> (lforeach #'print (llist 1 2 3 4 5))
1
2
3
4
5
NIL

> (setq a (liota 0 nil))
(0 . <function>)
> (setq b (ltake-while (lambda (x) (< x 10)) a))
(0 . <function>)
> (tolist b)
(0 1 2 3 4 5 6 7 8 9)
> (setq b (ltake (ldrop-while (lambda (x) (< x 10)) a) 20))
(10 . <function>)
> (tolist b)
(10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29)
> (levery (lambda (x) (= (mod x 2) 0)) (llist 2 4 6 8 10))
T
> (levery (lambda (x) (= (mod x 2) 0)) (llist 2 4 5 8 10))
NIL
> (lsome (lambda (x) (= (mod x 2) 1)) (llist 2 4 6 8 10))
NIL
> (lsome (lambda (x) (= (mod x 2) 1)) (llist 2 4 5 8 10))
T
```


# Spec
see http://www.nct9.ne.jp/m_hiroi/clisp/islisp14.html
- delay expr: A macro for delaying the evaluation of expression expr. It returns a promise.
- force p: Evaluates the promise p. The result is cached, and subsequent evaluations return the cached value.
- lcons x s: Returns a new lazy stream obtained by adding element x to the beginning of - - lazy stream s.
- lcar s: Returns the first element of lazy stream s.
- lcdr s: Returns a new lazy stream obtained by removing the first element of lazy stream s.
- The end of a lazy stream is represented by NIL.
- llist &rest args: Generates a lazy stream that contains the arguments.
- fromlist xs: Converts list xs to a lazy stream.
- tolist s: Converts lazy stream s to a list.
- liota n m: Generates a lazy stream containing integers from n to m, inclusive.
- ltabulate f n m: Generates a lazy stream by applying function f to the elements of the - liota stream. Passing nil as the argument m creates an infinite stream.
- lunfold p f g seed: Reverse folding operation.
        p: A function representing the termination condition. lunfold returns NIL when (funcall p seed) evaluates to true.
        g: A function applied to the seed to generate the next seed. It produces the next seed by (funcall g seed).
        f: A function applied to the seed, whose result becomes an element of the lazy stream.
        seed: A value representing the seed or the initial element of the lazy stream.
        If p always returns NIL, an infinite stream is created.
- lnth n s: Returns the nth element of the lazy stream s.
- llength s: Returns the length of the lazy stream s. If the argument s is an infinite stream, llength does not terminate.
- lappend s1 s2: Returns a lazy stream obtained by concatenating lazy streams s1 and s2.
- lappend-delay s1 s2: Lazy evaluation version of lappend (the argument s2 is a promise).
        Note that if s1 is an infinite stream, only the elements of s1 are output.
- lzip &rest ss: Extracts elements from lazy streams and returns a lazy stream whose elements are lists containing those elements.
- ltake s n: Returns a lazy stream that takes the first n elements from lazy stream s.
- ldrop s n: Returns a lazy stream obtained by removing the first n elements from lazy stream s.
- lmap f &rest ss: Returns a lazy stream obtained by applying function f to the elements of the lazy streams ss.
- flatlmap f s: Returns a flattened lazy stream after applying mapping.
- lfilter pred s: Returns a lazy stream containing elements for which predicate pred returns true.
- lfold-left f init s: Performs a left fold on the lazy stream s from the beginning.
- lfold-right f init s: Performs a right fold on the lazy stream s from the end.
- lscan-left f init s: Returns a lazy stream whose elements are intermediate values (accumulated values) during folding.
- lforeach f s: Applies function f to the elements of lazy stream s.
- lfold-left, lfold-right, and lforeach only support finite streams.
- ltake-while pred s: Returns a lazy stream that takes elements from lazy stream s as long as predicate pred returns true.
- ldrop-while pred s: Returns a lazy stream obtained by removing elements from lazy stream s as long as predicate pred returns true.
- levery pred &rest ss: Returns NIL immediately if predicate pred returns false.
        If there are no elements in an infinite stream that return false, levery does not terminate.
- lsome pred &rest ss: Returns T immediately if predicate pred returns true.
        If there are no elements in an infinite stream that return true, lsome does not terminate.
- lunion s1 s2: Union of lazy streams.
- lintersect s1 s2: Intersection of lazy streams.
- ldifferent s1 s2: Difference of lazy streams.

