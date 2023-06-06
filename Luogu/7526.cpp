#include <bits/stdc++.h>
class FastIostream {
	const int maxBF = 1 << 20;
	char *inbuf, *inst, *ined, *oubuf, *oust, *oued;
	void _flush() { fwrite(oubuf, 1, oued - oust, stdout); }
	char _getchar() {
		if (inst == ined) inst = inbuf, ined = inbuf + fread(inbuf, 1, maxBF, stdin);
		return inst == ined ? EOF : *inst++;
	} void _putchar(const char &c) {
		if (oued == oust + maxBF) _flush(), oued = oubuf;
		*oued++ = c;
	}
public:
	FastIostream() {
		inst = ined = inbuf = new char[maxBF];
		oust = oued = oubuf = new char[maxBF];
	} ~FastIostream() {_flush();}
	template <typename Int> FastIostream &operator>>(Int &n) {
		static char c;
		bool flag = false;
		while ((c = _getchar()) < '0' || c > '9') if (c == '-') flag = true;
		for (n = c - '0'; (c = _getchar()) >= '0' && c <= '9'; n = n * 10 + (c - 48));
		if (flag) n = ~n + 1;
		return *this;
	} template <typename Int> FastIostream &operator<<(Int n) {
		if (n < 0) _putchar('-'), n = ~n + 1;
		static char S[40];
		int t = 0;
		do {S[t++] = '0' + n % 10, n /= 10;} while (n);
		for (int i = 0; i < t; ++i) _putchar(S[t - i - 1]);
		return *this;
	} FastIostream &operator<<(const char *s) {
		for (int i = 0; s[i]; ++i) _putchar(s[i]);
		return *this;
	}
} io;
template<long long P>
struct Z {
	long long x;
	Z(long long _x = 0) : x(_x + (_x >> 63 & P)) {}
	Z &operator*=(const Z &rhs) {return x = (__int128)x * rhs.x % P, *this;}
	Z &operator+=(const Z &rhs) {return x += ((x + rhs.x - P) >> 63 & P) + rhs.x - P, *this;}
	Z &operator-=(const Z &rhs) {return x += ((x - rhs.x) >> 63 & P) - rhs.x, *this;}
	Z &operator/=(const Z &rhs) {return *this *= rhs.power(P - 2);}
	friend Z operator*(const Z &lhs, const Z &rhs) {return Z(lhs) *= rhs;}
	friend Z operator+(const Z &lhs, const Z &rhs) {return Z(lhs) += rhs;}
	friend Z operator-(const Z &lhs, const Z &rhs) {return Z(lhs) -= rhs;}
	friend Z operator/(const Z &lhs, const Z &rhs) {return Z(lhs) /= rhs;}
	template <typename Int> Z power(Int b) const {
		Z res = 1, a = *this;
		for (; b; b >>= 1, a *= a) if (b & 1) res *= a;
		return res;
	}
};
const long long Mod = 998244353;
using Int = Z<Mod>;
class Poly {
	std::vector<Int> a;
	std::vector<int> rev;
	std::vector<Int> roots{0, 1};
	void dft() {
		int n = a.size();
		if (int(rev.size()) != n) {
			int k = __builtin_ctz(n) - 1;
			rev.resize(n);
			for (int i = 0; i < n; ++i)
				rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
		}
		for (int i = 0; i < n; ++i)
			if (rev[i] < i) std::swap(a[i], a[rev[i]]);
		if (int(roots.size()) < n) {
			int k = __builtin_ctz(roots.size());
			roots.resize(n);
			while ((1 << k) < n) {
				Int e = Int(3).power((Mod - 1) >> (k + 1));
				for (int i = 1 << (k - 1); i < (1 << k); ++i) {
					roots[2 * i] = roots[i];
					roots[2 * i + 1] = roots[i] * e;
				}
				++k;
			}
		}
		for (int k = 1; k < n; k <<= 1)
			for (int i = 0; i < n; i += 2 * k)
				for (int j = 0; j < k; ++j) {
					Int u = a[i + j];
					Int v = a[i + j + k] * roots[k + j];
					a[i + j] = u + v;
					a[i + j + k] = u - v;
				}
	}
	void idft() {
		int n = a.size();
		std::reverse(std::next(a.begin()), a.end());
		(*this).dft();
		Int inv = Int(1) / n;
		for (int i = 0; i < n; ++i) a[i] *= inv;
	}
public:
	Poly() {}
	Poly(const std::vector<Int> &a) : a(a) {}
	Poly(const std::initializer_list<Int> &a) : a(a) {}
	int size() const {return a.size();}
	void resize(int n) {a.resize(n);}
	Int operator[](int idx) const {
		if (idx < 0 || idx >= size()) return 0;
		return a[idx];
	}
	Int &operator[](int idx) {return a[idx];}
	Poly mulxk(int k) const {
		auto b = a;
		b.insert(b.begin(), k, 0);
		return Poly(b);
	}
	Poly modxk(int k) const {
		k = std::min(k, size());
		return Poly(std::vector<Int>(a.begin(), a.begin() + k));
	}
	Poly divxk(int k) const {
		if (size() <= k) return Poly();
		return Poly(std::vector<Int>(a.begin() + k, a.end()));
	}
	friend Poly operator+(const Poly &a, const Poly &b) {
		std::vector<Int> res(std::max(a.size(), b.size()));
		for (int i = 0; i < int(res.size()); ++i) res[i] = a[i] + b[i];
		return Poly(res);
	}
	friend Poly operator-(const Poly &a, const Poly &b) {
		std::vector<Int> res(std::max(a.size(), b.size()));
		for (int i = 0; i < int(res.size()); ++i) res[i] = a[i] - b[i];
		return Poly(res);
	}
	friend Poly operator*(Poly a, Poly b) {
		if (a.size() == 0 || b.size() == 0) return Poly();
		int sz = 1, tot = a.size() + b.size() - 1;
		while (sz < tot) sz <<= 1;
		a.resize(sz);
		b.resize(sz);
		a.dft();
		b.dft();
		for (int i = 0; i < sz; ++i) a[i] *= b[i];
		a.idft();
		a.resize(tot);
		return a;
	}
	friend Poly operator*(Int a, Poly b) {
		for (int i = 0; i < int(b.size()); ++i) b[i] *= a;
		return b;
	}
	friend Poly operator*(Poly a, Int b) {
		for (int i = 0; i < int(a.size()); ++i) a[i] *= b;
		return a;
	}
	Poly &operator+=(Poly b) {return (*this) = (*this) + b;}
	Poly &operator-=(Poly b) {return (*this) = (*this) - b;}
	Poly &operator*=(Poly b) {return (*this) = (*this) * b;}
	Poly deriv() const {
		if (a.empty()) return Poly();
		std::vector<Int> res(size() - 1);
		for (int i = 0; i < size() - 1; ++i) res[i] = (i + 1) * a[i + 1];
		return Poly(res);
	}
	Poly integr() const {
		std::vector<Int> res(size() + 1);
		for (int i = 0; i < size(); ++i) res[i + 1] = a[i] / (i + 1);
		return Poly(res);
	}
	Poly inv(int m) const {
		Poly x{Int(1) / a[0]};
		int k = 1;
		while (k < m) {
			k <<= 1;
			x = (x * (Poly{2} - modxk(k) * x)).modxk(k);
		}
		return x.modxk(m);
	}
	Poly log(int m) const {return (deriv() * inv(m)).integr().modxk(m);}
	Poly exp(int m) const {
		Poly x{1};
		int k = 1;
		while (k < m) {
			k <<= 1;
			x = (x * (Poly{1} - x.log(k) + modxk(k))).modxk(k);
		}
		return x.modxk(m);
	}
	Poly pow(int k, int m) const {
		int i = 0;
		while (i < size() && a[i].x == 0) ++i;
		if (i == size() || 1LL * i * k >= m) return Poly(std::vector<Int>(m));
		Int v = a[i];
		auto f = divxk(i) * v.x;
		return (f.log(m - i * k) * k).exp(m - i * k).mulxk(i * k) * (Int(v).power(k));
	}
	Poly sqrt(int m) const {
		Poly x{1};
		int k = 1;
		while (k < m) {
			k <<= 1;
			x = (x + (modxk(k) * x.inv(k)).modxk(k)) * ((Mod + 1) / 2);
		}
		return x.modxk(m);
	}
	Poly mulT(Poly b) const {
		if (b.size() == 0) return Poly();
		int n = b.size();
		std::reverse(b.a.begin(), b.a.end());
		return ((*this) * b).divxk(n - 1);
	}
	std::vector<Int> eval(std::vector<Int> x) const {
		if (size() == 0) return std::vector<Int>(x.size(), 0);
		const int n = std::max(int(x.size()), size());
		std::vector<Poly> q(n << 2);
		std::vector<Int> ans(x.size());
		x.resize(n);
		std::function<void(int, int, int)> build = [&](int p, int l, int r) {
			if (r - l == 1) q[p] = Poly{1, Mod - x[l]};
			else {
				int m = (l + r) >> 1;
				build(p << 1, l, m);
				build(p << 1 | 1, m, r);
				q[p] = q[p << 1] * q[p << 1 | 1];
			}
		};
		build(1, 0, n);
		std::function<void(int, int, int, const Poly &)> work = [&](int p, int l, int r, const Poly &num) {
			if (r - l == 1) {
				if (l < int(ans.size())) {
					ans[l] = num[0];
				}
			} else {
				int m = (l + r) >> 1;
				work(p << 1, l, m, num.mulT(q[p << 1 | 1]).modxk(m - l));
				work(p << 1 | 1, m, r, num.mulT(q[p << 1]).modxk(r - m));
			}
		};
		work(1, 0, n, mulT(q[1].inv(n)));
		return ans;
	}
};
int main() {
	int n = 0, m, k;
	io >> m >> k;
	auto FWT = [&](std::vector<Int> &f, bool rev) {
		for (int i = 0; i < k; ++i)
			for (int j = 0; j < (1 << k); j += (1 << (i + 1)))
				for (int p = 0; p < (1 << i); ++p) {
					auto x = f[j | p], y = f[j | p | (1 << i)];
					f[j | p] = x + y, f[j | p | (1 << i)] = x - y;
					if (rev) f[j | p] *= 499122177, f[j | p | (1 << i)] *= 499122177;
				}
	};
	std::vector<Int> f(1 << k), g(1 << k);
	for (int i = 0, x; i < (1 << k); ++i) {
		io >> x;
		f[i] = x;
		n += x;
	}
	if (n > 1E6) {
		return 0;
	}
	std::vector<Int> fac(n + 1, 1), inv(n + 1);
	for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i;
	inv[n] = Int(1) / fac[n];
	for (int i = n; i >= 1; --i) inv[i - 1] = inv[i] * i;
	Poly a(std::vector<Int>(m + 1)), b(std::vector<Int>(n - m + 1));
	for (int i = 0; i <= m; ++i) {
		a[i] = inv[i] * inv[m - i];
		if ((m - i) & 1) a[i] = Mod - a[i];
	}
	for (int i = 0; i <= n - m; ++i) b[i] = inv[i] * inv[n - m - i];
	a = a * b;
	for (int i = 0; i <= n; ++i) a[i] *= fac[i] * fac[n - i];
	FWT(f, false);
	for (int i = 0; i < (1 << k); ++i) g[i] = a[((n + f[i]) * 499122177).x];
	FWT(g, true);
	long long ans = 0;
	for (int i = 0; i < (1 << k); ++i) ans ^= (g[i] * (i + 1)).x;
	io << ans;
	return 0;
}