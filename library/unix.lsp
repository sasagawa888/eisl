(c-include "<stdlib.h>")

(defun getenv (name)
   (the <string> name)
   (c-lang "char *val;")
   (c-lang "val = getenv(Fgetname(NAME));")
   (c-lang "res = (val == NULL) ? NIL : Fmakestr(val);"))
