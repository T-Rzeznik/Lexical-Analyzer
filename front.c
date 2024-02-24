/* front.c - alixical analyzer system for simple
			 arithemetic expression */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define FOR_CODE 30

#define EQUALS_OP 31    //STEP 2: added Tokens
#define LESS_THAN_OP 32
#define SEMICOLON 33
#define LEFT_BRACE 34
#define RIGHT_BRACE 35


/*************************************/
/* main driver */
int main(){
	char filename[100]; // Buffer for filename                    //STEP 3: read file name at run time
    printf("Enter the filename: ");
    scanf("%s", filename); // Read filename from keyboard
    if ((in_fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "ERROR - cannot open %s\n", filename);
	}
	else{
		getChar();
		do{
			lex();
		} while(nextToken != EOF);
	}
	return 0;
}

int lookup(char ch) {
	switch(ch) {
		case '(':
			addChar();
			nextToken = LEFT_PAREN;
			break;
		case ')':
			addChar();
			nextToken = RIGHT_PAREN;
			break;
		case '+':
			addChar();
			nextToken = ADD_OP;
			break;
		case '-':
			addChar();
			nextToken = SUB_OP;
			break;
		case '*':
			addChar();
			nextToken = MULT_OP;
			break;
		case '/':
			addChar();
			nextToken = DIV_OP;
			break;
		case '=':                    //STEP 2: added cases for new tokens
            addChar();
            nextToken = EQUALS_OP;
            break;
        case '<':
            addChar();
            nextToken = LESS_THAN_OP;
            break;
        case ';':
            addChar();
            nextToken = SEMICOLON;
            break;
        case '{':
            addChar();
            nextToken = LEFT_BRACE;
            break;
        case '}':
            addChar();
            nextToken = RIGHT_BRACE;
            break;
		default:
			addChar();
			nextToken = EOF;
			break;
	}
	return nextToken;
}

void addChar(){
	if(lexLen <= 98){
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else
		printf("Error - lexeme is too long \n");
}

void getChar() {

	if((nextChar = getc(in_fp)) != EOF){

		if(isalpha(nextChar))
			charClass = LETTER;
		else if(isdigit(nextChar))
			charClass = DIGIT;
		else charClass = UNKNOWN;
	}
	else
		charClass = EOF;
}

void getNonBlank() {
	while(isspace(nextChar))
	{
		printf("%c", nextChar);
		getChar();
	}
}

int lex() {
	lexLen = 0;
	getNonBlank();
	switch(charClass){
		case LETTER:
			addChar();
			getChar();
			while(charClass == LETTER || charClass == DIGIT){
				addChar();
				getChar();
			}
			nextToken = IDENT;
			break;
		case DIGIT:
			addChar();
			getChar();
			while(charClass == DIGIT){
				addChar();
				getChar();
			}
			nextToken = INT_LIT;
			break;
		case UNKNOWN:
			lookup(nextChar);
			getChar();
			break;
		case EOF:
			nextToken = EOF; //-1
			lexeme[0] = 'E';
			lexeme[1] = 'O';
			lexeme[2] = 'F';
			lexeme[3] = 0;
			break;
	}

	if(0==strcmp(lexeme,"for")){
		nextToken=FOR_CODE;
	}

	printf("Next token is : %d, Next lexeme is %s\n",nextToken, lexeme);
	return nextToken;
}




