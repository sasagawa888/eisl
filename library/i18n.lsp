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
(c-include "<xlocale.h>" macos)
(c-include "<nl_types.h>")
(c-include "<iconv.h>")
(c-include "<stdlib.h>")
(c-include "<stdio.h>")
(c-option "-liconv" macos)
(c-option "-I/usr/local/include -L/usr/local/lib -liconv" openbsd)
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
   (the <string> nlocname)(the <longnum> loc)
   (c-lang "char *res_str;")
   (c-lang "res_str = fast_sprint_hex_long(newlocale(LC_ALL_MASK, Fgetname(NLOCNAME), Fgetlong(LOC)));")
   (c-lang "res = Fmakefaststrlong(res_str);"))

(defun freelocale (loc)
   (the <longnum> loc)
   (c-lang "res = NIL; freelocale(Fgetlong(LOC));"))

(defun iconv-close (cd)
  (the <longnum> cd)
  (c-lang "res = iconv_close(Fgetlong(CD));"))

(defun isspace-l (c locale)
   (the <character> c)(the <longnum> locale)
   (c-lang "res = ((isspace_l(Fgetname(C)[0], (locale_t)Fgetlong(LOCALE)) == 0) ? NIL : T);"))

(defun strcoll-l (s1 s2 locale)
   (the <string> s1)(the <string> s2)(the <longnum> locale)
   (c-lang "res = strcoll(Fgetname(S1), Fgetname(S2), Fgetlong(LOCALE)) | INT_FLAG;"))

(defun toupper-l (c locale)
   (the <character> c)(the <longnum> locale)
   (c-lang "char uc[2];")
   (c-lang "uc[0] = toupper_l(Fgetname(C)[0], (locale_t)Fgetlong(LOCALE));")
   (c-lang "uc[1] = '\\0';")
   (c-lang "res = Fmakechar(uc);"))

(defun tolower-l (c locale)
   (the <character> c)(the <longnum> locale)
   (c-lang "char lc[2];")
   (c-lang "lc[0] = tolower_l(Fgetname(C)[0], (locale_t)Fgetlong(LOCALE));")
   (c-lang "lc[1] = '\\0';")
   (c-lang "res = Fmakechar(lc);"))

;;; Recommended usage pattern:

;; Recall that nested functions don't work in clang,
;; which breaks (flet ...) in compiled code.
;; But I don't think this is worth splitting up the file over.

;; Keep some globals here for convenience,
;; keeping the thin layer closer to UNIX.
(defglobal *iconvs* (cons 0 0))
(defglobal *latin-loc* (duplocale))

(defun init-iconv ()
   (setf (car *iconvs*) (iconv-open "ISO-8859-15" "UTF-8"))
   (setf (cdr *iconvs*) (iconv-open "UTF-8" "ISO-8859-15")))
(init-iconv)

;; I could (import "unix")
;; but I prefer some small duplication to dependencies.
(defun i18n--getenv (name)
   (the <string> name)
   (c-lang "char *val;")
   (c-lang "val = getenv(Fgetname(NAME));")
   (c-lang "res = (val == NULL) ? NIL : Fmakestr(val);"))

(defun safe-getenv (name)
   (the <string> name)
   (let ((value (i18n--getenv name)))
        (if (null value)
            "(unset)"
            (string-append "\"" value "\""))))

(defun i18n--perror (string)
   (the <string> string)
   (c-lang "res = NIL; perror(Fgetname(STRING));"))

(defun safe-setlocale ()
   (let ((res (setlocale "")))
        (if (null res)
            (progn (i18n--perror "setlocale")
                   (format (standard-output) "warning: Setting locale failed.~%warning: Please check that your locale settings:~%        LC_ALL = ~A~%        LANG = ~A~%    are supported and installed on your system.~%warning: Falling back to the standard locale (\"C\").~%" (safe-getenv "LC_ALL") (safe-getenv "LANG"))
                   (if (null (setlocale "C"))
                       (progn (i18n--perror "setlocale")
                              (error "setlocale")))))
        res))

(defun str-iconv (cd lstr)
   (the <longnum> cd)(the <string> lstr)
   (c-lang "static char ustr[I18N_STR_MAX];")
   (c-lang "const char *inbuf;")
   (c-lang "char *outbuf;")
   (c-lang "size_t inbytesleft, outbytesleft;")
   (c-lang "inbuf = Fgetname(LSTR);")
   (c-lang "inbytesleft = strlen(inbuf);")
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

(defun safe-newlocale (nlocname loc fallback)
   (the <string> nlocname)(the <longnum> loc)(the <string> fallback)
   (let ((res (newlocale nlocname loc)))
        (if (= res 0)
            (progn (i18n--perror "newlocale")
                   (format (standard-output) "warning: Setting locale failed.~%warning: Please check that the locale \"~A\" is supported and installed on your system.~%warning: Falling back to the global locale (\"~A\").~%" nlocname fallback)
                   (setq res loc)))
        res))

(defun init-locale (locname)
   (the <string> locname)
   (if (= *latin-loc* 0)
       (progn (i18n--perror "duplocale")
              (error "duplocale")))
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
                        (setq nlocname (string-append lang-country latin-suffix))
                        (setq *latin-loc* (safe-newlocale nlocname *latin-loc* locname)))))))

(defun isspace (c)
   (the <character> c)
   (isspace-l c *latin-loc*))

(defun strcoll (s1 s2)
   (the <string> s1)(the <string> s2)
   (strcoll-l s1 s2 *latin-loc*))

(defun toupper (c)
   (the <character> c)
   (toupper-l c *latin-loc*))

(defun tolower (c)
   (the <character> c)
   (tolower-l c *latin-loc*))

(defun cleanup-i18n ()
   (freelocale *latin-loc*)
   (iconv-close (car *iconvs*))
   (iconv-close (cdr *iconvs*)))
