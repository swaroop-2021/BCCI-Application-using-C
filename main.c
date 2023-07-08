#include <stdio.h>
#include <stdlib.h>
#include "func_declarations.c"
#include "double_linked_list.c"
#include "poll.c"
#include "functions.c"
int main()
{
    welcome();

    printf("Welcome to the official site for BCCI\n");
    printf("What are you looking for??\n");

    load_from_file();

    char nm[50];
    //char pd;
    while(1)
    {
        printf("\n\nSelect the options from below\n");
        int choice;
        printf("1- Player Details\n");
        printf("2- News Headlines\n");
        printf("3- News sort by date\n");
        printf("4- Details of Players by Role\n");
        printf("5- Upcoming Fixtures\n");
        printf("6- Details of Fixtures by type of the match\n");
        printf("7- Details of Fixtures by month range\n");
        printf("8- Fixtures Search by name\n");
        printf("9- Player Search by name\n");
        printf("10- Player Details in sorted format by name\n");
        printf("11- Details of Stadiums\n");
        printf("12- Details of Players according to debut from latest to least\n");
        printf("13- Details of Players according to date of birth\n");
        printf("14- Details of Players according to age\n");
        printf("15- Polls\n");
        printf("16- Details of Results\n");
        printf("17- Details of Results by date range\n");
        printf("18- IPL\n");
        printf("19- Gallery of BCCI\n");
        printf("20- Store of BCCI\n");
        printf("21- Latest Videos of BCCI\n");
        printf("22- Follow us on Facebook\n");
        printf("23- Follow us on Instagram\n");
        printf("24- Follow us on Twitter\n");
        printf("99- Exit\n");

        scanf("%d",&choice);
        switch(choice)
        {
            case 1: print_details();
                    break;
            case 2: news();
                    break;
            case 3: news_sort_by_date();
                    break;
            case 4: players_display_by_role();
                    break;
            case 5: fixture();
                    break;
            case 6: FIX_DISPLAY_BY_TYPE_OF_MATCH();
                    break;
            case 7: fix_display_by_month_range();
                    break;
            case 8: printf("Enter the String which has to be matched with the Fixture Name\n");
                    scanf("%s",nm);
                    rabin_sub_string_fixture(nm);
                    break;
            case 9:  printf("Enter the STRING\n");
                     scanf("%s",nm);
                     brute_force_search(nm);
                     break;
            case 10: sort_by_name();
                     break;
            case 11: venue_details();
                     break;
            case 12: players_sort_by_debut_date();
                     break;
            case 13: players_sort_by_dob();
                     break;
            case 14: players_sort_by_age();
                     break;
            case 15: poll();
                     break;
            case 16: results();
                     break;
            case 17: results_date_range();
                     break;
            case 18: Ipl();
                     break;
            case 19: Gallery();
                     break;
            case 20: Store();
                     break;
            case 21: videos();
                     break;
            case 22: Facebook();
                     break;
            case 23: Instagram();
                     break;
            case 24: Twitter();
                     break;
            case 99: printf("\nThanks for Visting BCCI\n");
                     exit(1);
                     break;
            default: printf("Invalid Choice\n");
        }
    }
    return 0;
}
