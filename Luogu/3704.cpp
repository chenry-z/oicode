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
	template <typename Int, std::enable_if_t<std::is_integral_v<Int>, int> = 0>
	constexpr Z(Int v)
		: v_(reduce(static_cast<unsigned long long>(v % static_cast<int>(Mod) + static_cast<int>(Mod)) * r2)) {}
	static constexpr unsigned mod() { return Mod; }
	constexpr unsigned val() const { return norm(reduce(v_)); }
	template <typename Int, std::enable_if_t<std::is_integral_v<Int>, int> = 0>
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
using Int = Z<1000000007>;
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	constexpr int N = 1E6;
	std::vector<int> pri, mu(N + 1);
	std::vector<Int> fib(N + 1), f(N + 1, 1);
	std::vector<bool> vis(N + 1);
	fib[2] = fib[1] = mu[1] = 1;
	for (int i = 3; i <= N; ++i) fib[i] = fib[i - 1] + fib[i - 2];
	for (int i = 2; i <= N; ++i) {
		if (!vis[i]) pri.push_back(i), mu[i] = -1;
		for (int p : pri) {
			if (p * i > N) break;
			vis[p * i] = true;
			if (i % p == 0) break;
			mu[i * p] = -mu[i];
		}
	}
	for (int i = 1; i <= N; ++i) {
		Int inv = 1 / fib[i];
		for (int j = i; j <= N; j += i) {
			if (mu[j / i] == -1) f[j] *= inv;
			else if (mu[j / i] == 1) f[j] *= fib[i];
		}
	}
	for (int i = 1; i <= N; ++i) f[i] *= f[i - 1];
	int T;
	std::cin >> T;
	for (int n, m; T--;) {
		std::cin >> n >> m;
		Int ans = 1;
		for (int x = 1, gx; x <= std::min(n, m); x = gx + 1) {
			gx = std::min(n / (n / x), m / (m / x));
			ans *= (f[gx] / f[x - 1]).pow(1ll * (n / x) * (m / x));
		}
		std::cout << ans << std::endl;
	}
	return 0;
}