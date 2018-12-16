#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<set>
#include<vector>
#define gv "2"//标记属性值设置 
using namespace std;
char strin[1000],fin[50];
struct news
{
	vector<string> atti;//普通属性 
	string grandatti;//核心属性 
};
struct ixs
{
	int p;
	string value;
	bool operator < (const ixs a) const
	{
		if(value==a.value) return p<a.p;
		else return value<a.value;
	}
};
struct stype
{
	string name;
	double gain;
	bool operator < (const stype a) const
	{
		if(fabs(gain-a.gain)<0.0001) return name>a.name;
		else return gain>a.gain;
	}
	bool operator == (const stype a) const
	{
		return name==a.name;
	}
};
vector<string> names;//类名 
vector<string> nas;//划分属性总集(共用) 
vector<news> sdata;//数据集 
vector<set<string> > atset;//属性值集 
set<string>::iterator it;
vector<multiset<string> > atsum,tatsum;//属性集 ,重要属性集 
multiset<string>::iterator it2;
set<stype> gset;//熵集 
set<stype>::iterator it3;
multiset<ixs>::iterator it4;
int tl,sl,rp,atype;//属性数量 条目数量 根节点下标 算法种类 
stype root;//判定树根 
set<string> ns;//二维容器初始化辅助值 
multiset<string> ns2;//二维容器初始化辅助值 
void judgetree();//判定树
double cals(int,int);//熵计算 
void decisiontree();//决策树 
int atfind(string,vector<string>);//属性列下标查找 
int findnextp(vector<news>);//下个递归的属性下标查找.   下个递归的数据 下个递归的剩余属性列 
void prind();//数据输出 
void prins();//熵输出 
void dcrun(int,int,vector<news>);//决策树核心迭代 param:属性列下标 层次 数据集 
int main()
{
	int i,j,k,l=0;
	FILE *fp;
	fp=fopen("data23.txt","rt"); 
//	printf("%lf %lf %lf\n",cals(9,14)+cals(5,14),cals(1,3)+cals(2,3),cals(10,17)+cals(7,17));
	string str;
	fgets(strin,1000,fp);
	while(~sscanf(strin+l,"%s",fin))
	{
		str=fin;
		if(isdigit(fin[strlen(fin)-1])) l+=strlen(fin)+1;//数字后只有一个/t 
		else l+=strlen(fin)+2;//字符串后有一个空格+/t 
		printf("[%s]",fin);
		names.push_back(str);
	}
	tl=names.size();
	for(i=0;i<tl;i++)
	{
		atset.push_back(ns);
		atsum.push_back(ns2);
		tatsum.push_back(ns2);
	}
	while(!feof(fp))
	{
		news nin;
		fgets(strin,1000,fp); 
		l=0;
		for(i=0;i<tl-1;i++)
		{
			sscanf(strin+l,"%s",fin);
			str=fin;
			if(isdigit(fin[strlen(fin)-1])) l+=strlen(fin)+1;//数字后只有一个/t 
			else l+=strlen(fin)+2;//字符串后有一个空格+/t 
//			printf("[%s]",fin);
			nin.atti.push_back(str);
			atset[i].insert(str);
			atsum[i].insert(str);
		}
		sscanf(strin+l,"%s",fin);
//		printf("[%s]",fin);
		if(!strcmp(fin,gv))
		{
			for(i=0;i<tl-1;i++) tatsum[i].insert(nin.atti[i]);//对于犯罪严重的人另行说明 
		}
		nin.grandatti=fin;
		sdata.push_back(nin);
	}
	sl=sdata.size();
	printf("\ntypes sum : %d\ncolumn sum : %d\n",tl,sdata.size());
	printf("grand attributes sum:%d\n\n",tatsum[0].size());
//	prind();
	printf("请输入算法选择 ID3 : 0 C4.5 : 1\n");
	scanf("%d",&atype);
	if(atype!=0 && atype != 1){ printf("输入错误！");return 0;}
	judgetree();
//	prins();
	decisiontree();
	fclose(fp); 
	return 0;
}
void judgetree()
{
	int i,sum=0,l,j,binsum,gbinsum,sum1=tatsum[0].size(),f,k,fk;//sum为某个偏向的类值总数(如偏向gv为严重) binsum为连续值离散化的中间值  
	stype in;
	string str;
	char fs[100];
	news pn;
	vector<int> val1,val2;
	set<int> intset;
	set<int>::iterator iit,fit;
	double ge;//C4.5额外熵 
	for(i=0;i<sl;i++)
	{
		if( sdata[i].grandatti==gv ) sum++;
	}
	in.gain=cals(sum,sl)+cals(sl-sum,sl);//样本熵 
	for(i=0;i<tl-1;i++)
	{
		in.name=names[i];
		val1.clear();
		val2.clear();
		in.gain=l=0;
		it=atset[i].begin();
		str=*it;
		if(!isdigit(str[0]))
		{
			for(;it!=atset[i].end();l++,it++)
			{
				str=*it;
				val1.push_back(atsum[i].count(str) );
				val2.push_back(tatsum[i].count(str) );
			}
			for(j=0;j<l;j++)//子类数 
			{
			in.gain-=val1[j]*1.0/sl*( cals(val2[j],val1[j]) + cals(val1[j]-val2[j],val1[j]) );//子集熵 只满足二极化的值
			ge+=cals(val1[j],sl);//C4.5额外熵 
			}
	//		printf("G : %lf\n",in.gain);
			if(atype==0) in.gain/=ge;
			gset.insert(in);
		}
		else
		{
			for(it=atset[i].begin();it!=atset[i].end();it++)//string 转 int 进行排序 
			{
				str=*it;
				intset.insert(atoi(str.data()));
			}
			binsum=0;
			gbinsum=0;
			for(iit=intset.begin();iit!=intset.end();l++,iit++)
			{
				k=*iit;
				itoa(k,fs,10);
				str=fs;
				in.gain=cals(sum,sl)+cals(sl-sum,sl);
				binsum+=atsum[i].count(str);
				gbinsum+=tatsum[i].count(str);
				in.gain=in.gain-binsum*1.0/sl*( cals(gbinsum,binsum) + cals(binsum-gbinsum,binsum) )
				-(sl-binsum)*1.0/sl*( cals(sum1-gbinsum,sl-binsum) + cals(sl-binsum-sum1+gbinsum,sl-binsum) );//子集熵 只满足二极化的值
				ge=cals(binsum,sl)+cals(sl-binsum,sl);//C4.5额外熵 
//				printf("G : %lf names : %s line : %d\n",in.gain,str.data(),i);
				fit=iit;
				fit++;
				if(fit!=intset.end()){
				fk=*fit;
				f=(k+fk)/2;
				itoa(f,fs,10);
				str=fs;
//				printf("[%d]\n",f);
				}
				in.name=names[i]+" "+str;//后缀为划分值 
//				in.name=names[i];
				if(atype==0) in.gain/=ge;
				gset.insert(in);
			}
		}
	}
	printf("I() : %lf\n\n",cals(sum,sl)+cals(sl-sum,sl));
	return;
}
void decisiontree()
{
	char fs[20];
	int i;
	it3=gset.begin();
	root=*it3;
	printf("root is :%s\n\n",root.name.data());
	nas=names;
	sscanf(root.name.data(),"%s%d",fs,&i);
	if(i)
	{
	root.name=fs;
	}
	printf("[%s]",root.name.data());
//	printf("names: %s %s %s %s",names[0].data(),names[1].data(),names[2].data(),names[3].data());
//	printf("if=%d\n",root.name==names[0]);
	if( ( rp=atfind(root.name,names) ) >= 0 )
	{
		dcrun(rp,1,sdata); 
		return;
	}
	else
	{
//		dcrun(0,1,sdata); 
		printf("no enough attributes!\n");
		return;
	}
}
void dcrun(int p,int le,vector<news> data)
{
	if(  data.size()==0 ) { putchar('\n'); return; }//无子数据 判终点标准之一 
	if(p==-1) {printf(" ——> %s \n",data[0].grandatti.data());return;}//属性值唯一 判终点标准之二 
	if( nas.size()==1  ) { putchar('\n'); return; }//无属性 判终点标准之一 
//	printf("\n[%d %d]\n",p,le);
	int i,stree=0,sum=0,l,j,binsum,gbinsum,sum1=tatsum[0].size(),f,k,fk;;
	string las;
	vector<news> nextd;
	multiset<ixs> indexs;//下标及名称存储
	multiset<ixs>::iterator itix;
	ixs in; 
//	vector<multiset<string> > atsum,tatsum;
	for(i=0;i<nas.size();i++)//去根 
	{
		if(nas[i]==names[p]){ nas.erase(nas.begin()+i); break;}
	}
	if(!isdigit(data[0].atti[p][0]))
	{
		for(i=0;i<data.size();i++)//值域记录 
		{
			in.p=i;
			in.value=data[i].atti[p];
			indexs.insert(in);
		}	
		itix=indexs.begin();
		in=*itix;
		las=in.value;
		for(;itix!=indexs.end();itix++)//子树划分 
		{
			in=*itix;
			if(las!=in.value)//某一值划分完毕 
			{
				printf("——> level %d attribute: %s",le,las.data());
	//			for(i=0;i<nextn.size();i++){if(nas[i]==names[p]){ nextn.erase(nextn.begin()+i); break;}}//去根 
				dcrun( findnextp(nextd), le+1, nextd);
				nextd.clear();
			}
			nextd.push_back(data[in.p]);//数据插入 
			las=in.value;
		}
		printf("——> level %d attribute: %s",le,las.data());
	//	for(i=0;i<nextn.size();i++){if(nextn[i]==names[p]){ nextn.erase(nextn.begin()+i); break;}}//去根 
		dcrun(findnextp(nextd),le+1,nextd); 
	}
	else//若属性为数字  则已存在熵排序 不需要再次排序 
	{
		stype st;
		vector<news> nextd2;
		it3=gset.begin();
		st=*it3;
		sscanf(st.name.data(),"%*s%d",&k);
//		printf(" huafen:%d ",k);
		for(i=0;i<data.size();i++)//string 转 int 进行排序 
		{
			if(atoi(data[i].atti[p].data())<=k)
			{
				nextd.push_back(data[i]);
			}
			else nextd2.push_back(data[i]);
		}
	//	for(i=0;i<nextn.size();i++){if(nextn[i]==names[p]){ nextn.erase(nextn.begin()+i); break;}}//去根 
		printf("——> level %d attribute: x<=%d size=%d ",le,k,nextd.size());
		dcrun(findnextp(nextd),le+1,nextd); 
		printf("——> level %d attribute: x>%d size=%d ",le,k,nextd2.size());
		dcrun(findnextp(nextd2),le+1,nextd2); 
	}
}
double cals(int a,int s)
{
	if(!a) return 0;
	return -(a*1.0*log(a*1.0/s)/s/log(2));
}
int atfind(string name,vector<string> ve)
{
	int i;
	for(i=0;i<ve.size();i++)
	{
//		printf("%s %s\n",name.data(),ve[i].data());
		if(ve[i]==name) return i;
	}
	return -1;
}
int findnextp(vector<news> data)
{
	//先判子数据是否归于一类 后判后序属性列
	int i,flag=0,j,k,l,binsum,gbinsum,f,fk;
	string lags=data[0].grandatti;
	vector<multiset<string> > fats,ftats;
	atset.clear();
	gset.clear();
	if(nas.size() <= 1) return -1;//无属性列自动退出 
	for(i=0;i<nas.size();i++)
	{
		fats.push_back(ns2);
		ftats.push_back(ns2);
		atset.push_back(ns);
	}
	for(i=0;i<data.size();i++)
	{
//		printf("\n");
		if(lags!=data[i].grandatti) flag++;
		for(k=j=0;j<nas.size()-1;j++)
		{
			while(names[k]!=nas[j]) k++;
//			printf("%s ",data[i].atti[k].data());
			fats[j].insert(data[i].atti[k]);
			atset[j].insert(data[i].atti[k]);
			if( data[i].grandatti==gv )
			{
				ftats[j].insert(data[i].atti[k]);//标记属性另作说明 
			}
		}
	} 
	if(!flag) return -1;
//	printf("flag=%d\n",flag);
	stype in,st;
	string str,fstr;
	double ge;
	vector<int> val1,val2;
	set<int> intset;
	set<int>::iterator iit,fit;
	char fs[20];
	int sum1=ftats[0].size();
	for(i=0;i<nas.size()-1;i++)
	{
		in.name=nas[i];
		val1.clear();
		val2.clear();
		l=0;
		in.gain= cals(flag,data.size() ) + cals(data.size()-flag,data.size() );//样本熵 
		it=atset[i].begin();
		str=*it;
		if(!isdigit(str[0]))
		{
		for(;it!=atset[i].end();l++,it++)
		{
			str=*it;
			val1.push_back(fats[i].count(str) );
			val2.push_back(ftats[i].count(str) );
		}
		for(j=0;j<l;j++)//子类数 
		{
			in.gain-=val1[j]*1.0/data.size()*( cals(val2[j],val1[j]) + cals(val1[j]-val2[j],val1[j]) );//子集熵 只满足二极化的值
			ge+=cals(val1[j],data.size() );//C4.5额外熵 
		}
//		printf("G : %lf\n",in.gain);
		if(atype==0) in.gain/=ge;
		gset.insert(in);
		}
		else
		{
			for(;it!=atset[i].end();l++,it++)//string 转 int 进行排序 
			{
				str=*it;
				intset.insert(atoi(str.data()));
			}
			binsum=0;
			gbinsum=0;
			for(iit=intset.begin();iit!=intset.end();iit++)
			{
				k=*iit;
				itoa(k,fs,10);
				str=fs;
				in.gain= cals(flag,data.size() ) + cals(data.size()-flag,data.size() );//样本熵 
				binsum+=fats[i].count(str);
				gbinsum+=ftats[i].count(str);
				in.gain=in.gain-binsum*1.0/data.size()*( cals(gbinsum,binsum) + cals(binsum-gbinsum,binsum) )
				-(data.size()-binsum)*1.0/data.size()*( cals(sum1-gbinsum,data.size()-binsum) + cals(data.size()-binsum-sum1+gbinsum,data.size()-binsum) );//子集熵 只满足二极化的值
				ge=cals(binsum,data.size())+cals(data.size()-binsum,data.size());//C4.5额外熵 
	//				printf("G : %lf names : %s line : %d\n",in.gain,str.data(),i);
				fit=iit;
				fit++;
				if(fit!=intset.end()){
				fk=*fit;
				f=(k+fk)/2;
				itoa(f,fs,10);
				str=fs;
	//			printf("[%d]\n",f);
				}
				in.name=names[i]+" "+str;//后缀为划分值 
	//			in.name=names[i];
				if(atype==0) in.gain/=ge;
				gset.insert(in);
			}
		}
	}
//	prins();
	it3=gset.begin();
	in=*it3;
	printf(" [%s] ",in.name.data());
	if(isdigit(str[0]))
	{
		sscanf(in.name.data(),"%s%*d",fs);
		in.name=fs;
	}
	return atfind(in.name,names);
}
void prins()
{
	stype pin;
	for(it3=gset.begin();it3!=gset.end();it3++)
	{
		pin=*it3;
		printf("%s %lf\n",pin.name.data(),pin.gain);
	}
}
void prind()
{
	int i,j,sum;
	string str;
	for(sum=i=0;i<sl-1;i++)
	{
		if(sum<100)
		{
			if(sdata[i].atti[0]>"32")
			{
				sum++;
				for(j=0;j<tl-1;j++)
				{
				printf("%s ",sdata[i].atti[j].data());
				}
				printf("%s\n",sdata[i].grandatti.data());
			}
		}
	}
	for(i=0;i<tl-1;i++)
	{
		printf("%s :\n",names[i].data());
		for(it=atset[i].begin();it!=atset[i].end();it++)
		{
			str=*it;
			printf("%s sum:%d grand:%d\n",str.data(),atsum[i].count(str),tatsum[i].count(str));
		}
	}
}
