#ifndef ANSI_H
#include <stdarg.h>
#define ANSI_H
#define ACCSI "\e["
#define ACCSIP "\e[?"
#define ACOSC "\e]"
#define ACDCS "\e(B"
#define ACDEC "\e(0"
#define ACRIS "\ec"
#define ACBCK "\u007f"
#define ACPAS "\u001a"
#define ACINS (ACCSI "2~")
#define ACDEL (ACCSI "3~")
#define ACPGU (ACCSI "5~")
#define ACPGD (ACCSI "6~")
#define ACF1 "\eOP"
#define ACF2 "\eOQ"
#define ACF3 "\eOR"
#define ACF4 "\eOS"
#define ACF5 (ACCSI "15~")
#define ACF6 (ACCSI "17~")
#define ACF7 (ACCSI "18~")
#define ACF8 (ACCSI "19~")
#define ACF9 (ACCSI "20~")
#define ACF10 (ACCSI "21~")
#define ACF11 (ACCSI "23~")
#define ACF12 (ACCSI "24~")
#define ACSRS (ACCSI "!p")
#define ACUP (ACCSI "A")
#define ACDWN (ACCSI "B")
#define ACRGT (ACCSI "C")
#define ACLFT (ACCSI "D")
#define ACHOM (ACCSI "H")
#define ACEND (ACCSI "F")
#define ACPAM "\e="
#define ACPNM "\e>"
#define ACHTS "\eH"
#define ACCUU(times) (AC_cur(times, 'A'))
#define ACCUD(times) (AC_cur(times, 'B'))
#define ACCUF(times) (AC_cur(times, 'C'))
#define ACCUB(times) (AC_cur(times, 'D'))
#define ACCNL(times) (AC_cur(times, 'E'))
#define ACCPL(times) (AC_cur(times, 'F'))
#define ACCHA(times) (AC_cur(times, 'G'))
#define ACCUP(x, y) (AC_cur_pos(x, y, 'H'))
#define ACHVP(x, y) (AC_cur_pos(x, y, 'f'))
#define ACEDR (AC_cur(0, 'J'))
#define ACEDL (AC_cur(1, 'J'))
#define ACEDB (AC_cur(2, 'J'))
#define ACEDD (AC_cur(3, 'J'))
#define ACELR (AC_cur(0, 'K'))
#define ACELL (AC_cur(1, 'K'))
#define ACELB (AC_cur(2, 'K'))
#define ACSU(times) (AC_cur(times, 'S'))
#define ACSD(times) (AC_cur(times, 'T'))
#define ACICH(times) (AC_cur(times, '@'))
#define ACDCH(times) (AC_cur(times, 'P'))
#define ACECH(times) (AC_cur(times, 'X'))
#define ACIL(times) (AC_cur(times, 'L'))
#define ACDL(times) (AC_cur(times, 'M'))
#define ACCHT(times) (AC_cur(times, 'I'))
#define ACCBT(times) (AC_cur(times, 'Z'))
#define ACTBC (AC_cur(0, 'g'))
#define ACTBA (AC_cur(3, 'g'))
#define ACDSR (ACCSI "6n")
#define ACSCP (ACCSI "s")
#define ACRCP (ACCSI "u")
#define ACDA (ACCSI "0c")
#define ACAUX(state) (AC_cur_prv(1049, state))
#define ACCKM(state) (AC_cur_prv(1, state))
#define ACBLN(state) (AC_cur_prv(12, state))
#define ACSCR(state) (AC_cur_prv(25, state))
#define ACESB(state) (AC_cur_prv(1049, state))
#define ACBPM(state) (AC_cur_prv(2004, state))
#define ACCOL(state) (AC_cur_prv(3, state))
#define ACTTL(title) (ACOSC "0;" #title "\a")
#define ACRST (AC_sgr(False, 1, RESET))
#define ACSGR(...) (AC_sgr(__VA_ARGS__))
#define ACMOD(i, r, g, b) (ACOSC "4;" #i ";rgb:" #r "/" #g "/" #b "\e")
#define ACSSR(t, b) (ACCSI #t ";" #b "r")
#define ACTKN(token) (#token)
	
	typedef enum Bool {
		False = 0,
		True
	} Bool;
	typedef enum {
		RESET = 0, BOLD, FAINT,
		ITALIC, UNDERLINE, BLINK,
		RAPIDBLINK, INVERSE, CONCEAL,
		CROSSOUT, FONT0, FONT1,
		FONT2, FONT3, FONT4,
		FONT5, FONT6, FONT7,
		FONT8, FONT9, FRAKTUR,
		DOUBLEUNDERLINE, BOLDFAINTOFF, ITALICFRAKTUROFF,
		UNDERLINEOFF, BLINKOFF, INVERSEOFF = 27,
		CONCEALOFF, CROSSOUTOFF, FBLACK,
		FRED, FGREEN, FYELLOW,
		FBLUE, FMAGENTA, FCYAN,
		FWHITE, FOREGROUND, DEFAULTFOREGROUND,
		BBLACK, BRED, BGREEN,
		BYELLOW, BBLUE, BMAGENTA,
		BCYAN, BWHITE, BACKGROUND,
		DEFAULTBACKGROUND, FRAMED, ENCIRCLED,
		OVERLINED, FRAMEENCIRCLEDOFF, OVERLINEDOFF,
		RIGHTLINE, RIGHTDOUBLELINE, LEFTLINE,
		LEFTDOUBLELINE, IDEOSTRESS, IDEOOFF,
		FBBLACK, FBRED, FBGREEN,
		FBYELLOW, FBBLUE, FBMAGENTA,
		FBCYAN, FBWHITE, BBBLACK,
		BBRED, BBGREEN, BBYELLOW,
		BBBLUE, BBMAGENTA, BBCYAN,
		BBWHITE
	} SGR;
	
	/*
		DOUBLEUNDERLINE equal BOLD-OFF
		RIGHTLINE equal IDEOUNDERLINE
		RIGHTDOUBLELINE equal IDEODOUBLEUNDERLINE
		LEFTLINE equal IDEOOVERLINE
		LEFTDOUBLELINE equal IDEODOUBLEOVERLINE
	*/
	
	char * AC_cur(int par, char type);
	char * AC_cur_prv(int par, Bool state);
	char * AC_cur_pos(int x, int y, char type);
	char * AC_sgr(Bool isstr, int args, ...);
	char * AC_sgr_chain(int args, SGR list[], char* joiner, char* ender);
	char * AC_sgr_chain_str(const char * prev, const char * str);
	
#endif
