#include <stdio.h>

int main() {

	char fname[128];
	printf("Enter program file name\n");
	scanf("%s",fname);

	FILE *f;
	f  = fopen(fname, "r");

	int c = getc(f);
	while (c != EOF) {
		putchar(c);
		c = getc(f);
	}

	fclose(f);
	getchar();

	return 0;
}

