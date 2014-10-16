//Sigma(N/b[i] *a[i] *Inverse(N/b[i], b[i]))% N
//N = b[1]*b[2]*b[3]...*b[n]
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define fo(i, l, r) for (int i = l; i <= r; i++)
#define LL long long
using namespace std;
     
int n;
LL ans, N, maxn;
LL a[11], b[11];
     
void ext_gcc(LL a, LL b, LL &x, LL &y){
    if (b == 0){
        x = 1;
        y = 0;
    } else{
        ext_gcc(b, a % b, y, x);
        y = y - a / b * x;
    }
}
     
LL inv(LL a, LL b){
    LL tmp, k;
    ext_gcc(a, b, tmp, k);
    return tmp;
}
     
int main(){
    while (cin >> n){
        N = 1;
        maxn = 0;
        fo(i, 1, n){
            cin >> a[i] >> b[i];
            N *= a[i];
            maxn = max(maxn, b[i]);
        }
        ans = 0;
        fo(i, 1, n)
            ans = (ans + N/a[i] * b[i] % N *
					inv(N/a[i], a[i]) % N) % N;
        while (ans < maxn) ans += N;
        cout << ans << endl;
    }
    return 0;
}
