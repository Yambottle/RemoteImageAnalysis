#include<cstdio>
#include<cstring>
#include<string>
#include<set>
#include<algorithm>
using namespace std;
set<string>::iterator it; 
int C45decisiontree(int,int,int);
int main()
{
	int i;
	string str;
	set<string> se;
	str="11";
	se.insert(str);
	str="22";
	se.insert(str);
	str="12";
	se.insert(str);
	for(it=se.begin();it!=se.end();it++)
	{
		str=*it;
		printf("%s\n",str.data());
	}
	str="B1 123";
	sscanf(str.data(),"%*s%d",&i);
	printf("%d\n",str=="12");
	printf("i=%d\n",i);
	return 0;
}
