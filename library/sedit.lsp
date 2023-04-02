#|
structure editor
*data structure
stack  ((original-index . original-current) ...)
current  current editing S-exp
index  start from 0
*usage
(editf 'function-name-symbol)
|#

(defmodule sedit
    (defglobal stack '())
    (defglobal current '())
    (defglobal index 0)
    (defglobal function-name nil)
    (defglobal buffer nil)
    (defglobal search-key nil)

    (defun push (x)
        (setq stack (cons x stack)) )

    (defun pop ()
        (let ((x (car stack)))
           (setq stack (cdr stack))
           x ))

    ;; edit function
    (defpublic editf (x)
        (setq function-name x)
        (setq current (eisl-get-myself x))
        (edits))

    ;; edit structure
    (defun edits ()
        (for ((com (reads) (reads)))
             ((eq com 'q)
              t )
             (cond ((eq com 'h) (help))
                   ((eq com 'p) (prints current))
                   ((eq com 'i) (insert (read) current index))
                   ((eq com 'a) (insert (read) current (+ index 1)))
                   ((eq com 'r) (right))
                   ((eq com 'l) (left))
                   ((eq com 'u) (up))
                   ((eq com 'd) (down))
                   ((eq com 't) (top))
                   ((eq com 'k) (delete current index))
                   ((eq com 's) (replace (read) current index))
                   ((eq com 'c) (setq buffer (elt current index)))
                   ((eq com 'm) (insert buffer current index))
                   ((eq com 'x) (exchange current index))
                   ((eq com 'f) (setq search-key (read)) (find search-key current 0))
                   ((eq com 'n) (find search-key (nth-cdr current index)))
                   ((consp com) (format (standard-output) "~A~%" (eval com)))
                   ((integerp com) (repeat com)))))

    (defun right ()
        (if (> index (length current))
            t
            (setq index (+ index 1))))

    (defun left ()
        (if (= 0 index)
            t
            (setq index (- index 1))))

    (defun repeat (n)
        (setq index (+ n index))
        (cond ((> index (length current)) (setq index (length current)))
              ((< index 0) (setq index 0))
              (t nil)))

    
    (defun up ()
        (let ((x (pop)))
           (setq index (car x))
           (setq current (cdr x))))

    (defun down ()
        (push (cons index current))
        (setq current (elt current index))
        (setq index 0))

    (defun top ()
        (setq current (eisl-get-myself function-name))
        (setq stack nil)
        (setq index 0))

    (defun reads ()
        (format (standard-output) "* ")
        (read))

    ;; print structured S-exp
    (defun prints (x)
        (format (standard-output) "(")
        (prints1 x)
        (format (standard-output) "  [~A]~%" index))

    (defun prints1 (x)
        (cond ((null (cdr x)) (prints2 (car x)) (format (standard-output) ")"))
              (t (prints2 (car x))
                 (format (standard-output) " ")
                 (prints1 (cdr x)))))

    (defun prints2 (x)
        (if (atom x)
            (format (standard-output) "~A" x)
            (format (standard-output) "###")))

    ;; insert x nth y destructively
    (defun insert (x y n)
        (if (= n 0)
            (insert1 x n)
            (insert2 x y n)))

    ;; insert head
    (defun insert1 (x n)
        (if (null stack)
            (setq current (cons x current))
            (let ((i (car (car stack)))
                  (s (cdr (car stack))) )
               (set-elt (cons x current) s i)
               (setq current (cons x current)))))

    ;; insert not head
    (defun insert2 (x y n)
        (if (= n 1)
            (set-cdr (cons x (cdr y)) y)
            (insert2 x (cdr y) (- n 1))))

    ;; replace x nth destructively
    (defun replace (x y n)
        (if (= n 0)
            (replace1 x n)
            (replace2 x y n)))

    ;; replace head
    (defun replace1 (x n)
        (if (null stack)
            (setq current (cons x (cdr current)))
            (let ((i (car (car stack)))
                  (s (cdr (car stack))) )
               (set-elt (cons x (cdr current)) s i)
               (setq current (cons x (cdr current))))))

    ;; replace not head
    (defun replace2 (x y n)
        (if (= n 1)
            (set-cdr (cons x (cdr (cdr y))) y)
            (replace2 x (cdr y) (- n 1))))

    ;; exchange nth and n+1th destructively
    (defun exchange (y n)
        (if (= n 0)
            (exchange1)
            (exchange2 y n)))

    ;; exchange head
    (defun exchange1 ()
        (if (null stack)
            (setq current (cons (elt current 1) (cons (elt current 0) (cdr (cdr current)))))
            (let ((i (car (car stack)))
                  (s (cdr (car stack))) )
               (set-elt (cons (elt current 1) (cons (elt current 0) (cdr (cdr current)))) s i)
               (setq current (cons (elt current 1) (cons (elt current 0) (cdr (cdr current))))))))

    ;; exchange not head
    (defun exchange2 (y n)
        (if (= n 1)
            (set-cdr (cons (elt y 2) (cons (elt y 1) (cdr (cdr (cdr y))))) y)
            (exchange2 (cdr y) (- n 1))))

    

    ;; delete nth y destructively
    (defun delete (y n)
        (if (= n 0)
            (delete1 n)
            (delete2 y n)))

    ;; delete head
    (defun delete1 (n)
        (if (null stack)
            (setq current (cdr current))
            (let ((i (car (car stack)))
                  (s (cdr (car stack))) )
               (set-elt (cdr current) s i)
               (setq current (cdr current)))))

    ;; delete not head
    (defun delete2 (y n)
        (if (= n 1)
            (set-cdr (cdr y) y)
            (delete2 (cdr y) (- n 1))))

    (defun copy (x)
        (cond ((null x) nil)
              ((atom x) x)
              (t (cons (copy (car x)) (copy (cdr x))))))

    (defun find (x y n)
        (cond ((null y) nil) 
              ((equal x (car y)) (setq index n))
              (t (find x (cdr y) (+ n 1)))))

    (defun nth-cdr (x n)
        (cond ((null x) nil)
              ((= n 0) (cdr x))
              (t (nth-cdr (cdr x) (- n 1)))))

    (defun help ()
        (format (standard-output) "q quit~%")
        (format (standard-output) "h help~%")
        (format (standard-output) "r move right~%")
        (format (standard-output) "l move left~%")
        (format (standard-output) "u move up~%")
        (format (standard-output) "d move down~%")
        (format (standard-output) "t move top~%")
        (format (standard-output) "n positive number move right n~%")
        (format (standard-output) "n negative number move left n~%")
        (format (standard-output) "i insert s-exp at left side of index~%")
        (format (standard-output) "a insert s-exp at right side of index~%")
        (format (standard-output) "k kill s-exp at index~%")
        (format (standard-output) "s replace s-exp at index~%")
        (format (standard-output) "c copy s-exp to buffer at index~%")
        (format (standard-output) "m paste s-exp from buffer at index~%")
        (format (standard-output) "x exchange s-exp at index and s-exp at index+1~%")
        (format (standard-output) "f find s-exp and set index~%")
        (format (standard-output) "n find next and set index~%")
        (format (standard-output) "p print s-exp and index~%")
        (format (standard-output) "(s-exp) eval s-exp and print it~%"))

    
)
