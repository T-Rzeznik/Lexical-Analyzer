#include <stdio.h>
#include <string.h>

#define FOR_CODE 30 
#define SWITCH_CODE 37

// additional challenge: how to make keyword case insensitive???
int lookupReseredWords(char * lexeme)
{

	if(0==strcmp("for", lexeme))
		return FOR_CODE ;
	if(0==strcmp("switch", lexeme))
		return SWITCH_CODE ;
	else
		return 0;

	//alternatively, can put all the keywords in an array to loop through
}

int main()
{
	const int LEN=100;
	char lexeme[LEN];
	int token;

        memset(lexeme, 0, sizeof(char)*LEN);	
	strcpy(lexeme, "for");
	token=lookupReseredWords(lexeme);
	printf("%i :%s\n", token, lexeme);

        memset(lexeme, 0, sizeof(char)*LEN);	
	strcpy(lexeme, "switch");
	token=lookupReseredWords(lexeme);
	printf("%i :%s\n", token, lexeme);

        memset(lexeme, 0, sizeof(char)*LEN);	
	strcpy(lexeme, "SWITCH");
	token=lookupReseredWords(lexeme);
	printf("%i :%s\n", token, lexeme);

	return 0;
}
