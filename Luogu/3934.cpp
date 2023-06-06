#include <bits/stdc++.h>
template<typename T>
class Fenwick {
	const int n;
	std::vector<T> a;
	T _Sum(int x) {
		T res = 0;
		for (; x; x -= x & (-x)) res += a[x];
		return res;
	}
public:
	Fenwick(int n = 0) : n(n), a(n + 1) {}
	void Add(int x, const T &v) {for (; x <= n; x += x & -x) a[x] += v;}
	T Sum(int l, int r) {return _Sum(r) - _Sum(l - 1);}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	constexpr int N = 2E7;
	std::vector<int> pri, phi(N + 1);
	std::vector<bool> vis(N + 1);
	phi[1] = 1;
	for (int i = 2; i <= N; ++i) {
		if (!vis[i]) pri.push_back(i), phi[i] = i - 1;
		for (auto p : pri) {
			if (i * p > N) break;
			vis[i * p] = true;
			if (i % p == 0) {
				phi[i * p] = phi[i] * p;
				break;
			}
			phi[i * p] = phi[i] * phi[p]; 
		}
	}
	int n, m;
	std::cin >> n >> m;
	Fenwick<long long> bit(n);
	for (int i = 1, x; i <= n; ++i) {
		std::cin >> x;
		bit.Add(i, x);
		if (i < n) bit.Add(i + 1, -x);
	}
	for (int op, l, r, p; m--;) {
		std::cin >> op >> l >> r >> p;
		if (op == 1) {
			bit.Add(l, p);
			if (r < n) bit.Add(r + 1, -p);
		} else {
			using Info = std::pair<int, bool>;
			std::function<Info(int, int, int)> Solve = [&](int L, int R, int P) -> Info {
				if (P == 1) return {0, true};
				long long x = bit.Sum(1, L);
				if (x == 1) return {1, false};
				if (L == R) return {x % P, x >= P};
				Info cur = Solve(L + 1, R, phi[P]);
				if (cur.second) cur.first += phi[P];
				return [](long long x, int b, int P) {
					Info res = {1, 0};
					if (x >= P) {
						x %= P;
						res.second = true;
					}
					for (; b; b >>= 1) {
						if (b & 1) {
							if  (res.first * x >= P) {
								res.first = res.first * x % P;
								res.second = true;
							} else res.first = res.first * x;
						}
						x *= x;
						if (x >= P) {
							x %= P;
							res.second = true;
						}
					}
					return res;
				}(x, cur.first, P);
			};
			std::cout << Solve(l, r, p).first << '\n';
		}
	}
	return 0;
}