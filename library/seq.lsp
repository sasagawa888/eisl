;;;
;;; seq.lsp : ISLisp 用列関数
;;;
;;;           Copyright (C) 2021 Makoto Hiroi
;;;
(import "macro")

;;;
;;; ISLisp の列関数 : length, elt, set-elt, subseq, map-into
;;;

;;;
;;; 列の変換 : list->vector, list->string, vector->list,
;;;            vector->string, string->list, string->vector
;;;

(defun list->vector (xs) (convert xs <general-vector>))
(defun list->string (xs)
  (let ((in (create-string-output-stream)))
    (dolist (x xs (get-output-stream-string in))
      (format-char in x))))

(defun vector->list (xs) (convert xs <list>))
(defun vector->string (xs)
  (let ((in (create-string-output-stream)))
    (dotimes (i (length xs) (get-output-stream-string in))
      (format-char in (elt xs i)))))

(defun string->list (xs) (convert xs <list>))
(defun string->vector (xs) (convert xs <general-vector>))

;;;
;;; 列の探索 : find, find-if, find-if-not,
;;;            position, position-if, position-if-not,
;;;            count, count-if, count-if-not
;;;

(defun find-if (pred xs)
  (if (listp xs)
      (dolist (x xs) (if (funcall pred x) (return x)))
    (dotimes (i (length xs))
      (let ((x (elt xs i)))
	(if (funcall pred x) (return x))))))

(defun find (item xs)
  (find-if (lambda (x) (eql x item)) xs))

(defun find-if-not (pred xs)
  (find-if (lambda (x) (not (funcall pred x))) xs))

(defun position-if (pred xs)
  (if (listp xs)
      (let ((i 0))
	(dolist (x xs -1)
	  (if (funcall pred x) (return i) (incf i))))
    (dotimes (i (length xs) -1)
      (let ((x (elt xs i)))
	(if (funcall pred x) (return i))))))

(defun position (item xs)
  (position-if (lambda (x) (eql x item)) xs))

(defun position-if-not (pred xs)
  (position-if (lambda (x) (not (funcall pred x))) xs))

(defun count-if (pred xs)
  (let ((c 0))
    (if (listp xs)
	(dolist (x xs c)
	  (if (funcall pred x) (incf c)))
      (dotimes (i (length xs) c)
	(let ((x (elt xs i)))
	  (if (funcall pred x) (incf c)))))))

(defun count (item xs)
  (count-if (lambda (x) (eql x item)) xs))

(defun count-if-not (pred xs)
  (count-if (lambda (x) (not (funcall pred x))) xs))

;;;
;;; 列の修正 : fill, remove, remove-if, remove-if-not
;;;            substitute, substitute-if, substitute-if-not,
;;;            nsubstitute, nsubstitute-if, nsubstitute-if-not,

(defun fill (xs item)
  (if (listp xs)
      (for ((ys xs (cdr ys)))
	   ((null ys) xs)
	   (set-car item ys))
    (dotimes (i (length xs) xs)
      (set-elt item xs i))))

(defun remove-if-not (pred xs)
  (let ((zs nil))
    (if (listp xs)
	(dolist (x xs (nreverse zs))
	  (if (funcall pred x) (push x zs)))
      (dotimes (i (length xs) (if (stringp xs)
				  (list->string (nreverse zs))
				(list->vector (nreverse zs))))
	(let ((x (elt xs i)))
	  (if (funcall pred x) (push x zs)))))))

(defun remove (item xs)
  (remove-if (lambda (x) (eql x item)) xs))

(defun remove-if (pred xs)
  (remove-if-not (lambda (x) (not (funcall pred x))) xs))

(defun substitute-if (newitem pred xs)
  (if (listp xs)
      (let ((a nil))
	(dolist (x xs (nreverse a))
	  (push (if (funcall pred x) newitem x) a)))
    (let* ((k (length xs))
	   (a (subseq xs 0 k)))
      (dotimes (i k a)
	(if (funcall pred (elt a i))
	    (set-elt newitem a i))))))

(defun substitute (newitem olditem xs)
  (substitute-if newitem (lambda (x) (eql x olditem)) xs))

(defun substitute-if-not (newitem pred xs)
  (substitute-if newitem (lambda (x) (not (funcall pred x))) xs))

(defun nsubstitute-if (newitem pred xs)
  (if (listp xs)
      (for ((ys xs (cdr ys)))
	   ((null ys) xs)
	   (if (funcall pred (car ys))
	       (set-car newitem ys)))
    (dotimes (i (length xs) xs)
      (if (funcall pred (elt xs i))
	  (set-elt newitem xs i)))))

(defun nsubstitute (newitem olditem xs)
  (nsubstitute-if newitem (lambda (x) (eql x olditem)) xs))

(defun nsubstitute-if-not (newitem pred xs)
  (nsubstitute-if newitem (lambda (x) (not (funcall pred x))) xs))

;;;
;;; 連結, マッピング, 畳み込みなど (リストは非効率)
;;; concatenate, map, reduce, reduce-right, some, every
;;;
(defun concatenate (result-type &rest args)
  (let* ((i 0)
	 (k (apply #'+ (mapcar #'length args)))
	 (s (case result-type
	      ((<list>) (create-list k))
	      ((<string>) (create-string k))
	      ((<general-vector>) (create-vector k))
	      (t (error "concatenate: illegal type")))))
    (dolist (xs args s)
      (dotimes (j (length xs))
	(set-elt (elt xs j) s i)
	(incf i)))))

(defun map (result-type func seq &rest args)
  (let* ((xs (cons seq args))
	 (k (apply #'min (mapcar #'length xs)))
	 (s (case result-type
	      ((<list>) (create-list k))
	      ((<string>) (create-string k))
	      ((<general-vector>) (create-vector k))
	      (t (error "map: illegal type")))))
    (dotimes (i k s)
      (set-elt (apply func (mapcar (lambda (ys) (elt ys i)) xs)) s i))))

(defun reduce (fn init seq &rest args)
  (let* ((xs (cons seq args))
	 (k (apply #'min (mapcar #'length xs)))
	 (a init))
    (dotimes (i k a)
      (setq a (apply fn a (mapcar (lambda (ys) (elt ys i)) xs))))))

(defun reduce-right (fn init seq &rest args)
  (let* ((xs (cons seq args))
	 (k (apply #'min (mapcar #'length xs)))
	 (a init))
    (for ((i (- k 1) (- i 1)))
	 ((< i 0) a)
	 (setq a (apply fn a (mapcar (lambda (ys) (elt ys i)) xs))))))

(defun some (pred seq &rest args)
  (let* ((xs (cons seq args))
	 (k (apply #'min (mapcar #'length xs))))
    (dotimes (i k)
      (let ((result (apply pred (mapcar (lambda (ys) (elt ys i)) xs))))
	(when result (return result))))))

(defun every (pred seq &rest args)
  (let* ((xs (cons seq args))
	 (k (apply #'min (mapcar #'length xs)))
	 (result nil))
    (dotimes (i k result)
      (setq result (apply pred (mapcar (lambda (ys) (elt ys i)) xs)))
      (unless result (return)))))

;;; end-of-fileS