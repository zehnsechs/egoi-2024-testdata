#!/usr/bin/python3
from collections import defaultdict

N, M = map(int, input().split())
conn = defaultdict(list)
for _ in range(M):
    a, b = map(int, input().split())
    conn[a].append(b)
    conn[b].append(a)


def make_subtree(n, tree, only_path):
    for i in conn[n]:
        if i not in tree and not any(j in conn[i] for j in tree[n]):
            tree[n].append(i)
            tree[i] = []
            make_subtree(i, tree, only_path)
            if only_path:
                return


def make_tree():
    for root in range(N):
        for subroot in conn[root]:
            tree = defaultdict(list)
            tree[root] = [subroot]
            tree[subroot] = []
            make_subtree(root, tree, False)
            make_subtree(subroot, tree, True)
            if len(tree) == N:
                return root, subroot, tree


root, subroot, tree = make_tree()

even = list(range(N))
odd = list(range(N))
trap = [root if i == subroot else i for i in range(N)]


def gen_moves(n, depth):
    for i in tree[n]:
        if depth % 2 == 0:
            even[i] = n
        else:
            odd[i] = n
        gen_moves(i, depth + 1)


gen_moves(root, 0)
moves = 3 * N // 2 * [' '.join(map(str, move)) for move in [even, odd, trap]]
print(len(moves))
for move in moves:
    print(move)
