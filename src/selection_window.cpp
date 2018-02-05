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

#include <ncurses.h>
#include <string>
#include <vector>

#include "helper.h" //get_center_start
#include "keys.h"
#include "selection_window.h"

extern uint _ROWS, _COLS;

//default window
selection_window::selection_window(std::string title, std::vector<std::string> vec, const uint& size)
: window(size+6, get_selection_width(vec), _ROWS/2-(vec.size()+4)/2, _COLS/2-(get_selection_width(vec)/2), 1) //size+6 = options + 2 for borders + 2 for title space + 2 for extstr
{
	start = 4; //start is starting point of menu options
	choice = start;
	menu = new selection_menu(vec, size);

	print(title, 1, get_center_start(get_selection_width(vec), title));
	print_choices();

	lines = size; //amount of options from the vector
	refresh();
}

selection_window::selection_window(const uint& size, const uint &width, const int &starty, const int &startx, const int &color, std::vector<std::string> vec)
: window(size+2, width, starty, startx, color)
{
	start = 2; //start is starting point of menu options
	choice = start;
	menu = new selection_menu(vec, size-2);

	print_choices();

	lines = size-2; //amount of options from the vector
	refresh();
}

selection_window::~selection_window()
{
	delete menu;
}

size_t selection_window::make_selection()
{
	int c; //int instead of char bc some of the keycodes exceed 127, char's limit
	bool whilevar = false;
	size_t selection = move_cursor(true);

	do { //loop for the menu movement
		c = getch();

		switch(c) {
		case _KEY_UP: //259
			selection = move_cursor(true); //move cursor up
			break;

		case _KEY_DOWN: //258
			selection = move_cursor(false); //move cursor down
			break;

		case _KEY_ENTER: //10
		case _KEY_SPACE: //32
			whilevar = true;
			break;

		case _KEY_ESC: //27
			return 0; //exit code
		}
    } while (!whilevar);

	return selection;
}

size_t selection_window::move_cursor(bool is_up)
{
	int first = 1;
	int second = first + 1;

	print_char(' ', choice, first);
	print_char(' ', choice, second);

	if (is_up) { //KEY_UP
		if (choice != start) //not at the beginning
			choice--;
		menu->move_cursor_up();
	} else { //KEY_DOWN
		if (choice != start + lines - 1) //not at the end
			choice++;
		menu->move_cursor_down();
	}

	print_char('-', choice, first);
	print_char('>', choice, second);
	print_choices();

	return menu->get_selection();
}

void selection_window::print_choices()
{
	uint cursor = start - 1;
	std::string msg = menu->get_ext_str(true);
	set_color(2);
	print(msg, cursor, get_center_start(get_width(), msg));
	set_color(1);

	cursor++;
	std::vector<std::string> vec = menu->get_menu();

	/* This double loop is to print over the WHOLE line
	It solves the problem of:
	 * New Game
	 * Some Options
	Becoming:
	 * New Gameions */
	for (size_t i = 0; i < vec.size(); i++) {
		for (size_t j = 0; j < get_width()-5; j++) {
			if (j < vec[i].length()) //if we're still printing the string
				print_char(vec[i][j], cursor, 4+j);
			else //else we're done and need to print spaces
				print_char(' ', cursor, 4+j);
		}
		cursor++;
	}

	msg = menu->get_ext_str(false);
	set_color(2);
	print(msg, cursor, get_center_start(get_width(), msg));
	set_color(1);

	refresh();
}
