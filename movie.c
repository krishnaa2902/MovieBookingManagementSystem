#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
void red () {
printf("\033[1;31m");
}
void blue() {
printf("\033[1;34m");
}
void purple() {
printf("\033[1;35m");
}
void cyan() {
printf("\033[1;36m");
}
void yellow() {
printf("\033[1;33m");
}
void reset () {
printf("\033[0m");
}
void green(){
printf("\033[1;32m");
}
typedef struct customer
{
    char name[25];
    char pno[12];
    struct customer *next;
}customer;
customer* front=NULL;
customer* rear=NULL;
int count = 0;
typedef struct mov
{
    char mname[25];
    char language[25];
    float rating;
    char certification[5];
}mov;
typedef struct trans
{
    char name[25];
    char pno[12];
    int showid;
    char stype[20];
    char mname[30];
    char date[10];
    int total_seats;
    int booked_seats[50]; 
    int amount;
}trans;
typedef struct show
{
    int showid;
    int seat[50];
    int seat_left;
    char stype[20];
    char mname[30];
    char date[10];
}show;
void readqueue()
{
    customer *temp,*t;
    FILE *f1=fopen("customerdata.txt","r");
    while(fread(t,sizeof(customer),1,f1))
    {
        if(front==NULL && rear ==NULL)
        {
            customer*temp;
            temp=(customer*)malloc(sizeof(customer));
            strcpy(temp->name,t->name);
            strcpy(temp->pno,t->pno);
            temp->next=NULL;
            front=temp;
            rear=temp;
        }
       else
       {
            customer*temp;
            temp=(customer*)malloc(sizeof(customer));
            strcpy(temp->name,t->name);
            strcpy(temp->pno,t->pno);
            temp->next=NULL;
            rear->next=temp;
            rear=temp;
       }
    }
    fclose(f1);
}
void writequeue()
{
    customer *temp=front;
    FILE *f= fopen ("customerdata.txt","w");
    if(front==NULL)
    {
        
    }
    else
    {
        
        while(temp!=NULL)
        {
            fwrite(temp,sizeof(customer),1,f);
            temp=temp->next;
        }
        
    }
    fclose(f);
}
void enqueue()
{
    if(front==NULL && rear ==NULL)
    {
        customer*temp;
        temp=(customer*)malloc(sizeof(customer));
        char nam[25];
        char pno[25];
        printf("\nEnter name :");
        scanf("%s",nam);
        pno:
        printf("\nEnter phone no :");
        scanf("%s",pno);
        if(strlen(pno)!=10)
        {
            printf("\nInvalid phone number!.. please enter again");
            goto pno;
        }
        strcpy(temp->name,nam);
        strcpy(temp->pno,pno);
        temp->next=NULL;
        front=temp;
        rear=temp;
    }
    else
    {
        char nam[25];
        char pno[25];
        printf("\nEnter name :");
        scanf("%s",&nam);
        printf("\nEnter phone no :");
        scanf("%s",&pno);
        customer*temp;
        temp=(customer*)malloc(sizeof(customer));
        strcpy(temp->name,nam);
        strcpy(temp->pno,pno);
        temp->next=NULL;
        rear->next=temp;
        rear=temp;
    }
}
void dequeue()
{
    if(front==NULL)
    {
        printf("\nEmpty!!");
    }
    else if(front==rear)
    {
        customer*temp=front;
        printf("\nThe customer dequeued is :%s",temp->name);
        printf("\n\nPRESS ANY KEY TO CONTINUE");
        getch();
        front=NULL;
        rear=NULL;
        free(temp);
    }
    else
    {
        customer*temp=front;
        printf("\nThe customer dequeued is : %s",temp->name);
        printf("\n\nPRESS ANY KEY TO CONTINUE");
        getch();
        front=front->next;
        free(temp);
    }
    writequeue();
}
void display()
{
    customer *temp=front;
    if(front==NULL)
    {
        printf("\nEmpty!!");
    }
    else
    {
        printf("\nFRONT <- ");
        while(temp!=NULL)
        {
            printf("[Name : %s - PhNo : %s] <- ",temp->name,temp->pno);
            temp=temp->next;
        }
        printf("REAR");
    }
}
void login()
{
    char uname[20];
    char pwd[20];
    int i=0;
    printf("\nEnter username :");
    scanf("%s", uname);
    printf("\nEnter Password :");
    while(i<20)
    {
        pwd[i]=getch();
        if(pwd[i]==13)break;
        else printf("*");
        i++;
    }
    pwd[i]='\0';
    if(strcmp(uname,"admin")==0 && strcmp(pwd,"pass")==0)
    {
        printf("\nLOGIN SUCCESS!!..");
    }
    else
    {
        printf("\nLOGIN FAILURE!!..");
        printf("\nWould you like to try again? (y/n)");
        char ch;
        ch=getch();
        if(ch=='y' || ch=='Y')
        {
            login();
        }
        else
        {
            printf("\n----Program terminated!!----");
            exit(0);
        }
    }
}
void rewrite(show s[30],int no)
{
    FILE *fws = fopen("shows.txt","w");
    int i = 0;
    fwrite(s,sizeof(struct show),no, fws) ; 
    fclose(fws);
}
void selectseats(int sid)
{
    show sh;
    char time[20];
    FILE *frs;
    int k=0,ct=0;
    frs=fopen("shows.txt", "r");
    while(fread(&sh, sizeof(struct show), 1, frs) && ct<=count) 
    {
        if(sh.showid==sid)
        {
            
            if(strcmp(sh.stype,"afternoon")==0)
            {
                strcpy(time,"1:30 PM");
            }
            if(strcmp(sh.stype,"evening")==0)
            {
                strcpy(time,"6:30 PM");
            }
            if(strcmp(sh.stype,"night")==0)
            {
                strcpy(time,"10:30 PM");
            }
            int c=1;
            printf("\n+------------------------------------------+");
            printf("\n|SHOW ID    :%-30d|",sh.showid);
            printf("\n|MOVIE NAME :%-30s|",sh.mname);
            printf("\n|SHOW TYPE  :%-10s-%-19s|",sh.stype,time);
            printf("\n|DATE       :%-30s|",sh.date);     
            printf("\n|SEATS LEFT :%-30d|",sh.seat_left);
            printf("\n+------------------------------------------+\n\n\n");
            yellow();
            printf("__________________________________________________________\n");
            printf("                     SCREEN THIS WAY                       \n");
            reset();
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            for(int i=0;i<5;i++)
            {
                for(int j=0;j<10;j++)
                {
                    if(sh.seat[c-1]==0)
                    {
                        green();
                        printf("%-4d  ",c++);
                        reset();
                    }
                    else if(sh.seat[c-1]==1)
                    {
                        //printf("      ");
                        red();
                        printf("%-4d  ",c++);
                        reset();
                        // c++;
                    }
                }
                printf("\n");
                printf("\n");
            }          
        }
        ct++;    
    }
}
void transaction(show,int*,int);
void book(show s[30])
{  
    tri:
    1==1;
    FILE *frs;
    frs=fopen("shows.txt", "r");
    if(frs==NULL)
    {
        printf("\nNo SHOW available");
        return;
    }
    if(front==NULL)
    {
        printf("\nNo one waiting in queue!");
        return;
    }
    int booked_seats[50];
    int no_of_seats;
    int seat_no;
    int x,xi=0;
    int sno;
    char cont;
    printf("\nBOOKING FOR %s\n",front->name); 
    printf("\nEnter SHOW NO of movie you would like to see :");
    scanf("%d",&sno);
    show sh,st[30];
    while(fread(&sh, sizeof(struct show), 1, frs))
    {
        st[xi].showid=sh.showid;
        strcpy(st[xi].mname,sh.mname);
        strcpy(st[xi].date,sh.date);       
        st[xi].seat_left=sh.seat_left;
        for(int i=0;i<50;i++)
        {
            st[xi].seat[i]=sh.seat[i];
            booked_seats[i]=0;
        }
        st[xi].showid=sh.showid;
        strcpy(st[xi].stype,sh.stype);
        if(sh.showid==sno)
        {
            for(int i=0;i<50;i++)
            {
                
            }
        }
        xi++;  
    }
    fclose(frs);
    if(sno >= 1000+xi || sno <1000)
    {
        printf("\nIncorrect SHOW ID !!.. Please try again");
        fclose(frs);
        goto tri;
    }
    x=sno-1000;
    if(st[x].seat_left<=0)
    {
        printf("\nAll seats booked !!");
        return;
    }
    here:
    selectseats(sno);
    printf("\nDo you want to select seats?(Y/N)");
    cont=getch();
    if(cont=='y' || cont=='Y')
    {
        printf("\nEnter number of seats you would like to select :");
        scanf("%d",&no_of_seats);
        if(st[x].seat_left < no_of_seats)
        {
            printf("\nNot enough seats available");
            return;
        }
        int seat_arr[50];
        int sc=0;
        for(int i=0;i<no_of_seats;i++)
        {
            printf("\nEnter seat no :");
            scanf("%d",&seat_no);
            seat_arr[sc++]=seat_no;
            if(st[x].seat[seat_no-1]==1)
            {
                printf("\nSeat already booked or invalid seat  !!");
                goto here;
            }
            // else if(st[x].seat[seat_no-1] >50 || st[x].seat[seat_no-1] < 0)
            // {
            //     printf("\nSeat already booked or invalid seat  !!");
            //     goto here;
            // }
            else if(seat_no >50 || seat_no < 0)
            {
                printf("\nSeat already booked or invalid seat  !!");
                goto here;
            }
        }
        for(int i=0;i<no_of_seats;i++)
        {
            if(st[x].seat[seat_arr[i]-1]==0)
            {
                st[x].seat[seat_arr[i]-1]=1;
            }
            else if(st[x].seat[seat_arr[i]-1]==1)
            {
                for(int i=0;i<sc;i++)
                {
                    st[x].seat[seat_arr[i]-1]=0;
                }
                printf("\nSeat already booked or invalid seat  !!");
                goto here;
            }   
        }
        for(int i=0;i<sc;i++)
        {
            booked_seats[seat_arr[i]-1]=1;
        }
        st[x].seat_left-=no_of_seats;
        transaction(st[x],booked_seats,no_of_seats);
    }
    rewrite(st,xi);  
}
void transaction(show sh,int booked_seats[],int total_seats)
{
    char time[20];
    if(strcmp(sh.stype,"afternoon")==0)
    {
        strcpy(time,"1:30 PM");
    }
    if(strcmp(sh.stype,"evening")==0)
    {
        strcpy(time,"6:30 PM");
    }
    if(strcmp(sh.stype,"night")==0)
    {
        strcpy(time,"10:30 PM");
    }
    purple();
    printf("\n********************************************");
    printf("\n*                                          *");
    printf("\n*                   BILL                   *");
    printf("\n*                                          *");
    printf("\n********************************************");
    printf("\n|NAME          :%-27s|",front->name);
    printf("\n|PHONE NO      :%-27s|",front->pno);
    printf("\n|SHOW ID       :%-27d|",sh.showid);          
    printf("\n|MOVIE NAME    :%-27s|",sh.mname);             
    printf("\n|SHOW TYPE     :%-10s-%-16s|",sh.stype,time); 
    printf("\n|DATE          :%-27s|",sh.date); 
    printf("\n|N(SEATS)      :%-27d|",total_seats);   
    printf("\n|SEATS BOOKED  :");
    for(int i=0;i<50;i++)
    {
        if(booked_seats[i]==1)
        {
            printf(" %d",i+1);
        }
    }
    printf("\n--------------------------------------------");
    printf("\n|TOTAL AMOUNT  : %d X 175 = Rs%d",total_seats,total_seats*175); 
    printf("\n--------------------------------------------");  
    reset();
    trans tr;
    strcpy(tr.name,front->name);
    strcpy(tr.pno,front->pno);
    tr.showid=sh.showid;
    strcpy(tr.mname,sh.mname);
    strcpy(tr.stype,sh.stype);
    strcpy(tr.date,sh.date);         
    tr.total_seats=total_seats;
    for(int i=0;i<50;i++)
    {
        tr.booked_seats[i]=booked_seats[i];
    }
    tr.amount=total_seats*175; 
    FILE *fws= fopen ("transaction.txt", "a");
    fwrite (&tr, sizeof(struct trans), 1, fws);
    fclose(fws);             
    dequeue();
}
void showtransaction()
{
    int trans_id=1000;
    trans tr;
    FILE *frs;
    frs=fopen("transaction.txt", "r");
    purple();
    printf("\n                                                 +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+");
    printf("\n                                                 |                                                         |");
    printf("\n                                                 |                      BOOKING HISTORY                    |");
    printf("\n                                                 |                                                         |");
    printf("\n                                                 +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+");
    printf("\n_________________________________________________________________________________________________________________________________________________________________________");
    printf("\n|        |                   |          |                            |          |       |           |        |        |                                                 |");
    printf("\n|TRANS ID|        NAME       | PHONE NO |          MOVIE NAME        |   DATE   |SHOW ID| SHOW TYPE | AMOUNT |N(SEATS)|             SEATS CHOSEN                        |");
    printf("\n|________|___________________|__________|____________________________|__________|_______|___________|________|________|_________________________________________________| ");  
                                                     
    while(fread(&tr, sizeof(struct trans), 1, frs))
    {
       printf("\n|%-8d|%-19s|%-10s|%-28s|%-10s|%-7d|%-11s|%-8d|%-8d|",trans_id++,tr.name,tr.pno,tr.mname,tr.date,tr.showid,tr.stype,tr.amount,tr.total_seats);  
        for(int i=0;i<50;i++)
        {
            if(tr.booked_seats[i]==1)
            {
                printf(" %d",i+1);
            }
        }
        printf("\n|________|___________________|__________|____________________________|__________|_______|___________|________|________|_________________________________________________| ");    

    }
    
    fclose(frs);
    reset();
}
void addmovie()
{
    char mname[25];
    char language[25];
    float rating;
    char certification[5];
    mov m;
    printf("\nEnter name of the movie : ");
    fflush(stdin);
    gets(mname);
    printf("\nEnter language of the movie : ");
    scanf("%s",language);
    printf("\nEnter rating of the movie : ");
    scanf("%f",&rating);
    printf("\nEnter certivation of the movie :");
    scanf("%s",certification);
    strcpy(m.mname,mname);
    strcpy(m.language,language);
    strcpy(m.certification,certification);
    m.rating=rating;
    FILE *fws= fopen ("moviedetails.txt", "a");
    fwrite (&m, sizeof(struct mov), 1, fws);
    fclose(fws);             
}
void sortmovie()
{
    int ch;
    printf("\n1.Show all movies sorted by RATINGS.");
    printf("\n2.Show all movies of a particular LANGUAGE sorted by ratings.");
    printf("\n3.Show all movies of a particular CERTIFICATION sorted by ratings.");
    printf("\nEnter choice :");
    scanf("%d", &ch);
    mov m,t;
    mov ms[20];
    int cm=0;

    FILE *frs;
    frs=fopen("moviedetails.txt", "r");
    while(fread(&m, sizeof(struct mov), 1, frs))
    {
        strcpy(ms[cm].mname,m.mname);
        strcpy(ms[cm].language,m.language);
        strcpy(ms[cm].certification,m.certification);
        ms[cm].rating=m.rating; 
        cm++;
    }
    for(int i=0;i<cm;i++)
    {
        for(int j=0;j<cm-i-1;j++)
        {
            if(ms[j].rating<ms[j+1].rating)
            {
                t=ms[j];
                ms[j]=ms[j+1];
                ms[j+1]=t;
            }
        }
    }
    if(ch==1)
    {
        purple();
        printf("\n                          +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+");
        printf("\n                          |                             |");
        printf("\n                          |         MOVIE DETAILS       |");
        printf("\n                          |                             |");
        printf("\n                          +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+");
        printf("\n______________________________________________________________________________________");
        printf("\n|                                       |                   |               |        |");
        printf("\n|             MOVIE NAME                |     LANGUAGE      | CERTIFICATION | RATING | ");
        printf("\n|_______________________________________|___________________|_______________|________|");
        for(int i=0;i<cm;i++)
        {
            FILE * f1 = fopen("shows.txt", "r");
            show s;
            while(fread(&s,sizeof(s),1,f1))
            {
                    if(strcmp(ms[i].mname,s.mname)==0)
                    {
                        printf("\n|%-39s|%-19s|%-15s|%-8.1f|",ms[i].mname,ms[i].language,ms[i].certification,ms[i].rating);
                        printf("\n|_______________________________________|___________________|_______________|________|");
                        break;
                    }        
            }
            
            fclose(f1);
        }
        reset();
    }
    if(ch==2)
    {
        char lang[25];
        purple();
        printf("\nEnter language to sort :");
        scanf("%s",lang);
        printf("\n                          +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+");
        printf("\n                          |                             |");
        printf("\n                          |         MOVIE DETAILS       |");
        printf("\n                          |                             |");
        printf("\n                          +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+");
        printf("\n______________________________________________________________________________________");
        printf("\n|                                       |                   |               |        |");
        printf("\n|             MOVIE NAME                |     LANGUAGE      | CERTIFICATION | RATING | ");
        printf("\n|_______________________________________|___________________|_______________|________|");
        for(int i=0;i<cm;i++)
        {
            if(strcmp(lang,ms[i].language)==0)
            {
                FILE * f1 = fopen("shows.txt", "r");
                show s;
                while(fread(&s,sizeof(s),1,f1))
                {
                    if(strcmp(ms[i].mname,s.mname)==0)
                    {
                        printf("\n|%-39s|%-19s|%-15s|%-8.1f|",ms[i].mname,ms[i].language,ms[i].certification,ms[i].rating);
                        printf("\n|_______________________________________|___________________|_______________|________|");
                        break;
                    }    
                }
                fclose(f1);
            }
        }
        reset();
    }
    if(ch==3)
    {
        purple();
        char cert[25];
        printf("\nEnter certification to sort :");
        scanf("%s",cert);
        printf("\n                          +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+");
        printf("\n                          |                             |");
        printf("\n                          |         MOVIE DETAILS       |");
        printf("\n                          |                             |");
        printf("\n                          +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+");
        printf("\n______________________________________________________________________________________");
        printf("\n|                                       |                   |               |        |");
        printf("\n|             MOVIE NAME                |     LANGUAGE      | CERTIFICATION | RATING | ");
        printf("\n|_______________________________________|___________________|_______________|________|");
        for(int i=0;i<cm;i++)
        {
            if(strcmp(cert,ms[i].certification)==0)
            {
                FILE * f1 = fopen("shows.txt", "r");
                show s;
                while(fread(&s,sizeof(s),1,f1))
                {
                    if(strcmp(ms[i].mname,s.mname)==0)
                    {
                        
                        printf("\n|%-39s|%-19s|%-15s|%-8.1f|",ms[i].mname,ms[i].language,ms[i].certification,ms[i].rating);
                        printf("\n|_______________________________________|___________________|_______________|________|");
                        break;
                    }    
                }
                fclose(f1);
                
            }
        }
    }
    reset();
    fclose(frs);
}
void createshow()
{
    show s[30];
    FILE * f = fopen ("moviedetails.txt", "r");
    mov m;
    if(f==NULL)
    {
        printf("\nNo movies added to create show !!");
        fclose(f);
        return;
    }
    int showid,x=0;
    char moviename[30],showtype[30];
    char date[10];    
    FILE *frs;
    frs=fopen("shows.txt", "r"); 
    if (frs == NULL) 
    {
      showid=1000;
      count=1;
    }
    else
    {
        show sh;
        int co=0;
        while(fread(&sh, sizeof(struct show), 1, frs)) 
        {
            s[co].showid=sh.showid;
            for(int i=0;i<50;i++) 
            {
                s[co].seat[i]=sh.seat[i];
            }
            strcpy(s[co].mname,sh.mname);
            strcpy(s[co].stype,sh.stype);
            strcpy(s[co].date,sh.date); 
            s[co].seat_left=sh.seat_left; 
            co+=1;
        }
        count=co+1;
        fclose(frs);
        showid=1000+co;
    }
    x=(showid-1000);
    purple();
    printf("\nSelect a movie from the list to create a show :");
    printf("\n_________________________________________");
    printf("\n|                                       |");
    printf("\n|             MOVIE NAME                |");
    printf("\n|_______________________________________|");
    
    while(fread(&m,sizeof(mov),1,f))
    {
        printf("\n|%-39s|",m.mname);
        printf("\n|_______________________________________|");
    }
    reset();
    fclose(f);
    selectmovie:
    printf("\nEnter name of the movie : ");
    fflush(stdin);
    gets(moviename);
    FILE * f1 = fopen ("moviedetails.txt", "r");
    mov m1;
    int flag=0;
    while(fread(&m1,sizeof(mov),1,f1))
    {
        if(strcmp(m1.mname,moviename)==0)
        {
            s[x].showid=showid;
            strcpy(s[x].mname,moviename);
            printf("\nEnter the showtype : ");
            scanf("%s",showtype);
            strcpy(s[x].stype,showtype);
            printf("\nEnter date : ");
            scanf("%s",date);
            strcpy(s[x].date,date);  
            s[x].seat_left=50;
            for(int i=0;i<50;i++) 
            {
                s[x].seat[i]=0;
            }
            FILE *fws= fopen ("shows.txt", "w");
            fwrite(s,sizeof(struct show), x+1, fws);
            fclose(fws);
            flag=1;
        }
    }
    if(flag==0)
    {
        printf("\nThe movie name does not exist Please try again !!");
        fclose(f1);
        goto selectmovie;
    }
    fclose(f1);


}
void displayshow()
{
    show sh;
    char time[20];
    int sid=1000,ct=0;
    FILE *frs;
    frs=fopen("shows.txt", "r");
    purple();
    printf("\n                                 +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+");
    printf("\n                                 |                             |");
    printf("\n                                 |            SHOWS            |");
    printf("\n                                 |                             |");
    printf("\n                                 +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+");
    printf("\n_____________________________________________________________________________________________________");
    printf("\n|                                       |                         |           |           |         |");
    printf("\n|              MOVIE NAME               |         SHOW TYPE       |    TIME   |    DATE   | SHOW ID |");
    printf("\n|_______________________________________|_________________________|___________|___________|_________|\n");
    while(fread(&sh, sizeof(struct show), 1, frs) /* || ct<count*/)  
    {
        printf("|%-39s|%-25s|",sh.mname,sh.stype);
        if(strcmp(sh.stype,"afternoon")==0)
        {
            strcpy(time,"1:30 PM");
        }
        if(strcmp(sh.stype,"evening")==0)
        {
            strcpy(time,"6:30 PM");
        }
        if(strcmp(sh.stype,"night")==0)
        {
            strcpy(time,"10:30 PM");
        }
        printf("%-11s|%-11s|%-9d|",time,sh.date,sh.showid); 
        printf("\n|_______________________________________|_________________________|___________|___________|_________|\n");
        ct+=1;
    }
    reset();
    fclose(frs);
}
void main() 
{
    show s[30];
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<50;j++)
        {
            s[i].seat[j]=0;
        }
        s[i].seat_left=50;
    }
    blue();
    printf("\t\t\t\t*************************************************");
    printf("\n\t\t\t\t*\t\t\t\t\t\t*\n\t\t\t\t*\t\t\t\t\t\t*\n\t\t\t\t*\t");
    printf("MOVIE BOOKING MANAGEMENT SYSTEM    \t*\n\t\t\t\t*\t\t\t\t\t\t*\n");
    printf("\t\t\t\t*\t\t\t\t\t\t*\n\t\t\t\t********************************");
    printf("*****************");
    login();
    readqueue();
    int no_of_shows_in_file=0;
    show sh;
    FILE * frs= fopen ("shows.txt","r");
    while(fread(&sh, sizeof(struct show), 1, frs))
    {
        no_of_shows_in_file+=1;//
    }
    count=no_of_shows_in_file;
    fclose(frs);
    printf("\n");
    while(1==1)
    {
        yellow();
        printf("\n");
        printf("+-------------------------------------+\n");
	    printf("|                MENU                 |\n");
        printf("+-------------------------------------+\n");
	    printf("+         1- ADD TO QUEUE             +\n");
        printf("+         2- BOOK TICKETS             +\n");
        printf("+         3- CREATE SHOW              +\n");
        printf("+         4- DISPLAY SHOW             +\n");
        printf("+         5- SHOW BOOKING HISTORY     +\n");
        printf("+         6- ADD MOVIE                +\n");
        printf("+         7- DISPLAY SORTED MOVIES    +\n");
	    printf("+         8- EXIT SYSTEM              +\n");
	    printf("+-------------------------------------+\n");
        int ch;
        printf("Enter choice : ");
        reset();
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                enqueue();
                writequeue();
            break;
            case 2:book(s);
            break;
            case 3:createshow();
            break;
            case 4:displayshow();
            break;
            case 5:showtransaction();
            break;
            case 6:addmovie();
            break;
            case 7:sortmovie();
            break;
            case 8:exit(0);
            break;
            default:printf("\nInvalid choice!!");
            break;
        }
    }
}