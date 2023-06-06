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
using Int = Z<1000000007>;
using Info = std::vector<Int>;
using Matrix = std::vector<Info>;
Info operator * (const Info &a, const Matrix &b) {
	int n = a.size();
	Info c(n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			c[j] += a[i] * b[i][j];
	return c;
}
Matrix operator * (const Matrix &a, const Matrix &b) {
	int n = a.size();
	Matrix c(n, Info(n));
	for (int i = 0; i < n; ++i)
		for (int k = 0; k < n; ++k)
			if (a[i][k] != 0)
				for (int j = 0; j < n; ++j)
					c[i][j] += a[i][k] * b[k][j];
	return c;
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, K, m = 0;
	std::cin >> n >> K;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
		m += a[i] == 0;
	}
	Info ans(m + 1);
	{
		int _ = 0;
		for (int i = 0; i < m; ++i) _ += a[i] == 0;
		ans[_] = 1;
	}
	Matrix f(m + 1, Info(m + 1));
	for (int i = 0; i <= m; ++i) {
		Int ret = Int(n - 1) * n / 2;
		Int ret1 = Int(n - 2 * m + i) * i;
		Int ret2 = Int(m - i) * (m - i);
		if (i != 0) f[i][i - 1] = ret1 / ret;
		if (i != m) f[i][i + 1] = ret2 / ret;
		f[i][i] = (ret - ret1 - ret2) / ret;
	}
	for (; K; K >>= 1, f = f * f)
		if (K & 1) ans = ans * f;
	std::cout << ans[m] << '\n';
	return 0;
}