module dextension;

import core.stdc.stdlib : getenv;
import disl;

extern (C):
// C functions like "getenv" imply @system
// betterC implies nothrow, @nogc

int
f_getenv(int arglist)
{
    int             arg1;

    arg1 = car(arglist);
    if (length(arglist) != 1) {
	error(WRONG_ARGS, "getenv", arglist);
    }
    char           *val = getenv(get_name(arg1));
    if (val == null) {
	return NIL;
    } else {
	return make_str(val);
    }
}
