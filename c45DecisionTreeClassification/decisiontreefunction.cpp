#include<cstdio>
unsigned char decisiontree(unsigned char,unsigned char,unsigned char);
int main()
{
	FILE *fp1,*fp2,*fp3,*fpnew;
	int sample=1440,line=813,ms,i,j;
	unsigned char k,nk,r,g,b;
	ms=sample*line;
	fp1=fopen("HJ1A-CCD2-450-72-20091015.img","rt+");
	fp2=fopen("HJ1A-CCD2-450-72-20091015.img","rt+");
	fp3=fopen("HJ1A-CCD2-450-72-20091015.img","rt+");
	fpnew=fopen("orderimg.img","wt+");
	fseek(fp2,ms,1);
	fseek(fp3,ms*2,1);
	for(i=0;i<line;i++)
	for(j=0;j<sample;j++)
	{
		fread(&r,1,1,fp1);
		fread(&g,1,1,fp2);
		fread(&b,1,1,fp3);
		nk=decisiontree(r,g,b);
		fwrite(&nk,1,1,fpnew);
//		if(i<50 && j<50) printf("[%d %d %d] ",i,j,nk);
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fpnew);
}
unsigned char decisiontree(unsigned char r,unsigned char g,unsigned char b)
{
	if(g<=133)//13
	{
		if(r<=74) return 1;
		else return 3;
	}
	else//23
	{
		if(b<173)
		{
			if(g<=133) return 3;
			else
			{
				if(r>196) return 3;
				else//�������޷��ֱ���Щ�� ռ 58/18715 
				{
					return 4;
				}
			}
		}
		else
		{
			return 2;
		}
	}
}
//1 2 ���� B2 <=133 1 >133 2
//1 3 ���� B1 <=74 1 >=74 3
//2 3 ���� B3 <173 B2 <=133 3 >133 B1 <=196 (13��2 45��45)
//>196 3(ȥ�����ŵ�����)
//B3 >173 2
