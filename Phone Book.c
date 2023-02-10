#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
    int day;
    int month;
    int year;
} date;
typedef struct
{
    char lastname[100];
    char firstname[100];
    date DOB;
    char address[100];
    char phonenumber[100];
    char email[100];
} contactinfo;
int n=0;
contactinfo c[100];
char name[100];
void phonumbvalid(char phone[])
{
    int i,notvalid=0;
    for(i=0; i<strlen(phone); i++)
    {
        if(!isdigit(phone[i])&&phone[i]!='+')
        {
            notvalid++;
        }
    }
    while(notvalid)
    {
        printf("\nPlease enter a valid phone number with only digits or '+'! ");
        scanf("%s",phone);
        notvalid=0;
        for(i=0; i<strlen(phone); i++)
        {
            if(!isdigit(phone[i])&&phone[i]!='+')
            {
                notvalid++;
            }
        }
    }
}
void emailVerify(char email[])
{
    int i,g=0,valid=0,space=0,at,inverse=strlen(email);
    for(i=0; i<strlen(email); i++)
    {
        if(email[i]==' ')
        {
            space++;
        }

        if(isalpha(email[i])==0&&email[i]!='.'&&email[i]!='_'&&isdigit(email[i])==0&&email[i]!='@')
        {
            g++;
        }
        if(email[i]=='@')
        {
            at=i;
            valid++;
        }
    }
    if(space!=0||g!=0)
    {
        printf("Please enter a valid email using only: letters,numbers,'_','.','@' and with no spaces and in the form: name@site.com\n");
        getchar();
        gets(email);
        emailVerify(email);
    }

    if(valid!=1||at==0||email[at+1]=='.'||email[at-1]=='.'||email[inverse-1]!='m'||email[inverse-2]!='o'||email[inverse-3]!='c'||email[inverse-4]!='.')
    {
        printf("Please enter a valid email in form: name@site.com\n");
        getchar();
        gets(email);
        emailVerify(email);
    }
}
void DOBverify(int year,int month,int day)
{
    int valid=0;
    if(year<1900||year>2021)
    {
        valid=0;
        while(valid==0)
        {
            printf("\nEnter a valid year from 1900 to 2021! ");
            scanf("%d",&year);
            if(year>1900&&year<2022)
            {
                valid=1;
            }
        }
    }
    if(month>12||month<1)
    {
        valid=0;
        while(valid==0)
        {
            printf("\nEnter a valid month from 1 to 12! ");
            scanf("%d",&month);
            if(month<13&&month>0)
            {
                valid=1;
            }
        }
    }
    if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
    {
        if(day<1||day>31)
        {
            valid=0;
            while(valid==0)
            {
                printf("\nEnter a valid day from 1 to 31! ");
                scanf("%d",&day);
                if(day<32&&day>0)
                {
                    valid=1;
                }
            }
        }
    }
    else if(month==2)
    {
        if(day<1||day>29)
        {
            valid=0;
            while(valid==0)
            {
                printf("\nEnter a valid day from 1 to 29! ");
                scanf("%d",&day);
                if(day<30&&day>0)
                {
                    valid=1;
                }
            }
        }
    }
    else
    {
        if(day<1||day>30)
        {
            valid=0;
            while(valid==0)
            {
                printf("\nEnter a valid day from 1 to 30! ");
                scanf("%d",&day);
                if(day<31&&day>0)
                {
                    valid=1;
                }
            }
        }
    }
}
void load()
{
    FILE*f;
    printf(" Please enter the name of the file you want to edit in the form ' name.txt ' ");
    scanf("%s",name);
    int count=strlen(name);
    while(name[count-1]!='t'||name[count-2]!='x'||name[count-3]!='t'||name[count-4]!='.'||count<=4)
    {
        printf("\nEnter a valid name of the file you want to edit in the form ' name.txt ' ");
        scanf("%s",name);
        count=strlen(name);
    }
    f = fopen(name,"r");
    if (f!= NULL)
    {
        while (!feof(f))
        {
            fscanf(f,"%[^,],",c[n].lastname);
            fscanf(f,"%[^,],",c[n].firstname);
            fscanf(f,"%d-%d-%d,",&c[n].DOB.day,&c[n].DOB.month,&c[n].DOB.year);
            fscanf(f,"%[^,],",c[n].address);
            fscanf(f,"%[^,],",c[n].phonenumber);
            fscanf(f,"%s\n",c[n].email);
            n++;
        }
        fclose (f);
    }
    else
    {
        printf("\nFile Not Found\n");
        load();
    }
}
void Search()
{
    int i,i1=0,s,found=0;
    char L[50];
    printf(" Please enter last name: ");
    getchar();
    gets(L);
    for (i=0; i<n; i++)
    {
        if(strcasecmp(c[i].lastname,L)==0)
        {
            i1++;
            found=1;
            printf("          Contact %d\n",i1);
            printf("Last name: %s\n",c[i].lastname);
            printf("First name: %s\n",c[i].firstname);
            printf("Date of Birth: %d-%d-%d\n",c[i].DOB.day,c[i].DOB.month,c[i].DOB.year);
            printf("Address: %s\n",c[i].address);
            printf("Phone number: %s\n",c[i].phonenumber);
            printf("E-mail: %s\n\n",c[i].email);
        }
    }
    if (found==0)
    {
        printf("Contact not found!\n");
        printf(" To search for an existing contact press '1' to quit press '0'\n");
        scanf("%d",&s);
        while(s!=1&&s!=0)
        {
            printf("Please enter a valid value!\n");
            scanf("%d",&s);
        }
        if(s==0)
        {
            QUIT();
        }
        else if(s==1)
        {
            Search();
        }
    }
}
void sortByLname()
{
    int i,j;
    contactinfo temp;
    for(i=0; i<n-1; i++)
    {
        for(j=0; j<n-1-i; j++)
        {
            if (strcasecmp(c[j].lastname,c[j+1].lastname )==1)
            {
                temp=c[j];
                c[j]=c[j+1];
                c[j+1]=temp;
            }
        }
    }
}
void sortbyDOB()
{
    int i,j;
    contactinfo temporary;
    for(i=0; i<n-1; i++)
    {
        for(j=0; j<n-1-i; j++)
        {
            if (c[j].DOB.year<c[j+1].DOB.year)
            {
                temporary=c[j];
                c[j]=c[j+1];
                c[j+1]=temporary;
            }
            else if (c[j].DOB.year==c[j+1].DOB.year)
            {
                if (c[j].DOB.month<c[j+1].DOB.month)
                {
                    temporary=c[j];
                    c[j]=c[j+1];
                    c[j+1]=temporary;
                }
                else if (c[j].DOB.month==c[j+1].DOB.month)
                {
                    if (c[j].DOB.day<c[j+1].DOB.day)
                    {
                        temporary=c[j];
                        c[j]=c[j+1];
                        c[j+1]=temporary;
                    }
                }
            }
        }
    }
}
void Print()
{
    int x,i;
    printf("Do you want to sort by last name or by Date of birth?\nIf by last name enter '1'\nIf by date of birth enter '2'\nTo quit enter '0':\n");
    scanf("%d",&x);
    while(x!=1&&x!=2&&x!=0)
    {
        printf("Please enter a valid value!\n");
        printf("Do you want to sort by last name or by Date of birth?\nIf by last name enter '1'\nIf by date of birth enter '2':\n");
        scanf("%d",&x);
    }
    if(x==0)
    {
        QUIT();
    }
    if (x==1)
    {
        sortByLname();
        for(i=0; i<n; i++)
        {
            printf("          Contact %d\n",i+1);
            printf("Last name: %s\n",c[i].lastname);
            printf("First name: %s\n",c[i].firstname);
            printf("Date of Birth: %d-%d-%d\n",c[i].DOB.day,c[i].DOB.month,c[i].DOB.year);
            printf("Address: %s\n",c[i].address);
            printf("Phone number: %s\n",c[i].phonenumber);
            printf("E-mail: %s\n\n",c[i].email);
        }
    }
    else if(x==2)
    {
        sortbyDOB();
        for(i=0; i<n; i++)
        {
            printf("          Contact %d\n",i+1);
            printf("Last name: %s\n",c[i].lastname);
            printf("First name: %s\n",c[i].firstname);
            printf("Date of Birth: %d-%d-%d\n",c[i].DOB.day,c[i].DOB.month,c[i].DOB.year);
            printf("Address: %s\n",c[i].address);
            printf("Phone number: %s\n",c[i].phonenumber);
            printf("E-mail: %s\n\n",c[i].email);
        }
    }
}
void ADD()
{
    printf("Please enter last name: ");
    getchar();
    gets(c[n].lastname);
    printf("\nPlease enter first name: ");
    scanf("%s",c[n].firstname);
    printf("\nPlease enter date of birth in form: DD-MM-YYYY ");
    int check=scanf("%d-%d-%d",&c[n].DOB.day,&c[n].DOB.month,&c[n].DOB.year);
    while (check!=3)
    {
        printf("\nPlease enter date of birth in form: DD-MM-YYYY! ");
        check=scanf("%d-%d-%d",&c[n].DOB.day,&c[n].DOB.month,&c[n].DOB.year);
    }
    DOBverify(c[n].DOB.year,c[n].DOB.month,c[n].DOB.day);
    printf("\nPlease enter address: ");
    getchar();
    gets(c[n].address);
    printf("\nPlease enter phone number: ");
    scanf("%s",c[n].phonenumber);
    phonumbvalid(c[n].phonenumber);
    printf("\nPlease enter an email in the form: name@site.com\n ");
    getchar();
    gets(c[n].email);
    emailVerify(c[n].email);
    printf(" Your contact has been added successfully!\n");
    n++;

}
void MODIFY()
{
    int i,v,b,pro,k=0,notvalid2=0,valid=1;
    int p[10];
    char L[50];
    printf(" Please enter last name:");
    getchar();
    gets(L);
    for(i=0; i<n; i++)
    {
        if(strcasecmp(c[i].lastname,L)==0)
        {
            p[k]=i;
            k++;
        }
    }
    if(k==0)
    {
        printf(" Last name not found!");
        printf(" To modify an existing contact press '1' To quit press'0' ");
        scanf("%d",&b);
        while(b!=0&&b!=1)
        {
            printf(" Please enter valid answer!\n");
            scanf("%d",&b);
        }
        if(b==1)
        {
            MODIFY();
        }
        else if (b==0)
        {
            QUIT();
        }
    }
    else if(k==1)
    {
        printf(" You will be modifying contact: %s,%s\n\n",c[p[0]].lastname,c[p[0]].firstname);
        printf(" Do you want to change last name? If yes enter '1' If no enter '0'.");
        scanf("%d",&v);
        while(v!=0&&v!=1)
        {
            printf(" Please enter valid answer!");
            scanf("%d",&v);
        }
        if(v==1)
        {
            printf(" Please enter new last name: ");
            scanf("%s",c[p[0]].lastname);
        }
        else if (v==0)
        {
            printf("\n OK.\n");
        }
        printf(" Do you want to change first name? If yes enter '1' If no enter '0'.");
        scanf("%d",&v);
        while(v!=0&&v!=1)
        {
            printf(" Please enter valid answer!");
            scanf("%d",&v);
        }
        if(v==1)
        {
            printf(" Please enter new first name: ");
            scanf("%s",c[p[0]].firstname);
        }
        else if (v==0)
        {
            printf("\n OK.\n");
        }
        printf(" Do you want to change date of birth? If yes enter '1' If no enter '0'.");
        scanf("%d",&v);
        while(v!=0&&v!=1)
        {
            printf(" Please enter valid answer!");
            scanf("%d",&v);
        }
        if(v==1)
        {
            printf("\nPlease enter date of birth in the form: DD-MM-YYYY ");
            int check2=scanf("%d-%d-%d",&c[p[0]].DOB.day,&c[p[0]].DOB.month,&c[p[0]].DOB.year);
            while (check2!=3)
            {
                printf("\nPlease enter date of birth in form: DD-MM-YYYY! ");
                check2=scanf("%d-%d-%d",&c[p[0]].DOB.day,&c[p[0]].DOB.month,&c[p[0]].DOB.year);
            }
            DOBverify(c[p[0]].DOB.year,c[p[0]].DOB.month,c[p[0]].DOB.day);
        }
        else if (v==0)
        {
            printf("\n OK.\n");
        }
        printf(" Do you want to change address? If yes enter '1' If no enter '0'.");
        scanf("%d",&v);
        while(v!=0&&v!=1)
        {
            printf(" Please enter valid answer!");
            scanf("%d",&v);
        }
        if(v==1)
        {
            printf(" Please enter new address ");
            getchar();
            gets(c[p[0]].address);
        }
        else if (v==0)
        {
            printf("\n OK.\n");
        }
        printf(" Do you want to change phone number? If yes enter '1' If no enter '0'.");
        scanf("%d",&v);
        while(v!=0&&v!=1)
        {
            printf(" Please enter valid answer!");
            scanf("%d",&v);
        }
        if(v==1)
        {
            printf(" Please enter new phone number: ");
            scanf("%s",c[p[0]].phonenumber);
            phonumbvalid(c[p[0]].phonenumber);
        }
        else if (v==0)
        {
            printf("\n OK.\n");
        }
        printf(" Do you want to change Email? If yes enter '1' If no enter '0'.");
        scanf("%d",&v);
        while(v!=0&&v!=1)
        {
            printf(" Please enter valid answer!");
            scanf("%d",&v);
        }
        if(v==1)
        {
            printf(" Please enter new Email in the form: name@site.com ");
            getchar();
            gets(c[p[0]].email);
            emailVerify(c[p[0]].email);
        }
        else if (v==0)
        {
            printf("\n OK.\n");
        }
        printf(" To save your modifications press '1' To quit press'0' ");
        scanf("%d",&pro);
        while(pro!=0&&pro!=1)
        {
            printf(" Please enter valid answer!\n");
            scanf("%d",&pro);
        }
        if (pro==0)
            QUIT();
        else if(pro==1)
        {
            printf(" Your contact has been modified successfully! \n");
        }
    }
    else if (k>1)
    {
        int f=0,t,r,u,t2,lol,f2=0;
        printf(" More than one contact with the same last name is found!\n");
        for(t=0; t<k; t++)
        {
            f++;
            printf("%d-%s,%s,%d-%d-%d,%s,%s\n",t+1,c[p[t]].lastname,c[p[t]].firstname,c[p[t]].DOB.day,c[p[t]].DOB.month,c[p[t]].DOB.year,c[p[t]].phonenumber,c[p[t]].email);
        }
        printf("%d-To quit enter '0'\n",f+1);
        printf(" Please enter desired contact's number: ");
        scanf("%d",&lol);
        if(lol==0)
        {
            QUIT();
        }
        else
        {
            for(t2=1; t2<=f; t2++)
            {
                if(lol!=t2)
                {
                    f2++;
                }
            }
            while(f2==f)
            {
                printf(" Enter a valid number!\n");
                scanf("%d",&lol);
                f2=0;
                for(t2=1; t2<=f; t2++)
                {
                    if(lol!=t2)
                    {
                        f2++;
                    }
                }
            }
        }
        for(u=0; u<k; u++)
        {
            if(u==lol-1)
            {
                printf(" You will be modifying contact: %s,%s,%d-%d-%d,%s,%s,%s\n\n",c[p[u]].lastname,c[p[u]].firstname,c[p[u]].DOB.day,c[p[u]].DOB.month,c[p[u]].DOB.year,c[p[u]].address,c[p[u]].phonenumber,c[p[u]].email);
                printf(" Do you want to change last name? If yes enter '1' If no enter '0'.");
                scanf("%d",&v);
                while(v!=0&&v!=1)
                {
                    printf(" Please enter valid answer!");
                    scanf("%d",&v);
                }
                if(v==1)
                {
                    printf(" Please enter new last name: ");
                    getchar();
                    gets(c[p[u]].lastname);
                }
                else if (v==0)
                {
                    printf("\n OK.\n");
                }
                printf(" Do you want to change first name? If yes enter '1' If no enter '0'.");
                scanf("%d",&v);
                while(v!=0&&v!=1)
                {
                    printf(" Please enter valid answer!");
                    scanf("%d",&v);
                }
                if(v==1)
                {
                    printf(" Please enter new first name: ");
                    scanf("%s",c[p[u]].firstname);
                }
                else if (v==0)
                {
                    printf("\n OK.\n");
                }
                printf(" Do you want to change date of birth? If yes enter '1' If no enter '0'.");
                scanf("%d",&v);
                while(v!=0&&v!=1)
                {
                    printf(" Please enter valid answer!");
                    scanf("%d",&v);
                }
                if(v==1)
                {
                    printf("\nPlease enter date of birth in form: DD-MM-YYYY ");
                    int check3=scanf("%d-%d-%d",&c[p[u]].DOB.day,&c[p[u]].DOB.month,&c[p[u]].DOB.year);
                    while (check3!=3)
                    {
                        printf("\nPlease enter date of birth in form: DD-MM-YYYY! ");
                        check3=scanf("%d-%d-%d",&c[p[u]].DOB.day,&c[p[u]].DOB.month,&c[p[u]].DOB.year);
                    }
                    DOBverify(c[p[u]].DOB.year,c[p[u]].DOB.month,c[p[u]].DOB.day);
                }
                else if (v==0)
                {
                    printf("\n OK.\n");
                }
                printf(" Do you want to change address? If yes enter '1' If no enter '0'.");
                scanf("%d",&v);
                while(v!=0&&v!=1)
                {
                    printf(" Please enter valid answer!");
                    scanf("%d",&v);
                }
                if(v==1)
                {
                    printf(" Please enter new address ");
                    getchar();
                    gets(c[p[u]].address);
                }
                else if (v==0)
                {
                    printf("\n OK.\n");
                }
                printf(" Do you want to change phone number? If yes enter '1' If no enter '0'.");
                scanf("%d",&v);
                while(v!=0&&v!=1)
                {
                    printf(" Please enter valid answer!");
                    scanf("%d",&v);
                }
                if(v==1)
                {
                    printf(" Please enter new phone number: ");
                    scanf("%s",c[p[u]].phonenumber);
                    phonumbvalid(c[p[u]].phonenumber);
                }
                else if (v==0)
                {
                    printf("\n OK.\n");
                }
                printf(" Do you want to change Email? If yes enter '1' else enter '0'.");
                scanf("%d",&v);
                while(v!=0&&v!=1)
                {
                    printf(" Please enter valid answer!");
                    scanf("%d",&v);
                }
                if(v==1)
                {
                    printf(" Please enter new Email in the form: name@site.com ");
                    getchar();
                    gets(c[p[u]].email);
                    emailVerify(c[p[u]].email);
                }
                else if (v==0)
                {
                    printf("\n OK.\n");
                }
                printf(" To save your modifications press '1' To quit press'0' ");
                scanf("%d",&pro);
                while(pro!=0&&pro!=1)
                {
                    printf(" Please enter valid answer!\n");
                    scanf("%d",&pro);
                }
                if (pro==0)
                {
                    QUIT();
                }
                else if(pro==1)
                {
                    printf(" Your contact has been modified successfully! \n");
                }
            }
        }
    }
}
void deleteContact()
{
    int i=0,found=0,pro,j;
    char L[50];
    char F[50];
    printf("Please enter last name: ");
    getchar();
    gets(L);
    printf("Please enter first name: ");
    scanf("%s",F);
    for(i=0; i<n; i++)
    {
        if((strcasecmp(c[i].lastname,L)==0)&&(strcasecmp(c[i].firstname,F)==0))
        {
            found++;
        }
    }
    if(found>0)
    {
        printf(" All contact(s) named as ' %s , %s ' will be deleted!\n",L,F);
        printf(" To proceed press '1' To quit press '0'\n");
        scanf("%d",&pro);
        while(pro!=0&&pro!=1)
        {
            printf(" Please enter valid answer!\n");
            scanf("%d",&pro);
        }
        if(pro==0)
        {
            QUIT();
        }
        else if(pro==1)
        {
            printf("\nContact(s) deleted successfully\n\n");
        }
        for(i=0; i<n; i++)
        {
            if((strcasecmp(c[i].lastname,L)==0)&&(strcasecmp(c[i].firstname,F)==0))
            {
                for(j=i; j<n; j++)
                {
                    c[j]=c[j+1];
                }
                n=n-1;
                i=i-1;
            }
        }
    }
    else if(found==0)
    {
        printf("\nContact not found!\n\n");
        printf(" If you want to delete an existing contact enter '1', to quit enter '0' ");
        scanf("%d",&pro);
        while(pro!=0&&pro!=1)
        {
            printf(" Please enter valid answer!\n");
            scanf("%d",&pro);
        }
        if (pro==0)
        {
            QUIT();
        }
        else if(pro==1)
        {
            deleteContact();
        }
    }
}
void SAVE()
{
    int i;
    FILE *f;
    f = fopen(name,"w");
    for(i=0; i<n; i++)
    {
        fprintf(f,"%s,",c[i].lastname);
        fprintf(f,"%s,",c[i].firstname);
        fprintf(f,"%d-%d-%d,",c[i].DOB.day,c[i].DOB.month,c[i].DOB.year);
        fprintf(f,"%s,",c[i].address);
        fprintf(f,"%s,",c[i].phonenumber);
        fprintf(f,"%s\n",c[i].email);
    }
    fclose(f);
    printf(" All your changes have been saved successfully!\n");
}
void QUIT()
{
    int h=3;
    printf(" Are you sure you want to quit? All your changes will not be saved\n");
    printf("If you want to quit without saving press '0'\nIf you want to save and quit press '1'\nIf you want to save and continue press '2'\n ");
    scanf("%d",&h);
    while(h!=0&&h!=1&&h!=2)
    {
        printf(" Please enter valid answer!\n");
        scanf("%d",&h);
    }
    if(h==1)
    {
        SAVE();
        printf("\nYour changes have been saved successfully\n\n");
        exit(0);
    }
    else if(h==0)
    {
        exit(0);
    }
    else
    {
        SAVE();
        printf("\nYour changes have been saved successfully\n\n");
    }
}
int main()
{
    int x,h,b;
    load();
    while (1)
    {
        x=0;
        printf(" \n\t\t\t\t\t\t  -MENU-\n");
        printf("\t\t 1.Load another file\t 2.Search\t 3.Add\t\t 4.Delete\n\t\t 5.Modify\t\t 6.Print\t 7.Save\t\t 8.Quit\n");
        scanf("%d",&x);
        while(x!=1&&x!=2&&x!=3&&x!=4&&x!=5&&x!=6&&x!=7&&x!=8)
        {
            printf(" Please enter valid answer!");
            scanf("%d",&x);
        }
        if(x==1)
        {
            load();
        }
        else if(x==2)
        {
            Search();
        }
        else if(x==3)
        {
            ADD();
        }
        else if(x==4)
        {
            deleteContact();
        }
        else if(x==5)
        {
            MODIFY();
        }
        else if(x==6)
        {
            Print();
        }
        else if(x==7)
        {
            SAVE();
        }
        else
        {
            QUIT();
        }
    }
    return 0;
}
