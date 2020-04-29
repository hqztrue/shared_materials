#include<bits/stdc++.h>
using namespace std;int64_t w[1005],I[1005],n,W,i,j,l,f[1<<20],c[1005],t,v=1<<20;
main(){
	for(cin>>n>>W,j=n;j--;cin>>w[I[j]=j]>>c[j]);
	for(sort(I,I+n,[](int i,int j){return c[i]*w[j]>c[j]*w[i];});++i<v;)
		for(j=min(3*v/i,n);j--;f[i]=max(f[i],(l=w[t=I[j]])<=i?f[i-l]+c[t]:0));
	i=max(j,(W-v)/l)+1;cout<<f[W-i*l]+i*c[t];return 0;
}