#include "ansi.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
	Sort commands alphabetically in both man  and page, use \ delimiters to split single string to multiple code lines.
*/

void help() {
	printf("\nCommands:\n\
	\n\t-attr\t- Show terminal attributes.\
	\n\t-aux on|off\t- Toggle auxillary port.\
	\n\t-cursor (x[ y] | (show|hide|blink|noblink))\t- Manage terminal cursor.\
	\n\t-dec\t- Switch from ASCII to DEC.\
	\n\t-erase\t- Manage terminal display.\
	\n\t-region\t- Set scrolling region.\
	\n\t-resize\t- Resize terminal window.\
	\n\t-reset\t- Reset window state.\
	\n\t-scroll [-]dy\t- Scroll terminal.\
	\n\t-switch alternative|normal\t- Switch terminal screen.\
	\n\t-title name\t- Change terminal title.\
	\n\t-paste block|enable\t- Toggle pasting.\
	\n\t-sgr params<num|SGR>\t- Set graphic rendition.\n\n");
}

char* error(int args, char* params[]) {
	char* ret = ACSGR(True, 2, "Invalid Command", BRED);
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
		ret = "\nUsage:\
		\n\t-cursor [x ]y\t-Moves cursor to designated position.\
		\n\t-cursor hide|show\t-Toggle visibility of cursor.\
		\n\t-cursor blink|noblink\t-Toggle cursor blinking.\n\n";
	}
	return ret;
}

char* dec(int args, char* params[]) {
	if (!args) {
		return "\nUsage:\n\t-dec on|off\t-Switch from ASCII to DEC.\n\n";
	} else if (!strcmp(params[0], "on")) {
		return ACDEC;
	} else if (!strcmp(params[0], "off")) {
		return ACDCS;
	}
	
	return "'dec' can only take the values 'on' and 'off'.\n";
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
	if (!args) {
		return "\nUsage:\n\t-aux on|off\t-Toggle AUX port.\n\n";
	} else if (!strcmp(params[0], "on")) {
		return ACAUX(True);
	} else if (!strcmp(params[0], "off")) {
		return ACAUX(False);
	}
	return "'aux' can only take the values 'on' and 'off'.\n";
}

char* region(int args, char* params[]) {
	char* ret;
	if (args >= 2) {
		ACSSR(params[0], params[1], ret);
		return ret;
	}
	return "\nUsage:\n\t-region x y\t-Set scrolling region.\n\n";
}

char* resize(int args, char* params[]) {
	if (!args) {
		return "\nUsage:\n\t-resize big|small\t-Change terminal screen size.\n\n";
	} else {
		if (!strcmp(params[0], "small")) {
			return ACCOL(False);
		} else if (!strcmp(params[0], "big")) {
			return ACCOL(True);
		} else {
			return "'resize' can only take the values 'small' and 'big'.\n";
		}
	}
}

char* reset(int args, char* params[]) {
	return ACSRS;
}

char* sgr(int args, char* params[]) {
	SGR* pars = (SGR*)calloc(args, sizeof(SGR));

	if (args) {
		for (register size_t i = 0; i < args; i++) {
			pars[i] = (SGR)atoi(params[i]);
		}
	
		return AC_chain(args, pars, ";", "m");
	}
	return "\nUsage:\n\t-sgr whitespace_separated_number_list\t-Set Graphics Rendition.\n\n";
}

char* swt(int args, char* params[]) {
	if (!args) {
		return "\nUsage:\n\t-switch alternative|normal\t-Switch terminal screen.\n\n";
	} else {
		if (!strcmp(params[0], "normal")) {
			return ACESB(False);
		} else if (!strcmp(params[0], "alternative")) {
			return ACESB(True);
		} else {
			return "'switch' can only take the values 'normal' and 'alternative'.\n";
		}
	}
}

char* paste(int args, char* params[]) {
	if (!args) {
		return "\nUsage:\n\t-paste bracketed|normal\t-Toggle bracketed paste mode.\n\n";
	} else {
		if (!strcmp(params[0], "normal")) {
			return ACBPM(False);
		} else if (!strcmp(params[0], "bracketed")) {
			return ACBPM(True);
		} else {
			return "'paste' can only take the values 'normal' and 'bracketed'.\n";
		}
	}
}

char* title(int args, char* params[]) {
	if (!args) {
		return "\nUsage:\n\t-title 'name'\t-Set terminal title.\n\n";
	} else {
		char* ret;
		ACTTL(arrjoin(params, "", args), ret);
		return ret;
	}
}

char* attribute(int args, char* params[]) {
	return ACDA;
}

char* (*hash(char* str))(int, char**) {
	char* (*out)(int, char**);
	if (!strcmp(str, "cursor") || !strcmp(str, "cur")) {
		out = cursor;
	} else if (!strcmp(str, "erase") || !strcmp(str, "ers")) {
		out = erase;
	} else if (!strcmp(str, "scroll")  || !strcmp(str, "scr")) {
		out = scroll;
	} else if (!strcmp(str, "aux") || !strcmp(str, "auxillary")) {
		out = aux;
	} else if (!strcmp(str, "sgr") || !strcmp(str, "graphic")) {
		out = sgr;
	} else if (!strcmp(str, "switch") || !strcmp(str, "swt")) {
		out = swt;
	} else if (!strcmp(str, "paste") || !strcmp(str, "pst")) {
		out = paste;
	} else if (!strcmp(str, "title") || !strcmp(str, "ttl")) {
		out = title;
	} else if (!strcmp(str, "attr") || !strcmp(str, "attribute")) {
		out = attribute;
	} else if (!strcmp(str, "dec")) {
		out = dec;
	} else if (!strcmp(str, "region") || !strcmp(str, "reg")) {
		out = region;
	} else if (!strcmp(str, "resize") || !strcmp(str, "res")) {
		out = resize;
	} else if (!strcmp(str, "reset") || !strcmp(str, "rst")) {
		out = reset;
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
