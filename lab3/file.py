from sets import Set

def tokenize(stmt):
	tokens = set()
	separated = separate(stmt)
	while(len(separated) > 1):
		tokens.add(separated[0])
		separated = separate(separated[1])
	separated[0] = '(' + separated[0]  + '->F)'
	tokens.add(separated[0])    
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
	tokens.append(token)
	#print tokens
	return tokens

def modusPodus(theorem_set):
	to_return = set();
	for arg1 in theorem_set:
		print("statement 1:"+arg1)
		print("compare with");
		for arg2 in theorem_set:
			print(arg2)
			tokens = separate(arg1);
			if(len(tokens) == 2 and tokens[0]==arg2):
				to_return.add(tokens[1])
				print(tokens[1]+" added")
		print("--------------")
	return to_return

stmt = "((p->q)->(((q->F)->p)->q))" ;
print(separate("((q->F)->p)"));
tokens = tokenize(stmt);
print(tokens);

result = tokens.union(modusPodus(tokens));
print(result);


















