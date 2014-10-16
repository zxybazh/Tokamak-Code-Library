/*************** Ac Automation Module ************/

#define alpha 26
#define N 505050
#define M 1111111

char buf[M];
int buflen;

struct acnode {
    int ch[alpha], fa, count;
	void clear() {
		memset(ch, 0, sizeof(ch)); fa = count = 0;
	}
};

class AcATM {
public:
	static acnode z[N];
	static int nume, Q[N], f, r;
	static void init() {nume = 1; z[1].clear(); z[1].fa = 1;}
	static void insert();
	static void BuildFail();
	static void match();
};

void AcATM::BuildFail() {
	Q[r=1] = 1; f = 0; int p = 0;
	while (++f <= r) {
		rep(i, alpha) {
			if (z[Q[f]].ch[i]) {
				p = z[Q[f]].fa;
				while (p != 1 && z[p].ch[i] == 0) p = z[p].fa;
				if (z[p].ch[i] && z[p].ch[i] != z[Q[f]].ch[i])
					z[z[Q[f]].ch[i]].fa = z[p].ch[i];
				else z[z[Q[f]].ch[i]].fa = 1;
				Q[++r] = z[Q[f]].ch[i];
			}
		}
	}
}

void AcATM::insert() {
	int p(1), x(0);
	while (x < buflen) {
		if (z[p].ch[buf[x]]) p = z[p].ch[buf[x]];
		else {
			z[z[p].ch[buf[x]] = ++nume].clear();
			p = nume;
		}
		x++;
	}
	z[p].count++;
}

void AcATM::match() {
	int tmp, x(0), p(1);
	while (x < buflen) {
		while (p != 1 && !z[p].ch[buf[x]]) p = z[p].fa;
		p = z[p].ch[buf[x]]; if (!p) p = 1; tmp = p;
		while (tmp != 1 && z[tmp].count != -1) {
			Ans += z[tmp].count;
			z[tmp].count = -1;
			tmp = z[tmp].fa;
		}
		x++;
	}
}

acnode AcATM::z[N];
int AcATM::nume, AcATM::Q[N], AcATM::f, AcATM::r;

/*************** End Line Of Module***************/
