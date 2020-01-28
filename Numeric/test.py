from random import randint
MODO = 2 ** 64 - 1 
for i in range(int(1e6)):
	print(randint(0, MODO), randint(0, MODO))
