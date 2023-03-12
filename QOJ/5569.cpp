#include <bits/stdc++.h>
template <typename T> T inverse(T a, T m) {
	T u = 0, v = 1;
	while (a != 0) {
		T t = m / a;
		m -= t * a, std::swap(a, m);
		u -= t * v, std::swap(u, v);
	}
	assert(m == 1);
	return u;
}
template <typename T> class Modular {
public:
	using Type = typename std::decay<decltype(T::value)>::type;
	constexpr Modular() : value() {}
	template <typename U> Modular(const U& x) {value = normalize(x);}
	template <typename U> static Type normalize(const U& x) {
		Type v;
		if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
		else v = static_cast<Type>(x % mod());
		if (v < 0) v += mod();
		return v;
	}
	const Type& operator()() const { return value; }
	template <typename U> explicit operator U() const { return static_cast<U>(value); }
	constexpr static Type mod() { return T::value; }
	Modular& operator+=(const Modular& other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
	Modular& operator-=(const Modular& other) { if ((value -= other.value) < 0) value += mod(); return *this; }
	template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
	template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
	Modular operator-() const { return Modular(-value); }
	template <typename U = T> typename std::enable_if<std::is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
		value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
		return *this;
	}
	template <typename U = T> typename std::enable_if<std::is_same<typename Modular<U>::Type, long long>::value, Modular>::type& operator*=(const Modular& rhs) {
		long long q = static_cast<long long>(static_cast<long double>(value) * rhs.value / mod());
		value = normalize(value * rhs.value - q * mod());
		return *this;
	}
	template <typename U = T> typename std::enable_if<!std::is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
		value = normalize(value * rhs.value);
		return *this;
	}
	Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }
	template <typename U> friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);
	template <typename V, typename U> friend V& operator>>(V& stream, Modular<U>& number);
private:
	Type value;
};
template <typename T> bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }
template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T> Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T> Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T> Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> power(Modular<T> a, U b) {
	assert(b >= 0);
	for (Modular<T> res = 1; ; a *= a) {
		if (b & 1) res *= a;
		if ((b >>= 1) == 0) return res;
	}
}
template <typename U, typename T> U& operator<<(U& stream, const Modular<T>& number) { return stream << number(); }
template <typename U, typename T> U& operator>>(U& stream, Modular<T>& number) {
	typename std::common_type<typename Modular<T>::Type, long long>::type x;
	stream >> x;
	number.value = Modular<T>::normalize(x);
	return stream;
}
// using ModType = int;
// struct VarMod { static ModType value; };
// ModType VarMod::value;
// ModType& md = VarMod::value;
// using Mint = Modular<VarMod>;
constexpr int md = 998244353;
using Mint = Modular<std::integral_constant<std::decay<decltype(md)>::type, md>>;
std::vector<Mint> fact{1}, inv_fact{1};
Mint C(int n, int k) {
	if (k < 0 || k > n) return 0;
	while ((int) fact.size() < n + 1) {
		fact.push_back(fact.back() * (int) fact.size());
		inv_fact.push_back(1 / fact.back());
	}
	return fact[n] * inv_fact[k] * inv_fact[n - k];
}
template <typename T>
class NTT {
public:
	using Type = typename std::decay<decltype(T::value)>::type;
	static Type md;
	static Modular<T> root;
	static int base;
	static int max_base;
	static std::vector<Modular<T>> roots;
	static std::vector<int> rev;
	static void clear() {
		root = base = max_base = 0;
		roots.clear(), rev.clear();
	}
	static void init() {
		md = T::value;
		assert(md >= 3 && md % 2 == 1);
		auto tmp = md - 1;
		max_base = 0;
		for (; tmp % 2 == 0; ++max_base) tmp /= 2;
		root = 2;
		while (power(root, (md - 1) >> 1) == 1) root += 1;
		assert(power(root, md - 1) == 1);
		root = power(root, (md - 1) >> max_base);
		base = 1;
		rev = {0, 1};
		roots = {0, 1};
	}
	static void ensure_base(int nbase) {
		if (md != T::value) clear();
		if (roots.empty()) init();
		if (nbase <= base) return;
		assert(nbase <= max_base);
		rev.resize(1 << nbase);
		for (int i = 0; i < (1 << nbase); i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
		roots.resize(1 << nbase);
		for (; base < nbase; ++base) {
			Modular<T> z = power(root, 1 << (max_base - 1 - base));
			for (int i = 1 << (base - 1); i < (1 << base); i++)
				roots[i << 1] = roots[i], roots[(i << 1) + 1] = roots[i] * z;
		}
	}
	static void fft(std::vector<Modular<T>> &a) {
		int n = (int)a.size(), zeros = __builtin_ctz(n), shift = base - zeros;
		assert((n & (n - 1)) == 0);
		ensure_base(zeros);
		for (int i = 0; i < n; i++) if (i < (rev[i] >> shift)) swap(a[i], a[rev[i] >> shift]);
		for (int k = 1; k < n; k <<= 1)
			for (int i = 0; i < n; i += 2 * k)
				for (int j = 0; j < k; j++) {
					Modular<T> x = a[i + j], y = a[i + j + k] * roots[j + k];
					a[i + j] = x + y;
					a[i + j + k] = x - y;
				}
	}
	static std::vector<Modular<T>> multiply(std::vector<Modular<T>> a, std::vector<Modular<T>> b) {
		if (a.empty() || b.empty()) return {};
		int eq = (a == b), need = (int) a.size() + (int) b.size() - 1, nbase = 0;
		while ((1 << nbase) < need) nbase++;
		ensure_base(nbase);
		int sz = 1 << nbase;
		a.resize(sz), b.resize(sz), fft(a);
		if (eq) b = a; else fft(b);
		Modular<T> inv_sz = 1 / static_cast<Modular<T>>(sz);
		for (int i = 0; i < sz; i++) a[i] *= b[i] * inv_sz;
		reverse(a.begin() + 1, a.end());
		fft(a), a.resize(need);
		return a;
	}
};
template <typename T> typename NTT<T>::Type NTT<T>::md;
template <typename T> Modular<T> NTT<T>::root;
template <typename T> int NTT<T>::base;
template <typename T> int NTT<T>::max_base;
template <typename T> std::vector<Modular<T>> NTT<T>::roots;
template <typename T> std::vector<int> NTT<T>::rev;
template <typename T> std::vector<Modular<T>> inverse(const std::vector<Modular<T>>& a) {
	assert(!a.empty());
	int n = (int) a.size();
	std::vector<Modular<T>> b = {1 / a[0]};
	while ((int) b.size() < n) {
		std::vector<Modular<T>> x(a.begin(), a.begin() + min(a.size(), b.size() << 1));
		x.resize(b.size() << 1);
		b.resize(b.size() << 1);
		std::vector<Modular<T>> c = b;
		NTT<T>::fft(c);
		NTT<T>::fft(x);
		Modular<T> inv = 1 / static_cast<Modular<T>>((int) x.size());
		for (int i = 0; i < (int) x.size(); i++) x[i] *= c[i] * inv;
		reverse(x.begin() + 1, x.end());
		NTT<T>::fft(x);
		rotate(x.begin(), x.begin() + (x.size() >> 1), x.end());
		fill(x.begin() + (x.size() >> 1), x.end(), 0);
		NTT<T>::fft(x);
		for (int i = 0; i < (int) x.size(); i++) x[i] *= c[i] * inv;
		reverse(x.begin() + 1, x.end());
		NTT<T>::fft(x);
		for (int i = 0; i < ((int) x.size() >> 1); i++) b[i + ((int) x.size() >> 1)] = -x[i];
	}
	b.resize(n);
	return b;
}
template <typename T> std::vector<Modular<T>> operator*(const std::vector<Modular<T>>& a, const std::vector<Modular<T>>& b) {
	if (a.empty() || b.empty()) return {};
	if (std::min(a.size(), b.size()) < 150) {
		std::vector<Modular<T>> c(a.size() + b.size() - 1, 0);
		for (int i = 0; i < (int) a.size(); i++)
			for (int j = 0; j < (int) b.size(); j++)
				c[i + j] += a[i] * b[j];
		return c;
	}
	return NTT<T>::multiply(a, b);
}
template <typename T> std::vector<Modular<T>> operator+=(std::vector<Modular<T>>& a, const std::vector<Modular<T>>& b) {
	// if (a.empty() || b.empty()) return {};
	int n = a.size(), m = b.size();
	a.resize(std::max(n, m));
	for (int i = 0; i < m; ++i) a[i] += b[i];
	return a;
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, K;
	std::string s;
	std::cin >> n >> K >> s;
	std::vector<int> a;
	for (int i = 0, j; i < n; i = j + 1) {
		for (j = i; j < n - 1; ++j)
			if (s[j + 1] != s[i]) break;
		a.emplace_back(j - i + 1);
	}
	using Info = std::array<std::array<std::vector<Mint>, 2>, 2>;
	auto Solve = [&](auto &&self, int l, int r) {
		if (r - l == 1) {
			Info f;
			f[0][0].assign(a[l], 1);
			f[0][0][0] = 0;
			f[0][1].resize(a[l] + 1);
			f[0][1][a[l]] = 1;
			f[1][0].assign(1, 1);
			return f;
		}
		int m = (l + r) >> 1;
		auto f = self(self, l, m), g = self(self, m, r);
		Info res;
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
				for (int k = 0; k < 2; ++k)
					for (int p = 0; p < 2; ++p) {
						if (k == 1 && j == 0) continue;
						res[i][p] += f[i][j] * g[k][p];
					}
		return res;
	};
	auto res = Solve(Solve, 0, a.size());
	Mint ans = power(Mint(2), K);
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j) {
			for (int p = 0; p < K && p < (int)res[i][j].size(); ++p)
				ans -= power(Mint(2), K - p - (j == 0)) * res[i][j][p];
		}
	std::cout << ans << '\n';
	return 0;
}