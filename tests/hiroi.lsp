;;
;; eight.l : 8 パズルの解法 (双方向探索)
;;
;;           Copyright (C) 2016 Makoto Hiroi
;;
(import "hash")
(import "seq")

;; ハッシュ関数
(defmethod hash-func ((key <list>))
  (fold-left (lambda (a x) (+ (* a 10) x)) 0 key))

;; 隣接リスト
;; 0 1 2
;; 3 4 5
;; 6 7 8
(defglobal adjacent
  #((1 3)   (0 2 4)   (1 5)
    (0 4 6) (1 3 5 7) (2 4 8)
    (3 7)   (4 6 8)   (5 7)))

;; アクセス関数
(defun get-board (xs) (first xs))
(defun get-space (xs) (second xs))
(defun get-prev (xs) (third xs))
(defun get-dir (xs) (fourth xs))

;; 手順の表示
(defun print-answer-f (st)
  (if (get-prev st)
      (print-answer-f (get-prev st)))
  (format (standard-output) "~A~%" (get-board st)))

(defun print-answer-b (st)
  (while st
    (format (standard-output) "~A~%" (get-board st))
    (setq st (get-prev st))))

(defun print-answer (st1 st2)
  (cond ((eq (get-dir st1) 'f)
         (print-answer-f st1)
         (print-answer-b st2))
        (t
         (print-answer-f st2)
         (print-answer-b st1))))

;; キュー
(defglobal q (create-vector 181440))
(defglobal front 0)
(defglobal rear 0)

(defun enq (x)
  (setf (aref q rear) x)
  (setq rear (+ rear 1))
  x)

(defun deq ()
  (let ((x (aref q front)))
    (setq front (+ front 1))
    x))

(defun emptyp () (= front rear))

;; 幅優先探索 (双方向探索)
(defun solver (start goal)
  (block exit
    (let ((h (create (class <hash>))))
      (sethash h start (enq (list start (position 0 start) nil 'f)))
      (sethash h goal  (enq (list goal  (position 0 goal)  nil 'b)))
      (while (not (emptyp))
        (let* ((st (deq))
               (sp (get-space st)))
            (for-each
             (lambda (x)
               (let ((bd (subseq (get-board st) 0 9)))
                 (setf (elt bd sp) (elt bd x))
                 (setf (elt bd x) 0)
                 (let ((st1 (gethash h bd)))
                   (cond ((null st1)
                          (sethash h bd (enq (list bd x st (get-dir st)))))
                         ((not (eq (get-dir st) (get-dir st1)))
                          (print-answer st st1)
                          (return-from exit t))))))
             (aref adjacent sp)))))))

(defun test ()
  (setq front 0)
  (setq rear 0)
  (solver '(8 6 7 2 5 4 3 0 1) '(1 2 3 4 5 6 7 8 0)))