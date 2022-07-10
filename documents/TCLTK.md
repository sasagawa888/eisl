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

## radiobutton

(tk::radiobutton object option)


## checkbutton

(tk::checkbutton object option)


## listbox

(tk::listbox object option)


## scrollbar

(tk::scrollbar object option)

## canvas

(tk:canvas object option)

#### create
(tk::create object class option)

class

```
line 
oval
arc
rectangle
polygon 
image 
bitmap
text
window 
```

## pack

(tk::pack object1 object2 ... objectN)

## command

(tk::command str)

```
> (tk::init)
NIL
> (tk::command "expr 2*3")
expr 2*3
6
T
> 
```



## option


### RGB

-fg #(R G B)   R G B is integer 

### font

e.g.
-font '((ＭＳ ゴシック) 16 underline)


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
