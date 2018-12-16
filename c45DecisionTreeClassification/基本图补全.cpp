#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
typedef unsigned short us;
using namespace std;
int sample,line,ms;
char hdr[10000],*fs;
char name[100]="2006ClassImage";
char newname[100]="2006ClassImageFill";
FILE *fpfs;
int main()
{
	int i,j,r,g,b,y,sp,lr,flag;
	unsigned char k,stat=1,fk;
	FILE *fp,*fp1,*fpnew;
	spot sp;
	verge ve;
	areaedge ar;
	bspot bs;
	fp=fopen("2006ClassImage.hdr","rt");
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
	

	for(i=0;i<line;i++)//需要三个文件指针一起处理 
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
	
	
    return 0;
}




