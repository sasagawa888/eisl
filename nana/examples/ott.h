/*
 * ott.h -  over the top example; a customised setup for the ott corporations
 *      new real time system.
 */

#ifndef _ott_h_
#define _ott_h_ 1

/*
 * Runtime invariant checking
 *
 * Each file has its own individual trace level stored in a static variable
 * which can be modified by gdb(1).
 *
 * I0(e) - checks assertion always. These are used for checking that the
 *    outside world (the stuff the hardware engineers have built, etc) 
 *    behaves the way we expect.
 * I1(e) - checks assertion iff FILE:_ott_level >= 1. These are used for
 *    checking between components in the system; e.g. are the arguments
 *    to a function correct.
 * I2(e) - checks assertion iff FILE:_ott_level >= 2. And finally these
 *    are used for all other checks; including the time consuming ones.
 *
 * When an error is detected all invariants simply call restart_system().
 */

static unsigned _ott_I_level = 0; /* check level set for each file */

void restart_system(const char *, int);

#define I_DEFAULT_HANDLER(e,f,l,p) restart_system(e,__LINE__)

#define I0(e) I(e)
#define I1(e) IG(e,_ott_I_level >= 1)
#define I2(e) IG(e,_ott_I_level >= 2)

/*
 * Log messages are broken into 3 categories:
 * 
 * LFAST(e...) - the fast messages that are kept in memory in a circular
 *   for later analysis if the system dies.
 *
 * LLONG(e...) - messages destined for a log file that records everything
 *   the device does in its life.
 *
 * LTERM(e...) - messages destined for the tester's terminal (status,
 *   warnings etc. These come out on stderr.
 *
 * LPLOT(e...) - messages to a plotting process (sorry visualisation engine).
 */

#include <stdio.h>
#include <L_buffer.h>

extern L_BUFFER *_ott_fast; /* buffer for fast messages */
extern FILE *_ott_longterm; /* long term log */
extern FILE *_ott_plotting; /* a plotting process */

#define L_DEFAULT_HANDLER fprintf /* default use print style formatting */

#define LFAST(e...) LHP(L_buffer_printf,_ott_fast,##e)
#define LLONG(e...) LP(_ott_longterm,##e)
#define LTERM(e...) LP(stderr,##e)
#define LPLOT(e...) LP(_ott_plotting,##e)

#include <nana.h>

#endif /* _ott_h_ */

