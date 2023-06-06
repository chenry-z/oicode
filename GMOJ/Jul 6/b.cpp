#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::string S, T;
	std::cin >> S >> T;
	int n = S.size(), m = T.size(), ans = 0;
	S = " " + S, T = " " + T;
	std::string ss = S;
	for (int i = 1; i <= n; ++i) {
		if (ans == n) break;
		for (char c = 'a'; c <= 'z'; ++c) {
			if (ans == n) break;
			std::vector<int> nxt(n + 1);
			S[i] = c;
			for (int i = 2, j = 0; i <= n; ++i) {
				while (j > 0 && S[i] != S[j + 1]) j = nxt[j];
				if (S[i] == S[j + 1]) ++j;
				nxt[i] = j;
			}
			for (int i = 1, j = 0; i <= m; ++i) {
				while (j > 0 && (j == n || T[i] != S[j + 1])) j = nxt[j];
				if (T[i] == S[j + 1]) ++j;
				ans = std::max(ans, j);
			}
			S = ss;
		}
	}
	std::cout << ans << std::endl;
	return 0;
}