#|
To understand Turing bombe by Alan Turing.
Enigma machine
input -> rotor1 -> rotor2 -> rotor3 -> reflection
 -> rotor3 -> rotor2 -> rotor1 -> output
Each rotor connect from a-z to a-z.
The rotor rotates each time when machine get a character.
counter vector represents its rotation.
e.g. counter #(0 0 0) -> #(0 0 1) -> #(0 0 25) -> #(0 1 0) -> #(0 1 1) ...
connecta shifts characters in the positive direction by the value of counter.
connectb shiftes in the negative direction by the value of counter.
This has the same effect as rotating.

Enigma function get string and convert to charactor list.
Enigma1 funciont get charactor list. e.g. "hello" -> (#\h #\e #l #\l #o)
The ica iica iiica function transforms forward by rotor.
The reflect function reverses data by plug. 
The icb iicb iiicb function transforms backward in by rotor.

run program
> (enigma "hello")
"sirhd"
> (enigma "sirhd")
"hello"
> 

|#
(import "elixir")

;;counter to rotate 
;;elt 0 is for rotor3, elt 1 is for rotor2, elt 2 is for rotor1  
(defglobal counter #(0 0 0))

;; main function
(defun enigma (str)
    (count-clean)
    (pipe str |> (convert <list>) |> (enigma1) |> (charlist->string)))

;; use pipe macros to show transform process easier
(defun enigma1 (ls)
    (cond ((null ls) nil)
          (t (let ((l (pipe (car ls) 
                            |> (connecta (elt counter 2)) |> (ica) 
                            |> (connecta (elt counter 1)) |> (iica)
                            |> (connecta (elt counter 0)) |> (iiica)
                            |> (reflect)
                            |> (iiicb) |> (connectb (elt counter 0))
                            |> (iicb)  |> (connectb (elt counter 1))
                            |> (icb)   |> (connectb (elt counter 2)))))
                (count-up) ;rotate
                (cons l (enigma1 (cdr ls)))))))

;; e.g. connecta(#\a 3) = #\d
(defun connecta (x shift)
    (let ((base (convert #\a <integer>)))
        (convert (+ (mod (+ (- (convert x <integer>) base) shift) 26) base)
                 <character>)))

;; e.g. connectb(#\a 3) = #\x
(defun connectb (x shift)
    (let ((base (convert #\a <integer>)))
        (convert (+ (mod (- (- (convert x <integer>) base) shift) 26) base)
                 <character>)))

(defun count-up ()
    (setf (elt counter 2) (+ (elt counter 2) 1))
    (cond ((< (elt counter 2) 26) t)
          (t (setf (elt counter 2) 0)
             (setf (elt counter 1) (+ (elt counter 1) 1))
             (cond ((< (elt counter 1) 26) t)
                   (t (setf (elt counter 1) 0)
                      (setf (elt (counter 0)) (+ (elt counter 0) 1)))))))


(defun count-clean ()
    (setf (elt counter 0) 0)
    (setf (elt counter 1) 0)
    (setf (elt counter 2) 0))

;rotor1
;ABCDEFGHIJKLMNOPQRSTUVWXYZ
;DMTWSILRUYQNKFEJCAZBPGXOHV
(defconstant rotor1
    '((#\a #\d) (#\b #\m) (#\c #\t) (#\d #\w) (#\e #\s) (#\f #\i)
      (#\g #\l) (#\h #\r) (#\i #\u) (#\j #\y) (#\k #\q) (#\l #\n)
      (#\m #\k) (#\n #\f) (#\o #\e) (#\p #\j) (#\q #\c) (#\r #\a)
      (#\s #\z) (#\t #\b) (#\u #\p) (#\v #\g) (#\w #\x) (#\x #\o)
      (#\y #\h) (#\z #\v)))

(defun ica (x)
    (finda x rotor1))

(defun icb (x)
    (findb x rotor1))

;rotor2
;ABCDEFGHIJKLMNOPQRSTUVWXYZ
;HQZGPJTMOBLNCIFDYAWVEUSRKX
(defconstant rotor2
    '((#\a #\h) (#\b #\q) (#\c #\z) (#\d #\g) (#\e #\p) (#\f #\j)
      (#\g #\t) (#\h #\m) (#\i #\o) (#\j #\b) (#\k #\l) (#\l #\n)
      (#\m #\c) (#\n #\i) (#\o #\f) (#\p #\d) (#\q #\y) (#\r #\a)
      (#\s #\w) (#\t #\v) (#\u #\e) (#\v #\u) (#\w #\s) (#\x #\r)
      (#\y #\k) (#\z #\x)))

(defun iica (x)
    (finda x rotor2))

(defun iicb (x)
    (findb x rotor2))

;rotor3
;ABCDEFGHIJKLMNOPQRSTUVWXYZ
;UQNTLSZFMREHDPXKIBVYGJCWOA
(defconstant rotor3
    '((#\a #\u) (#\b #\q) (#\c #\n) (#\d #\t) (#\e #\l) (#\f #\s)
      (#\g #\z) (#\h #\f) (#\i #\m) (#\j #\r) (#\k #\e) (#\l #\h)
      (#\m #\d) (#\n #\p) (#\o #\x) (#\p #\k) (#\q #\i) (#\r #\b)
      (#\s #\v) (#\t #\y) (#\u #\g) (#\v #\j) (#\w #\c) (#\x #\w)
      (#\y #\o) (#\z #\a)))

(defun iiica (x)
    (finda x rotor3))

(defun iiicb (x)
    (findb x rotor3))

;plug
;ABCDEFGHIJKLMNOPQRSTUVWXYZ
;DPLAXGFMRSOCHZKBYIJVWTUEQN
(defconstant plug
    '((#\a #\d) (#\b #\p) (#\c #\l) (#\d #\a) (#\e #\x) (#\f #\g)
      (#\g #\f) (#\h #\m) (#\i #\r) (#\j #\s) (#\k #\o) (#\l #\c)
      (#\m #\h) (#\n #\z) (#\o #\k) (#\p #\b) (#\q #\y) (#\r #\i)
      (#\s #\j) (#\t #\v) (#\u #\w) (#\v #\t) (#\w #\u) (#\x #\e)
      (#\y #\q) (#\z #\n)))

;;reflection
(defun reflect (x)
    (finda x plug))

;; for forward search
(defun finda (x rotor)
    (elt (assoc x rotor) 1))

;; for backward seach
(defun findb (x rotor)
    (elt (rassoc x rotor) 0))

;; reverse assoc 
(defun rassoc (x y)
    (cond ((null y) nil)
          ((char= x (elt (car y) 1)) (car y))
          (t (rassoc x (cdr y)))))

;; e.g. (#\h #\e #\l #\l #\o) "hello"
(defun charlist->string (ls)
    (cond ((null ls) "")
          (t (string-append (convert (car ls) <string>)
                            (charlist->string (cdr ls))))))
