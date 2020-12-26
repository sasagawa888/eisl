;;
;; pretty printer for ISLisp

(defconstant width 100)
(defglobal buffer nil)
(defglobal input-stream (standard-input))
(defglobal output-stream (standard-output))

(defun formatter (file)
  (let ((exp nil))
    (setq input-stream (open-input-file file))
    (setq exp (sexp-read))
    (while (not (end-of-file-p exp))
           (pp1 exp 0)
           ;(print exp)
           (setq exp (sexp-read)))
    (close input-stream)
    (setq input-stream (standard-input))
    t))


(defun pp ()
    (pp1 (sexp-read) 0))

(defun pp1 (x lm)
    (cond ((consp x)
           (cond ((and (stringp (car x)) (string= (car x) "cond")) (pp-cond x lm))
                 ((and (stringp (car x)) (string= (car x) "if")) (pp-if x lm))
                 ((and (stringp (car x)) (string= (car x) "let")) (pp-let x lm))
                 ((and (stringp (car x)) (string= (car x) "defun")) (pp-defun x lm))
                 ((and (stringp (car x)) (string= (car x) "defconstant")) (pp-defconstant x lm))
                 ((and (stringp (car x)) (string= (car x) "defglobal")) (pp-defglobal x lm))
                 ((and (stringp (car x)) (string= (car x) "defgeneric")) (pp-defgeneric x lm))
                 ((and (stringp (car x)) (string= (car x) "defmacro")) (pp-defmacro x lm))
                 ((< (+ (flatsize x) lm) width) (pp-flat x lm))
                 (t (pp-indent x lm))))
          ((null x) (pp-string "()"))
          ((characterp x)) ;; bug???
          ((string= x "") (format output-stream "~%"))
          ((comment-p x) (pp-string x)(newline lm))
          ;((vector-p x) (pp-vector x))
          ;((array-p x) (pp-array x))
          (t (pp-string x))))

;; write symbol number string object
(defun pp-string (x)
    (format output-stream x))

;; syntax cond
(defun pp-cond (x lm)
    (pp-string "(cond ")
    (pp-cond1 (cdr x) (+ lm 6))
    (pp-string " )"))

(defun pp-cond1 (x lm)
  (for ((s x (cdr s)))
       ((null s) t)
       (if (stringp (car s))
           (pp-string (car s))
           (pp1 (car s) lm))
       (if (not (null (cdr s)))
           (newline lm))))


;;syntax if
(defun pp-if (x lm)
  (let ((lm1 (+ lm 4)))
    (cond ((= (length x) 4)
           (pp-string "(if ")
           (pp1 (elt x 1) lm1)
           (newline lm1)
           (pp1 (elt x 2) lm1)
           (newline lm1)
           (pp1 (elt x 3) lm1)
           (pp-string " )"))
          (t (pp-string "(if ")
           (pp1 (elt x 1) lm1)
           (newline lm1)
           (pp1 (elt x 2) lm1)
           (pp-string " )")))))

;;syntax defun
(defun pp-defun (x lm)
  (let ((lm1 (+ lm 2)))
    (pp-string "(defun ")
    (pp1 (elt x 1) lm1)
    (pp-string " ")
    (pp1 (elt x 2) lm1)
    (newline lm1)
    (pp-body (cdr (cdr (cdr x))) lm1)
    (pp-string ")" )
    (newline lm)))

;; syntax defun body
(defun pp-body (x lm)
  (for ((s x (cdr s)))
       ((null s) t) 
       (if (stringp (car s))
           (pp-string (car s))
           (pp1 (car s) lm))
       (if (not (null (cdr s)))
           (newline lm))))

;; syntax let
(defun pp-let (x lm)
  (let ((lm1 (+ lm 5))
        (lm2 (+ lm 3)))
    (pp-string "(let ")
    (pp-let1 (elt x 1) lm1)
    (newline lm2)
    (pp-body (cdr (cdr x)) lm2)
    (pp-string " )" )))
  
(defun pp-let1 (x lm)
  (pp-string "(")
  (for ((s x (cdr s)))
       ((null s) (pp-string " )")) 
       (if (stringp (car s))
           (pp-string (car s))
           (pp1 (car s) lm))
       (if (not (null (cdr s)))
           (newline (+ lm 1)))))


;;syntax defgeneric
(defun pp-defgeneric (x lm)
  (let ((lm1 (+ lm 2)))
    (pp-string "(defgeneric ")
    (pp1 (elt x 1) lm1)
    (pp-string " ")
    (pp1 (elt x 2) lm1)
    (newline lm1)
    (pp-body (cdr (cdr (cdr x))) lm1)
    (pp-string ")" )
    (newline lm)))

;;syntax defgeneric
(defun pp-defmacro (x lm)
  (let ((lm1 (+ lm 2)))
    (pp-string "(defmacro ")
    (pp1 (elt x 1) lm1)
    (pp-string " ")
    (pp1 (elt x 2) lm1)
    (newline lm1)
    (pp-body (cdr (cdr (cdr x))) lm1)
    (pp-string ")" )
    (newline lm)))


;; syntax defconstant
(defun pp-defconstant (x lm)
    (pp-string "(defconstant ")
    (pp1 (elt x 1) lm)
    (pp-string " ")
    (pp1 (elt x 2) lm)
    (pp-string ")" )
    (newline lm))

;; syntax defglobal
(defun pp-defglobal (x lm)
    (pp-string "(defglobal ")
    (pp1 (elt x 1) lm)
    (pp-string " ")
    (pp1 (elt x 2) lm)
    (pp-string ")" )
    (newline lm))


;; write cons as flat
(defun pp-flat (x lm)
  (pp-string "(")
  (for ((s x (cdr s)))
       ((null s) 
        (pp-string ")"))
       (if (stringp (car s))
           (pp-string (car s))
           (pp1 (car s) lm))
       (if (not (null (cdr s)))
           (pp-string " "))))

;; write cons with indent
(defun pp-indent (x lm)
  (pp-string "(")
  (for ((s x (cdr s)))
       ((null s) (pp-string " )")) 
       (if (stringp (car s))
           (pp-string (car s))
           (pp1 (car s) lm))
       (if (not (null (cdr s)))
           (newline (+ lm 3)))))




(defun space (n)
    (for ((m n (- m 1)))
         ((<= m 0) t)
         (format output-stream " ")))

(defun newline (lm)
    (format output-stream "~%")
    (space lm))
    

;; calculate size of character 
(defun flatsize (x)
  (cond ((null x) 1)
        ((characterp x) 0)
        ((stringp (car x))
         (+ (length (car x)) 1 (flatsize (cdr x))))
        (t (+ (flatsize (car x)) 1 (flatsize (cdr x))))))


;; read S-expression. each atom is represented as string
(defun sexp-read ()
  (let ((token (get-token)))
    (cond ((and (characterp token)(char= token #\())
           (sexp-read-list))
          (t token))))


(defun sexp-read-list ()
  (let ((token nil)
        (result nil))
    (setq token (get-token))
    (cond ((and (characterp token)(char= token #\))) nil)
          ((and (characterp token)(char= token #\())
           (cons (sexp-read-list)(sexp-read-list)))
          ((atom token)
           (cons token (sexp-read-list))))))

;;get token
;;if file-end return eof symbol
;;if delimiter return the character
;;else (symbol number string) return string 
(defun get-token ()
  (block exit
    (let ((token nil)
          (char nil))
      (setq char (getc))
      (cond ((skip-p char)                                  ;;newline skip
             (space-skip)(setq char (getc))))
      (cond ((skip-p char)                                  ;;space skip
             (space-skip)(setq char (getc))))
      (cond ((end-of-file-p char) (return-from exit char))  ;;EOF
            ((char= char #\null) "")                        ;;empty line
            ((delimiterp char) char)                        ;;delimiter
            ((char= char #\")                               ;;string
             (setq token (cons char token))
             (setq char (getc))
             (while (not (char= char #\"))
                    (setq token (cons char token))
                    (setq char (getc)))
             (setq token (cons char token))
             (convert-to-string (reverse token)))
            ((and (char= char #\#) (char= (look) #\\))
             (setq token (cons (getc) (cons char nil)))
             (setq token (cons (getc) token))
             (setq char (getc))
             (while (not (delimiterp char))                 
                      (setq token (cons char token))
                      (setq char (getc)))
             (ungetc char)
             (convert-to-string (reverse token)))    ;; character
            ((char= char #\#)                               
             (while (not (delimiterp char))                 
                      (setq token (cons char token))
                      (setq char (getc)))
             (ungetc char)
             (setq token (reverse token))
             (cond ((member (elt token 1) '(#\X #\B #\O))
                    (convert-to-string token))  ;;hex oct bin integer
                 (cons (convert-to-string token) (sexp-read)))) ;;vector array
            ((char= char #\;)                               ;;comment
             (setq token (cons char token))
             (setq char (getc))
             (while (not (char= char #\newline))
                    (setq token (cons char token))
                    (setq char (getc)))
             (ungetc char)
             (convert-to-string (reverse token))) 
            (t (while (not (delimiterp char))               ;;atom
                      (setq token (cons char token))
                      (setq char (getc)))
               (ungetc char)
               (convert-to-string (reverse token)))))))


(defun space-skip ()
  ;;space skip
  (while (and (not (null buffer))
              (or (char= (car buffer) #\space)
                  (char= (car buffer) #\tab)
                  (char= (car buffer) #\newline)))
    (setq buffer (cdr buffer))))

;; convert atom to string
(defun convert-to-string (ls)
  (if (null ls)
      ""
      (string-append (convert (car ls) <string>)
                     (convert-to-string (cdr ls)))))


;; get one character from stream
(defun getc ()
  (block exit
    (let ((input nil)
          (result nil))
      (while (null buffer)
             (setq input (read-line input-stream nil 'eof))
             (cond ((end-of-file-p input)
                    (return-from exit 'eof))
                   ((string= input "") 
                    (return-from exit #\null))
                   (t (setq buffer (append (convert input <list>) '(#\newline))))))
      
      (setq result (car buffer))
      (setq buffer (cdr buffer))
      result)))

;; unget character to buffer
(defun ungetc (x)
  (setq buffer (cons x buffer)))

(defun look ()
  (car buffer))


(defun end-of-file-p (x)
  (eq x 'eof))


(defun delimiterp (c)
  (if (and (characterp c)
           (member c '(#\space #\newline #\( #\))))
      t
      nil))

(defun skip-p (c)
  (if (and (characterp c)
           (member c '(#\space #\newline)))
      t
      nil))

(defun comment-p (x)
  (char= (elt x 0) #\;)) 