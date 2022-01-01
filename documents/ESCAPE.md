# Escape sequence
ansi escape sequence library.

A library for cursor control in the terminal. I made it to make a CUI editor. Since it uses a C wrapper, please compile it. Cursor index (1,1) means at the top left of the screen. 

# usage
compile 

```
eisl -c

> compile-file("library/escape.lsp)
```

(import "escape")

# functions

|name                     | explanation               |
|-------------------------|---------------------------|
|(esc-move-home)          | move to row=1 col=1       |
|(esc-move-top)           | move to row=2 col=1       |
|(esc-clear-screen-after) | clear screen after cursol |
|(esc-clear-screen-before)| clear screen before cursol|
|(esc-clear-screen)       | clear screen all          |
|(esc-clear-line-after)   | clear line after cursol   |
|(esc-clear-line-before)  | clear line before cursol  |
|(esc-clear-line)         | clear line all            |
|(esc-move-left-margin x) | move cursol n from left   |
|(esc-move-right)         | move cursol right         |
|(esc-move-left)          | move cursol left          |
|(esc-move-up)            | move cursol up            |
|(esc-move-down)          | move cursol down          |
|(esc-scroll)             | scroll screen             |
|(esc-move-left-n x)      | move cursol left x        |
|(esc-move x y)           | move cursol raw=x col=y   |
|(esc-fore-black)         | set fore color black      |
|(esc-fore-red)           | set fore color red        |
|(esc-fore-green)         | set fore color green      |
|(esc-fore-yellow)        | set fore color yellow     |
|(esc-fore-blue)          | set fore color blue       |
|(esc-fore-magenta)       | set fore color magenta    |
|(esc-fore-cyan)          | set fore color cyan       |
|(esc-fore-white)         | set fore color white      |
|(esc-fore-origin)        | set fore color origin     |
|(esc-back-cyan)          | set back color cyan       |
|(esc-back-origin)        | set back color origin     |
|(esc-reverse)            | set reverse mode          |
|(esc-reset)              | reset reverse mode        |
|(esc-bold)               | set bold style            |



