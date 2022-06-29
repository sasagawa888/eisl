(c-include "<tcl/tcl.h>")
(c-option "-ltcl -ltk")
(c-define "BUFF_SIZE" "1024")

(defun foo ()
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

(defun bar ()
  (c-lang "Tcl_Interp *interp;        

  interp = Tcl_CreateInterp();
  Tcl_Init(interp);               
  Tk_Init(interp); 

  Tcl_Eval(
    interp,
    \"label .hello -text {Hello World} -width 22 -height 5\n\"
    \"pack .hello\n\"
  );

  Tk_MainLoop();
  return 0;")

)