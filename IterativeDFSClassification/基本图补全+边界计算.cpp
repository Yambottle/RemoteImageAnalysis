#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#define max(a,b) a>b?a:b
#define min(a,b) a>b?b:a
typedef unsigned short us;
using namespace std;
int sample,line,ms;
char hdr[10000],*fs;
char name[100]="2002ClassImage";
char newname[100]="2002ClassImageFill";
char orderout[100]="order2002.txt";
struct spot
{
	int x,y;
	bool operator < (const spot a) const
	{
		if(x==a.x) return y<a.y;
		else return x<a.x;
	}
};
struct bspot
{
	int x,y;
	char a,b;
	bool operator < (const bspot c) const
	{
		if(a==c.a) return b<c.b;
		else return a<c.a;
	}
};
struct verge
{
	int x,y;
	char a,b;
	bool operator < (const verge c) const
	{
		if(x==c.x) return y<c.y;
		else return x<c.x;
	}
};
struct areaedge
{
	int sum,index;//�߽�� ͬϵ������߽��±� 
	char a,b;
	bool operator < (const areaedge c) const
	{
		if(a==c.a&&b==c.b) return index<c.index;
		else if(a==c.a&&b!=c.b) return b<c.b;
		else return a<c.a;
	}	
};
set<spot> map;//��� ÿ������һ���������� ֻ����egde���߽磩 
set<spot>::iterator it1; 
set<verge> edge;//�����ı߽� �ص㣺˫�߽���� 
set<verge>::iterator it2; 
set<areaedge> sumv;//����߽�� �����߽�Ϊ����߽� �ں��߽�Ϊ�������Ʊ߽� 
set<areaedge>::iterator it3;  
set<bspot> bes;//Ԥ����ʼ�� 
set<bspot>::iterator it4; 
int maxindex[100][100],deept,stx,sty,dep,deepp;//ÿһ������ָ����� 
unsigned char la;
verge finv;
bspot finb;
areaedge fra,hea;
bool dfs(int,int,int);//�������Ƶ���dfs 
void insertbs(int,int,char,char);
void insertvd(int,int,char,char);
void insertmap(int,int); 
void prinorder();
void prinstart();
bool ifser(int,int);
bool ifser2(int,int);
bool ifser3(char,char);
FILE *fpfs;
int main()
{
	int i,j,r,g,b,y,sp,lr,flag;
	unsigned char k,stat=1,fk;
	FILE *fp,*fp1,*fpnew;
	verge ve;
	areaedge ar;
	bspot bs;
	fp=fopen("2002ClassImage.hdr","rt");
	while(1)//ͷ�ļ���ȡ 
	{
	fgets(hdr,10000,fp);
	if(strstr(hdr,"samples")!=NULL)
	{
	fs=strtok(hdr," ");
	fs=strtok(NULL," ");
	fs=strtok(NULL," ");
	sscanf(fs,"%d",&sample);
	fgets(hdr,10000,fp);
	fs=strtok(hdr," ");
	fs=strtok(NULL," ");
	fs=strtok(NULL," ");
	sscanf(fs,"%d",&line);
	fclose(fp);
	break;
	}
	}
	
	ms=sample*line;//ͼ�ֱ���
	
	fp1=fopen(name,"r");
	fpnew=fopen(newname,"w+");
	r=g=b=y=sp=0;
	

	for(i=0;i<line;i++)
	for(j=0;j<sample;j++)
	{
		if(j==0) stat=0;//�������� 
		fread(&k,sizeof(k),1,fp1);
		if(!k&&!stat)//��ͷ��϶���� 
		{
			stat=0;
			lr=0;
			fk=k;
			flag=1;
			while(!fk)
			{
				fread(&fk,sizeof(k),1,fp1);
				lr++;
				if(feof(fp1)) {flag=0;break;
				}
			}
			if(!flag){fk=0;fwrite(&fk,1,lr,fpnew);i=line;break;
			}
			stat=fk;
			fseek(fp1,-lr,1);
		}
		if(!k&&stat)
		{
			fwrite(&stat,1,1,fpnew);
		}
		if(k)
		{
			fwrite(&k,1,1,fpnew);
			stat=k;
		}
	}

	fclose(fp1);
	fclose(fpnew);
	
	fpfs=fopen(newname,"r");
	
	//dfs
	{
		finv.x=4040;
		finv.y=2589;
		finv.a=1;
		finv.b=3;
		edge.insert(finv);
	}
	spot fsp;
	unsigned char qs;
	fseek(fpfs,sample*5,0);
	fread(&k,sizeof(k),1,fpfs);
	fseek(fpfs,-1,1);
	la=fra.a=k;
	fra.index=1;
	fra.sum=0;
	fra.b=-1;
	stx=0,sty=0;
	memset(maxindex,0,sizeof(maxindex));
	printf("start:%d\n",k);
	dfs(0,5,0);
	while(!(stx==0&&sty==0))
	{
		deept=0;
		fseek(fpfs,stx+sty*sample,0);
		dfs(stx,sty,deepp);
	}
//	return 0;
	deept=0;
	//ͨ�������߽磨�ں��߽磩+������ʼ�߽磨Ԥ����ʼ�㣩+��ʼ��������+������������  ����ȷ��ִ�����ѹ��̣����ų��ظ������� 
	for(it4=bes.begin();it4!=bes.end();)//Ԥ����ʼ�㼯ѡȡ ����ջ 
	{
		prinstart();
		finb=*it4; 
		printf("start: solu:%d %d  rela:%d %d\n",finb.x+3675,finb.y+2371,finb.a,finb.b);
		bes.erase(it4);//�㼯���� 
		map.clear();
		fseek(fpfs,finb.y*sample+finb.x,0);//ָ������ �����߽��� 
		fread(&qs,sizeof(qs),1,fpfs);
		fseek(fpfs,2,1);
		fread(&k,sizeof(k),1,fpfs);//�ұ� 
		fseek(fpfs,-4,1);//ԭ�� 
		if(qs==k&&!ifser2(finb.x+3,finb.y))//���˵������ͬһ���� 
		{
			fseek(fpfs,3,1);
			la=k;
			dfs(finb.x+3,finb.y,0);
			while(!(stx==0&&sty==0))
			{
				deept=0;
				fseek(fpfs,stx+sty*sample,0);
				dfs(stx,sty,deepp);
			}
		}
		else
		{
			fseek(fpfs,-3,1);//��� 
			fread(&k,sizeof(k),1,fpfs);
			fseek(fpfs,2,1);//ԭ��
			if(qs==k&&!ifser2(finb.x-3,finb.y))
			{
				fseek(fpfs,-3,1);
				la=k;
				dfs(finb.x-3,finb.y,0);
				while(!(stx==0&&sty==0))
				{
					deept=0;
					fseek(fpfs,stx+sty*sample,0);
					dfs(stx,sty,deepp);
				}
			}
			else
			{
				fseek(fpfs,3*sample,1);//�±� 
				fread(&k,sizeof(k),1,fpfs);
				fseek(fpfs,-1-3*sample,1);//ԭ��
				if(qs==k&&!ifser2(finb.x,finb.y+3))
				{
					fseek(fpfs,3*sample,1);
					la=k;
					dfs(finb.x,finb.y+3,0);
					while(!(stx==0&&sty==0))
					{
						deept=0;
						fseek(fpfs,stx+sty*sample,0);
						dfs(stx,sty,deepp);
					}
				}
				else
				{
					fseek(fpfs,-3*sample,1);//�ϱ� 
					fread(&k,sizeof(k),1,fpfs);
					fseek(fpfs,3*sample-1,1);//ԭ��
					if(qs==k&&!ifser2(finb.x,finb.y-3))
					{
						fseek(fpfs,-3*sample,1);
						la=k;
						dfs(finb.x,finb.y-3,0);
						while(!(stx==0&&sty==0))
						{
							deept=0;
							fseek(fpfs,stx+sty*sample,0);
							dfs(stx,sty,deepp);
						}
					}
					//û��Ҫ���� 
				}
			}
		}
		it4=bes.begin();//���������� 
	}
	fclose(fpfs);
	prinorder();
    return 0;
}
bool dfs(int x,int y,int type)
{
	if(x<0||x>=sample-2||y<5||y>=line-5) return false;//��β��ɾ���� ����x��С���⻻�е��µĴ��� 
	unsigned char k;
	if(ifser(x,y)) return false;//���� 
	if(ifser2(x,y)) return false;//�߽���
	if(deept>10000) {stx=x,sty=y,deepp=type;return true;}//������ȿ��� Ψһ�Ŀ��������������� 
	fread(&k,sizeof(k),1,fpfs);
	fseek(fpfs,-1,1);
	deept++;
	
	stx=sty=0;//�ظ�������ʼ����� 
	
//	printf("now:%d %d %d %d\n",x+3675,y+2371,k,deept);
	if(k!=la)//�߽�㴦�� 
	{
		unsigned char l1,l2;
		l1=min(k,la);
		l2=max(k,la);
//		printf("edge spot:%d %d %d %d\n",x+3675,y+2371,l1,l2);
		if(!ifser3(l1,l2)&&sumv.count(fra)) maxindex[l1][l2]++;//��ʼ�㼯��û�� ���Ѵ����ڱߺͼ��� �Ҳ������ڱ߼� ˵������㼯��������Ҫ��������±� 
		if(fra.b==-1)//���α߽���ж� 
		{
			fra.a=l1;
			fra.b=l2;
			fra.sum=1;
			if(!maxindex[l1][l2]) maxindex[l1][l2]=1;
		}
		else
		{
			if(fra.a==l1&&fra.b==l2)//ͬ��߽���ж� 
			{
				fra.sum++;
			}
			else//��ͬ�� 
			{
				if((it3=sumv.find(fra))!=sumv.end())//�Ѵ���ͬ��� 
				{
					areaedge f=*it3;
					fra.sum+=f.sum;//ͬ����� 
					sumv.erase(f);
					sumv.insert(fra);
				}
				else//������ͬ��� 
				{
					sumv.insert(fra);
				}
				fra.a=l1;//��ǰ�ٽ�������û� 
				fra.b=l2;
				fra.sum=1;
				if(!maxindex[l1][l2]) maxindex[l1][l2]=1;
				fra.index=maxindex[l1][l2];
			}
		}
		insertbs(x,y,l1,l2);
		insertvd(x,y,l1,l2);
		if(type==1) insertvd(x-1,y,l1,l2);//�����߽� �� 
		else if(type==2) insertvd(x-1,y-1,l1,l2);//�����߽� ���� 
		else if(type==3) insertvd(x,y-1,l1,l2);//�����߽� �� 
		else if(type==4) insertvd(x+1,y-1,l1,l2);//�����߽� ���� 
		else if(type==5) insertvd(x+1,y,l1,l2);//�����߽� �� 
		else if(type==6) insertvd(x+1,y+1,l1,l2);//�����߽� ���� 
		else if(type==7) insertvd(x,y+1,l1,l2);//�����߽� �� 
		else if(type==8) insertvd(x-1,y+1,l1,l2);//�����߽� ���� 
		return false;
	}
	la=k;
	insertmap(x,y); 
	//V1�汾�����֪��4���������� 
	fseek(fpfs,1,1);//�� 
	if(dfs(x+1,y,1)) return true;
	fseek(fpfs,sample,1);//���� 
	if(dfs(x+1,y+1,2)) return true;
	fseek(fpfs,-1,1);//�� 
	if(dfs(x,y+1,3)) return true;
	fseek(fpfs,-1,1);//���� 
	if(dfs(x-1,y+1,4)) return true;
	fseek(fpfs,-sample,1);//�� 
	if(dfs(x-1,y,5)) return true;
	fseek(fpfs,-sample,1);//���� 
	if(dfs(x-1,y-1,6)) return true;
	fseek(fpfs,1,1);//�� 
	if(dfs(x,y-1,7)) return true;
	fseek(fpfs,1,1);//���� 
	if(dfs(x+1,y-1,8)) return true;
	fseek(fpfs,sample-1,1);//���ûص�����ʼλ�� 
	
	return false;
} 
void insertbs(int x,int y,char a,char b)
{
	bspot in;
	in.a=a;
	in.b=b;
	in.x=x;
	in.y=y;
	bes.insert(in);
	return;
}
void insertvd(int x,int y,char a,char b)
{
	verge in;
	in.a=a;
	in.b=b;
	in.x=x;
	in.y=y;
	edge.insert(in);
	return;
}
void insertmap(int x,int y)
{
	spot in;
	in.x=x;
	in.y=y;
	map.insert(in);
	return;
}
void prinorder()
{
	FILE *newfi=fopen(orderout,"wt+");
	areaedge ou;
	fprintf(newfi,"type 1\ttype 2\tsum\tclass index\n");
	for(it3=sumv.begin();it3!=sumv.end();it3++)
	{
		ou=*it3;
		if(ou.sum>10) fprintf(newfi,"%d\t%d\t%d\t%d\n",ou.a,ou.b,ou.sum,ou.index);//Լ���߽����10������߽� 
	}
	fclose(newfi);
}
void prinstart()
{
	set<bspot>::iterator fit;
	bspot fou;
	if(dep++>50) return;
	for(fit=bes.begin();fit!=bes.end();fit++)
	{
		fou=*fit;
		printf("solu:%d %d  rela:%d %d\n",fou.x+3675,fou.y+2371,fou.a,fou.b);
	} 
	putchar('\n');
	return;
}
bool ifser(int x,int y)
{
	spot in;
	in.x=x;
	in.y=y;
	if(map.count(in)) return true;
	return false;
}
bool ifser2(int x,int y)
{
	verge in;
	in.x=x;
	in.y=y;
	if(edge.count(in)) return true;
	return false;
}
bool ifser3(char a,char b)
{
	bspot in;
	in.a=a;
	in.b=b;
	if(bes.count(in)) return true;
	return false;
}





