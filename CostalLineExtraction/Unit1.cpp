//---------------------------------------------------------------------------

#include <vcl.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define x 386*3
#define y 398
using namespace std;

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    //求差---------------------------------
    FILE *fp;
    short int t;
    int cha[3];
    int min[3];
    int count=0;
    int sum;

    fp=fopen("D:\\Documents\\Downloads\\海岸线提取\\SeaSide\\exsample400-400","rb");
    while(count<3){
        sum=307254;
        fread(&t,sizeof(t),1,fp);
        short int max=t,mi=t;
    while(sum-=2){
        fread(&t,sizeof(t),1,fp);
        cha[count]=max-mi;
        if(t>max)
                {cha[count]=t-mi;max=t;}
        if(t<mi)
                {cha[count]=max-t;mi=t;min[count]=t;}
    }
    count++;
    }
    fclose(fp);
    /*while(count--)
    Memo1->Lines->Add(IntToStr(cha[count]));*///输出检测差
    //---------------------------------------------------
    //放图-----------------------------------------------
    FILE *R,*B,*G;
    R=fopen("D:\\Documents\\Downloads\\海岸线提取\\SeaSide\\exsample400-400","rb");
    G=fopen("D:\\Documents\\Downloads\\海岸线提取\\SeaSide\\exsample400-400","rb");
    fseek(G,x/3*y*2,1);
    B=fopen("D:\\Documents\\Downloads\\海岸线提取\\SeaSide\\exsample400-400","rb");
    fseek(B,x/3*y*4,1);
    int i,j;
    short int r,g,b;
    Image1->Canvas->Pen->Style=psSolid;
    Image1->Canvas->MoveTo(1,1);
    for(i=1;i<=x/3;i++,Image1->Canvas->MoveTo(1,i)){
    for(j=1;j<=y;j++){
    fread(&r,sizeof(r),1,R);
    fread(&g,sizeof(g),1,G);
    fread(&b,sizeof(b),1,B);
    Image1->Canvas->Pen->Color=TColor(RGB(
    ((r-min[0])*1.0/cha[0]*255),
    ((g-min[1])*1.0/cha[1]*255),
    ((b-min[2])*1.0/cha[2]*255)));
    Image1->Canvas->Pen->Width=1;
    Image1->Canvas->LineTo(j,i);
    }
    }
    /*
    if(b<11000){
    Image1->Canvas->Pen->Color=TColor(RGB(
    ((r-min[0])*1.0/cha[0]*255),
    ((g-min[1])*1.0/cha[1]*255),
    ((b-min[2])*1.0/cha[2]*255)));}
    else{
    Image1->Canvas->Pen->Color=TColor(RGB(255,255,255));
    }
    */
    //---------------------------------------------------
    /*读数-----------------------------------------------
    short int r;
    fp=fopen("D:\\Documents\\Downloads\\hanyx\\exsample400-400","rb");
    //
    fread(&r,sizeof(r),1,fp);
    //Memo1->Lines->Add(IntToStr(r));
    short int rmax=r;
    int c=0;
    while(c<=153628)
    {
     fread(&r,sizeof(r),1,fp);
     if(rmax<r)
        {rmax=r;
         c++;}
     else
         c++;
    }
    Memo1->Lines->Add(IntToStr(rmax));

    short int rmin=r;
    int c=0;
    while(c<=153628)
    {
     fread(&r,sizeof(r),1,fp);
     if(rmin>r)
        {rmin=r;
         c++;}
     else
         c++;
    }
    Memo1->Lines->Add(IntToStr(rmin)); */
    //



    /*fseek(fp,307254,1);
    fread(&b,sizeof(b),1,fp);
    Memo1->Lines->Add(IntToStr(b));

    fseek(fp,307254,1);
    fread(&g,sizeof(g),1,fp);
    Memo1->Lines->Add(IntToStr(g));*/
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
    //---------------------------------------------------
    //放大-----------------------------------------------
    //int x=386*3,y=398;
    short int all[x*2][y*2];
    short int f;
    //放大
    int i=0,j,z;
    FILE *fp;
    fp=fopen("D:\\Documents\\Downloads\\hanyx\\SeaSide\\exsample400-400","rb");
    for(z=0,i=0,j=0;z<x*y;j+=2,z++){
    fread(&f,sizeof(f),1,fp);
    all[i][j]=f;
    if(j==y*2-2){
    i+=2;
    j=0;
    }
    }
    fclose(fp);
    //填充
    for(z=0,i=0,j=0;z<x*y;j+=2,z++){
    if(i=x*2-2){
    all[i][j+1]=(all[i][j]+all[i][j+2])/2;
    }
    else{
    all[i][j+1]=(all[i][j]+all[i][j+2])/2;
    all[i+1][j]=(all[i][j]+all[i+2][j])/2;
    all[i+1][j+1]=(all[i][j]+all[i+2][j+2])/2;
    }
    if(j==y*2-1){
    i+=2;
    j=0;
    }
    }
    //放图
    short int t;
    int cha[3];
    int min[3];
    int count=0;
    int sum;
    fp=fopen("D:\\Documents\\Downloads\\hanyx\\SeaSide\\exsample400-400","rb");
    while(count<3){
        sum=x/3*y*4-2; ////////
        fread(&t,sizeof(t),1,fp);
        short int max=t,mi=t;
    while(sum-=2){
        fread(&t,sizeof(t),1,fp);
        cha[count]=max-mi;
        if(t>max)
                {cha[count]=t-mi;max=t;}
        if(t<mi)
                {cha[count]=max-t;mi=t;min[count]=t;}
    }
    count++;
    }
    fclose(fp);

    short int r,g,b;
    Image1->Picture->Assign(NULL);
    Image1->Canvas->Pen->Style=psSolid;
    Image1->Canvas->MoveTo(1,1);
    for(i=0;i<=x/6;i++,Image1->Canvas->MoveTo(1,i)){
    for(j=0;j<=y/2;j++){
    r=all[i][j];
    g=all[i+x/6][j];
    b=all[i+x/3][j];
    Image1->Canvas->Pen->Color=TColor(RGB(
    ((r-min[0])*1.0/cha[0]*255),
    ((g-min[1])*1.0/cha[1]*255),
    ((b-min[2])*1.0/cha[2]*255)));
    Image1->Canvas->Pen->Width=1;
    Image1->Canvas->LineTo(j,i);
    }
    }

}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
    //---------------------------------------------------
    //缩小-----------------------------------------------
    //int x=386*3,y=398;
    short int all[x/2][y/2];
    short int f,s;
    //列缩
    short int hang[x][y/2];
    int i=0,j,z;
    FILE *fp;
    fp=fopen("D:\\Documents\\Downloads\\hanyx\\SeaSide\\exsample400-400","rb");
    for(z=0,i=0,j=0;z<x*y/2;j++,z++){
    fread(&f,sizeof(f),1,fp);
    fread(&s,sizeof(s),1,fp);
    hang[i][j]=(f+s)/2;
    if(j==y/2){
    i++;
    j=0;
    }
    }
    fclose(fp);
    //行缩
    int k;
    for(i=0,j=0,z=0,k=0;z<x*y/4;k++,i+=2,z++){
    all[k][j]=(hang[i][j]+hang[i+1][j])/2;
    if(i==x-2){
    j++;
    k=0;
    i=0;
    }
    }
    //放图
    short int t;
    int cha[3];
    int min[3];
    int count=0;
    int sum;
    fp=fopen("D:\\Documents\\Downloads\\hanyx\\SeaSide\\exsample400-400","rb");
    while(count<3){
        sum=x/3*y*2-2;
        fread(&t,sizeof(t),1,fp);
        short int max=t,mi=t;
    while(sum-=2){
        fread(&t,sizeof(t),1,fp);
        cha[count]=max-mi;
        if(t>max)
                {cha[count]=t-mi;max=t;}
        if(t<mi)
                {cha[count]=max-t;mi=t;min[count]=t;}
    }
    count++;
    }
    fclose(fp);

    short int r,g,b;
    Image1->Picture->Assign(NULL);
    Image1->Canvas->Pen->Style=psSolid;
    Image1->Canvas->MoveTo(1,1);
    for(i=0;i<=x/6;i++,Image1->Canvas->MoveTo(1,i)){
    for(j=0;j<=y/2;j++){
    r=all[i][j];
    g=all[i+x/6][j];
    b=all[i+x/3][j];
    Image1->Canvas->Pen->Color=TColor(RGB(
    ((r-min[0])*1.0/cha[0]*255),
    ((g-min[1])*1.0/cha[1]*255),
    ((b-min[2])*1.0/cha[2]*255)));
    Image1->Canvas->Pen->Width=1;
    Image1->Canvas->LineTo(j,i);
    }
    }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button4Click(TObject *Sender)
{
   //分离---------------------------------

    FILE *fp;
    short int t;
    int cha[3];
    int min[3];
    int count=0;
    int sum;

    fp=fopen("D:\\Documents\\Downloads\\hanyx\\SeaSide\\exsample400-400","rb");
    while(count<3){
        sum=307254;
        fread(&t,sizeof(t),1,fp);
        short int max=t,mi=t;
    while(sum-=2){
        fread(&t,sizeof(t),1,fp);
        cha[count]=max-mi;
        if(t>max)
                {cha[count]=t-mi;max=t;}
        if(t<mi)
                {cha[count]=max-t;mi=t;min[count]=t;}
    }
    count++;
    }
    fclose(fp);
    /*while(count--)
    Memo1->Lines->Add(IntToStr(cha[count]));*///输出检测差
    //---------------------------------------------------
    //分离---------------------
    int fenli[x][y];
    FILE *R,*B,*G;
    R=fopen("D:\\Documents\\Downloads\\hanyx\\SeaSide\\exsample400-400","rb");
    G=fopen("D:\\Documents\\Downloads\\hanyx\\SeaSide\\exsample400-400","rb");
    fseek(G,x/3*y*2,1);
    B=fopen("D:\\Documents\\Downloads\\hanyx\\SeaSide\\exsample400-400","rb");
    fseek(B,x/3*y*4,1);
    int i,j;
    short int r,g,b;
    for(i=1;i<=x/3;i++){
    for(j=1;j<=y;j++){
    fread(&r,sizeof(r),1,R);
    fread(&g,sizeof(g),1,G);
    fread(&b,sizeof(b),1,B);
    if(b<=11000&&g>=9000&&r>=10000){
    fenli[i][j]=1;
    }
    else{
    fenli[i][j]=0;
    }
    i=0;j=0;
    int *after;
    //after=sousuo(fenli,i,j);

    }
    }

    /*//放图-----------------------------------------------
    FILE *R,*B,*G;
    R=fopen("D:\\Documents\\Downloads\\hanyx\\SeaSide\\exsample400-400","rb");
    G=fopen("D:\\Documents\\Downloads\\hanyx\\SeaSide\\exsample400-400","rb");
    fseek(G,x/3*y*2,1);
    B=fopen("D:\\Documents\\Downloads\\hanyx\\SeaSide\\exsample400-400","rb");
    fseek(B,x/3*y*4,1);
    int i,j;
    short int r,g,b;
    Image1->Canvas->Pen->Style=psSolid;
    Image1->Canvas->MoveTo(1,1);
    for(i=1;i<=x/3;i++,Image1->Canvas->MoveTo(1,i)){
    for(j=1;j<=y;j++){
    fread(&r,sizeof(r),1,R);
    fread(&g,sizeof(g),1,G);
    fread(&b,sizeof(b),1,B);
    if(b<=11000&&g>=9000&&r>=10000){
    Image1->Canvas->Pen->Color=TColor(RGB(
    ((r-min[0])*1.0/cha[0]*255),
    ((g-min[1])*1.0/cha[1]*255),
    ((b-min[2])*1.0/cha[2]*255)));}
    else{
    Image1->Canvas->Pen->Color=TColor(RGB(255,255,255));
    }
    Image1->Canvas->Pen->Width=1;
    Image1->Canvas->LineTo(j,i);
    }
    }
    fclose(R);
    fclose(G);
    fclose(B);*/
}
//---------------------------------------------------------------------------
     

int * TForm1::sousuo(int a[], int i, int j)
{

}


void __fastcall TForm1::Button5Click(TObject *Sender)
{      /*
     
     if(!Edit1->Text.IsEmpty())
        {       //try{

                TMemoryStream   *   Streamshp   =   new   TMemoryStream();				//新建一个流
                Streamshp->LoadFromFile("D:\\Documents\\Downloads\\hanyx\\SeaSide\\exsample400-400");//	                                                //打开二进制文件
                TBlobField *Field=(TBlobField*)ADOTable1-> FieldByName("img");			//IMAGE_data是数据库中字段的名字，格式为varbinary
                Field->LoadFromStream(Streamshp);
                Streamshp->Free();
                //}catch(exception){Edit1->Text="您输入的文件不存在或文件路径错误";}									//释放流
        //}
    // else{Edit1->Text="请输入文件路径";
                 }
    // Edit1->Clear(); */
                }  
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{     /*
    //SQL   
    ADOConnection1->Open();
    AnsiString sqlstr = "select *from C_E_T";
    //ADOQuery1->Close();
    ADOQuery1->SQL->Clear();
    ADOQuery1->SQL->Add(sqlstr);
    ADOQuery1->Open();    //查询操作
    //ADOQuery1->ExecSQL();       //插入、删除操作。
    DBGrid1->Columns->Items[0]->Width= 80;
    DBGrid1->Columns->Items[1]->Width= 80;
    DBGrid1->Columns->Items[2]->Width= 80;
    DBGrid1->Columns->Items[3]->Width= 80;
    DBGrid1->Columns->Items[4]->Width= 90;  */
}
//---------------------------------------------------------------------------
