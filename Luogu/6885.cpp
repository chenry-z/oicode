#include <bits/stdc++.h>
template<typename T>
class Fenwick {
	const int n;
	std::vector<T> a;
	T _Sum(int x) {
		T res;
		for (; x; x -= x & (-x)) res = res + a[x];
		return res;
	}
public:
	Fenwick(int n = 0) : n(n), a(n + 1) {}
	void Add(int x, const T &v) {for (; x <= n; x += x & -x) a[x] = a[x] + v;}
	T Sum(int r) {return _Sum(r);}
};
constexpr int mod = 1000000007;
struct node {
	int x, y;
	node(int x = 0, int y = 1) : x(x), y(y) {}
	node operator + (const node &rsh) const {
		if (x < rsh.x) return rsh;
		else if (x > rsh.x) return *this;
		return node(x, (x + y) % mod);
	}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (auto &c : a) std::cin >> c;
	auto b = a;
	std::sort(b.begin(), b.end());
	b.erase(std::unique(b.begin(), b.end()), b.end());
	for (auto &c : a) c = std::lower_bound(b.begin(), b.end(), c) - b.begin() + 2;
	Fenwick<node> s1(n + 2), s2(n + 2);
	std::vector<node> f1(n), f2(n);
	for (int i = n - 1; i >= 0; --i) {
		f1[i] = s1.Sum(a[i] - 1), f2[i] = s2.Sum(n + 1 - a[i]);
		++f1[i].x, ++f2[i].x;
		if (f1[i].x == 1) f1[i].y = 1;
		if (f2[i].x == 1) f2[i].y = 1;
		s1.Add(a[i], f1[i]), s2.Add(n + 2 - a[i], f2[i]);
	}
	std::vector<int> bit(n + 1, 1);
	for (int i = 1; i <= n; ++i) bit[i] = 2ll * bit[i - 1] % mod;
	int ans = 0, cnt = 1;
	for (int i = 0; i < n; ++i) {
		int cur = f1[i].x + f2[i].x - 1;
		int ret = 1ll * bit[n - cur] * f1[i].y % mod * f2[i].y % mod;
		if (ans < cur) ans = cur, cnt = ret;
		else if (ans == cur) (cnt += ret) %= mod;
	}
	std::cout << ans << ' ' << cnt << '\n';
	return 0;
}