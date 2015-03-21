:- dynamic signal/2.
or(X):- low(in(1,X)),low(in(2,X)),!, assert(signal(out(X),0)).
or(X):- assert(signal(out(X),1)).

and(X):- high(in(1,X)),high(in(2,X)),!, assert(signal(out(X),1)).
and(X):- assert(signal(out(X),0)).

not(X) :- low(in(1,X)),!,assert(signal(out(X),1)). 
not(X) :- high(in(1,X)),!,assert(signal(out(X),0)).
 

low(T1) :- notshorted(T1), signal(T1,0).
high(T1) :- notshorted(T1), signal(T1,1).

grounded(T1):- assert(signal(T1,0)),!.

signalled(T1):- signal(T1,0),!.
signalled(T1):- signal(T1,1),!.
signalled(_):- write('connection missing\n'),!,fail. 

notshorted(T1):- signal(T1,0), signal(T1,1),write('shorted\n'),!,fail.
notshorted(T1):- signal(T1,1), signal(T1,0),write('shorted\n'),!,fail.
notshorted(_).

connected(T1,T2):- signalled(T1), low(T1),!,assert(signal(T2,0)).
connected(T1,T2):- signalled(T1), high(T1),!,assert(signal(T2,1)).

my_not_retract(G):- retract(signal(in(_,G),_)), retract(signal(out(G),_)).

my_retract(G) :- retract(signal(in(1,G),_)), retract(signal(in(2,G),_)), retract(signal(out(G),_)).

verify(and,[X1,X2],Y):- assert(signal(in(1,x),X1)), assert(signal(in(2,x),X2)), and(x), signal(out(x),Y), my_retract(x).
verify(or,[X1,X2],Y):- assert(signal(in(1,x),X1)), assert(signal(in(2,x),X2)), or(x), signal(out(x),Y), my_retract(x).
verify(not,X1,Y):- assert(signal(in(1,x),X1)), not(x), signal(out(x),Y), my_not_retract(x).

verify(xor,[X1,X2],Y):- assert(signal(in(1,x),X1)), assert(signal(in(2,x),X2)), xor(x), signal(out(x),Y), my_retract(x).

verify(full_adder, [X,Y,Z],[A,B]):- assert(signal(in(1,ad1),X)), assert(signal(in(2,ad1),Y)), assert(signal(in(3,ad1),Z)), full_adder(ad1), signal(out(1,ad1),A), signal(out(2,ad1),B), my_add_retract(ad1),!.
