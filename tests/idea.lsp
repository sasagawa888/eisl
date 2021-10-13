#|
Idea memo ILOS compile
P is primariy method
Q is qualifier method
super is flag default is OFF
=call measn it's method's body has (call-next-method)

case there is no qualifier
1.P1,P2,P3     each method has return
1-1 P1,P2=call,P3  P2,{P3}return

case there is some qualifier
2. Q1,Q2,Q3,P1,P2,P3,Q4,Q5,Q6 each has no return
2-1 Q1,Q2,Q3,P1=call,P2,P3,Q4,Q5,Q6  P1={superON,P2,P3,Q4,Q5,Q6} return
2-2  Q1,Q2=call,Q3,P1,P2,P3,Q4,Q5,Q6  Q2={superON,Q3,P1,P2,P3,Q4,Q5,Q6} return

|#

    ;; flag for (next-method-p)
    ;; delete(defglobal next-method-p nil)
    
    (defun comp-defgeneric-body (x has-qualifier args)
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
                   (cond 
                         ((not has-qualifier)
                          (comp-generic-body1 code2 body x (varlis-to-lambda-args varlis) nil nil nil nil nil nil)
                          (format code2 "return(res);"))
                         (t
                          ;; when there is at least one qualifier, eash method has no return
                          (comp-generic-body1 code2 body x (varlis-to-lambda-args varlis) nil nil nil nil nil nil)))
                   (format code2 "}~%"))
                   (comp-defgeneric-body (cdr x) has-qualifier args))))

    ;;adapt to (next-method-p) (call-next-method) in not last body
    (defun comp-generic-body1 (stream x methods env args tail name global test clos)
        (cond ((null x) t)
              ((null (cdr x))
               (if (and (not (not-need-res-p (car x))) (not (tailcallp (car x) tail name)))
                   (format stream "res = "))
               (comp stream (car x) env args tail name global test clos)
               (if (not (not-need-colon-p (car x)))
                   (format stream ";")))
              ((equal (car x) '(call-next-method))
               ;; generate rest methods and rest body S-exp
               (format stream "{super_flag = 1;")
               (comp-generic-body stream (cdr methods) env args tail name global test clos)
               (comp-generic-body stream (cdr x) env args tail name global test clos)
               (format stream "return(res);}"))
              ((equal (car x) '(if (next-method-p)(call-next-method)))
               ;; generate rest methods and rest body S-exp
               (format stream "{super_flag = 1;")
               ;; when ther is no rest method, generate only rest body S-exp 
               (comp-generic-body stream (cdr methods) env args tail name global test clos)
               (comp-generic-body stream (cdr x) env args tail name global test clos)
               (format stream "return(res);}"))      
              (t
               (comp stream (car x) env args nil name global test clos)
               (if (not (not-need-colon-p (car x)))
                   (format stream ";~%"))
               (comp-generic-body1 stream (cdr x) methods env args tail name global test clos))))       
                   

   