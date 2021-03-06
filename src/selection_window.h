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

#ifndef __SELECTION_WINDOW_H__
#define __SELECTION_WINDOW_H__

#include <string>
#include <vector>

#include "base.h" //for the extension with detailed_selection_window
#include "selection_menu.h" //the text available
#include "window.h"

class selection_window : public window
{
public:
	selection_window(std::string title, std::vector<std::string> vec, const uint& size = 4);
	selection_window(const uint& size, const uint &width, const int &starty, const int &startx, const int &color, std::vector<std::string> vec);
	~selection_window();
	size_t make_selection();
	size_t move_cursor(bool is_up);
	void print_choices();
private:
	size_t lines;
	size_t start;
	size_t choice;
	selection_menu* menu;
};

#endif //__SELECTION_WINDOW_H__
