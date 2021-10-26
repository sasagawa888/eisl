Script started on Mon Apr 21 19:23:42 1997
% ed test.c
a
main() {
  int i = 10;

  DL("Hello"^H   \n");
  DL(  I(i == 10);
}
.
w
77
q
% # need to pass off any C preprocessor options to nana
% nana -I$HOME/work/play/include test.c
break test.c: 6			# generated debug script
condition $bpnum  (1)  
command $bpnum
silent
cont
end
break test.c: 7
condition $bpnum ( 1  ) && (!(  i == 10  ))
command $bpnum
silent
echo   "DI(""i == 10"")"   has failed at  f : l  with      \n
where
end
% nana-clg -I$HOME/work/play/include test.c
Breakpoint 1 at 0x1592: file test.c, line 6.
Breakpoint 2 at 0x1593: file test.c, line 7.

Program exited normally.
% exit
exit

Script done on Mon Apr 21 19:25:06 1997

