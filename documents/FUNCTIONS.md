# Functions
Search system for ISLisp functions

# Acknowledgments

The program was created by Dr. Gomi. And we translated into English with the permission of Dr. Gomi.

Mr. Poldy made a great contribution to the English translation.

Thank you. 

# Usage

(import "functions")


## Search Function 
List the signatures of the applicable system function, giving a part of the beginning of the function name 
(search-function function-name [short])

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
Give a part of the beginning of the function name to format the description of the corresponding system function
and display it on the screen.

```
   (say function-name [output-file]) display functions that begin with function-name

   (say-all [output-file]) display all system functions explanation as formatted

```
