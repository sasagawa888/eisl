(c-include "<tcl/tcl.h>")
(c-option "-ltcl -ltk")    
(c-define "BUFFSIZE" "1024")
(c-lang "Tcl_Interp *interp;
         char buff[BUFFSIZE];")

(defun tk::init ()
 (c-lang 
 "interp = Tcl_CreateInterp();
  Tcl_Init(interp);               
  Tk_Init(interp); 
  "))

(defun tk::label (l s w h)
  (c-lang 
  "strcpy(buff,''label .'');
   strcat(buff,''hello'');
   strcat(buff,'' -text {Hello World}'');
   strcat(buff,'' -width 22 -height 5\n'');
   Tcl_Eval(interp,buff);"))

;''label .hello -text {Hello World} -width 22 -height 5\n''

(defun tk::pack (l)
  (c-lang 
  "Tcl_Eval(
    interp,
    ''pack .hello\n''
  );"))

(defun main ()
  (tk::init)
  (tk::label 'hello "hello world" 22 5)
  (tk::pack 'hello)
  (tk::mainloop)
  T
)


(defun tk::mainloop ()
    (c-lang "Tk_MainLoop();"))
