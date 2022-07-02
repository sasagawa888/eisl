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

(defun tk::label (obj :rest l)
  (let ((option (label-option l)))
    (c-lang 
      "strcpy(buff,''label .'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,Fgetname(OPTION));
       strcat(buff,''\n'');
       printf(''%s'',buff);
       Tcl_Eval(interp,buff);")))

(defun tk::pack (:rest l)
  (let ((obj (packs l)))
  (c-lang 
  "strcpy(buff,''pack '');
   strcat(buff,str_to_lower(Fgetname(OBJ)));
   strcat(buff,''\n'');
   Tcl_Eval(
    interp,buff);")))


(defun main ()
  (tk::init)
  (tk::label 'hello '-text "hello world" '-width 22 '-hight 5)
  (tk::pack 'hello)
  (tk::mainloop)
  T
)


(defun tk::mainloop ()
    (c-lang "Tk_MainLoop();"))


(defun packs (ls)    
    (cond ((null ls) "")
          (t (string-append (string-append " ." (convert (car ls) <string>))
                            (packs (cdr ls))))))
                            

(defun cadr (x) (car (cdr x)))
(defun cddr (x) (cdr (cdr x)))

(defun label-option (ls)
    (cond ((null ls) "")
          ((eq (car ls) '-text) (string-append (string-append " -text {" (cadr ls) "}")
                                               (label-option (cddr ls))))
          ((eq (car ls) '-width) (string-append (string-append " -width " (convert (cadr ls) <string>))
                                                (label-option (cddr ls))))
          ((eq (car ls) '-hight) (string-append (string-append " -height " (convert (cadr ls) <string>))
                                                (label-option (cddr ls))))))