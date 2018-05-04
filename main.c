#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void mainMenu(){
	printf("-----------------------------------------------------------------------------\n");
	printf("TEXT TWIST\n");
	printf("[1] Start Game\n");
	printf("[2] Exit\n");
	printf("Your choice: ");
}

void printBlank(char blanks[8][15]){
	printf("-----------------------------------------------------------------------------\n");
	for(int i=0; i<30; i++){
		if(strcmp(blanks[i], "")==0){
			break;
		}
		printf("%s\n", blanks[i]);
	}
	printf("-----------------------------------------------------------------------------\n");
}

void shuffle(char shuffled[7]){
	int checker[strlen(shuffled)];
	char temp[7];
	int random;

	for(int i=0; i<strlen(shuffled); i++){
		checker[i]=0;
	}

	for(int i=0; i<strlen(shuffled); i++){
		do{
			random=rand()%strlen(shuffled);
			if(checker[random]==0){
				temp[random]=shuffled[i];
				checker[random]=1;
				break;
			}
		}while(1);
	}
	strcpy(shuffled, temp);
}

int checkInput(char round1Words[30][7], char round1Blank[30][15], char gameInput[7], int *points){
	for(int i=0; i<8; i++){
		gameInput[i]=tolower(gameInput[i]);
	}
	for(int i=0; i<30; i++){
		if(strcmp(gameInput, round1Words[i])==0){	//meaning they match
			int check=0;
			for(int j=0; j<30; j++){
				if(strcmp(gameInput, round1Blank[j])==0){	//check if already inputted
					check++;
					break;
				}
			}
			if(check==0){
				strcpy(round1Blank[i], round1Words[i]);
				//updating points
				if(strlen(round1Words[i])==3){
					*points+=5;
				}else if(strlen(round1Words[i])==4){
					*points+=10;
				}else if(strlen(round1Words[i])==5){
					*points+=20;
				}else{
					*points+=30;
				}
				return 1;
			}else{
				printf("Word already found!\n");
			}
		}
	}
	return 0;
}

int playGame(char words[30][7], char blanks[30][15], char shuffled[7], int *points){
	char gameInput[10];
	int toGuess=0;
	int guessed=0;
	int guessedLongest=0;
	
	for(int i=0; i<30; i++){
		if(strcmp(words[i], "")==0){
			break;
		}
		toGuess++;
	}

	do{
		printf("-----------------------------------------------------------------------------\n");
		printf("Shuffled word: %s\n", shuffled);
		printBlank(blanks);
		printf("Points: %d\n", *points);
		if(guessedLongest == 0){
			printf("Enter your guess below:\n(Type 'EXIT' to quit game, and 'SHUFFLE' to shuffle the words)\n>");
		} else {
			printf("Enter your guess below:\n(Type 'EXIT' to quit game, 'SHUFFLE' to shuffle the words, \n");
			printf("'YES' to proceed to next round)\n>");
		}
		scanf("%s", gameInput);
		if(strcmp(gameInput, "YES") == 0 && guessedLongest){
			break;
		}else if(strcmp(gameInput, "SHUFFLE") == 0){
			shuffle(shuffled);
		}else if(strcmp(gameInput, "EXIT") == 0){
			return 1;
		}else{
			guessed+=checkInput(words, blanks, gameInput, points);
			if(strcmp(gameInput, words[toGuess-1]) == 0){
				printf("Congratulations! You found the longest word.\nWould you like to proceed to the next round? YES or NO\n");
				scanf("%s", gameInput);
				if(strcmp(gameInput, "YES") == 0){
					break;
				}
				guessedLongest = 1;
			}
		}
		printf("\n");
	}while(toGuess!=guessed);
	return 0;

}

int main(){
	int menuChoice;

	do{
		int i;
		mainMenu();
		scanf("%d", &menuChoice);
		if(menuChoice==1){	//start playing the game
			int points=0;
			int exitRound=0;	//will be 1 if player exits round
			char shuffled[10][7]={"sbsra", "htroo", "smade", "celefed", "weltat", "dsaydr", "ctakde"};
			char words[10][30][7]={
				{"bar", "bra", "ass", "abs", "bass", "bars", "bras", "brass"},
				{"tor", "rot", "hot", "too", "rho", "tho", "root", "hoot", "roto", "toro", "thro", "ortho"},
				{"mad", "sea", "sad", "med", "dam", "ads", "made", "seam", "same", "dams", "dame", "mads", "mead", "dames"},
				{"cel", "eel", "elf", "led", "lee", "fed", "fee", "cede", "clef", "feed", "feel", "fled", "fleece", "fleeced"},
				{"eat", "let", "lea", "law", "tea", "tat", "ale", "ate", "awe", "awl", "wet", "late", "teal", "teat", "tale", "welt", "weal", "watt", "wattle"},
				{"say", "sad", "ads", "add", "yar", "ray", "dad", "day", "dry", "adds", "yard", "rays", "dads", "days", "dray", "yards", "drays", "dryad", "dryads"},
				{"eat", "cad", "cat", "ade", "ace", "act", "ate", "ted", "tea", "tad", "deck", "date", "cake", "aced", "teak", "take", "tack", "cadet", "caked", "acted", "tacked"}};
			char blanks[10][30][15]={
				{"_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _ _"},
				{"_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _ _"},
				{"_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _","_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _ _"},
				{"_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _ _", "_ _ _ _ _ _"},
				{"_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _ _ _"},
				{"_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _ _ _", "_ _ _ _ _ _", "_ _ _ _ _ _", "_ _ _ _ _ _ _"},
				{"_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _", "_ _ _ _ _", "_ _ _ _ _", "_ _ _ _ _", "_ _ _ _ _ _"}};

			for(i=0; i<2; i++){
				exitRound=playGame(words[i], blanks[i], shuffled[i], &points);
				if(exitRound==1){
					break;
				}
			}

			if(i==2){
				printf("Congratulations! You finished all the rounds.\n");
			}

		}else if(menuChoice!=2){
			printf("Invalid choice.\n");
		}else{	//exit game
			printf("Thank you for playing.\n");
		}
	}while(menuChoice!=2);
}