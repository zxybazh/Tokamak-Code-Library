/********************Dinic Module***************/
#define N (111*2)
#define M (N*N+2*N)

struct Dinic_node {
	int next, f, y;
};

class Dinic {
public:
	static int des, det, q[N], dist[N], nume;
	static Dinic_node z[N + M];
	static void init(int n) {
		nume = n | 1;
		kep(i, n) z[i].next = 0;
	}
	static void link(int x, int y, int f) {
		z[++nume].y = y;
		z[nume].f = f;
		z[nume].next = z[x].next;
		z[x].next = nume;
		z[++nume].y = x;
		z[nume].f = 0;
		z[nume].next = z[y].next;
		z[y].next = nume;
	}
	static void set(int x, int y) {
		des = x; det = y;
	}
	static bool level() {
		int f(0), r(0); q[f] = des;
		rep(i, N) dist[i] = -1;
		dist[des] = 0;
		while (f <= r) {
			for (int p = z[q[f]].next; p; p = z[p].next) {
				if (z[p].f > 0 && dist[z[p].y] == -1) {
					dist[z[p].y] = dist[q[f]] + 1;
					q[++r] = z[p].y;
				}
			}
			f++;
		}
		return (dist[det] != -1);
	}
	static int dinic(int x, int nowmin) {
		if (x == det) return nowmin;
		int flow = 0, tmp;
		for (int p = z[x].next; p && nowmin > flow; p = z[p].next) {
			if (z[p].f > 0 && dist[x] + 1 == dist[z[p].y]) {
				tmp = dinic(z[p].y, min(nowmin-flow, z[p].f));
				if (!tmp) {
					dist[z[p].y] = -1;
				} else {
					flow += tmp;
					z[p].f -= tmp;
					z[p^1].f += tmp;
				}
			}
		}
		return flow;
	}
	static int maxflow() {
		int flow = 0;
		while (level()) flow += dinic(des, inf);
		return flow;
	}
};

int Dinic::des, Dinic::det, Dinic::q[N], Dinic::dist[N], Dinic::nume;
Dinic_node Dinic::z[N + M];

/********************End Line*******************/
