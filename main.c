#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0

/* TODO: add padding options
*/

long batoi(char *s, int base /* input base */);

/* converts long int v to string in base 'base' and puts it in s */
void bitoa(long v, int base /* output base */, char *s, int sSize);

int  cnvchToInt(char c, int base);
char cnvIntToch(int a);

void reverseStr(char *is, char *os);

void parseProgArgs(int argc, char *argv[]);

char help[] = {
"\nreads from standard input and converts it to another base.\n\n"
"usage: \n"
"baseconv [OPTION]...\n\n"
" -o N prints output in base N\n"
" -i N prints input in base N\n"
" -p N padds output with 0 so the output becomes N digits long\n"
};

int ibase   = 10;
int obase   = 10;
int padding = 0;

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Didn't get any arguments.\n");
		printf("Type baseconv --help for help.\n");
		return 2;
	}

	parseProgArgs(argc, argv);

	printf("%d\n", padding);

	char *pnum = NULL;
	char ns[1024];
	char os[1024 + padding];
	size_t len = 0;

	while ( getline(&pnum, &len, stdin) > 1) {
		long n = batoi(pnum, ibase);
		bitoa(n, obase, ns, 1024);

		int nslen = strlen(ns);
		int i;
		for (i = 0; i < padding - nslen; ++i)
			os[i] = '0';
		os[i] = '\0';
		strcpy(&os[i], ns);

		printf("%s\n", os);
		free(pnum);
		pnum = NULL;
		len = 0;
	}
	free(pnum);
	pnum = NULL;

	return 0;
}

void parseProgArgs(int argc, char *argv[])
{
	int nextIsOutbase = FALSE;
	int nextIsInpbase = FALSE;
	int nextIsPadding = FALSE;

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
			else if (argv[i][1] == 'p') {
				if (argv[i][2] == '\0')
					nextIsPadding = TRUE;
				else 
					padding = batoi(&argv[i][2], 10);
			} 
			else if (argv[i][1] == '-') {
				if (strcmp(&argv[i][2], "help") == 0) {
					printf("%s\n", help);
					exit(1);
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
		else if (nextIsPadding) {
			padding = batoi(&argv[i][0], 10);
			nextIsPadding = FALSE;
		}
		else {
			printf("Invalid argument %s\n", argv[i]);
			nextIsOutbase = FALSE;
			nextIsOutbase = FALSE;
			nextIsPadding = FALSE;
		}
	}
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




