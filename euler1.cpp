#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<cmath>
#define LL  long long
#define MOD 1000000007
#define eps 1e-6
#define N 100010
#define zero(a)  fabs(a)<eps
using namespace std;
LL eular[N];
int prime[N][15],cnt[N];
void Prime(){
	for(int i=2;i<N;i++){
		if(eular[i]==i){
			eular[i]=i-1;
			for(int j=2;j*i<N;j++){
				eular[i*j]=eular[i*j]*(i-1)/i;
				prime[j*i][cnt[j*i]++]=i;
			}
		}
		eular[i]+=eular[i-1];
	}
}
void Init(){
	for(int i=1;i<N;i++)
		eular[i]=i;
	memset(cnt,0,sizeof(cnt));
	Prime();
}
LL dfs(int idx,int cur,int now){
	LL ret=0;
	for(int i=idx;i<cnt[now];i++)
		ret+=cur/prime[now][i]-dfs(i+1,cur/prime[now][i],now);
	return ret;
}
int main(){
	int t,cas=0;
	Init();
	scanf("%d",&t);
	while(t--){
		int a,b,c,d,k,l,r;
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		if(k==0){
            printf("Case %d: 0\n",++cas);
            continue;
        }
		l=b/k;
		r=d/k;
		if(l>r)
			swap(l,r);
		LL ans=eular[l];
		for(int i=l+1;i<=r;i++)
			ans+=l-dfs(0,l,i);
		printf("Case %d: %I64d\n",++cas,ans);
	}
	return 0;
}
