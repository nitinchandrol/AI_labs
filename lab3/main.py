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
	return '(' + A + '->(' + B + '->' + A +'))'

def apply_axiom2(tokens):
	print '(( A -> ( B -> C )) -> (( A -> B ) -> ( A -> C )))'
	while True:
		A = raw_input("Enter A: ").replace(' ','')
		B = raw_input("Enter B: ").replace(' ','')
		C = raw_input("Enter C: ").replace(' ','')
		left = '(' + A + '->' + '(' +  B +'->' + C  + '))'
		if left in tokens:
			break
		else:
			print "Invalid proposition used"
	return '((' + A + '->' + '(' +  B +'->' + C  + '))' +  '->' + '((' + 'A' +'->' + B +')->(' + A +'->' + C + ')))'

def apply_axiom3(tokens):
	print '((( A -> F ) -> F ) -> A )'
	while(True):
		A = raw_input("Enter A: ").replace(' ','')
		left = '((' + A + '->F)->F)'
		if left in tokens:
			break
		else:
			print "Invalid proposition used"
	return '(((' + A + '->F)->F)->' +  A + ')'	





stmt = "((p->q)->(((q->F)->p)->q))" ;
next_tokens = tokenize(stmt);
orig_tokens = next_tokens
tokens = set()
i = 0
while(True):	
	#print "next tokens", next_tokens
	if('F' in  next_tokens):
		print "proved"
		break
	tokens = tokens.union(next_tokens);	
	print "applying modus ponens"
	next_tokens = modus_ponens(tokens)
	i = i+1
	if(i > 10 or len(next_tokens) == 0):
		print("Human help needed. Current state of the proposition set is:"),
		print tokens
		while (1) :			
			axiom = raw_input("enter the axiom number to apply)(1,2,3):")
			if axiom == '1':
				token = apply_axiom1(tokens)
				break
			elif axiom == '2':
				token = apply_axiom2(tokens)
				break
			elif axiom == '3': 
				token = apply_axiom3(tokens)
				break
			else :
				print "invalid axiom number entered"	
		tokens.add(token)			
		i -= 2

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
			if parent[i] not in orig_tokens:
				state.add(parent[i])
			string += parent[i] + ' '	
		proof = string + '\n' +  proof
print proof		