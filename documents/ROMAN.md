# Roman
Convert between Roman numerals and Arabic numerals.

# Usage

```
> (import "roman")
T
```

# Spec

(roman-to-arabian str) I=1 V=5 X=10 L=50 C=100 D=500 M=1000

(arabian-to-roman n)  0 < n <~ 3999 

# Example

```
> (arabian-to-roman 99)
"XCIX"
> (roman-to-arabian "IX")
9
> 
```
