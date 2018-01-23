/* albino
Copyright (C) 2017-2018 Michael Ranciglio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>. */

#include <fstream> //global debug log
#include <ncurses.h>
#include <string>
#include <vector>

#include "battle.h" //battle call
#include "maze.h" //maze/dungeon
#include "maze_window.h" //maze_window object
#include "player.h" //player object
#include "player_window.h" //player_window windoselection
#include "selection_window.h" //main menu
#include "textlog_window.h" //textlog_window object
#include "window.h" //base class for all windows
#include "universal.h" //version number

extern uint _ROWS;
extern uint _COLS;

//game related functions
bool main_menu();
bool new_game_menu();
bool pause_game();

//helping functions
std::vector<std::string> get_main_menu_choices();
std::vector<std::string> get_pause_menu_choices();

//window functions
void backup(std::vector<window*>& v); //stores current window info in cache
void delete_windows(std::vector<window*>& v); //calls all window destructors
void restore(std::vector<window*>& v); //retrieves window info from cache

void game_main()
{
	player p1;
	maze dungeon;
	dungeon.gen_main(); //gen dungeon

	maze_window *mwin = new maze_window(&dungeon);
	textlog_window *tlwin = new textlog_window();
	player_window *pwin = new player_window(&p1);
	std::vector<window*> windows; //collection of primary game windows

	windows.push_back(mwin);
	windows.push_back(tlwin);
	windows.push_back(pwin);

	backup(windows);

	if (!main_menu()) { //if they chose to exit
		delete_windows(windows);
		return; //end it here
	}

	restore(windows);

	tlwin->print("Lots and lots and lots and lots and lots and lost and lots and lots and lots and lots of text.");
	mwin->print();
	pwin->refresh();
	mwin->test();

	refresh();
	getch(); //wait for user input
	delete_windows(windows);
}

bool main_menu()
{
	selection_window *menuwin = new selection_window("Welcome", get_main_menu_choices(), 22);

	bool whilevar = true;
	bool ret = true;

	do {
		int l = menuwin->make_selection();

		switch (l) {
			case 1:
				if (new_game_menu()) {
					whilevar = false;
				}
				break;
			case 2:
			case 3:
			case 4:
			default:
				ret = false; //exit
				whilevar = false; //end loop
				break;
		}
	} while (whilevar);

	delete menuwin;

	return ret;
}

bool new_game_menu()
{
	//not yet implemented
	return true;
}

bool pause_game()
{
	selection_window *pausewin = new selection_window("Paused", get_pause_menu_choices(), 22);

	bool whilevar = true;
	bool ret = true;

	do {
		int l = pausewin->make_selection();

		switch (l) {
			case 1:
				whilevar = false; //resume
				break;
			case 2:
				//options menu
				whilevar = false;
				break;
			case 3:
			default:
				ret = false; //exit
				whilevar = false; //end loop
				break;
		}
	} while (whilevar);

	delete pausewin;

	return ret;
}

std::vector<std::string> get_main_menu_choices()
{
	std::vector<std::string> choices;

	choices.push_back("New Game");
	choices.push_back("Other Option");
	choices.push_back("Other Option 2.0");
	choices.push_back("Exit Game");

	return choices;
}

std::vector<std::string> get_pause_menu_choices()
{
	std::vector<std::string> choices;

	choices.push_back("Resume");
	choices.push_back("Options");
	choices.push_back("Exit Game");

	return choices;
}

void backup(std::vector<window*>& v)
{
	for (size_t i = 0; i < v.size(); i++) {
		v[i]->backup();
	}
}

void restore(std::vector<window*>& v)
{
	for (size_t i = 0; i < v.size(); i++) {
		v[i]->restore();
	}
}

void delete_windows(std::vector<window*>& v)
{
	for (size_t i = 0; i < v.size(); i++) {
		delete v[i];
	}
}
