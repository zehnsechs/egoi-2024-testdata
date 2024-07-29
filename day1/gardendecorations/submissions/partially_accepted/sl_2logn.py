#!/usr/bin/env python3
import sys


def combine(sched1, sched2):
    return [
        [y for x in li for y in sched1[x]]
        for li in sched2
    ]


def solve_cycle_rec(n, cycle):
    cn = len(cycle)
    if cn == 1:
        return []
    assert cn > 1
    ncycle = []
    sched = [
        [[i] for i in range(n)]
        for _ in range(3)
    ]
    for i in range(cn//2):
        a = cycle[2*i]
        b = cycle[2*i+1]
        ncycle.append(b)
        if a > b:
            a, b = b, a
        sched[0][b] = [a, b]
        sched[1][a] = [a, b]
        sched[2][b] = [a, b]
    if cn % 2:
        ncycle.append(cycle[-1])
    sched2 = solve_cycle_rec(n, ncycle)
    if not sched2:
        return sched
    return sched[:2] + [combine(sched[2], sched2[0])] + sched2[1:]


def solve_cycle(cycle):
    # cycle[i] should get value from cycle[i+1]
    n = len(cycle)
    assert sorted(cycle) == list(range(n))
    return solve_cycle_rec(n, cycle)


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
