#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


///Structure for the date
typedef struct DATES
{
    int day,month,year;
}DATES;


///Doubly Linked List Structure to store the details of the upcoming matches(fixtures)
typedef struct fix
{
    struct DATES FDT;
    char fname[100];
    float tm;
    char am_pm[2];
    char opponent[30];
    char mat_type[10];
    int mat_no;
    char std[50];
    struct fix *next;
    struct fix *prev;
}FIX;

///Doubly Linked List Structure to store the latest news headlines
typedef struct bcci_news
{
    char headline[500];
    struct DATES News_Date;
    struct bcci_news *next;
    struct bcci_news *prev;
}NW;


///Doubly Linked List Structure to Store the information about the Stadiums in India (Venues)
typedef struct venue
{
    int nmb;
    char vname[50];
    int capacity;
    char location[30];
    char vstate[30];
    struct venue *next;
    struct venue *prev;
}VENUE;


///Doubly Linked List Structure to store the results of the ODI and T20 matches
typedef struct ODI_T20
{
    char s_name[100];
    char opp[50];
    struct DATES RDT;
    int op_run;
    int op_wc;
    float op_over;
    int in_run;
    int in_wc;
    float in_over;
    char res[100];
    struct ODI_T20 *next;
    struct ODI_T20 *prev;
}OT;


///Doubly Linked List Structure to store the results of the Test matches
typedef struct TST
{
    char s_name[100];
    char opp[50];
    struct DATES RDT;
    int op_run1;
    int op_wc1;
    float op_over1;
    int op_run2;
    int op_wc2;
    float op_over2;
    int in_run1;
    int in_wc1;
    float in_over1;
    int in_run2;
    int in_wc2;
    float in_over2;
    char res[100];
    struct TST *next;
    struct TST *prev;
}TT;

NW NWS[25];
int cc=0;
FIX FIXT[25];
VENUE VN[10];
TT TEST_RES[10];
int res_tst=0;
int res_t20=0;
OT OD[10];
OT T2[10];
int res_odi=0;

typedef struct bcci_news * NODE;
typedef struct fix * NODE2;
typedef struct venue * NODE3;
typedef struct ODI_T20 * NODE4;
typedef struct TST * NODE5;


///Doubly Linked List for the news
NODE head=NULL;
void news();
NODE getNode(int );
void NEWS_DISPLAY(NODE);
NODE Insert_end(NODE,int );
void news_sort_by_date();


///Doubly Linked List for the Fixtures
NODE2 head2=NULL;
int C3=0;
NODE2 getNode_FIXTURE(int );
void FIX_DISPLAY(NODE2);
NODE2 Insert_end_FIX(NODE2,int );


///Doubly Linked List for the Venues
NODE3 getNode_VENUE(int );
void VENUE_DISPLAY(NODE3);
NODE3 Insert_end_VENUE(NODE3,int );


///Doubly Linked List for the ODI and T20 matches results
NODE4 getNode_ODI_T20(OT [],int );
void print_result_odi_t20(NODE4);
NODE4 Insert_end_res_odi_t20(NODE4,OT [],int );
void results_odi_details();
void results_t20_details();


///Doubly Linked List for the Test match results
NODE5 getNode_TEST(int );
void print_result_test(NODE5);
NODE5 Insert_end_res_test(NODE5,int );
void results_test_details();

void results_date_range();
void results_odi_details_load();
void results_t20_details_load();
void results_test_details_load();
void results_odi_details();
void results_t20_details();
void results_test_details();
int compare_date(DATES a,DATES b);



/**
Function Name: news_load
Input Params: head node
Return Type: NODE
Description: Loads the news details into appropriate data structure
**/
NODE news_load(NODE head)
{
    FILE *fp2;

    /// Open the file in read mode
    fp2=fopen("NEWS.txt","r");

    /// Check if the file was successfully opened
    if (fp2 == NULL)
    {
        printf("File Not found\n");
        return head;
    }


    /// Until the end of the file, read all the file data
    while(!feof(fp2))
    {
          fscanf(fp2,"%d %d %d %s",&NWS[cc].News_Date.day,&NWS[cc].News_Date.month,&NWS[cc].News_Date.year,NWS[cc].headline);
          cc++;
    }

    ///Insert the read values in the Doubly linked list
    for(int i=0;i<cc;i++)
        head=Insert_end(head,i);

    fclose(fp2);

    return(head);
}

/**
Function Name: getNode
Input Params: i
Return Type: NODE
Description: Creates a node for the Doubly linked list of type NODE
**/
NODE getNode(int i)
{
    NODE Newnode=malloc(sizeof(struct bcci_news));
     if(Newnode==NULL)
    {
        printf("memory not allocated\n");
        exit(0);
    }
    strcpy(Newnode->headline,NWS[i].headline);
    Newnode->News_Date=NWS[i].News_Date;
    Newnode->next=NULL;
    Newnode->prev=NULL;
    return Newnode;
}

/**
Function Name: Insert_end
Input Params: head,i
Return Type: NODE
Description: Adds the new node to the end of the doubly linked list of the type NODE
**/
NODE Insert_end(NODE head,int i)
{
    NODE newnode=getNode(i);
    if(head==NULL)
    {
        head=newnode;
        return head;
    }
    else
    {
        NODE cur=head;
        while(cur->next!=NULL)
        {
            cur=cur->next;
        }
        cur->next=newnode;
        newnode->prev=cur;
        return head;
    }
}

/**
Function Name: news
Input Params: NILL
Return Type: NODE
Description: Redirect to the display news function
**/
void news()
{
    if(head!=NULL)
        NEWS_DISPLAY(head);
    else
        {
            head=news_load(head);
            NEWS_DISPLAY(head);
        }
}

/**
Function Name: News_Display
Input Params: NILL
Return Type: void
Description: Show the latest news headlines
**/
void NEWS_DISPLAY(NODE head)
{
    if(head==NULL)
    {
        printf("No news Available\n");
    }
    else
    {
        NODE cur=head;
        char ch;
        printf("\n%d\\%d\\%d %s\n\n",cur->News_Date.day,cur->News_Date.month,cur->News_Date.year,cur->headline);
        while(1)
        {
            if(cur->prev==NULL && cur->next==NULL )
            {
                printf("\n\nNo more news available\n\n");
                break;
            }
            else if(cur->prev==NULL)
            {
                prep: printf("Press N for Next News \n E for Exit\n");
                scanf("%c %c",&ch,&ch);
                if(toupper(ch)!='E'  && toupper(ch)!='N')
                {
                    printf("\nInvalid Choice\n");
                    goto prep;
                }
            }
            else if(cur->next==NULL)
            {
                nerp: printf("Press P for Previous News \n E for Exit\n");
                scanf("%c %c",&ch,&ch);
                if(toupper(ch)!='P' && toupper(ch)!='E')
                {
                    printf("\nInvalid Choice\n");
                    goto nerp;
                }
            }
            else
            {
                    printf("Press P for Previous News \n N for Next News \n E for Exit");
                    scanf("%c %c",&ch,&ch);
            }
            switch(toupper(ch))
            {
                case 'E': printf("\n\nNews Ended\n\n");
                          return;
                case 'P':
                          cur=cur->prev;
                          printf("\n%d\\%d\\%d %s\n\n",cur->News_Date.day,cur->News_Date.month,cur->News_Date.year,cur->headline);
                          break;
                 case 'N':
                          cur=cur->next;
                          printf("\n%d\\%d\\%d %s\n\n",cur->News_Date.day,cur->News_Date.month,cur->News_Date.year,cur->headline);
                          break;
                 default:printf("Invalid choice\n");
            }
        }
    }
}


/**
Function Name: fixture_load
Input Params: NILL
Return Type: NODE
Description: Loads the fixture details in the appropriate data structure
**/
void fixture_load()
{
    FILE *fp4;

    fp4=fopen("FIXTURES.txt","r");

    if (fp4 == NULL)
    {
        printf("File Not found\n");
        return;
    }

    while(!feof(fp4))
    {

          fscanf(fp4,"%s %d %d %d %f %s %s %s %d %s",FIXT[C3].fname,&FIXT[C3].FDT.day,
          &FIXT[C3].FDT.month,&FIXT[C3].FDT.year,&FIXT[C3].tm,FIXT[C3].am_pm,FIXT[C3].opponent,
          FIXT[C3].mat_type,&FIXT[C3].mat_no,FIXT[C3].std);

          C3++;
    }

    fclose(fp4);
}

/**
Function Name: FIXTURE
Input Params: NILL
Return Type: void
Description: Loads the Fixtures in the linked list and redirects to FIX_DISPLAY function
**/
void fixture()
{
    fixture_load();
    for(int i=0;i<C3;i++)
        head2=Insert_end_FIX(head2,i);

    FIX_DISPLAY(head2);
}

/**
Function Name: getNode_FIXTURE
Input Params: i
Return Type: NODE2
Description: Creates a node for the Doubly linked list of type NODE2
**/
NODE2 getNode_FIXTURE(int i)
{
    NODE2 Newnode=malloc(sizeof(struct fix));

     if(Newnode==NULL)
    {
        printf("memory not allocated\n");
        exit(0);
    }

    *Newnode=FIXT[i];

    Newnode->next=NULL;
    Newnode->prev=NULL;

    return Newnode;
}

/**
Function Name: Insert_end_FIX
Input Params: head,i
Return Type: NODE2
Description: Adds the new node to the end of the doubly linked list of the type NODE2
**/
NODE2 Insert_end_FIX(NODE2 head,int i)
{
    NODE2 newnode=getNode_FIXTURE(i);

    if(head==NULL)
    {
        head=newnode;
        return head;
    }

    else
    {
        NODE2 cur=head;
        while(cur->next!=NULL)
        {
            cur=cur->next;
        }
        cur->next=newnode;
        newnode->prev=cur;

        return head;
    }
}

/**
Function Name: FIX_DISPLAY
Input Params: head2
Return Type: void
Description: DISPLAYS THE UPCOMING FIXTURES OF TEAM INDIA
**/
void FIX_DISPLAY(NODE2 head2)
{
    if(head2==NULL)
    {
        printf("No FIX Available\n");
    }

    else
    {
        NODE2 cur=head2;
        char ch;

        printf("Fixture Name: %s\nDate: %d\\%d\\%d \nTime: %0.2f %s\nOpponent: %s\nMatch_Type: %s\nMatch_NO: %d\nStadium: %s\n",
        cur->fname,cur->FDT.day,cur->FDT.month,cur->FDT.year,cur->tm,
        cur->am_pm,cur->opponent,cur->mat_type,cur->mat_no,cur->std);


        while(1)
        {
            if(cur->prev==NULL && cur->next==NULL )
            {
                printf("\n\nNo more fixtures available\n\n");
                break;
            }

            else if(cur->prev==NULL)
            {
                prep: printf("Press N for Next FIXTURE \n E for Exit\n");
                scanf("%c %c",&ch,&ch);
                if(toupper(ch)!='E'  && toupper(ch)!='N')
                {
                    printf("\nInvalid Choice\n");
                    goto prep;
                }
            }

            else if(cur->next==NULL)
            {
                nerp: printf("Press P for Previous FIXTURE \n E for Exit\n");
                scanf("%c %c",&ch,&ch);
                if(toupper(ch)!='P' && toupper(ch)!='E')
                {
                    printf("\nInvalid Choice\n");
                    goto nerp;
                }
            }

            else
            {
                    printf("Press P for Previous FIXTURE \n N for Next FIXTURE \n E for Exit");
                    scanf("%c %c",&ch,&ch);
            }
            switch(toupper(ch))
            {
                case 'E': printf("\n\nEnd\n\n");
                          return;
                case 'P':
                          cur=cur->prev;
                          printf("Fixture Name: %s\nDate: %d\\%d\\%d \nTime: %0.2f %s\nOpponent: %s\nMatch_Type: %s\nMatch_NO: %d\nStadium: %s\n",
                          cur->fname,cur->FDT.day,cur->FDT.month,cur->FDT.year,cur->tm,
                          cur->am_pm,cur->opponent,cur->mat_type,cur->mat_no,cur->std);
                          break;
                 case 'N':
                          cur=cur->next;
                          printf("Fixture Name: %s\nDate: %d\\%d\\%d \nTime: %0.2f %s\nOpponent: %s\nMatch_Type: %s\nMatch_NO: %d\nStadium: %s\n",
                          cur->fname,cur->FDT.day,cur->FDT.month,cur->FDT.year,cur->tm,
                          cur->am_pm,cur->opponent,cur->mat_type,cur->mat_no,cur->std);
                          break;
                 default:printf("Invalid choice\n");
            }
        }
    }
}

/**
Function Name: rabin_sub_string_fixture
Input Params: string
Return Type: void
Description: prints the details of the Fixture whose name matches the entered sub_string
**/
void rabin_sub_string_fixture(char p[])
{
    fixture_load();
    char t[100];
    int i,l,ps=strlen(p),ts,psum=0;
    NODE2 temp=NULL;
    for(i=0;i<ps;i++)
    {
        int k;
        k=p[i];
         psum=psum+k;
    }

    for(int y=0;y<C3;y++)
    {
        int tsum=0,j=0,kk=0;
        strcpy(t,FIXT[y].fname);
        ts=strlen(t);
        while(j<ts-ps)
        {
            tsum=0;
            for(int m=j ; m<j+ps && m<ts-ps ; m++)
            {
                int u;
                u=t[m];
                tsum=tsum+u;
            }
            if(tsum==psum)
            {
                int c=0;
                for(l=0,kk=j;l<ps && j<ts-ps;l++,kk++)
                {
                    if(p[l]==t[kk])
                    {
                        c++;
                    }
                    else
                        break;
                }
                if(c==ps)
                {
                    temp=Insert_end_FIX(temp,y);
                    break;
                }
                j++;
            }
            else
            {
                 j++;
            }
        }

    }
    FIX_DISPLAY(temp);
}



/**
Function Name: FIX_DISPLAY_BY_TYPE_OF_MATCH
Input Params: NILL
Return Type: NODE
Description: Displays the upcoming match details by specific match type by getting user input
**/
void FIX_DISPLAY_BY_TYPE_OF_MATCH()
{
    if(head2==NULL)
    {
        fixture_load();
        for(int i=0;i<C3;i++)
        head2=Insert_end_FIX(head2,i);
    }
    NODE2 temp=NULL,cur=head2;
    int match_type,j=0;
    printf("Enter \n1 for ODI\n2 for T20I\n3 for TEST\n");
    scanf("%d",&match_type);

    switch(match_type)
    {
        case 1:  while(cur!=NULL)
                {
                    if(strcmp(cur->mat_type,"ODI")==0)
                    {
                        temp=Insert_end_FIX(temp,j);
                    }
                    j++;
                    cur=cur->next;
                }
                break;
         case 2:  while(cur!=NULL)
                {
                    if(strcmp(cur->mat_type,"T20I")==0)
                    {
                        temp=Insert_end_FIX(temp,j);
                    }
                    j++;
                    cur=cur->next;
                }
                break;
          case 3:   while(cur!=NULL)
                {
                    if(strcmp(cur->mat_type,"TEST")==0)
                    {
                        temp=Insert_end_FIX(temp,j);
                    }
                    j++;
                    cur=cur->next;
                }
                break;
    }

    cur=temp;
    if(cur==NULL)
    {
        printf("No FIX Available\n");
    }
    else
    {
        char ch;

                printf("Fixture Name: %s\nDate: %d\\%d\\%d \nTime: %0.2f %s\nOpponent: %s\nMatch_Type: %s\nMatch_NO: %d\nStadium: %s\n",
                cur->fname,cur->FDT.day,cur->FDT.month,cur->FDT.year,cur->tm,
                cur->am_pm,cur->opponent,cur->mat_type,cur->mat_no,cur->std);


        while(1)
        {
            if(cur->prev==NULL && cur->next==NULL )
            {
                printf("\n\nNo more fixtures available\n\n");
                break;
            }

            else if(cur->prev==NULL)
            {
                prep: printf("Press N for Next FIXTURE \n E for Exit\n");
                scanf("%c %c",&ch,&ch);
                if(toupper(ch)!='E'  && toupper(ch)!='N')
                {
                    printf("\nInvalid Choice\n");
                    goto prep;
                }
            }

            else if(cur->next==NULL)
            {
                nerp: printf("Press P for Previous FIXTURE \n E for Exit\n");
                scanf("%c %c",&ch,&ch);
                if(toupper(ch)!='P' && toupper(ch)!='E')
                {
                    printf("\nInvalid Choice\n");
                    goto nerp;
                }
            }

            else
            {
                    printf("Press P for Previous FIXTURE \n N for Next FIXTURE \n E for Exit");
                    scanf("%c %c",&ch,&ch);
            }
            switch(toupper(ch))
            {
                case 'E': printf("\n\nEnd\n\n");
                          return;
                case 'P':
                          cur=cur->prev;
                          printf("Fixture Name: %s\nDate: %d\\%d\\%d \nTime: %0.2f %s\nOpponent: %s\nMatch_Type: %s\nMatch_NO: %d\nStadium: %s\n",
                          cur->fname,cur->FDT.day,cur->FDT.month,cur->FDT.year,cur->tm,
                          cur->am_pm,cur->opponent,cur->mat_type,cur->mat_no,cur->std);
                          break;
                 case 'N':
                          cur=cur->next;
                          printf("Fixture Name: %s\nDate: %d\\%d\\%d \nTime: %0.2f %s\nOpponent: %s\nMatch_Type: %s\nMatch_NO: %d\nStadium: %s\n",
                          cur->fname,cur->FDT.day,cur->FDT.month,cur->FDT.year,cur->tm,
                          cur->am_pm,cur->opponent,cur->mat_type,cur->mat_no,cur->std);
                          break;
                 default:printf("Invalid choice\n");
            }
        }
    }
}


/**
Function Name: fix_display_by_month_range
Input Params: NILL
Return Type: NODE2
Description: Displays the upcoming match details between the user given month range for the year 2022
**/
void fix_display_by_month_range()
{
    if(head2==NULL)
    {
        fixture_load();
        for(int i=0;i<C3;i++)
        head2=Insert_end_FIX(head2,i);
    }
    int a,b;

    ///gets input from the user
    printf("\n\nEnter the Starting and Ending month of the year 2022\n");
    scanf("%d %d",&a,&b);

    NODE2 temp=NULL,cur=head2;
    int j=0;

    while(cur!=NULL)
    {
        if(cur->FDT.month >=a && cur->FDT.month <=b)
        {
            temp=Insert_end_FIX(temp,j);
        }
        j++;
        cur=cur->next;
    }

    FIX_DISPLAY(temp);
}

/**
Function Name: venue_details
Input Params: NILL
Return Type: void
Description: Loads the Venue details into appropriate data structure and calls the VENUE_DISPLAY function
**/
void venue_details()
{
    FILE *fp5;
    int C4=0;

    fp5=fopen("VENUE.txt","r");

    if (fp5 == NULL)
    {
        printf("File Not found\n");
        return;
    }

    while(!feof(fp5))
    {

          fscanf(fp5,"%d %s %d %s %s",&VN[C4].nmb,VN[C4].vname,&VN[C4].capacity,VN[C4].location,VN[C4].vstate);
          C4++;
    }

    fclose(fp5);

    NODE3 head=NULL;

   for(int i=0;i<C4;i++)
        head=Insert_end_VENUE(head,i);

    VENUE_DISPLAY(head);
}

/**
Function Name: getNode_VENUE
Input Params: i
Return Type: NODE3
Description: Creates a node for the Doubly linked list of type NODE3
**/
NODE3 getNode_VENUE(int i)
{
    NODE3 Newnode=malloc(sizeof(struct venue));

     if(Newnode==NULL)
    {
        printf("memory not allocated\n");
        exit(0);
    }

    *Newnode=VN[i];

    Newnode->next=NULL;
    Newnode->prev=NULL;

    return Newnode;
}

/**
Function Name: Insert_end_VENUE
Input Params: head,i
Return Type: NODE3
Description: Adds the new node to the end of the doubly linked list of the type NODE3
**/
NODE3 Insert_end_VENUE(NODE3 head,int i)
{
    NODE3 newnode=getNode_VENUE(i);

    if(head==NULL)
    {
        head=newnode;
        return head;
    }

    else
    {
        NODE3 cur=head;
        while(cur->next!=NULL)
        {
            cur=cur->next;
        }
        cur->next=newnode;
        newnode->prev=cur;

        return head;
    }
}

/**
Function Name: VENUE_DISPLAY
Input Params: head
Return Type: void
Description: DISPLAYS THE INFORMATION ABOUT THE STADIUMS IN INDIA
**/
void VENUE_DISPLAY(NODE3 head)
{
    if(head==NULL)
    {
        printf("No VENUE Available\n");
    }

    else
    {
        NODE3 cur=head;
        char ch;

        printf("Name : %s\nCapacity : %d\nLocation : %s\nState : %s\n\n",cur->vname,cur->capacity,cur->location,cur->vstate);

        while(1)
        {
            if(cur->prev==NULL && cur->next==NULL )
            {
                printf("\n\nNo more fixtures available\n\n");
                break;
            }

            else if(cur->prev==NULL)
            {
                prep: printf("Press N for Next VENUE \n E for Exit\n");
                scanf("%c %c",&ch,&ch);
                if(toupper(ch)!='E'  && toupper(ch)!='N')
                {
                    printf("\nInvalid Choice\n");
                    goto prep;
                }
            }

            else if(cur->next==NULL)
            {
                nerp: printf("Press P for Previous VENUE \n E for Exit\n");
                scanf("%c %c",&ch,&ch);
                if(toupper(ch)!='P' && toupper(ch)!='E')
                {
                    printf("\nInvalid Choice\n");
                    goto nerp;
                }
            }

            else
            {
                    printf("Press P for Previous VENUE \n N for Next VENUE \n E for Exit\n");
                    scanf("%c %c",&ch,&ch);
            }
            switch(toupper(ch))
            {
                case 'E': printf("\n\nEnd\n\n");
                          return;
                case 'P':
                          cur=cur->prev;
                          printf("Name : %s\nCapacity : %d\nLocation : %s\nState : %s\n\n",cur->vname,cur->capacity,cur->location,cur->vstate);
                          break;
                 case 'N':
                          cur=cur->next;
                           printf("Name : %s\nCapacity : %d\nLocation : %s\nState : %s\n\n",cur->vname,cur->capacity,cur->location,cur->vstate);
                          break;
                 default:printf("Invalid choice\n");
            }
        }
    }
}


/**
Function Name: news_sort_by_date
Input Params: NILL
Return Type: void
Description: Display the news details in the ascending order of their date of publish
**/
void news_sort_by_date()
{
    if(head==NULL)
    {
        head=news_load(head);
    }
    NODE temp=head,cur;
    while(temp->next!=NULL)
     temp=temp->next;
    while(temp->prev!=head)
    {
        cur=temp->next;
        temp=temp->prev;
        free(cur);
    }
    free(head);

	NW k[1];
	for(int i=0;i<cc;i++)
	{
		for(int j=0;j<=i;j++)
		{
			if(NWS[j].News_Date.year > NWS[i].News_Date.year)
			{
				k[0]=NWS[j];
				NWS[j]=NWS[i];
				NWS[i]=k[0];
			}
			else
			{
				if(NWS[j].News_Date.year==NWS[i].News_Date.year)
				{
					if(NWS[j].News_Date.month>NWS[i].News_Date.month)
					{
						k[0]=NWS[j];
                        NWS[j]=NWS[i];
                        NWS[i]=k[0];
					}
					else
					{
						if(NWS[j].News_Date.month==NWS[i].News_Date.month)
						{
							if(NWS[j].News_Date.day>NWS[i].News_Date.day)
							{
								k[0]=NWS[j];
                                NWS[j]=NWS[i];
                                NWS[i]=k[0];
							}

						}

					}

				}

			}
		}
	}

    head=NULL;
    for(int i=0;i<cc;i++)
        head=Insert_end(head,i);
    printf("\nNews in Ascending order of publish\n");
    NEWS_DISPLAY(head);
}


/**
Function Name: results
Input Params: NILL
Return Type: void
Description: Gets input from the user about specific match type to display the result
**/
void results()
{
    int match_type;
    printf("Enter \n1 for ODI\n2 for T20I\n3 for TEST\n");
    scanf("%d",&match_type);
    switch(match_type)
    {
        case 1: results_odi_details();
                break;
        case 2: results_t20_details();
                break;
        case 3: results_test_details();
                break;
    }
}

/**
Function Name: results_date_range
Input Params: NILL
Return Type: void
Description: Gets input from the user about specific match type to display the result between the date range given by user
**/
void results_date_range()
{
    DATES a,b;
    int match_type;
    NODE4 temp=NULL;
    printf("Enter \n1 for ODI\n2 for T20I\n3 for TEST\n");
    scanf("%d",&match_type);

    ///gets input from the user
    printf("\n\nEnter the Starting Date in the format dd mm yyyy\n");
    scanf("%d %d %d",&a.day,&a.month,&a.year);
    printf("\n\nEnter the Ending Date in the format dd mm yyyy\n");
    scanf("%d %d %d",&b.day,&b.month,&b.year);

    if(!(compare_date(a,b)))
    {
        printf("Invalid Date Format\nStarting Date should be less then end date");
        return;
    }

    switch(match_type)
    {
        case 1: results_odi_details_load();

                for(int i=0;i<res_odi;i++)
                {
                    if(OD[i].RDT.year > a.year && OD[i].RDT.year < b.year)
                    {
                        temp=Insert_end_res_odi_t20(temp,OD,i);
                    }
                    else if(OD[i].RDT.year==a.year || OD[i].RDT.year==b.year || a.year==b.year)
                    {
                        if(OD[i].RDT.month > a.month && OD[i].RDT.month < b.month)
                        {
                            temp=Insert_end_res_odi_t20(temp,OD,i);
                        }
                        else if(OD[i].RDT.month == a.month || OD[i].RDT.month == b.month || a.month==b.month)
                        {
                            if((OD[i].RDT.day > a.day && OD[i].RDT.day < b.day) ||a.day==b.day)
                            {
                                temp=Insert_end_res_odi_t20(temp,OD,i);
                            }
                        }
                    }
                }
                print_result_odi_t20(temp);
                break;
        case 2: results_t20_details_load();

                for(int i=0;i<res_t20;i++)
                {
                    if(T2[i].RDT.year > a.year && T2[i].RDT.year < b.year)
                    {
                        temp=Insert_end_res_odi_t20(temp,T2,i);
                    }
                    else if(T2[i].RDT.year==a.year || T2[i].RDT.year==b.year || a.year==b.year)
                    {
                        if(T2[i].RDT.month > a.month && T2[i].RDT.month < b.month)
                        {
                            temp=Insert_end_res_odi_t20(temp,T2,i);
                        }
                        else if(T2[i].RDT.month == a.month || T2[i].RDT.month == b.month || a.month==b.month)
                        {
                            if((T2[i].RDT.day > a.day && T2[i].RDT.day < b.day) ||a.day==b.day)
                            {
                                temp=Insert_end_res_odi_t20(temp,T2,i);
                            }
                        }
                    }
                }
                print_result_odi_t20(temp);
                break;
        case 3: results_test_details_load();

                NODE5 temp=NULL;

                for(int i=0;i<res_tst;i++)
                {
                    if(TEST_RES[i].RDT.year > a.year && TEST_RES[i].RDT.year < b.year)
                    {
                        temp=Insert_end_res_test(temp,i);
                    }
                    else if(TEST_RES[i].RDT.year==a.year || TEST_RES[i].RDT.year==b.year || a.year==b.year)
                    {
                        if(TEST_RES[i].RDT.month > a.month && TEST_RES[i].RDT.month < b.month)
                        {
                            temp=Insert_end_res_test(temp,i);
                        }
                        else if(TEST_RES[i].RDT.month == a.month || TEST_RES[i].RDT.month == b.month || a.month==b.month)
                        {
                            if((TEST_RES[i].RDT.day > a.day && TEST_RES[i].RDT.day < b.day) ||a.day==b.day)
                            {
                                temp=Insert_end_res_test(temp,i);
                            }
                        }
                    }
                }
                print_result_test(temp);
                break;
    }
}

/**
Function Name: compare_date
Input Params: date a,date b
Return Type: int
Description: Compares whether the format of the date is correct or not
**/
int compare_date(DATES a,DATES b)
{
    if(a.year==b.year && a.month==b.month && a.day==b.day)
        return 0;
    else if(a.year>b.year)
    {
        return 0;
    }
    else if(a.year==b.year)
    {
        if(a.month>b.month)
        {
            return 0;
        }
        else if(a.day>b.day)
        {
            return 0;
        }
    }
    return 1;
}


/**
Function Name: results_odi_details_load
Input Params: NILL
Return Type: void
Description: Gets the results from the file and load into appropriate structures
**/
void results_odi_details_load()
{
    FILE *fp;
    res_odi=0;

    fp=fopen("RESULTS_ODI.txt","r");

    if(fp==NULL)
    {
        printf("FILE NOT FOUND");
        return;
    }

    while(!feof(fp))
    {
        fscanf(fp,"%s %s %d %d %d %d %d %f %d %d %f %s",OD[res_odi].s_name,OD[res_odi].opp,&OD[res_odi].RDT.day,&OD[res_odi].RDT.month,&OD[res_odi].RDT.year,
        &OD[res_odi].op_run,&OD[res_odi].op_wc,&OD[res_odi].op_over,&OD[res_odi].in_run,&OD[res_odi].in_wc,&OD[res_odi].in_over,OD[res_odi].res);

        res_odi++;
    }
    fclose(fp);

}


/**
Function Name: results_odi_details
Input Params: NILL
Return Type: void
Description: Loads the data into the Doubly Linked list and calls the print function
**/
void results_odi_details()
{
    results_odi_details_load();
    NODE4 head=NULL;
    for(int i=0;i<res_odi;i++)
        head=Insert_end_res_odi_t20(head,OD,i);

    print_result_odi_t20(head);
}

/**
Function Name: results_t20_details_load
Input Params: NILL
Return Type: void
Description: Gets the results from the file and load into appropriate structures
**/
void results_t20_details_load()
{
    FILE *fp;
    res_t20=0;

    fp=fopen("RESULTS_T20.txt","r");

    if(fp==NULL)
    {
        printf("FILE NOT FOUND");
        return;
    }

    while(!feof(fp))
    {
        fscanf(fp,"%s %s %d %d %d %d %d %f %d %d %f %s",T2[res_t20].s_name,T2[res_t20].opp,&T2[res_t20].RDT.day,&T2[res_t20].RDT.month,&T2[res_t20].RDT.year,
        &T2[res_t20].op_run,&T2[res_t20].op_wc,&T2[res_t20].op_over,&T2[res_t20].in_run,&T2[res_t20].in_wc,&T2[res_t20].in_over,T2[res_t20].res);

        res_t20++;
    }
    fclose(fp);
}

/**
Function Name: results_t20_details
Input Params: NILL
Return Type: void
Description: Loads the data into the Doubly Linked list and calls the print function
**/
void results_t20_details()
{
    results_t20_details_load();
    NODE4 head=NULL;
    for(int i=0;i<res_t20;i++)
        head=Insert_end_res_odi_t20(head,T2,i);

    print_result_odi_t20(head);
}

/**
Function Name: getNode_ODI_T20
Input Params: i
Return Type: NODE4
Description: Creates a node for the Doubly linked list of type NODE4
**/
NODE4 getNode_ODI_T20(OT TE[],int i)
{
    NODE4 Newnode=malloc(sizeof(struct ODI_T20));

     if(Newnode==NULL)
    {
        printf("memory not allocated\n");
        exit(0);
    }

    *Newnode=TE[i];

    Newnode->next=NULL;
    Newnode->prev=NULL;

    return Newnode;
}

/**
Function Name: Insert_end_res_odi_t20
Input Params: head,i
Return Type: NODE4
Description: Adds the new node to the end of the doubly linked list of the type NODE4
**/
NODE4 Insert_end_res_odi_t20(NODE4 head,OT TE[],int i)
{
    NODE4 newnode=getNode_ODI_T20(TE,i);

    if(head==NULL)
    {
        head=newnode;
        return head;
    }

    else
    {
        NODE4 cur=head;
        while(cur->next!=NULL)
        {
            cur=cur->next;
        }
        cur->next=newnode;
        newnode->prev=cur;

        return head;
    }
}

/**
Function Name: print_result_odi_t20
Input Params: NILL
Return Type: void
Description: Displays the results of the form ODI and T20I
**/
void print_result_odi_t20(NODE4 head)
{
    if(head==NULL)
    {
        printf("No Results Available\n");
    }
    else
    {
        NODE4 cur=head;
        char ch;
        printf("\nODI Results\n");
        printf("\nSeries Name: %s\n",cur->s_name);
        printf("Date: %d\\%d\\%d\n",cur->RDT.day,cur->RDT.month,cur->RDT.year);
        printf("%s\n",cur->opp);
        printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->op_run,cur->op_wc,cur->op_over);
        printf("INDIA:\n");
        printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->in_run,cur->in_wc,cur->in_over);
        printf("Result: %s\n",cur->res);
        while(1)
        {
            if(cur->prev==NULL && cur->next==NULL )
            {
                printf("\n\nNo more Results are available\n\n");
                break;
            }

            else if(cur->prev==NULL)
            {
                prep: printf("Press \nN for Next Result \n E for Exit\n");
                scanf("%c %c",&ch,&ch);
                if(toupper(ch)!='E'  && toupper(ch)!='N')
                {
                    printf("\nInvalid Choice\n");
                    goto prep;
                }
            }

            else if(cur->next==NULL)
            {
                nerp: printf("Press \nP for Previous Result \n E for Exit\n");
                scanf("%c %c",&ch,&ch);
                if(toupper(ch)!='P' && toupper(ch)!='E')
                {
                    printf("\nInvalid Choice\n");
                    goto nerp;
                }
            }

            else
            {
                    printf("Press \nP for Previous FIXTURE \n N for Next FIXTURE \n E for Exit");
                    scanf("%c %c",&ch,&ch);
            }
            switch(toupper(ch))
            {
                case 'E': printf("\n\nEnd\n\n");
                          return;
                case 'P':
                          cur=cur->prev;
                          printf("\n\nSeries Name: %s\n",cur->s_name);
                          printf("Date: %d\\%d\\%d\n",cur->RDT.day,cur->RDT.month,cur->RDT.year);
                          printf("%s\n",cur->opp);
                          printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->op_run,cur->op_wc,cur->op_over);
                          printf("INDIA:\n");
                          printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->in_run,cur->in_wc,cur->in_over);
                          printf("Result: %s\n",cur->res);
                          break;
                 case 'N':
                           cur=cur->next;
                           printf("\n\nSeries Name: %s\n",cur->s_name);
                           printf("Date: %d\\%d\\%d\n",cur->RDT.day,cur->RDT.month,cur->RDT.year);
                           printf("%s\n",cur->opp);
                           printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->op_run,cur->op_wc,cur->op_over);
                           printf("INDIA:\n");
                           printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->in_run,cur->in_wc,cur->in_over);
                           printf("Result: %s\n",cur->res);
                           break;
                 default:  printf("Invalid choice\n");
            }
        }
    }
}


/**
Function Name: results_test_details_load
Input Params: NILL
Return Type: void
Description: Loads the Test results from file to appropriate data structure
**/
void results_test_details_load()
{
    FILE *fp;
    res_tst=0;
    fp=fopen("RESULTS_TEST.txt","r");

    if(fp==NULL)
    {
        printf("FILE NOT FOUND");
        return;
    }

    while(!feof(fp))
    {
        fscanf(fp,"%s %s %d %d %d %d %d %f %d %d %f %d %d %f %d %d %f %s",TEST_RES[res_tst].s_name,TEST_RES[res_tst].opp,
        &TEST_RES[res_tst].RDT.day,&TEST_RES[res_tst].RDT.month,&TEST_RES[res_tst].RDT.year,
        &TEST_RES[res_tst].op_run1,&TEST_RES[res_tst].op_wc1,&TEST_RES[res_tst].op_over1,
        &TEST_RES[res_tst].op_run2,&TEST_RES[res_tst].op_wc2,&TEST_RES[res_tst].op_over2,
        &TEST_RES[res_tst].in_run1,&TEST_RES[res_tst].in_wc1,&TEST_RES[res_tst].in_over1,
        &TEST_RES[res_tst].in_run2,&TEST_RES[res_tst].in_wc2,&TEST_RES[res_tst].in_over2,
        TEST_RES[res_tst].res);

        res_tst++;
    }
}

/**
Function Name: results_test_details
Input Params: NILL
Return Type: void
Description: Loads the data into the Doubly Linked list and calls the print function
**/
void results_test_details()
{
    results_test_details_load();
    NODE5 head=NULL;
    for(int i=0;i<res_tst;i++)
        head=Insert_end_res_test(head,i);

    print_result_test(head);
}

/**
Function Name: getNode_TEST
Input Params: i
Return Type: NODE5
Description: Creates a node for the Doubly linked list of type NODE5
**/
NODE5 getNode_TEST(int i)
{
    NODE5 Newnode=malloc(sizeof(struct TST));

     if(Newnode==NULL)
    {
        printf("memory not allocated\n");
        exit(0);
    }

    *Newnode=TEST_RES[i];

    Newnode->next=NULL;
    Newnode->prev=NULL;

    return Newnode;
}

/**
Function Name: Insert_end_res_test
Input Params: head,i
Return Type: NODE5
Description: Adds the new node to the end of the doubly linked list of the type NODE5
**/
NODE5 Insert_end_res_test(NODE5 head,int i)
{
    NODE5 newnode=getNode_TEST(i);

    if(head==NULL)
    {
        head=newnode;
        return head;
    }

    else
    {
        NODE5 cur=head;
        while(cur->next!=NULL)
        {
            cur=cur->next;
        }
        cur->next=newnode;
        newnode->prev=cur;

        return head;
    }
}


/**
Function Name: print_result_test
Input Params: NILL
Return Type: void
Description: Displays the results of the form TEST
**/
void print_result_test(NODE5 head)
{
    if(head==NULL)
    {
        printf("No Results Available\n");
    }
    else
    {
        NODE5 cur=head;
        char ch;
        printf("\nTEST Results\n");
        printf("Series Name: %s\n",cur->s_name);
        printf("Date: %d\\%d\\%d\n",cur->RDT.day,cur->RDT.month,cur->RDT.year);
        printf("%s\n",cur->opp);
        printf("First Innings\n");
        printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->op_run1,cur->op_wc1,cur->op_over1);
        printf("Second Innings\n");
        printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->op_run2,cur->op_wc2,cur->op_over2);
        printf("INDIA:\n");
        printf("First Innings\n");
        printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->in_run1,cur->in_wc1,cur->in_over1);
        printf("Second Innings\n");
        printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->in_run2,cur->in_wc2,cur->in_over2);
        printf("Reslut: %s\n",cur->res);

        while(1)
        {
            if(cur->prev==NULL && cur->next==NULL )
            {
                printf("\n\nNo more Results are available\n\n");
                break;
            }

            else if(cur->prev==NULL)
            {
                prep: printf("Press \nN for Next Result \n E for Exit\n");
                scanf("%c %c",&ch,&ch);
                if(toupper(ch)!='E'  && toupper(ch)!='N')
                {
                    printf("\nInvalid Choice\n");
                    goto prep;
                }
            }

            else if(cur->next==NULL)
            {
                nerp: printf("Press \nP for Previous Result \n E for Exit\n");
                scanf("%c %c",&ch,&ch);
                if(toupper(ch)!='P' && toupper(ch)!='E')
                {
                    printf("\nInvalid Choice\n");
                    goto nerp;
                }
            }

            else
            {
                    printf("Press \nP for Previous FIXTURE \n N for Next FIXTURE \n E for Exit");
                    scanf("%c %c",&ch,&ch);
            }
            switch(toupper(ch))
            {
                case 'E': printf("\n\nEnd\n\n");
                          return;
                case 'P':
                          cur=cur->prev;
                          printf("Series Name: %s\n",cur->s_name);
                          printf("Date: %d\\%d\\%d\n",cur->RDT.day,cur->RDT.month,cur->RDT.year);
                          printf("%s\n",cur->opp);
                          printf("First Innings\n");
                          printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->op_run1,cur->op_wc1,cur->op_over1);
                          printf("Second Innings\n");
                          printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->op_run2,cur->op_wc2,cur->op_over2);
                          printf("INDIA:\n");
                          printf("First Innings\n");
                          printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->in_run1,cur->in_wc1,cur->in_over1);
                          printf("Second Innings\n");
                          printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->in_run2,cur->in_wc2,cur->in_over2);
                          printf("Reslut:%s\n",cur->res);
                          break;
                case 'N':
                          cur=cur->next;
                          printf("Series Name: %s\n",cur->s_name);
                          printf("Date: %d\\%d\\%d\n",cur->RDT.day,cur->RDT.month,cur->RDT.year);
                          printf("%s\n",cur->opp);
                          printf("First Innings\n");
                          printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->op_run1,cur->op_wc1,cur->op_over1);
                          printf("Second Innings\n");
                          printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->op_run2,cur->op_wc2,cur->op_over2);
                          printf("INDIA:\n");
                          printf("First Innings\n");
                          printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->in_run1,cur->in_wc1,cur->in_over1);
                          printf("Second Innings\n");
                          printf("Runs: %d Wickets: %d Overs: %0.2f\n",cur->in_run2,cur->in_wc2,cur->in_over2);
                          printf("Reslut: %s\n",cur->res);
                          break;
                 default:printf("Invalid choice\n");
            }
        }
    }
}
