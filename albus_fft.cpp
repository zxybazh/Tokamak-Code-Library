inline void dft(CD out[], int n, int oper) {
	for (int i = 1, j = 0; i < n - 1; i++) {
		for (int s = n; j ^= s >>= 1, ~j & s;);  
		if (i < j) {
			swap(out[i], out[j]);
		}
	}
	for (int d = 0;(1<<d) < n;d++) {
		int m = 1<<d, m2 = m << 1;
		double theta = M_PI/m * oper;
		CD u0 = CD(cos(theta), sin(theta));
		for (int i = 0;i < n;i += m2) {
			CD u = 1.0;
			for (int j = i;j < i + m;j++) {
				CD p1 = out[j] + u*out[j+m];
				CD p2 = out[j] - u*out[j+m];
				out[j] = p1;
				out[j+m] = p2;
				u *= u0;
			}
		}
	}
}
inline void conv(int a[], int b[], int c[], int n) {
	static CD _a[maxn], _b[maxn], _c[maxn];
	for (int i = 0;i < n;i++) {
		_a[i] = CD(a[i], 0);
		_b[i] = CD(b[i], 0);
	}
	dft(_a, n, 1);
	dft(_b, n, 1);
	for (int i = 0;i < n;i++) {
		_c[i] = _a[i] * _b[i];
	}
	dft(_c, n, -1);
	for (int i = 0;i < n;i++) {
		c[i] = (int)(_c[i].real()/n + .5);
	}
}
