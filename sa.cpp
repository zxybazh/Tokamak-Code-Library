/*
    Author  :   WJMZBMR (added explaination by zxybazh)
    Data    :   2012.12.24
    Source  :   SPOJ_694_705
    Solution:   Suffix_Array_DA_sort
    Edit with *GVIM* in UBUNTU
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#define LL long long
using namespace std;

#define N 55555
#define fo(i, l, r) for (int i = l; i < r; i++)
#define fd(i, r, l) for (int i = r; i >= l;i--)
#define rep(i, r) fo(i, 0, r)

int testcase, n;
char A[N];
int ta[N], tb[N], sa[N], h[N];
int m, *x = ta, *y = tb;
LL ans;

void Sort()
//Radix Sort
{
    static int w[N];
    //clear W array
    rep(i, m) w[i]  = 0;
    rep(i, n) w[x[y[i]]]++;
    //count sort
    rep(i, m - 1) w[i + 1] += w[i];
    //make count
    fd(i, n - 1, 0) sa[--w[x[y[i]]]] = y[i];
    //calculate the ranks from 0 So -- before w[x[y[i]]];
    //smaller ones make bigger ranks;
}

bool cmp(int a, int b, int l)
{
    return (y[a] == y[b] && y[a + l] == y[b + l]);
}

void DA()
{
    rep(i, n){x[i] = A[i];y[i] = i;}
    Sort();
    //make it constant;
    int i, j, p;
    for(j = 1,p = 1; p < n; j *= 2, m = p)
    {
        /*j = 2^k to make double;*/
        for(p = 0, i = n - j; i < n; i++) y[p++] = i;
        //from n - j to n  all are beyond n;
        //So the answer can be made by the any order;
        rep(k, n) if (sa[k] >= j) y[p++] = sa[k] - j;
        //make the first ones by the sa order;
        Sort();
        //sort by the y array order;
        for(swap(x, y), p = 1, x[sa[0]] = 0,i = 1;i < n; i++)
        //make the ranks again sa[0] must be 0;
                x[sa[i]] = cmp(sa[i - 1], sa[i], j)?p - 1 : p++;
                //sa[i - 1] if the closest to sa[i] check equal or p++;
    }
}

void Calc_H()
{
    static int R[N];
    //Ra array : Suffix[i]'s rank;
    //Sa array : who is rank[i];
    int i, j, k = 0;
    for(i = 1; i <= n; i++) R[sa[i]] = i;
    //make Ra array
    for(i = 0; i < n; h[R[i++]] = k)
        // make height array by the order of i;
        for (k ? k-- : 0,j = sa[R[i] - 1];A[i + k] == A[j + k]; k++);
        /*h[i] >= h[i - 1] - 1 && h[i] >= 0;*/
}

void work()
{
    m = 256;
    //number of the all different ranks;
    gets(A);
    n = strlen(A);
    A[n++] = 0;

    DA();
    //double algorithm;
    n--;
    //delete the end of the array : added for convenience;
    Calc_H();
    //calculate the height array;
    LL ans = ((LL) n + 1) * (LL) n / 2;
    //all the substrings sums C(n,2);
    rep(i, n) ans -= h[i + 1];
    //h[i] substrings are recalculated;
    printf("%lld\n", ans);
}

int main()
{
    //freopen("in.txt", "r", stdin );
    //freopen("ou.txt", "w", stdout);

    scanf("%d\n", &testcase);
    while (testcase--) work();

    return 0;
}
