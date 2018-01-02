#include <stdio.h>
#include <string.h>
#include <ctype.h>

int batoi(char *s, int base);

// assumes s is big enough
void bitoa(int v, int base /* output base */, char *s, int sSize);

int  cnvchToInt(char c, int base);
char cnvIntToch(int a);

void reverseStr(char *is, char *os);

int main(int argc, char *argv[])
{
	int ibase = 10;
	int obase = 10;

	char num[1024];

	reverseStr(num, revs);
	printf("%s %s\n", num, revs);
	
	return 0;
}

int batoi(char *s, int base)
{
	int total = 0;
	int cnv;

	for (; *s != '\0'; ++s) {
		cnv = cnvchToInt(*s, base);
		if (cnv == -1)
			return 0;
		total = total * base + cnv;
	}
	return total;
}

void bitoa(int v, int base, char *s, int sSize)
{
	int i;
	for (i = 0; i < sSize && v != 0; v /= base, ++i)
		*s++ = cnvIntToch(v % base);
	*s = '\0';

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




