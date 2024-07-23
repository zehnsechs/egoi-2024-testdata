#!/usr/bin/env python3
import os
import runpy
import sys
import struct
from typing import List, Tuple


def judge_main() -> None:
    HANDSHAKE_REQ = "must_use_cpp_or_python"
    HANDSHAKE_RESP = "5GTwvkYR"
    ACCEPTED_MSG = "OK:gG7DDasY"

    assert input() == HANDSHAKE_REQ
    print(HANDSHAKE_RESP)

    # Identify the submission file
    parent_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    relevant_files = []
    for dname, dirs, files in os.walk(parent_dir):
        if "unique_J5PUR7Xc" in dname:
            continue
        for fname in files:
            if fname.endswith(".py"):
                relevant_files.append(os.path.join(dname, fname))
    assert len(relevant_files) == 1, "must be exactly one Python file in submission"
    sub_file = relevant_files[0]

    max_iterations = int(input())
    N = int(input())
    perm = list(map(int, input().split()))
    assert sorted(perm) == list(range(N))
    tape = list(map(int, input().split()))
    target_tape = [tape[perm[i]] for i in range(N)]

    # send stdout to stderr for the user program
    real_stdout = os.fdopen(os.dup(1), "w", closefd=False)
    os.dup2(2, 1)

    # redirect the stdin fd to make it slightly harder to read stdin twice
    os.close(0)
    os.open("/dev/null", os.O_RDONLY)

    def print_and_exit(msg: str):
        real_stdout.write(msg + "\n")
        sys.exit(0)

    def parse_int(s: str, what: str, lo: int, hi: int) -> int:
        # parse a base-10 number, ignoring leading/trailing spaces
        try:
            ret = int(s)
        except Exception:
            print_and_exit(f"failed to parse {what} as integer: {s}")
        if not (lo <= ret <= hi):
            print_and_exit(f"{what} out of bounds: {ret} not in [{lo}, {hi}]")
        return ret

    def wait_for_child(pid: int, read_fd: int, done_reading: bool = False) -> bytes:
        # Read everything the other process writes, until it terminates (or at
        # least closes the pipe write end).
        buf = b""
        if not done_reading:
            with os.fdopen(read_fd, "rb", closefd=False) as f:
                buf = f.read()

        pid, status = os.waitpid(pid, 0)
        if os.WIFSIGNALED(status):
            # propagate the signal, or if not possible at least exit with an error
            os.kill(os.getpid(), os.WTERMSIG(status))
            sys.exit(1)
        ex = os.WEXITSTATUS(status)
        if ex != 0:
            sys.exit(ex)

        os.close(read_fd)
        return buf

    def run_submission_interactively(iteration: int, N: int, perm: List[int], lines: List[str]) -> bytes:
        """Run the submission and alternatingly write and read lines, returning the output."""
        first_line = f"{iteration} {N}\n" + " ".join(map(str, perm))

        sys.stdout.flush()
        sys.stderr.flush()

        # CPython and Pypy don't currently use threads, so using fork without exec
        # here is safe.
        c2p_read, c2p_write = os.pipe()
        p2c_read, p2c_write = os.pipe()
        pid = os.fork()

        if pid == 0:
            os.close(p2c_write)
            os.close(c2p_read)

            os.dup2(p2c_read, 0)
            os.dup2(c2p_write, 1)

            # TODO optimize
            runpy.run_path(sub_file, {}, "__main__")

            sys.stdout.flush()
            sys.stderr.flush()
            os._exit(0)
        else:
            os.close(c2p_write)
            os.close(p2c_read)

            output = []
            done_reading = False
            with os.fdopen(p2c_write, "wb", buffering=0) as fout:
                try:
                    fout.write(first_line.encode("ascii") + b"\n")
                except BrokenPipeError:
                    pass

                pending_lines = 0
                for line in lines:
                    try:
                        fout.write(line.encode("ascii") + b"\n")
                    except BrokenPipeError:
                        pass
                    pending_lines += 1
                    while not done_reading and pending_lines > 0:
                        data = os.read(c2p_read, 32)
                        if not data:
                            done_reading = True
                            break
                        output.append(data)
                        pending_lines -= data.count(b"\n")

            output.append(wait_for_child(pid, c2p_read, done_reading))
            return b"".join(output)

    def run_machine(iteration: int, N: int, perm: List[int], tape: List[int]) -> List[int]:
        lines = [*map(str, tape)]

        enc_output = run_submission_interactively(iteration, N, perm, lines)

        output = enc_output.decode("latin1")
        lines = output.splitlines()
        if len(lines) != N:
            print_and_exit(f"wrong number of lines of output")

        return [parse_int(line, "bit", 0, 1) for line in lines]

    output = run_submission_interactively(0, N, perm, [])
    iterations = parse_int(output.decode("latin1"), "number of iterations", 0, max_iterations)

    for it in range(iterations):
        if it % 2:
            tape = tape[::-1]
        tape = run_machine(it + 1, N, perm, tape)
        if it % 2:
            tape = tape[::-1]

    sys.stdout.flush()

    if tape == target_tape:
        print_and_exit(f"{ACCEPTED_MSG}\n{iterations}")
    else:
        print_and_exit("wrong output tape")

if __name__ == "__main__":
    judge_main()
