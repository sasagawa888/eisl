;; Lambda calculus interpreter 
;; Usage   
;; (load "example/lambda.lsp")
;; > (repl)
;; L>
;; To quit enter end
;; L> end

;; inner data structure 
;; ^x.x -> (^ x x)
;; ^x.^y.y -> (^ x (^ y y))

;; Combinator 
;; I = ^x.x
;; K = ^x.^y.x
;; S = ^x.^y.^z.xz(yz)

;; Shorthand
;; ^xyz.z -> ^x.^y.^z.z

;; Test case
;; see lambda-test.lsp

(import "elixir")
(import "test")

(defun cadr (x)
  (car (cdr x)))

(defun caar (x) 
  (car (car x)))

(defun cddr (x)
  (cdr (cdr x)))

(defun caddr (x)
  (car (cdr (cdr x))))

(defun repl ()
  (format (standard-output) "Lambda calculus interpreter ~%")
  (format (standard-output) "To quit enter 'end'~%")
  (repl1))


(defun repl1 ()
  (block repl
    (cond ((catch 'exit
             (for ((s (read*) (read*)))
                  ((equal s 'end) (return-from repl t))
                  (print* (reduce (combinator s))))) t)
          (t (prompt)(repl1)))))

(defun read* ()
  (format (standard-output) "L> ")
  (parse* (read-line)))


(defun print* (x)
  (princ* x)
  (format (standard-output) "~%"))

(defun princ* (x)
  (cond ((lambda-p x) (print1* x))
        ((atom x) (format (standard-output) "~A" x))
        (t (print2* x))))
  

(defun print1* (x)
  (format (standard-output) "^")
  (format (standard-output) "~A" (cadr x))
  (format (standard-output) ".")
  (princ* (caddr x)))

(defun print2* (x)
  (cond ((null x) t)
        ((lambda-p (car x))
         (format (standard-output) "(") (princ* (car x)) (format (standard-output) ")")
         (print2* (cdr x)))
        (t (princ* (car x)) (print3* (cdr  x)))))

(defun print3* (x)
  (cond ((null x) t)
        ((consp (car x))
         (format (standard-output) "(") (princ* (car x)) (format (standard-output) ")")
         (print3* (cdr x)))
        (t (princ* (car x)) (print2* (cdr  x)))))


(defun parse* (x)
    (pipe x |> (convert <list>) |> (parse nil) ))
 
#|
parse 
 ^x.x -> (^ x x)
 (^x.x)(^y.y) -> ((^ x x)(^ y y))

|#
(defglobal *rest-list* nil)

(defpattern parse
  ((empty _res) _res)
  ;; space skip
  (((#\space :rest _ls) _res) (parse _ls _res))
  (((#\e #\n #\d) _res) 'end)
  (((#\^ _arg #\. :rest _ls) _) (let* ((arg1 (convert _arg <symbol>))
                                       (body (parse _ls nil)))
                                  (parse *rest-list* (list '^ arg1 body))))
  ;; e.g. ^xyz.z shorthand
  (((#\^ _arg :rest _ls) _) (let* ((arg1 (convert _arg <symbol>)))
                               (cons '^ (list arg1 (parse (cons #\^ _ls) nil)))))
  ;; ( )
  (((#\( :rest _ls) _res) (let* ((exp (parse _ls nil)))
                              (if (null _res)
                                  (parse *rest-list* exp)
                                  (parse *rest-list* (cons _res (list exp))))))
  (((#\) :rest _ls) _res)
      (setq *rest-list* _ls)
      _res)
  (((_body :rest _ls) empty) (when (variable-p _body))
             (setq *rest-list* _ls)
             (parse *rest-list* (convert _body <symbol>)))
  (((_body :rest _ls) _res) (when (variable-p _body))
             (setq *rest-list* _ls)
             (parse *rest-list* (cons _res (list (convert _body <symbol>)))))
  (else (print "syntax error")))

(defun lambda-p (x)
  (and (consp x) (eq (car x) '^)))

(defun variable-p (x)
  (and (characterp x) (char>= x #\A) (char<= x #\z)))

(defpattern combinator
  ((empty) nil)
  ((_x) (when (lambda-p _x)) _x)
  ((I) '(^ x x))
  ((K) '(^ x (^ y x)))
  ((S) '(^ x (^ y (^ z ((x z) (y z))))))
  ((Y) '(^ y ((^ x (^ y (^ x x))) (^ x (^ y (^ x x))))))
  (((_x :rest _xs)) (cons (combinator _x) (combinator _xs)))
  ((_x) _x))


(defpattern reduce
    ((end) (throw 'exit "end"))
    ((_x) (when (atom _x)) _x)
    (((^ _arg _body)) (print* (list '^ _arg _body)) (list '^ _arg (reduce _body)))
    (((_x _y)) (when (atom _x)) (print* (list _x _y)) (list _x _y))
    (((_x _y)) (when (lambda-p _x)) (print* (list _x _y)) (reduce (beta _x _y)))
    (((_x _y)) (when (consp _x)) (print* (list _x _y)) (beta (reduce _x) _y))
    (else (print "reduce error") 'error)
)
    

(defun beta (x y)
    (if (lambda-p x)
        (let ((arg (cadr x))
              (body (caddr x)))
          (replace arg body y))
        (list x y)))

(defun replace (arg body y)
    (cond ((null body) nil)
          ((and (atom body) (eq arg body)) y)
          ((atom body) body)
          (t (cons (replace arg (car body) y)
                   (replace arg (cdr body) y)))))


;;--------------tests------------------------
($test (parse* "^X.X") (^ x x))
($test (parse* "^X. X") (^ x x))
($test (parse* "^X.(^X.X)") (^ x (^ x x)))
($test (parse* "end") end)
($test (parse* "(^X.X)(^Y.Y)") ((^ x x)(^ y y)))
($test (parse* "^XY.Z") (^ x (^ y z)))
($test (parse* "^XYZ.Z") (^ X (^ Y (^ Z Z))))
($test (parse* "(XY)Z") ((x y) z))
($test (parse* "X(YZ)") (x (y z)))
($test (parse* "ABCD") (((a b) c) d))
($test (parse* "A(B(C(D)))") (a (b (c d))))

($test (reduce 'y) y)
($test (reduce '(x y)) (x y))
($test (reduce '((^ x x) y) ) y)
($test (reduce '((^ x a) y) ) a)

