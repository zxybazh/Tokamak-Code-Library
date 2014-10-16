#include <map>
#include <cmath>
#include <ctime>
#include <queue>
#include <string>
#include <bitset>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;
#define N 111111
#define fir first
#define sec second
typedef long long LL;
typedef pair<LL, LL> spn;
#define fo(i, l, r) for (LL i = l; i <= r; ++i)
#define re(i, l, r) for (LL i = l; i <  r; ++i)
    
int _ = 0, testcase;
LL n, k, m, p;
int prime[N];
bool pp[N];
    
void makeprime(){
    memset(pp, 0, sizeof(pp));
    p = 0;
    re(i, 2, N){
        if (!pp[i]) prime[p++] = i;
        re(j, 0, p){
            if (prime[j] * i  < N)
                pp[prime[j] * i]=true;
            else break;
            if (!(i % prime[j])) break;
        }
    }
}
    
LL make(LL n){
    if (n < 2) return n ^ 1;
    LL pre = 1;
    LL now = 0;
    LL ans = (n & 1)? -1: 1;
    LL l =  max((LL)3, n - m);
    LL i, j;
    for (i = n, j = 1; i >= l; i--, j++){
        now = (pre * (LL)i) % m; pre = now;
        ans =(ans+(now*((-i&1) ?1:-1))) % m;
    }
    ans = (ans + m) % m;
    return ans;
}
    
void ex_gcc(LL a, LL b, LL &x, LL &y){
    if (!b){
        x = 1;
        y = 0;
    } else{
        ex_gcc(b, a % b, y, x);
        y = y - a / b * x;
    }
}
    
LL Inv(LL a, LL b){
    LL c, d;
    ex_gcc(a, b, c, d);
    return c;
}
    
LL Pow(LL a, LL p, LL mo){
    LL ans = 1;
    for(; p; p >>= 1, a = a * a % mo){
        if (p & 1) ans = ans * a % mo;
    }
    return ans;
}
    
spn cal(LL n, LL mp, LL pr){
    spn ans;
    if (n < pr){
        ans.sec = 0;
        ans.fir = 1;
        fo(i, 2, n) ans.fir = ans.fir * i % mp;
    } else{
        spn tmp;
        tmp = cal(n / pr, mp, pr);
        ans.sec = n / pr + tmp.sec;
        ans.fir = 1;
        if (n <= mp){
            fo(i, 2, n)
                if (i % pr)
                    ans.fir = ans.fir * i % mp;
        } else{
            fo(i, 2, mp)
                if (i % pr)
                ans.fir = ans.fir * i % mp;
            ans.fir = Pow(ans.fir, n / mp, mp);
            fo(i, n - n % mp + 1, n)
                if (i % pr)
                    ans.fir = ans.fir * i % mp;
        }
        ans.fir = ans.fir * tmp.fir % mp;
    }
    return ans;
}
    
LL work(LL n, LL k, LL mp, LL pr){
    LL ans = 1;
    spn tmp[3];
    tmp[0] = cal(n, mp, pr);
    tmp[1] = cal(k, mp, pr);
    tmp[2] = cal(n - k, mp, pr);
    ans = ans * tmp[0].fir % mp;
    ans = ans * Inv(tmp[1].fir, mp) %mp;
    ans = ans * Inv(tmp[2].fir, mp) %mp;
    ans = ans * Pow(pr, tmp[0].sec - tmp[1].sec
	- tmp[2].sec, mp) % mp;
    return ans;
}
    
LL c(LL n, LL k, LL m){
    LL ans, sigp, tmp = 0, maxn = 0, mm = m;
    re(i, 0, p)
        if (!(mm % prime[i])) {
            sigp = 1;
            do {
                sigp *= prime[i];
                mm /= prime[i];
            } while (!(mm % prime[i]));
            ans = work(n, k, sigp, prime[i]);
            maxn = max(maxn, ans);
            tmp = (tmp + (m / sigp * ans % m *
		Inv(m / sigp, sigp) % m)) % m;
        }
        else if (mm == 1) break;
    while (tmp < maxn) tmp += m;
    return tmp;
}
    
LL calc(){
    LL ans = make(n - k);
    ans = ans * c(n, k, m) % m;
    return ans;
}
    
int main(){
    makeprime();
    scanf("%d", &testcase);
    while (testcase--){
        cin >> n >> k >> m;
        printf("Case %d: ", ++_);
        cout << calc() <<endl;
    }
    return 0;
}
