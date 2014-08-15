const LL mod = 998244353LL; 
const LL e = 3;
inline void dft(LL out[], int n, int oper) {
	for (int i = 1, j = 0; i < n - 1; i++) {
		for (int s = n; j ^= s >>= 1, ~j & s;);  
		if (i < j) {
			swap(out[i], out[j]);
		}
	}
	for (int d = 0;(1<<d) < n;d++) {
		int m = 1<<d, m2 = m << 1;
		LL u0 = qpow(e, (mod-1)/m2);
		u0 = qpow(u0, (mod-1+oper)%(mod-1));
		for (int i = 0;i < n;i += m2) {
			LL u = 1;
			for (int j = i;j < i + m;j++) {
				LL p1 = out[j] + (u*out[j+m])%mod; if (p1 >= mod)p1 -= mod;
				LL p2 = out[j] - (u*out[j+m])%mod; if (p2 < 0)   p2 += mod;
				out[j] = p1;
				out[j+m] = p2;
				u = (u * u0) % mod;
			}
		}
	}
}
inline void conv(LL a[], LL b[], LL c[], int n) {
	static LL _a[maxn], _b[maxn], _c[maxn];
	for (int i = 0;i < n;i++) {
		_a[i] = a[i];
		_b[i] = b[i];
	}
	dft(_a, n, 1);
	dft(_b, n, 1);
	for (int i = 0;i < n;i++) {
		_c[i] = (_a[i] * _b[i]) % mod;
	}
	dft(_c, n, -1);
	LL n1 = qpow(n, mod-2);
	for (int i = 0;i < n;i++) {
		c[i] = (_c[i] * n1) % mod;
	}
}
