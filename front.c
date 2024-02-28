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
void addChar(); 	// Function to add a character to the current lexeme
void getChar(); 	// Function to get the next character from the input file
void getNonBlank(); // Function to skip any whitespace characters
int lex();          // Function to perform lexical analysis and recognize tokens

int lookupReservedWords(char* lexeme); //Step 4: function prototype, Function to lookup reserved words

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

#define IF_CODE 36       //STEP 4: New token codes for reserved words
#define ELSE_CODE 37
#define WHILE_CODE 38
#define DO_CODE 39
#define INT_CODE 40
#define FLOAT_CODE 41
#define SWITCH_CODE 42   //make sure each token has unquie ID


/*************************************/
/* main driver */
int main(){
	char filename[100]; // Buffer for filename                    //STEP 3: read file name at run time
    printf("Enter the filename: ");
    scanf("%s", filename); // Read filename from keyboard
    if ((in_fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "ERROR - cannot open %s\n", filename); //----------
	}
	else{ 
		getChar(); // Get the first character from the file
		do{
			lex(); // analize lexeme
		} while(nextToken != EOF); // Continue until end of file
	}
	return 0;
}



int lookupReservedWords(char *lexeme) {  //Check if lexeme is a reserved word
    if (strcmp(lexeme, "for") == 0)  //strcmp, compares lexeme and hard coded string; this case "for"
        return FOR_CODE;
    else if (strcmp(lexeme, "if") == 0)
        return IF_CODE;
    else if (strcmp(lexeme, "else") == 0)
        return ELSE_CODE;
    else if (strcmp(lexeme, "while") == 0)
        return WHILE_CODE;
    else if (strcmp(lexeme, "do") == 0)
        return DO_CODE;
    else if (strcmp(lexeme, "int") == 0)
        return INT_CODE;
    else if (strcmp(lexeme, "float") == 0)
        return FLOAT_CODE;
    else if (strcmp(lexeme, "switch") == 0)
        return SWITCH_CODE;
    else
        return 0; // Indicating not a reserved word. Handling defaulting to IDENT in lex() function
}


int lookup(char ch) {
	switch(ch) {
		case '(':                   //if char is (
			addChar();              //add char to lexeme
			nextToken = LEFT_PAREN; //assign nextToken
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
		default:                   //no more characters, end of file
			addChar();
			nextToken = EOF;
			break;
	}
	return nextToken;
}

void addChar(){
	if(lexLen <= 98){  					//check if buffer is big enough
		lexeme[lexLen++] = nextChar; 	//add char to buffer
		lexeme[lexLen] = 0; 			//0 to end lexeme
	}
	else
		printf("Error - lexeme is too long \n");
}

void getChar() {

	if((nextChar = getc(in_fp)) != EOF){ //check if theres more char in the file

		if(isalpha(nextChar))   //if char is a letter
			charClass = LETTER;
		else if(isdigit(nextChar))  //if car is digit
			charClass = DIGIT;
		else charClass = UNKNOWN;   //neither its Unknown
	}
	else
		charClass = EOF; //end of file
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
    switch (charClass) {
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {  //adding char(letters or digit) to lexeme
                addChar();
                getChar();
            }
            nextToken = lookupReservedWords(lexeme); // STEP4: Putting our new function to use, checking if lexme is a reserved word
            if (nextToken == 0) {
                nextToken = IDENT; // If function returns 0, we default as Indentifer, which means its not a reserved word and most likey a user-defined name of a variable, function ,ect.
            }
            break;
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {  //adding char(digit only) to lexeme
                addChar();
                getChar();
            }
            nextToken = INT_LIT; //the token is an Integer
            break;
        case UNKNOWN:            //unknown character
            lookup(nextChar);
            getChar();
            break;
        case EOF:
            nextToken = EOF;  //end of file
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    }

    printf("Next token is : %d, Next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
}




