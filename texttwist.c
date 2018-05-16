#include "../../sdk/dexsdk.h"

#define FULL_ROW 320
#define FULL_COL 200

void erase(int x, int y, int w, int h){	//clears screen (reference from lights.c)
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,BLACK);
}

void mainMenu(){
	write_text("TEXT TWIST!",110,50,WHITE,5); //title
	write_text("FOR ICS-OS",110,70,RED,0);

	//menu options
	write_text("1 - Start",120,120,GREEN,3);
	write_text("2 - Quit",120,140,GREEN,3);
}

void printBlank(char blanks[8][15], int x, int y){
	erase(100,0,0,FULL_COL);
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
		//if(i )

		write_text(blanks[i],tempX,tempY,WHITE,0);
		if(i == 11 || i == 23){
			tempY = y;
			tempX += 50;
		}
		else{
			tempY+=13;
			//tempX=tempX;
		}
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
	erase(220,50,150,20);
	write_text(shuffled,220,50,WHITE,0);
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
				erase(270,160,300,25);
				char pts[10];
		   		sprintf(pts,"%d",*points);
				write_text(pts,280,160,WHITE,3);
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
	erase(0,0,FULL_ROW,FULL_COL);
	do{
		write_text(shuffled,220,50,WHITE,0);
		write_text("Entered: ",150,70,WHITE,0);
		printBlank(blanks,10,30);
		write_text("Points: ",210,160,WHITE,0);
		char pts[10];
   		sprintf(pts,"%d",*points);
		write_text(pts,280,160,WHITE,3);
		write_text("0 - Submit word",150,95,WHITE,0);
		write_text("1 - Shuffle",150,110,WHITE,0);
		write_text("2 - Exit/Clear",150,125,WHITE,0);
		if(guessedLongest == 1){
			write_text("3 - Next Round",150,140,GREEN,0);
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
			int x=220;
			gameInput[i]=keypress;
			write_char(keypress,x,70,WHITE,3);
			do{
				i++;
				if(i >= 7){
					i = 7;
					gameInput[i]=(char)getch();
					if(gameInput[i] == '2'){
						break;
					}
				}
				else{
				gameInput[i]=(char)getch();
				x+=8;
				if(gameInput[i]!='0'){
					if(gameInput[i] == '2'){
						break;
					}
					else{
						write_char(gameInput[i],x,70,WHITE,3);
					}
				}
				}
			}while(gameInput[i]!='0');
			if(gameInput[i] == '2'){}
			else{
			gameInput[i]='\0';
			guessed+=checkInput(words, blanks, gameInput, points);
			if(strcmp(gameInput, words[toGuess-1]) == 0){
				//write_text("You found the longest word. Would you like to proceed to the next round? 5-YES 6-NO",5,210,WHITE,0);
				// keypress=(char)getch();
				// if(keypress=='5'){
				// 	break;
				// }
				guessedLongest = 1;
			}
			}
			erase(0,0,320,200);
		}
	}while(toGuess!=guessed);
	return 0;

}

int main(){
	set_graphics(VGA_320X200X256);
	char menuChoice;
	do{
		erase(0,0,FULL_ROW,FULL_COL);
		int i;
		mainMenu();
		menuChoice=(char)getch();
		if(menuChoice=='1'){	//start playing the game
			int points=0;
			int exitRound=0;	//will be 1 if player exits round
			char shuffled[10][8]={"sbsra", "linvy", "htroo", "smade", "pleope", "celefed", "weltat", "dsaydr", "ctakde", "wdalde"};
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
				{"law", "dew", "wed", "awe", "add", "dad", "lad", "led", "ale", "lea", "lewd", "weld", "awed", "wade", "weal", "dead", "dale", "deal", "lade", "lead", "weald", "addle", "dawdle","waddle"}};
			char blanks[10][30][15]={

				{"___", "___", "___", "___", "____", "____", "____", "_____"},
				{"___", "___", "___", "___", "____", "____", "____", "_____"},
				{"___", "___", "___", "___", "___", "___", "____", "____", "____", "____", "____", "_____"},
				{"___", "___", "___", "___", "___", "___","____", "____", "____", "____", "____", "____", "____", "_____"},
				{"___", "___", "___", "___", "___", "___", "___", "___", "___", "____", "____", "____", "____", "____", "____", "_____", "______"},
				{"___", "___", "___", "___", "___", "___", "___", "____", "____", "____", "____", "____", "______", "_______"},
				{"___", "___", "___", "___", "___", "___", "___", "___", "___", "___", "___", "____", "____", "____", "____", "____", "____", "____", "______"},
				{"___", "___", "___", "___", "___", "___", "___", "___", "___", "____", "____", "____", "____", "____", "____", "______", "______", "______", "______"},
				{"___", "___", "___", "___", "___", "___", "___", "___", "___", "___", "____", "____", "____", "____", "____", "____", "____", "_____", "_____", "_____", "______"},
				{"___", "___", "___", "___", "___", "___", "___", "___", "___", "___", "____", "____", "____", "____", "____", "____", "____", "____", "____", "____", "_____", "_____", "______", "______"}};

			for(i=0; i<10; i++){
				exitRound=playGame(words[i], blanks[i], shuffled[i], &points);
				if(exitRound==1){
					break;
				}
			}

			if(i==10){
				erase(0,0,FULL_ROW,FULL_COL);
			}

		}else if(menuChoice!='2'){
			printf("Invalid choice.\n");
		}else{	//exit game
			printf("Thank you for playing.\n");
		}
	}while(menuChoice!='2');
}