#include<stdio.h>
#include<string.h>
#include<direct.h>
#include<windows.h>
#include<math.h>
#include<stdlib.h>

///Structure for the date
typedef struct DT
{
    int day,month,year;
}DT;

/// Structure to store the batting details
typedef struct MATCH_TYPE_BATTING
{
    int MATS,RUNS,NO,INN,HS,CEN,HCEN;
    float AVE,SR;
}MTB;

///Structure to store the balling details
typedef struct MATCH_TYPE_BOWLING
{
    int MATS,BALLS,RUNS,WKT,INN,WK4;
    float ECON;
}MTBW;

///Structure to store the player details
typedef struct PLAYER_DETAILS
{
    char pname[50];
    int age;
    struct DT debut;

    struct DT DOB;
    char state[10];
    char Role[30];
    char GRADE[2];

    struct MATCH_TYPE_BATTING BAT_ODI;
    struct MATCH_TYPE_BOWLING BALL_ODI;

    struct MATCH_TYPE_BATTING BAT_TEST;
    struct MATCH_TYPE_BOWLING BALL_TEST;

    struct MATCH_TYPE_BATTING BAT_T20;
    struct MATCH_TYPE_BOWLING BALL_T20;
}PD;

int global_count=0;
PD PDS[100];
PD p_temp[100];
int ll=0;


/**
Function Name: load_from_file
Input Params: NILL
Return Type: void
Description: loads the data available into appropriate data structure
**/
void load_from_file()
{
    FILE *fp;

    /// Open the file in read mode
    fp = fopen("PLAYER.txt", "r");

    /// Check if the file was successfully opened
    if (fp == NULL)
    {
        printf("File Not found\n");
        return;
    }

    /// Until the end of the file, read all the file data
    while(!feof(fp))
    {
        fscanf(fp,"%s %d %d %d %d %d %d %d %s %s", PDS[global_count].pname, &PDS[global_count].age,
                &PDS[global_count].debut.day,&PDS[global_count].debut.month,&PDS[global_count].debut.year,
                &PDS[global_count].DOB.day,&PDS[global_count].DOB.month,&PDS[global_count].DOB.year,
                PDS[global_count].Role,PDS[global_count].GRADE);

        fscanf(fp,"%d %d %d %d %d %f %f %d %d",
               &PDS[global_count].BAT_TEST.MATS, &PDS[global_count].BAT_TEST.INN,&PDS[global_count].BAT_TEST.NO,
               &PDS[global_count].BAT_TEST.RUNS,&PDS[global_count].BAT_TEST.HS,&PDS[global_count].BAT_TEST.AVE,
               &PDS[global_count].BAT_TEST.SR,&PDS[global_count].BAT_TEST.CEN,&PDS[global_count].BAT_TEST.HCEN);
        fscanf(fp,"%d %d %d %d %d %f %f %d %d",
               &PDS[global_count].BAT_ODI.MATS, &PDS[global_count].BAT_ODI.INN,&PDS[global_count].BAT_ODI.NO,
               &PDS[global_count].BAT_ODI.RUNS,&PDS[global_count].BAT_ODI.HS,&PDS[global_count].BAT_ODI.AVE,
               &PDS[global_count].BAT_ODI.SR,&PDS[global_count].BAT_ODI.CEN,&PDS[global_count].BAT_ODI.HCEN);
        fscanf(fp,"%d %d %d %d %d %f %f %d %d",
               &PDS[global_count].BAT_T20.MATS, &PDS[global_count].BAT_T20.INN,&PDS[global_count].BAT_T20.NO,
               &PDS[global_count].BAT_T20.RUNS,&PDS[global_count].BAT_T20.HS,&PDS[global_count].BAT_T20.AVE,
               &PDS[global_count].BAT_T20.SR,&PDS[global_count].BAT_T20.CEN,&PDS[global_count].BAT_T20.HCEN);


        fscanf(fp,"%d %d %d %d %d %f %d",
               &PDS[global_count].BALL_TEST.MATS, &PDS[global_count].BALL_TEST.INN,&PDS[global_count].BALL_TEST.BALLS,
               &PDS[global_count].BALL_TEST.RUNS,&PDS[global_count].BALL_TEST.WKT,&PDS[global_count].BALL_TEST.ECON,
               &PDS[global_count].BALL_TEST.WK4);
        fscanf(fp,"%d %d %d %d %d %f %d",
               &PDS[global_count].BALL_ODI.MATS, &PDS[global_count].BALL_ODI.INN,&PDS[global_count].BALL_ODI.BALLS,
               &PDS[global_count].BALL_ODI.RUNS,&PDS[global_count].BALL_ODI.WKT,&PDS[global_count].BALL_ODI.ECON,
               &PDS[global_count].BALL_ODI.WK4);
        fscanf(fp,"%d %d %d %d %d %f %d",
               &PDS[global_count].BALL_T20.MATS, &PDS[global_count].BALL_T20.INN,&PDS[global_count].BALL_T20.BALLS,
               &PDS[global_count].BALL_T20.RUNS,&PDS[global_count].BALL_T20.WKT,&PDS[global_count].BALL_T20.ECON,
               &PDS[global_count].BALL_T20.WK4);

        global_count++;
    }

    fclose(fp);
}


/**
Function Name: welcome
Input Params: NILL
Return Type: void
Description: prints the welcome messege and current IST and UTC date and time
**/
void welcome()
{
    for(int k=0;k<2;k++)
    {
        for(int i=0;i<20;i++)
        {
        if(i==19)
            printf("BCCI");
        else
            printf("BCCI_");
        }
        printf("\n");
    }

    printf("\n\n\n\t\t\t\t\tWELCOME TO THE BCCI!!!");
    printf("\n\t\t\t\tTHE BOARD OF CONTROL FOR CRICKET IN INDIA");

    /// Declare the two Date structures
    SYSTEMTIME t,t2;

    /// Fills out the t with the IST system date and time
    GetLocalTime(&t);

    /// Fills out the t2 with the UTC system date and time
    GetSystemTime(&t2);

    printf("\n\n\t\t\t\t     IST\t\t\tUTC");
    printf("\n\t\t\t\tDate:%d/%d/%d",t.wDay,t.wMonth,t.wYear);
    printf("\t\t   Date:%d/%d/%d",t2.wDay,t2.wMonth,t2.wYear);

    printf("\n\t\t\t\tTime:%d-%d-%d", t.wHour, t.wMinute, t.wSecond);
    printf("\t\t   Time:%d-%d-%d", t2.wHour, t2.wMinute, t2.wSecond);

    printf("\n\n\n\n");

    for(int k=0;k<2;k++)
    {
        for(int i=0;i<20;i++)
        {
        if(i==19)
            printf("BCCI");
        else
            printf("BCCI_");
        }
        printf("\n");
    }

    printf("\n");
}


/**
Function Name: print_details
Input Params: NILL
Return Type: void
Description: prints the details of all the players
**/
void print_details()
{

        ///prints the information about the player
        char t[9]={
                    strlen("Matches"),strlen("Innings"),strlen("Not_Outs"),
                    strlen("Runs_"),strlen("Highest_Score"),strlen("Average"),
                    strlen("Strike_Rate"),strlen("100's"),strlen("50's")
                  };

        char l[7]={
                    strlen("Matches"),strlen("Innings"),strlen("Balls"),strlen("Runs_"),
                    strlen("Wickets"),strlen("Economy"),strlen("4Wickets")
                  };

        for(int local_count=0;local_count<global_count;local_count++)
        {

        printf(" NAME:%s\n Age:%d\n Debut Date:%d/%d/%d\n DOB:%d/%d/%d\n Role:%s\n Grade:%s\n\n",
                PDS[local_count].pname,PDS[local_count].age,
                PDS[local_count].debut.day,PDS[local_count].debut.month,PDS[local_count].debut.year,
                PDS[local_count].DOB.day,PDS[local_count].DOB.month,PDS[local_count].DOB.year,
                PDS[local_count].Role,PDS[local_count].GRADE);

        ///prints the batting performance summary of the player
        printf("\n BATTING\n\n");


        printf("         %-*s %-*s %-*s %-*s %-*s %-*s %-*s %-*s %-*s \n",
                t[0],"Matches",t[1],"Innings",t[2],"NotOuts",
                t[3],"Runs",t[4],"HighestScore",t[5],"Average",
                t[6],"StrikeRate",t[7],"100's",t[8],"50's");
        printf("\n TEST :  %-*d %-*d %-*d %-*d %-*d %-*.2f %-*.2f %-*d %-*d\n",
               t[0],PDS[local_count].BAT_TEST.MATS,t[1],PDS[local_count].BAT_TEST.INN,t[2],PDS[local_count].BAT_TEST.NO,
               t[3],PDS[local_count].BAT_TEST.RUNS,t[4],PDS[local_count].BAT_TEST.HS,t[5],PDS[local_count].BAT_TEST.AVE,
               t[6],PDS[local_count].BAT_TEST.SR,t[7],PDS[local_count].BAT_TEST.CEN,t[8],PDS[local_count].BAT_TEST.HCEN);
        printf("\n ODI  :  %-*d %-*d %-*d %-*d %-*d %-*.2f %-*.2f %-*d %-*d\n",
               t[0],PDS[local_count].BAT_ODI.MATS,t[1],PDS[local_count].BAT_ODI.INN,t[2],PDS[local_count].BAT_ODI.NO,
               t[3],PDS[local_count].BAT_ODI.RUNS,t[4],PDS[local_count].BAT_ODI.HS,t[5],PDS[local_count].BAT_ODI.AVE,
               t[6],PDS[local_count].BAT_ODI.SR,t[7],PDS[local_count].BAT_ODI.CEN,t[8],PDS[local_count].BAT_ODI.HCEN);
        printf("\n T20  :  %-*d %-*d %-*d %-*d %-*d %-*.2f %-*.2f %-*d %-*d\n",
               t[0],PDS[local_count].BAT_T20.MATS,t[1],PDS[local_count].BAT_T20.INN,t[2],PDS[local_count].BAT_T20.NO,
               t[3],PDS[local_count].BAT_T20.RUNS,t[4],PDS[local_count].BAT_T20.HS,t[5],PDS[local_count].BAT_T20.AVE,
               t[6],PDS[local_count].BAT_T20.SR,t[7],PDS[local_count].BAT_T20.CEN,t[8],PDS[local_count].BAT_T20.HCEN);

        ///prints the bowling performance summary of the player
        printf("\n BOWLING\n\n");
        printf("         %-*s %-*s %-*s %-*s %-*s %-*s %-*s\n",
                l[0],"Matches",l[1],"Innings",l[2],"Balls",
                l[3],"Runs",l[4],"Wickets",l[5],"Economy",
                l[6],"4Wickets");
        printf("\n TEST :  %-*d %-*d %-*d %-*d %-*d %-*.2f %-*d\n",
               l[0],PDS[local_count].BALL_TEST.MATS,l[1],PDS[local_count].BALL_TEST.INN,l[2],PDS[local_count].BALL_TEST.BALLS,
               l[3],PDS[local_count].BALL_TEST.RUNS,l[4],PDS[local_count].BALL_TEST.WKT,l[5],PDS[local_count].BALL_TEST.ECON,
               l[6],PDS[local_count].BALL_TEST.WK4);
        printf("\n ODI  :  %-*d %-*d %-*d %-*d %-*d %-*.2f %-*d\n",
               l[0],PDS[local_count].BALL_ODI.MATS,l[1],PDS[local_count].BALL_ODI.INN,l[2],PDS[local_count].BALL_ODI.BALLS,
               l[3],PDS[local_count].BALL_ODI.RUNS,l[4],PDS[local_count].BALL_ODI.WKT,l[5],PDS[local_count].BALL_ODI.ECON,
               l[6],PDS[local_count].BALL_ODI.WK4);
        printf("\n T20  :  %-*d %-*d %-*d %-*d %-*d %-*.2f %-*d\n\n",
               l[0],PDS[local_count].BALL_T20.MATS,l[1],PDS[local_count].BALL_T20.INN,l[2],PDS[local_count].BALL_T20.BALLS,
               l[3],PDS[local_count].BALL_T20.RUNS,l[4],PDS[local_count].BALL_T20.WKT,l[5],PDS[local_count].BALL_T20.ECON,
               l[6],PDS[local_count].BALL_T20.WK4);
        }
}

/**
Function Name: print_details1
Input Params: NILL
Return Type: void
Description: prints the details of the players whose name matches
             with the user entered sub string and also used to print
             the details of the players based on their roles
**/
void print_details1(PD p_temp[])
{
        if(ll==0)
        {
            printf("No Players Available\n");
            return;
        }
        char t[9]={
                    strlen("Matches"),strlen("Innings"),strlen("Not_Outs"),
                    strlen("Runs_"),strlen("Highest_Score"),strlen("Average"),
                    strlen("Strike_Rate"),strlen("100's"),strlen("50's")
                  };

        char l[7]={
                    strlen("Matches"),strlen("Innings"),strlen("Balls"),strlen("Runs_"),
                    strlen("Wickets"),strlen("Economy"),strlen("4Wickets")
                  };

        for(int local_count=0;local_count<ll;local_count++)
        {

            ///prints the information about the player
            printf("\n NAME:%s\n Age:%d\n Debut Date:%d/%d/%d\n DOB:%d/%d/%d\n Role:%s\n Grade:%s\n",
                    p_temp[local_count].pname,p_temp[local_count].age,
                    p_temp[local_count].debut.day,p_temp[local_count].debut.month,p_temp[local_count].debut.year,
                    p_temp[local_count].DOB.day,p_temp[local_count].DOB.month,p_temp[local_count].DOB.year,
                    p_temp[local_count].Role,p_temp[local_count].GRADE);

             ///prints the batting performance summary of the player
            printf("\n BATTING\n\n");


            printf("         %-*s %-*s %-*s %-*s %-*s %-*s %-*s %-*s %-*s \n",
                    t[0],"Matches",t[1],"Innings",t[2],"NotOuts",
                    t[3],"Runs",t[4],"HighestScore",t[5],"Average",
                    t[6],"StrikeRate",t[7],"100's",t[8],"50's");
            printf("\n TEST :  %-*d %-*d %-*d %-*d %-*d %-*.2f %-*.2f %-*d %-*d\n",
                t[0],p_temp[local_count].BAT_TEST.MATS,t[1],p_temp[local_count].BAT_TEST.INN,t[2],p_temp[local_count].BAT_TEST.NO,
                t[3],p_temp[local_count].BAT_TEST.RUNS,t[4],p_temp[local_count].BAT_TEST.HS,t[5],p_temp[local_count].BAT_TEST.AVE,
                t[6],p_temp[local_count].BAT_TEST.SR,t[7],p_temp[local_count].BAT_TEST.CEN,t[8],p_temp[local_count].BAT_TEST.HCEN);
            printf("\n ODI  :  %-*d %-*d %-*d %-*d %-*d %-*.2f %-*.2f %-*d %-*d\n",
                t[0],p_temp[local_count].BAT_ODI.MATS,t[1],p_temp[local_count].BAT_ODI.INN,t[2],p_temp[local_count].BAT_ODI.NO,
                t[3],p_temp[local_count].BAT_ODI.RUNS,t[4],p_temp[local_count].BAT_ODI.HS,t[5],p_temp[local_count].BAT_ODI.AVE,
                t[6],p_temp[local_count].BAT_ODI.SR,t[7],p_temp[local_count].BAT_ODI.CEN,t[8],p_temp[local_count].BAT_ODI.HCEN);
            printf("\n T20  :  %-*d %-*d %-*d %-*d %-*d %-*.2f %-*.2f %-*d %-*d\n",
                t[0],p_temp[local_count].BAT_T20.MATS,t[1],p_temp[local_count].BAT_T20.INN,t[2],p_temp[local_count].BAT_T20.NO,
                t[3],p_temp[local_count].BAT_T20.RUNS,t[4],p_temp[local_count].BAT_T20.HS,t[5],p_temp[local_count].BAT_T20.AVE,
                t[6],p_temp[local_count].BAT_T20.SR,t[7],p_temp[local_count].BAT_T20.CEN,t[8],p_temp[local_count].BAT_T20.HCEN);

            ///prints the bowling performance summary of the player
            printf("\n BOWLING\n\n");
            printf("         %-*s %-*s %-*s %-*s %-*s %-*s %-*s\n",
                    l[0],"Matches",l[1],"Innings",l[2],"Balls",
                    l[3],"Runs",l[4],"Wickets",l[5],"Economy",
                    l[6],"4Wickets");
            printf("\n TEST :  %-*d %-*d %-*d %-*d %-*d %-*.2f %-*d\n",
                l[0],p_temp[local_count].BALL_TEST.MATS,l[1],p_temp[local_count].BALL_TEST.INN,l[2],p_temp[local_count].BALL_TEST.BALLS,
                l[3],p_temp[local_count].BALL_TEST.RUNS,l[4],p_temp[local_count].BALL_TEST.WKT,l[5],p_temp[local_count].BALL_TEST.ECON,
                l[6],p_temp[local_count].BALL_TEST.WK4);
            printf("\n ODI  :  %-*d %-*d %-*d %-*d %-*d %-*.2f %-*d\n",
                l[0],p_temp[local_count].BALL_ODI.MATS,l[1],p_temp[local_count].BALL_ODI.INN,l[2],p_temp[local_count].BALL_ODI.BALLS,
                l[3],p_temp[local_count].BALL_ODI.RUNS,l[4],p_temp[local_count].BALL_ODI.WKT,l[5],p_temp[local_count].BALL_ODI.ECON,
                l[6],p_temp[local_count].BALL_ODI.WK4);
            printf("\n T20  :  %-*d %-*d %-*d %-*d %-*d %-*.2f %-*d\n\n",
                l[0],p_temp[local_count].BALL_T20.MATS,l[1],p_temp[local_count].BALL_T20.INN,l[2],p_temp[local_count].BALL_T20.BALLS,
                l[3],p_temp[local_count].BALL_T20.RUNS,l[4],p_temp[local_count].BALL_T20.WKT,l[5],p_temp[local_count].BALL_T20.ECON,
                l[6],p_temp[local_count].BALL_T20.WK4);
        }
}

/**
Function Name: brute_force_search
Input Params: string
Return Type: void
Description: prints the details of the players whose name matches the entered sub_string
**/
void brute_force_search(char st[])
{
    int j,m,n;
    ll=0;
    m=strlen(st);
    for(int k=0;k<=global_count;k++)
    {
        n=strlen(PDS[k].pname);
        for(int i=0;i<=n-m || i<=n;i++)
        {
            j=0;

            ///compare the name character by character
            while(j<m && st[j]==PDS[k].pname[i+j])
            {
                j++;
            }
            if(j==m)
            {
                p_temp[ll]=PDS[k];
                ll++;
                break;
            }
        }
    }
    print_details1(p_temp);
}

/**
Function Name: sort_by_name
Input Params: NILL
Return Type: void
Description: Display the player Details in the increasing alphabetical order
**/
void sort_by_name()
{
    int j;
    PD v[1];
    for(int i=1;i<global_count;i++)
    {
        v[0]=PDS[i];
        j=i-1;

        ///compare the name character by character
        while(j>=0 && strcmp(PDS[j].pname,v[0].pname)>0)
        {    PDS[j+1]=PDS[j];
            j--;
        }
        PDS[j+1]=v[0];
    }
    print_details();
}

/**
Function Name: players_sort_by_age
Input Params: NILL
Return Type: void
Description: Display the player Details in the increasing order of their age
**/
void players_sort_by_age()
{
	PD k[1];
	for(int i=0;i<global_count;i++)
	{
		for(int j=0;j<=i;j++)
		{
		    ///compare the age of all the players
			if(PDS[j].age > PDS[i].age)
			{
				k[0]=PDS[j];
				PDS[j]=PDS[i];
				PDS[i]=k[0];
			}
		}
	}
	print_details();
}


/**
Function Name: players_sort_by_debut_date
Input Params: NILL
Return Type: void
Description: Display the player details from latest debut date to least
**/
void players_sort_by_debut_date()
{
	PD k[1];
	for(int i=0;i<global_count;i++)
	{
		for(int j=0;j<=i;j++)
		{
			if(PDS[j].debut.year < PDS[i].debut.year)
			{
				k[0]=PDS[j];
				PDS[j]=PDS[i];
				PDS[i]=k[0];
			}
			else
			{
				if(PDS[j].debut.year==PDS[i].debut.year)
				{
					if(PDS[j].debut.month<PDS[i].debut.month)
					{
						k[0]=PDS[j];
                        PDS[j]=PDS[i];
                        PDS[i]=k[0];
					}
					else
					{
						if(PDS[j].debut.month==PDS[i].debut.month)
						{
							if(PDS[j].debut.day<PDS[i].debut.day)
							{
								k[0]=PDS[j];
                                PDS[j]=PDS[i];
                                PDS[i]=k[0];
							}

						}

					}

				}

			}
		}

	}
	print_details();
}

/**
Function Name: players_sort_by_dob
Input Params: NILL
Return Type: void
Description: Display the player details in the increasing order of their dob
**/
void players_sort_by_dob()
{
	PD k[1];
	for(int i=0;i<global_count;i++)
	{
		for(int j=0;j<=i;j++)
		{
			if(PDS[j].DOB.year > PDS[i].DOB.year)
			{
				k[0]=PDS[j];
				PDS[j]=PDS[i];
				PDS[i]=k[0];
			}
			else
			{
				if(PDS[j].DOB.year==PDS[i].DOB.year)
				{
					if(PDS[j].DOB.month>PDS[i].DOB.month)
					{
						k[0]=PDS[j];
                        PDS[j]=PDS[i];
                        PDS[i]=k[0];
					}
					else
					{
						if(PDS[j].DOB.month==PDS[i].DOB.month)
						{
							if(PDS[j].DOB.day>PDS[i].DOB.day)
							{
								k[0]=PDS[j];
                                PDS[j]=PDS[i];
                                PDS[i]=k[0];
							}

						}

					}

				}

			}
		}

	}
	print_details();
}


/**
Function Name: player_display_by_role
Input Params: NILL
Return Type: void
Description: Display the player details according to role whether batsman/bowler/all-rounder according
             to user input
**/
void players_display_by_role()
{
    int choice;
    PD temp[global_count];
    ll=0;

    ///gets input from the user
    printf("Enter \n1 for Batsman\n2 for Bowler\n3 for All-Rounder\n");
    printf("Enter Your Choice: \n");
    scanf("%d",&choice);
    switch(choice)
    {
        ///to display the batsman details
        case 1: for(int i=0;i<global_count;i++)
                {
                    if(strcmp(PDS[i].Role,"BATSMAN")==0)
                    {
                        temp[ll]=PDS[i];
                        ll++;
                    }
                }
                if(ll==0)
                 printf("No Players Available\n");
                else
                 print_details1(temp);
                break;

        ///to display the bowler details
        case 2: for(int i=0;i<global_count;i++)
                {
                    if(strcmp(PDS[i].Role,"BOWLER")==0)
                    {
                        temp[ll]=PDS[i];
                        ll++;
                    }
                }
                if(ll==0)
                 printf("No Players Available\n");
                else
                 print_details1(temp);
                break;

        ///to display the all rounder details
        case 3: for(int i=0;i<global_count;i++)
                {
                    if(strcmp(PDS[i].Role,"ALL-ROUNDER")==0)
                    {
                        temp[ll]=PDS[i];
                        ll++;
                    }
                }
                if(ll==0)
                 printf("No Players Available\n");
                else
                 print_details1(temp);
                break;
        default : printf("Inavlid option\n");

    }
}

/**
Function Name: Facebook
Input Params: NILL
Return Type: void
Description: Open the official facebook page of the BCCI in browser
**/
void Facebook()
{
    printf("\nRedirecting To Facebook\n");
    system("start https://www.facebook.com/IndianCricketTeam/");
}


/**
Function Name: Instagram
Input Params: NILL
Return Type: void
Description: Open the official Instagram account of the BCCI in browser
**/
void Instagram()
{
    printf("\nRedirecting To Instagram\n");
    system("start https://www.instagram.com/indiancricketteam/");
}

/**
Function Name: Twitter
Input Params: NILL
Return Type: void
Description: Open the official Twitter handle of the BCCI in browser
**/
void Twitter()
{
    printf("\nRedirecting To Twitter\n");
    system("start https://twitter.com/BCCI");
}

/**
Function Name: Gallery
Input Params: NILL
Return Type: void
Description: Open the the recent photos (Gallery) in external browser
**/
void Gallery()
{
    printf("Redirecting to Gallery of BCCI\n");
    system("start https://www.bcci.tv/albums");
}

/**
Function Name: Store
Input Params: NILL
Return Type: void
Description: Open the the official merchandise shopping site in external browser
**/
void Store()
{
    printf("Redirecting to store of BCCI\n");
    system("start https://mplsports.in/pages/bcci");
}

/**
Function Name: Gallery
Input Params: NILL
Return Type: void
Description: Open the the recent videos in external browser
**/
void videos()
{
    printf("Redirecting to Videos of BCCI\n");
    system("start https://www.bcci.tv/videos/Latest");
}

/**
Function Name: IPL
Input Params: NILL
Return Type: void
Description: Redirect to the IPL website where all information about IPL is available
**/
void Ipl()
{
    printf("Redirecting IPL\n");
    system("start https://iplt20.com/");
}
