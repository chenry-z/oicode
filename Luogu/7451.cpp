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
struct Linear {
	std::vector<std::bitset<455>> v;
	Linear() : v(455) {}
	bool Insert(std::bitset<455> x) {
		for (int i = 454; i >= 0; --i)
			if (x[i]) {
				if (v[i].any()) x ^= v[i];
				else return v[i] = x, true;
			}
		return false;
	}
};
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	const int N = 1E7;
	std::vector<int> pri;
	std::vector<int> vis(N + 1);
	for (int i = 2; i <= N; ++i) {
		if (!vis[i]) pri.push_back(i);
		for (auto p : pri) {
			if (i * p > N) break;
			vis[i * p] = 1;
			if (i % p == 0) break;
		}
	}
	int T;
	std::cin >> T;
	for (int L, R; T--;) {
		std::cin >> L >> R;
		using Int = Z<998244353>;
		if (R -  L + 1 <= 6E3) {
			std::unordered_map<int, std::bitset<455>> f;
			int ans = R - L + 1;
			Linear l;
			for (int x = L; x <= R; ++x) {
				std::bitset<455> ret;
				int t = x;
				for (int i = 0; pri[i] * pri[i] <= N && t != 1; ++i)
					while (t % pri[i] == 0) t /= pri[i], ret[i] = !ret[i];
				if (t != 1) {
					if (!f.count(t)) {
						f[t] = ret;
						--ans;
						continue;
					} else ret ^= f[t];
				}
				if (l.Insert(ret)) --ans;
			}
			// for (int i = 454; i >= 0; --i)
				// if (l.v[i].any()) --ans;
			std::cout << Int(2).pow(ans) << '\n';
		} else {
			int ans = R - L + 1;
			for (int i = 0; pri[i] <= R; ++i) {
				if (R / pri[i] != (L - 1) / pri[i]) --ans;
			}
			std::cout << Int(2).pow(ans) << '\n';
		}
	}
	return 0;
}