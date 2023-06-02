#define private public
#include<bitset>
#undef private
#include<bits/stdc++.h>
using namespace std;
const int N=5005,L=8;
int n;
struct Matrix{
	bitset<N> a[N];
	inline void clear(){for (int i=0;i<n;++i)a[i].reset();}
	const Matrix& operator *(const Matrix &b)const{
		assert(sizeof(std::_Base_bitset<1>::_WordT)==4);
		assert(32%L==0);
		static Matrix c; c.clear();
		static bitset<N> d[1<<L];
		static int I[1<<L]; I[1]=0;
		for (int i=2;i<(1<<L);++i)I[i]=(i&1)?0:I[i>>1]+1;
		for (int l=0;l<n;l+=L){
			int r=min(l+L,n);
			for (int S=1;S<(1<<L);++S)
				d[S]=d[S-(1<<I[S])]|b.a[l+I[S]];
			for (int i=0,v;i<n;++i){
				v=(a[i]._M_w[l>>5]>>(l&31))&((1<<r-l)-1);
				c.a[i]|=d[v];
			}
		}
		return c;
	}
};
Matrix A,B,C;
inline int _rand(){static unsigned int x=31253125;x+=(x<<4)+(x>>21)+1;return x&=0x7fffffff;}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	n=N;
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)
			A.a[i].set(j,_rand()%2),B.a[i].set(j,_rand()%(n/2)==0);
	int t1=clock();
	//for (int i=0;i<10;++i)
	C=A*B;
	printf("time=%d\n",clock()-t1);
	int s=0;
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)
			s+=C.a[i][j]*(i^0x12345678)*(j^0x87654321);
	printf("s=%d\n",s);
	//system("pause");for (;;);
	return 0;
}

