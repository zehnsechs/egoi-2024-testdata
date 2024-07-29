import sys
from collections import defaultdict

N, K = map(int, input().split())
langs = list(map(int, input().split()))
childs = defaultdict(list)
for i in range(1, N):
    parent = int(input())
    childs[parent].append(i)


def dfs(n, dep, seen_langs):
    lang = langs[n]
    candidate = seen_langs is not None and lang not in seen_langs
    if candidate:
        seen_langs.add(lang)

    local_count = defaultdict(int)
    local_count_lang = defaultdict(lambda: defaultdict(int))
    local_count[dep] += 1
    local_count_lang[lang][dep] += 1
    best_productivity = 0
    best_swaps = 0
    for child in childs[n]:
        inc_local_count, inc_local_count_lang, productivity, swaps = dfs(child, dep+1, seen_langs)
        if len(inc_local_count) > len(local_count):
            inc_local_count, local_count = local_count, inc_local_count
            inc_local_count_lang, local_count_lang = local_count_lang, inc_local_count_lang
        for d, count in inc_local_count.items():
            local_count[d] += count
        for c, count_dep in inc_local_count_lang.items():
            for d, count in count_dep.items():
                local_count_lang[c][d] += count
        if productivity > best_productivity:
            best_productivity, best_swaps = productivity, swaps
        if productivity == best_productivity and swaps < best_swaps:
            best_swaps = swaps

    if candidate:
        seen_langs.remove(lang)
        non_swaps = productivity = 0
        deps = total_count_lang[lang].keys() if len(total_count_lang[lang]) < len(local_count) else local_count.keys()
        for d in deps:
            non_swaps += local_count_lang[lang][d]
            productivity += min(local_count[d], total_count_lang[lang][d])
        swaps = productivity - non_swaps
        if productivity > best_productivity:
            best_productivity, best_swaps = productivity, swaps
        if productivity == best_productivity and swaps < best_swaps:
            best_swaps = swaps

    return local_count, local_count_lang, best_productivity, best_swaps


sys.setrecursionlimit(N+10)
total_count, total_count_lang, _, _ = dfs(0, 0, None)
_, _, productivity, swaps = dfs(0, 0, set())
print(productivity, swaps)
