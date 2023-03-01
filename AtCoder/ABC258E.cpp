#include "atcoder/all"
#include "bits/stdc++.h"
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	int N, Q, X;
	cin >> N >> Q >> X;
	vector<int> W(N);
	for (auto &c : W) cin >> c;
	vector<int> ans, pos(N);
	long long sum = 0, cnt = 0, tt = 0;
	bool flag = true;
	while (flag) {
		for (int i = 0; i < N; ++i) {
			++cnt;
			sum += W[i];
			if (sum >= X) {
				ans.push_back(cnt);
				sum = cnt = 0;
				if (pos[i]) {
					flag = false;
					tt = i;
					break;
				}
				pos[i] = ans.size();
			}
		}
	}
	// for (auto c : ans) cerr << c << ' ';
	// cerr << '\n';
	// cerr << pos[tt] << '\n';
	for (long long K; Q--;) {
		cin >> K;
		if (K <= pos[tt]) cout << ans[K - 1] << endl;
		else {
			cerr << "D" << (K - pos[tt]) % (ans.size() - pos[tt]) + pos[tt] - 1 << endl;
			cout << ans[(K - pos[tt]) % (ans.size() - pos[tt]) + pos[tt] - 1] << endl;
		}
	}
	return 0;
}