// circle union (SPOJ CIRU)
inline bool isin(double m, double l, double r) {
	if (l < r) {
		return dcmp(l, m) <= 0 && dcmp(m, r) <= 0;
	} else {
		return dcmp(l, m) <= 0 || dcmp(m, r) <= 0;
	}
}

inline double cut(double x) {
	if (x > M_PI)
		return x - 2*M_PI;
	else if (x < -M_PI)
		return x + 2*M_PI;
	return x;
}

const int maxn = 1024;

Vec O[maxn]; 
double R1[maxn];
int st[maxn];
Vec P[maxn];
double R[maxn];

inline bool cmpr(const int &a, const int &b) {
	return R1[a] > R1[b];
}

int main() {
	int N;
	scanf("%d", &N);
	for (int i = 0;i < N;i++) {
		scanf("%lf%lf%lf", &O[i].x, &O[i].y, R1 + i);
	}
	for (int i = 0;i < N;i++) {
		st[i] = i;
	}
	sort(st, st + N, cmpr);
	int curr = 0;
	for (int t = 0;t < N;t++) {
		int i = st[t];
		bool flag = true ;
		if (dcmp(R1[i], 0) == 0) {
			flag = false ;
		}
		for (int k = 0;k < t;k++) {
			int j = st[k];
			double d = (O[i] - O[j]).norm();
			if (dcmp(d, R1[j] - R1[i]) <= 0) {
				flag = false ;
				break ;
			}
		}
		if (flag) {
			P[curr] = O[i];
			R[curr] = R1[i];
			curr ++;
		}
	}
	N = curr;
	double ans = 0.0;
	for (int i = 0;i < N;i++) {
		vector<double>lf, rt;
		for (int j = 0;j < N;j++) if (i != j && is_inter(P[i], R[i], P[j], R[j])) {
			pair<double, double> inter = cir_inter(P[i], R[i], P[j], R[j]);
			double l = inter.first, r = inter.second;
			Vec mid = P[j] - P[i];
			double m = atan2(mid.y, mid.x);
			if (!isin(m, l, r)) {
				swap(l, r);
			}
			if (l > r) {
				lf.push_back(l);
				rt.push_back(M_PI);
				lf.push_back(-M_PI);
				rt.push_back(r);
			} else {
				lf.push_back(l);
				rt.push_back(r);
			}
		}
		vector<double>all;
		all.push_back(-M_PI);
		all.push_back(+M_PI);
		for (int j = 0;j < (int)lf.size();j++) {
			all.push_back(lf[j]);
			all.push_back(rt[j]);
		}
		sort(all.begin(), all.end());
		for (int j = 0;j < (int)lf.size();j++) {
			lf[j] = lower_bound(all.begin(), all.end(), lf[j]) - all.begin();
			rt[j] = lower_bound(all.begin(), all.end(), rt[j]) - all.begin();
		}
		vector<int>ci(all.size());
		for (int j = 0;j < (int)lf.size();j++) {
			ci[lf[j]] ++;
			ci[rt[j]] --;
		}
		int c = 0;
		for (int j = 0;j + 1 < (int)ci.size();j++) {
			c += ci[j];
			if (c == 0) {
				double d = all[j + 1] - all[j];
				Vec l = P[i] + Vec(cos(all[j]), sin(all[j])) * R[i];
				Vec r = P[i] + Vec(cos(all[j+1]), sin(all[j+1])) * R[i];
				ans += R[i] * R[i] * (d - sin(d)) / 2.0 + l.det(r)/2.0;
			}
		}
	}
	printf("%.3f\n", ans);
	return 0;
}
