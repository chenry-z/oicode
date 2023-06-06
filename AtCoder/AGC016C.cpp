#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int H, W, h, w, K = 500;
	std::cin >> H >> W >> h >> w;
	if (H % h == 0 && W % w == 0) return std::cout << "No\n", 0;
	std::cout << "Yes\n";
	int val = (h * w - 1) * K + 1;
	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j)
			if (i % h == 0 && j % w == 0) std::cout << -val << " \n"[j == W];
			else std::cout << K << " \n"[j == W];
	return 0;
}