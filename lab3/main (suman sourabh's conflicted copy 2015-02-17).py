dict = {}
def tokenize(stmt):
    tokens = set()
    print "to prove: |-", stmt
    separated = separate(stmt)
    while(len(separated) > 1):
        tokens.add(separated[0])
        print "It's sufficient to show: " , tokens , "|- " , separated[1]
        separated = separate(separated[1])
    separated[0] = '(' + separated[0]  + '->F)'
    tokens.add(separated[0])
    print "It's sufficient to show: " , tokens , "|- F"    
    return tokens
        
def separate(stmt):
    tokens = []
    #print stmt
    if(stmt != "" and stmt[0]=='(' and stmt[-1] ==')'):
        stmt = stmt[1:-1]
    stmt = stmt.replace('->','>')
    paranthesis_count = 0
    token = ""
    for ch in stmt:
        if ch == '(':
            paranthesis_count += 1
        elif ch == ')':
            paranthesis_count -= 1
        if(paranthesis_count < 0):
            print paranthesis_count
            print "invalid input string"
        elif (paranthesis_count == 0 and ch == '>'):
            token = token.replace('>','->')
            tokens.append(token)
            token = ""
        else:
            token += ch
    token = token.replace('>','->')        
    tokens.append(token)
    #print tokens
    return tokens

def modus_ponens(theorem_set):
    to_return = set();
    for arg1 in theorem_set:
        #print("statement 1:"+arg1)
        #print("compare with");
        for arg2 in theorem_set:
        #    print(arg2)
            tokens = separate(arg1);
            if(len(tokens) == 2 and tokens[0]==arg2):
            	dict[tokens[1]] = [arg2, arg1]
                to_return.add(tokens[1])
                # print(tokens[1]+" added")
        #print("--------------")
    return to_return

def apply_axiom1(tokens):
	print "( A -> ( B -> A ))"
	while(True):
		A = raw_input("Enter A: ").replace(' ','')
		if(A in tokens or A == 'F'):
			break
		else:
			print "Invalid proposition used"	
	B = raw_input("Enter B: ")
	result_token = '(' + A + '->(' + B + '->' + A +'))'
	dict[result_token] = [A,'Axiom 1']			
	return result_token

def apply_axiom2(tokens):
	return_token_set = set()
#	print "applying axiom 2: (( A -> ( B -> C )) -> (( A -> B ) -> ( A -> C ))) on", tokens
	for token in tokens:
		separated = separate(token)
		if(len(separated) > 1):
			A = separated[0]
			separated = separate(separated[1])
			if(len(separated) > 1):
				B = separated[0]
				C = separated[1]
				result_token = '((' + A + '->' + '(' +  B +'->' + C  + '))' +  '->' + '((' + A +'->' + B +')->(' + A +'->' + C + ')))'				
				dict[result_token] = ['(' + A + '->' + '(' +  B +'->' + C  + '))','Axiom 2']
				return_token_set.add(result_token)
#				print result_token
	return return_token_set

def apply_axiom3(tokens):
#	print "applying axiom 3: ((( A -> F ) -> F ) -> A ) on set ",tokens ;
	set_to_return = set();
	for item in tokens:
		separated = separate(item); #( A -> F ) , F
		if(len(separated)==2 and separated[1]=='F' ):
			separated =separate(separated[0]);  # A , F	
			if(len(separated)==2 and separated[1]=='F' ):
				A = separated[0]
				result_token = '(((' + A +'->F)->F)->' + A + ')'
				dict[result_token] = ['((' + A +'->F)->F)','Axiom 3']
				set_to_return.add(result_token);
#				print result_token
	return set_to_return;	

# def apply_contrapositive(tokens):
# 	set_to_return = set();
# 	# (A->B) -> ((B->F)->(A->F))
# 	for item in tokens:
# 		separated = separate(item);
# 		if(len(separated)==2):			
# 			A = separated[0];
# 			B = separated[1];
# 			result_token ='(('+B+'->F)->('+A+'->F)))';
# 			dict[result_token] = ['('+A+'->'+B')',"contrapositive"];
# 			print item, result_token
# 			set_to_return.add(result_token);
# 	return set_to_return;


stmt =  "((p->q)->(((p->F)->q)->q))"
 
next_tokens = tokenize(stmt);
orig_tokens = next_tokens
tokens = set()
i = 0
while(True):	
	#print "next tokens", next_tokens
	if('F' in  next_tokens):
		print "proved"
		break
	next_tokens = next_tokens.union(apply_axiom2(next_tokens))
	next_tokens = next_tokens.union(apply_axiom3(next_tokens))	
	#next_tokens = next_tokens.union(apply_contrapositive(next_tokens))
	tokens = tokens.union(next_tokens);	
	if(i > 10 or len(next_tokens) == 0):
		print("Human help needed. Current state of the proposition set is:"), tokens
		token = apply_axiom1(tokens)
		tokens.add(token)
		i -= 2
	print "applying modus ponens"	
	next_tokens = modus_ponens(tokens)	
	i = i+1	


#--------------------------------proof------------------------------------
state = {'F'}
proof = ""
print "proof\n----------------------------------"
print "initial propositions", orig_tokens
while( len(state) != 0):
	temp = state |  set()
	for ch in temp:	
		string = ""
		parent = dict[ch]	
		state.remove(ch)	
		string += "=> " +  ch + " from "	
		for i in [0,1]:
			string += parent[i] + ' '	
			if parent[i]  in orig_tokens or parent[i].startswith('Axiom') or parent[i].startswith("contra") :
				pass
			else:	
				state.add(parent[i])				
		proof = string + '\n' +  proof
print proof		