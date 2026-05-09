;; ILOS method combination stress tests

(defglobal *call-tree* nil)

(defun add-call-tree (x)
   (setq *call-tree* (cons x *call-tree*)))

(defun reset-call-tree ()
   (setq *call-tree* nil))

(defun get-call-tree ()
   (reverse *call-tree*))

;;
;; classes
;;
(defclass mc00 () ())
(defclass mc11 () ())
(defclass mc22 (mc11) ())
(defclass mc33 (mc22) ())
(defclass mc44 (mc33) ())

(defglobal mc00 (create (class mc00)))
(defglobal mc11 (create (class mc11)))
(defglobal mc22 (create (class mc22)))
(defglobal mc33 (create (class mc33)))
(defglobal mc44 (create (class mc44)))

;;
;; test 1: full method combination chain
;;
(defgeneric mc-test-1-sub (x)
   (:method (x)
      (add-call-tree 'primary-object))

   (:method ((x <standard-object>))
      (add-call-tree 'primary-standard-begin)
      (call-next-method)
      (add-call-tree 'primary-standard-end))

   (:method :around ((x <standard-object>))
      (add-call-tree 'around-standard-begin)
      (if (next-method-p)
          (call-next-method))
      (add-call-tree 'around-standard-end))

   (:method :before ((x <standard-object>))
      (add-call-tree 'before-standard))

   (:method :after ((x <standard-object>))
      (add-call-tree 'after-standard))

   (:method ((x mc11))
      (add-call-tree 'primary-mc11-begin)
      (call-next-method)
      (add-call-tree 'primary-mc11-end))

   (:method :around ((x mc11))
      (add-call-tree 'around-mc11-begin)
      (if (next-method-p)
          (call-next-method))
      (add-call-tree 'around-mc11-end))

   (:method :before ((x mc11))
      (add-call-tree 'before-mc11))

   (:method :after ((x mc11))
      (add-call-tree 'after-mc11))

   (:method ((x mc22))
      (add-call-tree 'primary-mc22-begin)
      (call-next-method)
      (add-call-tree 'primary-mc22-end))

   (:method :around ((x mc22))
      (add-call-tree 'around-mc22-begin)
      (if (next-method-p)
          (call-next-method))
      (add-call-tree 'around-mc22-end))

   (:method :before ((x mc22))
      (add-call-tree 'before-mc22))

   (:method :after ((x mc22))
      (add-call-tree 'after-mc22))

   (:method ((x mc33))
      (add-call-tree 'primary-mc33-begin)
      (call-next-method)
      (add-call-tree 'primary-mc33-end))

   (:method :around ((x mc33))
      (add-call-tree 'around-mc33-begin)
      (if (next-method-p)
          (call-next-method))
      (add-call-tree 'around-mc33-end))

   (:method :before ((x mc33))
      (add-call-tree 'before-mc33))

   (:method :after ((x mc33))
      (add-call-tree 'after-mc33))

   (:method ((x mc44))
      (add-call-tree 'primary-mc44-begin)
      (call-next-method)
      (add-call-tree 'primary-mc44-end))

   (:method :around ((x mc44))
      (add-call-tree 'around-mc44-begin)
      (if (next-method-p)
          (call-next-method))
      (add-call-tree 'around-mc44-end))

   (:method :before ((x mc44))
      (add-call-tree 'before-mc44))

   (:method :after ((x mc44))
      (add-call-tree 'after-mc44))
   )

(defun mc-test-1 (x)
   (reset-call-tree)
   (mc-test-1-sub x)
   (get-call-tree))

;;
;; expected for mc44
;;
(defglobal *mc-test-1-mc44-expected*
   '(around-mc44-begin
     around-mc33-begin
     around-mc22-begin
     around-mc11-begin
     around-standard-begin
     before-mc44
     before-mc33
     before-mc22
     before-mc11
     before-standard
     primary-mc44-begin
     primary-mc33-begin
     primary-mc22-begin
     primary-mc11-begin
     primary-standard-begin
     primary-object
     primary-standard-end
     primary-mc11-end
     primary-mc22-end
     primary-mc33-end
     primary-mc44-end
     after-standard
     after-mc11
     after-mc22
     after-mc33
     after-mc44
     around-standard-end
     around-mc11-end
     around-mc22-end
     around-mc33-end
     around-mc44-end))

(defun mc-test-1-check ()
   (equal (mc-test-1 mc44)
          *mc-test-1-mc44-expected*))

;;
;; test 2: around method does NOT call next-method
;; before/after/primary should not run.
;;
(defgeneric mc-test-2-sub (x)
   (:method ((x <standard-object>))
      (add-call-tree 'primary-standard))

   (:method :before ((x <standard-object>))
      (add-call-tree 'before-standard))

   (:method :after ((x <standard-object>))
      (add-call-tree 'after-standard))

   (:method :around ((x mc22))
      (add-call-tree 'around-mc22-only))

   (:method ((x mc22))
      (add-call-tree 'primary-mc22)
      (call-next-method)))

(defun mc-test-2 (x)
   (reset-call-tree)
   (mc-test-2-sub x)
   (get-call-tree))

(defun mc-test-2-check ()
   (equal (mc-test-2 mc22)
          '(around-mc22-only)))

;;
;; test 3 revised:
;; next-method-p should become NIL at the least specific primary method.
;;
(defgeneric mc-test-3-sub (x)
   (:method ((x <standard-object>))
      (add-call-tree 'primary-standard-begin)
      (if (next-method-p)
          (call-next-method)
          (add-call-tree 'no-next-primary))
      (add-call-tree 'primary-standard-end))

   (:method ((x mc11))
      (add-call-tree 'primary-mc11-begin)
      (call-next-method)
      (add-call-tree 'primary-mc11-end)))

(defun mc-test-3 (x)
   (reset-call-tree)
   (mc-test-3-sub x)
   (get-call-tree))

(defun mc-test-3-check ()
   (equal (mc-test-3 mc11)
          '(primary-mc11-begin
            primary-standard-begin
            no-next-primary
            primary-standard-end
            primary-mc11-end)))

;;
;; test 4: before and after only
;; before: most specific -> least specific
;; after : least specific -> most specific
;;
(defgeneric mc-test-4-sub (x)
   (:method ((x <standard-object>))
      (add-call-tree 'primary-standard))

   (:method :before ((x <standard-object>))
      (add-call-tree 'before-standard))

   (:method :after ((x <standard-object>))
      (add-call-tree 'after-standard))

   (:method :before ((x mc11))
      (add-call-tree 'before-mc11))

   (:method :after ((x mc11))
      (add-call-tree 'after-mc11))

   (:method :before ((x mc22))
      (add-call-tree 'before-mc22))

   (:method :after ((x mc22))
      (add-call-tree 'after-mc22)))

(defun mc-test-4 (x)
   (reset-call-tree)
   (mc-test-4-sub x)
   (get-call-tree))

(defun mc-test-4-check ()
   (equal (mc-test-4 mc22)
          '(before-mc22
            before-mc11
            before-standard
            primary-standard
            after-standard
            after-mc11
            after-mc22)))

;;
;; test 5: call-next-method return value propagation
;;
(defgeneric mc-test-5-sub (x)
   (:method ((x <standard-object>))
      10)

   (:method ((x mc11))
      (+ 1 (call-next-method)))

   (:method ((x mc22))
      (+ 2 (call-next-method)))

   (:method ((x mc33))
      (+ 3 (call-next-method))))

(defun mc-test-5 (x)
   (mc-test-5-sub x))

(defun mc-test-5-check ()
   (= (mc-test-5 mc33) 16))

;;
;; test 6: around return value wrapping
;;
(defgeneric mc-test-6-sub (x)
   (:method ((x <standard-object>))
      1)

   (:method ((x mc11))
      (+ 10 (call-next-method)))

   (:method :around ((x mc11))
      (+ 100 (call-next-method)))

   (:method :around ((x mc22))
      (+ 1000 (call-next-method))))

(defun mc-test-6 (x)
   (mc-test-6-sub x))

(defun mc-test-6-check ()
   (= (mc-test-6 mc22) 1111))

;;
;; test 7: unspecialized primary + specialized before/after
;;
(defgeneric mc-test-7-sub (x)
   (:method (x)
      (add-call-tree 'primary-object))

   (:method :before ((x <standard-object>))
      (add-call-tree 'before-standard))

   (:method :before ((x mc11))
      (add-call-tree 'before-mc11))

   (:method :after ((x <standard-object>))
      (add-call-tree 'after-standard))

   (:method :after ((x mc11))
      (add-call-tree 'after-mc11)))

(defun mc-test-7 (x)
   (reset-call-tree)
   (mc-test-7-sub x)
   (get-call-tree))

(defun mc-test-7-check ()
   (equal (mc-test-7 mc11)
          '(before-mc11
            before-standard
            primary-object
            after-standard
            after-mc11)))

;;
;; run all
;;
(defun run-all ()
   (and (mc-test-1-check)
        (mc-test-2-check)
        (mc-test-3-check)
        (mc-test-4-check)
        (mc-test-5-check)
        (mc-test-6-check)
        (mc-test-7-check)))