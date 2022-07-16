 
(import "formula")

(defglobal buffer nil)

(defun cadr (x)
    (car (cdr x)))

(defun parse (stream)
    (cond ((null buffer) (cond ((eq stream 'stdin) (setq buffer (tokenize (read-line))) (parse stream))
                               ((eq stream 'filein) t)))
          ((string= (car buffer) "[") (parse-bracket (cdr buffer) stream))
          ((and (> (length buffer) 1) (string= (cadr buffer) "["))
           (let ((func (cons (convert (car buffer) <symbol>)  (parse-bracket (cdr (cdr buffer)) stream))))
               (cond ((string= (elt buffer 0) "=")
                      (setq buffer (cdr buffer))
                      (cons 'defun (cons func (parse stream))))
                     (t func))))
          (t (let ((exp (car buffer)))
                (setq buffer (cdr buffer)) 
                (infix->prefix (string->infix exp))))))



(defun parse-bracket (stream res)
    (cond ((null buffer) (cond ((eq stream 'stdin) (setq buffer (tokenize (read-line))) (parse stream))
                               ((eq stream 'filein) t)))
          ((string= (car buffer) "]") (reverse res))
          (()))) 

(defun tokenize (x)
    (tokenize1 (convert x <list>) "" nil))

(defun tokenize1 (ls token res)
    (cond ((null ls) (reverse (cons token res)))
          ((delimiter-p (car ls)) (tokenize1 (cdr ls)
                                                 ""
                                                 (cons (convert (car ls) <string>) (cons token res))))
          (t (tokenize1 (cdr ls) (string-append token (convert (car ls) <string>)) res))))

(defun delimiter-p (x)
    (or (char= x #\[)
        (char= x #\])
        (char= x #\()
        (char= x #\))
        (char= x #\,)
        (char= x #\;)
        (char= x #\n)))


