/*To-do:
	1. Implement 10 rounds
	2. Shuffle
	3. Timer
	4. Close words
	5. UI
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void mainMenu(){
	printf("TEXT TWIST\n");
	printf("[1] Start Game\n");
	printf("[2] Exit\n");
}

void printBlank(char round1Blank[8][10]){
	for(int i=0; i<8; i++){
		printf("%s\n", round1Blank[i]);
	}
}

int checkInput(char round1Words[8][6], char round1Blank[8][10], char gameInput[7], int points){
	for(int i=0; i<8; i++){
		gameInput[i]=tolower(gameInput[i]);
	}
	for(int i=0; i<8; i++){
		if(strcmp(gameInput, round1Words[i])==0){	//meaning they match
			int check=0;
			for(int j=0; j<8; j++){
				if(strcmp(gameInput, round1Blank[j])==0){	//check if already inputted
					check++;
					break;
				}
			}
			if(check==0){
				strcpy(round1Blank[i], round1Words[i]);
				//updating points
				if(strlen(round1Words[i])==3){
					points=points+5;
				}else if(strlen(round1Words[i])==4){
					points=points+10;
				}else if(strlen(round1Words[i])==5){
					points=points+20;
				}else{
					points=points+30;
				}
			}else{
				printf("Word already found!\n");
			}
		}
	}
	return points;
}

//NOT YET WORKING
void shuffle(char *shuffled){
// 	int checker[strlen(shuffled)-1];
// 	for(int i=0; i<strlen(shuffled)-1; i++){
// 		checker[i]=0;
// 	}
// 	int random, done;
// 	char temp[strlen(shuffled)];
// 	strcpy(temp,shuffled);
// 	for(int i=0; i<strlen(shuffled); i++){
// 		do{
// 			done=0;
// 			random=rand()%(strlen(shuffled)-1);
// 			if(checker[random]==0){
// 				printf("%d\n", random);
// 				checker[random]=1;
// 				temp[random]=shuffled[i];
// 				done=1;
// 				printf("%s\n", temp);
// 			}
// 		}while(done==0);
// 	}
// 	strcpy(shuffled, temp);
}

int main(){
	int choice; 
	mainMenu();
	scanf("%d", &choice);
	if(choice==1){	//Start Game
		int points=0;
		char gameInput[10];
		char shuffled[6]="sbrsa";
		char round1Words[8][6]={"bar", "bra", "ass", "abs", "bass", "bars", "bras", "brass"};
		char round1Blank[8][10]={"_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _ _"};

		do{
			printf("ROUND 1:\n");
			printBlank(round1Blank);
			printf("Points: %d\n", points);
			printf("Shuffled word: %s\n", shuffled);
			printf("Enter your guess below (Type 'EXIT' to quit game, and 'SHUFFLE' to shuffle the words):\n>");
			scanf("%s", gameInput);
			if(strcmp(gameInput, "SHUFFLE") == 0){
				shuffle(shuffled);
			}
			points=checkInput(round1Words, round1Blank, gameInput, points);
			printf("\n");
		}while(strcmp(gameInput, "EXIT") != 0);

	}else{	//Exit
		printf("Thank you for playing!\n");
	}
}