;;
;; translater from string to sexp
;; "1+2" -> (1 + 2)


(defun delimiter (x)
    (or (char= x #\+) 
        (char= x #\-)
        (char= x #\*)
        (char= x #\/)))

(defglobal *rest-list* nil)

(defun parse (x)
    (parse1 (convert x <list>) nil))

(defun convert-token (x)
    (let ((y (reverse x)))
        (convert (convert-token1 y) <symbol>)))

(defun convert-token1 (x)
    (cond ((null x) "")
          (t (string-append (convert (car x) <string>) (convert-token1 (cdr x))))))


(defun parse1 (x token)
    (cond ((null x) (list (convert-token token)))
          ((delimiter (car x)) (cons (convert-token token) (cons (convert (car x) <symbol>) (parse1 (cdr x) nil))))
          ((char= (car x) #\() (cons (convert-token token) (parse1 (cdr x) nil) (parse1 *rest-list* nil)))
          ((char= (car x) #\)) (setq *rest-list* (cdr x)) nil)
          (t (parse1 (cdr x) (cons (car x) token)))))