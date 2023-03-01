#include <bits/stdc++.h>
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int L, R;
	std::cin >> L >> R;
	std::vector<int> sum(1001);
	for (int i = 1; i <= 9; ++i) sum[i * 10 + i] = 1;
	for (int i = 1; i <= 9; ++i) {
		for (int j = 1; j <= i; ++j) {
			int k = i - j;
			sum[i * 100 + j * 10 + k] = 1;
			sum[i * 100 + k * 10 + j] = 1;
			sum[j * 100 + i * 10 + k] = 1;
			sum[j * 100 + k * 10 + i] = 1;
			sum[k * 100 + j * 10 + i] = 1;
			sum[k * 100 + i * 10 + j] = 1;
		}
	}
	for (int i = 1; i <= 1000; ++i) sum[i] += sum[i - 1];
	std::cout << sum[R] - sum[L - 1] << std::endl;
	return 0;
}