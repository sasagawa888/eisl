Script started on Mon Apr 21 19:20:38 1997
% ed main.c
main.c: No such file or directory
a
#include <nana.h>

main() {
  int i ;
  i = 0;
  I(i == 0);
}
.
wq
62
% # if you don't install nana in the main system directories you 
% # need to pass the include and library directories off to gcc
% gcc -L$HOME/work/play/lib -I$HOME/work/play/include main.c -lnana
% ./a.out
%

Script done on Mon Apr 21 19:23:33 1997
