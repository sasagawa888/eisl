#|
 study of DNA

 base: A T C G U
 amino acid:
 e.g. ala = Alanine

|#

(import "elixir")

(defglobal test-data1 "AUGCGCAAUGUGUAA")
(defglobal test-data2 "TTGCGAT")

(defun rna->amino (x)
    (pipe (convert x <list>) |> (decode nil)))

(defun dna->rna (x)
    (pipe (convert x <list>) |> (copy) |> (list->string)))

(defun make-pair-dna (x)
    (pipe (convert x <list>) |> (pair) |> (list->string)))


(defun list->string (x)
    (if (null x)
        ""
        (string-append (convert (car x) <string>)
                       (list->string (cdr x)))))

(defpattern decode 
    ((empty-list) nil)
    (((#\U #\U #\U :rest _x) _sw) (cons 'phe (decode _x _sw)))
    (((#\U #\U #\C :rest _x) _sw) (cons 'ala (decode _x _sw)))
    (((#\U #\U #\A :rest _x) _sw) (cons 'leu (decode _x _sw)))
    (((#\U #\U #\G :rest _x) _sw) (cons 'leu (decode _x _sw)))
    (((#\C #\U #\U :rest _x) _sw) (cons 'leu (decode _x _sw)))
    (((#\C #\U #\C :rest _x) _sw) (cons 'leu (decode _x _sw)))
    (((#\C #\U #\A :rest _x) _sw) (cons 'leu (decode _x _sw)))
    (((#\C #\U #\G :rest _x) _sw) (cons 'leu (decode _x _sw)))
    (((#\A #\U #\U :rest _x) _sw) (cons 'ile (decode _x _sw)))
    (((#\A #\U #\C :rest _x) _sw) (cons 'ile (decode _x _sw)))
    (((#\A #\U #\A :rest _x) _sw) (cons 'ile (decode _x _sw)))
    (((#\A #\U #\G :rest _x) nil) (cons 'begin (decode _x t)))
    (((#\A #\U #\G :rest _x) _sw) (cons 'met (decode _x _sw)))
    (((#\G #\U #\U :rest _x) _sw) (cons 'val (decode _x _sw)))
    (((#\G #\U #\C :rest _x) _sw) (cons 'val (decode _x _sw)))
    (((#\G #\U #\A :rest _x) _sw) (cons 'val (decode _x _sw)))
    (((#\G #\U #\G :rest _x) _sw) (cons 'val (decode _x _sw)))
    (((#\U #\C #\U :rest _x) _sw) (cons 'ser (decode _x _sw)))
    (((#\U #\C #\C :rest _x) _sw) (cons 'ser (decode _x _sw)))
    (((#\U #\C #\A :rest _x) _sw) (cons 'ser (decode _x _sw)))
    (((#\U #\C #\G :rest _x) _sw) (cons 'ser (decode _x _sw)))
    (((#\C #\C #\U :rest _x) _sw) (cons 'pro (decode _x _sw)))
    (((#\C #\C #\C :rest _x) _sw) (cons 'pro (decode _x _sw)))
    (((#\C #\C #\A :rest _x) _sw) (cons 'pro (decode _x _sw)))
    (((#\C #\C #\G :rest _x) _sw) (cons 'pro (decode _x _sw)))
    (((#\A #\C #\U :rest _x) _sw) (cons 'thr (decode _x _sw)))
    (((#\A #\C #\C :rest _x) _sw) (cons 'thr (decode _x _sw)))
    (((#\A #\C #\A :rest _x) _sw) (cons 'thr (decode _x _sw)))
    (((#\A #\C #\G :rest _x) _sw) (cons 'thr (decode _x _sw)))
    (((#\G #\C #\U :rest _x) _sw) (cons 'ala (decode _x _sw)))
    (((#\G #\C #\C :rest _x) _sw) (cons 'ala (decode _x _sw)))
    (((#\G #\C #\A :rest _x) _sw) (cons 'ala (decode _x _sw)))
    (((#\G #\C #\G :rest _x) _sw) (cons 'ala (decode _x _sw)))
    (((#\U #\A #\U :rest _x) _sw) (cons 'tyr (decode _x _sw)))
    (((#\U #\A #\C :rest _x) _sw) (cons 'thr (decode _x _sw)))
    (((#\U #\A #\A :rest _x) _sw) (cons 'end (decode _x _sw)))
    (((#\U #\A #\G :rest _x) _sw) (cons 'end (decode _x _sw)))
    (((#\C #\A #\U :rest _x) _sw) (cons 'his (decode _x _sw)))
    (((#\C #\A #\C :rest _x) _sw) (cons 'his (decode _x _sw)))
    (((#\C #\A #\A :rest _x) _sw) (cons 'gln (decode _x _sw)))
    (((#\C #\A #\G :rest _x) _sw) (cons 'gln (decode _x _sw)))
    (((#\A #\A #\U :rest _x) _sw) (cons 'asn (decode _x _sw)))
    (((#\A #\A #\C :rest _x) _sw) (cons 'asn (decode _x _sw)))
    (((#\A #\A #\A :rest _x) _sw) (cons 'lys (decode _x _sw)))
    (((#\A #\A #\G :rest _x) _sw) (cons 'lys (decode _x _sw)))
    (((#\G #\A #\U :rest _x) _sw) (cons 'asp (decode _x _sw)))
    (((#\G #\A #\C :rest _x) _sw) (cons 'asp (decode _x _sw)))
    (((#\G #\A #\A :rest _x) _sw) (cons 'glu (decode _x _sw)))
    (((#\G #\A #\G :rest _x) _sw) (cons 'glu (decode _x _sw)))
    (((#\U #\G #\U :rest _x) _sw) (cons 'cys (decode _x _sw)))
    (((#\U #\G #\C :rest _x) _sw) (cons 'cys (decode _x _sw)))
    (((#\U #\G #\A :rest _x) _sw) (cons 'end (decode _x _sw)))
    (((#\U #\G #\G :rest _x) _sw) (cons 'trp (decode _x _sw)))
    (((#\C #\G #\U :rest _x) _sw) (cons 'arg (decode _x _sw)))
    (((#\C #\G #\C :rest _x) _sw) (cons 'arg (decode _x _sw)))
    (((#\C #\G #\A :rest _x) _sw) (cons 'arg (decode _x _sw)))
    (((#\C #\G #\G :rest _x) _sw) (cons 'arg (decode _x _sw)))
    (((#\A #\G #\U :rest _x) _sw) (cons 'ser (decode _x _sw)))
    (((#\A #\G #\C :rest _x) _sw) (cons 'ser (decode _x _sw)))
    (((#\A #\G #\A :rest _x) _sw) (cons 'arg (decode _x _sw)))
    (((#\A #\G #\G :rest _x) _sw) (cons 'arg (decode _x _sw)))
    (((#\G #\G #\U :rest _x) _sw) (cons 'gly (decode _x _sw)))
    (((#\G #\G #\C :rest _x) _sw) (cons 'gly (decode _x _sw)))
    (((#\G #\G #\A :rest _x) _sw) (cons 'gly (decode _x _sw)))
    (((#\G #\G #\G :rest _x) _sw) (cons 'gly (decode _x _sw))))

(defpattern copy
    ((empty-list) nil)
    (((#\A :rest _x)) (cons #\U (copy _x)))
    (((#\T :rest _x)) (cons #\A (copy _x)))
    (((#\G :rest _x)) (cons #\C (copy _x)))
    (((#\C :rest _x)) (cons #\G (copy _x))))

(defpattern pair
    ((empty-list) nil)
    (((#\A :rest _x)) (cons #\T (pair _x)))
    (((#\T :rest _x)) (cons #\A (pair _x)))
    (((#\G :rest _x)) (cons #\C (pair _x)))
    (((#\C :rest _x)) (cons #\G (pair _x))))