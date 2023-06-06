#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int x = 0, f = 1;
	char ch;
	do
	{
		ch = getchar();
		if (ch == '-')
		{
			f = -1;
		}
	} while (!(ch >= '0' && ch <= '9'));
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
int n, c[10], minx = 0x3f3f3f3f3f, cnt, pos;
char ans[2000005];
int main() {
	n = read();
	for (int i = 1; i <= 9; ++i) {
		c[i] = read();
		if (c[i] <= minx) minx = c[i], pos = i;
	}
	int r = n / minx;
	for (int i = 9; i >= 1; i--) {
		if (i == pos) {
			for (int j = 1; j <= r; ++j) ans[++cnt] = pos + '0';
			break;
		}
		if (n == minx * r) {
			for (int j = 1; j <= r; ++j) ans[++cnt] = pos + '0';
			break;
		}
		int p = (n - minx * r) / (c[i] - minx);
		r -= p;
		n -= p * c[i];
		for (int j = 1; j <= p; ++j) ans[++cnt] = i + '0';
	}
	for (int i = 1; i <= cnt; ++i) printf("%c", ans[i]);
	return 0;
}