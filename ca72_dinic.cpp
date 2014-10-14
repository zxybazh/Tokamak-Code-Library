#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
 
const int INF = 0x7f7f7f7f;
const long long LINF = 0x7f7f7f7f7f7f7f7fLL;
template < typename T, int maxN >
class Queue
{
private:
    T p[maxN]; int head, tail;
public:
    inline Queue() { clear(); }
    inline void clear() { head = tail = 0; }
    inline void push(const T& in) { p[tail] = in; if (++tail == maxN) tail = 0; }
    inline void pop() { if (++head == maxN) head = 0; }
    inline T& front() { return p[head]; }
    inline bool isEmpty() { return head == tail; }
};
 
const int MAXV = 200011, MAXE = MAXV * 2;
struct Arc
{
    int dest, rest; Arc *next, *rev;
    inline Arc() { next = NULL; }
    inline Arc(int _dest, int _rest, Arc *_next)
    { dest = _dest, rest = _rest, next = _next; }
}*adj[MAXV], Npool[MAXE], *Nptr; int S, T;
 
inline void insert(int start, int finish, int cap)
{
    adj[start] = new Arc(finish, cap, adj[start]);
    adj[finish] = new Arc(start, cap, adj[finish]); //directed
    adj[start]->rev = adj[finish];
    adj[finish]->rev = adj[start];
}
 
Queue < int, MAXV > q; int dis[MAXV]; bool v[MAXV];
inline bool bfs()
{
    memset(v, 0, sizeof(v));
    memset(dis, 0, sizeof(dis)); q.clear();
    dis[S] = 1; q.push(S);
    while (!q.isEmpty())
    {
        int id = q.front(); q.pop();
        for (Arc *p = adj[id]; p; p = p->next)
            if (p->rest > 0 && dis[p->dest] == 0)
            {
                dis[p->dest] = dis[id] + 1;
                if (p->dest == T)
                    return true;
                q.push(p->dest);
            }
    }
    return false;
}
 
inline long long aug(int i, long long m)
{
    if (i == T)
        return m;
     
    long long ret = 0;
    for (Arc *p = adj[i]; p; p = p->next)
        if (p->rest > 0 && v[p->dest] == false && dis[p->dest] == dis[i] + 1)
            if (int a = aug(p->dest, min((long long)(p->rest), m - ret)))
            {
                p->rest -= a;
                p->rev->rest += a;
                ret += a;
                if (m == ret)
                    return ret;
            }
    v[i] = true;
    return ret;
}
 
inline long long maxflow()
{
    long long ret = 0;
    while (bfs())
        ret += aug(S, LINF);
    return ret;
}
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w" ,stdout);
#endif
 
    int Testcase;
    scanf("%d", &Testcase);
     
    for (int testcase = 1; testcase <= Testcase; testcase++)
    {
        memset(adj, 0, sizeof(adj));
        Nptr = Npool;
         
        int Ml = INF, Mr = -INF, V, E;
         
        scanf("%d%d", &V, &E);
        for (int i = 1; i <= V; i++)
        {
            int x;
            scanf("%d%*d", &x);
            if (x < Ml) { Ml = x; S = i; }
            if (x > Mr) { Mr = x; T = i; }
        }
         
        for (int i = 1; i <= E; i++)
        {
            int s, t, c;
            scanf("%d%d%d", &s, &t, &c);
            insert(s, t, c);
        }
         
        long long ans = maxflow();
        cout << ans << "\n";
    }
    return 0;
}
