#include <graphics.h>
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

/*
Matrix values:
0 - free position
1- X (Player 1)
2 - o (Player 2 / AI)
*/

// By Bratosin David - Robert
// June 2018

struct poz
{
    int x=0;
    int y=0;
}mouse,place,AI,TextAI;



bool p1=true,retry;
char gamemode;

int a[3][3],i,j,rfinal;

void Clear_Joc();
void Start();
void Clear_Screen();
int Terminare();
void Translate();
void TranslateAI();
void Initializare();
bool MiscarePosibila();
void JucatorVsJucator();
poz MiniMax();
int cautareMax();
int cautareMin();
void MiscareAI();
void JucatorVsAI();
void RezultatFinal_JvsJ();
void RezultatFinal_JvsAI();


int main()
{
    do{
        Start();
        Clear_Screen();
        cout<<gamemode<<'\n';
        if(gamemode=='0')
        {
            do{
                initwindow(300,400,"X si O (AI Mode)");
                Initializare();
                JucatorVsAI();
                RezultatFinal_JvsAI();
                getch();
                cleardevice();
                closegraph();
                Clear_Joc();
                Clear_Screen();
                cout<<"Doriti sa reincercati?"<<'\n';
                cout<<'\n';
                cout<<"1 - Da"<<'\n';
                cout<<"0 - Nu"<<'\n';
                cin>>retry;
                Clear_Screen();
            }while(retry==true);
        }
        else
        {
            if(gamemode=='1')
            {
                do{
                    initwindow(300,400,"X si O (PvsP)");
                    Initializare();
                    JucatorVsJucator();
                    RezultatFinal_JvsJ();
                    getch();
                    cleardevice();
                    closegraph();
                    Clear_Joc();
                    Clear_Screen();
                    cout<<"Doriti sa reincercati?"<<'\n';
                    cout<<'\n';
                    cout<<"1 - Da"<<'\n';
                    cout<<"0 - Nu"<<'\n';
                    cin>>retry;
                    Clear_Screen();
                }while(retry==true);
            }
        }
    }while(gamemode!='2');
    return 0;
}

void Clear_Joc()
{
    //Restaurez valorile
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
            a[i][j]=0;
    }
    p1=true;
}

void Clear_Screen()
{
    system("cls");
}

void Start()
{
    cout<<"Bun venit la X si O by BatedCrayon"<<'\n';
    cout<<"=================================="<<'\n';
    cout<<"Alegeti modul pe care doriti sa il jucati"<<'\n';
    cout<<"-----------------------------------------"<<'\n';
    cout<<'\n';
    cout<<"0 - Jucator vs AI"<<'\n';
    cout<<"1 - Jucator vs Jucator"<<'\n';
    cout<<"2 - Iesire"<<'\n';
    cin>>gamemode;
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
    settextstyle(10,HORIZ_DIR,1);
    outtextxy(150,390,"v. 1.0 Beta by BatedCrayon");
    settextstyle(DEFAULT_FONT, HORIZ_DIR,4);
}

void Translate()
{
    //Computing where to add on screen X / O
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
                else
                {
                    if(mouse.y>=300) //Here I had a problem. X and O were being placed where the text like "You won"/"Draw!"/etc. was supposed to be. It was resolved by placing the verification condition in the function that checks if the move is possible.
                        mouse.y=-1; //You stepped out of the grid. Why did you do that?
                }
}

void TranslateAI()
{
    //Computing where the AI will put X / O
    if(AI.x==0)
        TextAI.x=50;
    else
        if(AI.x==1)
            TextAI.x=150;
        else
            if(AI.x==2)
                TextAI.x=250;

    if(AI.y==0)
        TextAI.y=50;
    else
        if(AI.y==1)
            TextAI.y=150;
        else
            if(AI.y==2)
                TextAI.y=250;
}

int Terminare()
{

    /*
        1 - Player 1 wins
        2 - Player 2 / AI wins
        3 - Tie
        0 - The game is not finished */
    //////////////////////////////////////////////
    //////////Check the diagonals.//////////
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
    ///////////////Lines and columns check/////////////////
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
    //////////Checking if the match is finished////////////
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(a[i][j]==0)
                return 0;
        }
    }
    return 3; //Tie
}

bool MiscarePosibila()
{
    if(mouse.y==-1)
        return false;
    if(a[place.x][place.y]==0)
        return true;
    return false;
}

void JucatorVsJucator()
{
        do{
           if(ismouseclick(WM_LBUTTONDOWN)) //If i press left click
           {
               getmouseclick(WM_LBUTTONDOWN,mouse.x,mouse.y); //We get coords
               Translate(); //Computing where X / O should be
               cout<<mouse.x<<" "<<mouse.y<<'\n';
               if(p1==true && MiscarePosibila()==true) //Checking if P1 is the one which makes a move and if it is a valid move.
               {
                    a[place.x][place.y]=1; //Saving the move in the matrix
                    outtextxy(mouse.x,mouse.y,"X"); //Graphics 
                    p1=false; //P2 plays now
                    PlaySound(TEXT("place.wav"),NULL,SND_SYNC); //Sound.
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

poz MiniMax()
{
    int scorul= INT_MAX; //The score is INT_MAX at the beginning.
    poz Miscare; //Saving the position

    for(int n=0; n<3; n++)
    {
        for(int m=0; m<3; m++)
        {
            if(a[n][m]==0)
            {
                a[n][m]=2; //I apply a possible solution

                int aux = cautareMax(); //Minimax algo

                if(aux<scorul)
                {
                    scorul=aux;
                    Miscare.x=n;
                    Miscare.y=m;
                }
                a[n][m]=0; //Demarking, if you won't do this the sound will repeat a lot of times :(
            }
        }
    }
    return Miscare;
}

int cautareMax()
{
    if(Terminare()==1) //+ 10 if the player wins
        return 10;
    if(Terminare()==2) //-10 if the AI wins
        return -10;
    if(Terminare()==3) // 0 for tie
        return 0;

    int scorul = INT_MIN;

    for(int n=0; n<3; n++)
    {
        for(int m=0; m<3; m++)
        {
            if(a[n][m]==0)
            {
                a[n][m]=1;
                scorul=max(scorul,cautareMin()); //Computing the max value of the position marked
                a[n][m]=0;
            }
        }
    }
    return scorul;
}

int cautareMin()
{
    if(Terminare()==1)
        return 10;
    if(Terminare()==2)
        return -10;
    if(Terminare()==3)
        return 0;

    int scorul = INT_MAX;

    for(int n=0; n<3; n++)
    {
        for(int m=0; m<3; m++)
        {
            if(a[n][m]==0)
            {
                a[n][m]=2;
                scorul=min(scorul,cautareMax());
                a[n][m]=0;
            }
        }
    }
    return scorul;
}

void MiscareAI()
{
    AI=MiniMax(); //Minimax
    a[AI.x][AI.y]=2; //Apply the move from minimax
    TranslateAI(); //Computing where the graphics should be
    outtextxy(TextAI.x,TextAI.y,"O");
    p1=true; //Player 1
    PlaySound(TEXT("place.wav"),NULL,SND_SYNC); //Sound
    cout<<"AI a pus pe poz. "<<AI.x<<" "<<AI.y<<'\n'; //Debug...
}


void JucatorVsAI()
{
    do{
        if(p1==true)
        {
            if(ismouseclick(WM_LBUTTONDOWN)) //Similar to Player vs Player
            {
                getmouseclick(WM_LBUTTONDOWN,mouse.x,mouse.y);
                Translate();
                if(MiscarePosibila()==true)
                {
                    a[place.x][place.y]=1;
                    outtextxy(mouse.x,mouse.y,"X");
                    p1=false;
                    PlaySound(TEXT("place.wav"),NULL,SND_SYNC);
                    cout<<"Jucatorul a pus pe poz. :"<<place.x<<" "<<place.y<<'\n';
                }
            }
        }
        else
            MiscareAI();
    }while(Terminare()==0);
}

void RezultatFinal_JvsJ()
{
    rfinal=Terminare();
    if(rfinal==1 || rfinal==2)
    {
        setcolor(GREEN);
        line(0,0,300,300);
        line(0,300,300,0);
        settextstyle(10,HORIZ_DIR,2);
        if(rfinal==1)
            outtextxy(150,350,"X a castigat!");
        else
            outtextxy(150,350,"O a castigat!");
        PlaySound(TEXT("castigat.wav"),NULL,SND_SYNC);
    }
    else
    {
        setcolor(YELLOW);
        line(0,0,300,300);
        line(0,300,300,0);
        settextstyle(10,HORIZ_DIR,2);
        outtextxy(150,350,"Remiza!");
        PlaySound(TEXT("remiza.wav"),NULL,SND_SYNC);
    }
}


void RezultatFinal_JvsAI()
{
    rfinal=Terminare();
    if(rfinal==1)
    {
        setcolor(GREEN);
        line(0,0,300,300);
        line(0,300,300,0);
        settextstyle(10,HORIZ_DIR,2);
        outtextxy(150,350,"Ai castigat!");
        PlaySound(TEXT("castigat.wav"),NULL,SND_SYNC);
    }
    else
    {
        if(rfinal==2)
        {
            setcolor(12);
            line(0,0,300,300);
            line(0,300,300,0);
            settextstyle(10,HORIZ_DIR,2);
            outtextxy(150,350,"Ai pierdut!");
            PlaySound(TEXT("pierdut.wav"),NULL,SND_SYNC);
        }
        else
        {
            setcolor(YELLOW);
            line(0,0,300,300);
            line(0,300,300,0);
            settextstyle(10,HORIZ_DIR,2);
            outtextxy(150,350,"Remiza!");
            PlaySound(TEXT("remiza.wav"),NULL,SND_SYNC);
        }

    }
}
