#include<iostream>

using namespace std;

class T
{
public:
	T(){cout << "默认构造函数" << endl;}
	T(const T &other)
	{
		i = other.i;
		cout << "拷贝构造函数" << endl;
	}
private:
	int i;
};

int main()
{
	T a;
	T b(a);
	T c = b;
	return 0;
}
