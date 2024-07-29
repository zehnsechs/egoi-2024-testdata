N, M, Q = map(int, input().split())
input()  # skip k, it's x_i anyway

for _ in range(Q):
    x, y = map(int, input().split())
    print(min(abs(x-y), 2*N-abs(x-y), 1+abs(x+N-y), 1+2*N-abs(x+N-y)))
