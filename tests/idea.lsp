

    ;;start--------------------------------------------------------------
    (defun comp-defgeneric (x)
        (format (standard-output) "compiling ~A ~%" (elt x 1))
        (comp-defgeneric0 x)
        (comp-defgeneric1 x)
        (comp-defgeneric2 x)
        (comp-defgeneric3 x))
    
    (defun comp-defmodule (x)
        (let ((name (car (cdr x)))
              (body (cdr (cdr x)))
              (public nil) )
           (for ((s body (cdr s)))
                ((null s)
                 t )
                (if (and (consp (car s)) (eq (car (car s)) 'defpublic))
                    (setq public (cons (elt (car s) 1) public)))
                (compile (modulesubst (car s) name public)))))
    
    (defun comp-defun0 (x)
        (let* ((name (elt x 1))
               (args (elt x 2))
               (n (length args)) )
            (format code0 "static int f_")
            (format-object code0 (conv-name name) nil)
            (format code0 "(int arglist);")
            (format code0 "static int ")
            (format-object code0 (conv-name name) nil)
            (if (not optimize-enable)
                (gen-arg2 code0 args)
                (type-gen-arg2 code0 args (argument-type name)))
            (format code0 ";~%")))
    
    (defun comp-lambda0 (x name)
        (let* ((args (elt x 1))
               (n (length args)) )
            (format code0 "static int f_")
            (format-object code0 (conv-name name) nil)
            (format code0 "(int arglist);")
            (format code0 "static int ")
            (format-object code0 (conv-name name) nil)
            (gen-arg2 code0 args)
            (format code0 ";~%")))
    
    (defun comp-defgeneric0 (x)
        (let* ((name (elt x 1))
               (args (elt x 2))
               (n (length args)) )
            (format code0 "static int f_")
            (format-object code0 (conv-name name) nil)
            (format code0 "(int arglist);")
            (format code0 "static int ")
            (format-object code0 (conv-name name) nil)
            (gen-arg2 code0 args)
            (format code0 ";~%")))
    
    ;;generate f_XXX(int arg){...}
    (defun comp-defun1 (x)
        (let* ((name (elt x 1))
               (args (elt x 2))
               (n (count-args args)) )
            (format code1 "static int f_")
            (format-object code1 (conv-name name) nil)
            (format code1 "(int arglist){~%")
            (gen-arg1 (abs n))
            (gen-assign n)
            (if (not optimize-enable)
                (gen-call (conv-name name) (abs n))
                (type-gen-call name (abs n)))
            (format code1 "}~%")))
    
    (defun comp-lambda1 (x name)
        (let* ((args (elt x 1))
               (n (count-args args)) )
            (format code1 "static int f_")
            (format-object code1 (conv-name name) nil)
            (format code1 "(int arglist){~%")
            (gen-arg1 (abs n))
            (gen-assign n)
            (gen-call (conv-name name) (abs n))
            (format code1 "}~%")))
    
    
    (defun comp-defgeneric1 (x)
        (let* ((name (elt x 1))
               (args (elt x 2))
               (n (count-args args)) )
            (format code1 "static int f_")
            (format-object code1 (conv-name name) nil)
            (format code1 "(int arglist){~%")
            (gen-arg1 (abs n))
            (gen-assign n)
            (gen-call (conv-name name) (abs n))
            (format code1 "}~%")))
    
    ;;genrate int XXX(int x, ...){...} this is main function.
    (defun comp-defun2 (x)
        (let ((name (elt x 1))
              (args (elt x 2))
              (body (cdr (cdr (cdr x)))) )
           (format code2 "static int ")
           (format-object code2 (conv-name name) nil)
           (if (not optimize-enable)
               (gen-arg2 code2 args)
               (type-gen-arg2 code2 args (argument-type name)))
           (format code2 "{~%")
           (format code2 "int res;~%")
           (cond ((and (not optimize-enable) (has-tail-recur-p (macroexpand-all body) name))
                  ;;for tail recursive tempn var;
                  (gen-arg3 (length args)))
                 ((and optimize-enable (has-tail-recur-p (macroexpand-all body) name))
                  (type-gen-arg3 (length args) (argument-type name))))
           (cond ((has-tail-recur-p (macroexpand-all body) name)
                  (format-object code2 (conv-name name) nil)
                  (format code2 "loop:~%")))
           (cond ((not optimize-enable) (gen-shelterpush code2 args) (gen-checkgc)))
           (for ((body1 body (cdr body1)))
                ((null (cdr body1))
                 (if (and (not (not-need-res-p (car body1))) (not (tailcallp (car body1) t name)))
                    (format code2 "res = "))
                 (comp code2 (car body1) args args t name nil nil nil)
                 (if (not (not-need-colon-p (car body1)))
                    (format code2 ";~%"))
                 (if (not optimize-enable)
                    (gen-shelterpop code2 (reverse args)))
                 (format code2 "return(res);}~%") )
                (comp code2 (car body1) args args nil name nil nil nil)
                (if (not (not-need-colon-p (car body1)))
                    (format code2 ";~%")))))
    
    (defun comp-lambda2 (body env args name clos)
        (let ((stream (lambda-stream-callee)))
           (format stream "static int ")
           (format-object stream (conv-name name) nil)
           (gen-arg2 stream args)
           (format stream "{~%")
           (format stream "int res;~%")
           (cond ((has-tail-recur-p body name)
                  (format-object stream (conv-name name) nil)
                  (format stream "loop:~%")))
           (gen-shelterpush stream args)
           (for ((body1 body (cdr body1)))
                ((null (cdr body1))
                 (if (not (not-need-res-p (car body1)))
                    (format stream "res = "))
                 (comp stream (car body1) args args nil name nil nil clos)
                 (format stream ";~%")
                 (gen-shelterpop stream (reverse args))
                 (format stream "return(res);}~%") )
                (comp stream (car body1) args args nil name nil nil clos)
                (format stream ";~%"))))
    
    ;;when lambda nest, select nested str-stream
    ;;for lambda callee
    (defun lambda-stream-callee ()
        (cond ((= lambda-nest 0) code5)
              ((= lambda-nest 1) code5)
              ((= lambda-nest 2) code6)
              ((= lambda-nest 3) code7)
              (t (error* "lambda: over nesting" lambda-nest))))
    
    (defun lambda-stream-caller (global)
        (cond (global code4)
              ((= lambda-nest 1) code2)
              ((= lambda-nest 2) code5)
              ((= lambda-nest 3) code6)
              (t (error* "lambda: over nesting" lambda-nest))))
    
    ;;for lambda find free-variable. if no variable return '(t)
    (defun find-free-variable (x env args)
        (append (find-free-variable1 x env args) '(t)))
    
    (defun find-free-variable1 (x env args)
        (cond ((null x) nil)
              ((and (symbolp x) (not (member x env)) (member x args)) (list x))
              ((atom x) nil)
              (t
               (append
                (find-free-variable1 (car x) env args)
                (find-free-variable1 (cdr x) env args)))))
    
    ;;create free-variable list to set lambda-name symbol
    (defun free-variable-list (stream x)
        (cond ((null x) (format stream "NIL"))
              (t
               (format stream "Fcons(")
               (format-object stream (conv-name (car x)) nil)
               (format stream ",")
               (free-variable-list stream (cdr x))
               (format stream ")"))))
    
    ;;modify for ILOS
    (defun comp-defgeneric2 (x)
        (let* ((name (elt x 1))
               (args (varlis-to-lambda-args (elt x 2)))
               (method (get-method name)) )
            (format code2 "static int ")
            (format code2 (convert (conv-name name) <string>))
            (gen-arg2 code2 args)
            (format code2 "{~%")
            (format code2 "int res=-1;~%")
            (format code2 "int super_flag=0;~%")
            (gen-shelterpush code2 args)
            (gen-checkgc)
            (comp-defgeneric-body method (has-qualifier-p method) args)
            (gen-shelterpop code2 (reverse args))
            (format code2 "if(res==-1) FILOSerror(Fmakesym(\"~A\")," name)
            (gen-error-argument args)
            (format code2 ");~%")
            (format code2 "return(res);}~%")))
    
    (defconstant around 11)
    (defconstant befor 12)
    (defconstant primary 13)
    (defconstant after 14)
    ;;if methods has qualifier(:around :befor :after) return t else nil
    (defun has-qualifier-p (method)
        (cond ((null method) nil)
              ((= (get-method-priority (car method)) primary)
               (has-qualifier-p (cdr method)))
              (t t)))
    
    ;;geberate ILOSerror arguments list
    (defun gen-error-argument (args)
        (cond ((null args)
               (format code2 "NIL"))
              (t
                (format code2 "Fcons(~A," (car args))
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
    
    ;;method priority :around=11 :before=12 :primary=13 :after=14
    #|
    idea memo
    I will rewrite ILOS compile code.
    basic idea is follwoing

    super_flag = 0;
    <<parameter>>
    if(Fadapt(...) && Fadapt(...) && ...) qualifier-method body compile code
    if(!super_flag && (Fadapt(...) && Fadapt(...) && ...) ||
       (super_flag && Fsame(...) && Fsame(...) && ...)) primariy-method compile code 

   <<body>>
    1.There is no qualifier method and it is primary method and it has no (call-next-method)
    comp(body) return(res);
    2.There is no qualifier method and it is primary method and it has tail (call-next-method)
    comp(butlast(body)) comp(next-method-body);
    3.At least a qualifier method exist and all kind of method and it has not (call-next-method)
    comp(body)
    4.At least a qualifier method exist and :around method and it has tail (call-next-method)
    comp(butlast(body)) super_flag=1;

    Other case interpreter occurs an error. Compiler does not consider.

    (call-next-method) -> when :around-mthod super_flag=1 and continue
                       -> when primary-method next-method compile code 

    (next-method-p)  -> compiler can know rest method, so generate simple code.
                        set global-variable next-method-p T or nil and compiler generate T or NIL for (next-method-p)

    Probably code will be more simple.
    |#

    (defun butlast (x)
        (cond ((null x) nil)
              ((null (cdr x)) nil)
              (t (cons (car x) (butlast (cdr x))))))

    (defglobal next-method-p nil)
    
    (defun comp-defgeneric-body (x has_qualifier args)
        (cond ((null x) t)
              (t
               (let* ((varbody (get-method-body (car x)))
                      (varlis (alpha-conv-varlis (car varbody) args))
                      (body (alpha-conv-method (cdr varbody) (method-varlis-to-substlist (car varbody) args)))
                      (priority (get-method-priority (car x))) )
                   (format code2 "if(")
                   (if (= priority primary)
                       (comp-defgeneric-primary-cond varlis)
                       (comp-defgeneric-qualifier-cond varls))
                   (format code2 ")~%{")
                   ;;to compile (next-method-p) set flag 
                   (if (null (cdr x))
                       (setq next-method-p nil)
                       (setq next-method-p t))
                   (cond ((and (not has_qualifier) (not (equal (last body) '(call-next-method))) (= priority primary))
                          (comp-progn1 code2 body (varlis-to-lambda-args varlis) nil nil nil nil nil nil)
                          (format code2 "return(res);"))
                         ((and (not has_qualifier) (equal (last body) '(call-next-method)) (= priority primary))
                          (cond ((null (cdr x)) (format code2 "return(res);"))
                                (t
                                 (let* ((next-varbody (get-method-body (car (cdr x))))
                                       (next-varlis (alpha-conv-varlis (car next-varbody) args))
                                       (next-body (alpha-conv-method (cdr next-varbody) (method-varlis-to-substlist (car next-varbody) args))))
                                   (comp-progn1 code2 (butlast body) (varlis-to-lambda-args varlis) nil nil nil nil nil nil)
                                   (comp-progn1 code2 next-body (varlis-to-lambda-args next-varlis) nil nil nil nil nil nil)
                                   (format code2 "return(res);")))))
                         ((and (not (equal (last body) '(call-next-method))) (not (= priority primary)))
                          (comp-progn1 code2 body (varlis-to-lambda-args varlis) nil nil nil nil nil nil))
                         ((and (equal (last body) '(call-next-method)) (not (= priority primary)))
                          (comp-progn1 code2 (butlast body) (varlis-to-lambda-args varlis) nil nil nil nil nil nil)
                          (format code2 "super_flag=1;")))
                   (format code2 "}~%"))
                   (comp-defgeneric-body (cdr x) has_qualifier args))))
              
                   
    
    ;; ((x <integer>) (y <integer>)) (a b) -> ((a <integer>) (b <integer>))
    ;; ((x <integer>) y) (a b) -> ((a <integer>) b)
    (defun alpha-conv-varlis (x y)
        (cond ((null x) nil)
              ((symbolp (car x))
               (cons (car y) (alpha-conv-varlis (cdr x) (cdr y))))
              (t  
               (cons (list (car y) (elt (car x) 1)) (alpha-conv-varlis (cdr x) (cdr y))))))


    ;; ((x <integer>) (y <integer>)) (a b) -> ((x . a) (y . b))
    ;; ((x <integer>) y) (a b) -> ((x . a) (y . b))
    (defun method-varlis-to-substlist (x y)
        (cond ((null x) nil)
              ((symbolp (car x))
               (cons (cons (car x) (car y))
                     (method-varlis-to-substlist (cdr x) (cdr y))))
              (t
               (cons (cons (car (car x)) (car y))
                     (method-varlis-to-substlist (cdr x) (cdr y))))))

    ;; (COND ((= N 1) 1) ((= N 2) 1) (T (+ (GFIB (- N 1)) (GFIB (- N 2)))))) ((n . a)) -> 
    ;; (COND ((= a 1) 1) ((= a 2) 1) (T (+ (GFIB (- a 1)) (GFIB (- a 2))))))
    (defun alpha-conv-method (x y)
        (cond ((null x) nil)
              ((and (symbolp x) (alpha-var x y)) (alpha-var x y))
              ((atom x) x)
              (t (cons (alpha-conv-method (car x) y)
                       (alpha-conv-method (cdr x) y)))))

    ;; if x is alpha-conv variable substitute 
    ;; else return nil
    ;; x ((x . a)) -> a
    ;; y ((x . a)) -> nil
    (defun alpha-var (x y)
        (cond ((null y) nil)
              ((eq x (car (car y))) (cdr (car y)))
              (t (alpha-var x (cdr y)))))
    
    
    ;;varlis -> C condition
    (defun comp-defgeneric-qualifier-cond (x)
        (cond ((null x) t)
              ((eq (car x) ':rest) t)
              ((eq (car x) '%rest) t)
              ((symbolp (car x)) (comp-defgeneric-qualifier-cond (cdr x)))
              ((consp (car x))
               (format code2 "Fadaptp(")
               (format-object code2 (conv-name (elt (car x) 0)) nil)
               (format code2 ",Fmakesym(\"")
               (format-object code2 (elt (car x) 1) nil)
               (format code2 "\"))")
               (comp-defgeneric-qualifier-cond1 (cdr x)))
              (t (error* "defgeneric" x))))
    
    ;; generate Fadapt(P1) && Fadapt(P2) ... && Fadapt(Pn)  P is each parameter
    ;; Fadaptp check sameclass or superclass.
    (defun comp-defgeneric-qualifier-cond1 (x)
        (cond ((null x) t)
              ((eq (car x) ':rest) t)
              ((eq (car x) '%rest) t)
              ((symbolp (car x)) (comp-defgeneric-qualifier-cond1 (cdr x)))
              ((consp (car x))
               (format code2 " && Fadaptp(")
               (format-object code2 (conv-name (elt (car x) 0)) nil)
               (format code2 ",Fmakesym(\"")
               (format-object code2 (elt (car x) 1) nil)
               (format code2 "\"))")
               (comp-defgeneric-qualifier-cond1 (cdr x)))
              (t (error* "defgeneric" x))))

    ;;varlis -> C condition
    ;;for primary method. if((super_flag==1 && && ) || (super_flag==0 && && ))
    ;;(call-next-method) set supar_flag=1 then super-class primary method is execute.
    ;;not exist (call-next-method) super_flag is default 0. Only same class primary method is executes
    (defun comp-defgeneric-primary-cond (x)
        (format code2 "(super_flag==1 && ")
        (comp-defgeneric-qualifier-cond x)
        (format code2 ") || ")
        (format code2 "(super_flag==0 && ")
        (comp-defgeneric-primary-cond1 x)
        (format code2 ")"))

    ;;generate Feqlassp(P1) && Feqclassp(P2) ... && Feqclassp(Pn)
    ;; Feqlassp check has equal same class.
    (defun comp-defgeneric-primary-cond1 (x)
        (cond ((null x) t)
              ((eq (car x) ':rest) t)
              ((eq (car x) '%rest) t)
              ((symbolp (car x)) (comp-defgeneric-primary-cond1 (cdr x)))
              ((consp (car x))
               (format code2 "Feqclassp(")
               (format-object code2 (conv-name (elt (car x) 0)) nil)
               (format code2 ",Fmakesym(\"")
               (format-object code2 (elt (car x) 1) nil)
               (format code2 "\"))")
               (comp-defgeneric-primary-cond2 (cdr x)))
              (t (error* "defgeneric" x))))
    
    (defun comp-defgeneric-primary-cond2 (x)
        (cond ((null x) t)
              ((eq (car x) ':rest) t)
              ((eq (car x) '%rest) t)
              ((symbolp (car x)) (comp-defgeneric-primary-cond2 (cdr x)))
              ((consp (car x))
               (format code2 " && Feqclassp(")
               (format-object code2 (conv-name (elt (car x) 0)) nil)
               (format code2 ",Fmakesym(\"")
               (format-object code2 (elt (car x) 1) nil)
               (format code2 "\"))")
               (comp-defgeneric-primary-cond2 (cdr x)))
              (t (error* "defgeneric" x))))
    
    
    ;;end--------------------------------------------------------------------

