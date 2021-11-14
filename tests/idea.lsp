
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

(defun has-multiple-call-next-method-p (x)
    (let ((count 0)
          (ls x))
        (block call
            (while (not (null ls))
                (if (has-multiple-call-next-method-p1 (car ls))
                    (setq count (+ count 1)))
                (if (has-multiple-call-next-method-p2 (car ls))
                    (return-from call t))
                (setq ls (cdr ls)))
            (if (>= count 2)
                t 
                nil))))

(defun has-multiple-call-next-method-p1 (x)
    (cond ((null x) nil)
          ((and (symbolp x) (eq x 'call-next-method)) t)
          ((atom x) nil)
          ((or (has-multiple-call-next-method-p1 (car x))
               (has-multiple-call-next-method-p1 (cdr x))) t)
          (t nil)))

;;e.g. (list (call-next-method) (call-next-method))
(defun has-multiple-call-next-method-p2 (x)
    (let ((count 0)
          (ls x))
        (while (not (null ls))
            (if (has-multiple-call-next-method-p1 (car ls))
                (setq count (+ count 1)))
            (setq ls (cdr ls)))
        (if (>= count 2)
            t 
            nil)))

