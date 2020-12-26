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
                 ((and (stringp (car x)) (string= (car x) "defun")) (pp-defun x lm))
                 ((< (+ (flatsize x) lm) width) (pp-flat x lm))
                 (t (pp-indent x lm))))
          ((null x) (pp-string "()"))
          ((string= x "") (format output-stream "~%"))
          ((char= (elt x 0) #\;) (pp-string x)(newline lm))
          (t (pp-string x))))

;; write symbol number string object
(defun pp-string (x)
    (format output-stream x))

;; syntax cond
(defun pp-cond (x lm)
    (pp-string "(cond ")
    (pp-indent (cdr x) (+ lm 6))
    (pp-string " )"))

;;syntax if
(defun pp-if (x lm)
  (let ((lm1 (+ lm 4)))
    (pp-string "(if ")
    (pp1 (elt x 1) lm1)
    (newline lm1)
    (pp1 (elt x 2) lm1)
    (newline lm1)
    (pp1 (elt x 3) lm1)
    (pp-string " )")))

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



;; write cons as flat
(defun pp-flat (x lm)
  (pp-string "(")
  (for ((s x (cdr s)))
       ((null s) (pp-string ")"))
       (if (stringp (car s))
           (pp-string (car s))
           (pp1 (car s) lm))
       (if (not (null (cdr s)))
           (pp-string " "))))

;; write cons with indent
(defun pp-indent (x lm)
  (pp-string "(")
  (for ((s x (cdr s)))
       ((null s) (pp-string ")")) 
       (if (stringp (car s))
           (pp-string (car s))
           (pp1 (car s) lm))
       (if (not (null (cdr s)))
           (newline lm))))




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
;;if file-end return #\null
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
            ((delimiterp char) char)                        ;;delimiter
            ((char= char #\")                               ;;string
             (setq token (cons char token))
             (setq char (getc))
             (while (not (char= char #\"))
                    (setq token (cons char token))
                    (setq char (getc)))
             (setq token (cons char token))
             (convert-to-string (reverse token))) 
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
             (setq input (read-line input-stream nil #\null))
             (cond ((end-of-file-p input)
                    (return-from exit #\null))
                   ((string= input "")
                    (return-from exit input))
                   (t (setq buffer (append (convert input <list>) '(#\newline))))))
      
      (setq result (car buffer))
      (setq buffer (cdr buffer))
      result)))

;; unget character to buffer
(defun ungetc (x)
  (setq buffer (cons x buffer)))


(defun end-of-file-p (x)
  (if (and (characterp x)(char= x #\null))
      t
      nil))


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
