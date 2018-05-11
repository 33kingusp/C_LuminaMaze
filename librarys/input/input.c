//Write by 33kingusp
#include <ncurses.h>

#include "./input.h"

void SetupInput()
{
	noecho();
	cbreak();
	curs_set(0);
	timeout(0);
	keypad(stdscr, TRUE);
}

int Input()
{
	int i;

	switch (getch())
	{
		case KEY_UP:	case 'w': case 'W': i = IN_UP;		break;
		case KEY_DOWN:	case 's': case 'A': i = IN_DOWN;	break;
		case KEY_LEFT:	case 'a': case 'S': i = IN_LEFT;	break;
		case KEY_RIGHT:	case 'd': case 'D': i = IN_RIGHT;	break;
		case KEY_ENTER:	case 'z': case 'Z': i = IN_A;		break;
		case KEY_CANCEL:case 'x': case 'X': i = IN_B;		break;
		case 'q': case 'Q': i = IN_EXIT;			break;
		default: i = IN_NONE;					break;
	}

	return i;
}
