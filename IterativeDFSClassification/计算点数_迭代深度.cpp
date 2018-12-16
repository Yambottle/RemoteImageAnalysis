#include<stdio.h>
#include<stdlib.h>
#include<cstring>

using namespace std;
typedef unsigned char uc;
//read hdr
int sample,line,ms;
char hdr[10000],*fs;
char name[100]="2002ClassImageFill";
//compute
FILE *flag;
bool isRead[2000][1000]={0};
int r[100]={0},g[100]={0},b[100]={0},y[100]={0};
int rNum=0,gNum=0,bNum=0,yNum=0;
int blockTotal=0,mapTotal=0;
int deep=0;
int stx=0,sty=0;
//method
void readHeader();
void computeMap();
bool dfs(int,int,uc);

int main(){
	readHeader();
	computeMap();
	return 0;
}

void computeMap(){
	//compute
	flag=fopen(name,"r");
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
			stx=j,sty=i;
			do{
				dfs(stx,sty,k);	
			}while(!(stx==0&&sty==0));
			
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

bool dfs(int m,int n,uc c){//计算区域点数 
	//判断退出 
	if(m<0||n<0||m>sample-1||n>line-3)return false;
	if(isRead[m][n]==1)return false;
	if(deep>10000) {stx=m,sty=n,deep=0;isRead[m][n]=0;return true;}
	//状态更新 
	deep++,stx=0,sty=0,isRead[m][n]=1;
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
	if(dfs(m+1,n,cNow)) return true;//右
	fseek(flag,sample-1,1);
	if(dfs(m,n+1,cNow)) return true;//下 
	fseek(flag,-sample-2,1); 
	if(dfs(m-1,n,cNow)) return true;//左
	fseek(flag,-sample,1);
	if(dfs(m,n-1,cNow)) return true;//上 
	fseek(flag,sample-1,1);//重置回迭代起始位置 
	
	return false;
}

void readHeader(){
	
	FILE *fp;
	
	fp=fopen("2002ClassImageFill.hdr","rt");
	while(1)
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
	ms=sample*line;
}


