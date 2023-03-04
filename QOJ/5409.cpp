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
using Info = std::bitset<100001>;
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, q;
	std::cin >> n >> q;
	int B = std::ceil(std::sqrt(n));
	std::vector<int> a(n + 1), b(n + 1), block(n + 1);
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		b[a[i]] = i;
		block[i] = (i - 1) / B + 1;
	}
	Fenwick<int> bit(n);
	Info ans;
	std::vector<Info> P(block[n] + 1), Q(block[n] + 1);
	for (int i = n; i >= 1; --i) {
		ans[n - i + 1] = bit.Sum(1, a[i]) & 1;
		bit.Add(a[i], 1);
		P[block[i]][n - i + 1] = Q[block[a[i]]][n - i + 1] = 1;
	}
	for (int i = 1; i <= block[n]; ++i) P[i] |= P[i - 1], Q[i] |= Q[i - 1];
	auto PreP = [&](int x) {
		if (x == 0) return Info();
		Info res = P[block[x] - 1];
		for (int i = (block[x] - 1) * B + 1; i <= x; ++i)
			res[n - i + 1].flip();
		return res;
	};
	auto PreQ = [&](int x) {
		if (x == 0) return Info();
		Info res = Q[block[x] - 1];
		for (int i = (block[x] - 1) * B + 1; i <= x; ++i)
			res[n - b[i] + 1].flip();
		return res;
	};
	auto SumP = [&](int l, int r) {
		if (l > r) return Info();
		return PreP(l - 1) ^ PreP(r);
	};
	auto SumQ = [&](int l, int r) {
		if (l > r) return Info();
		return PreQ(l - 1) ^ PreQ(r);
	};
	for (int x, y; q--;) {
		std::cin >> x >> y;
		if (x > y) std::swap(x, y);
		int X = std::min(a[x], a[y]), Y = std::max(a[x], a[y]);
		ans ^= SumP(x + 1, y - 1) & SumQ(X, Y);
		std::swap(a[x], a[y]), std::swap(b[a[x]], b[a[y]]);
		for (int i = 1; i <= block[n]; ++i) {
			bool t = Q[i][n - x + 1];
			Q[i][n - x + 1] = Q[i][n - y + 1];
			Q[i][n - y + 1] = t;
		}
		ans[n - x + 1] = (SumP(x + 1, n) & SumQ(1, a[x])).count() & 1;
		ans[n - y + 1] = (SumP(y + 1, n) & SumQ(1, a[y])).count() & 1;
		std::cout << n - std::min(n + 1, (int)ans._Find_first()) + 2 << '\n';
	}
	return 0;
}