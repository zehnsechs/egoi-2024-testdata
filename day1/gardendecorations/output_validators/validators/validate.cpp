#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
	init_io(argc, argv);
	const int max_iterations = 60;

	// Hakeshake step. Technically this isn't necessary and this could be a
	// non-interactive problem (since our include/ takes care of interaction),
	// but it's nice to have it marked interactive in Kattis, and a handshake
	// might give slightly better error messages for non-C++/Python submissions.
	cout << "must_use_cpp_or_python" << endl;
	string auth;
	getline(cin, auth);
	if (!cin || auth != "5GTwvkYR") {
		wrong_answer("must use C++ or Python include files (bad initial auth: %s)", auth.c_str());
	}

	cout << max_iterations << endl;

	static char buf[1 << 20];
	while (judge_in.read(buf, sizeof(buf)))
		cout.write(buf, sizeof(buf));
	cout.write(buf, judge_in.gcount());
	cout.flush();

	int iterations;
	auth = "eof from runner!?";
	getline(cin, auth);
	if (!cin || auth != "OK:gG7DDasY") {
		wrong_answer("wrong answer: %s", auth.c_str());
	}
	cin >> iterations;
	if (!cin) {
		wrong_answer("missing number of iterations!?");
	}

	double score;
	if (iterations <= 3) {
		score = 1;
	} else if (iterations > max_iterations) {
		wrong_answer("too many iterations");
	} else {
		// TODO: confirm this is the score function we want.
		score = 1.0 - 0.5 * log10(iterations / 3.0);
	}

	// grader will rescale this to the test group's correct value
	score *= 1000;

	judge_message("used %d iterations; score: %.2f", iterations, score);
	accept_with_score(score);
}
