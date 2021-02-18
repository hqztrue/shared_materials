/***************************************************
Algorithm credit to @oldyan, modified by @hqztrue.
https://github.com/hqztrue/LeetCodeSolutions
***************************************************/
const int N=405;
int deg[N];
bool matrix[N][N];
short adj[N][N],adj_len[N];
class Solution {
	struct triple{
		short i,j;
		int k;
		triple(short _i,short _j,int _k):i(_i),j(_j),k(_k){}
	};
public:
	//使用bitset作为描述邻接表的数据结构，b[i][j]=0，表示i与j不相连；b[i][j]=1，表示i与j相连
	int minTrioDegree(int n, vector<vector<int>>& edges){return 0;}
	int minTrioDegree(int n, int m, int *edges1, int *edges2) {
		for (int i=0;i<=n;++i){
			deg[i]=adj_len[i]=0;
			for (int j=0;j<=n;++j)matrix[i][j]=0;
		}
		for (int I=0;I<m;++I){
			int i=edges1[I],j=edges2[I];
			deg[i]++;deg[j]++;
			matrix[i][j]=matrix[j][i]=true;
		}
		for (int I=0;I<m;++I){
			int i=edges1[I],j=edges2[I];
			if(deg[i]>deg[j]||(deg[i]==deg[j]&&i>j))adj[j][adj_len[j]++]=i;
			else adj[i][adj_len[i]++]=j;
		}
		int ans=INT_MAX;
		auto comp=[](triple*x,triple*y){
			return x->k>y->k;
		};
		int idx[n];
		iota(idx,idx+n,1);
		sort(idx,idx+n,[&](int x,int y){return deg[x]<deg[y];});
		bool used[n+1];
		memset(used,0,sizeof(used));
		for(int i=0;i<n;i++){
			int first=idx[i];
			if(used[first])continue;
			if(adj_len[first]<2)continue;
			short *v=adj[first];
			sort(v,v+adj_len[first],[&](short x,short y){return deg[x]<deg[y];});
			priority_queue<triple*,vector<triple*>,decltype(comp)>Q(comp);
			for(int i=0;i<adj_len[first]-1;i++){
				int k=deg[first]+deg[v[i]]+deg[v[i+1]]-6;
				if(k<ans)Q.emplace(new triple(i,i+1,k));
			}
			while(Q.size()&&Q.top()->k<ans){
				auto p=Q.top();
				Q.pop();
				if(matrix[v[p->i]][v[p->j]]){
					used[v[p->i]]=true;
					//used[v[p->j]]=true;
					ans=min(ans,p->k);
					break;
				}
				if(++(p->j)<adj_len[first]){
					p->k+=deg[v[p->j]]-deg[v[p->j-1]];
					if(p->k<ans)Q.emplace(p);
				}
			}
		}
		return short(ans);
	}
};

//fastIO
namespace Read{
	const int S=5000000;
	char _str[S],*p=_str;
	inline void read(char &c){while (*p<'!'||*p>'~')p++; c=*p++;}
	inline bool read_next(char c){while (*p!=c&&*p)++p; return *p!=0;}
	inline bool read_next_digit(){while (*p&&(*p<'0'||*p>'9'))++p; return *p!=0;}
	inline void read(int &x){
		bool sign=0; x=0; while (*p<'0'||*p>'9')if (*p++=='-')sign=1;
		while (*p>='0'&&*p<='9')x=x*10+*p++-48;if (sign)x=-x;
	}
	inline void read(double &x){
		bool sign=0; x=0; while (*p<'0'||*p>'9')if (*p++=='-')sign=1;
		while (*p>='0'&&*p<='9')x=x*10+*p++-48;
		if (*p=='.'){
			double tmp=1; ++p;
			while (*p>='0'&&*p<='9')tmp*=0.1,x+=tmp*(*p++-48);
		}
		if (sign)x=-x;
	}
	inline void read(char *s){
		while (*p<'0'||*p>'z')p++;
		while (*p>='0'&&*p<='z')*s++=*p++;
		*s=0;
	}
	inline void read_arr(int a[],int &n){
		n=0; while (*p++!='[');
		while (1){
			int x=0; bool sign=0;
			while (*p<'0'||*p>'9'&&*p!=']')if (*p++=='-')sign=1;
			if (*p==']'){++p; return;}
			while (*p>='0'&&*p<='9')x=x*10+*p++-48;
			if (sign)a[n++]=-x; else a[n++]=x;
		}
	}
	inline void read_double_arr(double a[],int &n){
		n=0; while (*p++!='[');
		while (1){
			if (*p==']'){++p; return;}
			double v=0; read(v); a[n++]=v;
		}
	}
	inline void read_char_arr(char a[],int &n){
		n=0; while (*p++!='[');
		while (1){
			while (*p<'A'||*p>'Z'&&*p<'a'&&*p!=']'||*p>'z')*p++;
			if (*p==']'){++p; return;}
			a[n++]=*p++;
			while (*p>='A'&&*p<='Z'||*p>='a'&&*p<='z')*p++;
		}
	}
	vector<int> read_int_vec(){
		vector<int> res;
		read_next('['); ++p;
		while (*p!=']'){
			int t; read(t);
			res.push_back(t);
		}
		++p; return res;
	}
	vector<vector<int> > read_int_vec2D(){
		vector<vector<int> > res;
		read_next('['); ++p;
		while (*p!=']'){
			res.emplace_back(read_int_vec());
		}
		return res;
	}
	void read_int_arr2D(int a[],int b[],int &m){
		read_next('['); ++p; m=0;
		while (*p!=']'){
			read(a[m]); read(b[m]); ++p; ++m;
		}
	}
	void read_init(){fread(p,1,S,stdin);}
	
	const int S1=1000000;
	char _buf[15],_out[S1],*o=_out;
	inline void print(int x,char c=0){
		char *b=_buf;
		if (x<0)*o++='-',x=-x;
		else if (!x)*b++='0';
		while (x){*b++=x%10+48;x/=10;}
		while (b--!=_buf)*o++=*b;
		if (c)*o++=c;
	}
	inline void print(char c){*o++=c;}
	inline void print(const char *s){while (*s)*o++=*s++;}
	inline void print(int a[],int n){
		print('[');
		for (int i=0;i<n;++i){
			print(a[i]);
			if (i==n-1)print("]\n");
			else print(',');
		}
	}
	inline void flush(FILE *fout=stdout){fwrite(_out,1,o-_out,fout); o=_out;}
	struct zzy{zzy(){read_init();}}zzy;
	struct zzy1{FILE *fout; zzy1(){fout=fopen("./user.out","w");} ~zzy1(){flush(fout);}}zzy1;
}
using namespace Read;

int edges1[N*N/2],edges2[N*N/2];
//main
int _main=[](){  //nasty trick
	while (1){
		if (!read_next_digit())break;
		int n,m; read(n);
		//vector<vector<int> > t=read_int_vec2D();
		read_int_arr2D(edges1,edges2,m);
		Solution A;
		print(A.minTrioDegree(n,m,edges1,edges2),'\n');
	}
	exit(0);
	return 0;
}();

