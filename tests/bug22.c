static int ADD_CALL_TREE(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
Fcheckgbc();
res = ({int res;
 res = Fset_cdr(Fmakesym("*CALL-TREE*"),Fcons(X,Fcdr(Fmakesym("*CALL-TREE*"))));res;});
if(CELLRANGE(X)) X=Fshelterpop();
return(res);}
static int FOO_SUB_30(int X){
int res=20000000;
if(CELLRANGE(X)) Fshelterpush(X);
int Xcopy = X;
Fcheckgbc();
if(Fadaptp(X,Fmakesym("C33")))
{res = ({int arg1,res;
arg1 = Fmakesym("AROUND-C3-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;
if(T != NIL){
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("C22")))
{res = ({int arg1,res;
arg1 = Fmakesym("AROUND-C2-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;
if(T != NIL){
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("AROUND-C1-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;
if(T != NIL){
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("AROUND-<STANDARD-OBJECT>-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;
if(T != NIL){
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("C33")))
{res = ({int arg1,res;
arg1 = Fmakesym("BEFORE-C3");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("C22")))
{res = ({int arg1,res;
arg1 = Fmakesym("BEFORE-C2");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("BEFORE-C1");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("BEFORE-<STANDARD-OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("C33")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C3-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("C22")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C2-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C1-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(1)
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C1-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C2-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C3-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("AFTER-<STANDARD-OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("AFTER-C1");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("C22")))
{res = ({int arg1,res;
arg1 = Fmakesym("AFTER-C2");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("C33")))
{res = ({int arg1,res;
arg1 = Fmakesym("AFTER-C3");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;}
 else res = NIL;res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("AROUND-<STANDARD-OBJECT>-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;}
 else res = NIL;res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("AROUND-C1-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;}
 else res = NIL;res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("AROUND-C2-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;}
 else res = NIL;res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("AROUND-C3-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
return(res);}
if(Fadaptp(X,Fmakesym("C22")))
{res = ({int arg1,res;
arg1 = Fmakesym("AROUND-C2-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;
if(T != NIL){
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("AROUND-C1-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;
if(T != NIL){
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("AROUND-<STANDARD-OBJECT>-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;
if(T != NIL){
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("C22")))
{res = ({int arg1,res;
arg1 = Fmakesym("BEFORE-C2");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("BEFORE-C1");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("BEFORE-<STANDARD-OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("C22")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C2-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C1-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(1)
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C1-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C2-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("AFTER-<STANDARD-OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("AFTER-C1");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("C22")))
{res = ({int arg1,res;
arg1 = Fmakesym("AFTER-C2");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;}
 else res = NIL;res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("AROUND-<STANDARD-OBJECT>-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;}
 else res = NIL;res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("AROUND-C1-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;}
 else res = NIL;res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("AROUND-C2-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
return(res);}
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("AROUND-C1-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;
if(T != NIL){
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("AROUND-<STANDARD-OBJECT>-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;
if(T != NIL){
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("BEFORE-C1");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("BEFORE-<STANDARD-OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C1-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(1)
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C1-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("AFTER-<STANDARD-OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("AFTER-C1");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;}
 else res = NIL;res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("AROUND-<STANDARD-OBJECT>-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;}
 else res = NIL;res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("AROUND-C1-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
return(res);}
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("AROUND-<STANDARD-OBJECT>-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;
if(T != NIL){
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("BEFORE-<STANDARD-OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(1)
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("AFTER-<STANDARD-OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;}
 else res = NIL;res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("AROUND-<STANDARD-OBJECT>-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
return(res);}
if(Fadaptp(X,Fmakesym("C33")))
{res = ({int arg1,res;
arg1 = Fmakesym("BEFORE-C3");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
}
if(Fadaptp(X,Fmakesym("C22")))
{res = ({int arg1,res;
arg1 = Fmakesym("BEFORE-C2");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
}
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("BEFORE-C1");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
}
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("BEFORE-<STANDARD-OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
}
if(Fmatchp(X,Fmakesym("C33")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C3-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("C22")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C2-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C1-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(1)
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C1-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C2-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C3-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
}
if(Fmatchp(X,Fmakesym("C22")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C2-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C1-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(1)
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C1-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C2-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
}
if(Fmatchp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C1-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(1)
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-C1-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
}
if(Fmatchp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-BEGIN");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
res = ({int res;Fargpush(X);
X = Xcopy;
if(1)
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
};
X = Fargpop();
res;})
;
res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<STANDARD-OBJECT>-END");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
}
if(1)
{res = ({int arg1,res;
arg1 = Fmakesym("PRIMARY-<OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
}
if(Fadaptp(X,Fmakesym("<STANDARD-OBJECT>")))
{res = ({int arg1,res;
arg1 = Fmakesym("AFTER-<STANDARD-OBJECT>");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
}
if(Fadaptp(X,Fmakesym("C11")))
{res = ({int arg1,res;
arg1 = Fmakesym("AFTER-C1");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
}
if(Fadaptp(X,Fmakesym("C22")))
{res = ({int arg1,res;
arg1 = Fmakesym("AFTER-C2");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
}
if(Fadaptp(X,Fmakesym("C33")))
{res = ({int arg1,res;
arg1 = Fmakesym("AFTER-C3");
Fshelterpush(arg1);
res = ADD_CALL_TREE(arg1);
arg1=Fshelterpop();
;res;});
}
if(CELLRANGE(X)) X=Fshelterpop();
if(res==20000000) FILOSerror(Fmakesym("FOO-SUB-30"),Fcons(X,NIL));
return(res);}
static int FOO_30(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
Fcheckgbc();
({int res;
 res = Fset_cdr(Fmakesym("*CALL-TREE*"),NIL);res;});
({int arg1,res;
arg1 = X;
Fshelterpush(arg1);
res = FOO_SUB_30(arg1);
arg1=Fshelterpop();
;res;});
res = Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(Fcdr(Fmakesym("*CALL-TREE*"))))
;
if(CELLRANGE(X)) X=Fshelterpop();
return(res);}
static int FOO_36(int A,int B,int C){
int res=20000000;
if(CELLRANGE(A)) Fshelterpush(A);
if(CELLRANGE(B)) Fshelterpush(B);
if(CELLRANGE(C)) Fshelterpush(C);
int Acopy = A;
int Bcopy = B;
int Ccopy = C;
Fcheckgbc();
if(Fmatchp(A,Fmakesym("<INTEGER>")) && Fmatchp(B,Fmakesym("<INTEGER>")))
{res = ({int res;int X = ({int arg1,res;
arg1 = ({int arg1,arg2,arg3,res;
arg1 = Fmakestr("foo");
Fshelterpush(arg1);
arg2 = Fmakestr("bar");
Fshelterpush(arg2);
arg3 = Fmakestr("yab");
Fshelterpush(arg3);
res = FOO_36(arg1,arg2,Fcons(arg3,NIL));
arg3=Fshelterpop();
arg2=Fshelterpop();
arg1=Fshelterpop();
;res;});
Fshelterpush(arg1);
res = Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(arg1));
arg1=Fshelterpop();
;res;});({int res;
 res = A = ({int res;Fargpush(A);Fargpush(fast_immediate(10));res=fast_mult();res;});res;})
;
({int res;
 res = B = ({int res;Fargpush(B);Fargpush(fast_immediate(10));res=fast_mult();res;});res;})
;
({int res;
if(T != NIL){
res = ({int res;
 res = X = Fcons(({int res;Fargpush(A);
A = Acopy;
Fargpush(B);
B = Bcopy;
Fargpush(C);
C = Ccopy;
if(Fadaptp(A,Fmakesym("<INTEGER>")) && Fadaptp(B,Fmakesym("<NUMBER>")))
{res = Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(({int res;Fargpush(A);
A = Acopy;
Fargpush(B);
B = Bcopy;
Fargpush(C);
C = Ccopy;
if(1111)
{res = ({int arg1,arg2,arg3,res;
arg1 = Fmakesym("DEFAULT");
Fshelterpush(arg1);
arg2 = A;
Fshelterpush(ar