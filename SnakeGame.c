#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>


#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27

int x[100],y[100];
int dir;
int key;
int speed;
int score;
int bestScore=0;
int food_x,food_y;
int length;

void gotoXY(int x,int y,char* s){
    COORD pos={2*x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    printf("%s",s);
}


void draw_map(void);
void title(void);
void move(int dir);
void game_over(void);
void status(void);
void food(void);
void start(void);
int main(){
title();
  while(1){
        if(kbhit()) do{key=getch();} while(key==224); 
        Sleep(speed);
        
        switch(key){   
            case LEFT:
            case RIGHT:
            case UP:
            case DOWN:
                if((dir==LEFT&&key!=RIGHT)||(dir==RIGHT&&key!=LEFT)||(dir==UP&&key!=DOWN)||
(dir==DOWN&&key!=UP))
                    dir=key;
                key=0; 
            break;
            case ESC: 
                exit(0);
        }
        move(dir);
        
       
    }    

return 0;
}


void draw_map(){
    int i;
    for (i = 4; i < 31; i++)
    {
    gotoXY(i,2,"a");
        
    }
    
    for (i = 3; i < 23; i++)
    {
        gotoXY(4,i,"a");
        gotoXY(30,i,"a");

    }
   for (i = 4; i < 31; i++)
    {
    gotoXY(i,23,"a");
        
    }
}

void title(){
    
    while(kbhit())getch();

    draw_map();
    gotoXY(10,10,"+--------------------------+");
    gotoXY(10,11,"|        S N A K E         |");
    gotoXY(10,12,"+--------------------------+");
    gotoXY(10,15," < PRESS ANY KEY TO START > ");
    gotoXY(12,17,"↑,↓,←,→ : Move");
    gotoXY(14,19,"ESC : Quit ");

        while(1){
        if(kbhit()){ 
            key=getch();
            if(key==ESC){

            exit(0);
            } 
            else {
                break;
                }  
        } 

}
    start();
}
void start(){
    int i;
    system("cls");
    draw_map();
    while(kbhit())getch();

    dir=UP;
    speed=150;
    length=6;
    score=0;
    x[0]=17;
    y[0]=9;
    for (i = 1; i <= length; i++)
    {   

        x[i]= x[0]; 
        y[i]=y[0]+i; 
        
        gotoXY(x[i],y[i],"O");
    }
    gotoXY(x[0],y[0],"C");
    food();
}

void move(int dir){
    int i;
    
    
    if (x[0]==food_x&&y[0]==food_y)
    {
        score+=10;
        length++;
        x[length]=x[length-1]; 
        y[length]=y[length-1];
        speed-=3;
        food();
    }
    for (i = 1; i <= length; i++)
    {
        
        if (x[0]==x[i]&&y[0]==y[i])
        {
            game_over();
            return;
        }
        
        if (x[i]==food_x&&y[i]==food_y)
        {
            food();
        }
        
    }
 
   if (x[0]==4||x[0]==30||y[0]==2||y[0]==23)
   {
        game_over();
        return;
   }
   



    gotoXY(x[length],y[length]," ");
    for(i=length;i>0;i--){ 
        x[i]=x[i-1];  
        y[i]=y[i-1]; 
    }


    gotoXY(x[0],y[0],"O");
    if (dir==LEFT)
    {
        --x[0];
    }
    if (dir==UP)
    {
        --y[0];
    }
    if (dir==RIGHT)
    {
        ++x[0];
    }
    if (dir==DOWN)
    {
         ++y[0];
    }
     gotoXY(x[0],y[0],"C");
     gotoXY(4,25," YOUR SCORE: ");
     printf("SCORE : %d  BESTSCORE : %d",score,bestScore);
}

void game_over(){
    gotoXY(10,10,"+--------------------------+");
    gotoXY(10,11,"|        GAME  OVER        |");
    gotoXY(10,12,"+--------------------------+");
    gotoXY(13,15,"  SOCRE :  ");
    printf("%d",score);
    gotoXY(10,18," Press any keys to restart ");

    if (score>bestScore)
    {
        bestScore=score;
        gotoXY(12,16,"<  BEST SCORE!!!   >");
    }
    while (kbhit())
    {
        if(getch()){
            start();
        }

    }
    
    
}

void food(){
    food_x= rand()%(29-5+1)+5;
    food_y=rand()%(22-3+1)+3;
    gotoXY(food_x,food_y,"z");
}