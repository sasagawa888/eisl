# Roman
Convert between Roman numerals and Arabic numerals.

# Usage

```
> (import "roman")
T
```

# Spec

(roman-to-arabic str) I=1 V=5 X=10 L=50 C=100 D=500 M=1000

(arabic-to-roman n)  0 < n <~ 3999 

# Example

```
> (arabic-to-roman 99)
"XCIX"
> (roman-to-arabic "IX")
9
> 
```
