#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>
#include<algorithm>


using namespace std;

class Screen
{
friend class WinManager;
public:
	typedef string::size_type pos;
	
	Screen() : 
		width(10), height(10), cursor(0), data(100, '*'){}
	
	Screen(char ch) : 
		width(10), height(10), cursor(0), data(100, ch){}

	Screen(pos w, pos h, pos cur, char ch) : 
		width(w), height(h), cursor(cur),data(w * h, ch){}
	
	Screen(const Screen &other) : 
		width(other.width), height(other.height), cursor(other.cursor), data(other.data){}

	Screen &operator=(const Screen &other);
	
	~Screen() = default;

	char get() const;
	char get(pos w, pos h) const;

	Screen &set(char ch);
	Screen &set(pos w, pos h, char ch);

	Screen &move(pos w, pos h);

private:
	void check(pos w, pos h) const;

private:
	pos width;
	pos height;
	pos cursor;
	string data;
};

Screen &Screen::operator=(const Screen &other)
{
	if (&other == this)	//防止自赋值
		return *this;

	width = other.width;
	height = other.height;
	cursor = other.cursor;
	data = other.data;
	return *this;
}

char Screen::get() const
{
	return data[cursor];
}

typedef string::size_type pos;

void Screen::check(pos w, pos h) const
{
	if (w >= width || h >= height)
		throw out_of_range("out of range !");
}

char Screen::get(pos w, pos h) const
{
	check(w, h);
	pos index = h * width + w;
	return data[index];
}

Screen &Screen::set(char ch)
{
	data[cursor] = ch;
	return *this;
}

Screen &Screen::set(pos w, pos h, char ch)
{
	check(w, h);
	pos index = h * width + w;
	data[index] = ch;
	return *this;
}

Screen &Screen::move(pos w, pos h)
{
	check(w, h);
	cursor = h * width + w;
	return *this;
}


/*************************************************/
class WinManager
{
public:
	WinManager() :
		wins(1, Screen('*')){}

	typedef vector<Screen>::size_type Screen_Index;
	Screen &select_Screen(Screen_Index index); 

	void add_Screen(const Screen &new_screen);

	void display(ostream &out, Screen &sc) const;

	void redisplay();

	void clear(Screen_Index index);
private:
	void check(Screen_Index index) const;

private:
	vector<Screen>	wins;
	
};

void WinManager::redisplay()
{
	for (auto screen : wins)
	{
		display(cout, screen);
	}
}

void WinManager::check(Screen_Index index) const
{
	if (index >= wins.size())
		throw out_of_range("no such Screen !");
}

Screen &WinManager::select_Screen(Screen_Index index)
{
	return wins[index];
}

void WinManager::add_Screen(const Screen &new_Screen)
{
	wins.push_back(new_Screen);
}

void WinManager::clear(Screen_Index index)
{
	Screen &sc = wins[index];
	fill(sc.data.begin(), sc.data.end(), ' ');
}

void WinManager::display(ostream &out, Screen &sc) const
{
	system("clear");
	int cursor = sc.cursor;
	pos cursor_x = cursor / sc.width;
	pos cursor_y = cursor % sc.width;
	for (int r = 0; r < sc.height; ++r)
	{
		for (int c = 0; c < sc.width; ++c)
		{
			if(cursor_x == c && cursor_y == r)
				out << '#';
			else
				out << sc.data[cursor_y * sc.width + cursor_x];
		}
		out << endl;
	}
}

void record_keys()
{
	WinManager winMg;
	char key;
	size_t last_x = 0;
	size_t last_y = 0;
	while (cin >> key)
	{
		if (key == 'q')
			break;
		Screen new_screen;	//每次按键后产生一个新的Screen
		switch (key)
		{
			case 'j':
				last_x += 1;
				break;
			case 'k':
				last_x -= 1;
				break;
			case 'l':
				last_y += 1;
				break;
			case 'h':
				last_y -= 1;
				break;
			default:
				break;
		}
		new_screen.move(last_x, last_y);
		winMg.display(cout, new_screen);
		winMg.add_Screen(new_screen);
	}
	cout << "是否要回放(y/n)？" << endl;
	char selection;
	cin >> selection;
	if (selection == 'y')
	{
		winMg.redisplay();
	}
}

int main()
{
	//WinManager winMg;
	//winMg.select_Screen(0).print(cout);
	record_keys();
	return 0;
}
