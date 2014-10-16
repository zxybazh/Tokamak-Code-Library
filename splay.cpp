/**************************************************************
    Problem: 1500
    User: zxybazh
    Language: C++
    Result: Accepted
    Time:7412 ms
    Memory:29504 kb
****************************************************************/
 
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 555555
 
class node {
    public:
    int maxl, maxr, del, maxn, data,
    size, f, ch[2], sum; bool rev, cov;
}z[N];
int n, m, st[N], top, tmp, *rt, lc, rc, p, a[N], k, la, fir, x, y;
char c, temp[111];
 
inline int max(int x, int y) {
    return x>y?x:y;
}
 
inline void swap(int &x, int &y) {
    x ^= y; y ^= x; x ^= y;
}
 
inline void _rev(int x) {
    z[x].rev ^= 1;
    swap(z[x].ch[0], z[x].ch[1]);
    swap(z[x].maxl, z[x].maxr);
}
 
inline void _cov(int x, int y) {
    z[x].data = y; z[x].sum = z[x].size * y;
    z[x].maxn = z[x].maxl = z[x].maxr = max(z[x].sum, y);
    z[x].cov = true; z[x].del = y;
}
 
inline void downtag(int x) {
    if (z[x].cov) {
        z[x].cov = z[x].rev = 0;
        if (z[x].ch[0]) _cov(z[x].ch[0], z[x].del);
        if (z[x].ch[1]) _cov(z[x].ch[1], z[x].del);
    }
    if (z[x].rev) {
        z[x].rev = 0;
        if (z[x].ch[0]) _rev(z[x].ch[0]);
        if (z[x].ch[1]) _rev(z[x].ch[1]);
    }
}
 
inline void update(int x) {
    lc = z[x].ch[0], rc = z[x].ch[1];
    z[x].size = z[lc].size + z[rc].size + 1;
    z[x].sum  = z[lc].sum  + z[rc].sum  + z[x].data;
    if (lc && rc) {
        z[x].maxl = max(z[lc].maxl, z[lc].sum + z[x].data);
        z[x].maxl = max(z[x].maxl, z[lc].sum + z[x].data + z[rc].maxl);
        z[x].maxr = max(z[rc].maxr, z[rc].sum + z[x].data);
        z[x].maxr = max(z[x].maxr, z[rc].sum + z[x].data + z[lc].maxr);
        z[x].maxn = z[x].data + max(z[lc].maxr, 0) + max(z[rc].maxl, 0);
        z[x].maxn = max(z[x].maxn, max(z[lc].maxn, z[rc].maxn));
    } else
    if (!(lc || rc)) {
        z[x].maxl = z[x].maxr = z[x].maxn = z[x].data;
    } else
    if (lc) {
        z[x].maxl = max(z[lc].maxl, z[lc].sum + z[x].data);
        z[x].maxr = max(z[lc].maxr + z[x].data, z[x].data);
        z[x].maxn = max(z[lc].maxn, z[x].maxr);
    } else {
        z[x].maxr = max(z[rc].maxr, z[rc].sum + z[x].data);
        z[x].maxl = max(z[rc].maxl + z[x].data, z[x].data);
        z[x].maxn = max(z[rc].maxn, z[x].maxl);
    }
}
 
inline void rotate(int x, int t) {
    int y = z[x].ch[t];
    if (z[x].cov || z[x].rev) downtag(x);
    if (z[y].cov || z[y].rev) downtag(y);
    z[x].ch[t] = z[y].ch[t^1];
    z[z[x].ch[t]].f = x;
    z[z[x].f].ch[z[z[x].f].ch[1] == x] = y;
    z[y].f = z[x].f;
    z[y].ch[t^1] = x;
    z[x].f = y;
    update(x); update(y);
}
 
inline void splay(int x, int &y) {
    while (x != y) {
        if (z[x].f == y) {
            rotate(y, z[y].ch[1] == x);
        } else {
            bool t1 = z[z[x].f].ch[1] == x;
            bool t2 = z[z[z[x].f].f].ch[1] == z[x].f;
            if (t1 ^ t2) {
                rotate(z[x].f, t1); rotate(z[x].f, t2);
            } else {
                rotate(z[z[x].f].f, t2); rotate(z[x].f, t1);
            }
        }
    }
}
 
inline int ask(int d){
    int p = st[top--];
    z[p].size = 1; z[p].rev = z[p].cov = false;
    z[p].sum = z[p].maxn = z[p].maxl = z[p].maxr = z[p].data = d;
    z[p].ch[0] = z[p].ch[1] = z[p].del = 0;
    return p;
}
 
inline int find(int x, int y) {
    if (z[x].cov || z[x].rev) downtag(x);
    if (z[z[x].ch[0]].size + 1 == y) return x; else
    if (z[z[x].ch[0]].size >= y) return find(z[x].ch[0], y);
    else return find(z[x].ch[1], y-z[z[x].ch[0]].size-1);
}
 
inline void insert(int p, int n) {
    x = find(*rt, p  ); splay(x, *rt);
    y = find(*rt, p+1); splay(y, z[*rt].ch[1]);
    la = 0; fir = 0;
    for (int i = n-1; i >= 0; i--) {
        k = ask(a[i]);
        if (la) {z[la].f = k; z[k].ch[1] = la; /*update(k);*/}
        la = k; if (!fir) fir = k;
    }
    z[y].ch[0] = k; z[k].f = y;
    splay(fir, *rt);
}
 
void dispose(int x) {
    st[++top] = x;
    if (z[x].ch[0]) dispose(z[x].ch[0]);
    if (z[x].ch[1]) dispose(z[x].ch[1]);
}
 
inline void remove(int p, int n) {
    x = find(*rt, p-1); splay(x, *rt);
    y = find(*rt, p+n); splay(y, z[*rt].ch[1]);
    dispose(z[y].ch[0]); z[y].ch[0] = 0;
    update(y); update(x);
}
 
inline int get_sum(int p, int n) {
    x = find(*rt, p-1); splay(x, *rt);
    y = find(*rt, p+n); splay(y, z[x].ch[1]);
    return z[z[y].ch[0]].sum;
}
 
inline void reverse(int p, int n) {
    x = find(*rt, p-1); splay(x, *rt);
    y = find(*rt, p+n); splay(y, z[x].ch[1]);
    _rev(z[y].ch[0]); update(y); update(x);
}
 
inline void make_same(int p, int n, int c) {
    x = find(*rt, p-1); splay(x, *rt);
    y = find(*rt, p+n); splay(y, z[x].ch[1]);
    _cov(z[y].ch[0], c); update(y); update(x);
}
 
inline int get_maxn(){
    splay(1, *rt);
    splay(2, z[1].ch[1]);
    return z[z[2].ch[0]].maxn;
};
 
int main(){
    //freopen("sequence.in" , "r", stdin );
    //freopen("sequence.out", "w", stdout);
    top = 0; memset(z, 0, sizeof(z));
    for (int i = N-1; i > 0; --i) st[++top] = i;
    rt = &z[0].ch[1]; *rt = ask(0); z[1].size++;
    z[1].ch[1] = ask(0); z[2].f = *rt;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    while (c!='\n') c = getchar(); insert(1, n);
    while (m--) {
        c = getchar();
        switch (c){
            case 'I':
                while (c != ' ') c = getchar();
                scanf("%d%d", &p, &n);
                for (int i = 0; i < n; i++) scanf("%d", &a[i]);
                insert(++p, n);
                break;
            case 'G':
                while (c != ' ') c = getchar();
                scanf("%d%d", &p, &n);
                printf("%d\n", get_sum(++p, n));
                break;
            case 'D':
                while (c != ' ') c = getchar();
                scanf("%d%d", &p, &n);
                remove(++p, n);
                break;
            case 'R':
                while (c != ' ') c = getchar();
                scanf("%d%d", &p, &n);
                reverse(++p, n);
                break;
            default:
                c = getchar();
                c = getchar();
                if (c == 'X')
                    printf("%d\n", get_maxn());
                else {
                    while (c != ' ') c = getchar();
                    scanf("%d%d%d", &p, &n, &k);
                    make_same(++p, n, k);
                }
        }
        while (c!='\n') c = getchar();
    }
    return 0;
}