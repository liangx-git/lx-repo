#include "Screen.h"

char Screen::get(pos r, pos c) const 
{
	return contents[r * width + c];
}

Screen &Screen::move(pos r, pos c) 
{
	cursor = r * width + c;
	return *this;
}

Screen &Screen::set(char ch)
{
	contents[cursor] = ch;
	return *this;
}

Screen &Screen::set(pos r, pos c, char ch)
{
	contents[r * width + c] = ch;
	return *this;
}


const Screen &Screen::display(std::ostream &os) const
{
	do_display(os);
	return *this;
}

Screen &Screen::display(std::ostream &os)
{
	do_display(os);
	return *this;
}

int main()
{
	return 0;
}
