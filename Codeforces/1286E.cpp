#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::string s;
	s.resize(n + 1);
	std::vector<int> w(n + 1), nxt(n + 1), anc(n + 1), stk{1};
	std::cin >> s[1] >> w[1];
	std::map<int, int> f;
	std::cout << w[1] << '\n';
	auto Find = [&](int pos) {
		return w[*std::lower_bound(stk.begin(), stk.end(), pos)];
	};
	__int128 sum = 0, ans = w[1];
	std::function<void(__int128)> Print = [&](__int128 x) -> void {
		if (x >= 10) Print(x / 10);
		std::cout << int(x % 10);
	};
	for (int i = 2, j = 0; i <= n; ++i) {
		std::cin >> s[i] >> w[i];
		s[i] = (s[i] - 'a' + ans) % 26 + 'a';
		w[i] ^= (ans & ((1 << 30) - 1));
		while (j > 0 && s[i] != s[j + 1]) j = nxt[j];
		if (s[i] == s[j + 1]) ++j;
		nxt[i] = j;
		if (s[nxt[i - 1] + 1] == s[i]) anc[i - 1] = anc[nxt[i - 1]];
		else anc[i - 1] = nxt[i - 1];
		for (int k = i - 1; k > 0;) {
			if (s[k + 1] == s[i]) k = anc[k];
			else {
				auto v = Find(i - k);
				sum -= v;
				--f[v];
				if (f[v] == 0) f.erase(v);
				k = nxt[k];
			}
		}
		while (stk.size() && w[i] <= w[stk.back()]) stk.pop_back();
		stk.push_back(i);
		for (auto it = f.upper_bound(w[i]); it != f.end();) {
			sum += 1ll * (w[i] - it -> first) * it -> second;
			f[w[i]] += it -> second;
			auto t = std::next(it);
			f.erase(it);
			it = t;
		}
		if (s[1] == s[i]) ++f[w[i]], sum += w[i];
		ans += sum + w[stk.front()];
		// std::cout << ans << '\n';
		Print(ans);
		std::cout << '\n';
	}
	return 0;
}