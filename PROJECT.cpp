#include<iostream>
using namespace std;
struct food
{
    int row;
    int col;
    char val;
};
struct poison
{
    int row;
    int col;
    char val;
};
struct node
{
    char data;
    node *next;
};
node *head=NULL;
class snake
{
public:
    node* create(char n)
    {
        node *ptr=new node;
        ptr->data=n;
        ptr->next=NULL;
        return ptr;
    }
    void inserttail2(char n)
    {
        node *temp,*t,*temp2;
        temp=create(n);
        if(head==NULL)
        {
            head=temp;
        }
        else
        {
            t=head;
        while(t->next!=NULL)
        {
            temp2=t;
            t=t->next;
        }
        temp->next=temp2->next;
        temp2->next=temp;
        }
    }
    void inserttail(char n)
    {
        node *temp,*t;
        temp=create(n);
        if(head==NULL)
        {
            head=temp;
        }
        else
        {
            t=head;

        while(t->next!=NULL)
        {
            t=t->next;
        }
        t->next=temp;
        temp->next=NULL;
        }
    }
    void del2()
    {
        node *t=head,*temp;
        while(t->next!=NULL)
        {
            temp=t;
            t=t->next;
        }
        delete t;
        temp->data='T';
        temp->next=NULL;
    }
    void displaysnake()
    {
        node *t;
        t=head;
        while(t!=NULL)
        {
            cout<<t->data<<endl;
            t=t->next;
        }
    }
};
void displayboard(char board[][80])
{
    cout << "\x1b[2J\x1b[1;1H" << flush;
    int r,c;
    for(r=0;r<20;r++)
    {
        for(c=0;c<80;c++)
        {
          cout<<board[r][c];
        }
    }
    cout<<"\n";
}
void snakemaking(int rowarr[],int colarr[],char board[][80],int counter)
{
    node *t=head;
    int i=0;
    while(i!=counter)
    {
        board[rowarr[i]][colarr[i]]=t->data;
        t=t->next;
        i++;
    }
}
void traverse(int rowarr[],int colarr[],int counter,char board[][80])
{
    board[rowarr[counter-1]][colarr[counter-1]]=' ';
    int i;
    for(i=counter-1;i>0;i--)
    {
        rowarr[i]=rowarr[i-1];
        colarr[i]=colarr[i-1];
    }
}
void makefood(food f1,char board[][80])
{
    board[f1.row][f1.col]=f1.val;
}
void makepoison(poison p1,char board[][80])
{
    board[p1.row][p1.col]=p1.val;
}
void frontpage(char board[][80])
{
    board[5][30]='S';board[5][32]='N';board[5][34]='A';board[5][36]='K';board[5][38]='E';
    board[5][42]='G';board[5][44]='A';board[5][46]='M';board[5][48]='E';
    board[10][34]='E';board[10][35]='N';board[10][36]='T';board[10][37]='E';board[10][38]='R';board[10][43]='y';
    board[13][34]='E';board[13][35]='X';board[13][36]='I';board[13][37]='T';board[13][43]='e';
    displayboard(board);
}
void initailboard(char board[][80])
{
    int r,c;
      for(r=0;r<20;r++)
    {
        for(c=0;c<80;c++)
        {
            if(r==0 || c==0 || r==19 || c==79)
            {
               board[r][c]='*';
            }
            else
            {
                board[r][c]=' ';
            }
        }
    }
}
void lastpage(char board[][80],int score)
{
    initailboard(board);
    board[8][36]='S';board[8][38]='C';board[8][40]='O';board[8][42]='R';board[8][44]='E';
    if(score<=9)
    {board[12][40]=48+(score);
    }
    else
    {
        int k=41;
        while(score!=0)
        {
        int rem;
        rem=score%10;
        score=score/10;
        board[12][k]=48+(rem);
        k--;
        }
    }
    displayboard(board);
}
int main()
{
    int left,right,top,bottom,maxrow=19,maxcol=79,r,c,rowarr[20],colarr[80],counter,f,score=0;
    char board[20][80],choice='a',tempchoice='d',frontpagetemp;
    snake s1;
    food f1;
    poison p1;
    initailboard(board);
    frontpage(board);
    cin>>frontpagetemp;
    if(frontpagetemp=='e')
    {
        return 0;
    }
    initailboard(board);
    s1.inserttail('H');
    s1.inserttail('#');
    s1.inserttail('#');
    s1.inserttail('T');
    /*for initial snake*/
    rowarr[0]=10;
    rowarr[1]=10;
    rowarr[2]=10;
    rowarr[3]=10;
    colarr[0]=38;
    colarr[1]=39;
    colarr[2]=40;
    colarr[3]=41;
    counter=4;
    snakemaking(rowarr,colarr,board,counter);
    /*End of initial Snake*/
    f1.col=5;
    f1.row=5;
    f1.val='A';
    makefood(f1,board);
    p1.col=65;
    p1.row=17;
    p1.val='B';
    makepoison(p1,board);
    displayboard(board);
    while(1)
    {
        cout<<"Enter Choice:\n";
        cin>>choice;
        if(choice==tempchoice)
        {
            cout<<"Invalid Direction\n";
        }
        else
        {
        if(rowarr[0]==f1.row && colarr[0]==f1.col)
        {
         s1.inserttail2('#');
         counter++;
         rowarr[counter-1]=rowarr[counter-2];
         colarr[counter-1]=colarr[counter-2];
         f1.row=(rand()%18)+1;
         f1.col=(rand()%78)+1;
         for(f=0;f<counter;f++)
            {
                if((f1.row==rowarr[f] && f1.col==colarr[f])||(f1.row==p1.row && f1.col==p1.col))
                {
                    f1.row=(rand()%18)+1;
                    f1.col=(rand()%78)+1;
                    f=-1;
                }
            }
         makefood(f1,board);
         score++;
        }
        if(rowarr[0]==p1.row && colarr[0]==p1.col)
        {
            if(counter==4)
            {
                lastpage(board,score);
                return 0;
            }
            s1.del2();
            board[rowarr[counter-1]][colarr[counter-1]]=' ';
            counter--;
            p1.row=(rand()%18)+1;
            p1.col=(rand()%78)+1;
            for(f=0;f<counter;f++)
            {
                if((p1.row==rowarr[f] && p1.col==colarr[f])||(p1.row==f1.row && p1.col==f1.col))
                {
                    p1.row=(rand()%18)+1;
                    p1.col=(rand()%78)+1;
                    f=-1;
                }
            }
            makepoison(p1,board);
            score--;
        }
        else
        {
        traverse(rowarr,colarr,counter,board);
        if(choice=='w')
        {
            if(rowarr[0]==1)
            {
                rowarr[0]=maxrow-1;
            }
            else
            {
            rowarr[0]--;
            }
            tempchoice='s';
        }
        if(choice=='s')
        {
            if(rowarr[0]==maxrow-1)
            {
                rowarr[0]=1;
            }
            else
            {
            rowarr[0]++;
            }
            tempchoice='w';
        }
        if(choice=='a')
        {
            if(colarr[0]==1)
            {
                colarr[0]=maxcol-1;
            }
            else
            {
            colarr[0]--;
            }
            tempchoice='d';
        }
        if(choice=='d')
        {
            if(colarr[0]==maxcol-1)
            {
                colarr[0]=1;
            }
            else
            {
            colarr[0]++;
            }
            tempchoice='a';
        }
        for(f=1;f<counter;f++)
        {
            if(rowarr[0]==rowarr[f] && colarr[0]==colarr[f])
            {
                lastpage(board,score);
                return 0;
            }
        }
        snakemaking(rowarr,colarr,board,counter);
        displayboard(board);
        }
        }
    }
    return 0;
}
