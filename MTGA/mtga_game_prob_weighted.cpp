#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
#define N 105
double f[N][N],w[N];
int n,m;
const double G=800,collection_p=0.6,pack=150,draft_pack=0.45*pack,randG=collection_p*G+(1-collection_p)*20./150*1000,
	ICR=0.15*G,dollar=200,ratio=5000./750,packG=pack*ratio,draft_token=1500;  //draft_pack=0.5*pack*6/(6+2) 0.45* 0.7*
double p=0.5,basic_reward,entry,res;
inline ll C(int n,int m){
	if (n<m)return 0;
	ll res=1;
	for (int i=1;i<=m;++i)res=res*(n-i+1)/i;
	return res;
}
void constructed(){
	n=7;m=3;
	w[0]=100+0.07*randG;w[1]=200+0.07*randG;w[2]=300+0.07*randG;w[3]=400+0.07*randG;w[4]=500+0.07*randG;w[5]=600+1.06*randG;w[6]=800+2.05*randG;w[7]=1000+2.05*randG;
	entry=500;
}
void traditional_constructed(){
	n=5;m=2;
	w[0]=0+0.15*G*p;w[1]=500+0.25*G*p;w[2]=1000+0.25*G*p;w[3]=1500+1.2*G*p;w[4]=1700+1.2*G*p;w[5]=2100+2.15*G*p;
	entry=1000;
}
void quick_draft(){
	n=7;m=3;
	w[0]=50+pack*1.2;w[1]=100+pack*1.22;w[2]=200+pack*1.24;w[3]=300+pack*1.26;w[4]=450+pack*1.3;w[5]=650+pack*1.35;w[6]=850+pack*1.4;w[7]=950+pack*2;
	basic_reward=3*draft_pack; entry=750;
}
void premier_draft(){
	n=7;m=3;
	w[0]=50+pack*1;w[1]=100+pack*1;w[2]=250+pack*2;w[3]=1000+pack*2;w[4]=1400+pack*3;w[5]=1600+pack*4;w[6]=1800+pack*5;w[7]=2200+pack*6;
	basic_reward=3*draft_pack; entry=1500;
}
void traditional_draft(){
	n=5;m=2;
	w[0]=0+pack*1;w[1]=0+pack*2;w[2]=800+pack*3;w[3]=1500+pack*4;w[4]=1800+pack*5;w[5]=2100+pack*6;
	basic_reward=3*draft_pack; entry=1500;
}
void draft_challenge(){
	n=6;m=2;
	w[0]=0;w[1]=2000+3*packG;w[2]=4000+6*packG;w[3]=7500+12*packG;w[4]=10000+20*packG;w[5]=15000+30*packG;w[6]=20000+40*packG;
	entry=15000;
}
void draft_challenge1(){
	n=6;m=2;
	w[0]=0;w[1]=draft_token;w[2]=draft_token+3*pack;w[3]=2*draft_token+6*pack;w[4]=3*draft_token+10*pack;w[5]=3*draft_token+15*pack;w[6]=4*draft_token+20*pack;
	basic_reward=3*draft_pack; entry=3000;
}
void sealed(){
	n=7;m=3;
	w[0]=200;w[1]=400;w[2]=600;w[3]=1200;w[4]=1400;w[5]=1600;w[6]=2000;w[7]=2200;
	for (int i=0;i<=n;++i)w[i]+=pack*3;
	basic_reward=6*draft_pack; entry=2000;
}
void traditional_sealed(){
	n=4;m=2;
	w[0]=200;w[1]=500;w[2]=1200;w[3]=1800;w[4]=2200;
	for (int i=0;i<=n;++i)w[i]+=pack*3;
	basic_reward=6*draft_pack; entry=2000;
}
void competitive_metagame(){  //i.e. standard metagame challenge
	n=7;m=1;
	w[0]=500;w[1]=1000;w[2]=2500;w[3]=5000;w[4]=7500;w[5]=13000;w[6]=24000;w[7]=35000;
	entry=2000;
}
void cube(){
	n=7;m=3;
	w[0]=randG;w[1]=500+randG;w[2]=1000+randG;w[3]=2000+randG;w[4]=3000+randG;w[5]=4000+2*randG;w[6]=5000+2*randG;w[7]=6000+2*randG;
}
void arena_open_day2(){
	n=7;m=2;
	w[0]=0;w[1]=2000;w[2]=4000;w[3]=6000;w[4]=10000;w[5]=20000;w[6]=1000*dollar;w[7]=2000*dollar;
	entry=0;
}
void arena_open_day1(){
	n=7;m=3;
	w[0]=0;w[1]=0;w[2]=0;w[3]=400;w[4]=800;w[5]=1200;w[6]=1600;w[7]=2000+23250;
	entry=4000;  //3000
}
void arena_open_day1_bo3(){
	n=4;m=1;
	w[0]=0;w[1]=1000;w[2]=2500;w[3]=5000;w[4]=5000+23250;
	entry=4000;
}
void qualifier_weekend_day1(){
	n=7;m=3;
	w[0]=0;w[1]=200;w[2]=400;w[3]=600;w[4]=800;w[5]=1000;w[6]=1200;w[7]=1200+2777;
	entry=0;
}
void qualifier_weekend_day2(){
	n=7;m=3;
	w[0]=0;w[1]=1000;w[2]=2000;w[3]=3000;w[4]=4000;w[5]=5000;w[6]=6000;w[7]=6000;
	entry=0;
}
void historic_challenge(){
	n=8;m=3;
	w[0]=4*randG;w[1]=4*randG+1000;w[2]=4*randG+2000;w[3]=4*randG+3000;w[4]=4*randG+4000;w[5]=8*packG+6000;w[6]=12*packG+8000;w[7]=20*packG+10000;w[8]=40*packG+15000;
	entry=10000;
}
void historic_challenge1(){
	n=7;m=2;
	w[0]=4*randG;w[1]=4*randG+1000;w[2]=4*randG+3000;w[3]=6*packG+5000;w[4]=12*packG+7500;w[5]=18*packG+10000;w[6]=24*packG+15000;w[7]=30*packG+25000;
	entry=10000;
}
double traditional_draft_new(bool flag=1){
	n=3;
	w[0]=pack*1;w[1]=pack*1;w[2]=1000+pack*4;w[3]=3000+pack*6;
	basic_reward=3*draft_pack; entry=1500;
	double s=(1-p)*(1-p)*(1-p)*w[0]+3*(1-p)*(1-p)*p*w[1]+3*(1-p)*p*p*w[2]+p*p*p*w[3];
	if (flag)printf("E[reward]=%.8lf gross=%.8lf net=%.8lf\n",s,s+basic_reward,s+basic_reward-entry);
	double t=(s+basic_reward-entry)/3;
	if (flag)printf("E[per match]=%.8lf\n",t);
	double m=(2+2*p*(1-p));
	if (flag)printf("E[#games]=%.8lf\n",m);  //per match
	res=t/m;
	if (flag)printf("E[per game]=%.8lf\n",res);
}
void traditional_arena_cube(){
	n=3;
	w[0]=randG;w[1]=randG;w[2]=4000+randG;w[3]=6000+2*randG;
	entry=4000;
}
void calc1(){
	double s=0;
	for (int i=0;i<=n;++i)s+=w[i]*C(n,i)/pow(2.,n);
	printf("E[reward]=%.8lf net=%.8lf\n",s,s-entry);
	exit(0);
}
double calc(bool flag=1){
	//constructed();
	//traditional_constructed();
	//quick_draft();
	//traditional_draft();
	premier_draft();
	//sealed();
	//traditional_sealed();
	//competitive_metagame();
	//cube();
	//arena_open_day1();
	//arena_open_day1_bo3();
	//arena_open_day2();
	//qualifier_weekend_day1();
	//qualifier_weekend_day2();
	//draft_challenge();
	//historic_challenge();
	//historic_challenge1();
	//traditional_draft_new(flag); return res;
	//draft_challenge1();
	//return 0;
	
	//traditional_arena_cube(); calc1();
	
	//for (int i=0;i<=7;++i)printf("%d %.5lf\n",i,w[i]);
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for (int I=0;I<=n+m-2;++I)
		for (int i=0;i<=min(I,n-1);++i){
			int j=I-i; if (j>=m)continue;
			f[i+1][j]+=p*f[i][j];
			f[i][j+1]+=(1-p)*f[i][j];
		}
	//expected wins
	double s=0,s1=0,s2=0;
	for (int i=0;i<n;++i){
		if (flag)printf("%d %.8lf %.2lf\n",i,f[i][m],w[i]);
		s+=f[i][m]*i;
	}
	for (int i=0;i<m;++i)s1+=f[n][i];
	if (flag)printf("%d %.8lf %.2lf\n",n,s1,w[n]);
	s+=s1*n;
	if (flag)printf("E[#games won]=%.8lf\n",s);
	
	//expected reward
	s=0;
	for (int i=0;i<n;++i)s+=f[i][m]*w[i];
	s+=s1*w[n];
	if (flag)printf("E[reward]=%.8lf gross=%.8lf net=%.8lf\n",s,s+basic_reward,s+basic_reward-entry);
	
	//average reward per game
	for (int i=0;i<n;++i)s2+=f[i][m]*(i+m);
	for (int i=0;i<m;++i)s2+=f[n][i]*(n+i);
	if (flag)printf("E[#games]=%.8lf\n",s2);
	double ans=(s+basic_reward-entry)/s2;
	if (flag)printf("E[per game]=%.8lf\n",ans);
	return ans;
}
void print(){
	vector<double> a,b;
	for (double p0=0.45;p0<0.76;p0+=0.01){
		p=p0;
		//p=p0*p0+2*p0*p0*(1-p0);
		a.push_back(p0);
		b.push_back(calc(0));
	}
	int n=a.size();
	freopen("data.txt","w",stdout);
	for (int i=0;i<n;++i)printf("%.5lf%c",a[i],i==n-1?'\n':',');
	for (int i=0;i<n;++i)printf("%.5lf%c",b[i],i==n-1?'\n':',');
	fclose(stdout);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	calc();
	//print(); return 0;
	system("pause");for (;;);
	return 0;
}


