#include "atcoder/all"
#include "bits/stdc++.h"
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	int k;
	cin >> k;
	if (k < 10) cout << "21:0" << k << endl;
	else if (k < 60) cout << "21:" << k << endl;
	else if (k < 70) cout << "22:0" << k - 60 << endl;
	else cout << "22:" << k - 60 << endl;
	return 0;
}