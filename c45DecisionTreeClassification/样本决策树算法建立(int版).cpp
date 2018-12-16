#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<set>
#include<vector>
#define gv "1"
using namespace std;
char strin[1000],fin[50];
struct news
{
	vector<int> atti;//��ͨ���� 
	int grandatti;//�������� 
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
vector<string> names;//���� 
vector<int> nas;//���������ܼ�(����) 
vector<news> sdata;//���ݼ� 
vector<set<int> > atset;//����ֵ�� 
set<int>::iterator it;
vector<multiset<int> > atsum,tatsum;//���Լ� ,��Ҫ���Լ� 
multiset<int>::iterator it2;
set<stype> gset;//�ؼ� 
set<stype>::iterator it3;
multiset<ixs>::iterator it4;
int tl,sl,rp,atype;//�������� ��Ŀ���� ���ڵ��±� �㷨���� 
stype root;//�ж����� 
set<int> ns;//��ά������ʼ������ֵ 
multiset<int> ns2;//��ά������ʼ������ֵ 
void judgetree();//�ж���
double cals(int,int);//�ؼ��� 
void decisiontree();//������ 
int atfind(string,vector<string>);//�������±���� 
int findnextp(vector<news>);//�¸��ݹ�������±����.   �¸��ݹ������ �¸��ݹ��ʣ�������� 
void prind();//������� 
void prins();//����� 
void dcrun(int,int,vector<news>);//���������ĵ��� param:�������±� ��� ���ݼ� 
int main()
{
	int i,j,k,l=0;
	FILE *fp;
	fp=fopen("data12.txt","rt"); 
//	printf("%lf %lf %lf\n",cals(9,14)+cals(5,14),cals(1,3)+cals(2,3),cals(10,17)+cals(7,17));
	string str;
	fgets(strin,1000,fp);
	while(~sscanf(strin+l,"%s",fin))
	{
		str=fin;
		l+=strlen(fin)+1;//���ֺ�ֻ��һ��/t 
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
		int fd;
		news nin;
		fgets(strin,1000,fp); 
		l=0;
		for(i=0;i<tl-1;i++)
		{
			sscanf(strin+l,"%d",&fd);
			if(isdigit(fin[0])) l+=strlen(fin)+1;//���ֺ�ֻ��һ��/t 
			else l+=strlen(fin)+2;//�ַ�������һ���ո�+/t 
//			printf("[%s]",fin);
			nin.atti.push_back(fd);
			atset[i].insert(fd);
			atsum[i].insert(fd);
		}
		sscanf(strin+l,"%s",fin);
//		printf("[%s]",fin);
		if(!strcmp(fin,gv))
		{
			for(i=0;i<tl-1;i++) tatsum[i].insert(nin.atti[i]);//���ڷ������ص�������˵�� 
		}
		nin.grandatti=fin;
		sdata.push_back(nin);
	}
	sl=sdata.size();
	printf("types sum : %d\ncolumn sum : %d\n",tl,sdata.size());
	printf("grand attributes sum:%d\n\n",tatsum[0].size());
	prind();
	printf("�������㷨ѡ�� ID3 : 0 C4.5 : 1\n");
	scanf("%d",&atype);
	if(atype!=0 && atype != 1){ printf("�������");return 0;}
	judgetree();
	prins();
//	decisiontree();
	fclose(fp); 
	return 0;
}
void judgetree()
{
	int i,sum=0,l,j,binsum,gbinsum,sum1=tatsum[0].size(),f;//sumΪĳ��ƫ�����ֵ����(��ƫ��gvΪ����) binsumΪ����ֵ��ɢ�����м�ֵ  
	stype in;
	string str,fstr;
	char fs[100];
	news pn;
	vector<int> val1,val2;
	set<string>::iterator fit;
	double ge;//C4.5������ 
	for(i=0;i<sl;i++)
	{
		if(!strcmp(sdata[i].grandatti.data(),gv)) sum++;
	}
	in.gain=cals(sum,sl)+cals(sl-sum,sl);//������ 
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
			for(j=0;j<l;j++)//������ 
			{
			in.gain-=val1[j]*1.0/sl*( cals(val2[j],val1[j]) + cals(val1[j]-val2[j],val1[j]) );//�Ӽ��� ֻ�����������ֵ
			ge+=cals(val1[j],sl);//C4.5������ 
			}
	//		printf("G : %lf\n",in.gain);
			if(atype==0) in.gain/=ge;
			gset.insert(in);
		}
		else
		{
			binsum=0;
			gbinsum=0;
			for(;it!=atset[i].end();l++,it++)
			{
				str=*it;
				in.gain=cals(sum,sl)+cals(sl-sum,sl);
				binsum+=atsum[i].count(str);
				gbinsum+=tatsum[i].count(str);
				in.gain=in.gain-binsum*1.0/sl*( cals(gbinsum,binsum) + cals(binsum-gbinsum,binsum) )
				-(sl-binsum)*1.0/sl*( cals(sum1-gbinsum,sl-binsum) + cals(sl-binsum-sum1+gbinsum,sl-binsum) );//�Ӽ��� ֻ�����������ֵ
				ge=cals(binsum,sl)+cals(sl-binsum,sl);//C4.5������ 
				printf("G : %lf names : %s line : %d\n",in.gain,str.data(),i);
				fit=it;
				fit++;
				if(fit!=atset[i].end()){
				fstr=*fit;
				f=(atoi(fstr.data())+atoi(str.data()))/2;
				itoa(f,fs,10);
				str=fs;
//				printf("[%d]\n",f);
				}
				in.name=names[i]+" "+str;
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
	it3=gset.begin();
	root=*it3;
	printf("root is :%s\n\n",root.name.data());
	nas=names;
	if( ( rp=atfind(root.name,names) ) > 0 )
	{
		dcrun(rp,1,sdata); 
		return;
	}
	else
	{
		printf("no enough attributes!\n");
		return;
	}
}
void dcrun(int p,int le,vector<news> data)
{
	if( nas.size()==0 || data.size()==0 ) { putchar('\n'); return; }//��������/���� ���յ��׼֮һ 
	if(p==-1) {printf(" ����> %s \n",data[0].grandatti.data());return;}//����ֵΨһ ���յ��׼֮�� 
//	printf("\n[%d %d]\n",p,le);
	int i,stree=0;
	string las;
	vector<news> nextd;
	multiset<ixs> indexs;//�±꼰���ƴ洢
	multiset<ixs>::iterator itix;
	ixs in; 
//	vector<multiset<string> > atsum,tatsum;
	for(i=0;i<data.size();i++)//ֵ���¼ 
	{
		in.p=i;
		in.value=data[i].atti[p];
		indexs.insert(in);
	}
	for(i=0;i<nas.size();i++)//ȥ�� 
	{
		if(nas[i]==names[p]){ nas.erase(nas.begin()+i); break;}
	}
	itix=indexs.begin();
	in=*itix;
	las=in.value;
	for(;itix!=indexs.end();itix++)//�������� 
	{
		in=*itix;
		if(las!=in.value)//ĳһֵ������� 
		{
			printf("����> level %d attribute: %s",le,las.data());
//			for(i=0;i<nextn.size();i++){if(nas[i]==names[p]){ nextn.erase(nextn.begin()+i); break;}}//ȥ�� 
			dcrun( findnextp(nextd), le+1, nextd);
			nextd.clear();
		}
		nextd.push_back(data[in.p]);//���ݲ��� 
		las=in.value;
	}
	printf("����> level %d attribute: %s",le,las.data());
//	for(i=0;i<nextn.size();i++){if(nextn[i]==names[p]){ nextn.erase(nextn.begin()+i); break;}}//ȥ�� 
	dcrun(findnextp(nextd),le+1,nextd); 
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
		if(ve[i]==name) return i;
	}
	return -1;
}
int findnextp(vector<news> data)
{
	//�����������Ƿ����һ�� ���к���������
	int i,flag=0,j,k,l;
	string lags=data[0].grandatti;
	vector<multiset<string> > fats,ftats;
	atset.clear();
	gset.clear();
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
			if(!strcmp(data[i].grandatti.data() , gv) )
			{
				ftats[j].insert(data[i].atti[k]);//�����������˵�� 
			}
		}
	} 
	if(!flag) return -1;
//	printf("flag=%d\n",flag);
	stype in;
	string str;
	double ge;
	vector<int> val1,val2;
	for(i=0;i<nas.size()-1;i++)
	{
		in.name=nas[i];
		val1.clear();
		val2.clear();
		in.gain=l=0;
		for(it=atset[i].begin();it!=atset[i].end();l++,it++)
		{
			str=*it;
			val1.push_back(fats[i].count(str) );
			val2.push_back(ftats[i].count(str) );
		}
		in.gain= cals(flag,data.size() ) + cals(data.size()-flag,data.size() );//������ 
		for(j=0;j<l;j++)//������ 
		{
			in.gain-=val1[j]*1.0/data.size()*( cals(val2[j],val1[j]) + cals(val1[j]-val2[j],val1[j]) );//�Ӽ��� ֻ�����������ֵ
			ge+=cals(val1[j],data.size() );//C4.5������ 
		}
//		printf("G : %lf\n",in.gain);
		if(atype==0) in.gain/=ge;
		gset.insert(in);
	}
//	prins();
	it3=gset.begin();
	in=*it3;
	printf(" [%s] ",in.name.data());
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
