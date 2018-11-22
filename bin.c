#include "ansi.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
	Sort commands alphabetically in both man  and page, use \ delimiters to split single string to multiple code lines.
*/

void help() {
	printf("\nCommands:\n\n\t-cursor (x[ y] | (show|hide|blink|noblink))\n\t-erase\n\t-scroll [-]dy\n\t-aux on|off\n\t-switch alternative|normal\n\t-title \"name\"\n\t-paste block|enable\n\t-sgr params<num|SGR>\n\n");
}

char* error(int args, char* params[]) {
	char* ret = ACSGR(True, 2, "Invalid command", BRED);
	ret = realloc(ret, strlen(ret) + sizeof(char) * 2);
	strcat(ret, "\n");
	return ret;
}

char* cursor(int args, char* params[]) {
	char* ret;
	if (args == 2) {
		ret = ACCUP(atoi(params[0]), atoi(params[1]));
	} else if (args == 1) {
		if (!strcmp(params[0], "show")) {
			ret = ACSCR(True);
		} else if (!strcmp(params[0], "hide")) {
			ret = ACSCR(False);
		} else if (!strcmp(params[0], "blink")) {
			ret = ACBLN(True);
		} else if (!strcmp(params[0], "noblink")) {
			ret = ACBLN(False);
		} else {
			ret = malloc(strlen(params[0]) + sizeof(char) * 7 + strlen(ACCSI) * 2);
			strcat(ret, ACCUP(0, 0));
			strcat(ret, ACCUD(atoi(params[0])));
		}
	} else {
		ret = "\nUsage:\n\t-cursor [x ]y\t-Moves cursor to designated position.\n\t-cursor hide|show\t-Toggle visibility of cursor.\n\t-cursor blink|noblink\t-Toggle cursor blinking.\n\n";
	}
	return ret;
}

char* erase(int args, char* params[]) {
	return ACEDB;
}

char* scroll(int args, char* params[]) {
	char* ret;
	
	if (!args) {
		ret = "\nUsage:\n\t-scroll [-]y\t-Scroll page by X lines (Negative values scroll down, panning the lines up).\n\n";
	} else {
		int sc = atoi(params[0]);
		
		if (sc < 0) {
			ret = ACSD(abs(sc));
		} else if (sc > 0) {
			ret = ACSU(sc);
		}
	}
	
	return ret;
}

char* aux(int args, char* params[]) {
	char* ret = "";
	return ret;
}

char* sgr(int args, char* params[]) {
	SGR* pars = (SGR*)calloc(args, sizeof(SGR));

	if (args) {
		for (register size_t i = 0; i < args; i++) {
			pars[i] = (SGR)atoi(params[i]);
		}
	
		return AC_sgr_chain(args, pars, ";", "m");
	}
	return "\nUsage:\n\t-sgr whitespace_separated_number_list\t-Set Graphics Rendition.\n\n";
}

char* swt(int args, char* params[]) {
	char* ret = "";
	return ret;
}

char* paste(int args, char* params[]) {
	char* ret = "";
	return ret;
}

char* title(int args, char* params[]) {
	char* ret = "";
	return ret;
}

char* (*hash(char* str))(int, char**) {
	char* (*out)(int, char**);
	if (!strcmp(str, "cursor") || !strcmp(str, "cur")) {
		out = cursor;
	} else if (!strcmp(str, "erase") || !strcmp(str, "ers")) {
		out = erase;
	} else if (!strcmp(str, "scroll")  || !strcmp(str, "scr")) {
		out = scroll;
	} else if (!strcmp(str, "aux")) {
		out = aux;
	} else if (!strcmp(str, "sgr")) {
		out = sgr;
	} else if (!strcmp(str, "switch") || !strcmp(str, "swt")) {
		out = swt;
	} else if (!strcmp(str, "paste") || !strcmp(str, "pst")) {
		out = paste;
	} else if (!strcmp(str, "title") || !strcmp(str, "ttl")) {
		out = title;
	} else {
		out = error;
	}
	
	return out;
}

int hasher(char* inp, size_t size, char* hash[]) {
	register size_t it = 0,
		out = -1;
	
	for (; it < size; it++) {
		if (!strcmp(inp, hash[it])) {
			out = it;
			break;
		}
	}
	
	return (int)out;
}

int main(int argc, char* argv[]) {
	register char** params = (char**)calloc(argc - 1, sizeof(char*));
	register char* (*func)(int, char**);
	
	for (int i = 1; i < argc; i++) {
		if (i != 1) {
			params[i - 2] = argv[i];
		} else {
			func = hash(argv[1]);
		}
	}
	
	if (argc - 1) {
		printf("%s", func(argc - 2, params));
	} else {
		help();
	}
}
