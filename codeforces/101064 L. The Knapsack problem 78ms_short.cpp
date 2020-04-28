#include<bits/stdc++.h>
using namespace std;
#define N 1005
int w[N],I[N],n,W,u,i,j;int64_t f[N*N],c[N],t;
int cmp(int i,int j){return c[i]*w[j]>c[j]*w[i];}
int main(){
	scanf("%d%d",&n,&W);
	while(j<n)scanf("%d%I64d",w+j,c+j),I[j]=j,u=max(u,w[j++]);
	sort(I,I+n,cmp);
	while(i<W&&i++<u*u)
		for(j=0;j<3*u*u/i&&j<n;++j)if(w[t=I[j]]<=i)f[i]=max(f[i],f[i-w[t]]+c[t]);
	t=max(0,(W-u*u)/w[*I]+1);
	cout<<f[W-t*w[*I]]+t*c[*I]<<endl;
}