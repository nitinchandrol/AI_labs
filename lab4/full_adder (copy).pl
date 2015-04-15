full_adder(Y):- 
	connected(in(1,Y),in(1,x1)), connected(in(2,Y),in(2,x1)), connected(in(1,Y),in(1,a1)), connected(in(2,Y),in(2,a1)), xor(x1), and(a1), connected(out(x1),in(1,x2)),connected(in(3,Y),in(2,x2)), xor(x2), connected(out(x2),out(2,Y)), connected(out(x1), in(1,a2)), connected(in(3,Y), in(2,a2)), and(a2), connected(out(a1), in(2,o1)), connected(out(a2),in(1,o1)), or(o1), connected(out(o1),out(1,Y)), my_retract(x1), my_retract(x2), my_retract(a1), my_retract(a2), my_retract(o1).

add([X,Y,Z],[A,B]):- assert(signal(in(1,ad1),X)), assert(signal(in(2,ad1),Y)), assert(signal(in(3,ad1),Z)), full_adder(ad1), signal(out(1,ad1),A), signal(out(2,ad1),B), my_add_retract(ad1),!.

my_add_retract(G):- retract(signal(in(1,G),_)), retract(signal(in(2,G),_)), retract(signal(in(3,G),_)), retract(signal(out(1,G),_)),  retract(signal(out(2,G),_)).



