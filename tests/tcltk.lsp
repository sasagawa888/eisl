(c-include "<tcl/tcl.h>")
(c-option "-ltcl -ltk")

(defun bar ()
  (c-lang "Tcl_Interp *interp;        

  interp = Tcl_CreateInterp();
  Tcl_Init(interp);               
  Tk_Init(interp); 

  Tcl_Eval(
    interp,
    ''label .hello -text {Hello World} -width 22 -height 5\n''
    ''pack .hello\n''
  );

  Tk_MainLoop();
  return 0;")

)