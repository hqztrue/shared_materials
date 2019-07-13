#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<set>
using namespace std;
set<string> S;
char s[105];
inline bool isnum(char c){return c>='0'&&c<='9';}
int main()
{
	system("file.bat");
	freopen("file.txt","r",stdin);
	freopen("solved.txt","w",stdout);
	while (gets(s))
		if (isnum(s[0])&&isnum(s[1])&&isnum(s[2])&&isnum(s[3]))
			S.insert(string("")+s[0]+s[1]+s[2]+s[3]);
	int cnt=0;
	for (set<string>::iterator zzy=S.begin();zzy!=S.end();++zzy){
		cout<<"p("<<*zzy<<") ";if (++cnt%10==0)cout<<endl;
	}
	//system("pause");for (;;);
	return 0;
}


