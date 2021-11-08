

({int res;      ...          ;res})

<global-var>
rest-method
generic-args  (defgeneric foo args) args
entry-parameter entry of the method  ((a <integer>)(b <number>))
caller-priority  around or primary

<local-var>
clos if in lambda T else NIL
use saved generic-args and rest-method

<lambda>
incorprate generic-args and rest-method as compile code




(list (call-next-method) 'integer)

subrcall('list ({int res;  ?   ;res}) , quote(makesym(integer)) )

?
primary
if(adapt(x,y)... res= ...;return(res); if(adapt(x,y)... res=...;return(res); return(NIL);

around
if(adapt(x,y)... res= ...; if(adapt(x,y)... res=...; return(res);

 when around method in next methods add resturn(res);

(next-method-p)
primary and around
({if(adapt(x,y) return(T); if(adapt(x,y) return(T);})

