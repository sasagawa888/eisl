# Lazy

Lazy evalution,
written by M.Hiroi.

# Acknowledgement
Thanks to Mr. Hiroi.

# Usage 

```lisp
(import "lazy")
```

# Example 1

```
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
```

# Example 2

```lisp
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

