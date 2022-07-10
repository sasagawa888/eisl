(c-include "<tcl/tcl.h>")
(c-option "-ltcl -ltk" linux)
(c-option "-I/opt/homebrew/opt/tcl-tk/include -L/opt/homebrew/opt/tcl-tk/lib -ltk8.6 -ltkstub8.6 -ltcl8.6 -ltclstub8.6" macos)
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
  (let ((opt (tk::option l)))
    (c-lang 
      "strcpy(buff,''label .'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))

(defun tk::button (obj :rest l)
  (let ((opt (tk::option l)))
    (c-lang 
      "strcpy(buff,''button .'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))


(defun tk::radiobutton (obj :rest l)
  (let ((opt (tk::option l)))
    (c-lang 
      "strcpy(buff,''radiobutton .'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))

(defun tk::checkbutton (obj :rest l)
  (let ((opt (tk::option l)))
    (c-lang 
      "strcpy(buff,''radiobutton .'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))

(defun tk::listbox (obj :rest l)
  (let ((opt (tk::option l)))
    (c-lang 
      "strcpy(buff,''listbox .'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))

(defun tk::scrollbar (obj :rest l)
  (let ((opt (tk::option l)))
    (c-lang 
      "strcpy(buff,''scrollbar .'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))

(defun tk::canvas (obj :rest l)
  (let ((opt (tk::option l)))
    (c-lang 
      "strcpy(buff,''canvas .'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))       

(defun tk::create (obj class :rest l)
  (let ((opt (tk::class-option l)))
    (c-lang 
      "strcpy(buff,''.'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,'' create '');
       strcat(buff,str_to_lower(Fgetname(CLASS)));")
    (c-lang   
      "strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);
       res = Fmakeint(atoi(Tcl_GetStringResult(interp)));")))       

(defun tk::pack (:rest l)
  (let ((obj (tk::packs l)))
  (c-lang 
  "strcpy(buff,''pack '');
   strcat(buff,str_to_lower(Fgetname(OBJ)));
   strcat(buff,''\n'');
   Tcl_Eval(
    interp,buff);")))


(defun tk::mainloop ()
    (c-lang "Tk_MainLoop();"))


(defun tk::command (cmd)
    (c-lang 
      "strcpy(buff,Fgetname(CMD));
       strcat(buff,''\n'');
       printf(''%s'',buff);
       Tcl_Eval(interp,buff);
       printf(''%s\n'', Tcl_GetStringResult(interp));")
    t)


(defun tk::packs (ls)    
    (cond ((null ls) "")
          (t (string-append (string-append " ." (convert (car ls) <string>))
                            (tk::packs (cdr ls))))))
                            

(defun tk::rgb (v)
    (string-append " #" (convert (elt v 0) <string>)
                        (convert (elt v 1) <string>)
                        (convert (elt v 2) <string>)))

(defun tk::list (ls)
    (cond ((null ls) "")
          ((atom (car ls)) (string-append (convert (car ls) <string>)
                                          (tk::list (cdr ls))))
          ((listp (car ls)) (string-append (tk::list (car ls))
                                           (tk::list (cdr ls))))))

(defun tk::widgets (ls)
    (if (not (listp ls)) (error "tk::menu incorrect widdet" ls))
    (cond ((null ls) "")
          (t (string-append (convert (car ls) <string>)
                            (tk::widgets (cdr ls))))))

(defun tk::option (ls)
    (cond ((null ls) "")
          ((eq (car ls) '-text) (cond ((stringp (car (cdr ls)))
                                       (string-append (string-append " -text \"" (car (cdr ls)) "\"")
                                                      (tk::option (cdr (cdr ls)))))
                                      ((listp (car (cdr ls)))
                                       (string-append (string-append " -text \"" (tk::list (car (cdr ls))) "\"")
                                                      (tk::option (cdr (cdr ls)))))))
          ((eq (car ls) '-width) (string-append (string-append " -width " (convert (car (cdr ls)) <string>))
                                                (tk::option (cdr (cdr ls)))))
          ((eq (car ls) '-height) (string-append (string-append " -height " (convert (car (cdr ls)) <string>))
                                                (tk::option (cdr (cdr ls)))))
          ((eq (car ls) '-relief) (string-append (string-append " -relief " (convert (car (cdr ls)) <string>))
                                                (tk::option (cdr (cdr ls)))))                       
          ((eq (car ls) 'command) (string-append (string-append " -command \"" (car (cdr ls)) "\"")
                                                 (tk::option (cdr (cdr ls)))))
          ((eq (car ls) '-xscrollcommand) (string-append (string-append " -xscrollcommand \"" (car (cdr ls)) "\"")
                                                 (tk::option (cdr (cdr ls)))))   	
          ((eq (car ls) '-yscrollcommand) (string-append (string-append " -yscrollcommand \"" (car (cdr ls)) "\"")
                                                 (tk::option (cdr (cdr ls)))))
          ((eq (car ls) '-selectmode)  (string-append (string-append " -selectmode " (car (cdr ls)))
                                                     (tk::option (cdr (cdr ls))))) 
          ((eq (car ls) '-orient)  (string-append (string-append " -orient " (car (cdr ls)))
                                                     (tk::option (cdr (cdr ls))))) 
          ((or (eq (car ls) '-fg) (eq (car ls) '-foreground)) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (strinf-append " -fg " (convert (car (cdr ls)) <string>))
                                                   (tk::option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (strinf-append " -fg " (tk::rgb (car (cdr ls))))
                                                   (tk::option (cdr (cdr ls)))))))
          ((or (eq (car ls) '-bg) (eq (car ls) '-background)) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (strinf-append " -bg " (convert (car (cdr ls)) <string>))
                                                   (tk::option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (strinf-append " -bg " (tk::rgb (car (cdr ls))))
                                                   (tk::option (cdr (cdr ls)))))))
          ((eq (car ls) '-activeforeground) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (strinf-append " -activeforeground " (convert (car (cdr ls)) <string>))
                                                   (tk::option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (strinf-append " -activeforeground " (tk::rgb (car (cdr ls))))
                                                   (tk::option (cdr (cdr ls)))))))
          ((eq (car ls) '-activebackground) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (strinf-append " -activebackground " (convert (car (cdr ls)) <string>))
                                                   (tk::option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (strinf-append " -activebackground " (tk::rgb (car (cdr ls))))
                                                   (tk::option (cdr (cdr ls)))))))
          ((eq (car ls) '-disabledforeground) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (strinf-append " -disabledforeground " (convert (car (cdr ls)) <string>))
                                                   (tk::option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (strinf-append " -disabledforeground " (tk::rgb (car (cdr ls))))
                                                   (tk::option (cdr (cdr ls)))))))                                         
          ((eq (car ls) '-troughcolor) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (strinf-append " -troughcolor " (convert (car (cdr ls)) <string>))
                                                   (tk::option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (strinf-append " -troughcolor " (tk::rgb (car (cdr ls))))
                                                   (tk::option (cdr (cdr ls)))))))
          ((eq (car ls) '-fill) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (strinf-append " -fill " (convert (car (cdr ls)) <string>))
                                                   (tk::option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (strinf-append " -fill " (tk::rgb (car (cdr ls))))
                                                   (tk::option (cdr (cdr ls)))))))
          ((eq (car ls) '-outline) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (strinf-append " -outline " (convert (car (cdr ls)) <string>))
                                                   (tk::option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (strinf-append " -outline " (tk::rgb (car (cdr ls))))
                                                   (tk::option (cdr (cdr ls)))))))
          ((eq (car ls) '-stipple) (string-append (string-append " -stipple " (convert (car (cdr ls)) <string>))
                                                (tk::option (cdr (cdr ls)))))                                          
          ((eq (car ls) '-anchor) (string-append (string-append " -anchor " (convert (car (cdr ls)) <string>))
                                                (tk::option (cdr (cdr ls)))))
          ((eq (car ls) '-font) (string-append (string-append " -font " (tk::list (car (cdr ls))))
                                                (tk::option (cdr (cdr ls)))))))
          

(defun tk::class-option (ls)
    (cond ((null ls) "")
          (t (string-append (string-append " " (convert (car ls) <string>))
                            (tk::class-option (cdr ls))))))