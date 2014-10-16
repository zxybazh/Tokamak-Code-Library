/*
    Author  :   zxybazh
    Date    :   2013.1.11
    Source  :   POJ_2478
    Solution:   Euler Function [O(N]
*/
   
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define N 1111111
using namespace std;
   
int n, t;
int prime[N], eu[N];
long long sum[N];
bool f[N];
   
void makeans(){
    t = 0;
    memset(f, 0, sizeof(f));
    sum[0] = 0; sum[1] = 0;
    for (int i = 1; i < N; i++) eu[i] = 1;
    for (int i = 2; i < N; i++) {
        if (!f[i]) {
            prime[++t] = i;
            eu[i] = i - 1;
        }
        for (int j = 1; j <= t; j++) {
            if (prime[j] * i >= N) break;
            int tmp = prime[j] * i;
            f[tmp] =true;
            if (!(i % prime[j])) {
                eu[tmp] *= eu[i] * prime[j];
                break;
            }
            else
                eu[tmp] = eu[i] * (prime[j] - 1);
        }
    }
    for (int i = 2; i < N; i++)
        sum[i] = sum[i - 1] + eu[i];
}
   
int main(){
    makeans();
    scanf("%d", &n);
    while (n) {
        cout << sum[n] << endl;
        scanf("%d", &n);
    }
}