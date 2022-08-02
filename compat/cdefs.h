/* Wrapper around BSD sys/cdefs.h annotations */

#ifndef COMPAT_CDEFS_H
#define COMPAT_CDEFS_H

#ifndef __dead
#define __dead \
        __attribute__((__noreturn__))
#endif

#ifndef __unused
#define __unused \
        __attribute__((__unused__))
#endif

#ifndef __packed
#define __packed \
        __attribute__((__packed__))
#endif

#endif
