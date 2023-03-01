#include <bits/stdc++.h>
using namespace std;
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	std::vector<std::vector<int>> e(n);
	std::vector<bool> pos(n);
	for (; m--; ) {
		int u, v;
		cin >> u >> v;
		--u; --v;
		if (u != -1) {
			e[u].push_back(v);
			e[v].push_back(u);
		} else pos[v] = true;
	}
	auto BFS = [&](int s) {
		queue<int> q;
		q.push(s);
		vector<int> dis(n, 1E9);
		dis[s] = 0;
		while (q.size()) {
			int u = q.front(); q.pop();
			for (auto &v : e[u]) {
				if (dis[v] != 1E9) continue;
				dis[v] = dis[u] + 1;
				q.push(v);
			}
		}
		return dis;
	};
	auto dis1 = BFS(0), dis2 = BFS(n - 1);
	int minx = 1E9, miny = 1E9;
	for (int i = 0; i < n; ++i) {
		if (pos[i] && dis1[i] < minx) {
			minx = dis1[i];
		}		
		if (pos[i] && dis2[i] < miny) {
			miny = dis2[i];
		}
	}
	for (int i = 0; i < n; ++i) {
		int ans = std::min(dis1[n - 1], minx + miny + 2);
		ans = std::min(ans, minx + 1 + dis2[i]);
		ans = std::min(ans, miny + 1 + dis1[i]);
		cout << (ans > 1E9 ? -1 : ans) << ' ';
	}
	return 0;
}