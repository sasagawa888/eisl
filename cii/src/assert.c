static const char __attribute__((unused)) rcsid[] = "$Id$";
#include "assert.h"
const Except_T Assert_Failed = { "Assertion failed" };
void (assert)(int e) {
	assert(e);
}
