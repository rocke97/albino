/* albino
Copyright (C) 2018 Michael Ranciglio

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

#include <ctime> //time(nullptr) for seeding rand_albino
#include <fstream> //global debug log
#include <iostream> //cout error
#include <ncurses.h> //framework we are using
#include <random> //rand_albino

#include "game.h" //game_main
#include "universal.h" //version number

void init(); //run this first
void init_colors(); //initialize colors
void print_first(); //get initial print stuff out of main

uint _ROWS, _COLS;

std::default_random_engine rand_albino; //global random engine
std::ofstream debug("debug.txt");

//NOTE: to self keep main clean, it's really easy to clutter it up

int main()
{
	init(); //initialize the game and ncurses

	if (_ROWS < 24 || _COLS < 80) {
		endwin(); //end ncurses mode
		std::cout << "Error: Required minimum 24 rows and 80 columns.\n";
		std::cout << "Try making your terminal bigger.\n";
		return 1;
	}

	game_main(); //start the game

	//getch(); //wait for user input
	endwin(); //end ncurses mode

	return 0;
}

void init()
{
	initscr(); //start curses mode
	start_color(); //enable color functionality
	cbreak(); //line buffering disabled
	noecho(); //echo disabled
	keypad(stdscr, true); //enable keypad for arrow keys
	curs_set(0); //no cursor
	init_colors(); //initialize color pairings
	refresh(); //let it all be SEEEN
	rand_albino.seed(time(nullptr)); //seed the random number generator
	getmaxyx(stdscr, _ROWS, _COLS); //initailize the game's row and col count
	print_first(); //get version and title printed on top
}

void init_colors()
{
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_RED, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(9, COLOR_BLACK, COLOR_GREEN);
	init_pair(10, COLOR_BLACK, COLOR_YELLOW);
	init_pair(11, COLOR_BLACK, COLOR_BLUE);
	init_pair(12, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(13, COLOR_BLACK, COLOR_CYAN);
	init_pair(14, COLOR_BLACK, COLOR_WHITE);
	init_pair(15, COLOR_YELLOW, COLOR_WHITE);
	init_pair(16, COLOR_RED, COLOR_WHITE);
	init_pair(17, COLOR_GREEN, COLOR_WHITE);
}

void print_first()
{
	attron(COLOR_PAIR(7)); //color the top red
	std::string msg = "albino version: " + VERSION + " There are %d rows and %d cols";
	printw(msg.c_str(), _ROWS, _COLS);
	attron(COLOR_PAIR(1)); //change back to white for redrawing windows
	refresh();
}
