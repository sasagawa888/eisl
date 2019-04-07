; Forth in ISLISP

(defglobal *data-stack* nil)
(defglobal *return-stack* nil)
(defglobal *word* '((dot dot)(bye t)(: define-word)(dot-s dot-s)(see see)
                   (drop drop)(swap swap)(dup dup)(rot rot)(cr cr)
                   (space space)(spaces spaces)(emit emit)
                   (mod mod*)(/mod /mod)(do do)(loop t)(do? do?)
                   (if if*)(then t)
                   (+ plus)(- minus)(* mult)(/ devide)))
(defglobal *buffer* nil)
(defglobal *current-code* nil)


(defmacro push (x)
  `(setq *data-stack* (cons ,x *data-stack*)))

(defmacro pop ()
  `(let ((x (car *data-stack*)))
      (setq *data-stack* (cdr *data-stack*))
      x))

(defmacro get ()
  `(let ((x (car *current-code*)))
      (setq *current-code* (cdr *current-code*))
      x))

(defun forth ()
  (initialize)
  (repl))

(defun repl ()
  (block repl
    (cond ((catch 'exit
             (for ((s (read-code) (read-code)))
                  ((equal s '(bye))
                   (format (standard-output) "May the Force be with you~%")
                   (return-from repl t))
                  (interpret-all s)))(repl))
          (t (repl)))))

(defun initialize ()
  (setq *data-stack* nil)
  (setq *return-stack* nil)
  (format (standard-output) "Forth for learning~%"))

;;一連のコードを解釈する。
;;実行中のコードのcdrは*current-code* に記憶する。do-loopで使用する。
(defun interpret-all (x)
  (setq *current-code* (cdr x))
  (cond ((null x) t)
        (t (interpret (car x))))
  (cond ((null *current-code*) t)
        (t (interpret-all *current-code*))))

;;1個のコードを解釈する。
(defun interpret (x)
  (cond ((and (symbolp x)(wordp x))
         (let ((y (entity x)))
            (if (symbolp y)
                (funcall (symbol-function y))
                (interpret-all y))))
        (t (cond ((numberp x) (push x))
                 ((stringp x) (format (standard-output) "~A" x))
                 (t (error* "undefined word" x))))))

;;エラー処理　msgとxを表示してreplに復帰する。
(defun error* (msg x)
  (format (standard-output) "Error ~A ~A~%" msg x)
  (throw 'exit t))

;;ワードか？
(defun wordp (x)
  (assoc x *word*))

;;ワードの実体を取得する
(defun entity (x)
  (elt (assoc x *word*) 1))

;; . DOT
(defun dot ()
  (if (null *data-stack*) (error* "no stack data" nil))
  (format (standard-output) "~A~%" (car *data-stack*))
  (setq *data-stack* (cdr *data-stack*)))

;; word .s
(defun dot-s ()
  (format (standard-output) "stack ~A ~A~%" (length *data-stack*) (reverse *data-stack*)))
;; word see
(defun see ()
  (let* ((word (get))
         (define (assoc word *word*)))
    (if (null define)
        (error* "undefined word" word)
        (format (standard-output) "~A ~A~%" word (elt define 1)))))

(defun drop ()
  (if (null *data-stack*) (error* "not enough data" 'drop))
  (setq *data-stack* (cdr *data-stack*)))

(defun swap ()
  (if (< (length *data-stack*) 2) (error* "not enough data" 'swap))
  (let ((first (elt *data-stack* 0))
        (second (elt *data-stack* 1)))
    (setq *data-stack* (cons second (cons first (cdr (cdr *data-stack*)))))))

(defun dup ()
  (if (null *data-stack*) (error* "not enough data" 'dup))
  (setq *data-stack* (cons (car *data-stack*) *data-stack*)))

(defun rot ()
  (if (< (length *data-stack*) 2) (error* "not enough data" 'rot))
  (let ((first  (elt *data-stack* 0))
        (second (elt *data-stack* 1))
        (third  (elt *data-stack* 2)))
      (setq *data-stack* (cons third (cons second (cons first (cdr (cdr (cdr *data-stack*)))))))))

(defun cr ()
  (format (standard-output) "~%"))

(defun space ()
  (format (standard-output) " "))

(defun spaces ()
  (let ((count (pop)))
    (if (< count 0) (error* "illegal number" count))
    (for ((i 0 (+ i 1)))
         ((= i count) t)
         (format (standard-output) " "))))

(defun emit ()
  (let ((data (pop)))
    (if (not (integerp data)) (error* "not integer" data))
    (format (standard-output) "~C" (convert data <character>))))

(defun do ()
  (let ((start (pop))
        (end   (pop))
        (loop (get-loop-code))
        (exit (get-exit-code)))
      (for ((i start (+ i 1)))
           ((>= i end) t)
           (interpret-all loop))
      (setq *current-code* exit)))

(defun do? ()
  (block do-question
    (let ((start (pop))
          (end   (pop))
          (loop (get-loop-code))
          (exit (get-exit-code)))
      (if (< end start) (return-from do-question t))
      (for ((i start (+ i 1)))
           ((>= i end) t)
           (interpret-all loop))
      (setq *current-code* exit))))

(defun get-loop-code ()
  (let ((body nil)
        (code *current-code*))
    (while (not (eql (car code) 'loop))
        (setq body (cons (car code) body))
        (setq code (cdr code)))
    (reverse body)))

(defun get-exit-code ()
  (let ((code *current-code*))
    (while (not (eql (car code) 'loop))
        (setq code (cdr code)))
    (cdr code)))

(defun if* ()
  (let ((test (pop))
        (true (get-true-code))
        (else (get-else-code)))
    (if (not (eql test 0))
        (interpret-all true))
    (setq *current-code* else)))

(defun get-true-code ()
    (let ((body nil)
          (code *current-code*))
        (while (not (eql (car code) 'then))
            (setq body (cons (car code) body))
            (setq code (cdr code)))
        (reverse body)))

(defun get-else-code ()
    (let ((code *current-code*))
        (while (not (eql (car code) 'then))
            (setq code (cdr code)))
        (cdr code)))

;;演算の実体
(defun plus ()
  (push (+ (pop) (pop))))

(defun minus ()
  (push (- (pop) (pop))))

(defun mult ()
  (push (* (pop) (pop))))

(defun devide ()
  (push (div (pop) (pop))))

(defun mod* ()
  (let ((first  (pop))
        (second (pop)))
    (push (mod second first))))

(defun /mod ()
  (let ((first  (pop))
        (second (pop)))
    (push (div second first))
    (push (mod second first))))


;;　ワードを定義する。
;;　ワードは　(name body) というリストとなっている。
;;　bodyはワードや数のリストとなっている。
;; 例　(foo (dup 1 +))
(defun define-word ()
  (let ((name nil)
        (body nil)
        (token nil))
    (setq name (get))
    (setq token (get))
    (while (not (eql token 'semicolon))
      (setq body (cons token body))
      (setq token (get)))
    (setq *word* (cons (list name (reverse body)) *word*))))

;; トークンを読み取る。プロンプトとして？を表示する。
;;　.　記号はシンボル　dot　に変換される。
;;　;　記号はシンボル　semicolon に変換される。
;; トークンはリストにまとめて返す。
(defun read-code ()
  (format (standard-output) "? ")
  (setq *buffer* (convert (read-line) <list>))
  (let ((code nil)
        (token nil))
      (setq token (gettoken))
      (while (not (null token))
        (setq code (cons token code))
        (setq token (gettoken)))
      (reverse code)))


(defun gettoken ()
  (if (null *buffer*)
      nil
      (gettoken1)))

;;スペースあるいは行末までトークンを読み取りgettoken2に渡す。
(defun gettoken1 ()
  (let ((token nil))
    (skip-space)
    (skip-paren)
    (while (and (not (null *buffer*))
                (not (char= (car *buffer*) #\space)))
      (setq token (cons (car *buffer*) token))
      (setq *buffer* (cdr *buffer*)))
    (gettoken2 (reverse token))))

;;トークンの種類に応じてリストからアトムに変換する。
(defun gettoken2 (ls)
  (cond ((and (= (length ls) 1) (char= (car ls) #\;)) 'semicolon)
        ((and (= (length ls) 1) (char= (car ls) #\.)) 'dot)
        ((and (= (length ls) 2) (char= (car ls) #\.) (char= (elt ls 1) #\s)) 'dot-s)
        ((and (= (length ls) 2) (char= (car ls) #\.) (char= (elt ls 1) #\")) (gettoken3))
        ((integer-list-p ls) (convert (convert-to-string ls) <integer>))
        ((float-list-p ls) (convert (convert-to-string ls) <float>))
        (t (convert (convert-to-string-upper ls) <symbol>))))

;; ." dot-string
;; "の直前までを読み込み文字列として返す。
(defun gettoken3 ()
  (let ((token nil))
    (skip-space)
    (while (and (not (null *buffer*))
                (not (char= (car *buffer*) #\")))
      (setq token (cons (car *buffer*) token))
      (setq *buffer* (cdr *buffer*)))
    (setq *buffer* (cdr *buffer*)) ;;discard "
    (convert-to-string (reverse token))))

;;空白を読み飛ばす。
(defun skip-space ()
  (while (and (not (null *buffer*))
              (char= (car *buffer*) #\space))
    (setq *buffer* (cdr *buffer*))))

;; ( ) をスキップする。　例　( n--n)
(defun skip-paren ()
  (cond ((and (not (null *buffer*)) (char= (car *buffer*) #\( ))
         (while (and (not (null *buffer*))
                     (not (char= (car *buffer*) #\) )))
           (setq *buffer* (cdr *buffer*)))
         (setq *buffer* (cdr *buffer*))
         (skip-space) )))

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


;;文字リストを文字列に変換する。
;;シンボルは大文字に変換される
(defun convert-to-string-upper (ls)
  (if (null ls)
      ""
      (string-append (convert (uppercase (car ls)) <string>)
                     (convert-to-string-upper (cdr ls)))))

;;文字リストを文字列に変換する。
(defun convert-to-string (ls)
  (if (null ls)
      ""
      (string-append (convert (car ls) <string>)
                     (convert-to-string (cdr ls)))))


;;アルファベット小文字を大文字に変換する
;;アルファベット以外はそのまま
(defun uppercase (x)
  (let ((ascii (convert x <integer>)))
    (if (and (>= ascii 97)(<= ascii 122))
        (convert (- ascii 32) <character>)
        x)))
