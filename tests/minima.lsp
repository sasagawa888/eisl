;;; Minima simple synbolic formula manipulation
;; usage 
;; invoke (minima)

;; derive
;; d(formula,var)
;; integra
;; int(formula,var)

(import "elixir")
(import "formula")

(defun minima ()
  (format (standard-output) "Minima Mathematics ~%")
  (format (standard-output) "To quit enter 'end'~%")
  (repl))


(defun repl ()
  (block repl
    (cond ((catch 'exit
             (for ((s (read*) (read*)))
                  ((equal s 'end) (return-from repl t))
                  (print* (simple (eval s))))))
          (t (repl1)))))

(defun read* ()
    (format (standard-output) "M> ")
    (infix->prefix (string->infix (read-line))))

(defun print* (x)
  (format (standard-output) "~A~%" (infix->string (prefix->infix x))))


(defmacro d (x y)
  `(derive ',x ',y))

(defmacro int (x y)
  `(integra ',x ',y))

(defpattern derive
    (((expt _x _n) _x) `(* ,_n (^ ,_x ,(- _n 1))))
    (((quotient 1 _x) _x)  `(/ -1 (^ ,_x 2)))
    (((sqrt _x) _x) `(/ 1 (* 2 sqrt(,_x))))
    (((sin _x) _x)  `(cos ,_x))
    (((cos _x) _x)  `(- (sin ,_x)))
    (((tan _x) _x)  `(/ 1 (^ (cos ,_x) 2)))
    (((exp _x) _x)  `(exp ,_x))
    (((expt _a _x) _x) `(* (^ ,_a ,_x) (log ,_a)))
    (((log _x) _x)  `(/ 1 ,_x))
    (((log _a _x) _x)   `(/ 1 (* ,_x (log ,_a))))
    (((* _k (_f _x)) _x)(when (numberp _k))
                               (let ((d (derive `(,_f ,_x) `,_x)))
                                              `(* ,_k ,d)))
    (((+ (_f _x) (_g _x)) _x)  (let ((d1 (derive `(,_f ,_x) `,_x))
                                     (d2 (derive `(,_g ,_x) `,_x)))
                                 `(+ ,d1 ,d2)))
    (((* (_f _x) (_g _x)) _x)  (let ((d1 (derive `(,_f ,_x) `,_x))
                                     (d2 (derive `(,_g ,_x) `,_x)))
                                  `(+ (* ,d1 (,_g ,_x)) (* (,_f ,_x) ,d2))))
    (((quotient (_f _x) (_g _x)) _x)  (let ((d1 (derive `(,_f ,_x) `,_x))
                                     (d2 (derive `(,_g ,_x) `,_x)))
                                  `(quotient (+ (* ,d1 (,_g ,_x)) (* (,_f ,_x) ,d2 (expt (,_g ,_x) 2))))))
    (((_f (_g _x)) _x)  (let ((d1 (derive `(,_f ,_x) `,_x))
                              (d2 (derive `(,_g ,_x) `,_x)))
                            `(* ,d2 (,(car d1) (,_g ,_x)))))
    (else (format (standard-output) "error")))
    

    (defpattern simple
        (((+ _a 0)) '_a)
        (((+ 0 _a)) '_a)
        (((+ _a _a)) '(* 2 ,_a))
        (((* 0 _a))  0)
        (((* _a 0))  0)
        (((* 1 _a)) '_a)
        (((* _a 1)) '_a)
        (((* _a _a)) '(^ ,_a 2))
        (((/ 0 _a)) 0)
        (((/ _a _a)) 1)
        (((^ _a 0)) 1)
        (((^ _a 1)) _a)
        (((+ _a _b)) (list '+ (simple _a) (simple _b)))
        (((- _a _b)) (list '- (simple _a) (simple _b)))
        (((* _a _b)) (list '* (simple _a) (simple _b)))
        (((/ _a _b)) (list '* (simple _a) (simple _b)))
        ((_x) _x)) 


(defpattern integra
    ((_c _x) (when (numberp _c)) `(* _c _x))
    ((_x _x) `(/ (^ ,_x 2) 2))
    (((log x) _x) `(- (* ,_x (log ,_x)) ,_x))
    (((sin _x) _x) `(- (cos ,_x)))
    (((cos _x) _x) `(sin ,_x))
    (((tan _x) _x) `(- (log (cos ,_x))))
    (((cot _x) _x) `(log (sin ,_x))))


(defpattern limit
    (((quotient (log (+ 1 _x)) _x) _x 0) 1)
    (((quotient (sin _x) _x) _X 0) 1))
    