;; test from M.Hiroi home page

;;
;; five.l : 5 パズル
;;
;;          Copyright (C) 2016 Makoto Hiroi
;;
(import "list")

;; 隣接リスト
;; 0 1 2
;; 3 4 5
(defglobal adjacent
  #((1 3) (0 2 4) (1 5)
    (0 4) (1 3 5) (2 4)))

;; アクセス関数
(defun get-board (xs) (first xs))
(defun get-space (xs) (second xs))
(defun get-prev (xs) (third xs))

;; キュー
(defglobal que (create-vector (* 3 4 5 6)))
(defglobal front 0)
(defglobal rear 0)

(defun enq (x)
  (setf (aref que rear) x)
  (setq rear (+ rear 1)))

(defun deq ()
  (let ((x (aref que front)))
    (setq front (+ front 1))
    x))

(defun emptyp () (= front rear))

;; 同一局面のチェック
(defun check-same-state (x)
  (block exit
    (for ((i 0 (+ i 1)))
         ((>= i rear))
         (if (equal (get-board (aref que i)) x)
             (return-from exit t)))))

;; 手順の表示
(defun print-answer (st)
  (if (get-prev st)
      (print-answer (get-prev st)))
  (format (standard-output) "~A~%" (get-board st)))

;; 幅優先探索
(defun solver (start goal)
  (block exit
    (enq (list start (char-index #\0 start) nil))
    (while (not (emptyp))
      (let* ((st (deq))
             (sp (get-space st)))
        (if (equal (get-board st) goal)
            (progn
              (print-answer st)
              (return-from exit t))
          (for-each
           (lambda (x)
             (let ((bd (subseq (get-board st) 0 6)))
               (setf (elt bd sp) (elt bd x))
               (setf (elt bd x) #\0)
               (if (not (check-same-state bd))
                   (enq (list bd x st)))))
           (aref adjacent sp)))))))

(defun test ()
  (setq front 0)
  (setq rear 0)
  (solver "450123" "123450"))

;; アクセス関数
(defun get-move (xs) (third xs))

;; 最長手数の探索
(defun solver-max (start)
  (enq (list start (char-index #\0 start) 0))
  (while (not (emptyp))
    (let* ((st (deq))
           (sp (get-space st)))
      (for-each
       (lambda (x)
         (let ((bd (subseq (get-board st) 0 6)))
           (setf (elt bd sp) (elt bd x))
           (setf (elt bd x) #\0)
           (if (not (check-same-state bd))
               (enq (list bd x (+ (get-move st) 1))))))
       (aref adjacent sp))))
  (for ((move (get-move (aref que (- rear 1))))
        (i (- rear 1) (- i 1)))
       ((/= move (get-move (aref que i))))
       (format (standard-output) "~D: ~A~%" move (get-board (aref que i)))))

(defun test-max ()
  (setq front 0)
  (setq rear 0)
  (solver-max "123450"))
