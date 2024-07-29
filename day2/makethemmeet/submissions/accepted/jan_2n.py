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
                best_tree
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
else:
    even = list(range(N))
    odd = list(range(N))

    def gen_moves(n, depth):
        if depth % 2 == 0:
            even[n] = n
        else:
            odd[n] = n
        for i in tree[n]:
            if depth % 2 == 0:
                even[i] = n
            else:
                odd[i] = n
            gen_moves(i, depth + 1)

    gen_moves(root, 0)
    gen_moves(subroot, 0)
    odd[subroot] = root
    even[subroot] = subroot

    def end_of_path(n, par):
        for i in tree[n]:
            return end_of_path(i, n)
        return n, par

    end1, end2 = end_of_path(subroot, root)
    odd[end1] = end2
    even[end1] = end2

print(2*N)
for _ in range(N):
    print(' '.join(map(str, even)))
    print(' '.join(map(str, odd)))
