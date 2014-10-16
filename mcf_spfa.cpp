/************MCF module with SPFA**************/

typedef int LD;
const LD inf = 1073741823;

struct mcf_node {
	int y, next, f;
	LD c;
};

#define N 4040
#define M 6*N
#define MM N*100

class min_cost_flow_spfa {
public:
	static mcf_node z[M*2+N];
	static int pre[N], fro[N], Q[MM], vis[N];
	static int des, nume, det, sumflow;
	static LD dist[N], ans;
	static void init(int n) {
		rep(i, n+1) z[i].next = 0;
		nume = n | 1;
	}
	static void link(int x, int y, int f, LD c) {
		z[++nume].y =y;
		z[nume].f = f;
		z[nume].c = c;
		z[nume].next = z[x].next;
		z[x].next = nume;
		z[++nume].y = x;
		z[nume].f = 0;
		z[nume].c = -c;
		z[nume].next = z[y].next;
		z[y].next = nume;
	}
	static void fill(LD x[], LD y) {rep(i, N) dist[i] = y;}
	static void set(int x, int y) {des = x; det = y;}
	static bool unequal(LD x, LD y) {return x != y;}
	static bool spfa() {
		fill(dist, inf);
		memset(vis, 0, sizeof(vis));
		vis[des] = 1;
		dist[des] = 0;
		Q[1] = des;
		int k, t, f(1), r(1);
		while (f <= r) {
			k = Q[f++]; vis[k] = 0;
			for (int p = z[k].next; p; p = z[p].next) {
				t = z[p].y;
				if (z[p].f && dist[k] + z[p].c < dist[t]) {
					dist[t] = dist[k] + z[p].c;
					if (!vis[t]) {Q[++r] = t; vis[t] = r;}
					if (dist[t] < dist[Q[f]]) {
						vis[Q[f]] = vis[t];
						swap(Q[f], Q[vis[t]]);
						vis[t] = f;
					}
					fro[t] = k; pre[t] = p;
				}
			}
		}
		return unequal(dist[det], inf);
	}
	static void aug() {
		int flow = inf;
		for (int k = det; k != des; k = fro[k])
			flow = min(flow, z[pre[k]].f);
		sumflow += flow;
		for (int k = det; k != des; k = fro[k]) {
			ans += flow * z[pre[k]].c;
			z[pre[k]].f -= flow;
			z[pre[k]^1].f += flow;
		}
	}
	static LD mcf() {
		sumflow = 0; ans = 0; while (spfa()) aug();
		return ans;
	}
};

int min_cost_flow_spfa::des, min_cost_flow_spfa::det;
int min_cost_flow_spfa::nume, min_cost_flow_spfa::pre[N];
int min_cost_flow_spfa::fro[N], min_cost_flow_spfa::Q[MM];
LD min_cost_flow_spfa::dist[N], min_cost_flow_spfa::ans;
mcf_node min_cost_flow_spfa::z[M*2+N];
int min_cost_flow_spfa::vis[N], min_cost_flow_spfa::sumflow;

/************End Of MCF moduel*****************/
