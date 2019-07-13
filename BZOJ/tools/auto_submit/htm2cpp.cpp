#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
#define J (")
#define N 100005
string name;
char S[N][1005];
bool equal(char *s,char *s1){
	int l=strlen(s1);
	for (int i=0;i<l;++i){
		char c1=s[i],c2=s1[i];
		if (c1>='A'&&c1<='Z')c1+='a'-'A';
		if (c2>='A'&&c2<='Z')c2+='a'-'A';
		if (c1!=c2)return 0;
	}
	return 1;
}
int main()
{
	system("md sol");
	system("echo Y|del sol\\*.*");
	freopen("1.txt","r",stdin);
	int len=0;
	while (gets(S[len]))++len;
	for (int i1=0;i1<len;++i1){
		char *s=S[i1];
		if (equal(s,"Problem")){
			fclose(stdout);
			name=string("sol\\")+s[7]+s[8]+s[9]+s[10];
			int next;for (next=i1+1;next<=len;++next)if (S[next][0]!=0)break;
			if (equal(S[next],"import"))name+=".java";
			else if (equal(S[next],"#include"))name+=".cpp";
			else if (equal(S[next],"var")||equal(S[next],"const")||equal(S[next],"program"))name+=".pas";
			else name+=".py";
			freopen(name.c_str(),"w",stdout);
		}
		else if (s[0])printf("%s\n",s);
	}
	fclose(stdout);
	//system("pause");for (;;);
	return 0;
}


