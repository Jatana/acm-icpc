a, b = list(map(int, input().split()))
MODO = (2 ** 61) - 1
print((a * b) % MODO, a % MODO, b % MODO)