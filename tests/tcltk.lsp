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
  "char number[32];
   strcpy(buff,''label .'');
   strcat(buff,str_to_lower(Fgetname(L)));
   strcat(buff,'' -text {'');
   strcat(buff,Fgetname(S));
   strcat(buff,''}'');")
  (c-lang 
  "sprintf(number,''%d'',Fgetint(W));
   strcat(buff,'' -width '');
   strcat(buff,number);
   sprintf(number,''%d'',Fgetint(H));
   strcat(buff,'' -height '');
   strcat(buff,number);
   strcat(buff,''\n'');")
  (c-lang 
   "Tcl_Eval(interp,buff);"))

;''label .hello -text {Hello World} -width 22 -height 5\n''

(defun tk::pack (l)
  (c-lang 
  "strcpy(buff,''pack .'');
   strcat(buff,str_to_lower(Fgetname(L)));
   strcat(buff,''\n'');
   Tcl_Eval(
    interp,buff);"))

;''pack .hello\n''

(defun main ()
  (tk::init)
  (tk::label 'hello "hello world" 22 5)
  (tk::pack 'hello)
  (tk::mainloop)
  T
)


(defun tk::mainloop ()
    (c-lang "Tk_MainLoop();"))
