;; C-Curve recursive drawing
;; Uses gr-line to draw on /dev/fb0

(defun c-curve (x0 y0 x1 y1 depth)
  (if (= depth 0)
      (gr-line x0 y0 x1 y1 'white)
      (let* ((mx (div (+ x0 x1) 2))
             (my (div (+ y0 y1) 2))
             (dx (- x1 x0))
             (dy (- y1 y0))
             (nx (+ mx (div (- dy) 2)))
             (ny (+ my (div dx 2))))
        (c-curve x0 y0 nx ny (- depth 1))
        (c-curve nx ny x1 y1 (- depth 1)))))

;; Example usage
(gr-open)
(gr-cls 'black)

;; Initial line: from left to right
(c-curve 50 150 250 150 10)   ;; Draw with depth 10

(gr-close)