:- dynamic signal/2.

or(X):- low(in(1,X)),low(in(2,X)),!, assert(signal(out(X),0)).
or(X):- assert(signal(out(X),1)).

and(X):- high(in(1,X)),high(in(2,X)),!, assert(signal(out(X),1)).
and(X):- assert(signal(out(X),0)).

not(X) :- low(in(1,X)),!,assert(signal(out(X),1)). 
not(X) :- high(in(1,X)),!,assert(signal(out(X),0)).

low(T1) :- signal(T1,0).
high(T1) :- signal(T1,1).

connected(T1,T2):- low(T1),!,assert(signal(T2,0)).
connected(T1,T2):- high(T1),!,assert(signal(T2,1)).

my_retract(G) :- retract(signal(in(_,G),_)), retract(signal(out(G),_)).


