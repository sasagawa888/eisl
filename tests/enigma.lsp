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

You can set initial position of rotors.
e.g. (set-init 1 2 3) 
This combination is 26^3 = 17,576

tb(Turing's Bombe) can find this setting in secons.
|#
(import "elixir")
(import "test")

;;counter to rotate 
;;elt 0 is for rotor3, elt 1 is for rotor2, elt 2 is for rotor1  
(defglobal counter #(0 0 0))

;;initial rotate position. You can set it with (set-init r3 r2 r1)
(defglobal initial #(0 0 0))


;; Turing's bombe
;; (tb "hello" "oqbep") -> #(1 2 3)
;; (tb "hello" "oikrw") -> #(25 25 25)
;; The actual bembe was a parallel machine. 12 parallel.
;; But tb function checks from (0 0 0) to (25 25 25) in sequential processing.
;; Today computer is fast enough to do this calculation in seconds.
(defun tb (str1 str2)
    (block exit
        (set-init 0 0 0)
        (while t 
            (if (string= (enigma str1) str2)
                (return-from exit t))
            (count-up initial)))
    (gbc); for compile code
    initial
)


;; Enigma main function
(defun enigma (str)
    (count-init)
    (pipe str |> (convert <list>) |> (enigma1) |> (charlist->string)))

;; use pipe macros to show transform process easier
(defun enigma1 (ls)
    (cond ((null ls) nil)
          (t (let ((l (pipe (car ls) |> (check)
                            |> (connecta (elt counter 2)) |> (check1) |> (ica)  |> (check1)
                            |> (connecta (elt counter 1)) |> |> (check1) |> (iica) |> (check1)
                            |> (connecta (elt counter 0)) |> (iiica) |> (check1) |> (check1)
                            |> (reflect) |> (check1)
                            |> (iiicb) |> (check1) |> (connectb (elt counter 0)) |> (check1)
                            |> (iicb)  |> (check1) |> (connectb (elt counter 1)) |> (check1)
                            |> (icb)   |> (check1) |> (connectb (elt counter 2)) |> (check1))))
                (count-up counter) ;rotate
                (cons l (enigma1 (cdr ls)))))))

(defun check (x)
    (print x)
    x)  

(defun check1 (x)
    (format (standard-output) "~A " x)
    x)

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

(defun count-up (x)
    (setf (elt x 2) (+ (elt x 2) 1))
    (cond ((< (elt x 2) 26) t)
          (t (setf (elt x 2) 0)
             (setf (elt x 1) (+ (elt x 1) 1))
             (cond ((< (elt x 1) 26) t)
                   (t (setf (elt x 1) 0)
                      (setf (elt x 0) (+ (elt x 0) 1)))
                      (cond ((< (elt x 0) 26) t)
                            (setf (elt x 0) 0)
                            (setf (elt x 1) 0)
                            (setf (elt x 2) 0))))))


(defun set-init (r3 r2 r1)
    (setf (elt initial 0) r3)
    (setf (elt initial 1) r2)
    (setf (elt initial 2) r1))

(defun count-init ()
    (setf (elt counter 0) (elt initial 0))
    (setf (elt counter 1) (elt initial 1))
    (setf (elt counter 2) (elt initial 2)))

(defun count-rand ()
    (setf (elt counter 0) (random 26))
    (setf (elt counter 1) (random 26))
    (setf (elt counter 2) (random 26)))

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
