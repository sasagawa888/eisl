;;; Internationalisation support.
;;; Probably limited to alphabetic languages for now.

(c-include "<locale.h>")
(c-include "<nl_types.h>")

(defun setlocale ()
   (let ((response nil))
        (setq response (c-lang "setlocale(LC_ALL, \"\")"))
        (if (null response)
            (c-lang "setlocale(LC_ALL, \"C\");")))
   (c-lang "res = NIL;"))

(defun catopen (name)
   (the <string> name)
   (c-lang "res = Fmakelong(catopen(Fgetname(NAME), NL_CAT_LOCALE));"))

(defun catgets (catd set-id msg-id s)
   (the <longnum> catd)(the <fixnum> set-id)(the <fixnum> msg-id)(the <string> s)
   (c-lang "res = Fmakestr(catgets(Fgetlong(CATD), SET_ID & INT_MASK, MSG_ID & INT_MASK, Fgetname(S)));"))

(defun catclose (catd)
   (the <longnum> catd)
   (c-lang "res = catclose(Fgetlong(CATD)) | INT_FLAG;"))
