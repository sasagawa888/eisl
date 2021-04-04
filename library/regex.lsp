;;; Regular expressions.
;;; The exact syntax supported is "POSIX extended regular expressions"
;;; ( https://man.openbsd.org/re_format.7#EXTENDED_REGULAR_EXPRESSIONS ).
;;;
;;; Interface following Openlisp ( http://www.eligis.com ).

(c-include "<sys/types.h>")
(c-include "<regex.h>")

(defclass <regexp> ()
  ((val :accessor regexp-val :initform 0))) ; Underlying UNIX struct

(defgeneric regexp-p (o))
(defmethod regexp-p ((o <regexp>))
   ;; Returns t if object is a computed regular  expression  (of  type  <regexp>), nil otherwise.
   ;;
   ;; Supplying hints like `(the <regexp> o)` to the compiler doesn't work for non-builtin classes
   t)

(defun regcomp (re)
   ;; Compute regular-expression in an internal  format  and  returns  a  <regexp> object.
   (the <string> re)
   (c-lang "regex_t *preg;")
   (c-lang "preg = (regex_t *)malloc(sizeof(regex_t));")
   (let ((res (create (class <regexp>)))
         (c-res (c-lang "regcomp(preg, Fgetname(RE), REG_EXTENDED | REG_NOSUB) | INT_FLAG")))
        (if (= c-res 0)
            (progn (setf (regexp-val res) (c-lang "Fmakelong(preg)"))
                   res)
            (progn (c-lang "free(preg);")
                   nil))))

(defgeneric regexe (re str))
(defmethod regexe ((re <regexp>) str)
   ;; Match string against regexp.
   (the <string> str)
   ;; TODO: retvect, start
   (if (not (eq (class-of re)(class <regexp>)))
       (error "regexe not <regexp>" re))
   (let* ((val (regexp-val re))
          (c-res (c-lang "regexec(Fgetlong(VAL), Fgetname(STR), (size_t)0, NULL, 0) | INT_FLAG")))
         (= c-res 0)))

(defun regmatch (str1 str2)
   ;; Match string1 against string2.
   (let* ((re (regcomp str1))
          (res (regexe re str2)))
         (regfree re)
         res))

;; TODO: maybe integrate with gc if it doesn't add too much complexity?
(defgeneric regfree (re))
(defmethod regfree ((re <regexp>))
   ;; Free any dynamically allocated storage associated with the <regexp> object.
   ;; This is very unidiomatic Lisp, further work is needed.
   (let ((val (regexp-val re)))
        (c-lang "regfree(Fgetlong(VAL));")
        (c-lang "res = NIL; free(Fgetlong(VAL));")))

;; Test code:

#|
(defglobal x (regcomp "[A-Z]+"))
(regexp-p x)
(regexe x "ABCAB")
(regexe x "abcab")
(regmatch "^[A-Z]oo" "Foo Bar")
|#
