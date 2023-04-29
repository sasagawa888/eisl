(defmodule pretty
    ;; pretty printer for ISLisp
    ;; written by kenichi sasagawa
    (defconstant width 100)
    (defconstant long-element 15)
    (defconstant long-element-sum 60)
    (defconstant defglobal-long-element 50)
    (defglobal buffer nil)
    (defglobal input-stream (standard-input))
    (defglobal output-stream (standard-output))
    (defglobal otomo nil)
    
    ;; to test pp1 in standard-input
    (defpublic pretty-print (x)
        (pp1 x 0) )

    ;; pretty-print if asdata is given, pp1 doesn't care syntax. 
    (defun pp1 (x lm :rest asdata)
        (cond ((atom x) (pp-atom x))
              ((consp x)
               (cond ((or (quote-p x) (backquote-p x) (unquote-p x)) (pp-quote x lm))
                     ((unquote-splicing-p x) (pp-unquote-splicing x lm))
                     ((and (null asdata) (eq (car x) 'cond)) (pp-cond x lm))
                     ((and (null asdata) (eq (car x) 'case)) (pp-case x lm))
                     ((and (null asdata) (eq (car x) 'if)) (pp-if x lm))
                     ((and (null asdata) (eq (car x) 'let)) (pp-let x lm))
                     ((and (null asdata) (eq (car x) 'let*)) (pp-let* x lm))
                     ((and (null asdata) (eq (car x) 'for)) (pp-for x lm))
                     ((and (null asdata) (eq (car x) 'defun)) (pp-defun x lm))
                     ((and (null asdata) (eq (car x) 'defpublic)) (pp-defun x lm))
                     ((and (null asdata) (eq (car x) 'defgeneric)) (pp-defun x lm))
                     ((and (null asdata) (eq (car x) 'defmacro)) (pp-defun x lm))
                     ((and (null asdata) (eq (car x) 'defmodule)) (pp-defmodule x lm))
                     ((and (null asdata) (eq (car x) 'defglobal)) (pp-defglobal x lm))
                     ((and (null asdata) (eq (car x) 'defconstant)) (pp-defglobal x lm))
                     ((and (null asdata) (eq (car x) 'defdynamic)) (pp-defglobal x lm))
                     ((and (null asdata) (eq (car x) 'block)) (pp-block x lm))
                     ((and (null asdata) (eq (car x) 'while)) (pp-block x lm))
                     ((and (null asdata) (eq (car x) 'dotimes)) (pp-block x lm))
                     ((and (null asdata) (eq (car x) 'dolist)) (pp-block x lm))
                     ((and (null asdata) (eq (car x) 'lambda)) (pp-lambda x lm))
                     ((and (null asdata) (eq (car x) 'labels)) (pp-labels x lm))
                     ((and (null asdata) (eq (car x) 'flet)) (pp-labels x lm))
                     ((and (null asdata) (long-element-p x)) (setq otomo t) (pp-long-element x lm))
                     ((< (+ (flatsize x) lm) width) (pp-flat x lm))
                     (t (setq otomo t) (pp-indent x lm))))))

    ;; write symbol number string object
    (defun pp-atom (x)
        (if (stringp x)
            (format output-stream "\"~A\"" x)
            (format output-stream "~A" x)))

    ;; write string as text
    (defun pp-text (x)
        (format output-stream "~A" x))

    ;; write cons as flat
    (defun pp-flat (x lm)
        (pp-text "(")
        (for ((s x (cdr s)))
             ((null s)
              (pp-text ")") )
             (pp1 (car s) lm)
             (if (not (null (cdr s))) ;not end element
                 (space 1))))

    ;; write cons with indent
    (defun pp-indent (x lm)
        (pp-text "(")
        (for ((s x (cdr s)))
             ((null s)
              (cond ((= (length x) 0) (pp-text ")"))
                   (otomo (pp-atom ")"))
                   (t (setq otomo t) (pp-text " )")))
              (if (= lm 0)
                 (newline 0)) )
             (pp1 (car s) (+ lm 1))
             (if (not (null (cdr s))) ;not end element
                 (newline (+ lm 1)))))

    

    ;; write each syntax but 
    ;; if it is quote,backquote,untuote,unquote-splicing 
    ;; pp-quote or pp-unquote-splicing
    (defun pp-special (x fun lm)
        (cond ((quote-p x) (pp-quote x lm))
              ((backquote-p x) (pp-quote x lm))
              ((unquote-p x) (pp-quote x lm))
              ((unquote-splicing-p x) (pp-quote x lm))))

    

    ;; syntax cond
    (defun pp-cond (x lm)
        (pp-text "(COND ")
        (pp-cond1 (cdr x) (+ lm 6))
        (cond (otomo (pp-text ")"))
              (t (setq otomo t) (pp-text " )"))))

    (defun pp-cond1 (x lm)
        (for ((s x (cdr s)))
             ((null s)
              t )
             (pp1 (car s) lm)
             (if (not (null (cdr s)))
                 (newline lm))))

    ;; syntax case
    (defun pp-case (x lm)
        (let ((lm1 (+ lm 3)))
           (pp-text "(CASE ")
           (pp1 (elt x 1) lm)
           (newline lm1)
           (pp-cond1 (cdr (cdr x)) lm1)
           (pp-text " )")))

    ;;syntax if
    ;;2 pattern (if test then) or (if test then else)
    (defun pp-if (x lm)
        (let ((lm1 (+ lm 4)))
           (pp-text "(IF ")
           (for ((s (cdr x) (cdr s)))
                ((null s)
                 (cond (otomo (pp-text ")"))
                      (t (setq otomo t) (pp-text " )"))) )
                (pp1 (car s) lm1)
                (if (not (null (cdr s)))
                    (newline lm1)))))

    ;;syntax defun type
    ;;also defmacro defgeneric
    (defun pp-defun (x lm)
        (let ((lm1 (+ lm 4)))
           (pp-text "(")
           (pp1 (elt x 0) lm1)
           (pp-text " ")
           (pp1 (elt x 1) lm1)
           (pp-text " ")
           (pp1 (elt x 2) lm1)
           (if (cdr (cdr (cdr x)))
               (newline lm1))
           (pp-body (cdr (cdr (cdr x))) lm1)
           (if otomo
               (pp-text ")")
               (pp-text " )"))
           (newline 0)))

    ;; syntax defun body
    ;; also body of let,let*,for
    (defun pp-body (x lm)
        (for ((s x (cdr s)))
             ((null s)
              t )
             (pp1 (car s) lm)
             (cond ((and (not (null (cdr s))) ;not end element
                         (not (and (the-p (car s)) (the-p (car (cdr s)))))) ;not the declare
                    (newline lm)))))

    ;; syntax defmodule
    (defun pp-defmodule (x lm)
        (let ((lm1 (+ lm 4))
              (exp nil) )
           (pp-text "(")
           (pp1 (elt x 0) lm1)
           (pp-text " ")
           (pp1 (elt x 1) lm1)
           (newline lm1)
           (setq exp (cdr (cdr x)))
           (while exp
              (pp1 (car exp) lm1)
              (if (not (comment-p (car exp)))
                  (newline lm1))
              (setq exp (cdr exp)))
           (newline lm)
           (pp-text ")")
           (newline lm)))

    (defun pp-defglobal (x lm)
        (let ((size (flatsize (elt x 2))))
           (pp-text "(")
           (pp1 (elt x 0) lm)
           (pp-text " ")
           (pp1 (elt x 1) lm)
           (cond ((< size defglobal-long-element) (pp-text " ") (pp1 (elt x 2) -1) (pp-text ")"))
                 (t (newline (+ lm 11))
                    (pp1 (elt x 2) (+ lm 11))
                    (pp-text ")")))
           (if (= lm 0)
               (newline lm))))

    ;; syntax let
    (defun pp-let (x lm)
        (let ((lm1 (+ lm 5))
              (lm2 (+ lm 3)) )
           (pp-text "(")
           (pp1 (elt x 0) lm1)
           (pp-text " ")
           (pp-special (elt x 1) #'pp-let1 lm1)
           (newline lm2)
           (pp-body (cdr (cdr x)) lm2)
           (cond (otomo (pp-text ")"))
                 (t (setq otomo t) (pp-text " )")))))

    ;; syntax let
    (defun pp-let* (x lm)
        (let ((lm1 (+ lm 6))
              (lm2 (+ lm 4)) )
           (pp-text "(")
           (pp1 (elt x 0) lm1)
           (pp-text " ")
           (pp-let1 (elt x 1) lm1)
           (newline lm2)
           (pp-body (cdr (cdr x)) lm2)
           (cond (otomo (pp-text ")"))
                 (t (setq otomo t) (pp-text " )")))))

    (defun pp-let1 (x lm)
        (pp-text "(")
        (for ((s x (cdr s)))
             ((null s)
              (cond ((= (length x) 1) (pp-text ")"))
                   (t (setq otomo t) (pp-text " )"))) )
             (pp1 (car s) lm)
             (if (not (null (cdr s)))
                 (newline (+ lm 1)))))

    (defun pp-for (x lm)
        (let ((lm1 (+ lm 5)))
           (pp-text "(FOR ")
           (pp-let1 (elt x 1) lm1)
           (newline lm1)
           (pp-let1 (elt x 2) lm1)
           (cond ((not (null (cdr (cdr (cdr x))))) (newline lm1) (pp-body (cdr (cdr (cdr x))) lm1)))
           (pp-text ")")))

    (defun pp-quote (x lm)
        (format output-stream "~C" #\')
        (pp1 (car (cdr x)) (+ lm 1) t))

    (defun pp-unquote-splicing (x lm)
        (format output-stream "~C" #\,)
        (format output-stream "~C" #\@)
        (pp1 (cdr x) (+ lm 2) t))

    ;; syntax block type
    (defun pp-block (x lm)
        (let ((lm1 (+ lm 3))
              (body (cdr (cdr x))) )
           (pp-text "(")
           (pp1 (elt x 0) lm1)
           (pp-text " ")
           (pp1 (elt x 1) lm1)
           (cond ((and (= (length body) 1) (<= (flatsize body) long-element)) (pp-flat body lm1))
                 (t (newline lm1) (pp-body body lm1)))
           (pp-text ")")))

    ;; syntax lambda type
    (defun pp-lambda (x lm)
        (let ((lm1 (+ lm 3))
              (body (cdr (cdr x))) )
           (pp-text "(")
           (pp1 (elt x 0) lm1)
           (pp-text " ")
           (pp1 (elt x 1) lm1)
           (pp-text " ")
           (cond ((= (length body) 1) (pp1 (car body) lm1)) ; 1 quote or atom e.g. 'no , env 
                 ((and (= (length body) 1) (<= (flatsize body) long-element))
                  (pp-flat (car body) lm1))
                 (t (newline lm1) (pp-body body lm1)))
           (pp-text ")")))

    ;; syntax labels
    (defun pp-labels (x lm)
        (let ((lm1 (+ lm 7))
              (lm2 (+ lm 4))
              (body (cdr (cdr x))) )
           (pp-text "(")
           (pp1 (elt x 0) lm1)
           (pp-text " (")
           (pp-labels1 (elt x 1) lm1)
           (pp-text ")")
           (newline lm2)
           (pp-body body lm2)
           (pp-text ")")))

    (defun pp-labels1 (x lm)
        (for ((s x (cdr s)))
             ((null s)
              t )
             (pp-labels2 (car s) lm)))

    (defun pp-labels2 (x lm)
        (let ((lm1 (+ lm 4)))
           (pp-text "(")
           (pp1 (elt x 0) lm1)
           (pp-text " ")
           (pp1 (elt x 1) lm1)
           (newline lm1)
           (pp-body (cdr (cdr x)) lm1)
           (if otomo
               (pp-text ")")
               (pp-text " )"))
           (if (= lm 0)
               (newline lm))))

    ;; write subr with long element
    (defun pp-long-element (x lm)
        (let ((lm1 (+ 2 lm (flatsize (car x)))))
           (pp-text "(")
           (pp-atom (car x))
           (pp-text " ")
           (for ((s (cdr x) (cdr s)))
                ((null s)
                 (cond ((= (length x) 0) (pp-text ")"))
                      (otomo (pp-text ")"))
                      (t (pp-test " )"))) )
                (if (stringp (car s))
                    (pp-atom (car s))
                    (pp1 (car s) lm1))
                (cond ((not (null (cdr s))) ;not end element
                       (newline lm1))))))

    ;; print n of spaces
    (defun space (n)
        (for ((m n (- m 1)))
             ((<= m 0)
              t )
             (format output-stream " ")))

    ;; print linefeed and print spaces
    (defun newline (lm)
        (format output-stream "~%")
        (space lm))

    ;; calculate size of S-expression
    (defun flatsize (x)
        (cond ((null x) 3)
              ((characterp x) 3)
              ((stringp x) (length x))
              ((symbolp x) (length (convert x <string>)))
              ((numberp x) (length (convert x <string>)))
              ((general-vector-p x) (+ 1 (flatsize (convert x <list>))))
              ((and (listp x) (null (cdr x))) (+ 2 (flatsize (car x))))
              (t (+ (flatsize (car x)) 1 (flatsize (cdr x))))))

    ;; e.g. (the a <integer>) return T else NIL
    (defun the-p (x)
        (and (consp x) (eq (car x) 'the)))

    ;; is it quote? e.g. 'foo
    (defun quote-p (x)
        (and (consp x) (eq (car x) 'quote)))

    ;; is it backquote? e.g. `(if a b c)
    (defun backquote-p (x)
        (and (consp x) (eq (car x) 'backquote)))

    ;; is it unquote? e.g. ,name
    (defun unquote-p (x)
        (and (consp x) (eq (car x) 'unquote)))

    ;; is it unquote-splicing? e.g. ,@name
    (defun unquote-splicing-p (x)
        (and (consp x) (eq (car x) 'unquote-splicing)))

    ;; is it function that has long size element?  e.g. (+ (asdfghjklqwert x)(lkjdslkjsdflkj y))
    ;; if all each element size is over long-element, return t.
    ;; if sum of all element size is over long-element-sum, return t.
    (defun long-element-p (x)
        (and (consp x)
             (atom (car x))
             (> (length x) 2)
             (or (long-element-p1 (cdr x))
                 (>= (flatsize (cdr x)) long-element-sum))))

    (defun long-element-p1 (x)
        (cond ((null x) nil)
              ((< (flatsize (car x)) long-element) nil)
              ((>= (flatsize (car x)) long-element) (long-element-p1 (cdr x)))
              (t nil)))

    ;; is one-liner?
    (defun one-liner-p (x lm)
        (< (+ (flatsize x) lm) width))

    
)
