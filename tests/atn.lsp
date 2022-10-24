#|
ATN Argumented Transition Network

|#

(import "elixir")

;; register
(defglobal np nil)
(defglobal v nil)
(defglobal vp nil)
(defglobal subj nil)

;; stack
(defglobal stack nil)

;; word
(defconstant wdet '(the))
(defconstant wn '(dog book))
(defconstant wnpr '(jhon mary))
(defconstant wvi '(runs))
(defconstant wvt '(likes))

(defun detp (x) (member x wdet))
(defun np (x) (member x wn))
(defun nprp (x) (member x wnpr))
(defun vip (x) (member x wvi))
(defun vtp (x) (member x wvt))



(defun start (s)
    (atn s np/))

(defpattern atn
    (((_x :rest _y) s/) (push) (atn _y s/np))
    (((_x :rest _y) s/np) (push) (atn _y s/vp))
    (((_x :rest _y) s/vp) (pop) t)
    (((_x :rest _y) np/) (atn _y np/det))
    (((_x :rest _y) np/det) (atn _y) np/np))


(defun setr (var val)
    (setq (eval var) val))

(defmacro getr (x)
    `(eval ',x))

(defun push (x)
    (set stack (cons x stack)))

(defun pop ()
    (let ((x (car stack)))
        (setq stack (cdr stack))))

