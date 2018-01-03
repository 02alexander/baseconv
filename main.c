#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

long batoi(char *s, int base /* input base */);

/* converts long int v to string in base 'base' and puts it in s */
void bitoa(long v, int base /* output base */, char *s, int sSize);

int  cnvchToInt(char c, int base);
char cnvIntToch(int a);

void reverseStr(char *is, char *os);

char help[] = {
"\nreads from standard input and converts it to another base.\n\n"
"usage: \n"
"baseconv [OPTION]...\n\n"
" -o N prints output in base N\n"
" -i N prints input in base N\n"
};

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Didn't get any arguments.\n");
		printf("Type baseconv --help for help.\n");
		return 2;
	}

	int ibase = 10;
	int obase = 10;

	int nextIsOutbase = FALSE;
	int nextIsInpbase = FALSE;


	for (int i = 1; i < argc; ++i) {

		if (argv[i][0] == '-') {

			if (argv[i][1] == 'o') {
				if (argv[i][2] == '\0')
					nextIsOutbase = TRUE;
				else 
					obase = batoi(&argv[i][2], 10);
			} 
			else if (argv[i][1] == 'i') {
				if (argv[i][2] == '\0')
					nextIsInpbase = TRUE;
				else
					ibase = batoi(&argv[i][2], 10);
			} 
			else if (argv[i][1] == '-') {
				if (strcmp(&argv[i][2], "help") == 0) {
					printf("%s\n", help);
					return 1;
				}
			} 

		} 
		else if (nextIsOutbase) {
			obase = batoi(&argv[i][0], 10);
			nextIsOutbase = FALSE;
		}
		else if (nextIsInpbase) {
			ibase = batoi(&argv[i][0], 10);
			nextIsInpbase = FALSE;
		}
		else {
			printf("Invalid argument %s\n", argv[i]);
			nextIsOutbase = FALSE;
			nextIsOutbase = FALSE;
		}

	}

	char *pnum = NULL;
	char ns[1024];
	size_t len = 0;

	while ( getline(&pnum, &len, stdin) > 1) {
		long n = batoi(pnum, ibase);
		bitoa(n, obase, ns, 1024);
		printf("%s\n", ns);
		free(pnum);
	}
	free(pnum);
	pnum = NULL;

	return 0;
}

long batoi(char *s, int base)
{
	long total = 0;
	int cnv;

	for (; isdigit(*s); ++s) {
		cnv = cnvchToInt(*s, base);
		if (cnv == -1)
			return 0;
		total = total * base + cnv;
	}
	return total;
}

void bitoa(long v, int base, char *s, int sSize)
{
	int i;
	for (i = 0; i < sSize && v != 0; v /= base, ++i)
		s[i] = cnvIntToch(v % base);
	s[i] = '\0';
	char revs[i];
	reverseStr(s, revs);
	strcpy(s, revs);
}

char cnvIntToch(int a)
{
	if (a < 10)
		return a + '0';
	return a + 'a' - 10;
}

int cnvchToInt(char c, int base)
{
	if (c <= '9' && c >= '0')
		return c - '0';

	if (islower(c))
		return c - 'a' + 10;
	else if (isupper(c))
		return c - 'A' + 10;
	else
		return -1;
}

void reverseStr(char *is, char *os)
{
	char *end = is + strlen(is);
	while(end != is)
		*os++ = *--end;
	*os = '\0';
}




