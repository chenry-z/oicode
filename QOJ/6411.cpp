#include <bits/stdc++.h>
template <std::uint32_t Mod>
class Z {
  using u32 = std::uint32_t;
  using i32 = std::int32_t;
  using u64 = std::uint64_t;
  u32 v_;

  static constexpr u32 getR() {
    u32 two = 2, iv = Mod * (two - Mod * Mod);
    iv *= two - Mod * iv;
    iv *= two - Mod * iv;
    return iv * (Mod * iv - two);
  }

  static constexpr u32 reduce(u64 x) {
    return (x + static_cast<u64>(static_cast<u32>(x) * r) * Mod) >> 32;
  }
  static constexpr u32 norm(u32 x) { return x - (Mod & -((Mod - 1 - x) >> 31)); }

  static constexpr u32 r    = getR();
  static constexpr u32 r2   = -static_cast<u64>(Mod) % Mod;
  static constexpr u32 mod2 = Mod << 1;

  static_assert(Mod & 1);
  static_assert(-r * Mod == 1);
  static_assert((Mod >> 30) == 0);
  static_assert(Mod != 1);

public:
  constexpr Z() : v_() {}
  template <typename Int, std::enable_if_t<std::is_integral_v<Int>, int> = 0>
  constexpr Z(Int v)
      : v_(reduce(static_cast<u64>(v % static_cast<i32>(Mod) + static_cast<i32>(Mod)) * r2)) {}
  static constexpr u32 mod() { return Mod; }
  static constexpr i32 smod() { return Mod; }
  constexpr u32 val() const { return norm(reduce(v_)); }
  constexpr i32 sval() const { return norm(reduce(v_)); }
  template <typename Int, std::enable_if_t<std::is_integral_v<Int>, int> = 0>
  explicit constexpr operator Int() const {
    return static_cast<Int>(val());
  }
  constexpr Z operator-() const {
    Z res;
    res.v_ = (mod2 & -(v_ != 0)) - v_;
    return res;
  }
  constexpr Z inv() const {
    i32 x1 = 1, x3 = 0, a = sval(), b = smod();
    while (b != 0) {
      i32 q = a / b, x1_old = x1, a_old = a;
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
  constexpr Z &operator*=(const Z &rhs) {
    v_ = reduce(static_cast<u64>(v_) * rhs.v_);
    return *this;
  }
  constexpr Z &operator/=(const Z &rhs) { return operator*=(rhs.inv()); }
  constexpr Z pow(u64 e) const {
    for (Z res(1u), x(*this);; x *= x) {
      if (e & 1) res *= x;
      if ((e >>= 1) == 0) return res;
    }
  }

  friend constexpr Z operator+(const Z &lhs, const Z &rhs) { return Z(lhs) += rhs; }
  friend constexpr Z operator-(const Z &lhs, const Z &rhs) { return Z(lhs) -= rhs; }
  friend constexpr Z operator*(const Z &lhs, const Z &rhs) { return Z(lhs) *= rhs; }
  friend constexpr Z operator/(const Z &lhs, const Z &rhs) { return Z(lhs) /= rhs; }
  friend constexpr bool operator==(const Z &lhs, const Z &rhs) {
    return norm(lhs.v_) == norm(rhs.v_);
  }
  friend constexpr bool operator!=(const Z &lhs, const Z &rhs) {
    return norm(lhs.v_) != norm(rhs.v_);
  }
  friend std::istream &operator>>(std::istream &is, Z &rhs) {
    i32 x;
    is >> x;
    rhs = Z(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const Z &rhs) { return os << rhs.val(); }
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
		while (i < size() && a[i] == 0) ++i;
		if (i == size() || 1LL * i * k >= m) return Poly(std::vector<Int>(m));
		Int v = a[i];
		auto f = divxk(i) * v;
		return (f.log(m - i * k) * k).exp(m - i * k).mulxk(i * k) * (Int(v).pow(k));
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
std::vector<Int> fact{1}, inv_fact{1};
Int C(int n, int k) {
	if (k < 0 || k > n) return 0;
	while ((int) fact.size() < n + 1) {
		fact.push_back(fact.back() * (int) fact.size());
		inv_fact.push_back(1 / fact.back());
	}
	return fact[n] * inv_fact[k] * inv_fact[n - k];
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, K = 0;
	std::cin >> n;
	auto Calc = [&](std::vector<int> a) {
		for (int i = 1; i <= n; ++i)
			if (i <= K) assert(a[i] >= K);
			else assert(a[i] <= K);
		std::function<Poly(int, int)> Solve = [&](int l, int r) -> Poly {
			if (l == r) return {a[l], Mod - 1};
			int m = (l + r) >> 1;
			return Solve(l, m) * Solve(m + 1, r);
		};
		auto F = Solve(1, K);
		int T = (K == n ? 0 : a[K + 1]);
		std::vector<Int> X(T + 1);
		for (int i = 0; i <= T; ++i) X[i] = i;
		auto f = F.eval(X);
		Int ans = 0;
		for (int i = 0; i <= T; ++i)
			if (i & 1) ans -= C(T, i) * f[i];
			else ans += C(T, i) * f[i];
		return ans;
	};
	std::vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; ++i) std::cin >> a[i], ++b[a[i]];
	for (int i = n - 1; i >= 1; --i) b[i] += b[i + 1];
	std::reverse(a.begin() + 1, a.end());
	for (int i = 1; i <= n; ++i) K = std::max(K, std::min(a[i], i));
	C(K, 0);
	std::cout << K << ' ' << Calc(a) + Calc(b) - fact[K] << '\n';
	return 0;
}