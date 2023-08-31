;;; GPS(General problem Solver) PAIP


(defglobal *ops* nil)
(defglobal *dbg* nil)



;; solve goals  
(defun gps (state goals)
    (if (gps1 state goals)
        t
        nil))

(defun gps1 (state goals)
    (if (null goals)
        state
        (let ((state1 (solve state (car goals))))
            (if state1
                (gps1 state1 (cdr goals))
                nil))))

;; solve a goal
(defun solve (state goal)
    (dbgprt state goal)
    (cond ((achieve state goal) state)
          (t (solve (apply-op state goal) goal))))

;; when goal is member of state, achieved a goal
(defun achieve (state goal)
    (if (member goal state) t nil))

;; apply goal on rule *ops*
(defun apply-op (state goal)
    (apply-op1 state goal *ops*))
    
;; sub program of apply
(defun apply-op1 (state goal ops)
    (cond ((null ops) nil) ;false 
          ((appropriate-p state goal (car ops)) ;success goal
           (format (standard-output) "executing ~A~%" (op-action (car ops)))
           (union (set-difference state (op-del-list (car ops))) (op-add-list (car ops))))
          (t (apply-op1 state goal (cdr ops))))) ; try next ops

;; case1 goal is member of add-list and state is subset of precond -> success
;; case2 goal is member of add-list and state is not subset of precond -> try subgoal precond.
;; case3 or else false
(defun appropriate-p (state goal op)
    (if (member goal (op-add-list op))
        (if (subsetp state (op-precond op))
            state
            (gps1 state (op-precond op)))
        nil))
          
(defun union (x y)
    (cond ((null x) y)
          ((member (car x) y) (union (cdr x) y))
          (t (cons (car x) (union (cdr x) y)))))

(defun set-difference (x y)
    (append (set-difference1 x y)
            (set-difference1 y x)))

(defun set-difference1 (x y)
    (cond ((null x) nil)
          ((member (car x) y) (set-difference1 (cdr x) y))
          (t (cons (car x) (set-difference1 (cdr x) y)))))

(defun subsetp (x y)
    (cond ((null x) t)
          ((member (car x) y) (subsetp (cdr x) y))
          (t nil)))

(defun make-op (action precond add-list del-list)
    (list action precond add-list del-list))

(defun op-action (x) (elt x 0))

(defun op-precond (x) (elt x 1))

(defun op-add-list (x) (elt x 2))

(defun op-del-list (x) (elt x 3))

(defun use (x) (setq *ops* x) (length x))

(defun dbgprt (state goal)
    (if *dbg*
        (format (standard-output) "state=~A goal=~A~%" state goal)))

(defun debug (x)
    (if x (setq *dbg* t) (setq *dbg* nil)))

;;; test
(defglobal *school-ops*
    (list
        (make-op 'drive-son-to-school
                 '(son-at-home car-works)
                 '(son-at-school)
                 '(son-at-home))
        (make-op 'shop-installs-battery
                 '(car-needs-battery shop-knows-problem shop-has-money)
                 '(car-works)
                 nil)
        (make-op 'tell-shop-problem
                 `(in-communication-with-shop)
                 '(shop-knows-problem)
                 nil)
        (make-op 'telephone-shop
                 '(know-phone-number)
                 '(in-communication-with-shop)
                 nil)
        (make-op 'look-up-number
                 '(have-phone-book)
                 '(know-phone-number)
                 nil)
        (make-op 'give-shop-money
                 '(have-money)
                 '(shop-has-money)
                 '(have-mone))))

(defun school1 ()
    (use *school-ops*)
    (gps '(son-at-home car-needs-battery have-money have-phone-book)
         '(son-at-school)))

(defun school2 ()
    (use *school-ops*)
    (gps '(son-at-home have-money car-works)
         '(have-money son-at-school)))

(defun school3 ()
    (use *school-ops*)
    (gps '(son-at-home car-needs-battery have-money have-phone-book)
         '(have-money son-at-school)))


(defglobal *banana-ops* 
    (list (make-op 'climb-on-chair
                   '(chair-at-middle-room at-middle-room on-floor)
                   '(at-bananas on-chair)
                   '(at-middle-room on-floor))
          (make-op 'push-chair-from-door-to-middle-room
                   '(chair-at-door at-door)
                   '(chair-at-middle-room at-middle-room)
                   '(chair-at-door at-door))
          (make-op 'walk-from-door-to-middle-room
                   '(at-door on-floor)
                   '(at-middle-room)
                   '(at-door))
          (make-op 'grasp-bananas
                   '(at-bananas empty-handed)
                   '(has-bananas)
                   '(empty-handed))
          (make-op 'drop-ball
                   '(has-ball)
                   '(empty-handed)
                   '(has-ball))
          (make-op 'eat-bananas
                   '(has-bananas)
                   '(empty-handed not-hungry)
                   '(has-bananas hungry))))

(defun banana ()
    (use *banana-ops*)
    (gps '(at-door on-floor has-ball hungry chair-at-door)
         '(not-hungry)))