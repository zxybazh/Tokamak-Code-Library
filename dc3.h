int max(int a, int b) {return a > b ? a : b;}
int min(int a, int b) {return a < b ? a : b;}

class SA
{
	const int SLEN =;
	const int SM =;
	public:

	int n, special;
	int a[SLEN], b[SLEN], cnt[SLEN], last[SLEN], rank[SM], sa[SM], sa12[SLEN], sa3[SLEN], height[SLEN];

	int f(int x, int len) {return x / 3 + (x % 3 == 1 ? 0 : len);}
	int g(int x, int len) {return x < len ? x * 3 + 1 : (x - len) * 3 + 2;}

	bool cmp_equal(int *a, int i, int j) {return a[i] == a[j] && a[i + 1] == a[j + 1] && a[i + 2] == a[j + 2];}
	bool cmp_small(int *a, int i, int j, int flag)
	{
		if (a[i] != a[j]) return a[i] < a[j];
		if (flag == 1) return b[i + 1] < b[j + 1]; else return cmp_small(a, i + 1, j + 1, 1);
	}

	void radix(int *a, int *last, int *now, int n, int m)
	{
		int i;

		REP(i, m + 1) cnt[i] = 0;
		REP(i, n) b[i] = a[last[i]];
		REP(i, n) cnt[b[i]]++;
		REP1(i, m) cnt[i] += cnt[i - 1];
		for (i = n - 1; i >= 0; i--) now[--cnt[b[i]]] = last[i];
	}

	void dc3(int *rank, int *sa, int n, int m)
	{
		int cnt, cnt12, cnt3, i, j, k, len = (n + 1) / 3;
		int *trank = rank + n, *tsa = sa + n;

		cnt = cnt12 = cnt3 = i = j = k = 0;
		rank[n] = rank[n + 1] = 0;
		for (i = n - 1; i >= 0; i--) if (i % 3) last[cnt12++] = i;
		radix(rank + 2, last, sa12, cnt12, m);
		radix(rank + 1, sa12, last, cnt12, m);
		radix(rank, last, sa12, cnt12, m);
		trank[f(sa12[0], len)] = cnt;
		REP1(i, cnt12 - 1) trank[f(sa12[i], len)] = cmp_equal(rank, sa12[i], sa12[i - 1]) ? cnt : ++cnt;
		if (cnt + 1 < cnt12) dc3(trank, tsa, cnt12, cnt); else REP(i, cnt12) tsa[trank[i]] = i;
		if (n % 3 == 1) last[cnt3++] = n - 1;
		REP(i, cnt12) if (tsa[i] < len) last[cnt3++] = tsa[i] * 3;
		radix(rank, last, sa3, cnt3, m);
		b[n] = b[n + 1] = -1;
		rank[n] = rank[n + 1] = -1;
		REP(i, cnt12) sa12[i] = g(tsa[i], len);
		REP(i, cnt12) b[sa12[i]] = i;
		for (i = 0; j < cnt12 && k < cnt3; i++) sa[i] = cmp_small(rank, sa12[j], sa3[k],  sa12[j] % 3) ? sa12[j++] : sa3[k++];
		while (j < cnt12) sa[i++] = sa12[j++];
		while (k < cnt3) sa[i++] = sa3[k++];
		REP(i, n) rank[sa[i]] = i;
	}

	int next_height(int id, int last)
	{
		int i = last;

		if (id < 2) return 0;
		while (a[sa[id] + i] == a[sa[id - 1] + i] && a[sa[id] + i] != sp && sa[id] + i < n && sa[id - 1] + i < n) i++;
		height[id] = i;
		return i;
	}

	void get_height()
	{
		int i, last = next_height(rank[0], 0);

		REP1(i, n - 1) last = next_height(rank[i], max(0, last - 1));
	}

	void go(int *da, int dn, int m)
	{
		int i;

		n = dn;
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		memset(cnt, 0, sizeof(cnt));
		memset(last, 0, sizeof(last));
		memset(rank, 0, sizeof(rank));
		memset(sa, 0, sizeof(sa));
		memset(sa12, 0, sizeof(sa12));
		memset(sa3, 0, sizeof(sa3));
		memset(height, 0, sizeof(height));
		REP(i, n) a[i] = da[i];
		REP(i, n) rank[i] = a[i];
		rank[n++] = 0;
		dc3(rank, sa, n, m);
		get_height();
	}
};
