;;; Regular expressions.
;;; The exact syntax supported is "POSIX extended regular expressions"
;;; ( https://man.openbsd.org/re_format.7#EXTENDED_REGULAR_EXPRESSIONS ).
;;;
;;; Programmatic interface following Openlisp ( http://www.eligis.com ),
;;; but beware that the RE syntax may be different.
;;; Also, ensure that you call the new function `regfree` as required.

(c-include "<sys/types.h>")
(c-include "<regex.h>")

(defclass <regexp> ()
  ((val :accessor regexp-val :initform 0))) ; Underlying UNIX struct

(defgeneric regexp-p (o))
(defmethod regexp-p ((o <regexp>))
   ;; Returns t if object is a computed regular  expression  (of  type  <regexp>), nil otherwise.
   ;;
   ;; Supplying hints like `(the <regexp> o)` to the compiler doesn't work for non-builtin classes
   (eq (class-of o) (class <regexp>)))

(defun regcomp (re)
   ;; Compute regular-expression in an internal  format  and  returns  a  <regexp> object.
   (the <string> re)
   (c-lang "regex_t *preg;")
   (c-lang "preg = (regex_t *)malloc(sizeof(regex_t));")
   (let ((res (create (class <regexp>)))
         (c-res (c-lang "regcomp(preg, Fgetname(RE), REG_EXTENDED) | INT_FLAG")))
        (if (= c-res 0)
            (progn (setf (regexp-val res) (c-lang "Fmakelong(preg)"))
                   res)
            (progn (c-lang "free(preg);")
                   nil))))

(defgeneric regexe (re str retvect &rest maybe-start))
(defmethod regexe ((re <regexp>) str retvect &rest maybe-start)
   ;; Match string against regexp.
   (the <string> str)
   (c-lang "regmatch_t pmatch[1];")
   (if (null maybe-start)
       (c-lang "pmatch[0].rm_so = 0;")
       (let ((start (car maybe-start)))
            (progn (c-lang "pmatch[0].rm_so = START & INT_MASK;"))))
   (c-lang "pmatch[0].rm_eo = strlen(Fgetname(STR));")
   (let* ((val (regexp-val re))
          (c-res (c-lang "regexec(Fgetlong(VAL), Fgetname(STR), (size_t)1, pmatch, REG_STARTEND) | INT_FLAG")))
         (if (not (null retvect))
             (progn (setf (elt retvect 0) (c-lang "pmatch[0].rm_so | INT_FLAG"))
                    (setf (elt retvect 1) (c-lang "pmatch[0].rm_eo | INT_FLAG"))))
         (= c-res 0)))

(defun regmatch (str1 str2 &rest maybe-start)
   ;; Match string1 against string2.
   (let ((re (regcomp str1)))
        (unwind-protect (apply #'regexe re str2 nil maybe-start)
                (regfree re))))

(defgeneric regfree (re))
(defmethod regfree ((re <regexp>))
   ;; Free any dynamically allocated storage associated with the <regexp> object.
   ;; You should probably call this from an unwind-protect handler to avoid resource leaks.
   (let ((val (regexp-val re)))
        (c-lang "regfree(Fgetlong(VAL));")
        (c-lang "res = NIL; free(Fgetlong(VAL));")))

;; Test code:

#|
(defglobal x (regcomp "[A-Z]+"))
(regexp-p x)
(regexe x "ABCAB")
(regexe x "abcab")
(defglobal y #(0 0))
(regexe x "ABCAB" y)
(regexe x "ABCAB" y 1)
(regfree x)
(regmatch "^[A-Z]oo" "Foo Bar")
(regmatch "^[A-Z]" "Foo Bar" 2)
(regmatch "^[A-Z]" "Foo Bar" 4)
|#
