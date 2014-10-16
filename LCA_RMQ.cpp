/*****LCA-RMQ**************************************/
/***1.Plz set the E & V number*********************/
/***2.Plz LCA_RMQ::all the arrays******************/
/***3.DFS(1,0,0) would be suitable*****************/
/***4.Plz include <cmath> to use log***************/
/***5.Plz follow: init->dfs->make->ques************/
/***6.DIY is required******************************/

struct Edge_Node {int y, next;};

#define E 101010
#define V 101010

class LCA_RMQ {
    private:
        static int dfn[V*2], pos[V], dep[V*2], f[V*2][30];
        static int edge_num, vnum, c2[33];
        static Edge_Node e[V+E];
        static int calc_min(int p, int q) {
            return dep[pos[p]] < dep[pos[q]] ? p : q;
        }
    public:
        static void init(int n) {
            edge_num = n | 1; vnum = 0;
            kep(i, edge_num) e[i].next = 0;
            c2[0] = 1; kep(i, 30) c2[i] = c2[i-1]*2;
        }
        static void link(int x, int y) {
            edge_num++; e[edge_num].y = y;
            e[edge_num].next = e[x].next; e[x].next = edge_num;
            edge_num++; e[edge_num].y = x;
            e[edge_num].next = e[y].next; e[y].next = edge_num;
        }
        static void dfs(int x, int la, int depth) {
            dfn[++vnum] = x; pos[x] = vnum; dep[vnum] = depth;
            for (int p = e[x].next; p; p = e[p].next) {
                if (e[p].y == la) continue;
                dfs(e[p].y, x, depth+1);
                dfn[++vnum] = x; dep[vnum] = depth;
            }
        }
        static void make(int n) {
            kep(i, n*2-1) f[i][0] = dfn[i];
            kep(j, 20) kep(i, n*2-1) if (i+c2[j] <= n*2)
                f[i][j] = calc_min(f[i][j-1], f[i+c2[j-1]][j-1]);
        }
        static int ques(int p, int q) {
            p = pos[p], q = pos[q]; if (p > q) swap(p, q);
            int k = (int)log2(q-p+1);
            return calc_min(f[p][k], f[q-c2[k]+1][k]);
        }
};

int LCA_RMQ::dfn[V*2], LCA_RMQ::pos[V],
    LCA_RMQ::dep[V*2], LCA_RMQ::f[V*2][30];
int LCA_RMQ::edge_num, LCA_RMQ::vnum, LCA_RMQ::c2[33];
Edge_Node LCA_RMQ::e[V+E];

/*****End Line Of LCA_RMQ by zxybazh****************/
