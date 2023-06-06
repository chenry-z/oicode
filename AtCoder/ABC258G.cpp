#include "atcoder/all"
#include "bits/stdc++.h"
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<int> deg(N);
	vector<vector<int>> g(N);
	for (int i = 0; i < N; ++i) {
		string s;
		cin >> s;
		for (int j = 0; j < N; ++j) {
			int c = s[j] - '0';
			if (i <= j || c == 0) continue;
			deg[i] += c;
			deg[j] += c;
			if (c) {
				g[j].push_back(i);
				g[i].push_back(j);
			}
		}
	}
	long long ans = 0, cnt = 0;
	bitset<3000> s;
	const int B = 700;
	vector<bitset<3000>> gg(N);
	vector<int> bel(N);
	for (int u = 0; u < N; ++u) {
		s.reset();
		for (auto v : g[u]) s[v] = 1;
		if (deg[u] >= B) gg[bel[u] = cnt++] = s;
		for (auto v : g[u]) {
			if (v < u) {
				if (bel[v]) ans += (gg[bel[v]] & s).count();
				else for (auto w : g[v]) ans += s[w];
			}
		}
	}
	cout << ans / 3;
	return 0;
}