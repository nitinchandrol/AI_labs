club(a).	
club(b).
club(c).

climber(X) :- club(X),!.
skier(X) :- club(X).

likes(a,X) :- likes(b,X),!,Fail.

likes(a,rain).
likes(a,snow).


