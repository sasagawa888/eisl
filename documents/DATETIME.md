# DateTime

Library for date and time.

# Usage 

```lisp
(import "datetime")
```

# Functions

### (get-decoded-time)
return list of integer. (year month day hour minut second)

### (weekday year month day)
return integer of day. (0-6  sun mon wed thu fri sat)

### Example

```

> (import "datetime")
T
> (get-decoded-time)
(2023 1 9 14 38 30)
> 
> (weekday 1945 4 14)
6
> 

```
