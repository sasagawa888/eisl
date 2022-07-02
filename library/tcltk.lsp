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


(defun tk::packs (ls)    
    (cond ((null ls) "")
          (t (string-append (string-append " ." (convert (car ls) <string>))
                            (tk::packs (cdr ls))))))
                            

(defun tk::rgb (v)
    (string-append " #" (convert (elt v 0) <string>)
                        (convert (elt v 1) <string>)
                        (convert (elt v 2) <string>)))

(defun tk::font (ls)
    (cond ((null ls) "")
          ((atom (car ls)) (string-append (convert (car ls) <string>)
                                          (tk::font (cdr ls))))
          ((listp (car ls)) (string-append (tk::font (car ls))
                                           (tk::font (cdr ls))))))

(defun tk::option (ls)
    (cond ((null ls) "")
          ((eq (car ls) '-text) (string-append (string-append " -text \"" (car (cdr ls)) "\"")
                                               (tk::option (cdr (cdr ls)))))
          ((eq (car ls) '-width) (string-append (string-append " -width " (convert (car (cdr ls)) <string>))
                                                (tk::option (cdr (cdr ls)))))
          ((eq (car ls) '-height) (string-append (string-append " -height " (convert (car (cdr ls)) <string>))
                                                (tk::option (cdr (cdr ls)))))
          ((eq (car ls) 'command) (string-append (string-append " -command " (car (cdr ls)))
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
          ((eq (car ls) '-anchor) (string-append (string-append " -anchor " (convert (car (cdr ls)) <string>))
                                                (tk::option (cdr (cdr ls)))))
          ((eq (car ls) '-font) (string-append (string-append " -font " (tk::font (car (cdr ls))))
                                                (tk::option (cdr (cdr ls)))))))
