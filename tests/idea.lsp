
    (defun comp-defgeneric2 (x)
        (let* ((name (elt x 1))
               (args (varlis-to-lambda-args (elt x 2)))
               (method (eisl-get-method name)) )
            (setq generic-args args)
            (setq rest-method method)
            (format code2 "static int ")
            (format code2 (convert (conv-name name) <string>))
            (gen-arg2 code2 args)
            (format code2 "{~%")
            (format code2 "int res=20000000;~%")
            (format code2 "int super_flag=0;~%")
            (gen-shelterpush code2 args)
            (gen-checkgc)
            (comp-defgeneric-body method)
            (gen-shelterpop code2 (reverse args))
            (format code2 "if(res==20000000) FILOSerror(Fmakesym(\"~A\")," name)
            (gen-error-argument args)
            (format code2 ");~%")
            (format code2 "return(res);}~%")))
    
    (defconstant around 11)
    (defconstant befor 12)
    (defconstant primary 13)
    (defconstant after 14)
   
    ;;geberate ILOSerror arguments list
    (defun gen-error-argument (args)
        (cond ((null args)
               (format code2 "NIL"))
              (t
                (format code2 "Fcons(~A," (conv-name (car args)))
                (gen-error-argument (cdr args))
                (format code2 ")"))))
    
    ;;ex ((x <list>)y :rest z) -> (x y z)
    (defun varlis-to-lambda-args (x)
        (cond ((null x) nil)
              ((eq (car x) ':rest) (cdr x))
              ((eq (car x) ':rest) (cdr x))
              ((symbolp (car x)) (cons (car x) (varlis-to-lambda-args (cdr x))))
              ((consp (car x)) (cons (car (car x)) (varlis-to-lambda-args (cdr x))))
              (t (error* "defgeneric" x))))
    
    ;; x is methods 
    (defun comp-defgeneric-body (x)
        (cond ((null x) t)
              (t
               (let* ((varbody (eisl-get-method-body (car x)))
                      (varlis (alpha-conv-varlis (car varbody) generic-args))
                      (body (alpha-conv-method (cdr varbody) (method-varlis-to-substlist (car varbody) generic-args)))
                      (priority (eisl-get-method-priority (car x))) )
                   (setq method-args varlis)
                   (setq caller-priotity priority)
                   (format code2 "if(")
                   (cond ((= priority primary)
                          (comp-defgeneric-primary-cond varlis))
                         (nextcall
                          (comp-defgeneric-primary-cond varlis))
                         (t
                          (comp-defgeneric-qualifier-cond varlis)))
                   (format code2 ")~%{")
                   (comp-defgeneric-body1 body x (varlis-to-lambda-args varlis))
                   (if (= priority around)
                       (format code2 "return(res);"))
                   (format code2 "}~%"))
                   (comp-defgeneric-body (cdr x) args))))

    ;;x is the method bodies
    (defun comp-defgeneric-body1 (x methods env)
        (cond ((null x) t) 
              (t
               (setq rest-method (cdr methods))
               (format code2 "res = ")
               (comp code2 (car x) env generic-args nil nil nil nil nil)
               (if (not (not-need-colon-p (car x)))
                   (format code2 ";~%"))
               (comp-defgeneric-body1 (cdr x) methods env))))


    (defun comp-call-next-method ()
        (format code2 "({int res;")
        (comp-call-next-method1 rest-method)
        (format code2 "res;})~%"))

    (defglobal rest-method nil)
    (defglobal method-args nil)
    (defglobal generic-args nil)
    (defglobal caller-priority nil)
    (defun comp-call-next-method1 (next-method)
      (cond ((null next-method) t)
            (t
              (let* ((varbody (eisl-get-method-body (car next-method)))
                     (varlis (alpha-conv-varlis (car varbody) generic-args))
                     (body (alpha-conv-method (cdr varbody) (method-varlis-to-substlist (car varbody) generic-args))))
                 ;; if parameter of next-method is subclass of method-args, ignore this next-method 
                 (if (eisl-superp-for-compiler method-args varlis)
                     (comp-call-next-method1 strean (cdr next-method)))
                 (format code2 "if(")
                 (comp-defgeneric-qualifier-cond varlis)
                 (format code2 ")~%{")
                 (comp-call-next-method2 body (varlis-to-lambda-args varlis))
                 (format code2 "}~%")
                 ;; if next-method is primary then end, else generate rest-methods
                 (if (and (= priority around) (not (null next-method)))
                     (comp-call-next-method1 code2 (cdr next-method)))))))

    (defun comp-call-next-method2 (body env)
        (cond ((null body) t)
              (t
               (format code2 "res = ")
               (comp code2 (car body) env generic-args nil nil nil nil nil)
               (if (not (not-need-colon-p (car body)))
                   (format code2 ";~%"))
               (comp-call-next-method2 (cdr body) env)))) 
   
    ;; comp-next-method-p is allways true in compiler
    (defun comp-next-method-p (stream)
        (format stream "1"))

#|
({int res;      ...          ;res})

<global-var>
rest-method
generic-args  (defgeneric foo args) args
entry-parameter entry of the method  ((a <integer>)(b <number>))
caller-priority  around or primary

<local-var>
clos if in lambda T else NIL
use saved generic-args and rest-method

<lambda>
incorprate generic-args and rest-method as compile code




(list (call-next-method) 'integer)

subrcall('list ({int res;  ?   ;res}) , quote(makesym(integer)) )

?
primary
if(adapt(x,y)... res= ...;return(res); if(adapt(x,y)... res=...;return(res); return(NIL);

around
if(adapt(x,y)... res= ...; if(adapt(x,y)... res=...; return(res);

 when around method in next methods add resturn(res);

(next-method-p)
primary and around
({if(adapt(x,y) return(T); if(adapt(x,y) return(T);})

|#