#include <bits/stdc++.h>
template <unsigned Mod>
class Z {
	unsigned v_;
	static constexpr unsigned getR() {
		unsigned iv = Mod * (2 - Mod * Mod);
		iv *= 2 - Mod * iv;
		iv *= 2 - Mod * iv;
		return iv * (Mod * iv - 2);
	}
	static constexpr unsigned reduce(unsigned long long x)
		{return (x + static_cast<unsigned long long>(static_cast<unsigned>(x) * r) * Mod) >> 32;}
	static constexpr unsigned norm(unsigned x) { return x - (Mod & -((Mod - 1 - x) >> 31)); }
	static constexpr unsigned r    = getR();
	static constexpr unsigned r2   = -static_cast<unsigned long long>(Mod) % Mod;
	static constexpr unsigned mod2 = Mod << 1;
public:
	constexpr Z() : v_() {}
	template <typename Int>
	constexpr Z(Int v)
		: v_(reduce(static_cast<unsigned long long>(v % static_cast<int>(Mod) + static_cast<int>(Mod)) * r2)) {}
	static constexpr unsigned mod() { return Mod; }
	constexpr unsigned val() const { return norm(reduce(v_)); }
	template <typename Int>
	explicit constexpr operator Int() const { return static_cast<Int>(val()); }
	constexpr Z operator-() const {
		Z res;
		res.v_ = (mod2 & -(v_ != 0)) - v_;
		return res;
	}
	constexpr Z inv() const {
		int x1 = 1, x3 = 0, a = val(), b = mod();
		while (b != 0) {
		  int q = a / b, x1_old = x1, a_old = a;
		  x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
		}
		return Z(x1);
	}
	constexpr Z &operator+=(const Z &rhs) {
		v_ += rhs.v_ - mod2;
		v_ += mod2 & -(v_ >> 31);
		return *this;
	}
	constexpr Z &operator-=(const Z &rhs) {
		v_ -= rhs.v_;
		v_ += mod2 & -(v_ >> 31);
		return *this;
	}
	constexpr Z &operator*=(const Z &rhs) { return v_ = reduce(static_cast<unsigned long long>(v_) * rhs.v_), *this;}
	constexpr Z &operator/=(const Z &rhs) { return operator*=(rhs.inv()); }
	constexpr Z pow(unsigned long long e) const {
		for (Z res(1u), x(*this);; x *= x) {
		  if (e & 1) res *= x;
		  if ((e >>= 1) == 0) return res;
		}
	}
	friend constexpr Z operator+(const Z &lhs, const Z &rhs) { return Z(lhs) += rhs; }
	friend constexpr Z operator-(const Z &lhs, const Z &rhs) { return Z(lhs) -= rhs; }
	friend constexpr Z operator*(const Z &lhs, const Z &rhs) { return Z(lhs) *= rhs; }
	friend constexpr Z operator/(const Z &lhs, const Z &rhs) { return Z(lhs) /= rhs; }
	friend constexpr bool operator==(const Z &lhs, const Z &rhs) { return norm(lhs.v_) == norm(rhs.v_); }
	friend constexpr bool operator!=(const Z &lhs, const Z &rhs) { return norm(lhs.v_) != norm(rhs.v_); }
	friend std::istream &operator>>(std::istream &is, Z &rhs) {
		int x;
		is >> x;
		rhs = Z(x);
		return is;
	}
	friend std::ostream &operator<<(std::ostream &os, const Z &rhs) { return os << rhs.val(); }
};
const unsigned Mod = 998244353;
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
	Poly mulT(Poly b) const {
		if (b.size() == 0) return Poly();
		int n = b.size();
		std::reverse(b.a.begin(), b.a.end());
		return ((*this) * b).divxk(n - 1);
	}
public:
	Poly() {}
	Poly(const std::vector<Int> &a) : a(a) {}
	Poly(const std::initializer_list<Int> &a) : a(a) {}
	/**
	 * @brief Construct a New Polynomial from n Points
	 * @param a Vector of Points in Form of std::pair (x_i, y_i)
	 */
	Poly(const std::vector<std::pair<Int, Int>> &a) {
		const int n = a.size();
		std::vector<Poly> q(4 << std::__lg(n)), f(4 << std::__lg(n));
		std::function<void(int, int, int)> Build = [&](int k, int l, int r) {
			if (r - l == 1) return q[k] = Poly{-a[l].first, 1}, void();
			int m = (l + r) >> 1;
			Build(k << 1, l, m);
			Build(k << 1 | 1, m, r);
			q[k] = q[k << 1] * q[k << 1 | 1];
		};
		Build(1, 0, n);
		const Poly M = q[1].deriv();
		std::vector<Int> _x;
		for (int i = 0; i < n; ++i) _x.push_back(a[i].first);
		auto _y = M.eval(_x);
		std::function<void(int, int, int)> Solve = [&](int k, int l, int r) {
			if (r - l == 1) {
				return f[k] = Poly{a[l].second / _y[l]}, void();
			}
			int m = (l + r) >> 1;
			Solve(k << 1, l, m);
			Solve(k << 1 | 1, m, r);
			f[k] = f[k << 1] * q[k << 1 | 1] + f[k << 1 | 1] * q[k << 1];
		};
		Solve(1, 0, n);
		(*this) = f[1];
	}
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
		a.resize(sz), b.resize(sz);
		a.dft(), b.dft();
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
	/**
	 * @brief the Polynomial's Derivative
	 */
	Poly deriv() const {
		if (a.empty()) return Poly();
		std::vector<Int> res(size() - 1);
		for (int i = 0; i < size() - 1; ++i) res[i] = (i + 1) * a[i + 1];
		return Poly(res);
	}
	/**
	 * @brief the Polynomial's Integral
	 */
	Poly integr() const {
		std::vector<Int> res(size() + 1);
		for (int i = 0; i < size(); ++i) res[i + 1] = a[i] / (i + 1);
		return Poly(res);
	}
	/**
	 * @brief the Polynomial's inverse
	 * @param m Polynomial's Degree of the Result
	 */
	Poly inv(int m) const {
		Poly x{Int(1) / a[0]};
		int k = 1;
		while (k < m) {
			k <<= 1;
			x = (x * (Poly{2} - modxk(k) * x)).modxk(k);
		}
		return x.modxk(m);
	}
	/**
	 * @brief the Polynomial's Logarithms
	 * @param m Polynomial's Degree of the Result
	 */
	Poly log(int m) const {return (deriv() * inv(m)).integr().modxk(m);}
	/**
	 * @brief the Polynomial's Exponentials
	 * @param m Polynomial's Degree of the Result
	 */
	Poly exp(int m) const {
		Poly x{1};
		int k = 1;
		while (k < m) {
			k <<= 1;
			x = (x * (Poly{1} - x.log(k) + modxk(k))).modxk(k);
		}
		return x.modxk(m);
	}
	/**
	 * @brief the Polynomial's Power
	 * @param k the Exponent
	 * @param m Polynomial's Degree of the Result
	 */
	Poly pow(int k, int m) const {
		int i = 0;
		while (i < size() && a[i] == 0) ++i;
		if (i == size() || 1LL * i * k >= m) return Poly(std::vector<Int>(m));
		Int v = a[i];
		auto f = divxk(i) * v;
		return (f.log(m - i * k) * k).exp(m - i * k).mulxk(i * k) * (Int(v).pow(k));
	}
	/**
	 * @brief the Polynomial's Square Root
	 * @param m Polynomial's Degree of the Result
	 */
	Poly sqrt(int m) const {
		Poly x{1};
		int k = 1;
		while (k < m) {
			k <<= 1;
			x = (x + (modxk(k) * x.inv(k)).modxk(k)) * ((Mod + 1) / 2);
		}
		return x.modxk(m);
	}
	/**
	 * @brief Compute the Polynomial's Value for all X in the Vector
	 * @param x the X Vector Needed to Be Computed
	 */
	std::vector<Int> eval(std::vector<Int> x) const {
		if (size() == 0) return std::vector<Int>(x.size(), 0);
		const int n = std::max(int(x.size()), size());
		std::vector<Poly> q(4 << std::__lg(n));
		std::vector<Int> ans(x.size());
		x.resize(n);
		std::function<void(int, int, int)> build = [&](int p, int l, int r) {
			if (r - l == 1) q[p] = Poly{1, -x[l]};
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
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::vector<Int> a(n);
	for (auto &c : a) std::cin >> c;
	Poly f{1, -12, 4};
	f = f.sqrt(n);
	f = Poly{3, -2} - f;
	for (int i = 0; i < n; ++i) f[i] *= 499122177;
	std::vector<Int> g(n + 1);
	for (int i = 1; i <= n; ++i) g[i] = f[i] * f[n - i];
	auto h = Poly(g) * Poly(a);
	Int ans = 0;
	for (int i = 1; i < n; ++i) ans += a[i] * h[i];
	std::cout << ans / 4 / f[n - 1] << '\n';
	return 0;
}