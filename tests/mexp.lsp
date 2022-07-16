 
(import "formula")

(defun cadr (x)
    (car (cdr x)))

(defun val (x)
    (car x))

(defun rest (x)
    (cdr x))

(defun parse (buffer stream)
    (cond ((null buffer) (cond ((eq stream 'stdin) (parse (tokenize (read-line)) stream))
                               ((eq stream 'filein) t)))
          ;; list [1;2;3]                    
          ((string= (car buffer) "[") (parse-bracket (cdr buffer) stream))
          ;; function e.g. sin[x] or difinition e.g. foo[x] = x
          ((and (> (length buffer) 1) (string= (cadr buffer) "["))
           (let* ((result0 (parse-bracket (cdr (cdr buffer)) stream nil))
                  (func (cons (convert (car buffer) <symbol>) (val result0))))
                    (cond ((and (> (length buffer) 1) (string= (car buffer) "="))
                           (let ((result1 (parse (rest result) stream)))
                              (cons (cons 'defun (cons func (val result1))) (rest result1))))
                          (t (cons func (rest result0))))))
          ;; formula 
          (t (cons (infix->prefix (string->infix (car buffer))) (cdr buffer)))))



(defun parse-bracket (buffer stream res)
    (cond ((null buffer) (cond ((eq stream 'stdin) (parse (tokenize (read-line)) stream))
                               ((eq stream 'filein) t)))
          ((string= (car buffer) "]") (cons (reverse res) (cdr buffer)))
          ((string= (car buffer) ";") (parse-bracket (cdr buffer) stream res))
          (t (let ((result (parse buffer stream)))
                (parse-bracket (rest result) stream (cons (val result) res))))))

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
        (char= x #\newline)))


