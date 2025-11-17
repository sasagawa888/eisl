# Simple Graphics API using /dev/fb0

This is a simple graphics system utilizing `/dev/fb0`. It is implemented as a built-in function. Below are the available functions and their specifications.

To use this feature, you need to switch to a physical terminal. You can switch by pressing CTRL+ALT+F3. To return to your original session, press CTRL+ALT+F7.

You need to use sudo when starting it.

```
sudo eisl
```

The default font on the TTY is small and hard to read. Therefore, please change the settings as follows next.

```
sudo dpkg-reconfigure console-setup
```

- UTF8
- Terminus
- 16*32

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

### `(gr-circle cx cy r color :rest opt)`
- **Description:** Draws a circle with the specified center, radius, and color.
- **Arguments:** 
  - `cx`: Integer X-coordinate of the center
  - `cy`: Integer Y-coordinate of the center
  - `r`: Integer radius
  - `color`: A symbol representing the color
  - `opt`: Symbol fill paint the figure
- **Return:** `T`

---


---

### `(gr-rect x0 y0 x1 y1 color :rest opt)`
- **Description:** Draws a circle with the specified center, radius, and color.
- **Arguments:** 
  - `x0`: Integer X-coordinate of the upper left
  - `y0`: Integer Y-coordinate of the upper left
  - `x1`: Integer X-coordinate of the lower right
  - `y1`: Integer Y-coordinate of the lower right
  - `color`: A symbol representing the color
  - `opt`: Symbol fill paint the figure
- **Return:** `T`

---


### `(gr-line x0 y0 x1 y1 color)`
- **Description:** Draws a line from `(x0, y0)` to `(x1, y1)` with the specified color.
- **Arguments:** 
  - `x0`, `y0`: Integer coordinates of the start point
  - `x1`, `y1`: Integer coordinates of the end point
  - `color`: A symbol representing the color
- **Return:** `T`
