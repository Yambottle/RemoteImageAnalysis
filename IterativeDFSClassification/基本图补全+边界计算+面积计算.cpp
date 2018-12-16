#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#define max(a,b) a>b?a:b
#define min(a,b) a>b?b:a
typedef unsigned short us;
typedef unsigned char uc;//Points
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
	int sum,index;//边界和 同系列区块边界下标 
	char a,b;
	bool operator < (const areaedge c) const
	{
		if(a==c.a&&b==c.b) return index<c.index;
		else if(a==c.a&&b!=c.b) return b<c.b;
		else return a<c.a;
	}	
};
set<spot> map;//标记 每搜索完一块区域就清空 只留下egde（边界） 
set<spot>::iterator it1; 
set<verge> edge;//不动的边界 重点：双边界规则 
set<verge>::iterator it2; 
set<areaedge> sumv;//所求边界点 外扩边界为所求边界 内含边界为辅助限制边界 
set<areaedge>::iterator it3;  
set<bspot> bes;//预留起始点 
set<bspot>::iterator it4; 
int maxindex[100][100],deept,stx,sty,dep,deepp;//每一类的最大分割类数 
unsigned char la;
verge finv;
bspot finb;
areaedge fra,hea;

//Points
//compute 
FILE *flag;
bool isRead[2000][1000]={0};
int r[100]={0},g[100]={0},b[100]={0},y[100]={0};
int rNum=0,gNum=0,bNum=0,yNum=0;
int blockTotal=0,mapTotal=0;
int deep=0;
int stxP=0,styP=0;

bool dfs(int,int,int);//连续控制迭代dfs 
void insertbs(int,int,char,char);
void insertvd(int,int,char,char);
void insertmap(int,int); 
void prinorder();
void prinstart();
bool ifser(int,int);
bool ifser2(int,int);
bool ifser3(char,char);
//method
void readHeader();
void computeMap();
bool dfsPoints(int,int,uc);

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
	while(1)//头文件读取 
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
	
	ms=sample*line;//图分辨率
	
	fp1=fopen(name,"r");
	fpnew=fopen(newname,"w+");
	r=g=b=y=sp=0;
	

	for(i=0;i<line;i++)
	for(j=0;j<sample;j++)
	{
		if(j==0) stat=0;//首列重置 
		fread(&k,sizeof(k),1,fp1);
		if(!k&&!stat)//开头间隙处理 
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
	//通过辅助边界（内含边界）+外扩初始边界（预备初始点）+初始四向搜索+迭代八向搜索  来正确地执行深搜过程，并排除重复搜索。 
	for(it4=bes.begin();it4!=bes.end();)//预备起始点集选取 类似栈 
	{
		prinstart();
		finb=*it4; 
		printf("start: solu:%d %d  rela:%d %d\n",finb.x+3675,finb.y+2371,finb.a,finb.b);
		bes.erase(it4);//点集更新 
		map.clear();
		fseek(fpfs,finb.y*sample+finb.x,0);//指针设置 外扩边界上 
		fread(&qs,sizeof(qs),1,fpfs);
		fseek(fpfs,2,1);
		fread(&k,sizeof(k),1,fpfs);//右边 
		fseek(fpfs,-4,1);//原点 
		if(qs==k&&!ifser2(finb.x+3,finb.y))//相等说明属于同一块区 
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
			fseek(fpfs,-3,1);//左边 
			fread(&k,sizeof(k),1,fpfs);
			fseek(fpfs,2,1);//原点
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
				fseek(fpfs,3*sample,1);//下边 
				fread(&k,sizeof(k),1,fpfs);
				fseek(fpfs,-1-3*sample,1);//原点
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
					fseek(fpfs,-3*sample,1);//上边 
					fread(&k,sizeof(k),1,fpfs);
					fseek(fpfs,3*sample-1,1);//原点
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
					//没必要重置 
				}
			}
		}
		it4=bes.begin();//迭代器更新 
	}
	fclose(fpfs);
	prinorder();
	printf("------------------------------------------\n");
	printf("------------------------------------------\n");
	printf("Compute Points:\n");
	printf("------------------------------------------\n");
	computeMap();
    return 0;
}
bool dfs(int x,int y,int type)
{
	if(x<0||x>=sample-2||y<5||y>=line-5) return false;//首尾各删五行 控制x大小避免换行导致的错误 
	unsigned char k;
	if(ifser(x,y)) return false;//块标记 
	if(ifser2(x,y)) return false;//边界标记
	if(deept>10000) {stx=x,sty=y,deepp=type;return true;}//迭代深度控制 唯一的快速跳出迭代条件 
	fread(&k,sizeof(k),1,fpfs);
	fseek(fpfs,-1,1);
	deept++;
	
	stx=sty=0;//重复迭代起始点控制 
	
//	printf("now:%d %d %d %d\n",x+3675,y+2371,k,deept);
	if(k!=la)//边界点处理 
	{
		unsigned char l1,l2;
		l1=min(k,la);
		l2=max(k,la);
//		printf("edge spot:%d %d %d %d\n",x+3675,y+2371,l1,l2);
		if(!ifser3(l1,l2)&&sumv.count(fra)) maxindex[l1][l2]++;//起始点集里没有 但已存在于边和集中 且不存在于边集 说明此类点集已搜索过要更新最大下标 
		if(fra.b==-1)//初次边界点判定 
		{
			fra.a=l1;
			fra.b=l2;
			fra.sum=1;
			if(!maxindex[l1][l2]) maxindex[l1][l2]=1;
		}
		else
		{
			if(fra.a==l1&&fra.b==l2)//同类边界点判定 
			{
				fra.sum++;
			}
			else//非同类 
			{
				if((it3=sumv.find(fra))!=sumv.end())//已存在同类点 
				{
					areaedge f=*it3;
					fra.sum+=f.sum;//同类求和 
					sumv.erase(f);
					sumv.insert(fra);
				}
				else//不存在同类点 
				{
					sumv.insert(fra);
				}
				fra.a=l1;//当前临界点类型置换 
				fra.b=l2;
				fra.sum=1;
				if(!maxindex[l1][l2]) maxindex[l1][l2]=1;
				fra.index=maxindex[l1][l2];
			}
		}
		insertbs(x,y,l1,l2);
		insertvd(x,y,l1,l2);
		if(type==1) insertvd(x-1,y,l1,l2);//辅助边界 右 
		else if(type==2) insertvd(x-1,y-1,l1,l2);//辅助边界 右下 
		else if(type==3) insertvd(x,y-1,l1,l2);//辅助边界 下 
		else if(type==4) insertvd(x+1,y-1,l1,l2);//辅助边界 左下 
		else if(type==5) insertvd(x+1,y,l1,l2);//辅助边界 左 
		else if(type==6) insertvd(x+1,y+1,l1,l2);//辅助边界 左上 
		else if(type==7) insertvd(x,y+1,l1,l2);//辅助边界 上 
		else if(type==8) insertvd(x-1,y+1,l1,l2);//辅助边界 右上 
		return false;
	}
	la=k;
	insertmap(x,y); 
	//V1版本结果得知，4向搜索不足 
	fseek(fpfs,1,1);//右 
	if(dfs(x+1,y,1)) return true;
	fseek(fpfs,sample,1);//右下 
	if(dfs(x+1,y+1,2)) return true;
	fseek(fpfs,-1,1);//下 
	if(dfs(x,y+1,3)) return true;
	fseek(fpfs,-1,1);//左下 
	if(dfs(x-1,y+1,4)) return true;
	fseek(fpfs,-sample,1);//左 
	if(dfs(x-1,y,5)) return true;
	fseek(fpfs,-sample,1);//左上 
	if(dfs(x-1,y-1,6)) return true;
	fseek(fpfs,1,1);//上 
	if(dfs(x,y-1,7)) return true;
	fseek(fpfs,1,1);//右上 
	if(dfs(x+1,y-1,8)) return true;
	fseek(fpfs,sample-1,1);//重置回迭代起始位置 
	
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
		if(ou.sum>10) fprintf(newfi,"%d\t%d\t%d\t%d\n",ou.a,ou.b,ou.sum,ou.index);//约定边界大于10才能算边界 
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

//Points
void computeMap(){
	//compute
	flag=fopen(newname,"r");//与原先不同 
	int i,j;
	uc k;
	for(i=0;i<line-3;i++){
		for(j=0;j<sample;j++){
			//跳过已读 
			if(isRead[j][i])continue;
			//进行递归 
			fseek(flag,i*sample+j,0);
			fread(&k,sizeof(k),1,flag);
			fseek(flag,-1,1);
			stxP=j,styP=i;
			do{
				dfsPoints(stxP,styP,k);	
			}while(!(stxP==0&&styP==0));
			
			//记录块面积
			if(blockTotal<100)continue;
			mapTotal+=blockTotal; 
			if(k==1){
//				r[rNum]=blockTotal;
				rNum++;	
				printf("------------------------------------------\n");
				printf("R:%d->%d\n",rNum,blockTotal);
				printf("------------------------------------------\n");
				blockTotal=0;
			}else if(k==2){
//				g[gNum]=blockTotal;
				gNum++;
				printf("------------------------------------------\n");
				printf("G:%d->%d\n",gNum,blockTotal);
				printf("------------------------------------------\n");
				blockTotal=0;
			}else if(k==3){
//				b[bNum]=blockTotal;
				bNum++;
				printf("------------------------------------------\n");
				printf("B:%d->%d\n",bNum,blockTotal);
				printf("------------------------------------------\n");
				blockTotal=0;
			}else if(k==4){
//				y[yNum]=blockTotal;
				yNum++;
				printf("------------------------------------------\n");
				printf("Y:%d->%d\n",yNum,blockTotal);
				printf("------------------------------------------\n");
				blockTotal=0;
			}
		}
	}
	printf("%d",mapTotal);
	fclose(flag);
}

bool dfsPoints(int m,int n,uc c){//计算区域点数 
	//判断退出 
	if(m<0||n<0||m>sample-1||n>line-3)return false;
	if(isRead[m][n]==1)return false;
	if(deep>10000) {stxP=m,styP=n,deep=0;isRead[m][n]=0;return true;}
	//状态更新 
	deep++,stxP=0,styP=0,isRead[m][n]=1;
	//操作
	uc cNow;
	fseek(flag,n*sample+m,0);
	fread(&cNow,sizeof(cNow),1,flag);
	fseek(flag,-1,1);
	if(cNow!=c){
		return false;
	}else{
		blockTotal++;
	}
	//下次迭代 
	fseek(flag,1,1); 
	if(dfsPoints(m+1,n,cNow)) return true;//右
	fseek(flag,sample-1,1);
	if(dfsPoints(m,n+1,cNow)) return true;//下 
	fseek(flag,-sample-2,1); 
	if(dfsPoints(m-1,n,cNow)) return true;//左
	fseek(flag,-sample,1);
	if(dfsPoints(m,n-1,cNow)) return true;//上 
	fseek(flag,sample-1,1);//重置回迭代起始位置 
	
	return false;
}




