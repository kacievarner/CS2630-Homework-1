//Kacie Varner
//Fall 2020
/*This application replicates the grep function by scanning a text file and printing every line 
that a specified keyword appears on. It also adds new functionality to this by including the flags
-i, -n, and -h. -i can be inserted before the keyword to ignore the case of the keyword in the file
and return all lines containing that string. -n can be inserted before the keyword to return the
line number where each line the keyword is located in is found. -n can also be combined with -i to
ignore the case of the keyword to number the lines of all instances where the keyword is used
regardless of case. -h is the help function, which lets you know that you accessed help, and then 
terminates the program peacefully. Any other flag used besides the ones specified above will cause
the program to terminate in error.
*/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

//Sets the max line length to 100
#define MAX_LINE_LENGTH 100

//These booleans are activated when a specific flag is used
bool iCase = false;
bool printLineNumber = false;
bool flagUsed = false;

//Character arrays for scanning lines at a keyword
char line[MAX_LINE_LENGTH];
char keyword[1000];

//Function definitions before the main loop to avoid implicit declaration
void helperFunction(int argc, char **argv);
char* myupper(char* myStr);

/*Defines main with the arguments as argument counter as an int and argument value as a char array.
Function takes in input from the user and then tests to see if a keyword was used, or if a flag was used
and then activates using booleans. When a flag is used it makes flagUsed true, which then sends the program
to the helper function.
*/
int main(int argc, char **argv)
{
	strcpy(keyword, argv[argc-1]);
	for (int i = 1; i < argc; i++) { //For every char/word in the text
		char *a = argv[i];
		if (strncmp(a, "-", 1) != 0 && flagUsed == false) { //If a flag is not specified, aka just a keyword
			strcpy(keyword, a); //make a copy
			//printf("%s\n", keyword);
			while (fgets(line, MAX_LINE_LENGTH, stdin)) { //scans lines to allow for keyword user input
   				if (strstr(line, keyword) != NULL) { //if there is a keyword in the line
      				printf("%s", line); //print the line containing the keyword
      			}
      		}
      	}
		if (strncmp(a, "-i", 2) == 0) { //activates -i flag
			iCase = true;
			flagUsed = true; //this boolean determines if a flag that is recognized has been activated
		}
		if (strncmp(a, "-n", 2) == 0) { //activates -n flag
			printLineNumber = true;
			flagUsed = true;
		}
		if (strncmp(a, "-h", 2) == 0) { //if -h flag is called
			flagUsed = true;
			printf("Usage: help function\n");
			printf("Example: ./igrep -i -n this <pg25525.txt\n");
			printf("-i: ignore case of keyword in input, can be used with -n\n");
			printf("-n: prints the line number next to every line whether keyword specified or not. Can be used with -i.\n");
			printf("-h: information and command screen, you are here now :)\n");
			printf("Any flag used that does not appear above will result in error.\n");
			exit(0);
		}
		else if (strncmp(a, "-", 1) == 0 && strncmp(a, "-i", 2) != 0 && strncmp(a, "-n", 2) != 0){ //if flag is not recognized
			flagUsed = true;
			printf("Flag unknown\n");
			exit(1);
		}
	}
	if (flagUsed){ //if true move to the helper function
			helperFunction(argc, argv);
	}
}

/* This function exectues the changes the -i, and -n make to the character array. It adds the line numbers
to the output text, and it also lays the roadwork for the -i flag. The function that makes -i work is not
in this function, but is called here to make for ease of reading the code. This function also gives the 
structure to the program to let the -i and -n flags be used at the same time. Takes the same args as the
main function because they are evaluating the same input, but this has a return type void because it is
feeding its output back to main.
*/
void helperFunction(int argc, char **argv)
{
	char lineCount[MAX_LINE_LENGTH]; //new array to keep track of lines
	int lineNumber = 0; //allows the lines to be counted from 1
	while (fgets(line, MAX_LINE_LENGTH, stdin)) { //while there are lines to read from input
		lineNumber++; //increase the line number
		strcpy(lineCount, line); //make a copy of the array
		if (iCase) { //if -i is used
			if (strstr(myupper(lineCount), myupper(keyword)) != NULL){ //if there is a keyword in the line
				if (printLineNumber) { //if -n is also called
					printf("%d:", lineNumber); //print the line number
				}
			printf("%s", line); //print the line with the keyword
			}
		}
		else if (printLineNumber) { //if just -n is called
			if (strstr(lineCount, keyword) != NULL) { //if there is a keyword in the line
				printf("%d:%s", lineNumber, line); //print the line number and the line with the keyword
			}
		}
	}
}

/* This function just converts the character array to uppercase that way the original case can be ignored.
It is the assisting function of the -i flag execution above. It returns a character array that is in all
uppercase.
*/
char* myupper(char* myStr){
	char *c = &myStr[0]; //new character array
	while (*c != '\0') { //while c is not NUL
		*c = toupper(*c); //Convert each letter to uppercase
		c++; //keep parsing through each letter and conver them
	}
	return myStr; //return the new array to be used in evaluating the -i flag
}
