static int CREATE_SERVER(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
Fcheckgbc();
struct sockaddr_in6 addr6;
struct sockaddr_in addr4;
struct sockaddr *addr;
socklen_t len;
({int res;
if(({int res;Fargpush(Ffinddyn(Fmakesym("*DEFAULT-IP-VERSION*")));Fargpush(Fmakesym("IPV6"));res=fast_eq();res;}) != NIL){
addr = &addr6; len = sizeof(addr6);
;}
else{
addr = &addr4; len = sizeof(addr4);
;}res;})
;
({int res;
if(fast_not(({int res;Fargpush(Fcallsubr(Fcar(Fmakesym("CLASS-OF")),Flist1(X))
);Fargpush(Faux(Fmakesym("SOCKET")));res=fast_eq();res;})) != NIL){
res = Fcallsubr(Fcar(Fmakesym("ERROR")),Fcons(Fmakestr("server-create not socket"),Flist1(X)))
;}
 else res = NIL;res;})
;
res = ({int res;int SOCK = NIL;int RESPONSE = NIL;int IP = Fapply(Fcar(Fmakesym("SOCKET-IP")),Flist1(X));int N = Fapply(Fcar(Fmakesym("SOCKET-N")),Flist1(X));int D = Fapply(Fcar(Fmakesym("SOCKET-D")),Flist1(X));({int res;
if(({int res;Fargpush(Ffinddyn(Fmakesym("*DEFAULT-IP-VERSION*")));Fargpush(Fmakesym("IPV6"));res=fast_eq();res;}) != NIL){
res = ({int res;
 res = SOCK = socket(AF_INET6, SOCK_STREAM, 0)
;res;})
;}
else{
res = ({int res;
 res = SOCK = socket(AF_INET, SOCK_STREAM, 0)
;res;})
;}res;})
;
({int res;
if(({int res;Fargpush(SOCK);Fargpush(fast_immediate(0));res=fast_smallerp();res;}) != NIL){
res = Fcallsubr(Fcar(Fmakesym("ERROR")),Fcons(Fmakestr("create-server"),Flist1(NIL)))
;}
 else res = NIL;res;})
;
({int res;
if(({int res;Fargpush(Ffinddyn(Fmakesym("*DEFAULT-IP-VERSION*")));Fargpush(Fmakesym("IPV6"));res=fast_eq();res;}) != NIL){
addr6.sin6_family = AF_INET6; addr6.sin6_port = htons(INT_MASK & N);
;}
else{
addr4.sin_family = AF_INET; addr4.sin_port = htons(INT_MASK & N);
;}res;})
;
({int res;
if(fast_not(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(IP))
) != NIL){
res = ({int res;
if(({int res;Fargpush(Ffinddyn(Fmakesym("*DEFAULT-IP-VERSION*")));Fargpush(Fmakesym("IPV6"));res=fast_eq();res;}) != NIL){
inet_pton(AF_INET6, Fgetname(IP), addr6.sin6_addr.s6_addr);
;}
else{
addr4.sin_addr.s_addr = inet_addr(Fgetname(IP));
;}res;})
;}
else{
res = ({int res;
if(({int res;Fargpush(Ffinddyn(Fmakesym("*DEFAULT-IP-VERSION*")));Fargpush(Fmakesym("IPV6"));res=fast_eq();res;}) != NIL){
addr6.sin6_addr = in6addr_any;
;}
else{
addr4.sin_addr.s_addr = INADDR_ANY;
;}res;})
;}res;})
;
({int res;
 res = RESPONSE = bind((INT_MASK & SOCK), addr, len);
;res;})
;
({int res;
if(({int res;Fargpush(RESPONSE);Fargpush(fast_immediate(0));res=fast_smallerp();res;}) != NIL){
res = Fcallsubr(Fcar(Fmakesym("ERROR")),Fcons(Fmakestr("server-create"),Flist1(NIL)))
;}
 else res = NIL;res;})
;
({int res;
 res = RESPONSE = listen((INT_MASK & SOCK), 5);
;res;})
;
({int res;
if(({int res;Fargpush(RESPONSE);Fargpush(fast_immediate(0));res=fast_smallerp();res;}) != NIL){
res = Fcallsubr(Fcar(Fmakesym("ERROR")),Fcons(Fmakestr("server-create"),Flist1(NIL)))
;}
 else res = NIL;res;})
;
