/*
	https://en.m.wikipedia.org/wiki/ANSI_escape_cyode
*/

#include "ansi.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("%sOK\n%s", ACCUP(5, 10), ACSCR(True));
	printf("%sbold%sreset\n", AC_sgr(False, 1, BOLD), ACRST);
	char* txt;
	ACTTL("test", txt);
	printf("%s%s%s%s", AC_sgr(False, 2, 1, 2), "bold italic\n", ACRST, txt);
	printf("%s%s%s%s%s", AC_sgr(False, 2, BOLD, 2), "boldtalic ", AC_sgr(False, 1, BOLD), "bold?\n", ACRST);
	printf("%s%s%s", ACSGR(False, 2, FRAKTUR, FGREEN), "ok\n", ACRST);
	SGR a[3] = { BOLD, ITALIC, FAINT };
	ACMOD("1", "ff", "00", "ff", txt);
	printf("%s%s\n", AC_sgr_chain_str(AC_chain(3, a, ";", "m"), "okie"), txt);
	return 0;
}
