#include <bits/stdc++.h>
const int P = 998244353;
int norm(int x) {if (x < 0) x += P; if (x >= P) x -= P;return x;}
struct Z {
	int x;
	Z(int x = 0) : x(norm(x)) {}
	int val() const {return x;}
	Z operator-() const {return Z(norm(P - x));}
	Z inv() const {return (*this).pow(P - 2);}
	Z &operator*=(const Z &rhs) {return x = 1ll * x * rhs.x % P, *this;}
	Z &operator+=(const Z &rhs) {return x = norm(x + rhs.x), *this;}
	Z &operator-=(const Z &rhs) {return x = norm(x - rhs.x), *this;}
	Z &operator/=(const Z &rhs) {return *this *= rhs.inv();}
	friend Z operator*(const Z &lhs, const Z &rhs) {Z res = lhs; res *= rhs; return res;}
	friend Z operator+(const Z &lhs, const Z &rhs) {Z res = lhs; res += rhs; return res;}
	friend Z operator-(const Z &lhs, const Z &rhs) {Z res = lhs; res -= rhs; return res;}
	friend Z operator/(const Z &lhs, const Z &rhs) {Z res = lhs; res /= rhs; return res;}
	Z pow(unsigned long long e) const {
		for (Z res(1), x(*this);; x *= x) {
		  if (e & 1) res *= x;
		  if ((e >>= 1) == 0) return res;
		}
	}
	friend std::istream &operator>>(std::istream &is, Z &rhs) {
		int x;
		is >> x;
		rhs = Z(x);
		return is;
	}
};
struct DSU {
	std::vector<int> fa, sz;
	DSU(int n = 0) : fa(n), sz(n, 1) {std::iota(fa.begin(), fa.end(), 0);}
	int Find(int x) {
		while (x != fa[x]) x = fa[x] = fa[fa[x]];
		return x;
	}
	bool Same(int x, int y) {return Find(x) == Find(y);}
	bool Merge(int x, int y) {
		x = Find(x), y = Find(y);
		if (x == y) return false;
		if (sz[x] > sz[y]) std::swap(x, y);
		fa[x] = y;
		sz[y] += sz[x];
		return true;
	}
	int size(int x) {return sz[Find(x)];}
};
int main() {
	freopen("milk.in", "r", stdin);
	freopen("milk.out", "w", stdout);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m;
	std::cin >> n >> m;
	DSU f1(n);
	for (int i = 0, u, v; i < m; ++i) {
		std::cin >> u >> v;
		--u, --v;
		f1.Merge(u, v);
	}
	std::vector<int> sz1(1 << n);
	int tol = 0;
	for (int i = 0; i < n; ++i) {
		if (f1.Find(i) == i) {
			sz1[1 << (tol++)] = f1.size(i);
		}
	}
	sz1.resize(1 << (tol));
		for (int j = 0; j < tol; ++j) {
	for (int i = 0; i < (1 << tol); ++i) {
			if (i & (1 << j)) {
				sz1[i] += sz1[i ^ (1 << j)];
			}
		}
	}
	DSU f2(n);
	for (int i = m + 1, u, v; i < n; ++i) {
		std::cin >> u >> v;
		--u; --v;
		f2.Merge(u, v);
	}
	int _tol = 0;
	std::vector<int> sz2(1 << n);
	for (int i = 0; i < n; ++i)
		if (f2.Find(i) == i) sz2[1 << (_tol++)] = f2.size(i);
	sz2.resize(1 << (_tol));
		for (int j = 0; j < _tol; ++j) {
	for (int i = 0; i < (1 << _tol); ++i) {
			if (i & (1 << j)) {
				sz2[i] += sz2[i ^ (1 << j)];
			}
		}
	}
	std::vector<Z> fac(n + 1, 1);
	for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i;
	std::vector<Z> g(1 << (n + 1)), f(1 << (n + 1));
	for (int i = 0; i < (1 << (n + 1)); ++i) {
		if (sz1[i & ((1 << tol) - 1)] == sz2[i >> tol]) {
			g[i] = fac[sz2[i >> tol]];
		}
	}
	f[0] = g[0] = 1;
	for (int i = 1; i < (1 << (n + 1)); ++i) {
		if (g[i].x == 0) continue;
		f[i] = g[i];
		if ((i & (-i)) >= (1 << tol)) continue;
		for (int j = ((-i) & i) ^ i; j; j = (j - 1) & (((-i) & i) ^ i))
			f[i] -= g[j] * f[i ^ j];
	}
	std::cout << f[(1 << (n + 1)) - 1].x << std::endl;
	return 0;
}