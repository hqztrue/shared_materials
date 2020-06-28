#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int K=4,L=5;
const double pack=150,draft_pack=0.4*pack,premier_entry=1500,quick_entry=750;
double w[]={50+pack*1,100+pack*1,250+pack*2,1000+pack*2,1400+pack*3,1600+pack*4,1800+pack*5,2200+pack*6},  //premier
	w1[]={50+pack*1.2,100+pack*1.22,200+pack*1.24,300+pack*1.26,450+pack*1.3,650+pack*1.35,850+pack*1.4,950+pack*2};  //quick
struct node{
	double v[3];  //premier W/L, quick L
	node *next[3];
	int act;  //0:premier W/L, 1:quick L, 2:premier L
};
node f[7][3][3][K][L+1][4];  //premier W/L, quick L, tier, tier bar, 3-game protection
double g[105][7][3][3][K][L+1][4],h[7][3][3][K][L+1][4],_h[7][3][3][K][L+1][4],best,p=0.6;
inline int comp(int k,int l,int l1){  //compress state
	if (k==0)return 0;
	if (l>=l1||(l==1||l==2)&&l1==3)return 0;
	return l1;
}
inline void move0(int i,int j,int j1,int k,int l,int l1,int &_i,int &_j,int &_j1,int &_k,int &_l,int &_l1,double &v){  //premier W
	_l=l+1,_k=k,_l1=max(l1-1,0);
	v=0,_j1=j1;
	if (l+1>=L)_l-=L,++_k,_l1=3;
	_l1=comp(_k,_l,_l1);
	if (_k>=K);
	else if (i+1<7)_i=i+1,_j=j;
	else _i=0,_j=0,v=w[7];
}
inline void move1(int i,int j,int j1,int k,int l,int l1,int &_i,int &_j,int &_j1,int &_k,int &_l,int &_l1,double &v){  //premier L
	_l1=max(l1-1,0),_k=k;
	v=0,_j1=j1;
	if (l>=1)_l=l-1;
	else if (l1>0)_l=0;
	else _l=L-1,--_k,_l1=0;
	_l1=comp(_k,_l,_l1);
	if (_k<0)_k=0,_l=0,_l1=0;
	if (j+1<3)_i=i,_j=j+1;
	else _i=0,_j=0,v=w[i];
}
inline void move2(int i,int j,int j1,int k,int l,int l1,int &_i,int &_j,int &_j1,int &_k,int &_l,int &_l1,double &v){  //quick L
	_l1=max(l1-1,0),_k=k;
	v=0,_i=i,_j=j;
	if (l>=1)_l=l-1;
	else if (l1>0)_l=0;
	else _l=L-1,--_k,_l1=0;
	_l1=comp(_k,_l,_l1);
	if (_k<0)_k=0,_l=0,_l1=0;
	if (j1+1<3)_j1=j1+1;
	else _j1=0,v=w1[0];
}
double eval(){
	fill_n(&h[0][0][0][0][0][0],sizeof(h)/sizeof(double),0.0);
	h[0][0][0][0][0][0]=1;
	for (int T=1;T<=1000;++T){
		fill_n(&_h[0][0][0][0][0][0],sizeof(h)/sizeof(double),0.0);
		for (int i=0;i<7;++i)
			for (int j=0;j<3;++j)
				for (int j1=0;j1<3;++j1)
					for (int k=0;k<K;++k)
						for (int l=0;l<=L;++l)
							for (int l1=0;l1<4;++l1){
								if (comp(k,l,l1)!=l1)continue;
								node *u=&f[i][j][j1][k][l][l1];
								double t=h[i][j][j1][k][l][l1];
								int _i,_j,_j1,_k,_l,_l1; double v;
								if (u->act==0){
									move0(i,j,j1,k,l,l1,_i,_j,_j1,_k,_l,_l1,v);
									_h[_i][_j][_j1][_k][_l][_l1]+=p*t;
									//if (_i<0||_i>6||_j<0||_j>2||_j1<0||_j1>2||_k<0||_k>K||_l<0||_l>L||_l1<0||_l1>3||comp(_k,_l,_l1)!=_l1)
									//	printf("err1 %d %d %d %d %d %d, %d %d %d %d %d %d\n",i,j,j1,k,l,l1,_i,_j,_j1,_k,_l,_l1);
									move1(i,j,j1,k,l,l1,_i,_j,_j1,_k,_l,_l1,v);
									_h[_i][_j][_j1][_k][_l][_l1]+=(1-p)*t;
								}
								else if (u->act==1){
									move2(i,j,j1,k,l,l1,_i,_j,_j1,_k,_l,_l1,v);
									_h[_i][_j][_j1][_k][_l][_l1]+=t;
								}
								else if (u->act==2){
									move1(i,j,j1,k,l,l1,_i,_j,_j1,_k,_l,_l1,v);
									_h[_i][_j][_j1][_k][_l][_l1]+=t;
								}
							}
		double diff=0,p1=0;
		for (int i=0;i<7;++i)
			for (int j=0;j<3;++j)
				for (int j1=0;j1<3;++j1)
					for (int k=0;k<K;++k)
						for (int l=0;l<=L;++l)
							for (int l1=0;l1<4;++l1){
								if (comp(k,l,l1)!=l1)continue;
								diff+=fabs(h[i][j][j1][k][l][l1]-_h[i][j][j1][k][l][l1]);
								p1+=_h[i][j][j1][k][l][l1];
							}
		//printf("T=%d diff=%.8lf %.8lf\n",T,diff,p1);
		memcpy(h,_h,sizeof(h));
	}
	double ans=0;
	for (int i=0;i<7;++i)
		for (int j=0;j<3;++j)
			for (int j1=0;j1<3;++j1)
				for (int k=0;k<K;++k)
					for (int l=0;l<=L;++l)
						for (int l1=0;l1<4;++l1){
							if (comp(k,l,l1)!=l1)continue;
							node *u=&f[i][j][j1][k][l][l1];
							double t=h[i][j][j1][k][l][l1];
							int _i,_j,_j1,_k,_l,_l1; double v;
							if (u->act==0){
								move0(i,j,j1,k,l,l1,_i,_j,_j1,_k,_l,_l1,v);
								ans+=t*p*u->v[0];
								move1(i,j,j1,k,l,l1,_i,_j,_j1,_k,_l,_l1,v);
								ans+=t*(1-p)*u->v[1];
							}
							else if (u->act==1){
								move2(i,j,j1,k,l,l1,_i,_j,_j1,_k,_l,_l1,v);
								ans+=t*u->v[2];
							}
							else if (u->act==2){
								move1(i,j,j1,k,l,l1,_i,_j,_j1,_k,_l,_l1,v);
								ans+=t*u->v[1];
							}
						}
	return ans;
}
/*double eval1(){
	for (int T=0;T<=100;++T)
		for (int i=0;i<7;++i)
			for (int j=0;j<3;++j)
				for (int j1=0;j1<3;++j1)
					for (int k=0;k<K;++k)
						for (int l=0;l<=L;++l)
							for (int l1=0;l1<4;++l1)g[T][i][j][j1][k][l][l1]=0;
	g[0][0][0][0][1][0][0]=1;
	for (int T=0;T<100;++T)
		for (int i=0;i<7;++i)
			for (int j=0;j<3;++j)
				for (int j1=0;j1<3;++j1)
					for (int k=0;k<K;++k)
						for (int l=0;l<=L;++l)
							for (int l1=0;l1<4;++l1){
								if (comp(k,l,l1)!=l1)continue;
								node *u=&f[i][j][j1][k][l][l1];
								double val=g[T][i][j][j1][k][l][l1];
								if (u->act==0){
									int _i,_j,_j1,_k,_l,_l1; double v;
									move0(i,j,j1,k,l,l1,_i,_j,_j1,_k,_l,_l1,v);
									g[T+1][_i][_j][_j1][_k][_l][_l1]+=p*val;
								}
								else {
									
								}
							}
}*/
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	srand(time(0));
	for (int i=0;i<=7;++i)w[i]+=draft_pack*3-premier_entry,w1[i]+=draft_pack*3-quick_entry;
	for (int i=0;i<7;++i)
		for (int j=0;j<3;++j)
			for (int j1=0;j1<3;++j1)
				for (int k=0;k<K;++k)
					for (int l=0;l<=L;++l)
						for (int l1=0;l1<4;++l1){
							if (comp(k,l,l1)!=l1)continue;
							node *u=&f[i][j][j1][k][l][l1];
							int _i,_j,_j1,_k,_l,_l1; double v;
							move0(i,j,j1,k,l,l1,_i,_j,_j1,_k,_l,_l1,v);
							if (_k>=K)u->next[0]=0;
							else u->next[0]=&f[_i][_j][_j1][_k][_l][_l1],u->v[0]=v;
							move1(i,j,j1,k,l,l1,_i,_j,_j1,_k,_l,_l1,v);
							u->next[1]=&f[_i][_j][_j1][_k][_l][_l1],u->v[1]=v;
							move2(i,j,j1,k,l,l1,_i,_j,_j1,_k,_l,_l1,v);
							u->next[2]=&f[_i][_j][_j1][_k][_l][_l1],u->v[2]=v;
							u->act=u->next[0]?0:1;
							//if (i==0&&j==2)u->act=2;
							if (i==6&&j<=1&&l>2)u->act=2;
						}
	best=eval();
	while (1){
		int i,j,j1,k,l,l1; node *u;
		while (1){
			i=rand()%7,j=rand()%3,j1=rand()%3,k=rand()%K,l=rand()%(L+1),l1=rand()%4;
			if (comp(k,l,l1)!=l1)continue;
			u=&f[i][j][j1][k][l][l1];
			if (u->act<=1){
				u->act^=1;
				break;
			}
		}
		double cur=eval();
		printf("best=%.8lf E=%.8lf\n",best,cur);
		if (cur>best)best=cur;
		else {
			u->act^=1;
		}
		//return 0;
	}
	system("pause");for (;;);
	return 0;
}


