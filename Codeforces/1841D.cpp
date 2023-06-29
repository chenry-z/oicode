#include <bits/stdc++.h>
#define int long long
using namespace std;
struct line
{
	int l, r;
};
bool cmp(line a, line b)
{
	if (a.l < b.l)
	{
		return 1;
	}
	if (a.l == b.l)
	{
		return a.r < b.r;
	}
	return 0;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		vector<line> l(n + 1);
		vector<int> pos(n + 1), R(n + 1), dp(n + 5);
		for (int i = 1; i <= n; ++i)
		{
			cin >> l[i].l >> l[i].r;
		}
		sort(l.begin(), l.end(), cmp);
		for (int i = 1; i <= n; ++i)
		{
			pos[i] = R[i] = i + 1;
			while (R[i] <= n && l[i].r >= l[R[i]].l)
			{
				++R[i];
			}
		}
		for (int i = 1; i <= n; ++i)
		{
			for (int j = i + 1; j < R[i]; ++j)
			{
				if (R[j] < R[pos[i]])
				{
					pos[i] = j;
				}
			}
		}
		vector<line> v;
		for (int i = 1; i <= n; ++i)
		{
			if (pos[i] >= R[i])
			{
				continue;
			}
			line a;
			a.l = i, a.r = R[pos[i]];
			a.r = max(a.r, R[i]);
			v.push_back(a);
		}
		sort(v.begin(), v.end(), cmp);
		int si = v.size();
		for (int i = 0; i < si; ++i)
		{
			int ll = v[i].l, rr = v[i].r;
			dp[rr] = max(dp[rr], dp[ll] + 1);
			for (int j = 1; j <= n + 1; ++j)
			{
				dp[j] = max(dp[j - 1], dp[j]);
			}
		}
		assert(dp[n + 1] * 2 <= n);
		cout << n - dp[n + 1] * 2 << "\n";
	}
	return 0;
}