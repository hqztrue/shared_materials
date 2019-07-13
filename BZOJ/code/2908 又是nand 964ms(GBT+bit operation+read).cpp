#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
namespace fastIO{
	#define BUF_SIZE 100000
	#define OUT_SIZE 100000
	#define ll long long
	//fread->read
	bool IOerror=0;
	inline char nc(){
		static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
		if (p1==pend){
			p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
			if (pend==p1){IOerror=1;return -1;}
			//{printf("IO error!\n");system("pause");for (;;);exit(0);}
		}
		return *p1++;
	}
	inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
	inline void read(int &x){
		bool sign=0; char ch=nc(); x=0;
		for (;blank(ch);ch=nc());
		if (IOerror)return;
		if (ch=='-')sign=1,ch=nc();
		for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
		if (sign)x=-x;
	}
	inline void read(unsigned int &x){
		bool sign=0; char ch=nc(); x=0;
		for (;blank(ch);ch=nc());
		if (IOerror)return;
		if (ch=='-')sign=1,ch=nc();
		for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
		if (sign)x=-x;
	}
	inline void read(ll &x){
		bool sign=0; char ch=nc(); x=0;
		for (;blank(ch);ch=nc());
		if (IOerror)return;
		if (ch=='-')sign=1,ch=nc();
		for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
		if (sign)x=-x;
	}
	inline void read(double &x){
		bool sign=0; char ch=nc(); x=0;
		for (;blank(ch);ch=nc());
		if (IOerror)return;
		if (ch=='-')sign=1,ch=nc();
		for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
		if (ch=='.'){
			double tmp=1; ch=nc();
			for (;ch>='0'&&ch<='9';ch=nc())tmp/=10.0,x+=tmp*(ch-'0');
		}
		if (sign)x=-x;
	}
	inline void read(char *s){
		char ch=nc();
		for (;blank(ch);ch=nc());
		if (IOerror)return;
		for (;!blank(ch)&&!IOerror;ch=nc())*s++=ch;
		*s=0;
	}
	inline void read(char &c){
		for (c=nc();blank(c);c=nc());
		if (IOerror){c=-1;return;}
	}
	//getchar->read
	inline void read1(int &x){
		char ch;int bo=0;x=0;
		for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
		for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
		if (bo)x=-x;
	}
	inline void read1(ll &x){
		char ch;int bo=0;x=0;
		for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
		for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
		if (bo)x=-x;
	}
	inline void read1(double &x){
		char ch;int bo=0;x=0;
		for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
		for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
		if (ch=='.'){
			double tmp=1;
			for (ch=getchar();ch>='0'&&ch<='9';tmp/=10.0,x+=tmp*(ch-'0'),ch=getchar());
		}
		if (bo)x=-x;
	}
	inline void read1(char *s){
		char ch=getchar();
		for (;blank(ch);ch=getchar());
		for (;!blank(ch);ch=getchar())*s++=ch;
		*s=0;
	}
	inline void read1(char &c){for (c=getchar();blank(c);c=getchar());}
	//scanf->read
	inline void read2(int &x){scanf("%d",&x);}
	inline void read2(ll &x){
		#ifdef _WIN32
			scanf("%I64d",&x);
		#else
		#ifdef __linux
			scanf("%lld",&x);
		#else
			puts("error:can't recognize the system!");
		#endif
		#endif
	}
	inline void read2(double &x){scanf("%lf",&x);}
	inline void read2(char *s){scanf("%s",s);}
	inline void read2(char &c){scanf(" %c",&c);}
	inline void readln2(char *s){gets(s);}
	//fwrite->write
	struct Ostream_fwrite{
		char *buf,*p1,*pend;
		Ostream_fwrite(){buf=new char[BUF_SIZE];p1=buf;pend=buf+BUF_SIZE;}
		void out(char ch){
			if (p1==pend){
				fwrite(buf,1,BUF_SIZE,stdout);p1=buf;
			}
			*p1++=ch;
		}
		void print(int x){
			static char s[15],*s1;s1=s;
			if (!x)*s1++='0';if (x<0)out('-'),x=-x;
			while(x)*s1++=x%10+'0',x/=10;
			while(s1--!=s)out(*s1);
		}
		void println(int x){
			static char s[15],*s1;s1=s;
			if (!x)*s1++='0';if (x<0)out('-'),x=-x;
			while(x)*s1++=x%10+'0',x/=10;
			while(s1--!=s)out(*s1); out('\n');
		}
		void print(ll x){
			static char s[25],*s1;s1=s;
			if (!x)*s1++='0';if (x<0)out('-'),x=-x;
			while(x)*s1++=x%10+'0',x/=10;
			while(s1--!=s)out(*s1);
		}
		void println(ll x){
			static char s[25],*s1;s1=s;
			if (!x)*s1++='0';if (x<0)out('-'),x=-x;
			while(x)*s1++=x%10+'0',x/=10;
			while(s1--!=s)out(*s1); out('\n');
		}
		void print(double x,int y){
			static ll mul[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,
				1000000000,10000000000LL,100000000000LL,1000000000000LL,10000000000000LL,
				100000000000000LL,1000000000000000LL,10000000000000000LL,100000000000000000LL};
			if (x<-1e-12)out('-'),x=-x;x*=mul[y];
			ll x1=(ll)floor(x); if (x-floor(x)>=0.5)++x1;
			ll x2=x1/mul[y],x3=x1-x2*mul[y]; print(x2);
			if (y>0){out('.'); for (size_t i=1;i<y&&x3*mul[i]<mul[y];out('0'),++i); print(x3);}
		}
		void println(double x,int y){print(x,y);out('\n');}
		void print(char *s){while (*s)out(*s++);}
		void println(char *s){while (*s)out(*s++);out('\n');}
		void flush(){if (p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}}
		~Ostream_fwrite(){flush();}
	}Ostream;
	inline void print(int x){Ostream.print(x);}
	inline void println(int x){Ostream.println(x);}
	inline void print(char x){Ostream.out(x);}
	inline void println(char x){Ostream.out(x);Ostream.out('\n');}
	inline void print(ll x){Ostream.print(x);}
	inline void println(ll x){Ostream.println(x);}
	inline void print(double x,int y){Ostream.print(x,y);}
	inline void println(double x,int y){Ostream.println(x,y);}
	inline void print(char *s){Ostream.print(s);}
	inline void println(char *s){Ostream.println(s);}
	inline void println(){Ostream.out('\n');}
	inline void flush(){Ostream.flush();}
	//puts->write
	char Out[OUT_SIZE],*o=Out;
	inline void print1(int x){
		static char buf[15];
		char *p1=buf;if (!x)*p1++='0';if (x<0)*o++='-',x=-x;
		while(x)*p1++=x%10+'0',x/=10;
		while(p1--!=buf)*o++=*p1;
	}
	inline void println1(int x){print1(x);*o++='\n';}
	inline void print1(ll x){
		static char buf[25];
		char *p1=buf;if (!x)*p1++='0';if (x<0)*o++='-',x=-x;
		while(x)*p1++=x%10+'0',x/=10;
		while(p1--!=buf)*o++=*p1;
	}
	inline void println1(ll x){print1(x);*o++='\n';}
	inline void print1(char c){*o++=c;}
	inline void println1(char c){*o++=c;*o++='\n';}
	inline void print1(char *s){while (*s)*o++=*s++;}
	inline void println1(char *s){print1(s);*o++='\n';}
	inline void println1(){*o++='\n';}
	inline void flush1(){if (o!=Out){if (*(o-1)=='\n')*--o=0;puts(Out);}}
	struct puts_write{
		~puts_write(){flush1();}
	}_puts;
	inline void print2(int x){printf("%d",x);}
	inline void println2(int x){printf("%d\n",x);}
	inline void print2(char x){printf("%c",x);}
	inline void println2(char x){printf("%c\n",x);}
	inline void print2(ll x){
		#ifdef _WIN32
			printf("%I64d",x);
		#else
		#ifdef __linux
			printf("%lld",x);
		#else
			puts("error:can't recognize the system!");
		#endif
		#endif
	}
	inline void println2(ll x){print2(x);printf("\n");}
	inline void println2(){printf("\n");}
	#undef ll
	#undef OUT_SIZE
	#undef BUF_SIZE
};
using namespace fastIO;
const int N=100005;
typedef unsigned int uint;
int K;
struct GBT{
	struct edge{
		edge *next;int link;
	}e[N*2],*e1,*son[N];
	struct rec{
		uint a0,a1,b0,b1;bool can;
		rec operator +(const rec &y)const{
			if (can)return y;
			if (y.can)return *this;
			//print();
			//y.print();
			rec res;res.can=0;
			/*for (int i=0;i<K;++i)res.a[i][0]=y.a[i][a[i][0]];
			for (int i=0;i<K;++i)res.a[i][1]=y.a[i][a[i][1]];
			for (int i=0;i<K;++i)
				for (int j=0;j<=1;++j)res.b[i][j]=b[i][y.b[i][j]];*/
			res.a0=(y.a0&~a0)+(y.a1&a0);
			res.a1=(y.a0&~a1)+(y.a1&a1);
			res.b0=(b0&~y.b0)+(b1&y.b0);
			res.b1=(b0&~y.b1)+(b1&y.b1);
			/*printf("rp1 %u\n",res.a0);
			printf("rp2 %u\n",res.a1);
			printf("rp3 %u\n",res.b0);
			printf("rp4 %u\n",res.b1);*/
			//printf("res=\n");res.print();
			return res;
		}
		rec rev()const{
			rec res;res.can=can;//printf("rev\n");
			res.a0=b0;res.a1=b1;res.b0=a0;res.b1=a1;
			return res;
		}
		void ini(uint x){can=0;
			/*for (int i=0;i<K;++i){
				uint x1=(x>>i)&1;
				if (!x1)a1|=1<<i;
				else a1&=~(1<<i);
			}*/
			b0=a0=~0u;b1=a1=~x;
		}
		/*void print()const{
			for (int i=0;i<K;++i)printf("%u * %u\n",a[i][0],a[i][1]);
			printf("\n");
		}*/
	};
	struct node{
		node *l,*r,*p,*head;int dep;
		rec key,sum;
		void update(){
			sum=key;
			if (l!=NULL)sum=sum+l->sum;
			if (r!=NULL)sum=r->sum+sum;
		}
	}a[N];
	int dep[N],size[N],fa[N],heavy[N];
	void clear(){
		for (int i=0;i<N*2;++i)e[i].next=NULL;
		for (int i=0;i<N;++i)son[i]=NULL;
		e1=e;size[0]=0;dep[0]=0;
	}
	GBT(){clear();}
	node *getnode(int x){return a+x;}
	int getid(node *x){return x-a;}
	bool istop(node *x){return x->p==NULL||x->p->l!=x&&x->p->r!=x;}
	void addedge(int x,int y){
		e1->link=y;e1->next=son[x];son[x]=e1++;
		e1->link=x;e1->next=son[y];son[y]=e1++;
	}
	node *build(int start,int siz,node *head,int dep){
		if (!siz)return NULL;
		int mid,s=size[start]-size[heavy[start]],now=start;
		while (s+s<siz)now=heavy[now],s+=size[now]-size[heavy[now]];
		node *x=getnode(now);x->head=head;x->dep=dep;
		if ((x->l=build(start,s-size[now]+size[heavy[now]],head,dep+1))!=NULL)x->l->p=x;
		if ((x->r=build(heavy[now],siz-s,head,dep+1))!=NULL)x->r->p=x;
		x->update();return x;
	}
	void bfs(int root,int n){
		//for (int i=2;i<=3;++i)getnode(i)->key.print();
		static int Q[N];int t=1;Q[1]=root;
		for (int i=1;i<=n;++i)dep[i]=0;
		dep[root]=1;fa[root]=0;
		for (int h=1;h<=t;++h){
			int x=Q[h];
			for (edge *i=son[x];i;i=i->next){
				int j=i->link;if (dep[j])continue;
				dep[j]=dep[x]+1;fa[j]=x;Q[++t]=j;
			}
		}
		for (int i1=t;i1;--i1){
			int x=Q[i1],max=0;heavy[x]=0;size[x]=1;
			for (edge *i=son[x];i;i=i->next)if (i->link!=fa[x]){
				int s=size[i->link];size[x]+=s;
				if (s>max)max=s,heavy[x]=i->link;
			}
		}
		for (int i1=1;i1<=n;++i1){
			int i=Q[i1];
			if (!fa[i]||heavy[fa[i]]!=i){
				node *x=build(i,size[i],getnode(i),getnode(fa[i])->dep+1);
				if (fa[i])x->p=getnode(fa[i]);
				else x->p=NULL;
			}
		}
	}
	void Change(node *x,uint y){
		x->key.ini(y);
		for (;;x=x->p){x->update();if (istop(x))break;}
	}
	void Change(int x,uint y){Change(getnode(x),y);}
	uint Query(node *x,node *y){
		rec left,right;//left.ini(0);
		left.can=1;right.can=1;
		while (x->head!=y->head)
			if (dep[getid(x->head)]>dep[getid(y->head)]){
				for (node *pre=x->r,*now=x;pre==now->l||pre==now->r;pre=now,now=now->p)
					if (pre==now->r){
						left=left+now->key;
						if (now->l!=NULL)left=left+now->l->sum;
					}
				x=getnode(fa[getid(x->head)]);
			}
			else {
				for (node *pre=y->r,*now=y;pre==now->l||pre==now->r;pre=now,now=now->p)
					if (pre==now->r){
						right=right+now->key;
						if (now->l!=NULL)right=right+now->l->sum;
					}
				y=getnode(fa[getid(y->head)]);
			}
		bool flag=dep[getid(x)]<dep[getid(y)]; node *prex,*prey;
		if (flag)prex=x->l,prey=y->r;
		else prex=x->r,prey=y->l;
		while (x!=y)
			if (x->dep>y->dep){
				if (flag&&prex==x->l){
					left=left+x->key;
					if (x->r!=NULL)left=left+x->r->sum.rev();
				}
				else if (!flag&&prex==x->r){
					left=left+x->key;
					if (x->l!=NULL)left=left+x->l->sum;
				}
				prex=x;x=x->p;
			}
			else {
				if (!flag&&prey==y->l){
					right=right+y->key;
					if (y->r!=NULL)right=right+y->r->sum.rev();
				}
				else if (flag&&prey==y->r){
					right=right+y->key;
					if (y->l!=NULL)right=right+y->l->sum;
				}
				prey=y;y=y->p;
			}
		//printf("left\n");left.print();
		//(left+x->key).print();
		//printf("right\n");right.rev().print();
		rec ans=left+x->key+right.rev();
		return ans.a0&((1LL<<K)-1);
	}
	uint Query(int x,int y){return Query(getnode(x),getnode(y));}
};
GBT T;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	//int t1=clock();
	int n,q;read(n),read(q),read(K);uint x;
	for (int i=1;i<=n;++i)read(x),T.getnode(i)->key.ini(x);
	for (int i=1;i<n;++i){
		int x,y;read(x),read(y);
		T.addedge(x,y);
	}
	T.bfs(1,n);
	while (q--){
		char zzy[15];int x,y;
		read(zzy);
		if (zzy[0]=='Q'){
			read(x),read(y);
			printf("%u\n",T.Query(x,y));
		}
		else {
			uint y;read(x),read(y);
			T.Change(x,y);
		}
	}
	//printf("time=%d\n",clock()-t1);
	//system("pause");for (;;);
	return 0;
}


