#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
int password();
void addrecord();
void viewrecord();
void editrecord();
void editpassword();
void deleterecord();

struct record

{

    char time[6];
    char name[30];
    char place[25];
    char duration[10];
    char note[500];

} ;

int main()

{

    int ch;
    printf("\n\n\t***********************************\n");
    printf("\t*Password protected personal diary*\n");
    printf("\t***********************************");

    while(1)

    {

        printf("\n\n\t\tMain Menu:");
        printf("\n\n\tAdd Record\t[1]");
        printf("\n\tView Record\t[2]");
        printf("\n\tEdit Record\t[3]");
        printf("\n\tDelete Record\t[4]");
        printf("\n\tEdit Password\t[5]");
        printf("\n\tEXIT\t\t[6]");
        printf("\n\n\tEnter Your Selection:");
        scanf("%d",&ch);

        switch(ch)

        {

        case 1:

            addrecord();
            break;

        case 2:

            viewrecord();
            break;

        case 3:

            editrecord();
            break;

        case 4:

            deleterecord();
            break;

        case 5:

            editpassword();
            break;

        case 6:

            printf("\n\n\t\tThank You For Using The Software ");
            getch();
            exit(0);

        default:

            printf("\nYou've Entered the Incorrect option");
            printf("\nPress Any Key To Try Again");
            getch();

            break;

        }

        system("cls");

    }

    return 0;

}

void addrecord( )

{

    system("cls");
    FILE *fp ;
    char another = 'Y' ,time[10];
    struct record e ;
    char filename[15];
    int choice;
    printf("\n\n\t\t***************************\n");
    printf("\t\t* Welcome To The Add Menu *");
    printf("\n\t\t***************************\n\n");
    printf("\n\n\tEnter The Date Of Your Record:[yyyy-mm-dd]:");
    fflush(stdin);
    gets(filename);

    fp = fopen (filename, "ab+" ) ;

    if ( fp == NULL )

    {

        fp=fopen(filename,"wb+");

        if(fp==NULL)

        {

            printf("\nSYSTEM ERROR...");
            printf("\nPRESS ANY KEY TO EXIT");
            getch();

            return ;

        }

    }

    while ( another == 'Y'|| another=='y' )

    {

        choice=0;
        fflush(stdin);
        printf ( "\n\tEnter Time:[hh:mm]:");
        scanf("%s",time);
        rewind(fp);

        while(fread(&e,sizeof(e),1,fp)==1)

        {

            if(strcmp(e.time,time)==0)

            {

                printf("\n\tThe Record Already Exists.\n");

                choice=1;

            }

        }

        if(choice==0)

        {

            strcpy(e.time,time);
            printf("\tEnter Name:");
            fflush(stdin);
            gets(e.name);
            fflush(stdin);
            printf("\tEnter Place:");
            gets(e.place);
            fflush(stdin);
            printf("\tEnter Duration:");
            gets(e.duration);
            fflush(stdin);
            printf("\tNote:");
            gets(e.note);
            fwrite ( &e, sizeof ( e ), 1, fp ) ;

            printf("\nYOUR RECORD IS ADDED...\n");

        }

        printf ( "\n\tADD ANOTHER RECORD...(Y/N) " ) ;

        fflush ( stdin ) ;

        another = getchar( ) ;

    }

    fclose ( fp ) ;

    printf("\n\n\tPRESS ANY KEY TO EXIT...");

    getch();

}

void viewrecord( )

{

    FILE *fpte ;
    system("cls");
    struct record customer ;
    char time[6],choice,filename[14];
    int ch;
    printf("\n\n\t\t*******************************\n");
    printf("\t\t* Here is the viewing menu *");
    printf("\n\t\t*******************************\n\n");
    choice=password();
    if(choice!=0)

    {

        return ;

    }

    do

    {

        printf("\n\tEnter The Date Of The Record To Be Viewed:[yyyy-mm-dd]:");
        fflush(stdin);
        gets(filename);
        fpte = fopen ( filename, "rb" ) ;
        if ( fpte == NULL )

        {

            puts ( "\nSpecified Record Dosen't Exist...\n" ) ;
            printf("PRESS ANY KEY TO EXIT...");
            getch();

            return ;

        }

        system("cls");
        printf("\n\tHow Would You Like To View:\n");
        printf("\n\t1.Whole Record Of The Day.");
        printf("\n\t2.Record of Fix Time.");
        printf("\n\t\tEnter Your Choice:");

        scanf("%d",&ch);

        switch(ch)

        {

        case 1:

            printf("\nThe Whole Record For %s Is:",filename);

            while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )

            {

                printf("\n");

                printf("\nTime: %s",customer.time);
                printf("\nMeeting With: %s",customer.name);
                printf("\nMeeting At: %s",customer.place);
                printf("\nDuration: %s",customer.duration);
                printf("\nNote: %s",customer.note);

                printf("\n");

            }

            break;

        case 2:

            fflush(stdin);

            printf("\nEnter Time:[hh:mm]:");

            gets(time);

            while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )

            {

                if(strcmp(customer.time,time)==0)

                {

                    printf("\nYour Record Is:");
                    printf("\nTime: %s",customer.time);
                    printf("\nMeeting With: %s",customer.name);
                    printf("\nMeeting At: %s",customer.place);
                    printf("\nDuration: %s",customer.duration);
                    printf("\nNote: %s",customer.note);

                }

            }

            break;

        default:
            printf("\nYou Had Typed Something Else...\n");

            break;

        }

        printf("\n\nWould You Like To Continue Viewing...(Y/N):");

        fflush(stdin);

        scanf("%c",&choice);

    }
    while(choice=='Y'||choice=='y');

    fclose ( fpte ) ;

    return ;

}

void editrecord()

{

    system("cls");

    FILE *fpte ;

    struct record customer ;

    char time[6],choice,filename[14];

    int num,count=0;

    printf("\n\n\t\t*******************************\n");
    printf("\t\t* Welcome To The Editing Menu *");
    printf("\n\t\t*******************************\n\n");

    choice=password();

    if(choice!=0)

    {

        return ;

    }

    do

    {

        printf("\n\tEnter The Date Of Record To Be Edited:[yyyy-mm-dd]:");
        fflush(stdin);
        gets(filename);
        printf("\n\tEnter Time:[hh:mm]:");
        gets(time);

        fpte = fopen ( filename, "rb+" ) ;

        if ( fpte == NULL )

        {

            printf( "\nRecord Does Not Exist:" ) ;
            printf("\nPress Any Key To Go Back");
            getch();

            return;

        }

        while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )

        {

            if(strcmp(customer.time,time)==0)

            {

                printf("\nYour Old Record was:");
                printf("\nTime: %s",customer.time);
                printf("\nMeeting With: %s",customer.name);
                printf("\nMeeting At: %s",customer.place);
                printf("\nDuration: %s",customer.duration);
                printf("\nNote: %s",customer.note);
                printf("\n\n\t\tWhat Would You Like To Edit..");
                printf("\n1.Time.");
                printf("\n2.Meeting Person.");
                printf("\n3.Meeting Place.");
                printf("\n4.Duration.");
                printf("\n5.Note.");
                printf("\n6.Whole Record.");
                printf("\n7.GO BACK TO MAIN MENU.");

                do

                {

                    printf("\n\tEnter Your Selection:");
                    fflush(stdin);
                    scanf("%d",&num);
                    fflush(stdin);

                    switch(num)

                    {

                    case 1:
                        printf("\nEnter The New Data:");
                        printf("\nNew Time:[hh:mm]:");
                        gets(customer.time);

                        break;

                    case 2:
                        printf("\nEnter The New Data:");
                        printf("\nNew Meeting Person:");
                        gets(customer.name);

                        break;

                    case 3:
                        printf("\nEnter The New Data:");
                        printf("\nNew Meeting Place:");
                        gets(customer.place);

                        break;

                    case 4:
                        printf("\nEnter The New Data:");
                        printf("\nDuration:");
                        gets(customer.duration);
                        break;

                    case 5:
                        printf("Enter The New Data:");
                        printf("\nNote:");
                        gets(customer.note);
                        break;

                    case 6:
                        printf("\nEnter The New Data:");
                        printf("\nNew Time:[hh:mm]:");
                        gets(customer.time);
                        printf("\nNew Meeting Person:");
                        gets(customer.name);
                        printf("\nNew Meeting Place:");
                        gets(customer.place);
                        printf("\nDuration:");
                        gets(customer.duration);
                        printf("\nNote:");
                        gets(customer.note);

                        break;

                    case 7:
                        printf("\nPRESS ANY KEY TO GO BACK...\n");
                        getch();
                        return ;
                        break;

                    default:
                        printf("\nYou Typed Something Else...Try Again\n");

                        break;

                    }

                }
                while(num<1||num>8);

                fseek(fpte,-sizeof(customer),SEEK_CUR);
                fwrite(&customer,sizeof(customer),1,fpte);
                fseek(fpte,-sizeof(customer),SEEK_CUR);
                fread(&customer,sizeof(customer),1,fpte);

                choice=5;

                break;

            }

        }

        if(choice==5)

        {

            system("cls");
            printf("\n\t\tEditing Completed...\n");
            printf("--------------------\n");
            printf("The New Record Is:\n");
            printf("--------------------\n");
            printf("\nTime: %s",customer.time);
            printf("\nMeeting With: %s",customer.name);
            printf("\nMeeting At: %s",customer.place);
            printf("\nDuration: %s",customer.duration);
            printf("\nNote: %s",customer.note);

            fclose(fpte);
            printf("\n\n\tWould You Like To Edit Another Record.(Y/N)");
            scanf("%c",&choice);

            count++;

        }

        else

        {

            printf("\nThe Selected Record Does Not Exist::\n");
            printf("\nWould You Like To Try Again...(Y/N)");
            scanf("%c",&choice);

        }

    }
    while(choice=='Y'||choice=='y');
    fclose ( fpte ) ;
    if(count==1)
        printf("\n%d File Is Edited...\n",count);
    else if(count>1)
        printf("\n%d Files Are Edited..\n",count);
    else
        printf("\nNo Files Were Edited...\n");
    printf("\tPRESS ENTER TO EXIT EDITING MENU.");

    getch();

}

int password()

{

    char pass[15]= {0},check[15]= {0},ch;
    FILE *fpp;
    int i=0,j;
    printf("::For Security Purpose::");
     printf("::Only Three Tries are Allowed::");

    for(j=0; j<3; j++)

    {

        i=0;

        printf("\n\n\tEnter The Password:");
        pass[0]=getch();
        while(pass[i]!='\r')

        {

            if(pass[i]=='\b')

            {

                i--;

                printf("\b");
                printf(" ");
                printf("\b");

                pass[i]=getch();

            }

            else

            {

                printf("*");
                i++;
                pass[i]=getch();

            }

        }

        pass[i]='\0';
        fpp=fopen("SE","r");

        if (fpp==NULL)

        {

            printf("\nError With The System File...[FILE MISSING]\n");
            getch();

            return 1;

        }

        else

            i=0;

        while(1)

        {

            ch=fgetc(fpp);

            if(ch==EOF)

            {

                check[i]='\0';
                break;

            }

            check[i]=ch-5;

            i++;

        }

        if(strcmp(pass,check)==0)

        {

            printf("\n\n\tAccess Granted...\n");
            return 0;

        }

        else

        {

            printf("\n\n\tWrong Password..\n\n\tAccess Denied...\n");

        }

    }

    printf("\n\n\t::You Entered the Wrond Password::You Are Not Allowed To Access Any File::\n\n\tPRESS ANY KEY TO GO BACK...");
    getch();
    return 1;

}

void editpassword()

{

    system("cls");
    printf("\n");
    char pass[15]= {0},confirm[15]= {0},ch;
    int choice,i,check;
    FILE *fp;
    fp=fopen("SE","rb");
    if(fp==NULL)
    {

        fp=fopen("SE","wb");
        if(fp==NULL)

        {

            printf("SYSTEM ERROR...");
            getch();
            return ;

        }

        fclose(fp);
        printf("\nSystem Restored...\nYour Password is 'ENTER'\n PRESS ENTER TO CHANGE PASSWORD\n\n");
        getch();

    }

    fclose(fp);
    check=password();
    if(check==1)

    {
        return ;
    }
    do
    {

        if(check==0)
        {
            i=0;
            choice=0;
            printf("\n\n\tENTER THE NEW PASSWORD:");
            fflush(stdin);
            pass[0]=getch();
            while(pass[i]!='\r')
            {
                if(pass[i]=='\b')
                {

                    i--;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    pass[i]=getch();
                }
                else
                {
                    printf("*");
                    i++;
                    pass[i]=getch();
                }
            }

            pass[i]='\0';
            i=0;
            printf("\n\tCONFIRM PASSWORD:");
            confirm[0]=getch();
            while(confirm[i]!='\r')
            {
                if(confirm[i]=='\b')
                {
                    i--;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    confirm[i]=getch();
                }
                else
                {
                    printf("*");
                    i++;
                    confirm[i]=getch();
                }
            }
            confirm[i]='\0';
            if(strcmp(pass,confirm)==0)
            {
                fp=fopen("SE","wb");
                if(fp==NULL)
                {
                    printf("\n\t\tSYSTEM ERROR");
                    getch();
                    return ;
                }

                i=0;

                while(pass[i]!='\0')
                {
                    ch=pass[i];
                    putc(ch+5,fp);
                    i++;
                }
                putc(EOF,fp);
                fclose(fp);

            }
            else
            {
                printf("\n\tThe New Password Does Not Match.");
                choice=1;

            }

        }

    }
    while(choice==1);
    printf("\n\n\tPassword Changed...\n\n\tPRESS ANY KEY TO GO BACK...");
    getch();

}
void deleterecord( )
{
    system("cls");
    FILE *fp,*fptr ;
    struct record file ;
    char filename[15],another = 'Y' ,time[10];;
    int choice,check;
    printf("\n\n\t\t*************************\n");
    printf("\t\t* Welcome To The Delete Menu*");
    printf("\n\t\t*************************\n\n");
    check = password();
    if(check==1)
    {
        return ;
    }
    while ( another == 'Y' )

    {
        printf("\n\n\tHow Would You Like To Delete.");
        printf("\n\n\t#Delete Whole Record\t\t\t[1]");
        printf("\n\t#Delete A Particular Record By Time\t[2]");
        do

        {
            printf("\n\t\tENTER YOU CHOICE:");
            scanf("%d",&choice);
            switch(choice)
            {
            case 1:
                printf("\n\tEnter The Date Of The Record To Be Deleted:[yyyy-mm-dd]:");
                fflush(stdin);
                gets(filename);
                fp = fopen (filename, "wb" ) ;
                if ( fp == NULL )
                {
                    printf("\nThe File Does Not Exist");
                    printf("\nPress Any Key To Go Back.");
                    getch();
                    return ;
                }
                fclose(fp);
                remove(filename);
                printf("\nDeleted Successfully...");
                break;
            case 2:
                printf("\n\tEnter The Date Of Record:[yyyy-mm-dd]:");
                fflush(stdin);
                gets(filename);
                fp = fopen (filename, "rb" ) ;
                if ( fp == NULL )
                {
                    printf("\nThe File Does Not Exist");
                    printf("\nPress Any Key To Go Back.");
                    getch();
                    return ;
                }
                fptr=fopen("temp","wb");
                if(fptr==NULL)
                {
                    printf("\nSystem Error");
                    printf("\nPRESS ANY KEY TO GO BACK");
                    getch();
                    return ;
                }
                printf("\n\tEnter The Time Of The Record To Be Deleted:[hh:mm]:");
                fflush(stdin);
                gets(time);
                while(fread(&file,sizeof(file),1,fp)==1)
                {
                    if(strcmp(file.time,time)!=0)
                        fwrite(&file,sizeof(file),1,fptr);
                }
                fclose(fp);
                fclose(fptr);
                remove(filename);
                rename("temp",filename);
                printf("\nDeleted Successfully...");
                break;

            default:
                printf("\n\tYou Entered The Wrong Option");
                break;
            }
        }
        while(choice<1||choice>2);
        printf("\n\tWould You Like To Delete Another Record.(Y/N):");
        fflush(stdin);
        scanf("%c",&another);
    }
    printf("\n\n\tPRESS ANY KEY TO EXIT...");
    getch();

}