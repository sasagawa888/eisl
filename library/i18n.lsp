;;; Internationalisation support.
;;; Probably limited to alphabetic languages for now.
;;;
;;; Similar to logger.lsp, this library is composed of two layers:
;;; 1. A thin wrapper around the UNIX API
;;; 2. An "opinionated" way for average applications to use this
;;;
;;; This "opinionated" way assumes that although I/O is in UTF-8,
;;; internally strings are single-byte. Purely because of the
;;; author's location, Latin-9 is chosen as an encoding here.
;;;
;;; NB: functions beginning with "c-" are for internal use only and
;;; should not be called by client code.

(c-include "<limits.h>")
(c-include "<locale.h>")
(c-include "<nl_types.h>")
(c-include "<iconv.h>")
(c-option "-liconv")
(c-define "I18N_STR_MAX" "256")

;;; Thin POSIX wrapper:

(defun c-setlocale (locale)
   (the <string> locale)
   (c-lang "char *val;")
   (c-lang "val = setlocale(LC_ALL, Fgetname(LOCALE));")
   (c-lang "res = (val == NULL) ? NIL : Fmakestr(val);"))

(defun catopen (name)
   (the <string> name)
   (c-lang "nl_catd catd;")
   (c-lang "char *res_str;")
   (c-lang "int temp;")
   (c-lang "catd = catopen(Fgetname(NAME), NL_CAT_LOCALE);")
   (c-lang "res_str = fast_sprint_hex_long(catd);")
   (c-lang "res = Fmakefaststrlong(res_str);"))

(defun catgets (catd set-id msg-id s)
   (the <longnum> catd)(the <fixnum> set-id)(the <fixnum> msg-id)(the <string> s)
   (c-lang "res = Fmakestr(catgets(Fgetlong(CATD), SET_ID & INT_MASK, MSG_ID & INT_MASK, Fgetname(S)));"))

(defun catclose (catd)
   (the <longnum> catd)
   (c-lang "res = catclose(Fgetlong(CATD)) | INT_FLAG;"))

(defun iconv-open (tocode fromcode)
   (the <string> tocode)(the <string> fromcode)
   (c-lang "char res_str[32];")
   (c-lang "snprintf(res_str, 31, \"%lld\", iconv_open(Fgetname(TOCODE), Fgetname(FROMCODE)));")
   (c-lang "res = Fmakestrlong(res_str);"))

;;; Recommended usage pattern:

(defun setlocale ()
   (let ((res (c-setlocale "")))
        (if (null res)
            (c-setlocale "C")
            res)))

(defglobal *iconvs* (cons 0 0))

(defun init-iconv ()
   (setf (car *iconvs*) (iconv-open "latin-9" "utf8"))
   (setf (cdr *iconvs*) (iconv-open "utf8" "latin-9")))

(defun str-iconv (cd lstr)
   (the <longnum> cd)(the <string> lstr)
   (c-lang "static char ustr[I18N_STR_MAX];")
   (c-lang "const char *inbuf;")
   (c-lang "char *outbuf;")
   (c-lang "size_t inbytesleft, outbytesleft;")
   (c-lang "inbuf = Fgetname(LSTR);")
   (c-lang "inbytesleft = strlen(Fgetname(LSTR));")
   (c-lang "outbuf = ustr;")
   (c-lang "outbytesleft = I18N_STR_MAX;")
   (c-lang "iconv(Fgetlong(CD), (char **)&inbuf, &inbytesleft, &outbuf, &outbytesleft);")
   (c-lang "*outbuf = '\\0';")
   (c-lang "res = Fmakestr(ustr);"))

(defun str-ltou (lstr)
   ;; Convert a string from Latin-9 to UTF8 encoding
   (the <string> lstr)
   (let ((latin-to-utf8 (cdr *iconvs*)))
        (str-iconv latin-to-utf8 lstr)))

(defun char-iconv (cd wc)
   (the <longnum> cd)(the <fixnum> wc)
   (c-lang "char uc[MB_LEN_MAX], lc[2];")
   (c-lang "int l;")
   (c-lang "char *inbuf, *outbuf;")
   (c-lang "size_t inbytesleft, outbytesleft;")
   (c-lang "l = wctomb(uc, WC & INT_MASK);")
   (c-lang "inbuf = uc;")
   (c-lang "inbytesleft = l;")
   (c-lang "outbuf = lc;")
   (c-lang "outbytesleft = 1;")
   (c-lang "iconv(Fgetlong(CD), &inbuf, &inbytesleft, &outbuf, &outbytesleft);")
   (c-lang "lc[1] = '\\0';")
   (c-lang "res = Fmakechar(lc);"))

(defun wc-to-latin (wc)
   ;; Convert a character from UTF8 to Latin-9 encoding
   (the <fixnum> wc)
   (let ((utf8-to-latin (car *iconvs*)))
        (char-iconv utf8-to-latin wc)))
