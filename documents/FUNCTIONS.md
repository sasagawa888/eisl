# Functions
Online help system for ISLisp functions.

# Acknowledgments

This program was written by Dr. Gomi, and translated into English with his permission.
"poldy" contributed to the English translation.

# Usage

```lisp
(import "functions")
```

## Search Function 
List the signatures of the applicable system function, given a partial beginning of a function name.
`(search-function function-name [short])`

```
    Exp. (search-function 'char) 
          --->
         (((CHARACTERP OBJ) BOOLEAN) 
          ((CHAR= CHAR1 CHAR2) BOOLEAN) 
           ... )
    Exp. (search-function 'char t) 
          --->
         (CHARACTERP CHAR= ...) 
```

## Say Function
Given a partial beginning of a function name, print the description of the corresponding system function
on the screen.

| Function                          | Description                                             |
| --------------------------------- | --------------------------------------------------------|
| (say function-name [output-file]) | Display functions that begin with function-name         |
| (say-all [output-file])           | Display a formatted description of all system functions |
