#include <graphics.h>
#include <windows.h>
#include <mmsystem.h>

using namespace std;

/*
0 - casuta goala
1- x
2 - o
*/


/*
                                ///////////////////// CHANGE LOG ////////////////////////////

                    Perioada ALPHA
                                versiunea 0.0.1:
                                *Versiune conceputa pentru test de grafica
                                versiunea 0.0.2:
                                *Versiune conceputa pentru test de sunet
                                (BUG #001): Programul se blocheaza la miscarea ferestrei
                                versinea 0.0.3:
                                +Adaugata grafica
                                +Adaugate sunete
                                -Lipseste mecanica jocului
                                *Reparat bug #001
                                versiunea 0.0.4:
                                *Fontul a fost facut mai mare
                                -Efectul de glow a fost scos din cauza problemelor la nivelul graficii.

                                ///
                                versiunea 0.1 (descarcare aici: https://pastebin.com/PB2S23sQ)
                                +Adaugat suport jucator vs jucator
                                +Adaugat efect sonor de castig
								+Se taie cu un X toata grila la castig.

                                versiunea 0.1.1:
                                *Optimizari la nivelul jocului

								///
                                versiunea 0.2:
                                +Adaugat efect sonor de remiza
								+Se taie cu un X toata grila la remiza si au fost schimbate culorile

                                versiunea 0.2.1:
                                *Ordonarea codului

versiunea curenta: Alpha 0.2.1

*/

struct poz
{
    int x;
    int y;
}mouse,place;

bool p1=true,egale;

int a[3][3],i,j;

int Terminare();
void Translate();
void Initializare();
bool MiscarePosibila();
void JucatorVsJucator();
void JucatorVsAI();
void RezultatFinal();


int main()
{
    initwindow(300,300);
    Initializare();
    JucatorVsJucator();
    RezultatFinal();
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
}

int Terminare()
{
    //////////////////////////////////////////////
    //////////Verifica diagonalele//////////
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
    /////////////////////////////////////////////////
    ///////////////Verifica liniile si coloanele/////////////////
    for(i=0; i<3; i++)
    {
        if(a[i][0]==a[i][1] && a[i][1]==a[i][2])
        {
            if(a[i][0]==1)
                return 1;
            if(a[i][0]==2)
                return 2;
        }
    }
    for(i=0; i<3; i++)
    {
        if(a[0][i]==a[1][i] && a[1][i]==a[2][i])
        {
            if(a[0][i]==1)
                return 1;
            if(a[0][i]==2)
                return 2;
        }
    }
    ///////////////////////////////////////////////////////
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

bool MiscarePosibila()
{
    if(a[place.x][place.y]==0)
        return true;
    return false;
}

void JucatorVsJucator()
{
        do{
           if(ismouseclick(WM_LBUTTONDOWN))
           {
               getmouseclick(WM_LBUTTONDOWN,mouse.x,mouse.y);
               Translate();
               if(p1==true && MiscarePosibila()==true)
               {
                    a[place.x][place.y]=1;
                    outtextxy(mouse.x,mouse.y,"X");
                    p1=false;
                    PlaySound(TEXT("place.wav"),NULL,SND_SYNC);
               }
                else
                {
                    if(MiscarePosibila()==true)
                    {
                        a[place.x][place.y]=2;
                        outtextxy(mouse.x,mouse.y,"O");
                        p1=true;
                        PlaySound(TEXT("place.wav"),NULL,SND_SYNC);
                    }
                }
           }
    }while(Terminare()==0);
}

void RezultatFinal()
{
    if(Terminare()==1 || Terminare()==2)
    {
        setcolor(GREEN);
        line(0,0,300,300);
        line(0,300,300,0);
        PlaySound(TEXT("win.wav"),NULL,SND_SYNC);
    }
    else
    {
        setcolor(GREEN);
        line(0,0,300,300);
        line(0,300,300,0);
        PlaySound(TEXT("tie.wav"),NULL,SND_SYNC);
    }
}