#include<bits/stdc++.h>
using namespace std;int64_t f[4<<20],v=1<<20,*c=f+v,*w=c+v,*I=w+v,n,W,i,l,t;
main(){
	for(cin>>n>>W;cin>>w[I[l]=l]>>c[l],++l<n;);
	for(sort(I,I+n,[](int i,int j){return c[i]*w[j]>c[j]*w[i];});n--;)
		for(i=l=w[t=I[n]];i<v&i*n<2*v;++i)f[i]=max(f[i],f[i-l]+c[t]);
	i=max(0LL,W-v+l)/l;cout<<f[W-i*l]+i*c[t];return 0;
}