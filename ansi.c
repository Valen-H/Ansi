#include "ansi.h"
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

static char* arrjoin(char* strings[], char* seperator, int count) {
	register char* str = NULL;
	register size_t total_length = 0,
    		i = 0;
    	
    for (i = 0; i < count; i++) total_length += strlen(strings[i]);
    total_length++;
    total_length += strlen(seperator) * (count - 1);
    str = (char*)malloc(total_length);
    str[0] = '\0';
    
    for (i = 0; i < count; i++) {
        strcat(str, strings[i]);
        if (i < (count - 1)) strcat(str, seperator);
    }
    
    return str;
}

char* AC_cur(int par, char type) {
	register char* ret = (char*)malloc(strlen(ACCSI) + sizeof(char) * 6);
	
	sprintf(ret, ACCSI "%d%c", par, type);
	
	return ret;
}

char* AC_cur_pos(int x, int y, char type) {
	register char* ret = (char*)malloc(strlen(ACCSI) + strlen(ACTKN(x)) + strlen(ACTKN(y)) + sizeof(char) * 2);
	
	sprintf(ret, ACCSI "%d;%d%c", x, y, type);
	
	return ret;
}

char* AC_cur_prv(int par, Bool state) {
	register char* ret = (char*)malloc(strlen(ACCSIP) + sizeof(char) * 7);
	
	sprintf(ret, ACCSIP "%d%c", par, (((int)state) ? 'h' : 'l'));
	
	return ret;
}

char* AC_sgr(Bool isstr, int args, ...) {
	va_list vlist;
	va_start(vlist, args);
	
	register SGR* ret = (SGR*)calloc(args, sizeof(SGR));
	register size_t i;
	register char* str;
	
	for (i = 0; i < args; i++) {
		if (!i && isstr) {
			str = va_arg(vlist, char*);
		} else {
			ret[i] = va_arg(vlist, SGR);
		}
	}
	
	va_end(vlist);
	
	register char* rr,
		* r;
	
	r = AC_sgr_chain(i, ret, ";", "m");
	if (!isstr) {
		rr = r;
	} else {
		rr = AC_sgr_chain_str(r, str);
	}
	
	return rr;
}

char* AC_sgr_chain(int args, SGR list[], char* joiner, char* ender) {
	register char** ret = (char**)calloc(args, sizeof(char*));
	register size_t i;
	
	for (i = 0; i < args; i++) {
		ret[i] = (char*)realloc(ret[i], 5);
		sprintf(ret[i], "%d", (int)list[i]);
	}
	
	register char* r = arrjoin(ret, joiner, i),
		* rr = (char*)malloc(strlen(ACCSI) + strlen(r) + strlen(ender) + 1);
		
	strcat(rr, ACCSI);
	strcat(rr, r);
	strcat(rr, ender);
	return rr;
}

char* AC_sgr_chain_str(const char* prev, const char* str) {
	const char* end = ACRST,
		* arr[3] = { prev, str, end };
		register char* rr = arrjoin((char**)arr, "", 3);
		
	return rr;
}
