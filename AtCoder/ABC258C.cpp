#include "atcoder/all"
#include "bits/stdc++.h"
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	int N, Q;
	cin >> N >> Q;
	string s;
	cin >> s;
	int cur = 0;
	for (int op, x; Q--;) {
		cin >> op >> x;
		if (op == 1) {
			cur = (cur + x) % N;
		} else {
			// cerr << (x - cur - 1) % N;
			cout << s[(x - cur - 1 + N) % N] << endl;
		}
	}
	return 0;
}