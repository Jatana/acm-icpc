import sys

req = ''
text = sys.stdin.read()
add = True
zip = ''
for line in text.split('\n'):
	if line[:2] == '# ':
		add = (line.find('/Library/Developer/') == -1)
		req += line + '\n'
	else:
		if add:
			zip += line + '\n'
print(req)
print(zip)