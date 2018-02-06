/* albino
Copyright (C) 2017 Michael Ranciglio

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

#ifndef __TEXTLOG_WINDOW_H__
#define __TEXTLOG_WINDOW_H__

#include <fstream>
#include <ncurses.h>
#include <string>

#include "text_buffer.h"
#include "window.h"

class textlog_window : public window
{
public:
	textlog_window();
	~textlog_window();
	void print(const std::string &s);

private:
	text_buffer *logbuf;
	std::ofstream output;
};

#endif //__textlog_window_H__
