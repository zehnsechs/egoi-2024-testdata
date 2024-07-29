#!/usr/bin/env python3
import sys


def solve_cycle(cycle):
    # cycle[i] should get value from cycle[i+1]
    n = len(cycle)
    assert sorted(cycle) == list(range(n))
    sched = [
        [[i] for i in range(n)]
        for _ in range(6)
    ]

    swaps = [[], []]
    for i in range(n // 2):
        swaps[0].append((i, n-1 - i))
    for i in range((n - 1) // 2):
        swaps[1].append((i, n-2 - i))

    for it in (0, 1):
        for a, b in swaps[it]:
            a = cycle[a]
            b = cycle[b]
            if (a > b) ^ it:
                a, b = b, a
            sched[it*3 + 0][b] = [a, b]
            sched[it*3 + 1][a] = [a, b]
            sched[it*3 + 2][b] = [a, b]
    return sched


def solve(perm):
    n = len(perm)
    seen = [False] * n
    total_sched = []
    inv = [-1] * n
    for i in range(n):
        if seen[i]:
            continue
        cycle = []
        at = i
        while not seen[at]:
            cycle.append(at)
            seen[at] = True
            at = perm[at]
        ren = sorted(cycle)
        for j, k in enumerate(ren):
            inv[k] = j
        subsched = solve_cycle([inv[x] for x in cycle])
        while len(total_sched) < len(subsched):
            total_sched.append([[i] for i in range(n)])
        for it, inds in enumerate(subsched):
            tot_inds = total_sched[it]
            for j in range(len(inds)):
                tot_inds[ren[j]] = [ren[x] for x in inds[j]]

    return total_sched


def assert_solution_ok2(perm, schedule, vals):
    n = len(perm)
    target_vals = [vals[perm[i]] for i in range(n)]
    for it, sched in enumerate(schedule):
        nvals = [0] * n
        for j, inds in enumerate(sched):
            x = 0
            for i in inds:
                if it % 2 == 0:
                    assert i <= j
                else:
                    assert i >= j
                x ^= vals[i]
            nvals[j] = x
        vals = nvals
    if vals != target_vals:
        print(vals)
        print(target_vals)
        print(schedule)
    assert vals == target_vals


def assert_solution_ok(perm, schedule):
    n = len(perm)
    import random
    vals = [random.randrange(2**32) for _ in range(n)]
    assert_solution_ok2(perm, schedule, list(range(n)))
    assert_solution_ok2(perm, schedule, vals)


def main():
    iteration, n = map(int, input().split())
    perm = list(map(int, input().split()))
    assert sorted(perm) == list(range(n))

    schedule = solve(perm)

    if iteration == 0:
        assert_solution_ok(perm, schedule)
        print(len(schedule))
        sys.exit(0)
    else:
        iteration -= 1
        assert 0 <= iteration < len(schedule)
        sched = schedule[iteration]
        bits = [None] * n
        for j in (range(n) if iteration % 2 == 0 else range(n-1, -1, -1)):
            inds = sched[j]
            bits[j] = int(input())
            x = 0
            for i in inds:
                x ^= bits[i]
            print(x)


if __name__ == "__main__":
    main()
