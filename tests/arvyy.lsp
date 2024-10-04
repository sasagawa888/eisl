;;; ISLisp portable tests 
;;; wirtten by Arvyy ,modifed for Easy-ISLisp by K.sasagawa


(import "test")

($assert (and (= 2 2) (> 2 1)) t)
($assert (and (= 2 2) (> 1 2)) nil)

(let ((arr #2a((1 2) (3 4))))
  ($assert (aref arr 0 0) 1)
  ($assert (aref arr 0 1) 2)
  ($assert (aref arr 1 0) 3)
  ($assert (aref arr 1 1) 4)

  (set-aref 5 arr 0 0)
  ($assert (aref arr 0 0) 5)
  ($assert (aref arr 0 1) 2)

  (setf (aref arr 0 0) 6)
  ($assert (aref arr 0 0) 6)
  ($assert (aref arr 0 1) 2)

  (set-garef 7 arr 0 0)
  ($assert (garef arr 0 0) 7)
  ($assert (garef arr 0 1) 2)

  (setf (garef arr 0 0) 8)
  ($assert (garef arr 0 0) 8)
  ($assert (garef arr 0 1) 2))

(let ((v #(1 2)))
  ($assert (aref v 0) 1)
  (set-aref 2 v 0)
  ($assert (aref v 0) 2)
  (setf (aref v 0) 3)
  ($assert (aref v 0) 3))

(let ((arr (create-array '(2 2) 1)))
  ($assert (aref arr 0 0) 1)
  ($assert (aref arr 0 1) 1)
  ($assert (aref arr 1 0) 1)
  ($assert (aref arr 1 1) 1)
  ($assert (garef arr 1 1) 1)
  ($assert (general-array*-p arr) t))

($assert (general-vector-p (create-array '(1))) t)

($assert (assure <integer> (+ 1 9)) 10)
($assert (assure <number> (+ 1 9)) 10)
#|
(block exit
    (with-handler
        (lambda (c)
            (return-from exit 1))
        (assure <number> "string")
        (format (standard-output) "FAIL")))
|#
($assert (the <integer> (+ 1 9)) 10)
($assert (the <number> (+ 1 9)) 10)
#|
(block exit
    (with-handler
        (lambda (c)
            (return-from exit 1))
        (the <number> "string")
        (format (standard-output) "FAIL")))
|#

(defun foo ()
    (block x
        (+ 10 (return-from x 6) 22)))

($assert (foo) 6)


($assert
    (case (+ 2 4)
      ((2 3 5 7) 'prime)
      ((4 6 8 9) 'composite))
    'composite)

($assert
    (case (car '(c d))
      ((a) 'a)
      ((b) 'b))
    nil)

($assert
    (case (car '(c d))
      ((a e i o u) 'vowel)
      ((y) 'semivowel)
      (t 'consonant))
    'consonant)

($assert
(let ((char #\u))
  (case char
    ((#\a #\e #\o #\u #\i) 'vowels)
    (t 'consonants)))
  'vowels)

($assert
  (case-using #'= (+ 1.0 1.0)
    ((1) 'one)
    ((2) 'two)
    (t 'more))
  'two)

($assert
  (case-using #'string= "bar"
    (("foo") 1)
    (("bar") 2))
  2)

($assert (characterp #\a) t)
($assert (characterp "a") nil)

($assert (char= #\a #\a) t)
($assert (char<= #\a #\a) t)
($assert (char<= #\a #\b) t)
($assert (char>= #\a #\a) t)
($assert (char>= #\c #\b) t)
($assert (char< #\a #\b) t)
($assert (char< #\a #\a) nil)
($assert (char> #\b #\a) t)
($assert (char> #\a #\a) nil)
($assert (char/= #\a #\b) t)
($assert (char/= #\a #\a) nil)

($assert
    (cond)
    nil)

($assert
    (cond ("1"))
    "1")

($assert
    (cond ((> 2 1) "1"))
    "1")

($assert
    (cond ((> 2 1) "1" "2"))
    "2")

($assert
    (cond
        ((< 2 1) "1")
        ((> 2 1) "2")
        ((> 3 1) "3"))
    "2")

($assert (convert #\a <character>) #\a)
($assert (convert 97 <character>) #\a)

($assert (convert #\a <integer>) 97)
($assert (convert 97 <integer>) 97)
($assert (convert "97" <integer>) 97)

($assert (convert 97 <float>) 97.0)
($assert (convert 97.0 <float>) 97.0)
($assert (convert "97.0" <float>) 97.0)

($assert (convert #\a <symbol>) 'a)
($assert (convert 'a <symbol>) 'a)
($assert (convert "a" <symbol>) 'a)

($assert (convert 97 <string>) "97")
($assert (convert 97.0 <string>) "97.0")
($assert (convert 'a <string>) "a")
($assert (convert "a" <string>) "a")

($assert (convert "97" <general-vector>) #(#\9 #\7))
($assert (convert #(1 2) <general-vector>) #(1 2))
($assert (convert '(1 2) <general-vector>) #(1 2))
($assert (convert '() <general-vector>) #())

($assert (convert "97" <list>) '(#\9 #\7))
($assert (convert #(1 2) <list>) '(1 2))
($assert (convert '(1 2) <list>) '(1 2))
($assert (convert '() <list>) '())

#|
(defclass <foo> ()
    ((bar :reader get-bar :writer set-bar :accessor bar :initarg bar :boundp bar-boundp)))

(let ((f (create (class <foo>) 'bar 1)))
  ($assert (get-bar f) 1)
  (set-bar 2 f)
  ($assert (get-bar f) 2))

;; check inheritance
(defclass <foo2> (<foo>) ())
(let ((f (create (class <foo2>) 'bar 2)))
  ($assert (get-bar f) 2))

;; check initialize-object
(defclass <foo3> () ((bar3 :reader get-bar3 :writer set-bar3 :initarg bar)))
(defmethod initialize-object ((f <foo3>) :rest args)
    (set-bar3 3 f)
    (call-next-method))
($assert (get-bar3 (create (class <foo3>) 'bar 0)) 3)

;; check accessor
(let ((obj (create (class <foo>))))
  (setf (bar obj) 4)
  ($assert (bar obj) 4))

;; check boundp
(let ((obj (create (class <foo>))))
  ($assert (bar-boundp obj) nil)
  (setf (bar obj) 6)
  ($assert (bar-boundp obj) t))

;; check class lookup error
(block exit
    (with-handler
        (lambda (condition)
            ($assert (instancep condition (class <undefined-entity>)) t)
            ($assert (undefined-entity-name condition) '<doesntexist>)
            ($assert (undefined-entity-namespace condition) 'class)
            (return-from exit nil))
        (class <doesntexist>)
        (format (standard-output) "FAIL~%")))


(defglobal foo "OK1")
($assert foo "OK1")
(let ((foo "OK2"))
    ($assert foo "OK2"))
($assert foo "OK1")
(setq foo "OK3")
($assert foo "OK3")


;; test conditions are properly raised when reading unbound variable
(block exit
    (with-handler
        (lambda (condition)
            ($assert (instancep condition (class <unbound-variable>)) t)
            (return-from exit nil))
        unbound
        ($assert nil t)))
|#

(defun foo1 (a) a)
($assert (foo1 "OK1") "OK1")

(defun foo2 (a :rest b)
    (car b))

($assert (foo2 "FAIL2" "OK2") "OK2")

(defun foo3 (a &rest b)
    (car b))

($assert (foo3 "FAIL3" "OK3") "OK3")

(defun foo4 ()
    "OK4")

($assert (foo4) "OK4")

#|
;; test conditions are properly raised on bad arg count
(block exit
    (with-handler
        (lambda (condition)
            ($assert (instancep condition (class <program-error>)) t)
            (return-from exit nil))
        (foo1)
        ($assert t nil)))
|#

(defdynamic *dyn1* 1)

($assert
    (dynamic *dyn1*)
    1)

#|
(dynamic-let ((*dyn1* 2)
              (*dyn2* 3))
  ($assert (dynamic *dyn1*) 2)
  ($assert (dynamic *dyn2*) 3)
  (set-dynamic 4 *dyn1*)
  ($assert (dynamic *dyn1*) 4))
|#
($assert (dynamic *dyn1*) 1)


(flet ((f (x) (+ x 3)))
    (flet ((f (x) (+ x (f x))))
        ($assert (= (f 7) 17) t)))

(defglobal inputs '())
(defglobal sum
  (let ((x '(1 3 5 7 9)))
     (for ((x x (cdr x))
           (sum 0 (+ sum (car x))))
          ((not x) sum)
       (setq inputs (cons (car x) inputs)))))

($assert sum 25)
($assert inputs '(9 7 5 3 1))

($assert (+ 1 2) 3)
($assert (funcall #'+ 1 2) 3)
($assert (funcall (function +) 1 2) 3)
($assert (apply #'+ (list 1 2)) 3)
($assert (apply #'+ 1 (list 2)) 3)
($assert ((lambda (a) (+ 1 a)) 2) 3)

#|
(block exit
    (with-handler
        (lambda (condition)
            ($assert t (instancep condition (class <undefined-function>)))
            (return-from exit nil))
        (doesntexist)
        ($assert 1 0)))

(block exit
    (with-handler
        (lambda (condition)
            ($assert t (instancep condition (class <undefined-function>)))
            (return-from exit nil))
        #'doesntexist
        ($assert 1 0)))
|#

($assert (ignore-errors) nil)
($assert
    (ignore-errors
      (format (standard-output) "OK~%")
      (+ 1 'b)
      (print "FAIL"))
    nil)


(labels ((evenp (n)
           (if (= n 0)
               t
               (oddp (- n 1))))
         (oddp (n)
           (if (= n 0)
               nil
               (evenp (- n 1)))))
    ($assert (evenp 88) t))


(defun foo (a)
    (let ((a (+ 1 2))
          (b a))
      (+ a b)))
($assert
    (foo 0)
    3)

(defun bar (a)
    (let* ((a (+ 1 2))
           (a (+ 1 a))
           (b a))
      (+ a b)))

($assert
    (bar 0)
    8)

($assert (let ((foo 1)) foo) 1)

(defglobal *closure* (let ((foo 5)) (lambda () foo)))
($assert (funcall *closure*) 5)

($assert (reverse (list 1 2 3)) (list 3 2 1))
($assert (nreverse (list 1 2 3)) (list 3 2 1))

;; taken from spec
($assert (assoc 'a '((a . 1) (b . 2))) '(a . 1))
($assert (assoc 'a '((a . 1) (a . 2))) '(a . 1))
($assert (assoc 'c '((a . 1) (b . 2))) nil)

;; taken from spec
($assert
  (member 'c '(a b c d e f))
  '(c d e f))
($assert
  (member 'g '(a b c d e f))
  nil)

;; taken from spec
($assert
    (maplist (lambda (x) (cons 'foo x)) '(a b c d))
    '((foo a b c d) (foo b c d) (foo c d) (foo d)))

;; taken from spec
(let ((k 0))
  (mapl (lambda (x)
          (setq k (+ k (if (member (car x) (cdr x)) 0 1))))
        '(a b a c d b c))
  ($assert k 4))

;; taken from spec
($assert
  (mapcar #'car '((1 a) (2 b) (3 c)))
  '(1 2 3))

;; taken from spec
(let ((x 0))
  (mapc (lambda (v)
          (setq x (+ x v)))
        '(3 5))
  ($assert x 8))

;; taken from spec
($assert
  (mapcan (lambda (x)
            (if (> x 0)
                (list x)))
          '(-3 4 0 5 -2 7))
  '(4 5 7))

;; taken from spec
($assert
  (mapcon (lambda (x)
            (if (member (car x) (cdr x))
                (list (car x))))
          '(a b a c d b c b c))
  '(a b c b c))

($assert
  (append '(1 2) '(3 4) '(5 6))
  '(1 2 3 4 5 6))

;; sequences
($assert (length '(1 2)) 2)
($assert (elt '(4 5 6) 0) 4)
(let ((lst (list 1 2 3)))
  (setf (elt lst 2) 4)
  ($assert lst '(1 2 4)))

#|
(block exit
    (with-handler
        (lambda (condition)
            ($assert (instancep condition (class <program-error>)) t)
            (return-from exit nil))
        (elt '(1 2 3) 4)
        (print "FAIL")))
(block exit
    (with-handler
        (lambda (condition)
            ($assert (instancep condition (class <program-error>)) t)
            (return-from exit nil))
        (setl-elt  4 (list 1 2 3) 4)
        (print "FAIL")))
|#

;;reader
($assert #b10 2)
($assert #b-10 -2)
($assert #o10 8)
($assert #o-10 -8)
($assert #x1f 31)
($assert #x-1f -31)

;; type checks
($assert (numberp 1) t)
($assert (numberp "1") nil)

;; min and max
($assert (= 1 (min 1)) t)
($assert (= 1 (min 3 1)) t)
($assert (= 1 (min 1 3)) t)

($assert (= 1 (max 1)) t)
($assert (= 3 (max 3 1)) t)
($assert (= 3 (max 1 3)) t)

;; addition
($assert (= 3 (+ 1 2)) t)
($assert (= 3 (+ 1.0 2.0)) t)
($assert (= 10000000000000000001 (+ 10000000000000000000 1)) t)

#|
(block exit
    (with-handler
      (lambda (condition)
        ($assert
            (instancep condition (class <domain-error>))
            t)
        (return-from exit nil))
      (+ 1 "2")
      ($assert nil t)))
|#

;; subtraction
($assert (- 1) -1)
($assert (- -4.0) 4.0)
($assert (- 4.0) -4.0)
($assert (- 1 2) -1)
($assert (- 92 43) 49)
($assert (- 0.0 0.0) 0.0)
($assert (- 3 4 5) -6)

;; multiplication; tests taken from spec
($assert
  (* 12 3)
  36)

($assert
  (* 12 3.0)
  36.0)

($assert
  (* 4.0 0)
  0.0)

($assert
  (* 2 3 4)
  24)

($assert
  (*)
  1)

;; division / reciprocal
($assert (reciprocal 2) 0.5)
($assert (quotient 10 5) 2)
($assert (quotient 1 2) 0.5)
($assert (quotient 2 -0.5) -4.0)
($assert (quotient 2 4 8) 0.0625)

#|
(block exit
    (with-handler
      (lambda (condition)
        ($assert
            (instancep condition (class <division-by-zero>))
            t)
        (return-from exit nil))
      (quotient 0.0 0.0)
      ($assert nil t)))
|#

;; sqrt
($assert (sqrt 4) 2)
($assert t (and (> (sqrt 2) 1.41421)
                   (< (sqrt 2) 1.41422)))

#|
(block exit
    (with-handler
      (lambda (condition)
        ($assert
            (instancep condition (class <domain-error>))
            t)
        (return-from exit nil))
      (sqrt -1)
      ($assert nil t)))
|#
;; trigonometry
($assert
    (and (> (sin 1) 0.841)
         (< (sin 1) 0.842))
    t)

($assert
    (and (> (cos 1) 0.540)
         (< (cos 1) 0.541))
    t)

($assert
    (and (> (tan 1) 1.557)
         (< (tan 1) 1.558))
    t)

($assert (or (= 2 2) (> 2 1)) t)
($assert (or (= 2 2) (> 1 2)) t)

(let ((p (cons 1 2)))
    ($assert (car p) 1)
    ($assert (cdr p) 2)
    (set-car 3 p)
    (set-cdr 4 p)
    ($assert (car p) 3)
    ($assert (cdr p) 4)
    (setf (car p) 5)
    (setf (cdr p) 6)
    ($assert (car p) 5)
    ($assert (cdr p) 6))

($assert `(1 2) (list 1 2))
($assert `(1 ,2) (list 1 2))
($assert `(1 ,(+ 1 2)) (list 1 3))
($assert `#(1 ,(+ 1 2)) (vector 1 3))
($assert `#(1 ,@(progn '(2 3))) (vector 1 2 3))

;; nested quasiquote representation seems to be underspecified,
;; use a macro defining macro to portably test nested quasiquote behavior.
#|
(defmacro m1 (a)
  `(defmacro m2 (b)
      `(list ,,a ,b)))

(m1 1)
($assert (m2 2) (list 1 2))
|#

($assert '(1 . 2) (cons 1 2))

($assert (floor  3.0) 3 )
($assert (floor  3.4) 3 )
($assert (floor  3.9) 3 )
($assert (floor -3.9) -4)
($assert (floor -3.4) -4)
($assert (floor -3.0) -3)

($assert (ceiling  3.0) 3 )
($assert (ceiling  3.4) 4 )
($assert (ceiling  3.9) 4 )
($assert (ceiling -3.9) -3)
($assert (ceiling -3.4) -3)
($assert (ceiling -3.0) -3)

($assert (truncate  3.0) 3 )
($assert (truncate  3.4) 3 )
($assert (truncate  3.9) 3 )
($assert (truncate -3.9) -3)
($assert (truncate -3.4) -3)
($assert (truncate -3.0) -3)

($assert (round  3.0) 3 )
($assert (round  3.4) 3 )
($assert (round  3.6) 4 )
($assert (round -3.6) -4)
($assert (round  3.5) 4 )
($assert (round -3.5) -4)
($assert (round  2.5) 2 )
($assert (round -0.5) 0 )

(let ((a (list 1 2 3 4))
      (b (list 10 10 10 10)))
  (map-into a #'+ a b)
  ($assert a (list 11 12 13 14))
  ($assert b (list 10 10 10 10)))

(let ((foo 1))
    (setq foo 2)
    ($assert foo 2)
    (setf foo 3)
    ($assert foo 3))

(defglobal *global* 1)
(setq *global* 2)
($assert *global* 2)

($assert (streamp (create-string-input-stream "foo")) t)
($assert (streamp (create-string-output-stream)) t)
($assert (streamp 123) nil)

($assert (input-stream-p (create-string-input-stream "foo")) t)
($assert (input-stream-p (create-string-output-stream)) nil)
($assert (input-stream-p 123) nil)

($assert (output-stream-p (create-string-input-stream "foo")) nil)
($assert (output-stream-p (create-string-output-stream)) t)
($assert (output-stream-p 123) nil)

($assert (output-stream-p (standard-output)) t)
($assert (output-stream-p (error-output)) t)
($assert (input-stream-p (standard-input)) t)

(let ((stream (create-string-input-stream "a")))
  ($assert (read-char stream) #\a)
  ($assert (read-char stream nil) nil))

(let ((stream (create-string-input-stream "a")))
  ($assert (read-char stream) #\a)
  ($assert (read-char stream nil 'foo) 'foo))

#|
(let ((stream (create-string-input-stream "a")))
  ($assert (read-char stream) #\a)
  (block exit
    (with-handler
      (lambda (err)
        ($assert (instancep err (class <end-of-stream>)) t)
        (return-from exit nil))
      (read-char stream t)
      ($assert nil t)))) ;; shouldn't get here
|#

(let ((stream (create-string-input-stream "a")))
  ($assert (preview-char stream) #\a)
  ($assert (preview-char stream) #\a)
  (read-char stream)
  ($assert (preview-char stream nil) nil))


(let ((out (create-string-output-stream)))
  (format out "abc~%de")
  ;(finish-output out)
  (let ((stream (create-string-input-stream (get-output-stream-string out))))
      ($assert (read-line stream) "abc")
      ($assert (read-line stream) "de")
      ($assert (read-line stream nil) nil)))

(let ((stream (create-string-input-stream "hello #(1 2 3) 123 #\\A")))
  ($assert (read stream) 'hello)
  ($assert (read stream) #(1 2 3))
  ($assert (read stream) 123)
  ($assert (read stream) #\A)
  ($assert (read stream nil "the end") "the end"))

($assert (create-string 3 #\1) "111")
($assert (string= (create-string 3 #\1) "111") t)

($assert (string= "abc" "abc") t)
($assert (string= "abc" "abb") nil)
($assert (string= "abc" "abcd") nil)

($assert (string/= "abc" "abc") nil)
($assert (string/= "abc" "abb") t)
($assert (string/= "abc" "abcd") t)

($assert (string> "a" "a") nil)
($assert (string> "a" "b") nil)
($assert (string> "b" "a") t)
($assert (string> "a" "aa") nil)
($assert (string> "aa" "a") t)

($assert (string>= "a" "a") t)
($assert (string>= "a" "b") nil)
($assert (string>= "b" "a") t)
($assert (string>= "a" "aa") nil)
($assert (string>= "aa" "a") t)

($assert (string< "a" "a") nil)
($assert (string< "a" "b") t)
($assert (string< "b" "a") nil)
($assert (string< "a" "aa") t)
($assert (string< "aa" "a") nil)

($assert (string<= "a" "a") t)
($assert (string<= "a" "b") t)
($assert (string<= "b" "a") nil)
($assert (string<= "a" "aa") t)
($assert (string<= "aa" "a") nil)

;; sequence; test mutable and immutable separately
($assert (elt "789" 0) #\7)
($assert (elt (create-string 3 #\7) 0) #\7)

#|
(block exit
    (with-handler
        (lambda (condition)
            ($assert (instancep condition (class <program-error>)) t)
            (return-from exit nil))
        (elt "123" 4)
        (print "FAIL")))
(block exit
    (with-handler
        (lambda (condition)
            ($assert (instancep condition (class <program-error>)) t)
            (return-from exit nil))
        (elt (create-string 3) 4)
        (print "FAIL")))
(block exit
    (with-handler
        (lambda (condition)
            ($assert (instancep condition (class <program-error>)) t)
            (return-from exit nil))
        (set-elt #\7 (create-string 3) 4)
        (print "FAIL")))
|#
($assert (length "ab") 2)
($assert (length (create-string 2 #\7)) 2)
(let ((str (create-string 1 #\0)))
  (setf (elt str 0) #\1)
  ($assert str "1"))

;; append
($assert (string-append "12" "34") "1234")
($assert (string-append "12" "" "34" "5") "12345")
($assert (string-append "12" (create-string 1 #\3)) "123")
($assert (string-append) "")

($assert (property 'foo 'bar "OK1") "OK1")

(set-property "OK2" 'foo 'bar)
($assert (property 'foo 'bar "FAIL2") "OK2")

(setf (property 'foo 'bar) "OK3")
($assert (property 'foo 'bar "FAIL3") "OK3")

(setf (property 'foo 'bar) "OK4")
($assert (remove-property 'foo 'bar) "OK4")
($assert (property 'foo 'bar "OK5") "OK5")

($assert (eql 'a 'a) t)
($assert (eql 'a 'c) nil)

(defmacro incf (var value)
    `(setq ,var (+ ,var ,value)))

(defun foo ()
 (let ((val 0))
    (tagbody
      (setq val 1)
      (go point-a)
      (incf val 16)
     point-c
      (incf val 04)
      (go point-b)
      (incf val 32)
     point-a
      (incf val 02)
      (go point-c)
      (incf val 64)
     point-b
      (incf val 08))
    val))
($assert (foo) 15)

($assert
    (+ 1
       (catch 'foo
         (+ 2 (throw 'foo 1)))
       3)
    5)

;; frivolous function to fake compution for long enough that at least some time passes.
;; prints empty string so that runtime cannot optimize action away
(defun fake-busy-fn (n)
  (for ((i n (- i 1)))
       ((= i 0) t)
   (format (standard-output) "")))

($assert (integerp (internal-time-units-per-second)) t)

(let ((t1 (get-internal-real-time))
      (t2 (get-internal-run-time))
      (t3 (get-universal-time)))
  ($assert (integerp t1) t)
  ($assert (integerp t2) t)
  ($assert (integerp t3) t)

  (fake-busy-fn 10000)

  ($assert (< t1 (get-internal-real-time)) t)
  ($assert (< t2 (get-internal-run-time)) t)
  ;; not too meaningful to test, since its granularity is in seconds, so it will fail with small fake-busy-fn,
  ;; and test will be time-wasteful with large fake-busy-fn.
  ;;($assert (< t3 (get-universal-time)) t)
  )

(let ((v1 (vector 1 2))
      (v2 (create-vector 3 3))
      (v3 #(4 5)))
  ($assert (elt v1 0) 1)
  ($assert (elt v2 0) 3)
  ($assert (elt v3 0) 4))

;; sequence
($assert (length #(1 2)) 2)
($assert (elt #(1 2 3) 2) 3)

#|
(block exit
    (with-handler
        (lambda (condition)
            ($assert (instancep condition (class <program-error>)) t)
            (return-from exit nil))
        (elt #(1 2 3) 4)
        (print "FAIL")))
(block exit
    (with-handler
        (lambda (condition)
            ($assert (instancep condition (class <program-error>)) t)
            (return-from exit nil))
        (set-elt 4 (vector 1 2 3) 4)
        (print "FAIL")))
|#
(let ((vec (vector 1 2 3)))
  (setf (elt vec 2) 4)
  ($assert vec #(1 2 4)))

(defglobal *data* '())

(let ((i 3))
  (while (> i 0)
    (setq *data* (cons i *data*))
    (setf i (- i 1))))

($assert *data* '(1 2 3))

(let ((s (create-string-output-stream)))
  (with-standard-output s
    (format s "2"))
  ($assert (get-output-stream-string s) "2"))
