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

(c-include "<limits.h>")
(c-include "<locale.h>")
(c-include "<xlocale.h>")               ; TODO: macOS only?
(c-include "<nl_types.h>")
(c-include "<iconv.h>")
(c-option "-liconv")
(c-define "I18N_STR_MAX" "256")

;;; Thin UNIX wrapper.
;;; Using this is not recommended.

(defun setlocale (locale)
   (the <string> locale)
   (c-lang "char *val;")
   (c-lang "val = setlocale(LC_ALL, Fgetname(LOCALE));")
   (c-lang "res = (val == NULL) ? NIL : Fmakestr(val);"))

(defun catopen (name)
   (the <string> name)
   (c-lang "char *res_str;")
   (c-lang "res_str = fast_sprint_hex_long(catopen(Fgetname(NAME), NL_CAT_LOCALE));")
   (c-lang "res = Fmakefaststrlong(res_str);"))

(defun catgets (catd set-id msg-id s)
   (the <longnum> catd)(the <fixnum> set-id)(the <fixnum> msg-id)(the <string> s)
   (c-lang "res = Fmakestr(catgets(Fgetlong(CATD), SET_ID & INT_MASK, MSG_ID & INT_MASK, Fgetname(S)));"))

(defun catclose (catd)
   (the <longnum> catd)
   (c-lang "res = catclose(Fgetlong(CATD)) | INT_FLAG;"))

(defun iconv-open (tocode fromcode)
   (the <string> tocode)(the <string> fromcode)
   (c-lang "char *res_str;")
   (c-lang "res_str = fast_sprint_hex_long(iconv_open(Fgetname(TOCODE), Fgetname(FROMCODE)));")
   (c-lang "res = Fmakefaststrlong(res_str);"))

(defun duplocale ()
   (c-lang "char *res_str;")
   (c-lang "res_str = fast_sprint_hex_long(duplocale(LC_GLOBAL_LOCALE));")
   (c-lang "res = Fmakefaststrlong(res_str);"))

(defun newlocale (nlocname loc)
   (c-lang "char *res_str;")
   (c-lang "res_str = fast_sprint_hex_long(newlocale(LC_ALL_MASK, Fgetname(NLOCNAME), Fgetlong(LOC)));")
   (c-lang "res = Fmakefaststrlong(res_str);"))

(defun freelocale (loc)
   (c-lang "res = NIL; freelocale(Fgetlong(LOC));"))

(defun isspace-l (c locale)
   (c-lang "res = ((isspace_l(Fgetname(C)[0], Fgetlong(LOCALE)) == 0) ? NIL : T);"))

(defun strcoll-l (s1 s2 locale)
   (c-lang "res = strcoll(Fgetname(S1), Fgetname(S2), Fgetlong(LOCALE)) | INT_FLAG;"))

(defun toupper-l (c locale)
   (c-lang "char uc[2];")
   (c-lang "uc[0] = toupper_l(Fgetname(C)[0], Fgetlong(LOCALE));")
   (c-lang "uc[1] = '\\0';")
   (c-lang "res = Fmakechar(uc);"))

(defun tolower-l (c locale)
   (c-lang "char lc[2];")
   (c-lang "lc[0] = tolower_l(Fgetname(C)[0], Fgetlong(LOCALE));")
   (c-lang "lc[1] = '\\0';")
   (c-lang "res = Fmakechar(lc);"))

;;; Recommended usage pattern:

;; Recall that nested functions don't work in clang,
;; which breaks (flet ...) in compiled code.
;; But I don't think this is worth splitting up the file over.

;; Keep some globals here for convenience,
;; keeping the thin layer closer to UNIX.
(defglobal *latin-to-utf8* (iconv-open "latin-9" "utf8"))
(defglobal *utf8-to-latin* (iconv-open "utf8" "latin-9"))
(defglobal *latin-loc* (duplocale))

(defun safe-getenv (name)
   ;; I could (import "unix") for the Lisp version,
   ;; not sure if it's worth funny dependencies like that though.
   (let ((value (getenv "name")))
        (if (null value)
            "(unset)"
            (string-append "\"" value "\""))))

(defun safe-setlocale ()
   ;; TODO: better error reporting
   (let ((res (setlocale "")))
        (if (null res)
            (setlocale "C")
            res)))

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
   (str-iconv *latin-to-utf8* lstr))

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
   (char-iconv *utf8-to-latin* wc))

(defun safe-newlocale (nlocname loc)
   ;; TODO: better error reporting
   (the <string> nlocname)(the <longnum> loc)
   (let ((res (newlocale nlocname loc)))
      (if (= res 0)
          (setq res loc))
      res))

(defun init-locale (locname)
   ;; TODO: Same error handling as C.
   ;;       Same error reporting.
   (if (= *latin-loc* 0)
       (error "duplocale"))             ; TODO: perror too
   (if (not (null locname))
       (let* ((utf8-suffix (if (eq (self-introduction) 'macos)
                               ".UTF-8"
                               ".utf8"))
              (utf8-suffixlen (length utf8-suffix))
              (latin-suffix (if (eq (self-introduction) 'macos)
	                            ".ISO8859-15"
	                            "@euro"))
              (lang-countrylen (- (length locname) utf8-suffixlen))
              (lang-country (subseq locname 0 lang-countrylen))
              (nlocname ""))
             (if (string= (subseq locname lang-countrylen (length locname))
                          utf8-suffix)
                 (progn
                        ;; (format (standard-output) "init-locale: *latin-loc* ~A~%" *latin-loc*)
                        (setq nlocname (string-append lang-country latin-suffix))
                        (format (standard-output) "init-locale: nlocname ~A~%" nlocname)
                        (setq *latin-loc* (safe-newlocale nlocname *latin-loc*)))))))

(defun isspace (c)
   (isspace-l c *latin-loc*))

(defun strcoll (s1 s2)
   (strcoll-l s1 s2 *latin-loc*))

(defun toupper (c)
   (toupper-l c *latin-loc*))

(defun tolower (c)
   (tolower-l c *latin-loc*))
