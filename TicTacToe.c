/*
Simple Tic-Tac-Toe Game in C
Written by Matthew D'Arcy
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<stdbool.h>

#define name_limit 64
#define TRUE 1
#define FALSE 0

struct playerdata	
{
	char P[64];
	char marker;	
};	

struct playerdata player1;
struct playerdata player2;
int total_choices[9] = {0,0,0,0,0,0,0,0,0};
char chararray[3][3] = { {'1','2','3'} , {'4','5','6'} , {'7','8','9'} };
int straight = 0, goplayer = 0, p1 = 0, p2 = 0, p3 = 0;
int gameover = FALSE;
int last, row, col;
int isdraw = 0;
char replay;
char null;
int play = TRUE;

/* Display tic-tac-toe board to user */
void show_board()
{	
	printf("\n %c | %c | %c\n",chararray[0][0],chararray[0][1],chararray[0][2]);
	printf("---+---+---\n");
	printf(" %c | %c | %c\n",chararray[1][0],chararray[1][1],chararray[1][2]);
	printf("---+---+---\n");
	printf(" %c | %c | %c\n\n",chararray[2][0],chararray[2][1],chararray[2][2]);
}

/* Upon game-end condition, ask to play again, if so reinitialize, otherwise quit */
void endgame()
{
	show_board();	
	gameover = TRUE;	
	if(goplayer == 1 && isdraw == 0)
	{
		printf("Game Over!\nThe winner is %s",player2.P);
	}
	else if (goplayer == 2 && isdraw == 0)
	{
		printf("Game Over!\nThe winner is %s",player1.P);
	}
	else
	{
		printf("The game is a draw!\n\r");
	}
	sleep(2);
	printf("Play again? (y for yes, anything else to end)\n\r");
	scanf("%c",&replay);
	while(getc(stdin) != '\n');
	if(replay == 'y' || replay == 'Y')
	{		
		chararray[0][0] = '1';
		chararray[0][1] = '2';
		chararray[0][2] = '3';
		chararray[1][0] = '4';
		chararray[1][1] = '5';
		chararray[1][2] = '6';
		chararray[2][0] = '7';
		chararray[2][1] = '8';
		chararray[2][2] = '9';
		memset(total_choices,0,sizeof(total_choices));
		straight = 0, goplayer = 0, p1 = 0, p2 = 0, p3 = 0;
		isdraw = 0;	
	}
	else
	{		
		printf("\nGoodbye!\n\n\r");		
		exit(0);
	}
}

/* Check for player win cases */
void gamecheck()
{	
	total_choices[p3] = last;
	p3++;
	if ((chararray[0][0] == chararray[1][1] && chararray[1][1] == chararray[2][2]) || (chararray[0][2] == chararray[1][1] && chararray[1][1] == chararray[2][0])) 
	{
		endgame();
	}
	else
	{	
		for(straight = 0; straight <=2; straight++)
		{
			if((chararray[straight][0] == chararray[straight][1] && chararray[straight][1] == chararray[straight][2]) || (chararray[0][straight] == chararray[1][straight] && chararray[1][straight] == chararray[2][straight]))
			{
				endgame();
			}
		}
		if (p3 > 8)
		{
			printf("p3 is %d",p3);
			isdraw = 1;
			endgame();
		}	
	}	
}

/* Randomly choose players' order and markers */
void first()
{
	sleep(1);
	printf("Randomizing...\n\n\r");	
	sleep(2);
	srand(time(NULL));
	int first = (rand()%4);	
	switch(first)
	{
		case 0:
			printf("Turn: %sYour symbol is X\n\n\r",player1.P);
			player1.marker = 'X';
			player2.marker = 'O';
			goplayer = 1;
			break;
		case 1:
			printf("Turn: %sYour symbol is O\n\n\r",player1.P);
			player1.marker = 'O';
			player2.marker = 'X';			
			goplayer = 1;
			break;
		case 2:
			printf("Turn: %sYour symbol is X\n\n\r",player2.P);
			player2.marker = 'X';	
			player1.marker = 'O';		
			goplayer = 2;
			break;
		case 3:
			printf("Turn: %sYour symbol is O\n\n\r",player2.P);
			player2.marker = 'O';	
			player1.marker = 'X';		
			goplayer = 2;
			break;
	}
	sleep(1);
}

int clean_user_input()
{
	while(getchar() != '\n');
	return(1);
}

/* Get user input for space selection and check validity */
void choose_space()
{	
	do
	{
		printf("(single digit 1 through 9): ");
	} while ((((scanf("%d%c", &last, &null) != 2) || null != '\n') && clean_user_input()) || last < 1 || last > 9);
	
	int j;	
	for(j=0;j<9;j++)
	{
		if(total_choices[j]==last)
		{
			printf("Space already chosen!\nPlease choose again: ");
			choose_space();
		}
	}	
	row = (last-1)/3;
	col = (last-1)%3;	
}

/* Place X or O where user has selected */
void place()
{
	switch(goplayer)
	{
		case 1:
			printf("Enter the number of your field of choice, %s", player1.P);
			choose_space();
			chararray[row][col] = player1.marker;		
			goplayer = 2;
			p1++;
			gamecheck();			
			break;
		case 2:
			printf("Enter the number of your field of choice, %s", player2.P);	
			choose_space();
			chararray[row][col] = player2.marker;
			goplayer = 1;
			p2++;
			gamecheck();
			break;
	}		
	if(gameover == FALSE)
	{	
		show_board();
	}
}

/* Main routine */
int main()
	{
		while(play == TRUE)
		{	
			gameover = FALSE;
			printf("\n\nWelcome to Tic-Tac-Toe!\n\n\n");
			printf("Please submit name of player 1: ");							
			fgets(player1.P,name_limit,stdin);	
			printf("Welcome %s\n", player1.P);
			printf("Please submit name of player 2: ");		
			fgets(player2.P,name_limit,stdin);
			printf("Welcome %s\n", player2.P);
			first();	
			show_board();
			while(gameover == FALSE)
			{
				place();
			}			
		}
		return(0);	
	}
