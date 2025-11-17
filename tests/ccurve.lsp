;; C-Curve recursive drawing
;; Uses gr-line to draw on /dev/fb0

(defun c-curve (x0 y0 x1 y1 depth)
  (if (= depth 0)
      (gr-line x0 y0 x1 y1 'BLACK)   ;; Base case: draw a line
      (let* ((mx (div (+ x0 x1) 2))
             (my (div (+ y0 y1) 2))
             ;; Rotate midpoint to form C-curve shape
             (dx (- x1 x0))
             (dy (- y1 y0))
             (nx (- mx dy))
             (ny (+ my dx)))
        ;; Recursive calls
        (c-curve x0 y0 nx ny (- depth 1))
        (c-curve nx ny x1 y1 (- depth 1)))))

;; Example usage
(gr-open)
(gr-cls 'WHITE)

;; Initial line: from left to right
(c-curve 50 150 250 150 10)   ;; Draw with depth 10

(gr-close)