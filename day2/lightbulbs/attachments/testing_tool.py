#!/usr/bin/env python3

"""
Example usage:

First create an input file, like "sample1.in" with the following contents:
5
VVHVH
HVHHV
VHHVV
HHHVH
HHVVV

For python programs, say "solution.py" (normally run as "pypy3 solution.py"):

    python3 testing_tool.py pypy3 solution.py < sample1.in

For C++ programs, first compile it
(e.g. with "g++ -g -O2 -std=gnu++20 -static  solution.cpp -o solution.out")
and then run

    python3 testing_tool.py ./solution.out < sample1.in

"""

from fcntl import fcntl
import sys
import os
import signal
from typing import List, Tuple

F_SETPIPE_SZ = 1031


def error(msg: str) -> None:
    print("ERROR:", msg, file=sys.stderr)
    sys.exit(1)

def wait_for_child(pid: int) -> None:
    pid, status = os.waitpid(pid, 0)
    if os.WIFSIGNALED(status):
        sig = os.WTERMSIG(status)
        error(f"Program terminated with signal {sig} ({signal.Signals(sig).name})")
    ex = os.WEXITSTATUS(status)
    if ex != 0:
        error(f"Program terminated with exit code {ex}")

def read_line(pid: int, file, what: str) -> str:
    line = file.readline()
    if not line:
        wait_for_child(pid)
        error(f"Failed to read {what}: no more output")
    return line.rstrip("\r\n")

def write_line(file, line: str) -> None:
    try:
        file.write(line + "\n")
        file.flush()
    except BrokenPipeError:
        pass

def run_solution(submission: List[str], N: int, lamps: List[List[chr]], silent: bool):

    c2p_read, c2p_write = os.pipe()
    p2c_read, p2c_write = os.pipe()
    try:
        fcntl(p2c_read, F_SETPIPE_SZ, 1024 * 1024)
    except Exception:
        print("Warning: failed to increase pipe capacity. This may lead to hangs.")
    pid = os.fork()

    if pid == 0:
        os.close(p2c_write)
        os.close(c2p_read)

        os.dup2(p2c_read, 0)
        os.dup2(c2p_write, 1)

        try:
            os.execvp(submission[0], submission)
        except Exception as e:
            error(f"Failed to execute program: {e}")
        assert False, "unreachable"
    else:
        os.close(c2p_write)
        os.close(p2c_read)

        with os.fdopen(p2c_write, "w") as fout:
            with os.fdopen(c2p_read, "r") as fin:

                queries = 0
                write_line(fout, f"{N}")
                while True:

                    line = read_line(pid, fin, f"query {queries+1}")
                    tokens = line.split();
                    if len(tokens) != 1 or (tokens[0] != '!' and tokens[0] != '?'):
                        error(f"[Query {queries+1}] Expected line with ? or !, got: \"{line}\"")
                    lines, grid = [], []
                    for i in range(N):
                        line = read_line(pid, fin, f"query {queries+1}")
                        line = line.replace(" ", "")
                        lines.append(line)
                        if len(line) != N:
                            error(f"[Query {queries+1}] Expected line of length N={N}; got: \"{line}\"")
                        for c in list(line):
                            if c not in ['0','1']:
                                error(f"[Query {queries+1}] Expected one of \"0\" or \"1\"; got \"{c}\"")
                        grid.append(list(line))

                    verticals = [0]*N
                    horizontals = [0]*N
                    turned_on = 0
                    for i in range(N):
                        for j in range(N):
                            if grid[i][j] == '1':
                                turned_on += 1
                                if lamps[i][j] == 'h' or lamps[i][j] == 'H':
                                    horizontals[i] = 1
                                if lamps[i][j] == 'v' or lamps[i][j] == 'V':
                                    verticals[j] = 1
                    sv = sum(verticals)
                    sh = sum(horizontals)
                    cover = N * (sv+sh) - sv*sh

                    lines = "    " + "\n    ".join(lines)


                    if tokens[0] == '!':
                        if not silent:
                            print(f"[*] Answered:\n{lines}")

                        if cover != N*N:
                            error(f"The lamps do not light up the entire grid")

                        # Wait for program to terminate, and read all its output
                        remainder = fin.read()
                        if remainder.strip():
                            error(f"Unexpected trailing output: {remainder}")
                        wait_for_child(pid)

                        return turned_on, queries

                    elif tokens[0] == '?':
                        queries = queries + 1
                        if not silent:
                            print(f"[*] Query #{queries}:\n{lines}")

                        if queries > 2000: 
                            error(f"Too many queries")

                        if not silent:
                            print(f"[*] -> {cover}")

                        write_line(fout, f"{cover}")


def main() -> None:
    silent = False
    args = sys.argv[1:]
    if args and args[0] == "--silent":
        args = args[1:]
        silent = True
    if not args:
        print("Usage:", sys.argv[0], '[--silent] program... < inputfile')
        sys.exit(0)

    N = int(input())
    grid = []
    for i in range(N):
        grid.append(list(input()))
        if len(grid[-1]) != N:
            error("input grid must be N x N")
        for c in grid[-1]:
            if c not in ['v','h','V','H']:
                error(f"unknown character \"{c}\" in input, expected one of \"V\" or \"H\"")

    print(f"[*] Running solution (N = {N})")

    turned_on, queries = run_solution(args, N, grid, silent)

    query_text = "queries" if queries != 1 else "query"
    print("[*] Finished running solution")
    print(f"[*] Final answer uses {turned_on} turned on lamps, and lights up the entire grid")
    print(f"[*] Used {queries} {query_text}")

if __name__ == "__main__":
    main()

