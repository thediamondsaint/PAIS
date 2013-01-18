#include <ncurses.h>
#include <fstream>
#include <cstring>
#include "extra.h"
using namespace std;
/*
	INFORMATION KEPT IN EXTRA_H

	This is made by Sa[i]nT -- You can find me @ irc.geekshed.net/#jupiterbroadcasting

*/


// defines
#define SREFRESH refresh();
#define SINIT_CURSES initscr(); noecho(); raw(); keypad(stdscr,TRUE); SREFRESH
#define SEND_CURSES SREFRESH endwin();
#define SGETRECT getmaxyx(stdscr, nRows, nCols);
#define SGETMOUSEPOS getyx(stdscr,mX,mY);
#define SCLEAR clear();

// protos
void showstartmenu();

// global vars
int nRows, nCols; // Maximum Rect of the console
int mX, mY; // mouse coordinates

// ----- USER INFORMATION
user_information USER_INFO;


int main(int argc, char ** argv)
{
	SINIT_CURSES

	// show first menu
	showstartmenu();

	SEND_CURSES

    return 0;
}

// NON-OO FUNCTIONS
void showstartmenu()
{
//	int c = 0;
	char userprompt[] = "Username: ";
	char passprompt[] = "Password: ";
	char username[80];
	char password[80];
	char notes[100];
	char notesS[] = "Enter your desired Username and Password!";
	bool error = false;

	while (1)
	{
		// refresh RECT
		SGETRECT

		// special coordinates, for the notes section
        int sy = nRows - 2;

		// print slogon top left
		int ty = 0;
		int tx = 0;
		attron(A_STANDOUT | A_BOLD);
		mvprintw(ty,tx, slogan);
		attroff(A_STANDOUT | A_BOLD);

		// is error? print notes
		(error) ? mvprintw(sy, (nCols - strlen(notes))/2, notes) : mvprintw(sy, (nCols - strlen(notesS))/2, notesS);

		SREFRESH
		mvprintw(nRows/2, (nCols - strlen(userprompt))/2 - 5, userprompt);

		// GET USER USERNAME
		echo();
        getstr(username);
		noecho();

		// look for error in username
        if (strlen(username) < 1)
		{
			// ERROR USERNAME_TOO_SHORT
			memset(notes, 0, sizeof notes);
			strcat(notes, "Last Error = ERROR USERNAME_TOO_SHORT!");
			error = true;
			SCLEAR
			continue;
		}

		if (strpbrk(username, forbidden_chars) != NULL)
		{
			// ERROR USERNAME_ILLEGAL_CHARS
			memset(notes, 0, sizeof notes);
			strcat(notes, "Last Error = ERROR USERNAME_ILLEGAL_CHARS!");
			error = true;
			SCLEAR
			continue;
		}
		error = false;
        SREFRESH


		mvprintw(nRows/2 + 1, (nCols - strlen(passprompt))/2 - 5, passprompt);

		// GET USER PASSWORD
		echo();
        getstr(password);
		noecho();

		// look for error in username
        if (strlen(password) < 1)
		{
			// ERROR USERNAME_TOO_SHORT
			memset(notes, 0, sizeof notes);
			strcat(notes, "Last Error = ERROR PASSWORD_TOO_SHORT!");
			error = true;
			SCLEAR
			continue;
		}
		if (strpbrk(password, forbidden_chars) != NULL)
		{
			// ERROR PASSWORD_ILLEGAL_CHARS
			memset(notes, 0, sizeof notes);
			strcat(notes, "Last Error = ERROR PASSWORD_ILLEGAL_CHARS!");
			error = true;
			SCLEAR
			continue;
		}
		error = false;
        SREFRESH


        // SHOW CONFIRMATION SCREEN
        SCLEAR
        SGETRECT
        char tmp[] = "Are you sure? Yes/No: ";
        char tu[] = "Username: ";
        char pu[] = "Password: ";
        strcat(tu, username);
        strcat(pu, password);

        char desc[10];
        mvprintw(nRows/2 - 2, (nCols - strlen(tu))/2 - 5, tu);
        mvprintw(nRows/2 - 1, (nCols - strlen(pu))/2 - 5, pu);
        mvprintw(nRows/2, (nCols - strlen(tmp))/2 - 5, tmp);

        echo();
        getstr(desc);
        noecho();

        if (strcmp(desc, "Yes") == 0 || strcmp(desc, "yes") == 0)
        {
            // SUCCESS
            memset(USER_INFO.username, 0, 80);
            strcat(USER_INFO.username, username);
            memset(USER_INFO.password, 0, 80);
            strcat(USER_INFO.password, password);
            SCLEAR
            break;
        } else if (strcmp(desc, "No") == 0 || strcmp(desc, "no") == 0)
        {
            SCLEAR
            continue;
        } else {
            SCLEAR
            continue;
        }
	}
	SREFRESH
}












