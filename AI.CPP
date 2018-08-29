#include<process.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<dos.h>
#include<conio.h>
#include<ctype.h>

//global variables
int homx=30;
int homy=13;


//function editdistance-intelligence function:::::::::::::::::::::::::::::::::::


char username[100],password[100];


int editdist(char x[],char y[])
{
 clrscr();
 int a[20][20],l1,l2,j,i,c,d1,d2,d3,z;
 l1=strlen(x);
 l2=strlen(y);
 a[0][0]=0;
  for(j=1;j<=l1;j++)
   a[0][j]=j;
 j=0;
  for(i=1;i<=l2;i++)
   a[i][0]=i;
 i=0;
for(i=1;i<=l2;i++)
 for(j=1;j<=l1;j++)
 {
  if(x[i-1]==y[j-1])
   c=0;
  else
   c=1;
    d1=c+a[i-1][j-1];//diagonal
    d2=1+a[i][j-1];//left
    d3=1+a[i-1][j];//up
   z=d1;
   if(z>d2)
    z=d2;
   if(z>d3)
    z=d3;
  a[i][j]=z;
  }
return z;
}

//user structure
struct user
{
char username[100];
char password[100];
char name[100];
}active,passive;

//reply structure
struct reply

{
char k[10][15];
char reply[100];
int kcode;
}s;

//class ai:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

class ai
{
char istr[100];
char ostr[100];
char pistr[100];
char postr[100];
public :
 void getoutput(); //these functions are declared outline
 void refine();
 void input();
 void display();
}h;


 void ai::input()  //function for inputting the query
 {
 void central();
 char ch;
 int driver =DETECT,mode;
 initgraph(&driver,&mode,"c:\\TurboC4\TC\BGI");
 moveto(getmaxx()/2-40,getmaxy()/2);
 outtext("->");
 char s[2];
 int c=0;
 int h=10;
 while(kbhit)
 {
 ch=getch();
 if(ch==0x0D)
 break;
 s[0]=ch;
 istr[c]=s[0];
 s[1]='\0';
 moveto(getx()+3,getmaxy()/2-1);
 outtext(s);
 c++;
 h++;
 }
 istr[c]='\0';
 delay(200);
  if(strcmp(istr,"exit")==0)
  {
  closegraph();
  central();
  }
 closegraph();
 }


 void ai::display()
 {
 int driver =DETECT,mode;
 initgraph(&driver,&mode,"c:\\TurboC4\TC\BGI");
 moveto(getmaxx()/2,getmaxy()/2);
 outtext("AI : ");
 outtext(ostr);
 getch();
 closegraph();

 }
 void ai::refine()
 {
 int l;
 l=strlen(istr);
 int i=0;
 for(i=0;i<=l;++i)
  {
  if((istr[i]==',')||(istr[i]=='.')||(istr[i]==':')||(istr[i]==';'))
  {istr[i]=' ';}
 }
 }

void ai::getoutput()
 {
 fstream f;
 char chstr[10][15];
 int l=strlen(istr),val,nw=1,k=0;
 int i=0,j=0,c[100],temp,pos=0,big=0;
 int min=0,wmin=0,rec=-1,mrec=0,recid,prev;
 char t[100];
  //getting the words
 for(i=0;i<l;i++)
  if(istr[i]==' ')
  nw++;
j=0;
 for(i=0;i<=l;i++,k++)
 {
  if(istr[i]==' ')
  {
  chstr[j][k]='\0';
  j++;k=0;i++;
  }
   chstr[j][k]=istr[i];
}
chstr[j][k]='\0';

//sorted according to length
for(i=0;i<nw;i++)
c[i]=strlen(chstr[i]);
for(j=0;j<nw;j++)
{
big=0;
for(i=0;i<nw;i++)
{
if(c[i]>big)
{
big=c[i];
pos=i;
}
}
temp=c[j];
c[j]=c[pos];
c[pos]=temp;
c[j]=0;
strcpy(t,chstr[j]);
strcpy(chstr[j],chstr[pos]);
strcpy(chstr[pos],t);
}

//checking
f.open("K_Base",ios::in|ios::binary);

while(f)
{
min=0;
f.read((char*)&s,sizeof(s)); //for every record
rec++;
 if(s.kcode>nw)
  break;
 for(i=0;i<s.kcode;i++)//for every word in query
  {
  wmin=editdist(s.k[0],chstr[i]);
    for(j=1;j<s.kcode;j++)
     {
     val=editdist(chstr[i],s.k[j]);
     if(val<wmin)
     {
       wmin=val;//we found the minimum editdistance of the ith word compared with which word in file
       }
     }
  min+=wmin;//add it to min.this is the comparison value for each record .
  }
  if(rec==0)
  {
  prev=min;
  mrec=rec;
  }
  if(min<prev)//we found the best suited record in all the records
  {
   prev=min;
   mrec=rec;
  }
}
f.close();
f.open("K_Base",ios::in|ios::binary);
f.seekg(mrec*sizeof(s),ios::beg);
f.read((char*)&s,sizeof(s));
strcpy(ostr,s.reply);
f.close();
}


//class ai closed::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
				       //
				       //
				       //
				       //
// other functions:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void createuser()
{
void home();
fstream f;
char check[100],check2[100];
clrscr();
char ch;
int left,right,top,bottom;
int driver =DETECT,mode;
initgraph(&driver,&mode,"c:\\TurboC4\TC\BGI");
setlinestyle(SOLID_LINE, 1, 1);
 left = getmaxx() / 2 - 87;
top = getmaxy() / 2 - 30;
right = getmaxx() / 2 + 87;
bottom = getmaxy() / 2 + 50;

rectangle(left,top,right,bottom);

setlinestyle(CENTER_LINE, 1, 1);
 left = getmaxx() / 2 - 90;
top = getmaxy() / 2 - 34;
right = getmaxx() / 2 + 90;
bottom = getmaxy() / 2 + 54;

rectangle(left,top,right,bottom);

moveto(getmaxx()/2,getmaxy()/2-20);
settextjustify(CENTER_TEXT,CENTER_TEXT);
outtext("CREATE USER");
moveto(getmaxx()/2-25,getmaxy()/2-1);
settextjustify(RIGHT_TEXT,LEFT_TEXT);
outtext("USER ID");

moveto(getmaxx()/2-18,getmaxy()/2+18);
outtext("PASSWORD");
int h=2;
moveto(getmaxx()/2-18,getmaxy()/2+36);
settextjustify(RIGHT_TEXT,LEFT_TEXT);
outtext("RETYPE");

moveto(getmaxx()/2-18,getmaxy()/2+54);
settextjustify(RIGHT_TEXT,LEFT_TEXT);
outtext("NAME");


//username
setcolor(CYAN);
moveto(getmaxx()/2-25,getmaxy()/2-1);
settextjustify(RIGHT_TEXT,LEFT_TEXT);
outtext("USER ID");
setcolor(15);
char s[2];
moveto(getmaxx()/2-h,getmaxy()/2+25);
int c=0;
while(kbhit)
{
if(c>11)
{
setlinestyle(CENTER_LINE, 1, 1);
setcolor(4);
left = getmaxx() / 2 - 90;
top = getmaxy() / 2 - 34;
right = getmaxx() / 2 + 90;
bottom = getmaxy() / 2 + 54;
rectangle(left,top,right,bottom);
setcolor(15);
delay(1000);
break ;
}
ch=getch();
if(ch==0x0D)
break;
s[0]=ch;
passive.username[c]=s[0];
s[1]='\0';
moveto(getmaxx()/2-h,getmaxy()/2-1);
outtext(s);
h-=8;
c++;

}
username[c]='\0';
moveto(getmaxx()/2-25,getmaxy()/2-1);
settextjustify(RIGHT_TEXT,LEFT_TEXT);
outtext("USER ID");



settextjustify(RIGHT_TEXT,LEFT_TEXT);
setcolor(CYAN);
moveto(getmaxx()/2-18,getmaxy()/2+18);
outtext("PASSWORD");
setcolor(15);


setlinestyle(CENTER_LINE, 1, 1);
setcolor(15);
left = getmaxx() / 2 - 90;
top = getmaxy() / 2 - 34;
right = getmaxx() / 2 + 90;
bottom = getmaxy() / 2 + 54;
rectangle(left,top,right,bottom);

moveto(getmaxx()/2+1,getmaxy()/2+18);
//password
c=0;h=2;
while(kbhit)
{
if(c>11)
{
setlinestyle(CENTER_LINE, 1, 1);
setcolor(4);
left = getmaxx() / 2 - 90;
top = getmaxy() / 2 - 34;
right = getmaxx() / 2 + 90;
bottom = getmaxy() / 2 + 54;
rectangle(left,top,right,bottom);
setcolor(15);
break;
}
ch=getch();
if(ch==0x0D)
break;
s[0]=ch;
check[c]=s[0];
s[0]='*';
s[1]='\0';
moveto(getmaxx()/2-h,getmaxy()/2+18);
outtext(s);
h-=8;
c++;

}
check[c]='\0';
settextjustify(RIGHT_TEXT,LEFT_TEXT);
moveto(getmaxx()/2-18,getmaxy()/2+18);
outtext("PASSWORD");

settextjustify(RIGHT_TEXT,LEFT_TEXT);
setcolor(CYAN);
moveto(getmaxx()/2-18,getmaxy()/2+36);
outtext("RETYPE");
setcolor(15);


setlinestyle(CENTER_LINE, 1, 1);
setcolor(15);
left = getmaxx() / 2 - 90;
top = getmaxy() / 2 - 34;
right = getmaxx() / 2 + 90;
bottom = getmaxy() / 2 + 54;
rectangle(left,top,right,bottom);

moveto(getmaxx()/2+1,getmaxy()/2+36);
//retype password
c=0;h=2;
while(kbhit)
{
if(c>11)
{
setlinestyle(CENTER_LINE, 1, 1);
setcolor(4);
left = getmaxx() / 2 - 90;
top = getmaxy() / 2 - 34;
right = getmaxx() / 2 + 90;
bottom = getmaxy() / 2 + 54;
rectangle(left,top,right,bottom);
setcolor(15);
break;
}
ch=getch();
if(ch==0x0D)
break;
s[0]=ch;
check2[c]=s[0];
s[0]='*';
s[1]='\0';
moveto(getmaxx()/2-h,getmaxy()/2+36);
outtext(s);
h-=8;
c++;

}
check2[c]='\0';
settextjustify(RIGHT_TEXT,LEFT_TEXT);
moveto(getmaxx()/2-18,getmaxy()/2+36);
outtext("RETYPE");
setcolor(CYAN);
moveto(getmaxx()/2-18,getmaxy()/2+54);
settextjustify(RIGHT_TEXT,LEFT_TEXT);
outtext("NAME");
setcolor(15);
moveto(getmaxx()/2-h,getmaxy()/2+54);
while(kbhit)
{
if(c>11)
{
setlinestyle(CENTER_LINE, 1, 1);
setcolor(4);
left = getmaxx() / 2 - 90;
top = getmaxy() / 2 - 34;
right = getmaxx() / 2 + 90;
bottom = getmaxy() / 2 + 54;
rectangle(left,top,right,bottom);
setcolor(15);
delay(1000);
break ;
}
ch=getch();
if(ch==0x0D)
break;
s[0]=ch;
passive.name[c]=s[0];
s[1]='\0';
moveto(getmaxx()/2-h,getmaxy()/2-1);
outtext(s);
h-=8;
c++;

}
passive.name[c]='\0';

moveto(getmaxx()/2-18,getmaxy()/2+64);
int flag=0;
if(strcmp(check2,check)!=0)
{
outtext("passwords dont match.do you want to exit?");
cin>>ch;
if(ch=='y')
exit(0);
}
else
{
flag=1;
strcpy(passive.password,check2);
}
if(flag==1)
{
f.open("user.dat",ios::binary|ios::app);
f.write((char *)&passive,sizeof(passive));
moveto(getmaxx()/2-24,getmaxy()/2+46);
settextjustify(CENTER_TEXT,CENTER_TEXT);
setcolor(CYAN);
outtext("succesful");
}
getch();
f.close();
closegraph();
home();
}

void session()
{
clrscr();
for(int i=0;i<3;i++)
{
h.input();
h.refine();
h.getoutput();
h.display();
}

}


void k_baseadd()
{
void central();
clrscr();
int n,i,j;
cout<<"Enter the number of conversations : ";
cin>>n;
cout<<endl;
fstream f;
f.open("K_Base",ios::app|ios::binary);
for(i=0;i<n;i++)
{
cout<<"CONVERSATION "<<i+1<<endl;
cout<<"Enter the no.of keywords : ";
cin>>s.kcode;
for(j=0;j<s.kcode;j++)
{
cout<<endl<<"enter Key "<<j<<" : ";
gets(s.k[j]);
}
cout<<endl<<"Enter the reply : ";
gets(s.reply);
cout<<endl;
getch();
f.write((char*)&s,sizeof(s));
}
f.close();
cout<<"\nBASEADDITION DONE";
delay(1000);
clrscr();
central();
}

void central()
{
getch();
clrscr();
int left,right,top,bottom ;
int gd=DETECT,gm, a,color;

initgraph(&gd,&gm,"c:\\TurboC4\TC\BGI");
setlinestyle(SOLID_LINE, 1, 1);
left = getmaxx() / 2 - 87;
top = getmaxy() / 2 - 30;
right = getmaxx() / 2 + 87;
bottom = getmaxy() / 2 + 50;

setlinestyle(CENTER_LINE, 1, 1);
left = getmaxx() / 2 - 91;
top = getmaxy() / 2 - 34;
right = getmaxx() / 2 + 91;
bottom = getmaxy() / 2 + 54;

rectangle(left,top,right,bottom);
settextjustify(LEFT_TEXT,CENTER_TEXT);
moveto(getmaxx()/2,getmaxy()/2-20);
outtext(active.name);
moveto(getmaxx()/2-85,gety()+12);
outtext("1 start talking");
moveto(getmaxx()/2-85,gety()+12);
outtext("2 add a conversation");
moveto(getmaxx()/2-85,gety()+12);
outtext("3 change password");
moveto(getmaxx()/2-85,gety()+12);
outtext("4 exit");
moveto(getmaxx()/2-85,gety()+12);
outtext("enter choice :");
char choice;
while(kbhit)
{
choice=getch();
switch(choice)
{
case '1':session();
       break;
case '2':k_baseadd();
       break;
case '3':k_baseadd();
       break;
case '4':exit(0);
       break;
default:exit(0);
	break;
}
}
getch();
closegraph();
}





void login()
{
void home();
clrscr();
char ch;
int left,right,top,bottom;
int driver =DETECT,mode;
initgraph(&driver,&mode,"c:\\TurboC4\TC\BGI");
setlinestyle(SOLID_LINE, 1, 1);
 left = getmaxx() / 2 - 87;
top = getmaxy() / 2 - 30;
right = getmaxx() / 2 + 87;
bottom = getmaxy() / 2 + 30;

rectangle(left,top,right,bottom);

setlinestyle(CENTER_LINE, 1, 1);
 left = getmaxx() / 2 - 90;
top = getmaxy() / 2 - 34;
right = getmaxx() / 2 + 90;
bottom = getmaxy() / 2 + 34;

rectangle(left,top,right,bottom);

moveto(getmaxx()/2,getmaxy()/2-20);
settextjustify(CENTER_TEXT,CENTER_TEXT);
outtext("SIGN IN");
moveto(getmaxx()/2-25,getmaxy()/2-1);
settextjustify(RIGHT_TEXT,LEFT_TEXT);
outtext("USER ID");

moveto(getmaxx()/2-18,getmaxy()/2+18);
outtext("PASSWORD");
int h=2;
//username
setcolor(CYAN);
moveto(getmaxx()/2-25,getmaxy()/2-1);
settextjustify(RIGHT_TEXT,LEFT_TEXT);
outtext("USER ID");
setcolor(15);


char s[2];
moveto(getmaxx()/2-h,getmaxy()/2+25);
int c=0;
while(kbhit)
{
if(c>11)
{
setlinestyle(CENTER_LINE, 1, 1);
setcolor(4);
left = getmaxx() / 2 - 90;
top = getmaxy() / 2 - 34;
right = getmaxx() / 2 + 90;
bottom = getmaxy() / 2 + 34;
rectangle(left,top,right,bottom);
setcolor(15);
delay(1000);
break ;
}
ch=getch();
if(ch==0x0D)
break;
s[0]=ch;
username[c]=s[0];
s[1]='\0';
moveto(getmaxx()/2-h,getmaxy()/2-1);
outtext(s);
h-=8;
c++;

}
username[c]='\0';
moveto(getmaxx()/2-25,getmaxy()/2-1);
settextjustify(RIGHT_TEXT,LEFT_TEXT);
outtext("USER ID");




settextjustify(RIGHT_TEXT,LEFT_TEXT);
setcolor(CYAN);
moveto(getmaxx()/2-18,getmaxy()/2+18);
outtext("PASSWORD");
setcolor(15);


setlinestyle(CENTER_LINE, 1, 1);
setcolor(15);
left = getmaxx() / 2 - 90;
top = getmaxy() / 2 - 34;
right = getmaxx() / 2 + 90;
bottom = getmaxy() / 2 + 34;
rectangle(left,top,right,bottom);

moveto(getmaxx()/2+1,getmaxy()/2+18);
//password
c=0;h=2;
while(kbhit)
{
if(c>11)
{
setlinestyle(CENTER_LINE, 1, 1);
setcolor(4);
left = getmaxx() / 2 - 90;
top = getmaxy() / 2 - 34;
right = getmaxx() / 2 + 90;
bottom = getmaxy() / 2 + 34;
rectangle(left,top,right,bottom);
setcolor(15);
break;
}
ch=getch();
if(ch==0x0D)
break;
s[0]=ch;
password[c]=s[0];
s[0]='*';
s[1]='\0';
moveto(getmaxx()/2-h,getmaxy()/2+18);
outtext(s);
h-=8;
c++;

}
password[c]='\0';
settextjustify(RIGHT_TEXT,LEFT_TEXT);
moveto(getmaxx()/2-18,getmaxy()/2+18);
outtext("PASSWORD");
fstream f;
int flag=0;
f.open("user.dat",ios::in,ios::binary);
while(f.read((char*)&active,sizeof(active)))
{
if((strcmp(active.username,username)==0)&&(strcmp(active.password,password)==0))
{
flag=1;
break;
}
}
if(flag==0)
{
moveto(getmaxx()/2-8,getmaxy()/2+26);
outtext("user not found");
delay(300);
home();
}
else
{
moveto(getmaxx()/2-18,getmaxy()/2+26);
outtext("welcome ");
outtext(active.name);
delay(1000);
central();
}
getch();
closegraph();
}

void help()
{        void home();
	clrscr();
	cout<<"Hey guys and gals!!..Im genesis.\nYour personal assisitant.\nHere to help you and make your bored life more joyfull and happy.\nTo enter into my world first begin by logging in with your awesome username and that secretive password that your hiding from me.\nThen the intro page or my home page comes up giving you options to various things.\nThe 'start talking' option allows you to talk with the awesome everloving me.\nThe 'add a conversation' allows you to edit me.\nThat is it allows you to teach me new and stunning things.\nPLEASE NOTE:Don't you dare press that backspace key when you'r talking with me.\nI jst HATE IT.\nWhen you feel like taking a break just type 'exit' and I'll give you time.\n";
	getch();
	home();
}
void home()
{
int left,right,top,bottom ;
int gd=DETECT,gm, a,color;
initgraph(&gd, &gm, "C:\\tc\\bgi");
int p;
setcolor(CYAN);
left = getmaxx() / 2 - 200;
top = getmaxy() / 2 - 10;
right = getmaxx() / 2 + 200;
bottom = getmaxy() / 2 + 10;
rectangle(left,top,right,bottom);
setlinestyle(SOLID_LINE, 2 ,1);
setcolor(CYAN);
rectangle(left-3,top-2,right+3,bottom+2);
setcolor(CYAN);
setlinestyle(SOLID_LINE, 1, 1);
for(a=left; a<=right; a++)
    {
      if(a>right-2)
      {
       setcolor(GREEN);
       for(a=left; a<=right; a++)
       {
       rectangle(left,top+2,a,bottom-2);
       }
       setcolor(RED);
       settextjustify(CENTER_TEXT,CENTER_TEXT);
       outtextxy(getmaxx()/2,getmaxy()/2,"DONE");
       setcolor(GREEN);
       }
    else
    {
    setcolor(GREEN);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(getmaxx()/2,getmaxy()/2,"LOADING");
    setcolor(LIGHTCYAN);
    rectangle(left,top+2,a,bottom-2);
    }
    delay(15);
    }
getch();
closegraph();

initgraph(&gd,&gm,"c:\TURBO\TC\BGI");
setlinestyle(SOLID_LINE, 1, 1);
left = getmaxx() / 2 - 87;
top = getmaxy() / 2 - 30;
right = getmaxx() / 2 + 87;
bottom = getmaxy() / 2 + 50;

setlinestyle(CENTER_LINE, 1, 1);
left = getmaxx() / 2 - 91;
top = getmaxy() / 2 - 34;
right = getmaxx() / 2 + 91;
bottom = getmaxy() / 2 + 54;


rectangle(left,top,right,bottom);
settextjustify(LEFT_TEXT,CENTER_TEXT);
moveto(getmaxx()/2,getmaxy()/2-20);
outtext("HOME");
moveto(getmaxx()/2-85,gety()+12);
outtext("1 login");
moveto(getmaxx()/2-85,gety()+12);
outtext("2 create a user");
moveto(getmaxx()/2-85,gety()+12);
outtext("3 help");
moveto(getmaxx()/2-85,gety()+12);
outtext("4 exit");
moveto(getmaxx()/2-85,gety()+12);
outtext("enter choice :");
char choice;
while(kbhit)
{
choice=getch();
switch(choice)
{
case '1':login();
       break;
case '2':createuser();
       break;
case '3':help();
       break;
default:exit(0);
	break;
}
}
getch();
closegraph();
}



//other functions over:::::::::::::::::::::::::::::::::::::::::::::::::::::::


void main()
{
int x;
home();
getch();
}