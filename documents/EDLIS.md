# Edlis
Edlis is a simple editor for ISLisp .

## Invocation
`(edit filename)` in the REPL.

## Commands

| Key    | Command     |
| ------ | ----------- |
| CTRL+O | Save file   |
| CTRL+X | Quit editor |
| CTRL+T | Insert file |

## Editing
The key bindings are a hybrid of Emacs and nano.

| Key       | Binding                         |
| --------- | ------------------------------- |
| Enter     | Automatically indent for Lisp   |
| Insert    | Switch between insert/overwrite |
| Tab       | Insert tab for Lisp             |
| BackSpace | Delete previous char            |
| Delete    | Delete next char                |
| CTRL+F    | Move right                      |
| CTRL+B    | Move left                       |
| CTRL+P    | Move up                         |
| CTRL+N    | Move down                       |
| CTRL+J    | End of line                     |
| CTRL+D    | Delete                          |
| CTRL+H    | Backspace                       |
| CTRL+A    | Beginning of line               |
| CTRL+E    | End of line                     |
| CTRL+V    | Page up                         |
| ESC V     | Page down                       |
| CTRL+K    | Cut selection                   |
| CTRL+U    | Uncut selection                 |
| CTRL+L    | Go to line                      |
| CTRL+W    | Search for word                 |
| CTRL+R    | Replace word                    |
| ESC TAB   | Complete builtin function or syntax |
| ESC <     | Goto top page                   |
| ESC >     | Goto end page                   |
| ESC A     | Mark (or unmark) row for selection. "ESC A" marks the current row, then cursor up or down selects rows. "ESC A" again unmarks. This is similer to nano. |
| ←　→　↑　↓　| Usual cursor movement          |
| Home      | Display top page                |
| End       | Display end page                |
| PageUp    | Page up                         |
| PageDown  | Page down                       |
