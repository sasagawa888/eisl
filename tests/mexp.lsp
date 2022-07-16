 
#|
idea memo
parse   e.g. sin[x]+cos[x]
step1
operator ()
operand  ((sin x))
step2
operator (+)
operand  ((sin x))
step3
operator (+)
operand ((sin x)(cos x))

terminal
when parse get null buffer, stop parsing
|#

(defun cadr (x)
    (car (cdr x)))

(defun val (x)
    (car x))

(defun rest (x)
    (cdr x))

(defun mexp ()
  (initialize)
  (repl))

(defun repl ()
  (block repl
    (cond ((catch 'exit
             (for ((s (val (mread nil 'stdin)) (val (mread nil 'stdin))))
                  ((equal s '(quit)) (return-from repl t))
                  (print (eval s))
                  (if (and (consp s)(eq (elt s 0) 'load))
                      (format (standard-output) "~A~%" (ignore-errors (load* (elt s 1))))
                      (format (standard-output) "~A~%" (ignore-errors (eval s))))
                  (prompt))) t)
          (t (prompt)(repl)))))


(defun initialize ()
  (format (standard-output) "Meta expression translater~%")
  (prompt))


(defun prompt ()
  (format (standard-output) "M> "))


(defun error* (msg arg)
  (format (standard-output) msg)
  (format (standard-output) "~A" arg)
  (format (standard-output) "~%")
  (if (not (eq input-stream (standard-input)))
      (close input-stream))
  (setq input-stream (standard-input))
  (throw 'exit nil))

(defglobal operator '(("+" '+)("-" '-)("*" '*)("/" 'quotient)))

(defun operator-p (x)
    (assoc x operator))

(defun parse (buffer stream operator operand)
    (cond ((null buffer) (cond ((eq stream 'stdin) (parse (tokenize (read-line)) stream))
                               ((eq stream 'filein) t)))
          (t t)))


(defun mread (buffer stream)
    (cond ((null buffer) (cond ((eq stream 'stdin) (mread (tokenize (read-line)) stream))
                               ((eq stream 'filein) t)))
          ((float-str-p (car buffer)) (cons (convert (car buffer) <float>) buffer))
          ((integer-str-p (car buffer)) (cons (convert (car buffer) <integer>) buffer))
          ;; list [1;2;3]                    
          ((string= (car buffer) "[") (mread-bracket (cdr buffer) stream))
          ;; function e.g. sin[x]
          ((and (> (length buffer) 1) (string= (cadr buffer) "["))
           (let* ((result0 (mread-bracket (cdr (cdr buffer)) stream nil))
                  (fn (make-symbol (car buffer)))
                  (arg (val result0))
                  (buffer* (rest result0)))
              (cons (cons fn arg) buffer*)))
          (t (error* "mread" (car buffer)))))



(defun mread-bracket (buffer stream res)
    (cond ((null buffer) (cond ((eq stream 'stdin) (mread (tokenize (read-line)) stream))
                               ((eq stream 'filein) t)))
          ((string= (car buffer) "]") (cons (reverse res) (cdr buffer)))
          ((string= (car buffer) ";") (mread-bracket (cdr buffer) stream res))
          (t (let ((result (mread buffer stream)))
                (mread-bracket (rest result) stream (cons (val result) res))))))


(defun make-symbol (str)
  (convert (to-upper-string (convert str <list>)) <symbol>))


(defun to-upper-string (ls)
  (if (null ls)
      ""
      (string-append (convert (to-upper (car ls)) <string>)
                     (to-upper-string (cdr ls)))))


(defun to-upper (x)
  (let ((ascii (convert x <integer>)))
    (if (and (>= ascii 97)(<= ascii 122))
        (convert (- ascii 32) <character>)
        x)))


(defun tokenize (x)
    (tokenize1 (convert x <list>) "" nil))

(defun tokenize1 (ls token res)
    (cond ((null ls) (if (string= token "") 
                         (reverse res)
                         (reverse (cons token res))))
          ((char= (car ls) #\space) (tokenize1 (cdr ls) token res))
          ((delimiter-p (car ls)) (if (string= token "")
                                      (tokenize1 (cdr ls)
                                                 ""
                                                 (cons (convert (car ls) <string>) res))
                                      (tokenize1 (cdr ls)
                                                 ""
                                                 (cons (convert (car ls) <string>) (cons token res)))))
          (t (tokenize1 (cdr ls) (string-append token (convert (car ls) <string>)) res))))

(defun delimiter-p (x)
    (or (char= x #\[)
        (char= x #\])
        (char= x #\()
        (char= x #\))
        (char= x #\=)
        (char= x #\,)
        (char= x #\;)))


;;is token string-type?
(defun string-str-p (x)
  (and (char= (elt x 0) #\")
       (char= (car (reverse (convert x <string>))) #\")))

;;is token integer-type?
(defun integer-str-p (x)
  (cond ((and (char= (elt x 0) #\+) (number-char-p (elt x 1))) t)
        ((and (char= (elt x 0) #\-) (number-char-p (elt x 1))) t)
        ((number-char-p (elt x 0)) t)
        (t nil)))

(defun number-char-p (x)
  (and (char>= x #\0)
       (char<= x #\9)))

;;is token float-type?
(defun float-str-p (x)
  (cond ((and (integer-str-p x) (string-index "." x)) t)
        ((and (integer-str-p x) (string-index "e" x)) t)
        (t nil)))


