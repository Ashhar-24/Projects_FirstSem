#include <stdio.h>
#include <time.h> //includes the time and date function used in this game to display previous results
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <process.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length;
int bend_no;
int len;
char key;
void record();
void load();
int life;
void Delay(long double);
int Score();
void gotoxy(int x, int y);
void GotoXY(int x,int y);
void Bend();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();

struct coordinate //coordinate axes x and y
{
    int x;
    int y;
    int direction;
};

typedef struct coordinate coordinate;

coordinate head, bend[500],food,body[30];

void Print() //Prints the welcome messgae                            
{   
    printf("\n\n*****************************Made by ASHHAR_21IT3019***********************\n");
    printf("\tWelcome to the Snake Game.\n");
    printf("\n(Press Any Key To Continue...)\n");
    getch(); //pauses the console until any key is pressed
    system("cls"); //clears the screen

    printf("\t\t_____________Game Instructions____________\n");
    printf("\ni. Use arrow keys to move the snake.");
    printf("\nii.You will be provided with fruit (O) at random coordinates of the screen, you've to eat it to increase your score.");
	printf("\niii. Everytime you eat, your score increases by 1 as well as the lenght of your snake.");
	printf("\niv. You are provided with three lives. Your life will decrease as you either hit the Wall or the snake's body.");
	printf("\nv. To pause the game press any key. To resume it press any key!");
	printf("\nvi. If you want to exit press 'ESC'.\n");
    printf("\n\nPress any key to start your game!...");
    if(getch()==27)
        exit(0);
}
void gotoxy(int x, int y)// This function allows you to print text in any place of screen.//
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
} 
 
void GotoXY(int x, int y)// This function allows you to print text in any place of screen.//
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}

void Boarder()
{
    system("cls"); //clears the screen
    int i;
    GotoXY(food.x,food.y);  
    printf("O");
    for(i=10; i<71; i++)
    {
        GotoXY(i,10);
        printf("*");
        GotoXY(i,30);
        printf("*");
    }
    for(i=10; i<31; i++)
    {
        GotoXY(10,i);
        printf("*");
        GotoXY(79,i);
        printf("*");
    }
}

void Food()
{
    if(head.x==food.x&&head.y==food.y)
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%79;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)

            food.y+=11;
    }
    else if(food.x==0) //creates the food for the first time
    {
        food.x=rand()%79;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
}

void Move() //Moves the snake
{
    int a,i;
    do
    {
        Food();
        fflush(stdin);
        len=0;
        for(i=0; i<30; i++)
        {
            body[i].x=0;
            body[i].y=0;
            if(i==length)
                break;
        }
        Delay(length);
        Boarder();
        if(head.direction==RIGHT)
            Right();
        else if(head.direction==LEFT)
            Left();
        else if(head.direction==DOWN)
            Down();
        else if(head.direction==UP)
            Up();
        ExitGame();
    }
    while(!kbhit());
    a=getch();
    if(a==27)
    {
        system("cls");
        exit(0);
    }
    key=getch();
    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))
    {
        bend_no++;
        bend[bend_no]=head;
        head.direction=key;
        if(key==UP)
            head.y--;
        if(key==DOWN)
            head.y++;
        if(key==RIGHT)
            head.x++;
        if(key==LEFT)
            head.x--;
        Move();
    }
    else if(key==27)
    {
        system("cls");
        exit(0);
    }
    else
    {
        printf("\a");
        Move();
    }
}

void load() //This function is called before start the game
{
    int row,col,r,c,q;
    gotoxy(36,14);
    printf("Loading...");
    gotoxy(30,15);
    for(r=1; r<=20; r++)
    {
        for(q=0; q<=100000000; q++); //to display the character slowly
        printf("%c",177);
    }
    getch();
}

void Down() //This function is used to go downward
{
    int i;
    for(i=0; i<=(head.y-bend[bend_no].y)&&len<length; i++)
    {
        GotoXY(head.x,head.y-i);
        {
            if(len==0)
                printf("v");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}

void Delay(long double k) //Used to delay the execution
{
    Score();
    long double i;
    for(i=0; i<=(10000000); i++);
}

void ExitGame() 
{
    int i,check=0;
    for(i=4; i<length; i++) //starts with 4 because it needs minimum 4 element to touch its own body
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {
            check++;    //check's value increases as the coordinates of head is equal to any other body coordinate
        }
        if(i==length||check!=0)
            break;
    }
    if(head.x<=10||head.x>=79||head.y<=10||head.y>=30||check!=0)
    {
        life--;
        if(life>=0)
        {
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            Move();
        }
        else
        {
            system("cls");
            printf("Game Over!! \n\nPress Any Key To Quit The Game\n");
            record();
            exit(0);
        }
    }
}

void Left() //used to move the snake to left
{
    int i;
    for(i=0; i<=(bend[bend_no].x-head.x)&&len<length; i++)
    {
        GotoXY((head.x+i),head.y);
        {
            if(len==0)
                printf("<");
            else
                printf("*");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;
}

void Right() //used to move the snake to right
{
    int i;
    for(i=0; i<=(head.x-bend[bend_no].x)&&len<length; i++)
    {
        body[len].x=head.x-i;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
                printf(">");
            else
                printf("*");
        }
        len++;
    }
    Bend();
    if(!kbhit())
        head.x++;
}

void Bend()
{
    int i,j,diff;
    for(i=bend_no; i>=0&&len<length; i--)
    {
        if(bend[i].x==bend[i-1].x)
        {
            diff=bend[i].y-bend[i-1].y;
            if(diff<0)
                for(j=1; j<=(-diff); j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff; j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1; j<=(-diff)&&len<length; j++)
                {
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff&&len<length; j++)
                {
                    body[len].x=bend[i].x-j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
    }
}

void record() //this function is used to record players gameplay
{
    char plname[20],nplname[20],cha,c;
    int i,j,px;
    FILE *info;
    info=fopen("record.txt","a+");
    getch();
    system("cls");
    printf("Enter Your Name: ");
    scanf("%[^\n]",plname);
    for(j=0; plname[j]!='\0'; j++) //to convert the first letter after space to capital
    {
        nplname[0]=toupper(plname[0]);
        if(plname[j-1]==' ')
        {
            nplname[j]=toupper(plname[j]);
            nplname[j-1]=plname[j-1];
        }
        else nplname[j]=plname[j];
    }
    nplname[j]='\0';
    fprintf(info,"\n\nPlayer's Name: %s\n",nplname);
    //for date and time
    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"\nPlayed Date:%s",ctime(&mytime));
    fprintf(info,"Score: %d\n",px=Scoreonly());//call score to display score
    for(i=0; i<=50; i++)
        fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
    printf("Press 'Y' if you want to see past records (Y/N): ");
    cha=getch();
    system("cls");
    if(cha=='Y')
    {
        info=fopen("record.txt","r");
        do
        {
            putchar(c=getc(info));
        }
        while(c!=EOF);
    }
    fclose(info);
}
int Score() //this function is used to check the score
{
    int score;
    GotoXY(20,8);
    score=length-5;
    printf("SCORE : %d",(length-5));
    score=length-5;
    GotoXY(50,8);
    printf("Life : %d",life);
    return score;
}

int Scoreonly()
{
    int score=Score();
    system("cls");
    return score;
}

void Up()
{
    int i;
    for(i=0; i<=(bend[bend_no].y-head.y)&&len<length; i++)
    {
        GotoXY(head.x,head.y+i);
        {
            if(len==0)
                printf("^");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y+i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y--;
}

int main()
{
    char key;
    Print();
    system("cls"); //clears the screen
    system("color 7A"); //used to colour the screen: first letter is used to set the background whereas the second text's colour
    load();
    length=5;
    head.x=25;
    head.y=20;
    head.direction=RIGHT;
    Boarder(); //prints the boarder
    Food(); //Genetration of food coordinates
    life=3; //total number of lives
    bend[0]=head;
    Move();   //initialing initial bend coordinate
    return 0;
}