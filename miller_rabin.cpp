/*
    Author  :   zxybazh
    Date    :   2013.1.6
    Source  :   Fzu_1649
    Solution:   Miller_Rabin
*/
    
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#define LL long long
using namespace std;
    
const LL a[10] = {2, 3, 5, 7, 11, 13, 17, 53, 61, 24251};
//exceptation:46 856 248 255 981
    
LL mul(LL a, LL b, LL p){
    a %= p;
    b %= p;
    LL c = (double) a * (double) b / (double) p;
    return (a * b  + p - c * p) % p;
}
    
LL POW(LL a, LL c, LL p){
    LL ans = 1;
    for (a %= p; c; c /= 2, a = mul(a, a, p))
        if (c & 1) ans = mul(ans, a, p);
    return ans;
}
    
bool MR(LL a, LL p){
    LL d = p - 1;
    while (!(d & 1)) d /= 2;
    LL t = POW(a, d, p);
    while (d != p - 1 && t != 1 && t != p -1){
        t= mul(t, t, p);
        d *= 2;
    }
    return (t == p - 1) || (d & 1);
}
    
bool Miller_Rabin(LL x){
    if (x == 2) return true;
    if (x == 1 || !(x % 2)) return false;
    for(LL i = 0; i < 10; i++)
        if ((a[i] < x) && (!MR(a[i], x))) return false;
    return true;
}
    
LL x;
/*
bool check(LL x){
    if (x == 2) return true;
    if (x == 1) return false;
    if (!(x % 2)) return false;
    int n = sqrt(x);
    for (int i = 2; i <= n; i++)
        if (!(x % i)) return false;
    return true;
}
*/
int main(){
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    while (scanf("%I64d", &x) != EOF){
        if (Miller_Rabin(x))
            printf("It is a prime number.\n");
        else
            printf("It is not a prime number.\n");
    }
    return 0;
}
