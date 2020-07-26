#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 1005
int w[N],c[N],id[N],n,W,u; ll f[N*N];
bool cmp(int i,int j){return (ll)c[i]*w[j]>(ll)c[j]*w[i];}
int main(){
	scanf("%d%d",&n,&W);
	for (int i=0;i<n;++i)scanf("%d%d",w+i,c+i),u=max(u,w[i]),id[i]=i;
	sort(id,id+n,cmp);
	for (int i=1;i<=min(W,u*u);++i)
		for (int j=0;j<min((int)ceil(3.*u*u/i),n);++j)
			if (w[id[j]]<=i)f[i]=max(f[i],f[i-w[id[j]]]+c[id[j]]);
	ll m=ceil(1.*max(0,W-u*u)/w[id[0]]);
	cout<<f[W-m*w[id[0]]]+m*c[id[0]]<<endl;
	return 0;
}