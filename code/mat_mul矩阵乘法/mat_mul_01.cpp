#pragma GCC target("popcnt")
#include<bits/stdc++.h>
using namespace std;
typedef unsigned short us;
typedef unsigned long long ull;
const int N=2880,W=64,NB=(N+W-1)/W,w=16,h=16;  //5120, 80
void mat_mul_bf(int *a,int *b,int *c,int n){
	int t1=clock();
	memset(c,0,n*n*sizeof(int));
	for (int i=0;i<n;++i)
		for (int k=0;k<n;++k)if (a[i*n+k]){
			int *_b=b+k*n,*_c=c+i*n;
			for (int j=0;j<n;++j)_c[j]+=_b[j];
		}
	printf("time=%d\n",clock()-t1);
}
void mat_mul_01(int *a,int *b,int *c,int n){
	static bitset<N> A[N],B[N];
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j){
			if (a[i*n+j])A[i].set(j,1);
			if (b[i*n+j])B[j].set(i,1);
		}
	int t1=clock();
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)
			c[i*n+j]=(A[i]&B[j]).count();
	printf("time=%d\n",clock()-t1);
}
alignas(64) ull a[N*NB],b[NB*N]; us c[N*N];
void mat_mul_01_word(int *_a,int *_b,int *c,int n){
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(int)*n*n);
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j){
			if (_a[i*n+j])a[i*NB+j/W]|=1ull<<j%W;
			if (_b[i*n+j])b[j*NB+i/W]|=1ull<<i%W;
		}
	int t1=clock();
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)
			for (int k=0;k<NB;++k)
				c[i*n+j]+=__builtin_popcountll(a[i*NB+k]&b[j*NB+k]);
	printf("time=%d\n",clock()-t1);
}
void kernel(int x,int y,int l,int r){
	us t[w][h]{0};
	for (int k=l;k<r;++k)
		for (int i=0;i<w;++i){
			ull a0=a[(x+i)*NB+k],*b0=b+k*N+y;
			for (int j=0;j<h;++j)
				t[i][j]+=__builtin_popcountll(a0&b0[j]);
		}
	for (int i=0;i<w;++i)
		for (int j=0;j<h;++j)c[(x+i)*N+y+j]+=t[i][j];
}
void mat_mul_01_fast(int *_a,int *_b,int *_c,int n){
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j){
			if (_a[i*n+j])a[i*NB+j/W]|=1ull<<j%W;
			if (_b[i*n+j])b[i/W*N+j]|=1ull<<i%W;
		}
	int t1=clock();
	const int s3=256,s2=16,s1=16;
	for (int i3=0;i3<n;i3+=s3)
		for (int i2=0;i2<n;i2+=s2)
			for (int i1=0;i1<NB;i1+=s1)
				for (int x=i2;x<min(i2+s2,n);x+=w)
					for (int y=i3;y<min(i3+s3,n);y+=h)
						kernel(x,y,i1,min(i1+s1,NB));
	printf("time=%d\n",clock()-t1);
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)_c[i*n+j]=c[i*n+j];
}
void verify(int *c,int n){
	int s=0;
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)
			s+=c[i*n+j]*(i^0x12345678)*(j^0x87654321);
	printf("s=%d\n",s);
}
void mat_mul_01_test(int n){
	static int a[N*N],b[N*N],c[N*N];
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)
			a[i*n+j]=rand()%2,b[i*n+j]=rand()%2;
	mat_mul_01_fast(a,b,c,n);
	verify(c,n);
	mat_mul_01_word(a,b,c,n);
	verify(c,n);
	mat_mul_01(a,b,c,n);
	verify(c,n);
	mat_mul_bf(a,b,c,n);
	verify(c,n);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	//srand(time(0)); 
	int n=N;
	mat_mul_01_test(n);
	//system("pause");for (;;);
	return 0;
}


