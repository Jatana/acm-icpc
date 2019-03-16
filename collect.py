l = '''
FFTNum
FFTSolver
Berleykamp
HungarianDance
Auto
z_function
prefix_function
BipolarDisorder
MaxMatch
MaxMatchWithoutEachVertex
interpol
Bridges
CriticalPoints
determinant
'''

for name in l.split():
	code = open(name + '.cpp').read()
	print()
	print('=' * 10, name, '=' * 10)
	print()
	print(code)