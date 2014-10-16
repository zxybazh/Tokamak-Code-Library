/*
!!!!!!!!DANGER: have not been tested
	NOTE: a O(nlogn) algorithm of divide tree
	use sum[deep][i] to record prefix sum of how many node are in left

	fnl, fnr: the amount of elements before [lo2, hi2] in the left/right
	inl, inr: the amount of elements belongs to [lo2, hi2] in the left/right

	using class DIVIDE
	using constant LOGN
	using structure DNUM

!!!!!!!!future expection: change ask() into loop
*/

#include <algorithm>
#include <string.h>
#define REP(i, n) for (i = 0; i < n; i++)
#define REP1(i, n) for (i = 1; i <= n; i++)
using namespace std;

const int DLOGN = 30 +10;

struct DNUM
{
	int id;
	int v;
};

bool operator <(DNUM a, DNUM b) {return a.v != b.v ? a.v < b.v : a.id < b.id;}

class DIVIDE
{
	public:

	bool cmp_v(DNUM a, DNUM b) {return a.v != b.v ? a.v < b.v : a.id < b.id;}

	int n;
	int *flect;
	int *d[DLOGN];
	int *sum[DLOGN];

	DNUM *num;

	void divide(int deep, int lo, int hi)
	{
		int mid = (lo + hi) >> 1;
		int i;
		int j = lo;
		int k = mid + 1;

		if (lo >= hi) return;
		for (i = lo; i <= hi; i++)
		{
			sum[deep][i] = sum[deep][i - 1];
			if (flect[d[deep][i]] <= mid)
			{
				d[deep + 1][j++] = d[deep][i];
				sum[deep][i]++;
			}
			else d[deep + 1][k++] = d[deep][i];
		}
		divide(deep + 1, lo, mid);
		divide(deep + 1, mid + 1, hi);
	}

	void init(int SIZE, int *a)
	{
		int i;

		n = SIZE;
		SIZE += 10;
		REP(i, DLOGN) 
		{
			d[i] = new int[SIZE];
			sum[i] = new int[SIZE];
		}
		flect = new int[SIZE];
		num = new DNUM[SIZE]; 

		REP1(i, n)
		{
			num[i].v = a[i];
			num[i].id = i;
		}
		sort(num + 1, num + n + 1);
		REP1(i, n)
		{
			d[1][i] = i;
			flect[num[i].id] = i;
		}
		divide(1, 1, n);
	}

	int ask(int deep, int lo1, int hi1, int lo2, int hi2, int kth)
	{
		int fnl = sum[deep][lo2 - 1] - sum[deep][lo1 - 1];
		int fnr = lo2 - lo1 - fnl;
		int inl = sum[deep][hi2] - sum[deep][lo2 - 1];
		int inr = hi2 - lo2 + 1 - inl;
		int mid = (lo1 + hi1) >> 1;

		if (lo1 == hi1) return lo1;
		if (kth <= inl)
		{
			hi1 = mid;
			lo2 = lo1 + fnl;
			hi2 = lo2 + inl - 1;
		}
		else
		{
			lo1 = mid + 1;
			lo2 = lo1 + fnr;
			hi2 = lo2 + inr - 1;
			kth -= inl;
		}
		return ask(deep + 1, lo1, hi1, lo2, hi2, kth);
	}
};
