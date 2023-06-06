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
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m, K;
	using edges = std::vector<std::pair<int, int>>;
	std::function<Mint(int, edges)> Solve = [&](int S, edges e) -> Mint {
		if (__builtin_popcount(S) == 1) return K;
		for (auto &[u, v] : e) {
			if (u > v) std::swap(u, v);
			assert(S >> u & 1);
			assert(S >> v & 1);
		}
		std::sort(e.begin(), e.end());
		e.erase(std::unique(e.begin(), e.end()), e.end());
		std::vector<std::vector<int>> g(n);
		for (auto [u, v] : e) {
			g[u].emplace_back(v);
			g[v].emplace_back(u);
		}
		{
			std::queue<int> q;
			q.emplace(__builtin_ctz(S));
			int T = 1 << __builtin_ctz(S);
			while (q.size()) {
				int u = q.front(); q.pop();
				for (auto v : g[u])
					if (!(T >> v & 1)) q.emplace(v), T |= 1 << v;
			}
			if (T != S) {
				edges eT, eS;
				for (auto [u, v] : e) {
					if (T >> u & 1) eT.emplace_back(u, v), assert(T >> v & 1);
					else eS.emplace_back(u, v);
				}
				return Solve(T, eT) * Solve(S ^ T, eS);
			}
		}
		int x = -1;
		for (int i = 0; i < n; ++i)
			if ((S >> i & 1) && (x == -1 || g[x].size() > g[i].size())) x = i;
		edges other;
		for (auto [u, v] : e)
			if (u != x && v != x) other.emplace_back(u, v);
		int M = g[x].size();
		Mint res = 0, sum = Solve(S ^ (1 << x), other);
		for (int T = 0; T < (1 << M); ++T) {
			if (T == 0) res += sum * K;
			else if (__builtin_popcount(T) == 1) res -= sum;
			else {
				int p = __builtin_ctz(T), nS = 1 << x;
				auto eT = other;
				bool flag = true;
				for (int i = 0; i < M; ++i)
					if (T >> i & 1) nS |= 1 << g[x][i];
				for (auto &[u, v] : eT) {
					if (nS >> u & 1) u = g[x][p];
					if (nS >> v & 1) v = g[x][p];
					if (u == v) flag = false;
				}
				if (!flag) continue;
				if (__builtin_parity(T)) res -= Solve((S ^ nS) | (1 << g[x][p]), eT); 
				else res += Solve((S ^ nS) | (1 << g[x][p]), eT);
			}
		}
		return res;
	};
	std::cin >> n >> m >> K;
	edges e;
	for (int i = 0, u, v; i < m; ++i) {
		std::cin >> u >> v;
		--u, --v;
		e.emplace_back(u, v);
	}
	std::cout << Solve((1 << n) - 1, e) << '\n';
	return 0;
}