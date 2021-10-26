# nana_DEFINE(name,args,code) - generates a #define for use in nana-config.h
#   this needs to be redone (the naming and quoting is wonderful).
#
AC_DEFUN(nana_DEFINE,[
AC_MSG_CHECKING([$1])
if test -z "$$1"
then # use code to work out the value
  $3
# else its been defined by the user
fi

if test -z "$$1"
then 
  AC_MSG_RESULT("default")
else 
  AC_MSG_RESULT($$1)
  $1="#define $1$2 $$1"
fi
AC_SUBST($1)
])
