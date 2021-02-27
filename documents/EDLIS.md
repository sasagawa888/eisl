# Edlis
Edlis is a simple editor for ISLisp 

## invoke
(edit filename) in REPL

## Command

```
CTRL+O save file.
CTRL+X quit editor.
CTRL+T insert file.
```

## Editing
Key bindings are hybrid of Emacs and nano.

```
Enter key insert tab for Lisp automatic
Insert key switch insert/overwrite
Tab key insert tab for Lisp
BackSpace key delete backword char
Delete key delete forward char
CTRL+F move to right
CTRL+B move to left
CTRL+P move to up
CTRL+N move to down
CTRL+J end of line
CTRL+D delete
CTRL+H backspace
CTRL+A begin of line
CTRL+E end of line
CTRL+V page up
ESC V page down
CTRL+K cut selection
CTRL+U uncut selection
CTRL+L goto line
CTRL+W search word
CTRL+R replace word
ESC TAB complete builtin function or syntax
ESC < goto top page
ESC > goto end page
ESC A mark(or unmark) row for selection ESC A mark current row position. After this operation, cursol up or down reverse selected rows. ESC A again, unmark. Similer to nano editor.
←　→　↑　↓　key is avarable
Home key display top page
End key display end page
PageUp key PageUp
PageDown PageDown o
```