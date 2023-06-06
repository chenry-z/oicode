#include <bits/stdc++.h>
#define int long long
using namespace std;
const int INF = 0x3f3f3f3f;
const int MOD = 998244353;
const int N = 15;
int a[N][N];
string tmp;
int dx[8] = {1, 1, 1, 0, -1, -1, -1, 0};
int dy[8] = {1, 0, -1, -1, -1, 0, 1, 1};
signed main()
{
	int n, ans = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> tmp;
		for (int j = 1; j <= n; j++)
		{
			a[i][j] = tmp[j - 1] - '0';
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			for (int d = 0; d <= 7; d++)
			{
				int sum = a[i][j], tx = i, ty = j;
				for (int k = 1; k < n; k++)
				{
					tx += dx[d];
					ty += dy[d];
					if (tx == 0)
						tx = n;
					if (ty == 0)
						ty = n;
					if (tx == n + 1)
						tx = 1;
					if (ty == n + 1)
						ty = 1;
					sum = 1ll * sum * 10 + a[tx][ty];
				}
				ans = max(ans, sum);
			}
		}
	}
	cout << ans;
	return 0;
}