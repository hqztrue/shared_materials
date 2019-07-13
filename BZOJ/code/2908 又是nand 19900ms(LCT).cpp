#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=100005;
typedef unsigned int uint;
int K;
struct DynamicTree{
	struct rec{
		uint a[32][2],b[32][2];int can;
		rec operator +(const rec &y)const{
			if (can)return y;
			if (y.can)return *this;
			//print();
			//y.print();
			rec res;res.can=0;
			for (int i=0;i<32;++i)
				for (int j=0;j<=1;++j)res.a[i][j]=y.a[i][a[i][j]];
			for (int i=0;i<32;++i)
				for (int j=0;j<=1;++j)res.b[i][j]=b[i][y.b[i][j]];
			//printf("res=\n");res.print();
			return res;
		}
		rec rev()const{
			rec res;res.can=can;//printf("rev\n");
			memcpy(res.a,b,sizeof(b));memcpy(res.b,a,sizeof(a));
			return res;
		}
		void ini(uint x){can=0;
			for (int i=0;i<32;++i){
				uint x1=(x>>i)&1;
				if (!x1)a[i][0]=a[i][1]=1;
				else a[i][0]=1,a[i][1]=0;
			}
			memcpy(b,a,sizeof(a));
		}
		void print()const{
			for (int i=0;i<K;++i)printf("%u * %u\n",a[i][0],a[i][1]);
			printf("\n");
		}
	};
	struct node{
		node *l,*r,*p;rec key,sum;
		void update(){
			sum.can=1;
			if (r!=NULL)sum=r->sum;
			sum=sum+key;
			if (l!=NULL)sum=sum+l->sum;
		}
	};
	node *a,*null;
	int max(int x,int y){return x>y?x:y;}
	int isroot(node *p){return p->p->l!=p&&p->p->r!=p;}
	void clear(){
		null=new node;null->l=null->r=null;null->key.ini(0);null->key.can=1;null->sum=null->key;
	}
	void ini_node(node *p){
		p->l=p->r=p->p=null;p->key.ini(0);
	}
	DynamicTree(int n=5){
		n+=5;a=new node[n];clear();
		for (int i=0;i<n;++i)ini_node(a+i);
	}
	void zig(node *x){
		node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else if (z->r==y)z->r=x;
		x->p=z;y->p=x;y->l=x->r;x->r=y;
		y->l->p=y;y->update();
	}
	void zag(node *x){
		node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else if (z->r==y)z->r=x;
		x->p=z;y->p=x;y->r=x->l;x->l=y;
		y->r->p=y;y->update();
	}
	void splay(node *x){
		node *y,*z;if (x==null) return;
		while (!isroot(x)){
			y=x->p;z=y->p;
			if (isroot(y)){if (x==y->l)zig(x);else zag(x);}
			else
				if (y==z->l)
					if (x==y->l){zig(y);zig(x);}
					else{zag(x);zig(x);}
				else
					if (x==y->r){zag(y);zag(x);}
					else{zig(x);zag(x);}
		}
		x->update();
	}
	node *head(node *p){
		for(;p->l!=null;)p=p->l;
		splay(p);return p;
	}
	node *tail(node *p){
		for(;p->r!=null;)p=p->r;
		splay(p);return p;
	}
	node *prev(node *p){
		if (p->l==null)return null;
		node *q=p->l;
		for (;q->r!=null;)q=q->r;
		splay(q);return q;
	}
	node *next(node *p){
		if (p->r==null)return null;
		node *q=p->r;
		for (;q->l!=null;)q=q->l;
		splay(q);return q;
	}
	node *Expose(node *p){
		node *q=null;
		for (;p!=null;p=p->p){
			splay(p);p->r=q;(q=p)->update();
		}
		return q;
	}
	node *getnode(int x){return a+x;}
	int getid(node *p){return p-a;}
	void Change(node *p,uint key){
		splay(p);p->key.ini(key);p->update();
	}
	node *Parent(node *p){
		splay(p);if (p->l!=null)return prev(p);
		else return p->p;
	}
	node *Root(node *p){return head(Expose(p));}
	node *LCA(node *p,node *q){
		node *x=Root(p),*y=Expose(q),*z=head(y);
		if (x==z)return y;
		else return null;
	}
	uint Query(node *p,node *q){
		rec ans,left,right;left.can=right.can=1;
		Expose(p);
		node *y=Expose(q);
		right=y->key+y->r->sum.rev();
		if (p!=y)splay(p),left=p->sum;
		//printf("left %d\n",(int)left.can);left.print();
		//printf("right %d\n",(int)right.rev().can);right.rev().print();
		ans=left+right;
		//printf("ans\n");ans.print();
		uint xx=0;
		for (int i=0;i<K;++i)if (ans.a[i][0])xx+=1<<i;
		return xx;
	}
	/*void print(){
		for (int i=1;i<=n;i++){
			node *tmp=getnode(i);
			printf("node%d: %d %d %d %d %d\n",i,tmp->l->num,tmp->r->num,tmp->p->num,tmp->key,tmp->max);
		}
	}*/
	void Change(int x,uint key){Change(getnode(x),key);}
	int Parent(int x){return getid(Parent(getnode(x)));}
	int Root(int x){return getid(Root(getnode(x)));}
	uint Query(int p,int q){return Query(getnode(p),getnode(q));}
};
DynamicTree a(N);
struct Edge{
	int link[N*2],next[N*2],son[N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
};
Edge e;
struct Tree{
	int fa[N],dep[N];uint w[N];
	void Build(int x,int y,int deep){
		dep[x]=deep;fa[x]=y;
		for (int i=e.son[x];i;i=e.next[i]){
			int j=e.link[i];
			if (j!=y)Build(j,x,deep+1);
		}
	}
};
Tree c;
int n;
char str[105];
void copy(){
	for (int i=1;i<=n;++i){
		a.a[i].p=a.getnode(c.fa[i]);
		a.a[i].l=a.a[i].r=a.null;
		a.a[i].key.ini(c.w[i]);
		a.getnode(i)->update();
	}
	a.a[1].p=a.null;
	/*for (int i=1;i<=n;i++)a.a[i].num=i;
	a.a[0].num=1234;
	a.null->num=-1;*/
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	//int t1=clock();
	int q;scanf("%d%d%d",&n,&q,&K);uint x;a.clear();e.clear();
	for (int i=1;i<=n;++i)scanf("%u",&c.w[i]);
	for (int i=1;i<n;++i){
		int x,y;scanf("%d%d",&x,&y);
		e.addedge(x,y);e.addedge(y,x);
	}
	c.Build(1,0,0);copy();
	while (q--){
		char zzy[15];int x,y;
		scanf("%s",zzy);
		if (zzy[0]=='Q'){
			scanf("%d%d",&x,&y);
			printf("%u\n",a.Query(x,y));
		}
		else {
			uint y;scanf("%d%u",&x,&y);
			a.Change(x,y);
		}
	}
	//printf("time=%d\n",clock()-t1);
	//system("pause");for (;;);
	return 0;
}


