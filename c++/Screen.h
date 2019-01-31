#include<iostream>
#include<vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


class Screen
{
public:
	using pos = string::size_type;	//size_type别名
	
	Screen() = default;	//当类中声明了非默认构造函数时，需要显示声明默认构造函数
	Screen(pos ht, pos wh, char c) : height(ht), width(wh), contents(ht * wh, c) {}
	
	//读取光标处的字符
	char get() const { return contents[cursor]; }
	
	//函数重载
	inline char get(pos r, pos c) const;
	
	Screen &move(pos r, pos c) ;
	inline Screen &set(char ch);
	inline Screen &set(pos r, pos c, char ch);
	const Screen &display(std::ostream &os)const;
	Screen &display(std::ostream &os);

private:
	void do_display(std::ostream &os) const { os << contents[cursor];}

private:
	pos cursor = 0;
	pos height = 0, width = 0;
	string contents;

};

class WindowMgr
{
public:
	
private:
	vector<Screen> screens{Screen(24, 80, '#')};
};
