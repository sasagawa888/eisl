# Unistd
Wraps core Unix syscalls defined in <unistd.h>

## Usage

```lisp
(import "unistd")
```

## Specification

### Functions

#### `(sleep seconds)`
Sleeps for SECONDS seconds or until a signal arrives that is not ignored. Returns zero if the requested time has elapsed, or the number of seconds to sleep, if the call was interrupted by a signal handler.