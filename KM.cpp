/***************** KM Module ********************/

typedef int LD;

#define N 222

const int inf = 0x7fffffff/2;

class KM {
private:
	static int f, r, n, d, pre[N], pax[N], pay[N], Q[N*2];
	static LD slack[N], lx[N], ly[N], z[N][N];
	static bool vx[N], vy[N];
public:
	static void init(int);
	static void link(int, int, LD);
	static pair<bool, LD> getans();
	static void augment(int);
	static bool BFS();
};

void KM::init(int tn) {
	n = tn; memset(z, 0, sizeof(z));
	memset(pax, 0, sizeof(pax));
	memset(pay, 0, sizeof(pay));
	kep(i, n) {lx[i] = -inf; ly[i] = 0;}
}

void KM::link(int x, int y, LD c) {
    if (c < z[x][y]) return;
	z[x][y] = c; lx[x] = max(c, lx[x]);
}

bool KM::BFS() {
	int p, u;
	while (f <= r) {
		p = Q[f++], u = p >> 1;
		if (p & 1) {
			if (!pay[u]) {augment(u); return true;}
			else {vx[pay[u]] = true; Q[++r] = pay[u] << 1;}
		} else {
			kep(i, n) if (z[u][i]) {
				if (vy[i]) continue;
				else if (lx[u] + ly[i] != z[u][i]) {
					p = lx[u] + ly[i] - z[u][i];
					if (slack[i] > p) {slack[i] = p; pre[i] = u;}
				} else {
					vy[i] = true; pre[i] = u;
					Q[++r] = (i << 1) | 1;
				}
			}
		}
	}
	return false;
}

void KM::augment(int u) {
	int prev; while (u) {
		prev = pax[pre[u]]; pay[u] = pre[u];
		pax[pre[u]] = u; u = prev;
	}
}

pair<bool, LD> KM::getans() {
    pair<bool, LD> tmp;
	bool aug = true;
	kep(tk, n) {
		if (aug) {
		    memset(vx, 0, sizeof(vx));
            memset(vy, 0, sizeof(vy));
            kep(i, n) slack[i] = inf;
            Q[f = r = 1] = tk<<1; vx[tk] = true;
		}
		if (BFS()) {aug = true; continue;}
		int ex = inf; tk--; aug = false;
		kep(i, n) if (!vy[i]) ex = min(slack[i], ex);
		if (ex == inf) {tmp.first = false; return tmp;}
		kep(i, n) {
			if (vx[i]) lx[i] -= ex;
			if (vy[i]) ly[i] += ex;
			slack[i] -= ex;
		}
		kep(i, n)
			if (!vy[i] && slack[i] == 0) {
				vy[i] = true; Q[++r] = (i << 1)|1;
			}
	}
    tmp.first = false;
	kep(i, n) if (pay[pax[i]] != i) return tmp;
    tmp.first = true;
    int cost = 0; kep(i, n) cost += z[i][pax[i]];
    tmp.second = cost;
    return tmp;
}

int KM::n, KM::d, KM::pre[N], KM::pax[N];
int KM::f, KM::r, KM::pay[N], KM::Q[N*2];
LD KM::slack[N], KM::lx[N], KM::ly[N], KM::z[N][N];
bool KM::vx[N], KM::vy[N];

/***************** End Line Of KM ***************/
