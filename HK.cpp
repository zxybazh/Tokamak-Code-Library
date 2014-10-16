/*******************HK Module*********************/

#define N 50100*2
#define M 150500*2

const int inf = 1073741823;

struct node {
    int y, next;
};

class HK {
public:
    static node z[M+N];
    static int nume, n, m, ans, Q[N], mat[N], dist[N];
    static void init(int n) {
        for (int i = 0; i <= n; i++) z[i].next = 0; nume = n;
    }
    static bool BFS() {
        int f(1), r(0), v;
        kep(i, n) if (mat[i]) dist[i] = inf; else {
            dist[i] = 0; Q[++r] = i;
        }
        dist[0] = inf;
        while (f <= r) {
            v = Q[f++];
            if (dist[v] < dist[0]) {
                for (int p = z[v].next; p; p = z[p].next) {
                    if (dist[mat[z[p].y]] == inf) {
                        dist[mat[z[p].y]] = dist[v] + 1;
                        Q[++r] = mat[z[p].y];
                    }
                }
            }
        }
        return dist[0] != inf;
    }
    static bool dfs(int x) {
        if (!x) return true;
        for (int p = z[x].next; p; p = z[p].next)
            if (dist[mat[z[p].y]] == dist[x] + 1 && dfs(mat[z[p].y])) {
                mat[z[p].y] = x; mat[x] = z[p].y; return true;
            }
        dist[x] = inf; return false;
    }
    static void link(int x, int y) {
        z[++nume].y = y; z[nume].next = z[x].next; z[x].next = nume;
    }
    static void set(int tn, int tm) {
        n = tn; m = tm;
    }
    static int getans() {
        memset(mat, 0, sizeof(mat)); ans = 0;
        while (BFS()) kep(i, n) if (!mat[i]) ans += dfs(i);
        return ans;
    }
};

node HK::z[M+N];
int HK::nume, HK::n, HK::m, HK::Q[N], HK::mat[N], HK::ans, HK::dist[N];

/*******************End Of Module*****************/
