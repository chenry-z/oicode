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
const unsigned Mod = 998244353;
using Int = Z;
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
				Int e = Int(3).pow((Mod - 1) >> (k + 1));
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
	friend Poly operator*(Poly a, Poly b) {
		if (a.size() == 0 || b.size() == 0) return Poly();
		int sz = 1, tot = a.size() + b.size() - 1;
		while (sz < tot) sz <<= 1;
		a.resize(sz), b.resize(sz);
		a.dft(), b.dft();
		for (int i = 0; i < sz; ++i) a[i] *= b[i];
		a.idft();
		a.resize(tot);
		return a;
	}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	Int h, alpha, beta, pa, pb, qa, qb;
	std::cin >> n >> h >> alpha >> beta >> pa >> pb >> qa >> qb;
	Int p = pa / pb, q = qa / qb, ans = 0;
	std::vector<Int> a(n + 1), b(n + 1), fac(2 * n + 1, 1);
	for (int i = 1; i <= 2 * n; ++i) fac[i] = fac[i - 1] * i;
	for (int i = 1; i <= n; ++i) std::cin >> a[i];
	for (int i = 1; i <= n; ++i) std::cin >> b[i];
	for (int i = 1; i <= n; ++i)
		ans += h.pow(1ll * i * (n + 1)) * a[i] + h.pow(i) * b[i];
	for (int i = 0; i <= (n >> 1); ++i) std::swap(a[i], a[n - i]);
	Poly p1(std::vector<Int>(n + 1)), p2(std::vector<Int>(n + 1));
	for (int i = 0; i <= n; i++) p1[i] = h.pow(1ll * (n + 1) * i);
	Poly A = a * p1;
	p1.resize(n);
	for (int i = 0; i < n; ++i) p1[i] = A[i + n] * p.pow(i) / fac[i];
	for (int i = 1; i <= n; ++i) p2[i] = q.pow(i) * h.pow(i) / fac[i - 1];
	A = p1 * p2;
	for (int i = 1; i < n * 2; ++i) ans += fac[i - 1] * A[i];
	p1.resize(n + 1);
	p2.resize(n + 1);
	for (int i = 0; i <= (n >> 1); ++i) std::swap(b[i], b[n - i]);
	for (int i = 0; i <= n; ++i) p1[i] = h.pow(i);
	A = b * p1;
	p1.resize(n);
	for (int i = 0; i < n; ++i) p1[i] = A[i + n] * q.pow(i) / fac[i];
	for (int i = 1; i <= n; ++i) p2[i] = p.pow(i) * h.pow(1ll * i * (n + 1)) / fac[i - 1];
	A = p1 * p2;
	for (int i = 1; i < n * 2; ++i) ans += fac[i - 1] * A[i];
	p1.resize(n); p2.resize(n);
	for (int i = 0; i < n; ++i) p1[i] = p.pow(i) * (h.pow(1ll * (n + 1) * (n + 1)) - h.pow(1ll * (n + 1) * (i + 1))) / fac[i] / (h.pow(n + 1) - 1);
	for (int i = 0; i < n; ++i) p2[i] = q.pow(i) * (h.pow(n + 1) - h.pow(i + 1)) / (h - 1) / fac[i];
	A = p1 * p2;
	for (int i = 0; i < 2 * n - 1; ++i) ans += (p * alpha + q * beta) * fac[i] * A[i];
	std::cout << ans.x << std::endl;
	return 0;
}