#include "../../sdk/dexsdk.h"

void erase(int x, int y, int w, int h){	//clears screen (reference from lights.c)
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,100);
}

void mainMenu(){
	write_text("TEXT TWIST!",270,150,WHITE,5); //title

	//menu options
	write_text("1 - Start",270,300,WHITE,3);
	write_text("2 - Quit",270,340,WHITE,3);
}

void printBlank(char blanks[8][15], int x, int y){
	erase(100,0,100,480);
	int tempX=x;
	int tempY=y;

	for(int i=0; i<30; i++){
		if(strcmp(blanks[i], "")==0){
			break;
		}
		// for(int j=0; j<strlen(blanks[i]); j++){
		// 	fill_rect(tempX, tempY, 10, 10, WHITE);
		// 	tempX+=13;
		// }
		write_text(blanks[i],tempX,tempY,WHITE,0);
		tempY+=13;
		tempX=x;
	}
}

void shuffle(char shuffled[7]){
int len=0;
	for(int i=0; i<strlen(shuffled); i++){
		if(shuffled[i]==""){
			break;
		}
		len++;
	}

	int checker[len];
	char temp[len];
	int random;

	for(int i=0; i<len; i++){
		checker[i]=0;
	}

	for(int i=0; i<len; i++){
		do{
			random=rand()%len;
			if(checker[random]==0){
				temp[random]=shuffled[i];
				checker[random]=1;
				break;
			}
		}while(1);
	}
	temp[len]='\0';
	strcpy(shuffled, temp);
	erase(200,30,300,50);
	write_text(shuffled,200,30,WHITE,3);
}

int checkInput(char round1Words[30][7], char round1Blank[30][15], char gameInput[7], int *points){
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
	char keypress;
	char gameInput[7]="";
	int toGuess=0;
	int guessed=0;
	int guessedLongest=0;
	
	for(int i=0; i<30; i++){
		if(strcmp(words[i], "")==0){
			break;
		}
		toGuess++;
	}
	erase(0,0,640,480);
	do{
		write_text(shuffled,380,120,WHITE,3);
		write_text("Entered: ",330,150,WHITE,3);
		printBlank(blanks,130,80);
		write_text("Points: ",380,180,WHITE,3);
		write_text((char)*points,450,180,WHITE,3);
		if(guessedLongest == 0){
			write_text("0 - Enter word",330,300,WHITE,3);
			write_text("1 - Shuffle",340,340,WHITE,3);
			write_text("2 - Exit",350,380,WHITE,3);
		} else {
			write_text("3 - Next Round",300,400,WHITE,0);
		}

		keypress=(char)getch();
		if(keypress=='1'){	//SHUFFLE
			shuffle(shuffled);
		}else if(keypress=='2'){	//EXIT
			return 1;
		}else if(keypress=='3' && guessedLongest){	//proceed to next round
			break;
		}else{
			int i=0;
			gameInput[i]=keypress;
			do{
				i++;
				gameInput[i]=(char)getch();
			}while(gameInput[i]!='0');
			gameInput[i]='\0';
			guessed+=checkInput(words, blanks, gameInput, points);
			// if(strcmp(gameInput, words[toGuess-1]) == 0){
			// 	write_text("You found the longest word. Would you like to proceed to the next round? 5-YES 6-NO",5,210,WHITE,0);
			// 	keypress=(char)getch();
			// 	if(keypress=='5'){
			// 		break;
			// 	}
			// 	guessedLongest = 1;
			// }
		}
	}while(toGuess!=guessed);
	return 0;

}

int main(){
	set_graphics(VGA_640X480X16);
	char menuChoice;
	do{
		erase(0,0,640,480);
		int i;
		mainMenu();
		menuChoice=(char)getch();
		if(menuChoice=='1'){	//start playing the game
			int points=0;
			int exitRound=0;	//will be 1 if player exits round
			char shuffled[10][7]={"sbsra", "linvy", "htroo", "smade", "pleope", "celefed", "weltat", "dsaydr", "ctakde", "wdalde"};
			char words[10][30][7]={
				{"bar", "bra", "ass", "abs", "bass", "bars", "bras", "brass"},
				{"ivy", "yin", "lin", "nil", "viny", "inly", "liny", "vinyl"},
				{"tor", "rot", "hot", "too", "rho", "tho", "root", "hoot", "roto", "toro", "thro", "ortho"},
				{"mad", "sea", "sad", "med", "dam", "ads", "made", "seam", "same", "dams", "dame", "mads", "mead", "dames"},
				{"eel", "lee", "ope", "ole", "pol", "pee", "lop", "pep", "pop", "pepo", "peel", "peep", "plop", "pole", "pope", "elope", "people"},
				{"cel", "eel", "elf", "led", "lee", "fed", "fee", "cede", "clef", "feed", "feel", "fled", "fleece", "fleeced"},
				{"eat", "let", "lea", "law", "tea", "tat", "ale", "ate", "awe", "awl", "wet", "late", "teal", "teat", "tale", "welt", "weal", "watt", "wattle"},
				{"say", "sad", "ads", "add", "yar", "ray", "dad", "day", "dry", "adds", "yard", "rays", "dads", "days", "dray", "yards", "drays", "dryad", "dryads"},
				{"eat", "cad", "cat", "ade", "ace", "act", "ate", "ted", "tea", "tad", "deck", "date", "cake", "aced", "teak", "take", "tack", "cadet", "caked", "acted", "tacked"},
				{"wad", "law", "dew", "wed", "awe", "add", "dad", "lad", "led", "ale", "lea", "lewd", "weld", "awed", "wade", "weal", "dead", "dale", "deal", "lade", "lead", "weald", "addle", "dawdle"}};
			char blanks[10][30][15]={

				{"___", "___", "___", "___", "____", "____", "____", "_____"},
				{"___", "___", "___", "___", "____", "____", "____", "_____"},
				{"___", "___", "___", "___", "___", "___", "____", "____", "____", "____", "____", "_____"},
				{"___", "___", "___", "___", "___", "___","____", "____", "____", "____", "____", "____", "____", "_____"},
				{"___", "___", "___", "___", "___", "___", "___", "___", "___", "____", "____", "____", "____", "____", "____", "_____", "______"},
				{"___", "___", "___", "___", "___", "___", "___", "____", "____", "____", "____", "____", "_____", "______"},
				{"___", "___", "___", "___", "___", "___", "___", "___", "___", "___", "___", "____", "____", "____", "____", "____", "____", "____", "______"},
				{"___", "___", "___", "___", "___", "___", "___", "___", "___", "____", "____", "____", "____", "____", "____", "______", "______", "______", "_______"},
				{"___", "___", "___", "___", "___", "___", "___", "___", "___", "___", "____", "____", "____", "____", "____", "____", "____", "_____", "_____", "_____", "______"},
				{"___", "___", "___", "___", "___", "___", "___", "___", "___", "___", "___", "____", "____", "____", "____", "____", "____", "____", "____", "____", "____", "_____", "_____", "_____", "______"}};

			for(i=0; i<10; i++){
				exitRound=playGame(words[i], blanks[i], shuffled[i], &points);
				if(exitRound==1){
					break;
				}
			}

			if(i==10){
				erase(0,0,640,480);
			}

		}else if(menuChoice!='2'){
			printf("Invalid choice.\n");
		}else{	//exit game
			printf("Thank you for playing.\n");
		}
	}while(menuChoice!='2');
}