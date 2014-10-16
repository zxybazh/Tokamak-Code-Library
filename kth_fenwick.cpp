#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 100001
#define M 55555
  
int f[N], a[N], b[N], ans[M], sym[N];
int n, m, x, y, z, D, ll, rr;
struct data{
    int x, y, k, t;
    friend bool operator < (const data &a, const data &b) {
        return (a.x == b.x ? a.y < b.y : a.x < b.x);
    }
}queries[M];
  
int lbt(int x) {return (x & (-x));}
  
void add(int x, int d) {
    while (x <= n) {
        f[x] += d;
        x += lbt(x);
    }
}
  
int ques(int k) {
    int ans = 0;
    for (int i = D - 1; i >= 0; i--) {
        if (ans + (1 << i) <= n && f[ans + (1 << i)] < k) {
            k -= f[ans += 1 << i];
        }
    }
    return ans + 1;
}
  
int main(){
    //freopen("in.txt", "r", stdin);
    //freopen("ou.txt", "w", stdout);
    D = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i); b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++) {
        int tmp = lower_bound(b + 1, b + n + 1, a[i]) - b;
        sym[tmp] = a[i];
        a[i] = tmp;
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &queries[i].x, &queries[i].y, &queries[i].k);
        queries[i].t = i;
    }
    while ((1 << D )<= n) D++;
    sort(queries + 1, queries + m + 1);
    ll = 1; rr = 0;
    for (int i = 1; i <= m; i++) {
        while (rr < queries[i].y) add(a[++rr], 1);
        while (ll < queries[i].x) add(a[ll++],-1);
        ans[queries[i].t] = ques(queries[i].k);
    }
    for (int i = 1; i <= m; i++) printf("%d\n", sym[ans[i]]);
    return 0;
}