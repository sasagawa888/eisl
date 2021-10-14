#|
Idea memo ILOS compile
P is primariy method
Q is qualifier method
super is flag default is OFF
=call measn it's method's body has (call-next-method)


1.P1,P2,P3     each method has no return
1-1 P1,P2=call,P3  P2,{P3,return}
2. Q1,Q2,Q3,P1,P2,P3,Q4,Q5,Q6 each has no return
2-1 Q1,Q2,Q3,P1=call,P2,P3,Q4,Q5,Q6  P1={superON,P2,P3,Q4,Q5,Q6,return}
2-2  Q1,Q2=call,Q3,P1,P2,P3,Q4,Q5,Q6  Q2={superON,Q3,P1,P2,P3,Q4,Q5,Q6,return} 

|#

    ;; flag for (next-method-p)
    ;; delete(defglobal next-method-p nil)
    
    (defun comp-defgeneric-body (x args)
        (cond ((null x) t)
              (t
               (let* ((varbody (get-method-body (car x)))
                      (varlis (alpha-conv-varlis (car varbody) args))
                      (body (alpha-conv-method (cdr varbody) (method-varlis-to-substlist (car varbody) args)))
                      (priority (get-method-priority (car x))) )
                   (format code2 "if(")
                   (if (= priority primary)
                       (comp-defgeneric-primary-cond varlis)
                       (comp-defgeneric-qualifier-cond varlis))
                   (format code2 ")~%{")
                   (comp-defgeneric-body1 priority body x (varlis-to-lambda-args varlis) arg)
                   (format code2 "}~%"))
                   (comp-defgeneric-body (cdr x) args))))

    ;;x is the method bodies
    (defun comp-defgeneric-body1 (priority x methods env arg)
        (cond ((null x) t)
              ((equal (car x) '(call-next-method))
               ;; generate rest methods and rest body S-exp
               (format code2 "{super_flag = 1;")
               ;; if the method is primary generate only a next method else generate all rest methods
               (if (= priority primariy)
                   (comp-defgeneric-body (car (cdr methods) env arg))
                   (comp-defgeneric-body (cdr methods) env arg))
               (format code2 "super_flag = 0;")
               (comp-defgeneric-body1 priority (cdr x) env arg)
               (format code2 "}~%"))
              ((equal (car x) '(if (next-method-p)(call-next-method)))
               ;; generate rest methods and rest body S-exp
               (format code2 "{super_flag = 1;")
               ;; when ther is no rest method, generate only rest body S-exp 
               (if (= priority primariy)
                   (comp-defgeneric-body (car (cdr methods) env arg))
                   (comp-defgeneric-body (cdr methods) env arg))
               (format code2 "super_flag = 0;")
               (comp-defgeneric-body1 priority (cdr x) env arg)
               (format code2 "}~%"))      
              (t
               (comp stream (car x) env nil nil nil nil nil nil)
               (if (not (not-need-colon-p (car x)))
                   (format stream ";~%"))
               (comp-defgeneric-body1 priority (cdr x) methods env arg))))      
                   

   