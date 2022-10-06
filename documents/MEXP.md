# Mexp
M-expression translator

under construction

# Usage

```
(import "mexp")
> (mexp)

M> 1+2
3
```

# M-expression
Wikipedia

John McCarthy published the first paper on Lisp in 1960 while a research fellow at the Massachusetts Institute of Technology. In it he described a language of symbolic expressions (S-expressions) that could represent complex structures as lists. Then he defined a set of primitive operations on the S-expressions, and a language of meta-expressions (M-expressions) that could be used to define more complex operations. Finally, he showed how the meta-language itself could be represented with S-expressions, resulting in a system that was potentially self-hosting. The draft version of this paper is known as "AI Memo 8".


# Spec

|class       |M-expression |S-expression |
|------------|-------------|-------------|
|function    |sin[x]       |(sin x)      |
|definition  |foo[x]<-x+1  |(defun foo(x)|
|            |             |    (+ x 1)) |
|variable    |  x          |  x          |
|integer     |  1          |  1          |
|float       |  1.2        |  1.2        |
|string      | "abc"       |  "abc"      |
|list        | (a b c)     |  '(a b c)   |
|formula     | sin[2+3]    |(sin (+ 2 3))|
|cond-clause |[atom[x]->t; |(cond ((atom x) t)|
|            | t->nil]     |      (t nil)|


