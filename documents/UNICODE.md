# Unicode support
The ISLisp standard does not define Unicode. Extended independently in Easy-ISLisp. Unicode is only available for strings and characters.

# Extended functions

### convert
The convert function can convert a Unicode integer to a character.
It can convert a character to a Unicode integer.
It can convert a string that include unicode character to a list.

e.g.
```
> (convert #\山 <integer>)
23665
> (convert 23665 <character>)
#\山
> (convert "山川" <list>)
(#\山 #\川)
```

### elt
The elt function can run for a string that include unicode character.

e.g.
```
> (elt "山川" 1)
#\川
```
### length
The length function can run for a string that include unicode character.

e.g.
```
> (length "山川") 
2
> 
```

### aref
The aref function can run for a string that include unicode character.

e.g.
```
> (aref "山川" 1)
#\川
> 
```

### set-aref
The set-aref function can run for a string that include unicode character.

e.g.
```
> (defglobal a "山川")
A
> (set-aref #\笹 a 0)
#\笹
> a
"笹川"
> 

```

### subseq
The subseq function can run for a string that include unicode character.

e.g.
```
> (subseq "あいうえお" 2 4)
"うえ"
> 
```

