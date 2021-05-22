# Seq

Common-Lisp like sequence library.
The Seq library was written by M. Hiroi.

# Acknowledgement
Thanks to Mr. Hiroi.

# Usage 

```lisp
(import "seq")

```

# Specification
- list-> vector xs
    Convert list xs to vector
- list-> string xs
    Convert list xs to a string (list elements must be characters)
- vector-> list xs
    Convert vector xs to string
- vector-> string xs
    Convert vector xs to a string (vector elements must be characters)
- string-> list xs
    Convert a string to a list
- string-> vector xs
    Convert a string to a list 
- find item xs
    Find the element equal to item (eql) in column xs
- find-if pred xs
    Find the element in column xs for which the predicate pred returns true
- find-if-not pred xs
    Column xs predicate pred looks for false element
- position item xs
    Returns the position of the element equal to item from column xs
- position-if pred xs
    Returns the position of the element from column xs where the predicate pred returns true
- position-if-not pred xs
    Returns the position of the element from column xs where the predicate pred returns false
- count item xs
    Returns the number of (eql) elements equal to item from column xs
- count-if pred xs
    Returns the number of elements for which the predicate pred returns true from column xs
- count-if-not pred xs
    Column xs Predicate pred returns false and number of elements 
- fill xs item
    Destructively rewrite the element of column xs to item
- remove item xs
    Returns a new column with the (eql) element equal to item removed
- remove-if pred xs
    Returns a new column with the element whose predicate pred returns true
- remove-if-not pred xs
    Predicate pred returns false Returns a new column with the element removed
- substitute new old xs
    Returns a new column with an element equal to old (eql) replaced by new
- substitute-if new pred xs
    Returns a new column with the element for which the predicate pred returns true replaced by new
- substitute-if-not new pred xs
    Predicate pred returns false Returns a new column with new elements replaced
- nsubstitute new old xs
    Equal to old (eql) Replace element with new (destructive)
- nsubstitute-if new pred xs
    Replace the element for which the predicate pred returns true with new (destructive)
- nsubstitute-if-not new pred xs
    Replace elements where the predicate pred returns false with new (destructive) 
- concatenate result-type [xs1 ...]
    Create a new column (type is result-type) that concatenates the argument columns
- map result-type fn xs1 [xs2 ...]
    Apply the function fn to the elements of the argument column and return a new column (type is result-type) containing the result
- reduce fn init xs1 [xs2 ...]
    Convolve the argument sequence from the beginning
    Cumulative values are passed as the first argument of the function fn, and column elements are passed as the remaining arguments.
- reduce-right fn init xs1 [xs2 ...]
    Convolve the argument sequence from the end
    Cumulative values are passed as the first argument of the function fn, and column elements are passed as the remaining arguments.
- some pred xs1 [xs2 ...]
    Apply the predicate pred to the elements of a column and return T if any element returns true.
- every pred xs1 [xs2 ...]
    Apply the predicate pred to an element of a column and return NIL if any element returns false. 

# Test cases


```lisp
(test (remove 'a '(a b a b c a b c d)) (B B C B C D))
(test (remove 'a #(a b a b c a b c d)) #(B B C B C D))
(test (remove #\a "ababcabcd") "bbcbcd")
(test (remove-if #'evenp '(1 2 3 4 5 6 7 8 9)) (1 3 5 7 9))
(test (remove-if-not #'evenp #(1 2 3 4 5 6 7 8 9)) #(2 4 6 8))
(test (substitute 'z 'a '(a b a b c a b c d)) (Z B Z B C Z B C D))
(test (substitute 'z 'a #(a b a b c a b c d)) #(Z B Z B C Z B C D))
(test (substitute #\z #\a "ababcabcd") "zbzbczbcd")
(test (substitute-if 0 #'evenp '(1 2 3 4 5 6 7 8 9)) (1 0 3 0 5 0 7 0 9))
(test (substitute-if-not 0 #'evenp #(1 2 3 4 5 6 7 8 9)) #(0 2 0 4 0 6 0 8 0))
(test (list->vector '(1 2 3 4 5)) #(1 2 3 4 5))
(test (list->string '(#\1 #\2 #\3 #\4 #\5)) "12345")
(test (vector->list #(1 2 3 4 5)) (1 2 3 4 5))
(test (vector->string #(#\1 #\2 #\3 #\4 #\5)) "12345")
(test (string->list "12345") (#\1 #\2 #\3 #\4 #\5))
(test (string->vector "12345") #(#\1 #\2 #\3 #\4 #\5))
(test (find 3 '(1 2 3 4 5 6 7 8)) 3)
(test (find 9 '(1 2 3 4 5 6 7 8)) NIL)
(test (find 3 #(1 2 3 4 5 6 7 8)) 3)
(test (find 9 #(1 2 3 4 5 6 7 8)) NIL)
(test (find #\3 "12345678") #\3)
(test (find #\9 "12345678") NIL)
($eval (defun evenp (x) (= (mod x 2) 0)))
($eval (defun oddp (x) (= (mod x 2) 1)))
(test (find-if #'evenp '(1 2 3 4 5 6 7 8)) 2)
(test (find-if-not #'evenp '(1 2 3 4 5 6 7 8)) 1)
(test (find-if #'evenp #(1 2 3 4 5 6 7 8)) 2)
(test (find-if-not #'evenp #(1 2 3 4 5 6 7 8)) 1)
(test (position 3 '(1 2 3 4 5 6 7 8)) 2)
(test (position 9 '(1 2 3 4 5 6 7 8)) -1)
(test (position 3 #(1 2 3 4 5 6 7 8)) 2)
(test (position 9 #(1 2 3 4 5 6 7 8)) -1)
(test (position #\3 "12345678") 2)
(test (position #\9 "12345678") -1)
(test (position-if #'oddp '(1 2 3 4 5 6 7 8)) 0)
(test (position-if-not #'oddp #(1 2 3 4 5 6 7 8)) 1)
(test (count 3 '(1 2 1 2 3 1 2 3 4)) 2)
(test (count 0 '(1 2 1 2 3 1 2 3 4)) 0)
(test (count 3 #(1 2 1 2 3 1 2 3 4)) 2)
(test (count 0 #(1 2 1 2 3 1 2 3 4)) 0)
(test (count #\3 "121231234") 2)
(test (count #\0 "121231234") 0)
(test (count-if #'evenp '(1 2 1 2 3 1 2 3 4)) 4)
(test (count-if-not #'evenp #(1 2 1 2 3 1 2 3 4)) 5)
(test (concatenate '<list> '(1 2 3 4) #(5 6 7 8) "abcd") (1 2 3 4 5 6 7 8 #\a #\b #\c #\d))
(test (concatenate '<general-vector> '(1 2 3 4) #(5 6 7 8) "abcd") #(1 2 3 4 5 6 7 8 #\a #\b #\c #\d))
(test (concatenate '<string> '(#\1 #\2 #\3 #\4) #(#\5 #\6 #\7 #\8) "abcd") "12345678abcd")
(test (map '<list> #'list '(1 2 3 4) #(5 6 7 8) "abcd") ((1 5 #\a) (2 6 #\b) (3 7 #\c) (4 8 #\d)))
(test (map '<general-vector> #'list '(1 2 3 4) #(5 6 7 8) "abcd") #((1 5 #\a) (2 6 #\b) (3 7 #\c) (4 8 #\d)) equal)
(test (map '<string> (lambda (x y) (if (char< x y) x y)) "AbCd" "aBcD") "ABCD")
(test (reduce (lambda (a x y z) (cons (list x y z) a)) nil '(1 2 3 4) #(5 6 7 8) "abcd") ((4 8 #\d) (3 7 #\c) (2 6 #\b) (1 5 #\a)))
(test (reduce-right (lambda (a x y z) (cons (list x y z) a)) nil '(1 2 3 4) #(5 6 7 8) "abcd") ((1 5 #\a) (2 6 #\b) (3 7 #\c) (4 8 #\d)))
(test (some #'evenp #(1 3 5 7 9)) NIL)
(test (some #'evenp #(1 3 5 7 8 9)) T)
(test (some #'= '(1 2 3 4) #(7 6 5 4)) T)
(test (some #'= '(1 2 3 4) #(7 6 5 8)) NIL)
(test (some #'char= "abcd" "ABCd") T)
(test (some #'char= "abcd" "ABCD") NIL)
(test (every #'oddp '(1 3 5 7 9)) T)
(test (every #'oddp '(1 3 5 7 9 10)) NIL)
(test (every #'= '(1 2 3 4) #(1 2 3 4)) T)
(test (every #'= '(1 2 3 4) #(1 2 3 5)) NIL)
(test (every #'char= "abcd" "abcd") T)
(test (every #'char= "abcd" "abcD") NIL)

```

Side effect functions example

```lisp
>(defglobal a '(a b c d e f))
A
>a
(A B C D E F)
>(fill a 'g)
(G G G G G G)
>a
(G G G G G G)
>(defglobal b #(a b c d e f))
B
>(fill b 'g)
#(G G G G G G)
>b
#(G G G G G G)
>(defglobal c "abcdef")
C
>(fill c #\g)
"gggggg"
>c
"gggggg"

>(remove 'a '(a b a b c a b c d))
(B B C B C D)
>(remove 'a #(a b a b c a b c d))
#(B B C B C D)
>(remove #\a "ababcabcd")
"bbcbcd"
>(remove-if #'evenp '(1 2 3 4 5 6 7 8 9))
(1 3 5 7 9)
>(remove-if-not #'evenp #(1 2 3 4 5 6 7 8 9))
#(2 4 6 8)

>(substitute 'z 'a '(a b a b c a b c d))
(Z B Z B C Z B C D)
>(substitute 'z 'a #(a b a b c a b c d))
#(Z B Z B C Z B C D)
>(substitute #\z #\a "ababcabcd")
"zbzbczbcd"
>(substitute-if 0 #'evenp '(1 2 3 4 5 6 7 8 9))
(1 0 3 0 5 0 7 0 9)
>(substitute-if-not 0 #'evenp #(1 2 3 4 5 6 7 8 9))
#(0 2 0 4 0 6 0 8 0)

>(defglobal a '(a b a b c a b c d))
A
>(nsubstitute 'z 'a a)
(Z B Z B C Z B C D)
>a
(Z B Z B C Z B C D)
>(defglobal b #(a b a b c a b c d))
B
>(nsubstitute 'z 'a b)
#(Z B Z B C Z B C D)
>b
#(Z B Z B C Z B C D)
>(defglobal c "ababcabcd"))
C
>(nsubstitute #\z #\a c)
"zbzbczbcd"
>c
"zbzbczbcd"
>(defglobal a '(1 2 3 4 5 6 7 8 9))
A
>(nsubstitute-if 0 #'evenp a)
(1 0 3 0 5 0 7 0 9)
>a
(1 0 3 0 5 0 7 0 9)
>(defglobal b #(1 2 3 4 5 6 7 8 9))
B
>(nsubstitute-if-not 1 #'evenp b)
#(1 2 1 4 1 6 1 8 1)
>b
#(1 2 1 4 1 6 1 8 1)


```