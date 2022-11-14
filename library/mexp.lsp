#|
idea memo
from John allen book and Masakazu Nakanishi book
* function e.g.  sin[x]
* argument e.g. [x;y;z]
* S-expression ()  e.g. (A B C)  (A . B)
* cond clause e.g. [odd[x]->t;t->nil]
* data structure 
* each function return list (value . rest-buffer)
* 
* tokenize e.g. "sin[x]" -> "sin" "[" "x" "]"
*               "( a b c)" -> "(" "a" "b" "c" ")"
|#

(defmodule meta
    (import "formula" infix->prefix string->infix)
    
    (defglobal epilog nil)

    (defun cadr (x)
        (car (cdr x)) )

    (defun cddr (x)
        (cdr (cdr x)) )

    (defun val (x)
        (car x) )

    (defun rest (x)
        (cdr x) )

    (defpublic mexp ()
        (format (standard-output) "Meta expression translator~%")
        (repl) )

    (defun repl ()
       (for ( )
            (epilog (setq epilog nil) 'goobye)
            (format (standard-output) "M> ")
            (let ((s (val (mread nil (standard-input)))))
               (let ((res (catch 'exit
                                 (with-handler 
                                     (lambda (c) (throw 'exit c))
                                     (cond ((equal s '(quit)) (setq epilog t))
                                           ((and (consp s) (eq (elt s 0) 'load)) (load* (elt s 1)))
                                           ((and (consp s) (eq (elt s 0) 'sexp)) (sexp (elt s 1)))
                                           (t (eval s)))))))
                  (cond ((instancep res (class <error>)) 
                         (format (standard-output) "System error ~A~%" (class-of res)))
                        ((not (eq res 'error)) (print res)))) )))
                        

    (defun error* (msg arg)
        (format (standard-output) "~A ~A~%" msg arg)
        (throw 'exit 'error))

    (defun mread (buffer stream)
        (cond ;; file end
              ((and (stringp buffer)(string= buffer "the end")) (cons buffer nil)) 
              ;; buffer empty
              ((null buffer) (mread (tokenize (read-line stream nil "the end")) stream))
              ;; comment line
              ((string= (car buffer) ";") (mread (tokenize (read-line stream nil "the end")) stream))
              ;; string
              ((string-str-p (car buffer)) (cons (make-string (car buffer)) (cdr buffer)))
              ;; cond clause [x->x1;y->y1;z->z1]                    
              ((string= (car buffer) "[") (mread-cond (cdr buffer) stream nil))
              ;; S-expression
              ((string= (car buffer) "(")
               (let* ((result (sread (cdr buffer) stream nil))
                      (sexp (val result))
                      (buffer* (rest result)))
                 (cons (list 'quote sexp) buffer*)))
              ;; definition e.g. foo[x] <= x+1
              ((and (>= (length buffer) 5) (string= (cadr buffer) "[") (member "<=" buffer))
               (let* ((result0 (mread-argument (cdr (cdr buffer)) stream nil))
                      (fn (make-symbol (car buffer)))
                      (arg (val result0))
                      (dummy (eval (list 'defun fn arg))) ;for recursive call
                      (buffer* (rest result0))
                      (result1 (mread (cdr buffer*) stream))
                      (body (val result1))
                      (buffer** (rest result1)) )
                   (cons (list 'defun fn arg body) buffer**)))
              ;; load["filename"], sexp["filename"], quit[]
              ((or (and (>= (length buffer) 4) (string= (car buffer) "load"))
                   (and (>= (length buffer) 4) (string= (car buffer) "sexp"))
                   (and (>= (length buffer) 4) (string= (car buffer) "string-append"))
                   (and (>= (length buffer) 3) (string= (car buffer) "quit")))
               (let* ((result (mread-argument (cdr (cdr buffer)) stream nil))
                      (fn (make-symbol (car buffer)))
                      (arg (val result))
                      (buffer* (rest result)))
                    (cons (cons fn arg) buffer*)))
              ;; formula e.g. sin[x]+cos[x]
              (t (let* ((result (mread-formula buffer stream ""))
                        (formula (val result))
                        (buffer* (rest result)))
                    (cons (infix->prefix (string->infix formula)) buffer*)))))

    ;; e.g. ("foo" "[" "2" ";" "4" "]" "+bar" "[" "3" "]" "->") 
    ;;   -> "foo(2,4)+bar(3)"  rest=("->") 
    (defun mread-formula (buffer stream res)
        (cond ((null buffer) (cons res buffer))
              ((string= (car buffer) "->") (cons res buffer))
              ((string= (car buffer) ";") (cons res buffer))
              ((string= (car buffer) "]") (cons res buffer))
              ((string= (car buffer) "[") (let* ((result (mread-formula1 (cdr buffer) stream "("))
                                                 (arg (val result))
                                                 (buffer* (rest result)))
                                            (mread-formula buffer* stream (string-append res arg))))
              (t (mread-formula (cdr buffer) stream (string-append res (car buffer))))))
    
    ;; e.g. ("2" ";" "4" "]" "+bar" "[" "3" "]" "->")
    ;;   -> "(2.4)" rest= ("+bar" "[" "3" "]" "->")
    (defun mread-formula1 (buffer stream res)
        (cond ((null buffer) (mread-formula1 (tokenize (read-line stream nil "the end")) stream))
              ((string= (car buffer) "]") (cons (string-append res ")") (cdr buffer)))
              ((string= (car buffer) ";") (mread-formula1 (cdr buffer) stream (string-append res ",")))
              ((string= (car buffer) "[") (let* ((result (mread-formula1 (cdr buffer) stream "("))
                                                 (arg (val result))
                                                 (buffer* (rest result)))
                                            (mread-formula1 buffer* stream (string-append res arg))))
              (t (mread-formula1 (cdr buffer) stream (string-append res (car buffer))))))


    (defun mread-cond (buffer stream res)
        (cond ((null buffer) (mread-cond (tokenize (read-line stream nil "the end")) stream res))
              ((string= (car buffer) "]") (cons (cons 'cond (reverse res)) (cdr buffer)))
              ((string= (car buffer) "->") (mread (cdr buffer) stream))
              ((string= (car buffer) ";") (mread-cond (cdr buffer) stream res))
              (t
               (let* ((result0 (mread buffer stream))
                      (exp0 (val result0))
                      (buffer* (rest result0))
                      (result1 (mread-cond buffer* stream nil))
                      (exp1 (val result1))
                      (buffer** (rest result1)) )
                   (mread-cond buffer** stream (cons (list exp0 exp1) res))))))

    (defun mread-argument (buffer stream res)
        (cond ((null buffer) (mread (tokenize (read-line stream nil "the end")) stream))
              ((string= (car buffer) "]") (cons (reverse res) (cdr buffer)))
              ((string= (car buffer) ";") (mread-argument (cdr buffer) stream res))
              (t
               (let ((result (mread buffer stream)))
                  (mread-argument (rest result) stream (cons (val result) res))))))

    (defun sread (buffer stream res)
        (cond ((string= (car buffer) ")") (cons (reverse res) (cdr buffer)))
              ((string= (car buffer) ".")
               (let* ((result (sread (cdr buffer) stream nil))
                      (sexp (val result))
                      (buffer* (rest result)))     
                  (cons (cons (car res) (car sexp)) buffer*)))
              ((float-str-p (car buffer))
               (sread (cdr buffer) stream (cons (convert (car buffer) <float>) res)))
              ((integer-str-p (car buffer))
               (sread (cdr buffer) stream (cons (convert (car buffer) <integer>) res)))
              (t (sread (cdr buffer) stream (cons (make-symbol (car buffer)) res)))))

    (defun make-symbol (str)
        (convert (to-upper-string (convert str <list>)) <symbol>))

    (defun make-string (str)
        (make-string1 (reverse (cdr (reverse (cdr (convert str <list>)))))))

    (defun make-string1 (ls)
        (cond ((null ls) "")
              (t (string-append (convert (car ls) <string>) (make-string1 (cdr ls))))))

    (defun to-upper-string (ls)
        (if (null ls)
            ""
            (string-append (convert (to-upper (car ls)) <string>) (to-upper-string (cdr ls)))))

    (defun to-upper (x)
        (let ((ascii (convert x <integer>)))
           (if (and (>= ascii 97) (<= ascii 122))
               (convert (- ascii 32) <character>)
               x)))

    (defun tokenize (x)
        (if (string= x "the end")
            x
            (tokenize1 (convert x <list>) "" nil)))

    ;; tokenize as M-expression
    (defun tokenize1 (ls token res)
        (cond ((null ls) (if (string= token "")
                             (reverse res)
                             (reverse (cons token res))))
              ((char= (car ls) #\space) (tokenize1 (cdr ls) token res))
              ((char= (car ls) #\()
               (if (string= token "")
                   (tokenize2 (cdr ls) "" (cons (convert (car ls) <string>) res) 0)
                   (tokenize2 (cdr ls) "" (cons (convert (car ls) <string>) (cons token res)) 0)))
              ((delimiter-p (car ls))
               (if (string= token "")
                   (tokenize1 (cdr ls) "" (cons (convert (car ls) <string>) res))
                   (tokenize1 (cdr ls) "" (cons (convert (car ls) <string>) (cons token res)))))
              ((and (> (length ls) 1) (char= (car ls) #\<) (char= (cadr ls) #\=))
               (if (string= token "")
                   (tokenize1 (cddr ls) "" (cons "<=" res))
                   (tokenize1 (cddr ls) "" (cons "<=" (cons token res)))))
              ((and (> (length ls) 1) (char= (car ls) #\-) (char= (cadr ls) #\>))
               (if (string= token "")
                   (tokenize1 (cddr ls) "" (cons "->" res))
                   (tokenize1 (cddr ls) "" (cons "->" (cons token res)))))
              (t (tokenize1 (cdr ls) (string-append token (convert (car ls) <string>)) res))))

    (defun delimiter-p (x)
        (or (char= x #\[) (char= x #\]) (char= x #\;)))

    ;; tokenize as S-expression
    (defun tokenize2 (ls token res nest)
        (cond ((char= (car ls) #\()
               (if (string= token "")
                   (tokenize2 (cdr ls) "" (cons (convert (car ls) <string>) res) (+ nest 1))
                   (tokenize2
                    (cdr ls)
                    ""
                    (cons (convert (car ls) <string>) (cons token res))
                    (+ nest 1))))
              ((and (char= (car ls) #\)) (> nest 0))
               (if (string= token "")
                   (tokenize2 (cdr ls) "" (cons (convert (car ls) <string>) res) (+ nest 1))
                   (tokenize2
                    (cdr ls)
                    ""
                    (cons (convert (car ls) <string>) (cons token res))
                    (+ nest 1))))
              ((and (char= (car ls) #\)) (= nest 0))
               (if (string= token "")
                   (tokenize1 (cdr ls) "" (cons (convert (car ls) <string>) res))
                   (tokenize1 (cdr ls) "" (cons (convert (car ls) <string>) (cons token res)))))
              ((char= (car ls) #\space)
               (if (string= token "")
                   (tokenize2 (cdr ls) "" res nest)
                   (tokenize2
                    (cdr ls)
                    ""
                    (cons token res)
                    nest)))
              ((and (> (length ls) 1) (char= (car ls) #\space) (char= (cadr ls) #\.))
               (if (string= token "")
                   (tokenize2 (cdr ls) "" (cons (convert (cadr ls) <string>) res) nest)
                   (tokenize2
                    (cdr ls)
                    ""
                    (cons (convert (cadr ls) <string>) (cons token res))
                    nest)))
              (t (tokenize2 (cdr ls) (string-append token (convert (car ls) <string>)) res nest))))

    (defun s-delimiter-p (x)
        (or (char= x #\space) (char= x #\.)))

    
    (defun string-str-p (x)
        (and (char= (elt x 0) #\") (char= (elt x (- (length x) 1)) #\")))

    
    ;;is token integer-type?
    (defun integer-str-p (x)
        (cond ((and (char= (elt x 0) #\+) (number-char-p (elt x 1))) t)
              ((and (char= (elt x 0) #\-) (number-char-p (elt x 1))) t)
              ((number-char-p (elt x 0)) t)
              (t nil)))

    (defun number-char-p (x)
        (and (char>= x #\0) (char<= x #\9)))

    ;;is token float-type?
    (defun float-str-p (x)
        (cond ((and (integer-str-p x) (string-index "." x)) t)
              ((and (integer-str-p x) (string-index "e" x)) t)
              (t nil)))

    (defun load* (filename)
        (let ((instream (open-input-file filename))
              (sexp nil))
           (while (not (file-end-p sexp))
              (setq sexp (val (mread nil instream)))
              (eval sexp))
           (close instream))
        t)

    (defun sexp (filename)
        (let* ((filename* (string-append (subseq filename 0 (char-index #\. filename)) ".lsp"))
               (instream (open-input-file filename))
               (outstream (open-output-file filename*))
               (sexp nil))
           (while (not (file-end-p sexp))
              (setq sexp (val (mread nil instream)))
              (if (not (file-end-p sexp))
                  (format outstream "~A~%" sexp)))
           (close instream)
           (close outstream))
        t)

    (defun file-end-p (x)
        (and (stringp x) (string= x "the end")))

)

