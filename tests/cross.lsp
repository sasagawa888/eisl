;; cross refference

;; dasta ((name1 ref1 ref2 ... refn) (name2 ref1 ref2 ... refn)
(defglobal functions nil)
(defglobal globalvars nil)
(defglobal dynamicvars nil)

(defun cross (fn)
    (let ((instream (open-input-file fn))
          (sexp nil))
        (while (setq sexp (read instream nil nil))
            (analize sexp))
        (close instream))
        t)


(defun analize (x)
    (cond ((eq (car x) 'defun) (reg-fun (elt x 1)) (analize-defun (cdr (cdr (cdr x))) (elt x 1)))
          ((eq (car x) 'defglobal (reg-global (elt x 1))))
          ((eq (car x) 'defdynamic) (reg-dynamic (elt x 1)))))


(defun analize-defun (x fun)
    (cond ((null x) t)
          (t (analize-sexp (car x) fun) (analize-defun (cdr x) fun))))


(defun analize-sexp (x fun)
    (cond ((null x) t)
          ((atom x) t)
          ((subrp (car x)) (analize-args (cdr x) fun))
          (t (add-ref (car x) fun) (analize-args (cdr x) fun))))

(defun analize-args (x fun)
    (cond ((null x) t)
          (t (analize-sexp (car x) fun) (analize-args (cdr x) fun))))

(defun reg-fun (x)
    (if (member x functions)
        t
        (setq functions (cons (cons x nil) functions))))

(defun reg-fun1 (x y)
    (setq functions (cons (list x y) functions)))


(defun add-ref (x fun)
    (let ((dt (assoc fun functions)))
        (cond ((null dt) (reg-fun1 fun x))
              ((member x dt) t)
              (t (add-ref1 dt x)))))


(defun add-ref1 (dt x)
    (cond ((null (cdr dt)) (set-cdr (list x) dt))
          (t (add-ref1 (cdr dt) x))))


