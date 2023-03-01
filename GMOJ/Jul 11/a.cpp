#include <bits/stdc++.h>
#pragma GCC optimize(2)
int main() {
	freopen("a.in", "r", stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m, q, sum = 0;
	std::cin >> n >> m;
	std::vector<std::vector<std::pair<int, int>>> e(n);
	for (int i = 0, u, v; i < m; ++i) {
		std::string s;
		std::cin >> u >> v >> s;
		--u; --v;
		if (s == "x") {e[u].push_back({v, 0}); ++sum;}
		else e[u].push_back({v, std::stoi(s)});
	}
	std::cin >> q;
	auto SPFA = [&](int s, int t) {
		std::vector<std::vector<long long>> dis(n, std::vector<long long>(1, INT64_MAX / 2));
		std::vector<bool> vis(n);
		std::queue<int> q;
		dis[s][0] = 0;
		q.push(s);
		while (q.size()) {
			int u = q.front();
			q.pop();
			vis[u] = false;
			for (auto &item : e[u]) {
				int v = item.first, w = item.second;
				auto mn = dis[v];
				for (int i = 0; i < (int)dis[v].size() - 1; ++i)
					mn[i + 1] = std::min(mn[i + 1], mn[i]);
				for (int i = 0; i < (int)dis[u].size(); ++i) {
					if (w == 0) {
						if ((int)dis[v].size() <= i + 1) {
							if (!(dis[u][i] < mn.back() && (int)dis[v].size() <= sum)) continue;
							for (int j = dis[v].size(); j <= i; ++j) dis[v].push_back(INT64_MAX / 2);
							dis[v].push_back(dis[u][i]);
							if (!vis[v]) {
								q.push(v);
								vis[v] = true;
							}
						} else if (dis[v][i + 1] > dis[u][i]) {
							dis[v][i + 1] = dis[u][i];
							if (!vis[v]) {
								q.push(v);
								vis[v] = true;
							}
						}
					} else {
						if ((int)dis[v].size() <= i) {
							if (!(dis[u][i] + w < mn.back() && (int)dis[v].size() <= sum)) continue;
							for (int j = dis[v].size(); j < i; ++j) dis[v].push_back(INT64_MAX / 2);
							dis[v].push_back(dis[u][i] + w);
							if (!vis[v]) {
								q.push(v);
								vis[v] = true;
							}
						} else if (dis[v][i] > dis[u][i] + w) {
							dis[v][i] = dis[u][i] + w;
							if (!vis[v]) {
								q.push(v);
								vis[v] = true;
							}
						}
					}
				}
			}
		}
		return dis[t];
	};
	for (int s, t; q--;) {
		std::cin >> s >> t;
		auto dis = SPFA(s - 1, t - 1);
		long long mn = INT64_MAX;
		std::vector<std::pair<int, long long>> line;
		for (int i = 0; i < (int)dis.size(); ++i) {
			if (dis[i] < mn) {
				mn = dis[i];
				line.emplace_back(i, dis[i]);
			}
		}
		if (dis[0] >= INT64_MAX / 2) {
			if ((int)dis.size() == 1) std::cout << "0 0\n";
			else std::cout << "inf\n";
			continue;
		}
		if ((int)line.size() == 1) {
			std::cout << "1 " << dis[0] << '\n';
			continue;
		}
		std::reverse(line.begin(), line.end());
		// for (auto &[k, b] : line) std::cerr << k << " " << b << std::endl;
		long long x = 1, ans = dis[0], gx = 0;
		for (int i = 0, j; i < (int)line.size() - 1; ++i) {
			long long k1 = line[i].first, b1 = line[i].second;
			std::map<std::pair<long long, int>, int> buk;
			for (j = i + 1; j < (int)line.size(); ++j) {
				long long k2 = line[j].first, b2 = line[j].second;
				gx = (b2 - b1) / (k1 - k2);
				if (k1 * gx + b1 <= dis[0]) buk[{gx, -k2}] = j;
			}
			j = (*buk.begin()).second;
			long long k2 = line[j].first, b2 = line[j].second;
			gx = (b2 - b1) / (k1 - k2);
			ans += k1 * (x + gx) * (gx - x + 1) / 2 + b1 * (gx - x + 1);
			if (k1 * gx + b1 == dis[0]) {
				ans -= dis[0];
				break;
			}
			x = ++gx;
			i = j - 1;
		}
		std::cout << gx << ' ' << ans << std::endl;
	}
	return 0;
}