#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
#define rep(i, n) for (int i = 0; i < n; i++)
#define kep(i, n) for (int i = 1; i <=n; i++)
#define OPT(p) p->opt

#define NMax 1010

int N, nume;

struct edge{
    int e, f;
    edge *next, *opt;
} z[1001010], *E[1010];

int SAP(){
    static int d[NMax],g[NMax+1],Q[NMax];
    static edge *c[NMax],*pre[NMax];
    int ret=0,x=0,bot;
    for (int i=0;i<N;i++)c[i]=E[i],d[i]=N,g[i]=0;
    d[N-1]=0;
    pre[g[N]=0]=NULL;
    Q[(bot=1)-1]=N-1;
    for (int i=0;i<bot;i++)for (edge *p=E[Q[i]];p;p=p->next)
        if (OPT(p)->f && p->e!=N-1 && d[p->e]==N)d[Q[bot++]=p->e]=d[Q[i]]+1;
    for (int i=0;i<N;i++)g[d[i]]++;
    while (d[0]<N){
        while (c[x] && (!c[x]->f || d[c[x]->e]+1!=d[x]))c[x]=c[x]->next;
        if (c[x]){
            pre[c[x]->e]=OPT(c[x]);
            x=c[x]->e;
            if (x==N-1){
                int t=~0u>>1;
                for (edge *p=pre[N-1];p;p=pre[p->e])if (t>OPT(p)->f)t=OPT(p)->f;
                for (edge *p=pre[N-1];p;p=pre[p->e])
                    p->f+=t,OPT(p)->f-=t;
                ret+=t;
                x=0;
            }
        }else{
            int od=d[x];
            g[d[x]]--; d[x]=N;
            for (edge *p=c[x]=E[x];p;p=p->next)if (p->f && d[x]>d[p->e]+1)d[x]=d[p->e]+1;
            g[d[x]]++;
            if (x)x=pre[x]->e;
            if (!g[od])break;
        }
    }
    return ret;
}

void link(int x, int y, int f) {
    z[++nume].e = y;
    z[nume].f = f;
    z[nume].next = E[x];
    z[nume].opt = &z[nume+1];
    E[x] = &z[nume];
    z[++nume].e = x;
    z[nume].f = 0;
    z[nume].next = E[y];
    z[nume].opt = &z[nume-1];
    E[y] = &z[nume];
}

int n, m, k, sumx[1010], sumy[1010], totx, toty, a[1010][1010];
edge *w[444][444], *ins[1010];
bool v[1010];

bool dfs(int x, int l) {
    v[x] = true;
    for (edge *p = E[x]; p; p = p->next) if (p->f && ins[x] != OPT(p)) {
        if (ins[p->e] && l >= 1) {
            return true;
        } else if (!ins[p->e]) {
            ins[p->e] = p; p->f = 0;
            if (dfs(p->e, l+1)) return true;
            ins[p->e] = NULL;
        }
    }
    return false;
}

int main() {
    //freopen("B.in", "r", stdin);
    while (scanf("%d%d%d", &n, &m, &k) != EOF) {
        N = n+m+2; nume = 0;
        rep(i, N) E[i] = NULL;
        kep(i, n) {
            scanf("%d", &sumx[i]);
            link(0, i, sumx[i]);
        }
        kep(i, m) {
            scanf("%d", &sumy[i]);
            link(n+i, n+m+1, sumy[i]);
        }
        kep(i, n) kep(j, m) {
            w[i][j] = &z[nume+1];
            link(i, n+j, k);
        }
        int tans = SAP();
        totx = toty = 0;
        kep(i, n) totx += sumx[i];
        kep(i, m) toty += sumy[i];
        if (totx != toty || totx != tans) {
            puts("Impossible"); continue;
        }
        kep(i, n) kep(j, m) a[i][j] =  k-w[i][j]->f;
        bool flag = false;
        rep(i, N) v[i] = false;
        rep(i, N) if (!v[i]){
            ins[i] = &z[0];
            if (dfs(i, 0)) {
                puts("Not Unique");
                flag = true;
                break;
            }
            ins[i] = NULL;
        }
        rep(i, N) ins[i] = NULL;
        if (flag) continue;
        puts("Unique");
        kep(i, n) {
            kep(j, m) {
                printf("%d", a[i][j]);
                j == m ? printf("\n") : printf(" ");;
            }
        }
    }
}