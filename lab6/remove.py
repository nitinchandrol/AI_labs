f = open('output.txt','r')
maxi = 0
for line in f:
	words = line.split(' ')
	if(maxi < len(words)):
		maxi = len(words)
		maxline = line
#	if(words[0].isalpha()):
#		if(len(words[0]) == len(words) - 2):
#			print line,

print maxi, maxline
