#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
#include<immintrin.h>
using namespace std;
typedef unsigned int uint;
typedef unsigned long long ull;
const int N=5040,W=32,W1=256,N1=(N+W1-1)/W1*(W1/W),L=8,K=4;
const uint mask=(1<<L)-1;
typedef uint vec[N1];
alignas(64) vec a[N],b[N],c[N],d[K][1<<L]; int I[1<<L],n;
/*void vec_or(uint *a,uint *b,uint *c,int _n=N1){
	int n=_n/2; ull *p=(ull*)a,*q1=(ull*)b,*q2=(ull*)c,*end=p+n;
	while (p!=end)*p++=*q1++|*q2++;
}*/
/*void vec_or(uint *p,uint *q,int n=N1){
	uint *end=p+n;
	while (p!=end)*p++|=*q++;
}*/
/*void vec_or(uint *a,uint *b,int _n=N1){
	int n=_n/2; ull *p=(ull*)a,*q=(ull*)b,*end=p+n;
	while (p!=end)*p++|=*q++;
}*/
/*void vec_or(uint *a,uint *b,int _n=N1){
	int n=_n/8; __m256i *p=(__m256i*)a,*q=(__m256i*)b,*end=p+n;
	while (p!=end)*p++|=*q++;
}*/
void vec_or(uint *a,uint *b,uint *c,int _n=N1){
	int n=_n/8; __m256i *p=(__m256i*)a,*q1=(__m256i*)b,*q2=(__m256i*)c,*end=p+n;
	for (;p!=end;p+=4,q1+=4,q2+=4){
		*p=*q1|*q2; *(p+1)=*(q1+1)|*(q2+1);
		*(p+2)=*(q1+2)|*(q2+2); *(p+3)=*(q1+3)|*(q2+3);
	}
}
void vec_or(uint *a,uint *b,int _n=N1){
	int n=_n/8; __m256i *p=(__m256i*)a,*q=(__m256i*)b,*end=p+n;
	for (;p!=end;p+=4,q+=4){
		*p|=*q; *(p+1)|=*(q+1);
		*(p+2)|=*(q+2); *(p+3)|=*(q+3);
	}
}
void mat_mul_bool(){
	memset(c,0,sizeof(c));
	I[1]=0; for (int i=2;i<(1<<L);++i)I[i]=(i&1)?0:I[i>>1]+1;
	for (int l=0;l<n;l+=L*K){
		for (int S=1;S<(1<<L);++S)
			for (int k=0;k<K;++k)
				vec_or(d[k][S],d[k][S-(1<<I[S])],b[L*k+l+I[S]]);
		for (int i=0;i<n;++i){
			int v[K];
			for (int k=0;k<K;++k)v[k]=(a[i][(L*k+l)/W]>>(L*k+l)%W)&mask;
			for (int k=0;k<K;++k)vec_or(c[i],d[k][v[k]]);
		}
	}
}
inline int _rand(){static unsigned int x=31253125;x+=(x<<4)+(x>>21)+1;return x&=0x7fffffff;}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	n=N;
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)
			a[i][j/W]|=_rand()%2<<j%W,b[i][j/W]|=(_rand()%(n/2)==0)<<j%W;
	int t1=clock();
	for (int i=0;i<10;++i)
	mat_mul_bool();
	printf("time=%d\n",clock()-t1);
	int s=0;
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)
			s+=((c[i][j/W]>>j%W)&1)*(i^0x12345678)*(j^0x87654321);
	printf("s=%d\n",s);
	//system("pause");for (;;);
	return 0;
}


