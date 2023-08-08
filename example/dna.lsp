#|
 study of DNA

 nucleotide: A(adenine) T(thymine) C(cytosine) G(guanine) U(uracil)
 amino acid:
 e.g. ala = Alanine
DNA and RNA data is string each element is nucleotide.
DNA is pair of a DNA e.g. ("TTGCGAT" "AACGCTA")

example execution
> (foo dna)
(ARG ASN VAL TYR ILE PRO ALA SER GLN PHE GLN GLY CYS LYS)
|#

(import "elixir")
;; ARG ASN VAL TYR ILE PRO ALA SER GLN PHE GLN GLY CYS LYS
;; CGU AAU GUU UAU AUU CCU GCU UCU CAA UUU CAA GGA UGU AAA 
(defglobal dt1 "CGUAAUGUUUAUAUUCCUGCUUCUCAAUUUCAAGGAUGUAAA")
(defglobal dt2 "GCATTACAAATATAAGGACGAAGAGTTAAAGTTCCTACATTT")
(defglobal dna '("GCATTACAAATATAAGGACGAAGAGTTAAAGTTCCTACATTT" 
                 "CGTAATGTTTATATTCCTGCTTCTCAATTTCAAGGATGTAAA"))

(defun foo (x)
    (pipe dna |> (car) |> (dna->rna) |> (add-pointer) |> (rna->amino)))                 

;; make amino acid list from RNA
(defun rna->amino (x)
    (pipe (convert x <list>) |> (ribosome nil)))

;; tracscript DNA to RNA
(defun dna->rna (x)
    (pipe (convert x <list>) |> (transcript) |> (list->string)))

;; make pair-DNA
(defun make-pair (x)
    (pipe (convert x <list>) |> (pair) |> (list->string)))

;; add start-point(AUG) end-point(UAA)
(defun add-pointer (x)
    (string-append "AUG" x "UAA")) 

;; Thomas Jefferson University
(defun rna->dna (x)
    (pipe (convert x <list>) |> (reverse-transcript) |> (list->string)))


;; generate Amino acid from mRNA
(defpattern ribosome
    ((empty) nil)
    ;;AUG is start-poinrt AUG is also met amino, distinguish them with _sw(nil,t)
    (((#\A #\U #\G :rest _x) nil) (ribosome _x t))
    ;;UAA and UAG are end-point
    (((#\U #\A #\A :rest _x) _sw) nil )
    (((#\U #\A #\G :rest _x) _sw) nil )

    (((#\U #\U #\U :rest _x) _sw) (cons 'phe (ribosome _x _sw)))
    (((#\U #\U #\C :rest _x) _sw) (cons 'ala (ribosome _x _sw)))
    (((#\U #\U #\A :rest _x) _sw) (cons 'leu (ribosome _x _sw)))
    (((#\U #\U #\G :rest _x) _sw) (cons 'leu (ribosome _x _sw)))
    (((#\C #\U #\U :rest _x) _sw) (cons 'leu (ribosome _x _sw)))
    (((#\C #\U #\C :rest _x) _sw) (cons 'leu (ribosome _x _sw)))
    (((#\C #\U #\A :rest _x) _sw) (cons 'leu (ribosome _x _sw)))
    (((#\C #\U #\G :rest _x) _sw) (cons 'leu (ribosome _x _sw)))
    (((#\A #\U #\U :rest _x) _sw) (cons 'ile (ribosome _x _sw)))
    (((#\A #\U #\C :rest _x) _sw) (cons 'ile (ribosome _x _sw)))
    (((#\A #\U #\A :rest _x) _sw) (cons 'ile (ribosome _x _sw)))
    (((#\A #\U #\G :rest _x) _sw) (cons 'met (ribosome _x _sw)))
    (((#\G #\U #\U :rest _x) _sw) (cons 'val (ribosome _x _sw)))
    (((#\G #\U #\C :rest _x) _sw) (cons 'val (ribosome _x _sw)))
    (((#\G #\U #\A :rest _x) _sw) (cons 'val (ribosome _x _sw)))
    (((#\G #\U #\G :rest _x) _sw) (cons 'val (ribosome _x _sw)))
    (((#\U #\C #\U :rest _x) _sw) (cons 'ser (ribosome _x _sw)))
    (((#\U #\C #\C :rest _x) _sw) (cons 'ser (ribosome _x _sw)))
    (((#\U #\C #\A :rest _x) _sw) (cons 'ser (ribosome _x _sw)))
    (((#\U #\C #\G :rest _x) _sw) (cons 'ser (ribosome _x _sw)))
    (((#\C #\C #\U :rest _x) _sw) (cons 'pro (ribosome _x _sw)))
    (((#\C #\C #\C :rest _x) _sw) (cons 'pro (ribosome _x _sw)))
    (((#\C #\C #\A :rest _x) _sw) (cons 'pro (ribosome _x _sw)))
    (((#\C #\C #\G :rest _x) _sw) (cons 'pro (ribosome _x _sw)))
    (((#\A #\C #\U :rest _x) _sw) (cons 'thr (ribosome _x _sw)))
    (((#\A #\C #\C :rest _x) _sw) (cons 'thr (ribosome _x _sw)))
    (((#\A #\C #\A :rest _x) _sw) (cons 'thr (ribosome _x _sw)))
    (((#\A #\C #\G :rest _x) _sw) (cons 'thr (ribosome _x _sw)))
    (((#\G #\C #\U :rest _x) _sw) (cons 'ala (ribosome _x _sw)))
    (((#\G #\C #\C :rest _x) _sw) (cons 'ala (ribosome _x _sw)))
    (((#\G #\C #\A :rest _x) _sw) (cons 'ala (ribosome _x _sw)))
    (((#\G #\C #\G :rest _x) _sw) (cons 'ala (ribosome _x _sw)))
    (((#\U #\A #\U :rest _x) _sw) (cons 'tyr (ribosome _x _sw)))
    (((#\U #\A #\C :rest _x) _sw) (cons 'thr (ribosome _x _sw)))
    (((#\C #\A #\U :rest _x) _sw) (cons 'his (ribosome _x _sw)))
    (((#\C #\A #\C :rest _x) _sw) (cons 'his (ribosome _x _sw)))
    (((#\C #\A #\A :rest _x) _sw) (cons 'gln (ribosome _x _sw)))
    (((#\C #\A #\G :rest _x) _sw) (cons 'gln (ribosome _x _sw)))
    (((#\A #\A #\U :rest _x) _sw) (cons 'asn (ribosome _x _sw)))
    (((#\A #\A #\C :rest _x) _sw) (cons 'asn (ribosome _x _sw)))
    (((#\A #\A #\A :rest _x) _sw) (cons 'lys (ribosome _x _sw)))
    (((#\A #\A #\G :rest _x) _sw) (cons 'lys (ribosome _x _sw)))
    (((#\G #\A #\U :rest _x) _sw) (cons 'asp (ribosome _x _sw)))
    (((#\G #\A #\C :rest _x) _sw) (cons 'asp (ribosome _x _sw)))
    (((#\G #\A #\A :rest _x) _sw) (cons 'glu (ribosome _x _sw)))
    (((#\G #\A #\G :rest _x) _sw) (cons 'glu (ribosome _x _sw)))
    (((#\U #\G #\U :rest _x) _sw) (cons 'cys (ribosome _x _sw)))
    (((#\U #\G #\C :rest _x) _sw) (cons 'cys (ribosome _x _sw)))
    (((#\U #\G #\A :rest _x) _sw) (cons 'end (ribosome _x _sw)))
    (((#\U #\G #\G :rest _x) _sw) (cons 'trp (ribosome _x _sw)))
    (((#\C #\G #\U :rest _x) _sw) (cons 'arg (ribosome _x _sw)))
    (((#\C #\G #\C :rest _x) _sw) (cons 'arg (ribosome _x _sw)))
    (((#\C #\G #\A :rest _x) _sw) (cons 'arg (ribosome _x _sw)))
    (((#\C #\G #\G :rest _x) _sw) (cons 'arg (ribosome _x _sw)))
    (((#\A #\G #\U :rest _x) _sw) (cons 'ser (ribosome _x _sw)))
    (((#\A #\G #\C :rest _x) _sw) (cons 'ser (ribosome _x _sw)))
    (((#\A #\G #\A :rest _x) _sw) (cons 'arg (ribosome _x _sw)))
    (((#\A #\G #\G :rest _x) _sw) (cons 'arg (ribosome _x _sw)))
    (((#\G #\G #\U :rest _x) _sw) (cons 'gly (ribosome _x _sw)))
    (((#\G #\G #\C :rest _x) _sw) (cons 'gly (ribosome _x _sw)))
    (((#\G #\G #\A :rest _x) _sw) (cons 'gly (ribosome _x _sw)))
    (((#\G #\G #\G :rest _x) _sw) (cons 'gly (ribosome _x _sw))))

(defpattern transcript
    ((empty-list) nil)
    (((#\A :rest _x)) (cons #\U (transcript _x)))
    (((#\T :rest _x)) (cons #\A (transcript _x)))
    (((#\G :rest _x)) (cons #\C (transcript _x)))
    (((#\C :rest _x)) (cons #\G (transcript _x))))

(defpattern reverse-transcript
    ((empty-list) nil)
    (((#\U :rest _x)) (cons #\A (reverse-transcript _x)))
    (((#\A :rest _x)) (cons #\T (reverse-transcript _x)))
    (((#\C :rest _x)) (cons #\G (reverse-transcript _x)))
    (((#\G :rest _x)) (cons #\C (reverse-transcript _x))))

(defpattern pair
    ((empty-list) nil)
    (((#\A :rest _x)) (cons #\T (pair _x)))
    (((#\T :rest _x)) (cons #\A (pair _x)))
    (((#\G :rest _x)) (cons #\C (pair _x)))
    (((#\C :rest _x)) (cons #\G (pair _x))))


;; (#\a #\b #\c) -> "abc"
(defun list->string (x)
    (if (null x)
        ""
        (string-append (create-string 1 (car x))
                       (list->string (cdr x)))))
