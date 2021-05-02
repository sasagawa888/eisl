(import "elixir")


(defun cadr (x)
  (cdr (car x)))

(defun caar (x) 
  (car (car x)))

(defun caddr (x)
  (car (cdr (cdr x))))

(defun repl ()
  (format "Lambda calculus interpreter")
  (format "To quit enter 'end'")
  (repl))


(defun repl ()
  (block repl
    (cond ((catch 'exit
             (for ((s (read*) (read*)))
                  ((equal s 'end) (return-from repl t))
                  (print* (reduce (combinator s)))
                  (prompt))) t)
          (t (prompt)(repl)))))

(defun read* ()
  (format (standard-output) "~%L> ")
  (parse (convert (read-line) <list>) nil))

(defun print* (x)
  (if (eq (car x) '^)
      (print1* x)
      (print2* x)))

(defun print1* (x)
  (format (standard-output) "^")
  (format-object (standard-output) (cadr x))
  (format (standard-output) ".")
  (print* (caddr x)))

(defun print2* (x)
  (print1* (car x))
  (print1* (cadr x)))


  ;; for test
  (defun test (x)
    (pipe (parse x nil) |> (combinator) |> (reduce)))
 
#|
parse 
 ^x.x -> (^ x x)
 (^x.x)(^y.y) -> ((^ x x)(^ y y))

input char-list  respons
return (body . rest-list)
|#

(defpattern parse
  ((empty _res) _res)
  (((#\e #\n #\d) _res) 'end)
  (((#\^ _arg #\. :rest _ls)) (let* ((arg1 (convert _arg <symbol>))
                                     (dt (parse _ls nil))
                                     (body (car dt))
                                     (ls1 (cdr dt)))
                                  (parse ls1 (cons '^ (list arg1 body)))))
  ;; e.g. ^xyz.z shorthand
  (((#\^ _arg :rest _ls) _) (let* ((arg1 (convert _arg <symbol>)))
                               (cons '^ (list arg1 (parse (cons #\^ _ls) nil)))))
  ;; ( )
  (((#\( :rest ls) _res) (let* ((dt (parse (cons #\( ls) nil))
                                (exp (car dt))
                                (ls1 (cdr dt)))
                            (cond ((null _res) (parse ls1 exp))
                                  (t (parse ls1 (append (list _res) (list exp)))))))
  ;; space skip
  (((#\space :rest ls) _res) (parse ls res))
  (((_body :rest _ls)) (cons (convert _body <symbol>) _ls))
  (else (throw 'exit "syntax error")))


(defun newline ()
  (format (standard-output) "~%"))

(defun is-lambda (x)
  (and (consp x) (eq (car) '^)))

(defpattern combinator
  ((I) `(^ x x))
  ((K) '(^ x (^ y x)))
  ((S) '(^ x (^ y (^ z ((^ x z), (^ y z))))))
  ((Y) '(^ y ((^ x (^ y (^ x x))) (^ x (^ y (^ x x))))))
  (((_x _y))  (append (combinator _x) (combinator _y)))
  ((_x) _x))


(defun reduce (x)
    (cond ((eq x 'end) (throw 'exit "end"))
          ((atom x) x)
          ((and (consp x) (is_lambda (car x)))
           (print* x) (newline) (reduce (beta x)))
          ((and (consp x) (consp (car x)))
           (print* x) (newline) (if (cant-reduce x) x (reduce (list (reduce (car x)) (cadr x)))))
          ((is_lambda x) (newline) 
                         (list '^ (car x) (reduce (cadr x))))))


(defun cant-reduce (x)
  (cond ((atom x) t)
        ((and (consp x) (atomp (car x))) t)
        (t nil)))


(defpattern replace 
    ((_x (_x _ys) _z) (list _z (replace _x _ys _z)))
    ((_x (_y _ys) _z) (cond ((atom _x) (list _x (replace _x _ys _z)))
                            ((atom _y) (list _y (replace _x _ys _z)))
                            ((is-lambda _y) (list (replace _x _y _z) (replace _x _ys _z)))
                            ((consp y) (list (replace _x _y _z (replace _x _ys _z))))
                            (t (reduce (list _y _ys)))))
    ((_x (^ _arg _body) _z) (list '^ _arg (replace _x _body _z)))
    ((_ _y _) y))
