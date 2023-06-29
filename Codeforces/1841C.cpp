#include <bits/stdc++.h>
int main() {
	#define int long long
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T;
	std::cin >> T;
	while (T--) {
		std::string s;
		std::cin >> s;
		int n = s.size();
		s = " " + s;
		std::vector<int> a{1, 10, 100, 1000, 10000};
		std::vector<int> coff(n + 1), mxc(n + 2), sum(n + 1);
		std::vector ssum(5, std::vector(n + 1, 0));
		long long ans = 0;
		for (int i = n, mx = 'A' - 1; i >= 1; --i) {
			if (s[i] >= mx) {
				mx = s[i];
				coff[i] = 1;
				ans += a[s[i] - 'A'];
			} else coff[i] = -1, ans -= a[s[i] - 'A'];
			mxc[i] = mx;
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 0; j < 5; ++j) {
				ssum[j][i] = ssum[j][i - 1] + ((s[i] - 'A' >= j && coff[i] == -1) ? a[s[i] - 'A'] : 0);
			}
		long long ret = ans;
		for (char c = 'A'; c <= 'E'; ++c) {
			for (int i = 1; i < n; ++i) {
				sum[i] = sum[i - 1];
				if (coff[i] == 1 && s[i] < c) sum[i] += a[s[i] - 'A'];
			}
			for (int i = 1; i <= n; ++i) {
				ret = std::max(ret, ans - 2 * sum[i - 1] + 2 * ssum[std::max((char)mxc[i + 1], c) - 'A'][i - 1] - a[s[i] - 'A'] * coff[i] + a[c - 'A']);
			}
		}
		std::cout << ret << '\n';
	}
	return 0;
}