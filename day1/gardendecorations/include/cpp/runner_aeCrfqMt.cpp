#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

#define CHECK(var, fn) do { if ((var) == -1) { perror(fn); exit(1); } } while (false)

using namespace std;

namespace {

int realStdout;

void writeToFd(int fd, const string& buf) {
	const char* ptr = buf.data();
	size_t len = buf.size();
	while (len > 0) {
		ssize_t w = write(fd, ptr, len);
		if (w == -1 && errno == EINTR) continue;
		if (w == -1 && errno == EPIPE) break;
		CHECK(w, "write");
		len -= w;
		ptr += w;
	}
}

string readFromFdUntilNl(int fd, string& rem) {
	size_t ind, searchStart = 0;
	static char buf[1 << 20];
	while ((ind = rem.find('\n', searchStart)) == string::npos) {
		searchStart = rem.size();
		ssize_t r = read(fd, buf, sizeof(buf));
		if (r == -1 && errno == EINTR) continue;
		if (r == 0) {
			writeToFd(2, "tried to read line, found EOF\n");
			exit(1);
		}
		CHECK(r, "read");
		rem.insert(rem.end(), buf, buf + r);
	}
	if (ind == string::npos) return "";
	string ret(rem.begin(), rem.begin() + ind + 1);
	rem.erase(rem.begin(), rem.begin() + ind + 1);
	return ret;
}

void readFromFd(int fd, string& ret) {
	static char buf[1 << 20];
	for (;;) {
		ssize_t r = read(fd, buf, sizeof(buf));
		if (r == -1 && errno == EINTR) continue;
		if (r == 0) break;
		CHECK(r, "read");
		ret.insert(ret.end(), buf, buf + r);
	}
}

[[noreturn]]
void printAndExit(string msg) {
	msg += "\n";
	writeToFd(realStdout, msg);
	exit(0);
}

int parseInt(const string& s, const char* what, int lo, int hi) {
	// parse a base-10 number, ignoring leading/trailing spaces
	istringstream iss(s);
	int ret;
	string more;
	if (!(iss >> ret) || (iss >> more)) {
		printAndExit(string("failed to parse ") + what + " as integer: " + s);
	}
	if (!(lo <= ret && ret <= hi)) {
		printAndExit(string(what) + " out of bounds: " + to_string(ret) +
				" not in [" + to_string(lo) + ", " + to_string(hi) + "]");
	}
	return ret;
}

string waitForChild(int pid, int readFd, bool doneReading = false) {
	string buf;
	if (!doneReading)
		readFromFd(readFd, buf);

	int status;
	CHECK(waitpid(pid, &status, 0), "waitpid");
	if (WIFSIGNALED(status)) {
		// propagate the signal, or if not possible at least exit with an error
		CHECK(kill(getpid(), WTERMSIG(status)), "kill");
		exit(1);
	}
	int ex = WEXITSTATUS(status);
	if (ex != 0)
		exit(ex);

	CHECK(close(readFd), "close");
	return buf;
}

[[noreturn]]
void runSubmission(int in, int out) {
	CHECK(dup2(in, 0), "dup2");
	CHECK(dup2(out, 1), "dup2");
	// Throw an exception to resume execution at the end of real_main(),
	// after which main() will be called.
	throw true;
}

string runSubmissionInteractively(int iteration, int N, const vector<int>& perm, const vector<string>& lines) {
	string firstLine = to_string(iteration) + " " + to_string(N) + "\n";
	bool first = true;
	for (int x : perm) {
		if (!first)
			firstLine += ' ';
		first = false;
		firstLine += to_string(x);
	}

	int pipefds[2];
	CHECK(pipe(pipefds), "pipe");
	int c2pRead = pipefds[0], c2pWrite = pipefds[1];
	CHECK(pipe(pipefds), "pipe");
	int p2cRead = pipefds[0], p2cWrite = pipefds[1];
	pid_t pid = fork();
	CHECK(pid, "fork");

	if (pid == 0) {
		CHECK(close(c2pRead), "close");
		CHECK(close(p2cWrite), "close");

		runSubmission(p2cRead, c2pWrite);
	} else {
		CHECK(close(p2cRead), "close");
		CHECK(close(c2pWrite), "close");

		writeToFd(p2cWrite, firstLine + '\n');

		char buf[32];
		string output;
		bool doneReading = false;
		int pendingLines = 0;
		for (const string& line : lines) {
			writeToFd(p2cWrite, line + '\n');
			pendingLines++;

			while (!doneReading && pendingLines > 0) {
				ssize_t r = read(c2pRead, buf, sizeof(buf));
				if (r == -1 && errno == EINTR) continue;
				if (r == 0) {
					doneReading = true;
					break;
				}
				CHECK(r, "read");
				output.insert(output.end(), buf, buf + r);
				pendingLines -= (int)count(buf, buf + r, '\n');
			}
		}
		CHECK(close(p2cWrite), "close");
		auto more = waitForChild(pid, c2pRead, doneReading);
		output.insert(output.end(), more.begin(), more.end());
		return output;
	}
}

void runMachine(int iteration, int N, const vector<int>& perm, vector<int>& tape) {
	vector<string> lines(N);
	for (int i = 0; i < N; i++) {
		lines[i] = to_string(tape[i]);
	}

	string output = runSubmissionInteractively(iteration, N, perm, lines);

	lines.clear();
	size_t i = 0;
	while (i < output.size()) {
		size_t j = output.find('\n', i);
		if (j == string::npos) {
			j = output.size();
		}
		lines.push_back(output.substr(i, j - i));
		i = j + 1;
	}

	if (lines.size() != (size_t)N) {
		printAndExit("wrong number of lines of output");
	}

	for (int i = 0; i < N; i++) {
		tape[i] = parseInt(lines[i], "bit", 0, 1);
	}
}

__attribute__((constructor))
void real_main() try {
	const char* HANDSHAKE_REQ = "must_use_cpp_or_python";
	const char* HANDSHAKE_RESP = "5GTwvkYR";
	const char* ACCEPTED_MSG = "OK:gG7DDasY";

	signal(SIGPIPE, SIG_IGN);

	string buf;
	assert(readFromFdUntilNl(0, buf) == HANDSHAKE_REQ + string("\n"));
	writeToFd(1, HANDSHAKE_RESP + string("\n"));

	string inp;
	inp += readFromFdUntilNl(0, buf); // max iterations
	inp += readFromFdUntilNl(0, buf); // N
	inp += readFromFdUntilNl(0, buf); // perm
	inp += readFromFdUntilNl(0, buf); // tape
	istringstream judgeIn(inp);

	int maxIterations;
	judgeIn >> maxIterations;

	int N;
	judgeIn >> N;

	vector<int> perm(N), seen(N);
	for (int i = 0; i < N; i++) {
		judgeIn >> perm[i];
		assert(0 <= perm[i] && perm[i] < N);
		assert(!seen[perm[i]]++);
	}
	vector<int> tape(N), targetTape(N);
	for (int i = 0; i < N; i++) {
		judgeIn >> tape[i];
	}
	for (int i = 0; i < N; i++) {
		targetTape[i] = tape[perm[i]];
	}

	// send stdout to stderr for the user program
	realStdout = dup(1);
	CHECK(realStdout, "dup");
	CHECK(dup2(2, 1), "dup2");

	// redirect the stdin fd to make it slightly harder to read stdin twice
	CHECK(close(0), "close");
	CHECK(open("/dev/null", O_RDONLY), "open");

	string output = runSubmissionInteractively(0, N, perm, {});
	int iterations = parseInt(output, "number of iterations", 0, maxIterations);

	for (int it = 0; it < iterations; it++) {
		if (it % 2) reverse(tape.begin(), tape.end());
		runMachine(it + 1, N, perm, tape);
		if (it % 2) reverse(tape.begin(), tape.end());
	}

	if (tape == targetTape) {
		printAndExit(string(ACCEPTED_MSG) + "\n" + to_string(iterations));
	} else {
		printAndExit("wrong output tape");
	}

	assert(0);
} catch (bool) {}

}
