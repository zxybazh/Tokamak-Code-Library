#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 2011111;
typedef pair<int, int> pii;

bool operator <(pii A, pii B)
{
	if(A.first < B.first)
		return true;
	if(A.first == B.first && A.second > B.second)
		return true;
	return false;
}

int nxt[N][23];
int main()
{
	ios::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	vector<pii> V(0);
	for(int i = 0; i < m; i++)
	{
		int l, r; 
		cin >> l >> r;
		if(l > r)
			V.push_back(make_pair(l, r+n+1));
		else
		{
			//V.push_back(make_pair(l+n, r+n+1));
			V.push_back(make_pair(l, r+1));
		}
	}
	sort(V.begin(), V.end());
	vector<pii> tV(0);
	tV.push_back(V[0]);
	for(int i = 1; i < V.size(); i++)
		if(V[i].second > tV[tV.size()-1].second)
			tV.push_back(V[i]);
	V = tV;
	int t = 0;
	for(int i = 0; i < V.size()-1; i++)
	{
		while(t+1 < V.size() && V[i].second >= V[t+1].first)
			t++;
		nxt[i][0] = t;
	}
	nxt[V.size()-1][0] = V.size()-1;
	for(int j = 1; j < 23; j++)
		for(int i = 0; i < V.size(); i++)
		{
			nxt[i][j] = nxt[nxt[i][j-1]][j-1];
			//cout << i << ' ' << j << ' ' << nxt[i][j] << '\n';
		}
	int ans = 2333333;
	for(int i = 0; i < V.size(); i++)
	{
		int left = 0, right = 2211111;
		while(left+1 < right)
		{
			int mid = (left+right)>>1;
			int t = i;
			for(int j = 0; j < 23; j++)
				if(((mid-1)>>j)&1)
					t = nxt[t][j];
			//cout << t << ' ' << i << '\n';
			//cout << left << ' ' << right << ' ' << V[t].second-V[i].first << '\n';
			if(V[t].second-V[i].first >= n)
				right = mid;
			else left = mid;
		}
		//cout << left << '\n';
		ans = min(ans, left+1);
	}
	if(ans <= m)
		cout << ans << '\n';
	else cout << "impossible\n";
	return 0;
}