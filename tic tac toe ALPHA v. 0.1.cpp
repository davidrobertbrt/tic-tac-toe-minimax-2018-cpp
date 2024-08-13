#include <graphics.h>
#include <windows.h>
#include <mmsystem.h>

using namespace std;

/*
0 - casuta goala
1- x
2 - o
*/

struct poz
{
    int x;
    int y;
}mouse,place;

bool p1=true,ocupat,egale;

int a[3][3],i,j;

int Terminare();
void Translate();
void Initializare();


int main()
{
    initwindow(300,300);
    Initializare();
    while(Terminare()==0)
    {
           if(ismouseclick(WM_LBUTTONDOWN))
           {
               getmouseclick(WM_LBUTTONDOWN,mouse.x,mouse.y);
               Translate();
               if(p1==true && ocupat==false)
               {
                outtextxy(mouse.x,mouse.y,"X");
                p1=false;
                PlaySound(TEXT("place.wav"),NULL,SND_SYNC);
               }
                else
                {
                    if(ocupat==false)
                    {
                        outtextxy(mouse.x,mouse.y,"O");
                        p1=true;
                        PlaySound(TEXT("place.wav"),NULL,SND_SYNC);
                    }
                }
           }
    }
    if(Terminare()==1 || Terminare()==2)
    {
        setcolor(RED);
        line(0,0,300,300);
        line(0,300,300,0);
        PlaySound(TEXT("win.wav"),NULL,SND_SYNC);
    }
    getch();
    cleardevice();
    return 0;
}

void Initializare()
{
    rectangle(0,0,100,100);
    rectangle(100,0,200,200);
    rectangle(200,0,300,100);
    rectangle(0,100,100,200);
    rectangle(0,200,100,300);
    rectangle(100,100,200,200);
    rectangle(100,200,300,300);
    rectangle(200,200,300,300);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(DEFAULT_FONT, HORIZ_DIR,4);
}

void Translate()
{
    ocupat=false;
            if(mouse.x<100)
            {
                mouse.x=50;
                place.x=0;
            }
            else
           if(mouse.x<200)
           {
                mouse.x=150;
                place.x=1;
           }
            else
                if(mouse.x<300)
                {
                    mouse.x=250;
                    place.x=2;
                }
            if(mouse.y<100)
            {
                mouse.y=50;
                place.y=0;
            }
            else
                if(mouse.y<200)
                {
                    mouse.y=150;
                    place.y=1;
                }
            else
                if(mouse.y<300)
                {
                    mouse.y=250;
                    place.y=2;
                }
        if(a[place.x][place.y]!=0)
            ocupat=true;
        else
        {
            if(p1==true)
                a[place.x][place.y]=1;
            else
                a[place.x][place.y]=2;
        }
}

int Terminare()
{
    if(a[0][0]==a[1][1] && a[1][1]==a[2][2])
    {
        if(a[0][0]==1)
            return 1;
        if(a[0][0]==2)
            return 2;
    }
    if(a[2][0]==a[1][1] && a[0][2]==a[1][1])
    {
        if(a[2][0]==1)
            return 1;
        if(a[2][0]==2)
            return 2;
    }
    for(i=0; i<3; i++)
    {
        egale=true;
        for(j=1; j<3 && egale==true; j++)
        {
            if(a[i][j-1]!=a[i][j])
                egale=false;
        }
        if(egale==true)
        {
            if(a[i][0]==1)
                return 1;
            if(a[i][0]==2)
                return 2;
        }
    }
    for(i=0; i<3; i++)
    {
        egale=true;
        for(j=1; j<3 && egale==true; j++)
        {
            if(a[j-1][i]!=a[j][i])
                egale=false;
        }
        if(egale==true)
        {
            if(a[0][i]==1)
                return 1;
            if(a[0][i]==2)
                return 2;
        }
    }
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(a[i][j]==0)
                return 0;
        }
    }
    return 3;
}