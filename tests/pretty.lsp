;;
;; pretty printer for ISLisp

(defglobal lp 0) ;;left-position
(defglobal buffer nil)
(defglobal input-stream (standard-input))
(defglobal output-stream (standard-output))


(defun pp ()
    (pp1 (sexp-read) 0))

(defun pp1 (x lm)
  (space lm)
    (cond ((consp x)
           (cond ((and (stringp (car x)) (string= (car x) "cond")) (pp-cond x lm))
                 ((and (stringp (car x)) (string= (car x) "defun")) (pp-defun x lm))
                 (t (pp-sexp x lm))))
          (t (format output-stream x))))


(defun pp-string (x)
    (setq lp (+ lp (length x)))
    (format output-stream x))

(defun pp-cond (x lm)
    (space lm)
    (pp-string "(cond ")
    (pp-body (cdr x) (+ lm 7))
    (pp-string ")"))

(defun pp-defun (x lm)
    (space lm)
    (pp-write-string "(defun ")
    (pp1 (elt x 1) lm)
    (pp-string " ")
    (pp1 (elt x 2) lm)
    (newline)
    (pp-body (cdr (cdr (cdr x))) (+ lm 2))
    (pp-string ")" ))

(defun pp-body (x lm)
    (for ((s x (cdr s))
          (n (length x) (- n 1)))
         ((null s) t)
         (pp1 (car s) lm)
         (if (> n 1)
            (newline))))

(defun pp-sexp (x lm)
  (space lm)
  (pp-string "(")
  (for ((s x (cdr s)))
       ((null s) (pp-string ")"))
       (if (stringp (car s))
           (pp-string (car s))
           (pp1 (car s) lm))
       (if (not (null (cdr s)))
           (pp-string " "))))



(defun space (n)
    (for ((m (- n lp) (- m 1)))
         ((<= m 0) t)
         (format output-stream " ")))

(defun newline ()
    (setq lp 0)
    (format output-stream "~%"))



;;S表現を読み取る
(defun sexp-read ()
  (let ((token (get-token)))
    (cond ((and (characterp token)(char= token #\())
           (sexp-read-list))
          (t token))))

;;S表現のリストを読み取る
(defun sexp-read-list ()
  (let ((token nil)
        (result nil))
    (setq token (get-token))
    (cond ((and (characterp token)(char= token #\))) nil)
          ((and (characterp token)(char= token #\())
           (cons (sexp-read-list)(sexp-read-list)))
          ((atom token)
           (cons token (sexp-read-list))))))

;;トークンを読み取る。
;;()のような区切り記号に達した場合にはその文字をバッファに戻す
;;end-of-fileの場合には"the end"を返す。
(defun get-token ()
  (block exit
    (let ((token nil)
          (char nil))
      (setq char (space-skip))
      (if (end-of-file-p char)
          (return-from exit char))
      (setq char (getc))
      (if (end-of-file-p char)
          (return-from exit char))
      (cond ((delimiterp char) char)
            ((char= char #\")
             (setq token (cons char token))
             (setq char (getc))
             (while (not (char= char #\"))
                    (setq token (cons char token))
                    (setq char (getc)))
             (setq token (cons char token))
             (convert-to-string (reverse token)))
            (t (while (not (delimiterp char))
                      (setq token (cons char token))
                      (setq char (getc)))
               (ungetc char)
               (convert-to-string (reverse token)))))))


;;文字リストを文字列に変換する。
;;シンボルは大文字に変換される
(defun convert-to-string (ls)
  (if (null ls)
      ""
      (string-append (convert (car ls) <string>)
                     (convert-to-string (cdr ls)))))



 ;;バッファから1文字を取り出す。バッファが空ならばストリームより読み取る
;; !マークがあった場合にはバッファを廃棄、新たな文字を読み取る
;;end-of-fileの場合には"the end"を返す。
(defun getc ()
  (block exit
    (let ((input nil)
          (result nil))
      (while (null buffer)
             (setq input (read-line input-stream nil "the end"))
             (if (end-of-file-p input)
                 (return-from exit "the end")
                 (setq buffer (convert input <list>))))
      (cond ((char= (car buffer) #\!)
             (setq input (read-line input-stream nil "the end"))
             (if (end-of-file-p input)
                 (return-from exit "the end")
                 (setq buffer (convert input <list>)))))
      (setq result (car buffer))
      (setq buffer (cdr buffer))
      result)))

;;1文字を戻す。
(defun ungetc (c)
  (setq buffer (cons c buffer)))


;;スペース文字お呼びタブ文字を読み飛ばす。
;;end-of-fileに達した場合には文字列"the end"を返す。
(defun space-skip ()
  (block exit
    (let ((char nil))
      (setq char (getc))
      (if (and (stringp char)(string= char "the end"))
          (return-from exit char))
      (while (or (char= char #\space)
                 (char= char #\tab))
             (setq char (getc))
             (if (and (stringp char)(string= char "the end"))
                 (return-from exit char)))
      (ungetc char))))

;;ファイルストリームの終わりであればtを、そうでなければnilを返す
(defun end-of-file-p (x)
  (if (and (stringp x)(string= x "the end"))
      t
      nil))

;;引数が区切り記号であればtを、そうでなければnilを返す
(defun delimiterp (c)
  (if (and (characterp c)
           (member c '(#\space #\( #\))))
      t
      nil))

