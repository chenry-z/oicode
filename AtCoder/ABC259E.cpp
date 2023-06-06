#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	char ch;
	int x = 0, flag = 1;
	do
	{
		ch = getchar();
		if (ch == '-') flag = -1;
	} while (!(ch >= '0' && ch <= '9'));
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * flag;
}
int n, ans, m[200005];
vector<int> p[200005], e[200005];
unordered_map<int, int> ma, cnt;
signed main()
{
	n = read();
	for (int i = 0; i < n; ++i)
	{
		m[i] = read();
		for (int j = 0; j < m[i]; ++j)
		{
			int x = read();
			p[i].push_back(x);
			int num = read();
			e[i].push_back(num);
			ma[x] = max(num, ma[x]);
		}
	}
	int flag = 1;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m[i]; ++j)
			if (ma[p[i][j]] == e[i][j])
				cnt[p[i][j]]++;
	for (int i = 0; i < n; ++i)
	{
		int q = 0;
		for (int j = 0; j < m[i]; ++j)
			if (ma[p[i][j]] == e[i][j])
				if (cnt[p[i][j]] == 1)
				{
					q = 1;
					break;
				}
		if (q)
		{
			ans++;
			continue;
		}
		ans += flag;
		flag = 0;
	}
	printf("%d\n", ans);
	return 0;
}