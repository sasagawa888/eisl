 ;;
    ;; translater from string to sexp written by Kenichi Sasagawa
    ;; e.g. "1+2" -> (1 + 2)   "a+(b+x)" -> (a (b + c))
    
    (defun operator-p (x)
        (or (char= x #\+) (char= x #\-) (char= x #\*) (char= x #\/) (char= x #\^)))

    (defglobal *rest-list* nil)
    
    (defun symbol-token-p (x)
        (and (char>= (car x) #\A) (char<= (car x) #\z)))

    (defun integer-token-p (x)
        (and (char>= (car x) #\0) (char<= (car x) #\9) (not (member #\. x))))

    (defun float-token-p (x)
        (and (char>= (car x) #\0) (char<= (car x) #\9) (member #\. x)))

    
    (defun to-upper (x)
        (mapcar
         (lambda (x) 
            (if (and (char>= x #\a) (char<= x #\z))
                (convert (- (convert x <integer>) 32) <character>)
                x))
         x))

    (defun convert-token (x)
        (let ((y (reverse x)))
           (cond ((null x) nil)
                 ((symbol-token-p y) (convert (convert-token1 (to-upper y)) <symbol>))
                 ((integer-token-p y) (convert (convert-token1 y) <integer>))
                 ((float-token-p y) (convert (convert-token1 y) <float>))
                 (t (format (standard-output) "syntax error")))))

    (defun convert-token1 (x)
        (cond ((null x) "")
              (t (string-append (convert (car x) <string>) (convert-token1 (cdr x))))))

    (defun string->infix (x)
        (let ((s (parse x)))
                (if (= (length s) 1)
                    (car s)
                    s)))

    (defun parse (x)
        (setq *rest-list* nil)
        (parse1 (convert x <list>) nil nil))

    (defun parse1 (x token stack)
        (cond ((null x)
               (cond ((null token) (reverse stack))
                     (t (reverse (cons (convert-token token) stack)))))
              ((char= (car x) #\space) (parse1 (cdr x) token stack))
              ((operator-p (car x))
               (cond ((null token)
                      (parse1 (cdr x) nil (cons (convert (car x) <symbol>) stack)))
                     (t (parse1 (cdr x) nil (cons (convert (car x) <symbol>) (cons (convert-token token) stack))))))
              ((char= (car x) #\()
               (cond ((null token)
                      (let ((s (parse1 (cdr x) nil nil)))
                        (parse1 *rest-list* nil (cons s stack))))
                     ;; function e.g. foo(boo(x),bar(y))
                     (t 
                       (let ((s (parse1 (cdr x) nil nil))) 
                         (parse1 *rest-list* nil (cons (cons (convert-token token) (reverse s)) stack))))))
              ((char= (car x) #\))
               (setq *rest-list* (cdr x))
               (cond ((null token) stack)
                     (t (cons (convert-token token) stack) )))
              ((char= (car x) #\,)
               (setq *rest-list* (cdr x)) 
               (cond ((null token) 
                      (let ((s (parse1 (cdr x) nil nil)))
                         (append s stack )))
                     (t 
                      (let ((s (parse1 (cdr x) nil nil)))
                         (append s (cons (convert-token token) stack))))))
              (t (parse1 (cdr x) (cons (car x) token) stack))))

  (defun parse2 (x)
      (if (null (cdr x))
          x
          (list x)))
