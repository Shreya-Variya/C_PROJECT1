#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct bank
{
    int ac_no;
    char name[20];
    char ac_type[20];
    float balance;
    float amt_deposit;
    float amt_withdraw;
    char branch[20];  
    struct address
    {
        char city[20];
        char state[20];
    }a;
}b;

int empty()
{
    int c=0;
    FILE *fp;
    fp = fopen("Account_holders_record","r");
    while (fread(&b,sizeof(b),1,fp))
    {
        c=1;
    }
    fclose(fp);
    return c;
}

int available(int ac_no)
{
    FILE *fp;
    fp = fopen("Account_holders_record","r");
    while (!feof(fp))
    {
        fread(&b,sizeof(b),1,fp);
        if(ac_no==b.ac_no)
        {
            fclose(fp);
            return 1;
        }
        else
        {
            fclose(fp);
            return 0;
        }
    }    
}

void printmenu()
{
    printf("\n******************** SELECT ANY ONE OPTION ********************");
    printf("\n\t\t\t1.INSERT.");
    printf("\n\t\t\t2.DISPLAY.");
    printf("\n\t\t\t3.UPDATE.");
    printf("\n\t\t\t4.DELETE.");
    printf("\n\t\t\t5.SORT.");
    printf("\n\t\t\t6.SEARCH BY NAME.");
    printf("\n\t\t\t7.SEARCH BY ACCOUNT NUMBER.");
    printf("\n\t\t\t8.SEARCH BY ACCOUNT TYPE.");
    printf("\n\t\t\t9.EXIT.");
}

void insert()
{
    FILE *fp;
    fp = fopen("Account_holders_record","a");

    printf("Enter the account number : ");
    scanf("%d",&b.ac_no);
    printf("Enter the name of account holder : ");
    scanf("%s",b.name);
    printf("Enter the type of account : ");
    scanf("%s",b.ac_type);
    printf("Enter the total amount of balance : ");
    scanf("%f",&b.balance);
    printf("Enter the deposited amount : ");
    scanf("%f",&b.amt_deposit);
    printf("Enter the withdraw amount : ");
    scanf("%f",&b.amt_withdraw);
    printf("Enter the bank branch : ");
    scanf("%s",b.branch);
    printf("Enter the Address : ");
    printf("\nEnter the city : ");
    scanf("%s",b.a.city);
    printf("Enter the state : ");
    scanf("%s",b.a.state);

    fwrite(&b,sizeof(b),1,fp);

    fclose(fp);
}

void display()
{
    FILE *fp1;

    fp1 = fopen("Account_holders_record","r");

    printf("\nAc_no\t\tName\t\tType\t\tBalance\t\tDeposit\t\tWithdraw\tBranch\t\tCity\t\tState\n");
    while (fread(&b,sizeof(b),1,fp1))
    {
        printf("\n%d\t\t%s\t\t%s\t\t%.2f\t%.2f\t%.2f\t%s\t\t%s\t\t%s\n",b.ac_no,b.name,b.ac_type,b.balance,b.amt_deposit,b.amt_withdraw,b.branch,b.a.city,b.a.state);
    }
    fclose(fp1);
}

void update()
{
    int avl;
    FILE *fpt;
    FILE *fpo;
    int s,r,ch,d,w;

    printf("Enter the account number to update : ");
    scanf("%d",&r);

    avl = available(r);
    d = b.amt_deposit;
    w = b.amt_withdraw;

    if(avl==0)
    {
        printf("\nEntered account number is not available.");
    }
    else
    {
        fpo = fopen("Account_holders_record","r");
        fpt = fopen("TempFile","w");
        while (fread(&b,sizeof(b),1,fpo))
        {
            s = b.ac_no;
            if(s!=r)
            {
                fwrite(&b,sizeof(b),1,fpt);
            }
            else
            {
                printf("\n1.UPDATE THE NAME OF AC_NO %d.",r);
                printf("\n2.UPDATE THE ADDRESS OF AC_NO %d.",r);
                printf("\n3.UPDATE THE DEPOSITED AMOUNT.");
                printf("\n4.UPDATE THE WITHDRAWEL AMOUNT.");
                printf("\nEnter the choice : ");
                scanf("%d",&ch);

                switch (ch)
                {
                case 1:
                    printf("\nEnter the name : ");
                    scanf("%s",b.name);
                    break;

                case 2: 
                    printf("\nEnter the updated address : ");
                    printf("\nEnter the city : ");
                    scanf("%s",b.a.city);
                    printf("\nEnter the state : ");
                    scanf("%s",b.a.state);
                    break;

                case 3:
                    printf("\nEnter the updated amount of deposit : ");
                    scanf("%f",&b.amt_deposit);
                    b.balance = b.balance + b.amt_deposit;
                    b.amt_deposit = d + b.amt_deposit;
                    break;

                case 4:
                    printf("\nEnter the updated amount of withdrawel : ");
                    scanf("%f",&b.amt_withdraw);
                    b.balance = b.balance - b.amt_withdraw;
                    b.amt_withdraw = w + b.amt_withdraw;
                    break;

                default:
                    printf("\nInvalid Selection.");
                    break;
                }
                fwrite(&b,sizeof(b),1,fpt);
            }
        }
        fclose(fpo);
        fclose(fpt);
        fpo = fopen("Account_holders_record","w");
        fpt = fopen("TempFile","r");

        while (fread(&b,sizeof(b),1,fpt))
        {
            fwrite(&b,sizeof(b),1,fpo);
        }
        fclose(fpo);
        fclose(fpt);
        printf("\nRECORD UPDATED.");    
    }
}

void delete()
{
    FILE *fpo;
    FILE *fpt;
    int r,s;
    printf("\nEnter the account number you want to delete : ");
    scanf("%d",&r);

    if(available(r)==0)
    {
        printf("\nEntered account number is not available.");
    }
    else
    {
        fpo = fopen("Account_holders_record","r");
        fpt = fopen("TempFile","w");
        while (fread(&b,sizeof(b),1,fpo))
        {
            s = b.ac_no;
            if(s!=r)
            {
                fwrite(&b,sizeof(b),1,fpt);
            }
        }
        fclose(fpo);
        fclose(fpt);
        fpo = fopen("Account_holders_record","w");
        fpt = fopen("TempFile","r");
        while (fread(&b,sizeof(b),1,fpt))
        {
            fwrite(&b,sizeof(b),1,fpo);
        }
        fclose(fpo);
        fclose(fpt);
        printf("\nRECORD DELETED."); 
    }
}

void sort()
{
    int a[20],i,j,t,c,count = 0;
    FILE *fpo;

    fpo = fopen("Account_holders_record","r");
    while(fread(&b,sizeof(b),1,fpo))
    {
        a[count] = b.ac_no;
        count++;
    }
    c=count;

    for(i=0 ; i<count ; i++)
    {
        for(j=i+1 ; j<count ; j++)
        {
            if(a[i]>a[j])
            {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }

    printf("\nAc_no\t\tName\t\tType\t\tBalance\t\tDeposit\t\tWithdraw\tBranch\t\tCity\t\tState\n");

    count = c;

    for(i=0 ; i<count ; i++)
    {
        rewind(fpo);
        while(fread(&b,sizeof(b),1,fpo))
        {
            if(a[i] == b.ac_no)
            {
                printf("\n%d\t\t%s\t\t%s\t\t%.2f\t%.2f\t%.2f\t%s\t\t%s\t\t%s\n",b.ac_no,b.name,b.ac_type,b.balance,b.amt_deposit,b.amt_withdraw,b.branch,b.a.city,b.a.state);
            }
        }
    }
}

void search_by_name()
{
    FILE *fp2;
    char name[20];
    int c=0;

    printf("\nEnter the name you want to search : ");
    scanf("%s",name);

    fp2 = fopen("Account_holders_record","r");
    while(fread(&b,sizeof(b),1,fp2))
    {
        if(strcmp(name,b.name)==0)
        {
            printf("\n%d\t\t%s\t\t%s\t\t%.2f\t%.2f\t%.2f\t%s\t\t%s\t\t%s\n",b.ac_no,b.name,b.ac_type,b.balance,b.amt_deposit,b.amt_withdraw,b.branch,b.a.city,b.a.state);
            c++;
        }
    }
    if (c==0)
    {
        printf("\nNo of record fount with name %s.",name);
    }
    else
    {
        printf("\n%d record found.",c);
    }
    fclose(fp2);
}

void search_by_ac_no()
{
    FILE *fp2;
    int ac_no;
    int c=0;

    printf("\nEnter the account number you want to search : ");
    scanf("%d",&ac_no);

    fp2 = fopen("Account_holders_record","r");
    while(fread(&b,sizeof(b),1,fp2))
    {
        if(ac_no == b.ac_no)
        {
            printf("\n%d\t\t%s\t\t%s\t\t%.2f\t%.2f\t%.2f\t%s\t\t%s\t\t%s\n",b.ac_no,b.name,b.ac_type,b.balance,b.amt_deposit,b.amt_withdraw,b.branch,b.a.city,b.a.state);
            c++;
        }
    }
    if (c==0)
    {
        printf("\nNo record found with %d account number.",ac_no);
    }
    else
    {
        printf("\n%d record found.",c);
    }
    fclose(fp2);
}

void search_by_ac_type()
{
    FILE *fp2;
    char ac_type[20];
    int c=0;

    printf("Enter the account type you want to search : ");
    scanf("%s",ac_type);

    fp2 = fopen("Account_holders_record","r");
    while(fread(&b,sizeof(b),1,fp2))
    {
        if(strcmp(ac_type,b.ac_type)==0)
        {
            printf("\n%d\t\t%s\t\t%s\t\t%.2f\t%.2f\t%.2f\t%s\t\t%s\t\t%s\n",b.ac_no,b.name,b.ac_type,b.balance,b.amt_deposit,b.amt_withdraw,b.branch,b.a.city,b.a.state);
            c++;
        }
    }
    if (c==0)
    {
        printf("\nNo of record fount with %s account type.",ac_type);
    }
    else
    {
        printf("\n%d record found.",c);
    }
    fclose(fp2);

}

int main()
{
    int c,emp;
    do
    {
        printmenu();

        printf("\nEnter your choice : ");
        scanf("%d",&c);
        printf("\n");

        switch (c)
        {
        case 1:
            insert();
            break;

        case 2:
            emp = empty();
            if(emp<=0)
            {
                printf("\nFILE IS EMPTY.\n");
            }
            else
            {
                display();
            }
            break;  

        case 3:
            update();
            break; 

        case 4:
            delete();
            break; 

        case 5:
            emp = empty();
            if(emp<=0)
            {
                printf("\nFILE IS EMPTY.\n");
            }
            else
            {
                sort();
            }
            break;  

        case 6:
            search_by_name();
            break;    

        case 7:
            search_by_ac_no();
            break;

        case 8:
            search_by_ac_type();
            break;  

        case 9:
            printf("\nTNE END.");
            exit(1);
            break;    
        
        default:
            printf("\nEnter correct choice.");
            break;
        }
    }
    while(c!=9);
    return 0;
}