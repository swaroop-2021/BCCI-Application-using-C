#include<stdio.h>
#include<string.h>
#include<stdlib.h>

///Structure for poll
typedef struct polling
{
    char Question[80];
    char choice1[30],choice2[30],choice3[30],choice4[30];
    int ans1,ans2,ans3,ans4,p_count;
}P;

///Structure Member for Storing the data of the Poll
P po[50];
///Variable for counting the Questions
int q_count=0;


/**
Function Name: poll_load
Input Params: NILL
Return Type: void
Description: loads the data available into appropriate data structure
**/
void poll_load()
{
    FILE *fp;
    ///Opens the File in Read Mode
    fp=fopen("POLLS.txt","r");

    /// Check if the file was successfully opened
    if (fp == NULL)
    {
        printf("File Not found\n");
        return;
    }

    /// Until the end of the file, read all the file data
    while(!(feof(fp)))
    {
        fscanf(fp,"%s %s %s %s %s %d %d %d %d %d",po[q_count].Question,po[q_count].choice1,po[q_count].choice2,po[q_count].choice3
        ,po[q_count].choice4,&po[q_count].ans1,&po[q_count].ans2,&po[q_count].ans3,&po[q_count].ans4,&po[q_count].p_count);
        q_count++;
    }
    fclose(fp);
}

/**
Function Name: poll_store
Input Params: NILL
Return Type: void
Description: stores the data of the polls updated by the user back into the file
**/
void poll_store()
{
    FILE *fp;
    int i=0;
    ///Opens the File in Write Mode
    fp=fopen("POLLS.txt","w");

    /// Check if the file was successfully opened
    if (fp == NULL)
    {
        printf("File Not found\n");
        return;
    }
    /// Until the end of the Questions, write all the data into the file
    while(i<q_count)
    {
        fprintf(fp,"%s %s %s %s %s %d %d %d %d %d",po[i].Question,po[i].choice1,po[i].choice2,
        po[i].choice3,po[i].choice4,po[i].ans1,po[i].ans2,po[i].ans3,po[i].ans4,po[i].p_count);
        i++;
        if(i!=q_count)
            printf("\n");
    }
    fclose(fp);
}

/**
Function Name: poll
Input Params: NILL
Return Type: void
Description: displays the questions,accepts answers from the user and prints the final result of each question.
**/
void poll()
{
    ///Calls the "poll_load" function to get the data from the file
    poll_load();
    char a=177,b=219;
    int sum,ans;
    float perc1,perc2,perc3,perc4;

    ///Displays Questions with 4 choices and takes the answer as user input
    for(int i=0;i<q_count;i++)
    {
            printf("Question %d : %s\n\n",i+1,po[i].Question);
            printf("Choice 1: %s\t\n",po[i].choice1);
            printf("Choice 2: %s\t\n",po[i].choice2);
            printf("Choice 3: %s\t\n",po[i].choice3);
            printf("Choice 4: %s\n",po[i].choice4);
            printf("Enter the Choice: ");

            ///"IP" is a Identifier for the goto Statement
            IP :scanf("%d",&ans);


            switch(ans)
            {
                case 1: po[i].ans1++;
                        break;
                case 2: po[i].ans2++;
                        break;
                case 3: po[i].ans3++;
                        break;
                case 4: po[i].ans4++;
                        break;
                default : printf("\nInvalid option Enter the Choice Again\n");
                          goto IP;
            }

            ///Calculate the sum of the answers given
            sum=po[i].ans1+po[i].ans2+po[i].ans3+po[i].ans4;

            ///Calculates the Percentage of each answer
            perc1=((float)po[i].ans1/(float)sum)*100;
            perc2=((float)po[i].ans2/(float)sum)*100;
            perc3=((float)po[i].ans3/(float)sum)*100;
            perc4=((float)po[i].ans4/(float)sum)*100;


            printf("\n\n\t\t\t");
            ///Prints Each answer with its Percentage and the Status Bar
            for (int i = 0; i < 50; i++)
                printf("%c", a);

            if(perc1!=0)
            {
                printf("\r\t\t\t");

                for (int i = 0; i < perc1/2; i++)
                    printf("%c", b);
            }
            printf("\r %s ->%0.2f%% : ",po[i].choice1,perc1);
            printf("\n\n\t\t\t");


            for (int i = 0; i < 50; i++)
                printf("%c", a);
            if(perc2!=0)
            {
                printf("\r\t\t\t");
                for (int i = 0; i < perc2/2; i++)
                    printf("%c", b);
            }
            printf("\r %s ->%0.2f%% : ",po[i].choice2,perc2);



            printf("\n\n\t\t\t");
            for (int i = 0; i < 50; i++)
                printf("%c", a);
            if(perc3!=0)
            {
                printf("\r\t\t\t");

                for (int i = 0; i < perc3/2; i++)
                    printf("%c", b);
            }
            printf("\r %s ->%0.2f%% : ",po[i].choice3,perc3);


            printf("\n\n\t\t\t");
            for (int i = 0; i < 50; i++)
                printf("%c", a);
            if(perc4!=0)
            {
                printf("\r\t\t\t");

                for (int i = 0; i < perc4/2; i++)
                    printf("%c", b);
            }
            printf("\r %s ->%0.2f%% : ",po[i].choice4,perc4);
            po[i].p_count++;
            ///Prints the Total no. of Users Attempted this Quetion
            printf("\n\nNo. of users attempted this poll:%d \n\n",po[i].p_count);
    }
    ///After updating the poll answers the data is stored back
    ///into the file by calling the "poll_store" functions.
    poll_store();
}

