append([],A,A).
append(A,[],A).
append([H|T],X,[H|Rest]):- append(T,X,Rest).

reverse1([],[]).
reverse1([H|T],Y):-  append(P,[H],Y), reverse1(T,P).

member(X,[X|T]).
member(X,[H|T]):-member(X,T).

rem_dup([],[]).
rem_dup([H|T],X):-member(H,T),!,rem_dup(T,X).
rem_dup([H|T],[H|X]):-rem_dup(T,X).

union1([],[],[]).
union1([],X,X).
union1([H|T],X,Y):-member(H,X),!,union1(T,X,Y).
union1([H|T],X,[H|Y]):- union1(T,X,Y).

intersection([],[],[]).
intersection([],X,[]).
intersection([H|T],X,[H|Y]):- member(H,X),!,intersection(T,X,Y).
intersection([H|T],X,Y):- intersection(T,X,Y).