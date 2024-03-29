#|
Morse signal encoder and decoder

e.g.
> (encode "sos")
"... --- ... "
> (decode "... --- ... ")
"SOS"
> 
> (encode "I love you")
"..  .-.. --- ...- .  -.-- --- ..- "
> (decode "..  .-.. --- ...- .  -.-- --- ..- ")
"I LOVE YOU"
> 
|#


(import "elixir")

(defun encode (str)
    (pipe (convert str <list>) |> (capitalize) |> (list->morse) |> (list->string)))

(defun list->string (ls)
    (if (null ls)
        ""
        (string-append (car ls) (list->string (cdr ls)))))

(defun list->morse (ls)
    (mapcar (lambda (x) (char->morse x)) ls))

(defun char->morse (c)
    (case c
       ((#\A) ".- ")
       ((#\B) "-... ")
       ((#\C) "-.-. ")
       ((#\D) "-.. ")
       ((#\E) ". ")
       ((#\F) "..-. ")
       ((#\G) "--. ")
       ((#\H) ".... ")
       ((#\I) ".. ")
       ((#\J) ".--- ")
       ((#\K) "-.- ")
       ((#\L) ".-.. ")
       ((#\M) "-- ")
       ((#\N) "-. ")
       ((#\O) "--- ")
       ((#\P) ".--. ")
       ((#\Q) "--.- ")
       ((#\R) ".-. ")
       ((#\S) "... ")
       ((#\T) "- ")
       ((#\U) "..- ")
       ((#\V) "...- ")
       ((#\W) ".-- ")
       ((#\X) "-..- ")
       ((#\Y) "-.-- ")
       ((#\Z) "--.. ")
       ((#\0) "----- ")
       ((#\1) ".---- ")
       ((#\2) "..--- ")
       ((#\3) "...-- ")
       ((#\4) "....- ")
       ((#\5) "..... ")
       ((#\6) "-.... ")
       ((#\7) "--... ")
       ((#\8) "---.. ")
       ((#\9) "----. ")
       ((#\.) ".-.-.- ")
       ((#\,) "--..-- ")
       ((#\?) "..--.. ")
       ((#\space) " " ) ))


(defun capitalize (ls)
    (mapcar (lambda (x) (capitalize1 x)) ls))

(defun capitalize1 (c)
    (let ((i (convert c <integer>)))
        (if (and (>= i 97)(<= i 122))
            (convert (- i 32) <character>)
            c)))


(defun decode (str)
    (pipe (convert str <list>) |> (morse->list) |> (char->str) |> (list->string)))

(defpattern morse->list (x)
       ((empty) nil)
       (((#\space :rest _y)) (cons #\space (morse->list _y)))
       (((#\. #\-  #\space :rest _y)) (cons #\A (morse->list _y)))
       (((#\- #\. #\. #\.  #\space :rest _y)) (cons #\B (morse->list _y)))
       (((#\- #\. #\- #\.  #\space :rest _y)) (cons #\C (morse->list _y)))
       (((#\- #\. #\.  #\space :rest _y)) (cons #\D (morse->list _y)))
       (((#\.  #\space :rest _y)) (cons #\E (morse->list _y)))
       (((#\. #\. #\- #\.  #\space :rest _y)) (cons #\F (morse->list _y)))
       (((#\- #\- #\.  #\space :rest _y)) (cons #\G (morse->list _y)))
       (((#\. #\. #\. #\.  #\space :rest _y)) (cons #\H (morse->list _y)))
       (((#\. #\.  #\space :rest _y)) (cons #\I (morse->list _y)))
       (((#\. #\- #\- #\-  #\space :rest _y)) (cons #\J (morse->list _y)))
       (((#\- #\. #\-  #\space :rest _y)) (cons #\K (morse->list _y)))
       (((#\. #\- #\. #\.  #\space :rest _y)) (cons #\L (morse->list _y)))
       (((#\- #\-  #\space :rest _y)) (cons #\M (morse->list _y)))
       (((#\- #\.  #\space :rest _y)) (cons #\N (morse->list _y)))
       (((#\- #\- #\-  #\space :rest _y)) (cons #\O (morse->list _y)))
       (((#\. #\- #\- #\.  #\space :rest _y)) (cons #\P (morse->list _y)))
       (((#\- #\- #\. #\-  #\space :rest _y)) (cons #\Q (morse->list _y)))
       (((#\. #\- #\.  #\space :rest _y)) (cons #\R (morse->list _y)))
       (((#\. #\. #\.  #\space :rest _y)) (cons #\S (morse->list _y)))
       (((#\-  #\space :rest _y))  (cons #\T (morse->list _y)))
       (((#\. #\. #\-  #\space :rest _y)) (cons #\U (morse->list _y)))
       (((#\. #\. #\. #\-  #\space :rest _y)) (cons #\V (morse->list _y)))
       (((#\. #\- #\-  #\space :rest _y)) (cons #\W (morse->list _y)))
       (((#\- #\. #\. #\-  #\space :rest _y)) (cons #\X (morse->list _y)))
       (((#\- #\. #\- #\-  #\space :rest _y)) (cons #\Y (morse->list _y)))
       (((#\- #\- #\. #\.  #\space :rest _y)) (cons #\Z (morse->list _y)))
       (((#\- #\- #\- #\- #\-  #\space :rest _y)) (cons #\0 (morse->list _y)))
       (((#\. #\- #\- #\- #\-  #\space :rest _y)) (cons #\1 (morse->list _y)))
       (((#\. #\. #\- #\- #\-  #\space :rest _y)) (cons #\2 (morse->list _y)))
       (((#\. #\. #\. #\- #\-  #\space :rest _y)) (cons #\3 (morse->list _y)))
       (((#\. #\. #\. #\. #\-  #\space :rest _y)) (cons #\4 (morse->list _y)))
       (((#\. #\. #\. #\. #\.  #\space :rest _y)) (cons #\5 (morse->list _y)))
       (((#\- #\. #\. #\. #\.  #\space :rest _y)) (cons #\6 (morse->list _y)))
       (((#\- #\- #\. #\. #\.  #\space :rest _y)) (cons #\7 (morse->list _y)))
       (((#\- #\- #\- #\. #\.  #\space :rest _y)) (cons #\8 (morse->list _y)))
       (((#\- #\- #\- #\- #\.  #\space :rest _y)) (cons #\9 (morse->list _y)))
       (((#\. #\- #\. #\- #\. #\-  #\space :rest _y)) (cons #\. (morse->list _y)))
       (((#\- #\- #\. #\. #\- #\-  #\space :rest _y)) (cons #\, (morse->list _y)))
       (((#\. #\. #\- #\- #\. #\.  #\space :rest _y)) (cons #\? (morse->list _y)))
       ((else) (error "morse->list illegal code")))

(defun char->str (ls)
    (mapcar (lambda (x) (convert x <string>)) ls))