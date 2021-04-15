
(defmodule csv
    (defpublic read-csv (s)
        (read-csv0 s) )
    (defun read-csv0 (s)
        (let ((line (read-line s nil 'eof)))
           (cond ((eq line 'eof) 'eof)
                 ((string= line "") nil)
                 (t (read-csv1 (convert line <list>) nil nil)) )))
    (defun read-csv1 (ls word ans)
        (cond ((null ls) (reverse (cons (convert-to-atom (reverse word)) ans)))
              ((char= (car ls) #\,)
               (read-csv1 (cdr ls) nil (cons (convert-to-atom (reverse word)) ans)))
              ((char= (car ls) #\space) (read-csv1 (cdr ls) word ans))
              (t (read-csv1 (cdr ls) (cons (car ls) word) ans))))
    
    (defpublic parse-csv (s)
        (parse-csv1 s nil))
    (defun parse-csv1 (s ans)
        (let ((line (read-csv0 s)))
           (if (eq line 'eof)
               (reverse ans)
               (parse-csv1 s (cons line ans)))))
    
    ;;convert to char-list to each atom
    (defun convert-to-atom (ls)
        (cond ((string-list-p ls) (convert-to-string (cut-both-side ls)))
              ((integer-list-p ls) (convert-to-integer ls))
              ((float-list-p ls) (convert-to-float ls))
              (t (convert-to-symbol ls))))
    ;; convert char-list to string
    (defun convert-to-string (ls)
        (if (null ls)
            ""
            (string-append (convert (car ls) <string>) (convert-to-string (cdr ls)))))
    ;;cut both side of char-list
    (defun cut-both-side (ls)
        (reverse (cdr (reverse (cdr ls)))))
    ;;convert char-list to symbol
    (defun convert-to-symbol (ls)
        (convert (convert-to-string ls) <symbol>))
    
    ;;convert char-list to integer
    (defun convert-to-integer (ls)
        (convert (convert-to-string ls) <integer>))

    ;;convert char-list to float-number
    (defun convert-to-float (ls)
        (convert (convert-to-string ls) <float>))

    ;;when char-list express string-type return t, else return nil
    (defun string-list-p (ls)
        (and (not (null ls)) (char= (car ls) #\") (char= (car (reverse ls)) #\")))

    ;;when char-list express integer-type return t, else return nil
    (defun integer-list-p (ls)
        (cond ((char= (car ls) #\+) (integer-list-p1 (cdr ls)))
              ((char= (car ls) #\-) (integer-list-p1 (cdr ls)))
              (t (integer-list-p1 ls))))

    (defun integer-list-p1 (ls)
        (cond ((null ls) nil)
              ((and (number-char-p (car ls)) (null (cdr ls))) t)
              ((not (number-char-p (car ls))) nil)
              (t (integer-list-p1 (cdr ls)))))

    ;;when char-list express float-type return t, else nil.
    (defun float-list-p (ls)
        (cond ((not (number-char-p (car ls))) nil)
              ((char= (car ls) #\+) (float-list-p1 (cdr ls)))
              ((char= (car ls) #\-) (float-list-p1 (cdr ls)))
              (t (float-list-p1 ls))))

    ;;float-type e.g. 123.4、123e4、123e+4、123e-4
    (defun float-list-p1 (ls)
        (cond ((char= (car ls) #\.) (integer-list-p (cdr ls)))
              ((char= (car ls) #\e) (integer-list-p (cdr ls)))
              ((not (number-char-p (car ls))) nil)
              (t (float-list-p1 (cdr ls)))))
              
    (defun number-char-p (x)
        (and (char>= x #\0) (char<= x #\9)))
)
