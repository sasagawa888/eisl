# Simple Graphics API using /dev/fb0

This is a simple graphics system utilizing `/dev/fb0`. It is implemented as a built-in function. Below are the available functions and their specifications.

---

## Functions

### `(gr-open)`
- **Description:** Opens the graphics framebuffer.
- **Arguments:** None
- **Return:** `T` if successful, `NIL` otherwise.

---

### `(gr-close)`
- **Description:** Closes the graphics framebuffer.
- **Arguments:** None
- **Return:** `T`

---

### `(gr-cls color)`
- **Description:** Clears the screen and fills it with the specified color.
- **Arguments:** 
  - `color`: A symbol representing the color (`BLACK`, `BLUE`, `RED`, `MAGENTA`, `GREEN`, `CYAN`, `YELLOW`, `WHITE`).
- **Return:** `T`

---

### `(gr-pset x y color)`
- **Description:** Draws a single pixel at the specified coordinates with the given color.
- **Arguments:** 
  - `x`: Integer X-coordinate
  - `y`: Integer Y-coordinate
  - `color`: A symbol representing the color
- **Return:** `T`

---

### `(gr-circle cx cy r color)`
- **Description:** Draws a circle with the specified center, radius, and color.
- **Arguments:** 
  - `cx`: Integer X-coordinate of the center
  - `cy`: Integer Y-coordinate of the center
  - `r`: Integer radius
  - `color`: A symbol representing the color
- **Return:** `T`

---

### `(gr-line x0 y0 x1 y1 color)`
- **Description:** Draws a line from `(x0, y0)` to `(x1, y1)` with the specified color.
- **Arguments:** 
  - `x0`, `y0`: Integer coordinates of the start point
  - `x1`, `y1`: Integer coordinates of the end point
  - `color`: A symbol representing the color
- **Return:** `T`

## Example
```
;; C-Curve recursive drawing
;; Uses gr-line to draw on /dev/fb0

(defun c-curve (x0 y0 x1 y1 depth)
  (if (= depth 0)
      (gr-line x0 y0 x1 y1 'BLACK)   ;; Base case: draw a line
      (let* ((mx (/ (+ x0 x1) 2))
             (my (/ (+ y0 y1) 2))
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
```