:- [general].

xor(Y):- connected(in(1,Y),in(1,a1)), connected(in(2,Y),in(1,n1)), connected(in(1,Y),in(1,n2)), connected(in(2,Y),in(2,a2)), not(n1), not(n2), connected(out(n1),in(2,a1)),connected(out(n2),in(1,a2)), and(a1), and(a2), connected(out(a1), in(1,o1)), connected(out(a2), in(2,o1)), or(o1), connected(out(o1),out(Y)), my_retract(n1), my_retract(n2), my_retract(a1), my_retract(a2), my_retract(o1).

my_xor([X1,X2],Y):- assert(signal(in(1,x),X1)), assert(signal(in(2,x),X2)), xor(x), signal(out(x),Y), my_retract(x).