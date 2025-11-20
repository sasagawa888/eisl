;; C-Curve recursive drawing
;; Uses gr-line to draw on /dev/fb0

(defun c-curve (x0 y0 x1 y1 depth)
  (if (= depth 0)
      (gr-line x0 y0 x1 y1 'red)
      (let* ((mx (div (+ x0 x1) 2))
             (my (div (+ y0 y1) 2))
             (dx (- x1 x0))
             (dy (- y1 y0))
             (nx (+ mx (div (- dy) 2)))
             (ny (+ my (div dx 2))))
        (c-curve x0 y0 nx ny (- depth 1))
        (c-curve nx ny x1 y1 (- depth 1)))))

;; Example usage
(defun draw ()
  (gr-open)
  (gr-cls 'black)
  (c-curve 1200 300 1500 600 10))

;; rect and circle
(defun japan ()
  (gr-open)
  (gr-cls 'black)                
  (draw-flag 900 300 400) 
  (gr-close))

(defun draw-flag (x0 y0 w)
  (let* ((x1 (+ x0 w))
         (h (div (* w 2) 3))
         (y1 (+ y0 h))
         (cx (+ x0 (div w 2)))
         (cy (+ y0 (div h 2)))
         (r (div (* h 3) 10)))
    (gr-rect x0 y0 x1 y1 'white 'fill)
    (gr-circle cx cy r 'red 'fill)))


