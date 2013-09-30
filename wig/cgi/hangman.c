#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
	//the list of words to choose from
	char* words[5] = {"cats", "love", "cute", "what", "home"};

	//retrieve the info sent via post
	char string[200];
	int length = atoi(getenv("CONTENT_LENGTH"));
	fgets(string, length+1, stdin);
	int i;
	//replaces all the &'s with spaces
	for(i = 0; i < length; i++){
		if(string[i] == '&'){
			string[i] = ' ';
		}
	}
	
	int option; //the index of the word chosen
	int position; //the position of the letter being guessed
	char letter; //the letter being guessed
	char correct[4]; //correct letters guessed so far
	
	int triesLeft; 
	
	//first time this is called save the option to the session1.txt file
	//then print the "guess" html
	if(sscanf(string, "option=%d", &option) != 0){
		triesLeft = 5;
	
		FILE* session = fopen("session.csv", "wt");
		//format of file is (option),(triesLeft),(correct letters or '_' if letter has not been guessed yet)
		fprintf(session, "%d,%d,____", option, triesLeft);
		fclose(session);
		
		printf("Content-type: text/html\n\n");
		printf("<html><body>Start by making a guess.<br />\n");
		printf("You have %d tries left<br />\n", triesLeft);
		printf("Guess a letter in ____.<br />\n");
		printf("<form action=\"http://www.cs.mcgill.ca/~vkovec/hangman.cgi\" method=\"post\">\n");
		printf("Position (1-4): <input name=\"position\" type=\"text\" size=\"1\">\n");
		printf("<br />Letter: <input name=\"letter\" type=\"text\" size=\"1\">\n");
		printf("<br /><input type=\"submit\" value=\"go\"/></form>");
		printf("</body></html>");
	}
		
	else{
		sscanf(string, "position=%d letter=%c", &position, &letter);
		
		char line[50];
		
		//open the session.csv file
		FILE* session = fopen("session.csv", "r+wt");
		fgets(line, 49, session);
		
		//restore the session
		sscanf(line, "%d,%d,%c%c%c%c", &option, &triesLeft, &correct[0], &correct[1], &correct[2], &correct[3]);
		
		//if there are still tries left and not all letters have been guessed correctly
		//then check if the current guess is correct
		if(triesLeft > 0 && (correct[0] == '_' || correct[1] == '_' || correct[2] == '_' || correct[3] == '_')){
			
			//overwrite the session1.txt file
			fseek(session, 0, SEEK_SET);
			
			if(words[option-1][position-1] == letter){
				//the guess is correct
				correct[position-1] = letter;
				fprintf(session, "%d,%d,%c%c%c%c", option, triesLeft, correct[0], correct[1], correct[2], correct[3]);
				fclose(session);
				
				//if all the letters have been guessed correctly
				if(correct[0] != '_' && correct[1] != '_' && correct[2] != '_' && correct[3] != '_'){
					printf("Content-type: text/html\n\n");
					printf("<html><body>Congratulations. The word was %s. You win.</body></html>", words[option-1]);
				}
				else{	
					printf("Content-type: text/html\n\n");
					printf("<html><body>Start by making a guess.<br />\n");
					printf("You have %d tries left<br />\n", triesLeft);
					printf("Guess a letter in %c%c%c%c.<br />\n", correct[0], correct[1], correct[2], correct[3]);
					printf("<form action=\"http://www.cs.mcgill.ca/~vkovec/hangman.cgi\" method=\"post\">\n");
					printf("Position (1-4): <input name=\"position\" type=\"text\" size=\"1\">\n");
					printf("<br />Letter: <input name=\"letter\" type=\"text\" size=\"1\">\n");
					printf("<br /><input type=\"submit\" value=\"go\"/></form>");
					printf("</body></html>");
				}				
			}
			else{
				//try again with less tries
				triesLeft--;
				fprintf(session, "%d,%d,%c%c%c%c", option, triesLeft, correct[0], correct[1], correct[2], correct[3]);
				fclose(session);
				
				printf("Content-type: text/html\n\n");
				printf("<html><body>Start by making a guess.<br />\n");
				printf("You have %d tries left<br />\n", triesLeft);
				printf("Guess a letter in %c%c%c%c.<br />\n", correct[0], correct[1], correct[2], correct[3]);
				printf("<form action=\"http://www.cs.mcgill.ca/~vkovec/hangman.cgi\" method=\"post\">\n");
				printf("Position (1-4): <input name=\"position\" type=\"text\" size=\"1\">\n");
				printf("<br />Letter: <input name=\"letter\" type=\"text\" size=\"1\">\n");
				printf("<br /><input type=\"submit\" value=\"go\"/></form>");
				printf("</body></html>");				
			}
		}
	
		//lose if not more tries are left and word has not been guessed
		else if(triesLeft == 0){
			printf("Content-type: text/html\n\n");
			printf("<html> <body>You have failed. Game over.</body></html>");
		}

	}
	
	return 1;
}
