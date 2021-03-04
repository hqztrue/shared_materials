#import<bits/stdc++.h>
using namespace std;int64_t f[4<<20],v=1e6,*c=f+v,*w=c+v,*I=w+v,n,W,i,l,t;
main(){
	for(cin>>n>>W;cin>>w[I[l]=l]>>c[l],++l<n;);
	for(sort(I,I+n,[](int i,int j){return c[i]*w[j]>c[j]*w[i];});n--;)
		for(i=l=w[t=I[n]];i<v&i*n<4*v;)f[i]=max(f[i++],f[i-l]+c[t]);
	i=W<v?0:(W-v)/l+1;cout<<f[W-i*l]+i*c[t];
}