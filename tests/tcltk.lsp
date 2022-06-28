(c-include "<tcl/tcl.h>")
(c-option "-ltcl")
(c-define "BUFF_SIZE" "1024")

(defun foo (arg1)
  (c-lang "char buff[BUFF_SIZE];")
  (c-lang "Tcl_Interp *ip = Tcl_CreateInterp();")

  (c-lang "printf(\"\ntcl> \");")
  (c-lang "while (fgets(buff, BUFF_SIZE, stdin) != NULL) {
    if (Tcl_Eval(ip, buff) != TCL_OK) {
      fprintf(stderr, \"%s\n\", Tcl_GetStringResult(ip));
    } else {
      printf(\"%s\n\", Tcl_GetStringResult(ip));
    }
    printf(\"\ntcl> \");
  }")

  (c-lang "Tcl_DeleteInterp(ip);")
  (c-lang "return (T);")
)