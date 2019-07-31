#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include <sys/types.h>
#include <unistd.h>

//declaring linked list
typedef struct database{
    char name[100];
    int age;
    char user[7];
    char sex;
    struct database* next;
};

void add(struct database *Head, int Age, char Name[100],char User[7],char Sex){
    struct database *current = Head;
    while(current->next !=NULL){
        current =current->next;
    }
    current ->next = malloc(sizeof(struct database));
    current ->next->age = Age;
    strcpy(current ->next->name,Name);
    strcpy(current ->next->user,User);
    current->next->sex = Sex;
    current ->next->next = NULL;
}

void print_database(struct database *head){
    struct database *current = head;
    while(current!=NULL){
        printf("\t%d",current->age);
        printf("\t%s",current->name);
        printf("\t%c",current->sex);
        printf("\t%s",current->user);
        current =current->next;
    }
}

void save_databaseP(struct database *head){
    struct database *current = head;
    int cnt=0;
    current =current->next;
    while(current != NULL){
        FILE *fp;
        FILE *qp;
        char x[11];
        sprintf(x,"%s.txt",current->user);
        fp=fopen("Patient_database.txt","a");
        qp=fopen(x,"w");
        fprintf(fp,"%s\t%d\t%s\n",current->user,current->age,current->name);
        fprintf(qp,"Name: %s\nAge: %d\nSex: %c\n",current->name,current->age,current->sex);
        fclose(fp);
        fclose(qp);
        current =current->next;
    }

}


int main(){
    //declarations
    system("COLOR 70");
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(hConsole,241);
    char stri[500],check[4];
    int dSum;
    int www=2;
    char curUser[100];
    char sol[500]={};
    char symptomCode[20];
    char diseaseCode[20];
    char disease2[20];
    FILE *disease,*Disease;
    FILE *doc,*doc2;
    FILE *user=NULL;
    FILE *fp,*qp;
    int mark2=0;
    int mark=0;
    int ex=0;
    SYSTEMTIME d;
    char a;
    int doctor=0;
    GetSystemTime(&d);
    struct database *head=NULL;
    char USER[7],USERtxt[11]="doc000.txt";
    head = (struct database*)calloc(1,sizeof(struct database));
    if(head==NULL){
        return 1;
    }
    head->next=NULL;

    //start menu
    {
        SetConsoleTextAttribute(hConsole,241);
        printf("                                                             \n                    DR.COMPUTER'S CHAMBER                    \n                                                             \n\n");
        SetConsoleTextAttribute(hConsole,112);
        printf("Welcome to Dr.Computer's Chamber.\n\n    Are you a new user? y(yes)/n(no)/d(for doctor) ");
        a=getchar();
        if(a=='d' || a=='D'){
            doctor=1;
        }
    }

    //new or old or doc
    {
        while(a!='d' && a!='D' && a!='n' && a!='N' && a!='y' && a!='Y'){
            system("cls");
            SetConsoleTextAttribute(hConsole,241);
            printf("                                                             \n                    DR.COMPUTER'S CHAMBER                    \n                                                             \n\n");
            SetConsoleTextAttribute(hConsole,112);
            printf("Welcome to Dr.Computer's Chamber.\n\n    Are you a new user? y(yes)/n(no)/d(for doctor) ");
            printf("\n\n    Invalid input");
            a=getchar();
        }
        if(a=='d' || a=='D'){
            www=1;
        }
        else{
            www=0;
        }


        //new user
        if(a=='y' || a=='Y'){
            char name[100];
            char uname[4];
            int age;
            char sex;
            printf("\n\t\bPlease fill up the following form.\n");
            printf("\nName: ");
            fflush(stdin);
            gets(name);
            while(strlen(name)<3){
                printf("Please enter a name longer than 3 letters\n\nName: ");
                gets(name);
            }
            printf("\nAge: ");
            scanf("%d",&age);
            printf("\nSex(F/M): ");
            fflush(stdin);
            scanf("%c",&sex);
            uname[0]=name[0];
            uname[1]=name[1];
            uname[2]=name[2];
            uname[3]='\0';
            int sl;

            fp= fopen("SL.txt","r");
            fscanf(fp,"%d",&sl);
            sl++;
            fclose(fp);
            fp=fopen("SL.txt","w");
            fprintf(fp,"%03d",sl);
            fclose(fp);
            char user[7];
            sprintf(user,"%s%03d",uname,sl);
            printf("Your username is ");
            SetConsoleTextAttribute(hConsole,116);
            printf("%s\n",user);
            SetConsoleTextAttribute(hConsole,112);
            printf("\nPlease store username\n\n",user);
            printf("Press any key to continue");
            strcpy(USER,user);
            sprintf(USERtxt,"%s.txt",USER);
            add(head,age,name,user,sex);
            //print_database(head);
            fflush(stdin);
            save_databaseP(head);
            getch();
        }

        //old user
        else if(a=='n' || a=='N'){
            printf("\nUsername: ");
            fflush(stdin);
            gets(USER);
            sprintf(USERtxt,"%s.txt",USER);
            user = fopen(USERtxt,"r+");
            while(user==NULL){
                printf("\nThat is not a valid username.\nUsername:");
                fflush(stdin);
                gets(USER);
                sprintf(USERtxt,"%s.txt",USER);
                user = fopen(USERtxt,"r+");
            }
            fclose(user);
        }

    }

    //access userfile
    {
        doc= fopen(USERtxt,"r");
        fseek(doc,5,SEEK_SET);
        fgets(curUser,99,doc);
        fclose(doc);
        doc= fopen(USERtxt,"a");


    }


    while(ex!=2){
        ex=0;
        {

        fflush(stdin);
        a='x';
        //menu
        while(1){
            if(a==80){
                mark++;
                if(mark==8)
                    mark=0;
            }
            else if(a==72){
                mark--;
                if(mark==-1)
                    mark=7;
            }
            else if(a==13)
                break;
            system("cls");
            SetConsoleTextAttribute(hConsole,241);
            printf("                                                             \n                    DR.COMPUTER'S CHAMBER                    \n                                                             \n\n");
            SetConsoleTextAttribute(hConsole,112);
            if(!doctor)printf("Hello%s",curUser);
            else printf("Hello doctor");
            printf("\n    Please choose specialist:\n\n");
            if(mark==0)
                printf("-->");
            else
                printf("   ");
            printf(" General\n");

            if(mark==1)
                printf("-->");
            else
                printf("   ");
            printf(" Respiratory\n");

            if(mark==2)
                printf("-->");
            else
                printf("   ");
            printf(" Cardiovascular\n");

            if(mark==3)
                printf("-->");
            else
                printf("   ");
            printf(" Gastrointestinal(under construction)\n");

            if(mark==4)
                printf("-->");
            else
                printf("   ");
            printf(" Rheumatology and Haematology(under construction)\n");

            if(mark==5)
                printf("-->");
            else
                printf("   ");
            printf(" Neurology(under construction)\n");

            if(mark==6)
                printf("-->");
            else
                printf("   ");
            printf(" View Previous Records\n");

            if(mark==7)
                printf("-->");
            else
                printf("   ");
            printf(" Exit\n");


            printf("\n                 ");
            SetConsoleTextAttribute(hConsole,252);
            printf("  USE ARROWS TO NAVIGATE  ");
            SetConsoleTextAttribute(hConsole,112);
            printf("                  ");

            fflush(stdin);
            a=getche();
        }

        }

    //Symptoms
    {
        //General(done)
        if(mark==0 && ex==0){

            //declaration
            int fever=0;
            int fatigue=0;
            int weight=0;
            int bowlH=0;
            int bowlC=0;
            int headache=0;
            int rash=0;
            int joint=0;

            fflush(stdin);
            a=0;
            while(a!=13){
                if(a==80){
                    mark2++;
                    if(mark2==9)
                        mark2=0;
                }
                else if(a==72){
                    mark2--;
                    if(mark2==-1)
                        mark2=8;
                }
                else if(a==13)
                    break;
                system("cls");
                SetConsoleTextAttribute(hConsole,241);
                printf("                                                             \n                    DR.COMPUTER'S CHAMBER                    \n                                                             \n\n");
                SetConsoleTextAttribute(hConsole,112);
                if(!doctor)printf("Hello%s",curUser);
                else printf("\tHello doctor.");
                printf("\n");

                //fever
                {
                    if(mark2==0)
                        printf("\n--> Fever  ");
                    else
                        printf("\n    Fever  ");
                    {
                        if(mark2==0 && a==32){
                            fever++;
                            fever=fever%3;
                        }
                        switch(fever){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("low");
                            break;
                        case(2):
                            printf("high");
                            break;
                        }
                    }
                }

                //fatigue
                {
                    if(mark2==1)
                        printf("\n--> Fatigue or tiredness  ");
                    else
                        printf("\n    Fatigue or tiredness  ");
                    {
                        if(mark2==1 && a==32){
                            fatigue++;
                            fatigue=fatigue%3;
                        }
                        switch(fatigue){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("low");
                            break;
                        case(2):
                            printf("high");
                            break;
                        }
                    }
                }

                //weight change
                {
                    if(mark2==2)
                        printf("\n--> Weight  ");
                    else
                        printf("\n    Weight  ");
                    {
                        if(mark2==2 && a==32){
                            weight++;
                            weight=weight%3;
                        }
                        switch(weight){
                        case(0):
                            printf("normal");
                            break;
                        case(1):
                            printf("increased");
                            break;
                        case(2):
                            printf("decreased");
                            break;
                        }
                    }
                }

                //bowl amount
                {
                    if(mark2==3)
                        printf("\n--> Bowl and bladder habit  ");
                    else
                        printf("\n    Bowl and bladder habit  ");
                    {
                        if(mark2==3 && a==32){
                            bowlH++;
                            bowlH=bowlH%3;
                        }
                        switch(bowlH){
                        case(0):
                            printf("regular");
                            break;
                        case(1):
                            printf("frequent");
                            break;
                        case(2):
                            printf("reduced");
                            break;
                        }
                    }
                }

                //bowl color
                {
                    if(mark2==4)
                        printf("\n--> Bowl and bladder color  ");
                    else
                        printf("\n    Bowl and bladder color  ");
                    {
                        if(mark2==4 && a==32){
                            bowlC++;
                            bowlC=bowlC%3;
                        }
                        switch(bowlC){
                        case(0):
                            printf("regular");
                            break;
                        case(1):
                            printf("light yellow");
                            break;
                        case(2):
                            printf("dark yellow");
                            break;
                        }
                    }
                }

                //headache
                {
                    if(mark2==5)
                        printf("\n--> Headache  ");
                    else
                        printf("\n    Headache  ");
                    {
                        if(mark2==5 && a==32){
                            headache++;
                            headache=headache%3;
                        }
                        switch(headache){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("light");
                            break;
                        case(2):
                            printf("severe");
                            break;
                        }
                    }
                }

                //rash
                {
                    if(mark2==6)
                        printf("\n--> Rashes  ");
                    else
                        printf("\n    Rashes  ");
                    {
                        if(mark2==6 && a==32){
                            rash++;
                            rash=rash%2;
                        }
                        switch(rash){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("yes");
                            break;
                        }
                    }
                }

                //joint pain
                {
                    if(mark2==7)
                        printf("\n--> Joint pain  ");
                    else
                        printf("\n    Joint pain  ");
                    {
                        if(mark2==7 && a==32){
                            joint++;
                            joint=joint%2;
                        }
                        switch(joint){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("yes");
                            break;
                        }
                    }
                }

                //exit
                {
                    if(mark2==8)
                        printf("\n--> Back  ");
                    else
                        printf("\n    Back  ");
                }


                printf("\n\n                    ");
                SetConsoleTextAttribute(hConsole,252);
                printf(" HIT SPACE TO CHANGE ");
                SetConsoleTextAttribute(hConsole,112);
                printf("                    ");
                a=getche();
            }
            if(mark2==8){
                mark2=0;
                ex=1;
                continue;
            }

            fprintf(doc,"\n");
            fprintf(doc,"\nDate: %d-%d-%d\n",d.wDay,d.wMonth,d.wYear);
            sprintf(symptomCode,"%d%d%d%d%d%d%d%d%d",mark,fever,fatigue,weight,bowlH,bowlC,headache,rash,joint);
            dSum = fever+fatigue+weight+bowlH+bowlC+headache+rash+joint;
            fprintf(doc,symptomCode);

            fprintf(doc, "\nFever  ");
                switch(fever){
                    case(0):
                        fprintf(doc,"no");
                        break;
                    case(1):
                        fprintf(doc,"low");
                        break;
                    case(2):
                        fprintf(doc,"high");
                        break;
                }
            fprintf(doc, "\nFatigue or tiredness  ");
                switch(fatigue){
                    case(0):
                        fprintf(doc,"no");
                        break;
                    case(1):
                        fprintf(doc,"low");
                        break;
                    case(2):
                        fprintf(doc,"high");
                        break;
                    }
            fprintf(doc, "\nWeight  ");
                switch(weight){
                    case(0):
                        fprintf(doc,"normal");
                        break;
                    case(1):
                        fprintf(doc,"increased");
                        break;
                    case(2):
                        fprintf(doc,"decreased");
                        break;
                    }

            fprintf(doc, "\nBowl habit  ");
                switch(bowlH){
                    case(0):
                        fprintf(doc,"regular");
                        break;
                    case(1):
                        fprintf(doc,"frequent");
                        break;
                    case(2):
                        fprintf(doc,"reduced");
                        break;
                    }


            fprintf(doc, "\nBowl color  ");
                switch(bowlC){
                    case(0):
                        fprintf(doc,"regular");
                        break;
                    case(1):
                        fprintf(doc,"light yellow");
                        break;
                    case(2):
                        fprintf(doc,"dark yellow");
                        break;
                    }

            fprintf(doc, "\nHeadache  ");
                switch(headache){
                    case(0):
                        fprintf(doc,"no");
                        break;
                    case(1):
                        fprintf(doc,"light");
                        break;
                    case(2):
                        fprintf(doc,"severe");
                        break;
                    }

            fprintf(doc, "\nRash  ");
                switch(rash){
                    case(0):
                        fprintf(doc,"no");
                        break;
                    case(1):
                        fprintf(doc,"yes");
                        break;
                    }

            fprintf(doc, "\nJoint pain  ");
                switch(joint){
                    case(0):
                        fprintf(doc,"no");
                        break;
                    case(1):
                        fprintf(doc,"yes");
                        break;
                    }
        }


        //Respiratory(done)
        else if(mark==1 && ex==0){

            //declaration
            int cough=0;
            int throat =0;
            int chest=0;
            int breath=0;
            int ear=0;
            int nose=0;
            int fever=0;

            fflush(stdin);
            a=0;
            while(a!=13){
                if(a==80){
                    mark2++;
                    if(mark2==8)
                        mark2=0;
                }
                else if(a==72){
                    mark2--;
                    if(mark2==-1)
                        mark2=7;
                }
                else if(a==13)
                    break;
                system("cls");
                SetConsoleTextAttribute(hConsole,241);
                printf("                                                             \n                    DR.COMPUTER'S CHAMBER                    \n                                                             \n\n");
                SetConsoleTextAttribute(hConsole,112);
                if(!doctor)printf("Hello%s",curUser);
                else printf("\tHello doctor.");
                printf("\n");

                //Cough
                {
                    if(mark2==0)
                        printf("\n--> Cough  ");
                    else
                        printf("\n    Cough  ");
                    {
                        if(mark2==0 && a==32){
                            cough++;
                            cough=cough%2;
                        }
                        switch(cough){
                        case(0):
                            printf("dry");
                            break;
                        case(1):
                            printf("productive");
                            break;
                        }
                    }
                }

                //throat
                {
                    if(mark2==1)
                        printf("\n--> Throat pain  ");
                    else
                        printf("\n    Throat pain  ");
                    {
                        if(mark2==1 && a==32){
                            throat++;
                            throat=throat%2;
                        }
                        switch(throat){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("yes");
                            break;
                        }
                    }
                }

                //chest
                {
                    if(mark2==2)
                        printf("\n--> Chest pain  ");
                    else
                        printf("\n    Chest pain  ");
                    {
                        if(mark2==2 && a==32){
                            chest++;
                            chest=chest%2;
                        }
                        switch(chest){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("yes");
                            break;
                        }
                    }
                }

                //breath
                {
                    if(mark2==3)
                        printf("\n--> Shortness of breath  ");
                    else
                        printf("\n    Shortness of breath  ");
                    {
                        if(mark2==3 && a==32){
                            breath++;
                            breath=breath%2;
                        }
                        switch(breath){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("yes");
                            break;
                        }
                    }
                }

                //nose
                {
                    if(mark2==4)
                        printf("\n--> Runny nose  ");
                    else
                        printf("\n    Runny nose  ");
                    {
                        if(mark2==4 && a==32){
                            nose++;
                            nose=nose%2;
                        }
                        switch(nose){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("yes");
                            break;
                        }
                    }
                }

                //ear
                {
                    if(mark2==5)
                        printf("\n--> Ear pain  ");
                    else
                        printf("\n    Ear pain  ");
                    {
                        if(mark2==5 && a==32){
                            ear++;
                            ear=ear%2;
                        }
                        switch(ear){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("yes");
                            break;
                        }
                    }
                }

                //fever
                {
                    if(mark2==6)
                        printf("\n--> Fever  ");
                    else
                        printf("\n    Fever  ");
                    {
                        if(mark2==6 && a==32){
                            fever++;
                            fever=fever%3;
                        }
                        switch(fever){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("low");
                            break;
                        case(2):
                            printf("high");
                            break;
                        }
                    }
                }

                //back
                {
                    if(mark2==7)
                        printf("\n--> Back  ");
                    else
                        printf("\n    Back  ");
                }

                printf("\n\n                    ");
                SetConsoleTextAttribute(hConsole,252);
                printf(" HIT SPACE TO CHANGE ");
                SetConsoleTextAttribute(hConsole,112);
                printf("                    ");
                a=getche();
            }
            if(mark2==7){
                mark2=0;
                ex=1;
                continue;
            }

            fprintf(doc,"\n");
            fprintf(doc,"\nDate: %d-%d-%d\n",d.wDay,d.wMonth,d.wYear);
            sprintf(symptomCode,"%d%d%d%d%d%d%d%d",mark,cough,throat,chest,breath,nose,ear,fever);
            dSum = cough+throat+chest+breath+nose+ear+fever;
            fprintf(doc,symptomCode);

            fprintf(doc, "\nCough  ");
                switch(cough){
                    case(0):
                        fprintf(doc,"no");
                        break;
                    case(1):
                        fprintf(doc,"low");
                        break;
                    case(2):
                        fprintf(doc,"high");
                        break;
                }
            fprintf(doc, "\nThroat pain  ");
                switch(throat){
                        case(0):
                            fprintf(doc,"no");
                            break;
                        case(1):
                            fprintf(doc,"yes");
                            break;
                        }
            fprintf(doc, "\nChest pain  ");
                switch(chest){
                        case(0):
                            fprintf(doc,"no");
                            break;
                        case(1):
                            fprintf(doc,"yes");
                            break;
                        }
            fprintf(doc, "\nShortness of breath  ");
                switch(breath){
                        case(0):
                            fprintf(doc,"no");
                            break;
                        case(1):
                            fprintf(doc,"yes");
                            break;
                        }
            fprintf(doc, "\nRunny nose  ");
                switch(nose){
                        case(0):
                            fprintf(doc,"no");
                            break;
                        case(1):
                            fprintf(doc,"yes");
                            break;
                        }
            fprintf(doc, "\nEar pain  ");
                switch(ear){
                        case(0):
                            fprintf(doc,"no");
                            break;
                        case(1):
                            fprintf(doc,"yes");
                            break;
                        }
            fprintf(doc, "\nFever  ");
                switch(fever){
                        case(0):
                            fprintf(doc,"no");
                            break;
                        case(1):
                            fprintf(doc,"low");
                            break;
                        case(2):
                            fprintf(doc,"high");
                            break;
                        }

        }


        //Cardiovascular(done but disease not ready)
        else if(mark==2 && ex==0){

            //declaration
            int breath=0;
            int chest=0;
            int leg=0;

            fflush(stdin);
            a=0;
            while(a!=13){
                //printf("   Page under construction\n");
                //exit(0);
                if(a==80){
                    mark2++;
                    if(mark2==4)
                        mark2=0;
                }
                else if(a==72){
                    mark2--;
                    if(mark2==-1)
                        mark2=3;
                }
                else if(a==13)
                    break;
                system("cls");
                SetConsoleTextAttribute(hConsole,241);
                printf("                                                             \n                    DR.COMPUTER'S CHAMBER                    \n                                                             \n\n");
                SetConsoleTextAttribute(hConsole,112);
                if(!doctor)printf("Hello%s",curUser);
                else printf("\tHello doctor.");
                printf("\n");

                //breath
                {
                    if(mark2==0)
                        printf("\n--> Breathlessness  ");
                    else
                        printf("\n    Breathlessness  ");
                    {
                        if(mark2==0 && a==32){
                            breath+=2;
                            breath=breath%6;
                        }
                        switch(breath){
                        case(0):
                            printf("no");
                            break;
                        case(2):
                            printf("on exertion");
                            break;
                        case(4):
                            printf("at rest");
                            break;
                        }
                    }
                }
                //chest
                {
                    if(mark2==1)
                        printf("\n--> Chest pain  ");
                    else
                        printf("\n    Chest pain  ");
                    {
                        if(mark2==1 && a==32){
                            chest+=2;
                            chest=chest%6;
                        }
                        switch(chest){
                        case(0):
                            printf("no");
                            break;
                        case(2):
                            printf("on exertion");
                            break;
                        case(4):
                            printf("at rest");
                            break;
                        }
                    }
                }
                //leg
                {
                    if(mark2==2)
                        printf("\n--> Heaviness or swelling of legs  ");
                    else
                        printf("\n    Heaviness or swelling of legs  ");
                    {
                        if(mark2==2 && a==32){
                            leg+=2;
                            leg=leg%4;
                        }
                        switch(leg){
                        case(0):
                            printf("no");
                            break;
                        case(2):
                            printf("yes");
                            break;
                        }
                    }
                }

                //exit
                {
                    if(mark2==3)
                        printf("\n--> Back  ");
                    else
                        printf("\n    Back  ");
                }



                printf("\n\n                    ");
                SetConsoleTextAttribute(hConsole,252);
                printf(" HIT SPACE TO CHANGE ");
                SetConsoleTextAttribute(hConsole,112);
                printf("                    ");
                a=getche();
            }
            if(mark2==3){
                mark2=0;
                ex=1;
                continue;
            }

            fprintf(doc,"\n");
            fprintf(doc,"\nDate: %d-%d-%d\n",d.wDay,d.wMonth,d.wYear);
            sprintf(symptomCode,"%d%d%d%d%d",mark,breath,chest,leg);
            dSum=breath +chest+leg;
            fprintf(doc,symptomCode);

            fprintf(doc, "\nBreathlessness  ");
                switch(breath){
                        case(0):
                            fprintf(doc,"no");
                            break;
                        case(2):
                            fprintf(doc,"on exertion");
                            break;
                        case(4):
                            fprintf(doc,"at rest");
                            break;
                        }
            fprintf(doc, "\nChest pain  ");
                switch(chest){
                        case(0):
                            fprintf(doc,"no");
                            break;
                        case(2):
                            fprintf(doc,"on exertion");
                            break;
                        case(4):
                            fprintf(doc,"at rest");
                            break;
                        }
            fprintf(doc, "\nHeaviness or swelling of legs  ");
                switch(leg){
                        case(0):
                            fprintf(doc,"no");
                            break;
                        case(2):
                            fprintf(doc,"yes");
                            break;
                        }

        }


        //Gastrointestinal
        else if(mark==3 && ex==0){

            //declaration
            int fever=0;
            int fatigue=0;
            int weight=0;
            int bowlH=0;
            int bowlC=0;

            fflush(stdin);
            a=0;
            while(a!=13){
                system("cls");
                SetConsoleTextAttribute(hConsole,241);
                printf("                                                             \n                    DR.COMPUTER'S CHAMBER                    \n                                                             \n\n");
                SetConsoleTextAttribute(hConsole,112);
                printf("   Page under construction\n");

                {
                    ex=1;
                    break;
                }

                if(a==80){
                    mark2++;
                    if(mark2==5)
                        mark2=0;
                }
                else if(a==72){
                    mark2--;
                    if(mark2==-1)
                        mark2=4;
                }
                else if(a==13)
                    break;
                system("cls");
                SetConsoleTextAttribute(hConsole,241);
                printf("                                                             \n                    DR.COMPUTER'S CHAMBER                    \n                                                             \n\n");
                SetConsoleTextAttribute(hConsole,112);
                if(!doctor)printf("Hello%s",curUser);
                else printf("\tHello doctor.");
                printf("\n");

                //fever
                {
                    if(mark2==0)
                        printf("\n--> Fever  ");
                    else
                        printf("\n    Fever  ");
                    {
                        if(mark2==0 && a==32){
                            fever++;
                            fever=fever%3;
                        }
                        switch(fever){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("low");
                            break;
                        case(2):
                            printf("high");
                            break;
                        }
                    }
                }
                //fatigue
                {
                    if(mark2==1)
                        printf("\n--> Fatigue or tiredness  ");
                    else
                        printf("\n    Fatigue or tiredness  ");
                    {
                        if(mark2==1 && a==32){
                            fatigue++;
                            fatigue=fatigue%3;
                        }
                        switch(fatigue){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("low");
                            break;
                        case(2):
                            printf("high");
                            break;
                        }
                    }
                }
                //weight change
                {
                    if(mark2==2)
                        printf("\n--> Weight  ");
                    else
                        printf("\n    Weight  ");
                    {
                        if(mark2==2 && a==32){
                            weight++;
                            weight=weight%3;
                        }
                        switch(weight){
                        case(0):
                            printf("normal");
                            break;
                        case(1):
                            printf("increased");
                            break;
                        case(2):
                            printf("decreased");
                            break;
                        }
                    }
                }

                //bowl amount
                {
                    if(mark2==3)
                        printf("\n--> Bowl and bladder habit  ");
                    else
                        printf("\n    Bowl and bladder habit  ");
                    {
                        if(mark2==3 && a==32){
                            bowlH++;
                            bowlH=bowlH%3;
                        }
                        switch(bowlH){
                        case(0):
                            printf("regular");
                            break;
                        case(1):
                            printf("frequent");
                            break;
                        case(2):
                            printf("reduced");
                            break;
                        }
                    }
                }

                //bowl color
                {
                    if(mark2==4)
                        printf("\n--> Bowl and bladder color  ");
                    else
                        printf("\n    Bowl and bladder color  ");
                    {
                        if(mark2==4 && a==32){
                            bowlC++;
                            bowlC=bowlC%3;
                        }
                        switch(bowlC){
                        case(0):
                            printf("regular");
                            break;
                        case(1):
                            printf("light yellow");
                            break;
                        case(2):
                            printf("dark yellow");
                            break;
                        }
                    }
                }
                printf("\n\n                    ");
                SetConsoleTextAttribute(hConsole,252);
                printf(" HIT SPACE TO CHANGE ");
                SetConsoleTextAttribute(hConsole,112);
                printf("                    ");
                a=getche();
            }
            {
                getch();
                continue;
            }

            fprintf(doc,"\n");
            fprintf(doc,"\nDate: %d-%d-%d\n",d.wDay,d.wMonth,d.wYear);
            sprintf(symptomCode,"%d%d%d%d%d",fever,fatigue,weight,bowlH,bowlC);
            fprintf(doc,symptomCode);

            fprintf(doc, "\nFever  ");
                switch(fever){
                    case(0):
                        fprintf(doc,"no");
                        break;
                    case(1):
                        fprintf(doc,"low");
                        break;
                    case(2):
                        fprintf(doc,"high");
                        break;
                }
            fprintf(doc, "\nFatigue or tiredness  ");
                switch(fatigue){
                    case(0):
                        fprintf(doc,"no");
                        break;
                    case(1):
                        fprintf(doc,"low");
                        break;
                    case(2):
                        fprintf(doc,"high");
                        break;
                    }
            fprintf(doc, "\nWeight  ");
                switch(weight){
                    case(0):
                        fprintf(doc,"normal");
                        break;
                    case(1):
                        fprintf(doc,"increased");
                        break;
                    case(2):
                        fprintf(doc,"decreased");
                        break;
                    }

            fprintf(doc, "\nBowl habit  ");
                switch(bowlH){
                    case(0):
                        fprintf(doc,"regular");
                        break;
                    case(1):
                        fprintf(doc,"frequent");
                        break;
                    case(2):
                        fprintf(doc,"reduced");
                        break;
                    }


            fprintf(doc, "\nBowl color  ");
                switch(bowlC){
                    case(0):
                        fprintf(doc,"regular");
                        break;
                    case(1):
                        fprintf(doc,"light yellow");
                        break;
                    case(2):
                        fprintf(doc,"dark yellow");
                        break;
                    }

        }


        //Haematology
        else if(mark==4 && ex==0){

            //declaration
            int fever=0;
            int fatigue=0;
            int weight=0;
            int bowlH=0;
            int bowlC=0;

            fflush(stdin);
            a=0;
            while(a!=13){
                system("cls");
                SetConsoleTextAttribute(hConsole,241);
                printf("                                                             \n                    DR.COMPUTER'S CHAMBER                    \n                                                             \n\n");
                SetConsoleTextAttribute(hConsole,112);
                printf("   Page under construction\n");
                {
                    ex=1;
                    break;
                }

                if(a==80){
                    mark2++;
                    if(mark2==5)
                        mark2=0;
                }
                else if(a==72){
                    mark2--;
                    if(mark2==-1)
                        mark2=4;
                }
                else if(a==13)
                    break;
                system("cls");
                SetConsoleTextAttribute(hConsole,241);
                printf("                                                             \n                    DR.COMPUTER'S CHAMBER                    \n                                                             \n\n");
                SetConsoleTextAttribute(hConsole,112);
                if(!doctor)printf("Hello%s",curUser);
                else printf("\tHello doctor.");
                printf("\n");

                //fever
                {
                    if(mark2==0)
                        printf("\n-->Fever  ");
                    else
                        printf("\n   Fever  ");
                    {
                        if(mark2==0 && a==32){
                            fever++;
                            fever=fever%3;
                        }
                        switch(fever){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("low");
                            break;
                        case(2):
                            printf("high");
                            break;
                        }
                    }
                }
                //fatigue
                {
                    if(mark2==1)
                        printf("\n-->Fatigue or tiredness  ");
                    else
                        printf("\n   Fatigue or tiredness  ");
                    {
                        if(mark2==1 && a==32){
                            fatigue++;
                            fatigue=fatigue%3;
                        }
                        switch(fatigue){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("low");
                            break;
                        case(2):
                            printf("high");
                            break;
                        }
                    }
                }
                //weight change
                {
                    if(mark2==2)
                        printf("\n-->Weight  ");
                    else
                        printf("\n   Weight  ");
                    {
                        if(mark2==2 && a==32){
                            weight++;
                            weight=weight%3;
                        }
                        switch(weight){
                        case(0):
                            printf("normal");
                            break;
                        case(1):
                            printf("increased");
                            break;
                        case(2):
                            printf("decreased");
                            break;
                        }
                    }
                }

                //bowl amount
                {
                    if(mark2==3)
                        printf("\n-->Bowl and bladder habit  ");
                    else
                        printf("\n   Bowl and bladder habit  ");
                    {
                        if(mark2==3 && a==32){
                            bowlH++;
                            bowlH=bowlH%3;
                        }
                        switch(bowlH){
                        case(0):
                            printf("regular");
                            break;
                        case(1):
                            printf("frequent");
                            break;
                        case(2):
                            printf("reduced");
                            break;
                        }
                    }
                }

                //bowl color
                {
                    if(mark2==4)
                        printf("\n-->Bowl and bladder color  ");
                    else
                        printf("\n   Bowl and bladder color  ");
                    {
                        if(mark2==4 && a==32){
                            bowlC++;
                            bowlC=bowlC%3;
                        }
                        switch(bowlC){
                        case(0):
                            printf("regular");
                            break;
                        case(1):
                            printf("light yellow");
                            break;
                        case(2):
                            printf("dark yellow");
                            break;
                        }
                    }
                }
                printf("\n\n                    ");
                SetConsoleTextAttribute(hConsole,252);
                printf(" HIT SPACE TO CHANGE ");
                SetConsoleTextAttribute(hConsole,112);
                printf("                    ");
                a=getche();
            }

            {
                getch();
                continue;
            }
            fprintf(doc,"\nDate: %d-%d-%d\n",d.wDay,d.wMonth,d.wYear);
            sprintf(symptomCode,"%d%d%d%d%d",fever,fatigue,weight,bowlH,bowlC);
            fprintf(doc,symptomCode);

            fprintf(doc, "\nFever  ");
                switch(fever){
                    case(0):
                        fprintf(doc,"no");
                        break;
                    case(1):
                        fprintf(doc,"low");
                        break;
                    case(2):
                        fprintf(doc,"high");
                        break;
                }
            fprintf(doc, "\nFatigue or tiredness  ");
                switch(fatigue){
                    case(0):
                        fprintf(doc,"no");
                        break;
                    case(1):
                        fprintf(doc,"low");
                        break;
                    case(2):
                        fprintf(doc,"high");
                        break;
                    }
            fprintf(doc, "\nWeight  ");
                switch(weight){
                    case(0):
                        fprintf(doc,"normal");
                        break;
                    case(1):
                        fprintf(doc,"increased");
                        break;
                    case(2):
                        fprintf(doc,"decreased");
                        break;
                    }

            fprintf(doc, "\nBowl habit  ");
                switch(bowlH){
                    case(0):
                        fprintf(doc,"regular");
                        break;
                    case(1):
                        fprintf(doc,"frequent");
                        break;
                    case(2):
                        fprintf(doc,"reduced");
                        break;
                    }


            fprintf(doc, "\nBowl color  ");
                switch(bowlC){
                    case(0):
                        fprintf(doc,"regular");
                        break;
                    case(1):
                        fprintf(doc,"light yellow");
                        break;
                    case(2):
                        fprintf(doc,"dark yellow");
                        break;
                    }

        }


        //Neurology
        else if(mark==5 && ex==0){

            //declaration
            int fever=0;
            int fatigue=0;
            int weight=0;
            int bowlH=0;
            int bowlC=0;

            fflush(stdin);
            a=0;
            while(a!=13){
                system("cls");
                SetConsoleTextAttribute(hConsole,241);
                printf("                                                             \n                    DR.COMPUTER'S CHAMBER                    \n                                                             \n\n");
                SetConsoleTextAttribute(hConsole,112);
                printf("   Page under construction\n");
                {
                    ex=1;
                    break;
                }


                if(a==80){
                    mark2++;
                    if(mark2==5)
                        mark2=0;
                }
                else if(a==72){
                    mark2--;
                    if(mark2==-1)
                        mark2=4;
                }
                else if(a==13)
                    break;
                system("cls");
                SetConsoleTextAttribute(hConsole,241);
                printf("                                                             \n                    DR.COMPUTER'S CHAMBER                    \n                                                             \n\n");
                SetConsoleTextAttribute(hConsole,112);
                if(!doctor)printf("Hello%s",curUser);
                else printf("\tHello doctor.");
                printf("\n");

                //fever
                {
                    if(mark2==0)
                        printf("\n-->Fever  ");
                    else
                        printf("\n   Fever  ");
                    {
                        if(mark2==0 && a==32){
                            fever++;
                            fever=fever%3;
                        }
                        switch(fever){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("low");
                            break;
                        case(2):
                            printf("high");
                            break;
                        }
                    }
                }
                //fatigue
                {
                    if(mark2==1)
                        printf("\n-->Fatigue or tiredness  ");
                    else
                        printf("\n   Fatigue or tiredness  ");
                    {
                        if(mark2==1 && a==32){
                            fatigue++;
                            fatigue=fatigue%3;
                        }
                        switch(fatigue){
                        case(0):
                            printf("no");
                            break;
                        case(1):
                            printf("low");
                            break;
                        case(2):
                            printf("high");
                            break;
                        }
                    }
                }
                //weight change
                {
                    if(mark2==2)
                        printf("\n-->Weight  ");
                    else
                        printf("\n   Weight  ");
                    {
                        if(mark2==2 && a==32){
                            weight++;
                            weight=weight%3;
                        }
                        switch(weight){
                        case(0):
                            printf("normal");
                            break;
                        case(1):
                            printf("increased");
                            break;
                        case(2):
                            printf("decreased");
                            break;
                        }
                    }
                }

                //bowl amount
                {
                    if(mark2==3)
                        printf("\n-->Bowl and bladder habit  ");
                    else
                        printf("\n   Bowl and bladder habit  ");
                    {
                        if(mark2==3 && a==32){
                            bowlH++;
                            bowlH=bowlH%3;
                        }
                        switch(bowlH){
                        case(0):
                            printf("regular");
                            break;
                        case(1):
                            printf("frequent");
                            break;
                        case(2):
                            printf("reduced");
                            break;
                        }
                    }
                }

                //bowl color
                {
                    if(mark2==4)
                        printf("\n-->Bowl and bladder color  ");
                    else
                        printf("\n   Bowl and bladder color  ");
                    {
                        if(mark2==4 && a==32){
                            bowlC++;
                            bowlC=bowlC%3;
                        }
                        switch(bowlC){
                        case(0):
                            printf("regular");
                            break;
                        case(1):
                            printf("light yellow");
                            break;
                        case(2):
                            printf("dark yellow");
                            break;
                        }
                    }
                }
                printf("\n\n                    ");
                SetConsoleTextAttribute(hConsole,252);
                printf(" HIT SPACE TO CHANGE ");
                SetConsoleTextAttribute(hConsole,112);
                printf("                    ");
                a=getche();
            }

            {
                getch();
                continue;
            }
            fprintf(doc,"\nDate: %d-%d-%d\n",d.wDay,d.wMonth,d.wYear);
            sprintf(symptomCode,"%d%d%d%d%d",fever,fatigue,weight,bowlH,bowlC);
            fprintf(doc,symptomCode);

            fprintf(doc, "\nFever  ");
                switch(fever){
                    case(0):
                        fprintf(doc,"no");
                        break;
                    case(1):
                        fprintf(doc,"low");
                        break;
                    case(2):
                        fprintf(doc,"high");
                        break;
                }
            fprintf(doc, "\nFatigue or tiredness  ");
                switch(fatigue){
                    case(0):
                        fprintf(doc,"no");
                        break;
                    case(1):
                        fprintf(doc,"low");
                        break;
                    case(2):
                        fprintf(doc,"high");
                        break;
                    }
            fprintf(doc, "\nWeight  ");
                switch(weight){
                    case(0):
                        fprintf(doc,"normal");
                        break;
                    case(1):
                        fprintf(doc,"increased");
                        break;
                    case(2):
                        fprintf(doc,"decreased");
                        break;
                    }

            fprintf(doc, "\nBowl habit  ");
                switch(bowlH){
                    case(0):
                        fprintf(doc,"regular");
                        break;
                    case(1):
                        fprintf(doc,"frequent");
                        break;
                    case(2):
                        fprintf(doc,"reduced");
                        break;
                    }


            fprintf(doc, "\nBowl color  ");
                switch(bowlC){
                    case(0):
                        fprintf(doc,"regular");
                        break;
                    case(1):
                        fprintf(doc,"light yellow");
                        break;
                    case(2):
                        fprintf(doc,"dark yellow");
                        break;
                    }

        }


        //previous data
        else if(mark==6 && ex==0){
            doc2= fopen(USERtxt,"r");
            ex=1;
            int CNT=0;
            char mnop=1;
            system("cls");
            SetConsoleTextAttribute(hConsole,241);
            printf("                                                             \n                    DR.COMPUTER'S CHAMBER                    \n                                                             \n\n");
            SetConsoleTextAttribute(hConsole,112);
            while((fgets(stri,500,doc2))!=NULL){

                if(stri[0]=='\n'){
                    if(mnop!=13){
                        printf("\nPress enter for next record\n");
                        mnop=getch();
                    }
                    if(mnop!=13)
                        break;

                }
                else if(stri[0]!='0' && stri[0]!='1' && stri[0]!='2'){
                    mnop=1;
                    printf("%s",stri);
                }
            }
            if(mnop==13){
                printf("\nSorry. No more record available\n");
            }
            getch();
            fclose(doc2);
            continue;
        }

        //return
        else if(mark==7){
            fclose(doc);
            return 0;
        }

    }

    //Diagnosis
    if(www==0){
        printf("\n\n");
        disease = fopen("Disease.txt","r");
        while((fgets(disease2,20,disease))!=NULL){
            fscanf(disease,"%s",diseaseCode);
            if(strcmp(diseaseCode,symptomCode)==0){
                fgets(sol,500,disease);
                puts(sol);
                break;
            }
        }
        if(strlen(sol)<5){
            if(dSum>5)
                printf("\nYour disease is complex and serious. \nContact a doctor immediately.\n");
            else if(dSum<3)
                printf("\nYou should not worry much. \nIts nothing serious. Take rest.\n");
            else
                printf("\nThings should get better soon. Don't worry. \nContact doctor if problem persists.\n");
        }
        fclose(disease);
    }

    //Append disease list
    else if(www=1){
        printf("\n\n");
        disease = fopen("Disease.txt","r");
        Disease = fopen("Disease.txt","a");
        while((fgets(disease2,20,disease))!=NULL){
            fscanf(disease,"%s",diseaseCode);
            if(strcmp(diseaseCode,symptomCode)==0){
                fgets(sol,500,disease);

                printf("The disease already exists in database.\n");
                printf("Present solution: ");
                puts(sol);
                break;
            }
        }
        if(strlen(sol)<5){
            printf("\nSolution: \n");
            gets(sol);
            fprintf(Disease,"%s %s\n",symptomCode,sol);
        }
        fclose(disease);
        fclose(Disease);
    }



    //final line
    {
        SetConsoleTextAttribute(hConsole,116);
        printf("\n\n\t\t    Prepared by: Md. Mushfiqur Rahman");
        printf("\n\t\t                      160041011\n\t\t                 Mashrur Mashfi\n\t\t                      160041003\n\t\t                 Abeed Hanif Aurko\n\t\t                      160041012");
        SetConsoleTextAttribute(hConsole,241);
        printf("\n\n                  Press any key to terminate.                   \n");
        printf("                 Press Enter for another input.                 \n");
        SetConsoleTextAttribute(hConsole,112);

    }
        char ttt=getch();
        if(ttt=='p')system("powerpnt Presentation1.pptx");
        else if(ttt!= 13)
            ex=2;

    }

    //end process
    fclose(doc);





    return 0;
}
