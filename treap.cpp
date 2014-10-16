#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <stack>
#include <ctime>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <numeric>
#include <iostream>
#include <algorithm>
using namespace std;
#define LL long long
#define LD long double
#define VI vector<int>
#define PB push_back
#define N 111111
#define M 55555
#define update(x) z[x].size = z[z[x].ch[0]].size + z[z[x].ch[1]].size + z[x].count

int n, m, t, rt, ll, rr;
int a[N], ans[M];

struct data{
    int l, r, k, t;
friend bool operator < (const data &a, const data &b) {
return (a.l == b.l ? a.r < b.r : a.l < b.l);
}
} b[M];

struct node {
    int size, count, ch[2], w, d;
}z[N];


int ask(int x) {
    z[++t].d = x; z[t].w = rand();
    z[t].size = 1; z[t].count = 1;
    z[t].ch[0] = z[t].ch[1] = 0;
    return t;
}

void rotate(int &x, int t) {
    int y = z[x].ch[t];
    z[x].ch[t] = z[y].ch[t^1];
    z[y].ch[t^1] = x;
    update(x);
    update(y);
    x = y;
}

void insert(int &x, int y) {
    if (x) {
        if (y == z[x].d)
            z[x].count++;
        else {
            int t = z[x].d < y;
            insert(z[x].ch[t], y);
            if (z[x].w < z[z[x].ch[t]].w)
		rotate(x, t);
        }
    } else
        x = ask(y);
    update(x);
}

void remove(int &x, int y) {
    if (z[x].d == y) {
        if (z[x].count > 1) z[x].count--;
        else{
            if (!z[x].ch[0] && !z[x].ch[1]) {
            x = 0; return;
            }
            int t = z[z[x].ch[0]].w
                < z[z[x].ch[1]].w;
                rotate(x, t);
                remove(z[x].ch[t^1], y);
        }
    } else remove(z[x].ch[z[x].d < y], y);
    update(x);
}

int find(int x, int y) {
    if (z[z[x].ch[0]].size >= y)
        return find(z[x].ch[0], y);
    else if (z[z[x].ch[0]].size + z[x].count >=y)
        return z[x].d;
    else
        return find(z[x].ch[1],
        y - z[z[x].ch[0]].size - z[x].count);
}

int main(){
    //freopen("in.txt", "r", stdin);
    //freopen("ou.txt", "w", stdout);
    //srand(time(0));
    t = 0; rt = 0; z[0].w = -1;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 0; i < m;  i++)
    {scanf("%d%d%d", &b[i].l, &b[i].r, &b[i].k); b[i].t = i;}
    sort(b, b+m);
    ll = 1; rr = 0;
    for (int i = 0; i < m; i++) {
        while (b[i].r > rr) insert(rt, a[++rr]);
        while (b[i].l > ll) remove(rt, a[ll++]);
        ans[b[i].t] = find(rt, b[i].k);
    }
    for (int i = 0; i < m; i++) printf("%d\n", ans[i]);
    return 0;
}
