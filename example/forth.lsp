;; Forth in ISLISP
;; usage
;; (load "exa,ple/forth.lsp")
;; (forth)
;; ? 1 2 + .
;; 3

(defglobal *data-stack* nil)
(defglobal *return-stack* nil)
(defglobal *word* '((dot dot)(bye t)(: define-word)(dot-s dot-s)(see see)
                   (drop drop)(swap swap)(dup dup)(rot rot)(cr cr)
                   (over over)
                   (space space)(spaces spaces)(emit emit)
                   (mod mod*)(/mod /mod)(do do)(loop t)(?do ?do)
                   (if if*)(then t)
                   (+ plus)(- minus)(* mult)(/ devide)(sqrt sqrt*)
                   (abs abs*)(negate negate)(max max*)(min mnin*)))
(defglobal *buffer* nil)
(defglobal *current-code* nil)


(defmacro push (x)
  `(setq *data-stack* (cons ,x *data-stack*)))

(defun pop ()
  (if (null *data-stack*)
      (error* "not enough data in stack" nil))
  (let ((x (car *data-stack*)))
    (setq *data-stack* (cdr *data-stack*))
    x))

(defun get ()
  (let ((x (car *current-code*)))
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

;; interpret codes. codes are packed in list.
;; running codes are stored in *current-code*. The word do,loop use this one.
(defun interpret-all (x)
  (setq *current-code* (cdr x))
  (cond ((null x) t)
        (t (interpret (car x))))
  (cond ((null *current-code*) t)
        (t (interpret-all *current-code*))))

;;interpret one code.
(defun interpret (x)
  (cond ((and (symbolp x)(wordp x))
         (let ((y (entity x)))
            (if (symbolp y)
                (funcall (symbol-function y))
                (let ((rest *current-code*))
                  (interpret-all y)
                  (setq *current-code* rest)))))
        (t (cond ((numberp x) (push x))
                 ((stringp x) (format (standard-output) "~A" x))
                 (t (error* "undefined word" x))))))

;;invoke error. display msg and x. Restor to REPL.
(defun error* (msg x)
  (format (standard-output) "Error ~A ~A~%" msg x)
  (throw 'exit t))

;;is it word?
(defun wordp (x)
  (assoc x *word*))

;;entity of word
(defun entity (x)
  (elt (assoc x *word*) 1))

;; . DOT
(defun dot ()
  (if (null *data-stack*) (error* "no stack data" nil))
  (format (standard-output) "~A~%" (pop)))

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

;; word drop
(defun drop ()
  (if (null *data-stack*) (error* "not enough data" 'drop))
  (setq *data-stack* (cdr *data-stack*)))

;; word swap
(defun swap ()
  (if (< (length *data-stack*) 2) (error* "not enough data" 'swap))
  (let ((first (elt *data-stack* 0))
        (second (elt *data-stack* 1)))
    (setq *data-stack* (cons second (cons first (cdr (cdr *data-stack*)))))))

;; word dup
(defun dup ()
  (if (null *data-stack*) (error* "not enough data" 'dup))
  (setq *data-stack* (cons (car *data-stack*) *data-stack*)))

;; word rot
(defun rot ()
  (if (< (length *data-stack*) 2) (error* "not enough data" 'rot))
  (let ((first  (elt *data-stack* 0))
        (second (elt *data-stack* 1))
        (third  (elt *data-stack* 2)))
      (setq *data-stack* (cons third (cons second (cons first (cdr (cdr (cdr *data-stack*)))))))))

;; word over
(defun over ()
  (if (< (length *data-stack*) 2) (error* "not enough data" 'rot))
  (let ((second (elt *data-stack* 1)))
    (setq *data-stack* (cons second *data-stack*))))

;; word cr
(defun cr ()
  (format (standard-output) "~%"))

;; word space
(defun space ()
  (format (standard-output) " "))

;; word spaces
(defun spaces ()
  (let ((count (pop)))
    (if (< count 0) (error* "illegal number" count))
    (for ((i 0 (+ i 1)))
         ((= i count) t)
         (format (standard-output) " "))))

;; word emit
(defun emit ()
  (let ((data (pop)))
    (if (not (integerp data)) (error* "not integer" data))
    (format (standard-output) "~C" (convert data <character>))))

;; word do
(defun do ()
  (let ((start (pop))
        (end   (pop))
        (loop (get-loop-code))
        (exit (get-exit-code)))
      (for ((i start (+ i 1)))
           ((>= i end) t)
           (interpret-all loop))
      (setq *current-code* exit)))

;; word ?do
(defun ?do ()
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

;; e.g. (do ." Hello" cr loop) -> (" Hello" cr)
(defun get-loop-code ()
  (let ((body nil)
        (code *current-code*))
    (while (not (eql (car code) 'loop))
        (setq body (cons (car code) body))
        (setq code (cdr code)))
    (reverse body)))

;; e.g. (do ." Hello" cr loop) -> ()
(defun get-exit-code ()
  (let ((code *current-code*))
    (while (not (eql (car code) 'loop))
        (setq code (cdr code)))
    (cdr code)))

;; word if
(defun if* ()
  (let ((test (pop))
        (true (get-true-code))
        (else (get-else-code)))
    (if (not (eql test 0))
        (interpret-all true))
    (setq *current-code* else)))

;; e.g. (if a then b) -> (a)
(defun get-true-code ()
    (let ((body nil)
          (code *current-code*))
        (while (not (eql (car code) 'then))
            (setq body (cons (car code) body))
            (setq code (cdr code)))
        (reverse body)))

;; e.g. (if a then b) -> (b)
(defun get-else-code ()
    (let ((code *current-code*))
        (while (not (eql (car code) 'then))
            (setq code (cdr code)))
        (cdr code)))

;;arithmetic word
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

(defun abs* ()
  (let ((x (pop)))
    (push (abs x))))

(defun negate ()
  (let ((x (pop)))
    (if (> x 0)
        (push (- x))
        (push (abs x)))))

(defun max* ()
  (let ((x (pop))
        (y (pop)))
    (push (max x y))))

(defun min* ()
  (let ((x (pop))
        (y (pop)))
    (push (min x y))))

(defun sqrt* ()
  (let ((x (pop)))
    (push (sqrt (pop)))))

;; word = (name entity)
;; e.g. wntity = (1 + .)
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


;; return code as list
;; display prompt ?
(defun read-code ()
  (setq *buffer* '(#\\)) ;; dummy
  (while (char= (car *buffer*) #\\) ;; skip comment line
    (format (standard-output) "? ")
    (setq *buffer* (convert (read-line (standard-input)) <list>)))
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

(defun gettoken1 ()
  (let ((token nil))
    (skip-space)
    (skip-paren)
    (while (and (not (null *buffer*))
                (not (char= (car *buffer*) #\space)))
      (setq token (cons (car *buffer*) token))
      (setq *buffer* (cdr *buffer*)))
    (gettoken2 (reverse token))))

(defun gettoken2 (ls)
  (cond ((and (= (length ls) 1) (char= (car ls) #\;)) 'semicolon)
        ((and (= (length ls) 1) (char= (car ls) #\.)) 'dot)
        ((and (= (length ls) 2) (char= (car ls) #\.) (char= (elt ls 1) #\s)) 'dot-s)
        ((and (= (length ls) 2) (char= (car ls) #\.) (char= (elt ls 1) #\")) (gettoken3))
        ((integer-list-p ls) (convert (convert-to-string ls) <integer>))
        ((float-list-p ls) (convert (convert-to-string ls) <float>))
        (t (convert (convert-to-string-upper ls) <symbol>))))

;; ." dot-string
;; "e.g. ." hello"
(defun gettoken3 ()
  (let ((token nil))
    (skip-space)
    (while (and (not (null *buffer*))
                (not (char= (car *buffer*) #\")))
      (setq token (cons (car *buffer*) token))
      (setq *buffer* (cdr *buffer*)))
    (setq *buffer* (cdr *buffer*)) ;;discard "
    (convert-to-string (reverse token))))

;;skip space
(defun skip-space ()
  (while (and (not (null *buffer*))
              (char= (car *buffer*) #\space))
    (setq *buffer* (cdr *buffer*))))

;; ( ) slip paren. e.g. ( n--n )
(defun skip-paren ()
  (cond ((and (not (null *buffer*)) (char= (car *buffer*) #\( ))
         (while (and (not (null *buffer*))
                     (not (char= (car *buffer*) #\) )))
           (setq *buffer* (cdr *buffer*)))
         (setq *buffer* (cdr *buffer*))
         (skip-space) )))

;;is it list that discribe integer?
(defun integer-list-p (ls)
  (cond ((char= (car ls) #\+)
         (integer-list-p1 (cdr ls)))
        ((char= (car ls) #\-)
         (integer-list-p1 (cdr ls)))
        (t (integer-list-p1 ls))))

(defun integer-list-p1 (ls)
  (cond ((null ls) nil)
        ((and (number-char-p (car ls))(null (cdr ls))) t)
        ((not (number-char-p (car ls))) nil)
        (t (integer-list-p1 (cdr ls)))))

;;is it list that discribe float number
(defun float-list-p (ls)
  (cond ((not (number-char-p (car ls))) nil)
        ((char= (car ls) #\+)
         (float-list-p1 (cdr ls)))
        ((char= (car ls) #\-)
         (float-list-p1 (cdr ls)))
        (t (float-list-p1 ls))))

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


;; convert from list of character to string
;; lowercase letters are convert to uppercase letter
(defun convert-to-string-upper (ls)
  (if (null ls)
      ""
      (string-append (convert (uppercase (car ls)) <string>)
                     (convert-to-string-upper (cdr ls)))))

;; convert from list of character to string
(defun convert-to-string (ls)
  (if (null ls)
      ""
      (string-append (convert (car ls) <string>)
                     (convert-to-string (cdr ls)))))


;; convert lowercase leteer to uppercase.
;; oter charater is same
(defun uppercase (x)
  (let ((ascii (convert x <integer>)))
    (if (and (>= ascii 97)(<= ascii 122))
        (convert (- ascii 32) <character>)
        x)))
