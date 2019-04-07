;;M言語からS表現への変換器


(defglobal buffer nil)
(defglobal input-stream (standard-input))

(set-property 500 'weight '+)
(set-property 500 'weight '-)
(set-property 400 'weight '*)
(set-property 400 'weight '/)
(set-property 300 'weight '^)
(set-property 'yfx 'type '+)
(set-property 'yfx 'type '-)
(set-property 'yfx 'type '*)
(set-property 'yfx 'type '/)
(set-property 'xfy 'type '^)
(set-property '+ 'sexp '+)
(set-property '- 'sexp '-)
(set-property '* 'sexp '*)
(set-property 'quotient 'sexp '/)
(set-property 'expt 'sexp '^)

(defun get-weight (x)
  (property 'weight x))

(defun get-type (x)
  (property 'type x))

(defun get-sexp (x)
  (property 'sexp x))

(defun mexp ()
  (initialize)
  (repl))

(defun repl ()
  (block repl
    (cond ((catch 'exit
             (for ((s (parse)(parse)))
                  ((equal s '(quit)) (return-from repl t))
                  (if (and (consp s)(eq (elt s 0) 'load))
                      (format (standard-output) "~A~%" (ignore-errors (load* (elt s 1))))
                      (format (standard-output) "~A~%" (ignore-errors (eval s))))
                  (prompt))) t)
          (t (prompt)(repl)))))

;;初期化
;;メッセージを表示し、プロンプトを表示する
(defun initialize ()
  (setq buffer nil)
  (format (standard-output) "Meta expression translater~%")
  (prompt))


;;プロンプトを表示する
(defun prompt ()
  (format (standard-output) "M> "))

;;エラー処理
(defun error* (msg arg)
  (format (standard-output) msg)
  (format (standard-output) "~A" arg)
  (format (standard-output) "~%")
  (setq buffer nil)
  (if (not (eq input-stream (standard-input)))
      (close input-stream))
  (setq input-stream (standard-input))
  (throw 'exit nil))

;;ファイルからM言語を読み取り、評価する
(defun load* (file)
  (let ((exp nil))
    (setq input-stream (open-input-file file))
    (setq exp (parse))
    (while (not (and (stringp exp)(string= exp "the end")))
           (eval exp)
           (setq exp (parse)))
    (close input-stream)
    (setq input-stream (standard-input))
    t))

;;M言語をストリームより読み込んでS式に変換する。
;;end-of-fileのときには文字列"the end"を返す。
(defun parse ()
  (let ((exp (mexp-read))
        (ope (get-token))
        (terminal nil))
    (cond ((and (stringp exp)(string= exp "the end")) exp) ;end of file
          ((and (symbolp ope) (eq ope '<=))
           (let ((result (list 'defun (car exp) (cdr exp) (mexp-read))))
             (setq terminal (get-token))
             (if (not (terminalp terminal))
                 (error* "Syntax error expected period " terminal))
             result))
          ((terminalp ope)
           exp)
          (t (error* "Syntax error " ope)))))

;;M言語を標準入力から読み取りS表現にして返す。
;;クォート記号を読み取った場合には直後はS表現とみなす。
;;ストリームからend-of-fileを受け取ったときには文字列"the end"を返す。
(defun mexp-read ()
  (let ((token (get-token))
        (result nil))
    (cond ((end-of-file-p token) token) ;end of file
          ((and (characterp token)(char= token #\[))
           (setq result (mexp-read-list))
           (if (eq (elt result 1) '->)
               (convert-to-cond result)
               result))
          ((and (symbolp token)(or (eq token 'lambda)
                                   (eq token '^)))
           (if (not (char= (get-token) #\[))
               (error* "Syntax error expected [" token))
           (if (not (char= (get-token) #\[))
               (error* "Syntax error expected ]" token))
           (setq result (list 'lambda (mexp-read-list) (mexp-read)))
           (if (not (char= (get-token) #\]))
               (error* "Syntax error expected ]" token))
           (cond ((char= (look) #\[)
                  (get-token)
                  (cons result (mexp-read-list)))))
          ((and (symbolp token)(char= (look) #\[))
           (get-token)
           (setq result (cons token (mexp-read-list)))
           (if (operator-char-p (look))
               (formula result (get-token))
               result))
          ((and (symbolp token)(operator-char-p (look)))
           (formula token (get-token)))
          ((symbolp token) token)
          ((and (numberp token)(operator-char-p (look)))
           (formula token (get-token)))
          ((and (characterp token)(char= token #\())
           (setq result (list 'quote (sexp-read-list)))
           (if (and (not (char= (look) #\.))
                    (not (char= (look) #\;))
                    (not (char= (look) #\])))
               (error* "Syntax error expected ; or ] " result))
           result)
          ((and (characterp token)(char= token #\'))
           (list 'quote (sexp-read)))
          ((delimiterp token)
           (error* "M-exp illegal object " token))
          (t token))))


(defun formula (operand1 operator)
  (formula1 operand1 (formula-read) operator (get-weight operator) (get-type operator)))

(defun formula1 (operand1 operand2 operator weight type)
  (let ((token (formula-read)))
    (cond ((end-of-file-p token) token)
          ((delimiterp token)
           (ungetc token)
           (list (get-sexp operator) operand1 operand2))
          ((and (operatorp token)(not (null operator))
                (> weight (get-weight token)))
           (formula1 operand1 (list (get-sexp token) operand2 (formula-read)) operator weight type))
          ((and (operatorp token)(not (null operator))
                (< weight (get-weight token)))
           (formula1 (list (get-sexp operator) operand1 operand2) (formula-read) token weight type))
          ((and (operatorp token)(not (null operator))
                (eq type 'yfx)(= (get-weight token) weight))
           (formula1 (list (get-sexp operator) operand1 operand2) (formula-read) token weight type))
          ((and (operatorp token)(not (null operator))
                (eq type 'xfy)(= (get-weight token) weight))
           (formula1 operand1 (formula1 operand2 (formula-read) token (get-weight token)(get-type token))
                     operator weight type))
          (t (error* "Syntax error illegal formula" token)))))


(defun formula-read ()
  (let ((token (get-token)))
    (cond ((end-of-file-p token) token)
          ((delimiterp token) token)
          ((operatorp token) token)
          ((numberp token) token)
          ((and (symbolp token)(not (null buffer))(char= (look) #\[))
           (getc)
           (cons token (mexp-read-list)))
          ((symbolp token) token)
          (t (error* "Syntax error illegal formula element" token)))))

(defun convert-to-cond (ls)
  (cond ((atom ls) ls)
        ((and (consp ls)(< (length ls) 3)) ls)
        ((and (consp ls)(>= (length ls) 3)(not (eq (elt ls 1) '->))) ls)
        (t (cons 'cond (convert-to-cond1 ls)))))

(defun convert-to-cond1 (ls)
  (cond ((null ls) nil)
        ((< (length ls) 3) ls)
        (t (cons (list (elt ls 0)(convert-to-cond (elt ls 2)))
                 (convert-to-cond1 (cdr (cdr (cdr ls))))))))

;;cond節を表す->記号があるときは [a -> b;c -> d] = (a -> b c -> d)のように
;;変換する。
(defun mexp-read-list ()
  (let ((token (get-token))
        (result nil))
    (cond ((and (characterp token)(char= token #\])) nil)
          ((and (characterp token)(char= token #\[))
           (cons (mexp-read-list)(mexp-read-list)))
          ((and (characterp token)(char= token #\;))
           (mexp-read-list))
          ((and (symbolp token)(eq token '->))
           (cons token (mexp-read-list)))
          ((and (symbolp token)(char= (look) #\[))
           (get-token)
           (cons (cons token (mexp-read-list))
                 (mexp-read-list)))
          ((and (characterp token)(char= token #\())
           (setq result (sexp-read-list))
           (if (and (not (char= (look) #\-)) ;; check for ->
                    (not (char= (look) #\;))
                    (not (char= (look) #\])))
               (error* "Syntax error expected ; or ] " result))
           (cons (list 'quote result) (mexp-read-list)))
          ((and (characterp token)(char= token #\'))
           (cons (list 'quote (sexp-read)) (mexp-read-list)))
          ((numberp token)
           (if (operator-char-p (look))
               (cons (formula token (get-token))(mexp-read-list))
               (cons token (mexp-read-list))))
          ((symbolp token)
           (if (and (operator-char-p (look))(not (char= (look1) #\>)))
               (cons (formula token (get-token))(mexp-read-list))
               (cons token (mexp-read-list))))
          ((stringp token)
           (if (and (not (char= (look) #\-)) ;; check for ->
                    (not (char= (look) #\;))
                    (not (char= (look) #\])))
               (error* "Syntax error expected ; or ] " token))
           (cons token (mexp-read-list)))
          (t (error* "M-exp illegal object" token)))))

;;;

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
                    (t (convert-to-atom (list char)))))
            ((char= char #\")
             (setq token (cons char token))
             (setq char (getc))
             (while (not (char= char #\"))
                    (setq token (cons char token))
                    (setq char (getc)))
             (setq token (cons char token))
             (convert-to-atom (reverse token)))
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
               (convert-to-atom (reverse token)))))))

;;文字リストを各種のアトムに変換する
(defun convert-to-atom (ls)
  (cond ((string-list-p ls)
         (convert-to-string (cut-both-side ls)))
        ((integer-list-p ls)
         (convert-to-integer ls))
        ((float-list-p ls)
         (convert-to-float ls))
        (t (convert-to-symbol ls))))

;;リストの両端をカットする。
(defun cut-both-side (ls)
  (reverse (cdr (reverse (cdr ls)))))

;;文字リストをシンボルに変換する
(defun convert-to-symbol (ls)
  (convert (convert-to-string ls) <symbol>))

;;文字リストを文字列に変換する。
;;シンボルは大文字に変換される
(defun convert-to-string (ls)
  (if (null ls)
      ""
      (string-append (convert (uppercase (car ls)) <string>)
                     (convert-to-string (cdr ls)))))

;;アルファベット小文字を大文字に変換する
;;アルファベット以外はそのまま
(defun uppercase (x)
  (let ((ascii (convert x <integer>)))
    (if (and (>= ascii 97)(<= ascii 122))
        (convert (- ascii 32) <character>)
        x)))

;;文字リストを整数に変換する
(defun convert-to-integer (ls)
  (convert (convert-to-string ls) <integer>))

;;文字リストを浮動小数点数に変換する
(defun convert-to-float (ls)
  (convert (convert-to-string ls) <float>))

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


;;M言語の終端記号であるピリオドであればtを、そうでなければnilを返す
(defun terminalp (c)
  (and (characterp c)(char= c #\.)))

;;演算子の文字のときにtを、そうでなければnilを返す
(defun operator-char-p (c)
  (if (and (characterp c)(member c '(#\+ #\- #\* #\/ #\^)))
      t
      nil))

;;左カッコのときにtを、そうでなければnilを返す
(defun left-paren-p (c)
  (if (and (characterp c)(char= #\())
       t
       nil))

;;右カッコのときにtを、そうでなければnilを返す
(defun right-paren-p (c)
  (if (and (characterp c)(char= #\)))
       t
       nil))

;;演算子のシンボルのときにtを、そうでなければnilを返す
(defun operatorp (x)
  (if (member x '(+ - * / ^))
      t
      nil))

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

;;lookのもうひとつ先を読む
(defun look1 ()
  (block exit
    (let ((max (length buffer)))
      (if (null buffer)
          (return-from exit #\.))
      (for ((pos 0 (+ pos 1)))
           ((>= pos max) nil)
           (if (not (char= (elt buffer pos) #\space))
               (return-from exit (elt buffer (+ pos 1))))))))

;;文字リストが文字列を表すならばtを、そうでなければnilを返す
(defun string-list-p (ls)
  (and (char= (car ls) #\")
       (char= (car (reverse ls)) #\")))

;;文字リストが整数を表しているならばtを、そうでなければnilを返す
(defun integer-list-p (ls)
  (cond ((char= (car ls) #\+)
         (integer-list-p1 (cdr ls)))
        ((char= (car ls) #\-)
         (integer-list-p1 (cdr ls)))
        (t (integer-list-p1 ls))))

;;整数は必ず1文字の数文字から構成されていなければならない
(defun integer-list-p1 (ls)
  (cond ((null ls) nil)
        ((and (number-char-p (car ls))(null (cdr ls))) t)
        ((not (number-char-p (car ls))) nil)
        (t (integer-list-p1 (cdr ls)))))

;;文字リストが浮動小数点数を表しているならばtを、そうでなければnilを返す
(defun float-list-p (ls)
  (cond ((not (number-char-p (car ls))) nil)
        ((char= (car ls) #\+)
         (float-list-p1 (cdr ls)))
        ((char= (car ls) #\-)
         (float-list-p1 (cdr ls)))
        (t (float-list-p1 ls))))

;;浮動小数点数は 123.4、123e4、123e+4、123e-4のような形式とする
(defun float-list-p1 (ls)
  (cond ((null ls) nil)
        ((char= (car ls) #\.)
         (integer-list-p (cdr ls)))
        ((char= (car ls) #\e)
         (integer-list-p (cdr ls)))
        ((not (number-char-p (car ls))) nil)
        (t (float-list-p1 (cdr ls)))))

(defun number-char-p (x)
  (and (char>= x #\0)
       (char<= x #\9)))
