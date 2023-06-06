#include <bits/stdc++.h>
const int P = 1E9 + 7;

int norm(int x) {if (x < 0) x += P; if (x >= P) x -= P;return x;}

template<class T>T power(T a, int b) {
	T res = 1;
	for (; b; b >>= 1, a *= a) 
		if (b & 1) res *= a;
	return res;
}

struct Z {
	int x;
	Z(int x = 0) : x(norm(x)) {}
	int val() const {return x;}
	Z operator-() const {return Z(norm(P - x));}
	Z inv() const {return power(*this, P - 2);}
	Z &operator*=(const Z &rhs) {return x = 1ll * x * rhs.x % P, *this;}
	Z &operator+=(const Z &rhs) {return x = norm(x + rhs.x), *this;}
	Z &operator-=(const Z &rhs) {return x = norm(x - rhs.x), *this;}
	Z &operator/=(const Z &rhs) {return *this *= rhs.inv();}
	friend Z operator*(const Z &lhs, const Z &rhs) {Z res = lhs; res *= rhs; return res;}
	friend Z operator+(const Z &lhs, const Z &rhs) {Z res = lhs; res += rhs; return res;}
	friend Z operator-(const Z &lhs, const Z &rhs) {Z res = lhs; res -= rhs; return res;}
	friend Z operator/(const Z &lhs, const Z &rhs) {Z res = lhs; res /= rhs; return res;}
};
struct Mat {
	std::vector<std::vector<Z>> a;
	Mat(int n) : a(n, std::vector<Z>(n, 0)) {}
	Mat operator * (const Mat &rhs) const {
		Mat c(a.size());
		int n = a.size();
		for (int i = 0; i < n; ++i)
			for (int k = 0; k < n; ++k)
				if (a[i][k].x != 0)
					for (int j = 0; j < n; ++j)
						c.a[i][j] += a[i][k] * rhs.a[k][j];
		return c;
	};
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m, p, q;
	std::cin >> n >> m >> p >> q;
	if (p == 1) {
		std::cout << 1 << '\n';
		return 0;
	} else if (p == 2) {
		return 0;
	}
	Mat a((1 << n) * (p - 1) * (q + 1));
	for (int S = 1; S < (1 << n) - 1; ++S) {
		for (int T = 1; T < (1 << n) - 1; ++T) {
			for (int P = S; P; P = (P - 1) & S)
				for (int Q = T; Q; Q = (Q - 1) & T) {
					for (int i = 0; i <= q; ++i)
						if ((P & Q) == Q)
							a.a[i * (1 << n) + P][(q + 1) * (1 << n) + i * (1 << n) + Q] += 1;
						else if ((P & Q) == 0) {
							a.a[i * (1 << n) + P][i * (1 << n) + Q] += 1;
							a.a[(q + 1) * (1 << n) + i * (1 << n) + P][i * (1 << n) + Q] += 1;
						} else a.a[i * (1 << n) + P][(q + 1) * (1 << n) + i * (1 << n) + (P & Q)] += 1;
				}
		}
	}
	for (int S = 1; S < (1 << n) - 1; ++S) {
		for (int i = 0; i <= q; ++i) {
			a.a[i * (1 << n) + 0][i * (1 << n) + S] += 1;
			for (int j = 1; j <= 2; ++j)
				a.a[(j - 1) * (q + 1) * (1 << n) + i * (1 << n) + S][i * (1 << n) + 0] += 1;
		}
	}
	for (int S = 1; S < (1 << n) - 1; ++S) {
		for (int i = 1; i <= q; ++i) {
			a.a[(i - 1) * (1 << n) + S][(q + 1) * (1 << n) + i * (1 << n) + S] += 1;
			a.a[i * (1 << n) + (1 << n) - 1][(q + 1) * (1 << n) + i * (1 << n) + S] += 1;
		}
	}
	for (int i = 0; i <= q; ++i)
		a.a[i * (1 << n) + 0][i * (1 << n) + 0] += 1;
	for (int i = 1; i <= q; ++i)
		a.a[(i - 1) * (1 << n) + 0][i * (1 << n) + (1 << n) - 1] += 1;
	for (int i = 1; i <= q; ++i)
		a.a[i * (1 << n) + (1 << n) - 1][i * (1 << n) + 0] += 1;
	for (int i = 2; i <= q; ++i)
		a.a[(i - 1) * (1 << n) + (1 << n) - 1][i * (1 << n) + (1 << n) - 1] += 1;
	Mat ret((1 << n) * (p - 1) * (q + 1));
	for (int i = 0; i < (int)ret.a.size(); ++i) ret.a[i][i] = 1;
	for (; m; m >>= 1, a = a * a)
		if (m & 1) ret = ret * a;
	Z ans = 0;
	for (int i = 0; i < (int)ret.a.size(); ++i) ans += ret.a[i][i];
	std::cout << ans.x << '\n';
	return 0;
}