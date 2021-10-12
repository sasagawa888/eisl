#|
Idea memo ILOS compile
1. 1. If no qualifiers exist.
next is the basic method and is a simple case. Compile the following basic method and return.
2. If the modifier exists and ends with next
If it is the end, allow the superclass and execute after that. Do not return.
3. 3. If the modifier exists and is next except at the end
Compile all subsequent methods while allowing superclasses, compile after next and return 
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
                         ((and (not has-qualifier) (equal (last body) '(call-next-method)) (= priority primary))
                          (cond ((null (cdr x)) (format code2 "return(res);"))
                                (t
                                 (let* ((next-varbody (get-method-body (car (cdr x))))
                                       (next-varlis (alpha-conv-varlis (car next-varbody) args))
                                       (next-body (alpha-conv-method (cdr next-varbody) (method-varlis-to-substlist (car next-varbody) args))))
                                   (comp-progn1 code2 (butlast body) (varlis-to-lambda-args varlis) nil nil nil nil nil nil)
                                   (comp-progn1 code2 next-body (varlis-to-lambda-args next-varlis) nil nil nil nil nil nil)
                                   (format code2 "return(res);")))))
                         ((and has-qualifier (equal (last body) '(call-next-method)))
                          (comp-progn1 code2 (butlast body) (varlis-to-lambda-args varlis) nil nil nil nil nil nil)
                          (format code2 "super_flag=1;"))
                         ((and (not (equal (last body) '(call-next-method))))
                          (comp-generic-body1 code2 body x (varlis-to-lambda-args varlis) nil nil nil nil nil nil)
                          (format code2 "return(res);")))
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
               (format stream "{")
               (comp-generic-body stream (cdr methods) env args tail name global test clos)
               (comp-generic-body stream (cdr x) env args tail name global test clos)
               (format stream "}"))
              ((equal (car x) '(if (next-method-p)(call-next-method)))
               (cond ((null (cdr methods)) t)
                     (t (format stream "{")
                        (comp-generic-body stream (cdr methods) env args tail name global test clos)
                        (comp-generic-body stream (cdr x) env args tail name global test clos)
                        (format stream "}"))))
              (t
               (comp stream (car x) env args nil name global test clos)
               (if (not (not-need-colon-p (car x)))
                   (format stream ";~%"))
               (comp-generic-body1 stream (cdr x) methods env args tail name global test clos))))       
                   

   