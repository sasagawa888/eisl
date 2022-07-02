# Tcl/Tk

Library to use the Tk GUI.

Under construction.

# Usage

## Install Tcl/Tk

*Linux*: `sudo apt install tcl-dev tk-dev`

*macOS*: `brew install tcl-tk`

## Compile

```
eisl -c
(compile-file "library/tcltk.lsp")
```

## Import

```lisp
(import "tcltk")
```

# Functions

## label

(tk::label object option)


## button
(tk::button object option)


## pack

(tk::pack object1 object2 ... objectN)

# Example

```lisp
(import "tcltk")

(defun main ()
  (tk::init)
  (tk::label 'hello '-text "hello world" '-width 22 '-height 5)
  (tk::pack 'hello)
  (tk::mainloop)
  T)
```
