#include <stdio.h>

typedef/**/struct{unsigned/**/aku;char*const/**/soku;}zan;
typedef##struct{unsigned##aku;char*char##soku;}zat;

int main()
{
	zat	a;
	zan	b;

	a.aku = 9;
	b.aku = 10;
	printf("%u\n%u\n", a.aku, b.aku);
	return (0);
}