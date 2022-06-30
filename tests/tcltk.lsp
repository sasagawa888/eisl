(c-include "<tcl/tcl.h>")
(c-option "-ltcl -ltk")
(c-lang "Tcl_Interp *interp;")    

(defun init ()
 (c-lang 
 "interp = Tcl_CreateInterp();
  Tcl_Init(interp);               
  Tk_Init(interp); 
  "))

(defun foo ()
  (c-lang 
  "Tcl_Eval(
    interp,
    ''label .hello -text {Hello World} -width 22 -height 5\n''
    );"))

(defun bar ()
  (c-lang 
  "Tcl_Eval(
    interp,
    ''pack .hello\n''
  );"))

(defun main ()
  (init)
  (foo)
  (bar)
  (tk::mainloop)
  T
)


(defun tk::mainloop ()
    (c-lang "Tk_MainLoop();"))
