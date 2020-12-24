;;
;; pretty printer for ISLisp

(defglobal lp 0) ;;left-position
(defglobal buffer nil)
(defglobal input-stream (standard-input))


(defun pp (x)
    (pp1 x (standard-output) 0))

(defun pp1 (x stream lm)
    (cond ((consp x)
           (cond ((eq (car x) 'cond) (pp-cond x stream lm))
                 ((eq (car x) 'defun) (pp-defun x stream lm))
                 (t (space lm stream) (format stream "~S" x))))
          ((numberp x) (space lm stream) (format-object stream x t))))


(defun pp-write-string (x stream)
    (setq lp (+ lp (length x)))
    (format stream x))

(defun pp-cond (x stream lm)
    (space lm stream)
    (pp-write-string "(cond (" stream)
    (pp-body (cdr x) stream (+ lm 7))
    (pp-write-string stream ")"))

(defun pp-defun (x stream lm)
    (space lm stream)
    (format stream "(defun ")
    (format-object stream (elt x 1) t)
    (format-object stream (elt x 2) t)
    (newline stream)
    (pp-body (cdr (cdr (cdr x))) stream (+ lm 2))
    (pp-write-string ")" stream))

(defun pp-body (x stream lm)
    (for ((s x (cdr s))
          (n (length x) (- n 1)))
         ((null s) t)
         (pp1 (car s) stream lm)
         (if (> n 1)
            (newline stream))))


(defun space (n stream)
    (for ((m (- n lp) (- m 1)))
         ((<= m 0) t)
         (format stream " ")))

(defun newline (stream)
    (setq lp 0)
    (format stream "~%"))



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
          ((char= (look) #\.)
           (get-token)
           (setq result (cons token (sexp-read)))
           (get-token)
           result)
          ((atom token)
           (cons token (sexp-read-list))))))

;;トークンを読み取る。
;;　1.1のようにピリオドの後が空でない場合には浮動小数点数と考える
;;  1e-1 のような形式の浮動小数点数を切り出す。
;;[]()のような区切り記号に達した場合にはその文字をバッファに戻す
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
            ((operator-char-p char)
             (cond ((and (char= char #\-)(char= (look) #\>))
                    (getc)
                    '->)
                    (t (convert-to-string (list char)))))
            ((char= char #\")
             (setq token (cons char token))
             (setq char (getc))
             (while (not (char= char #\"))
                    (setq token (cons char token))
                    (setq char (getc)))
             (setq token (cons char token))
             (convert-to-string (reverse token)))
            (t (while (and (not (delimiterp char))
                           (not (operator-char-p char)))
                      (setq token (cons char token))
                      (setq char (getc)))
               (cond ((and (char= char #\.)(not (null buffer))(number-char-p (look)))
                      (setq token (cons char token))
                      (setq char (getc))
                      (while (and (not (delimiterp char))
                                  (not (operator-char-p char)))
                             (setq token (cons char token))
                             (setq char (getc))))
                     ((and (char= char #\+)(char= (car token) #\e))
                      (setq token (cons char token))
                      (setq char (getc))
                      (while (and (not (delimiterp char))
                                  (not (operator-char-p char)))
                             (setq token (cons char token))
                             (setq char (getc))))
                     ((and (char= char #\-)(char= (car token) #\e))
                      (setq token (cons char token))
                      (setq char (getc))
                      (while (and (not (delimiterp char))
                                  (not (operator-char-p char)))
                             (setq token (cons char token))
                             (setq char (getc)))))
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
           (member c '(#\space #\[ #\] #\( #\) #\; #\, #\' #\.)))
      t
      nil))

;;演算子の文字のときにtを、そうでなければnilを返す
(defun operator-char-p (c)
  (if (and (characterp c)(member c '(#\+ #\- #\* #\/ #\^)))
      t
      nil))

;;バッファの先頭要素を覗き見る
;;バッファが空ならばピリオド文字を返す
(defun look ()
  (block exit
    (let ((max (length buffer)))
      (if (null buffer)
          (return-from exit #\.))
      (for ((pos 0 (+ pos 1)))
           ((>= pos max) nil)
           (if (not (char= (elt buffer pos) #\space))
               (return-from exit (elt buffer pos)))))))
