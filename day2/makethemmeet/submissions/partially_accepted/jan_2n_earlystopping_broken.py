#!/usr/bin/python3
from collections import defaultdict

N, M = map(int, input().split())
conn = defaultdict(list)
for _ in range(M):
    a, b = map(int, input().split())
    conn[a].append(b)
    conn[b].append(a)


def make_subtree(n, tree, only_path):
    dep = 1
    for i in conn[n]:
        if i not in tree and not any(j in conn[i] for j in tree[n]):
            tree[n].append(i)
            tree[i] = []
            dep = max(dep, make_subtree(i, tree, only_path) + 1)
            if only_path:
                break
    return dep


def make_tree():
    best_dep = (N+1, N+1)
    best_tree = None
    for root in range(N):
        for subroot in conn[root]:
            tree = defaultdict(list)
            tree[root] = [subroot]
            tree[subroot] = []
            tree_dep = make_subtree(root, tree, False)
            path_dep = make_subtree(subroot, tree, True)
            if len(tree) == N and (path_dep, tree_dep) < best_dep:
                best_dep = (path_dep, tree_dep)
                best_tree = root, subroot, tree, tree_dep, path_dep
    return best_tree


root, subroot, tree, tree_dep, path_dep = make_tree()

if tree_dep + path_dep == N:
    def get_path(n, skip):
        for i in tree[n]:
            if i != skip:
                return [n] + get_path(i, None)
        return [n]

    path = list(reversed(get_path(subroot, None))) + get_path(root, subroot)

    even = list(range(N))
    odd = list(range(N))
    for i in range(N // 2):
        even[path[2*i]] = even[path[2*i+1]]
        if 2*i+2 < N:
            odd[path[2*i+1]] = even[path[2*i+2]]

    base_moves = [even, odd]
else:
    even = list(range(N))
    odd = list(range(N))
    odd[subroot] = root

    def gen_moves(n, depth):
        for i in tree[n]:
            if depth % 2 == 0:
                even[i] = n
            else:
                odd[i] = n
            gen_moves(i, depth + 1)

    gen_moves(root, 0)

    base_moves = [even, odd]


def get_next(n, move):
    res = set()
    for i in conn[n]:
        if move[i] == move[n]:
            res.add(i)
    if not res:
        res = {n}
    return res


pos = {(a, b) for a in range(N) for b in range(a)}
moves = []

while pos:
    move = base_moves[len(moves) % len(base_moves)]
    moves.append(move)

    npos = set()
    for a, b in pos:
        na = get_next(a, move)
        nb = get_next(b, move)
        for aa in na:
            for bb in nb:
                if aa != bb and not (aa == b and bb == a):
                    npos.add((aa,bb))
    pos = npos

    if len(moves) > 20000:
        break

print(len(moves))
for move in moves:
    print(' '.join(map(str, move)))
