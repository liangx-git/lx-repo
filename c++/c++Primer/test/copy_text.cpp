#include<iostream>
#include<string>

using namespace std;

class HasPtr
{
public:
	HasPtr(const string &s = string()) : p(new string(s)), i(0){}
	HasPtr(const HasPtr &other) : p(new string(*(other.p))), i(other.i){};
	~HasPtr()
	{
		if (p != nullptr)
		{
			delete p;
			p = nullptr;
		}
		
	}
	
	void Print()
	{
		cout << *p << " " << i << endl;
	}
private:
	string *p;
	int i;
};


int main()
{

	HasPtr s1("asdfa");
	s1.Print();
	HasPtr s2(s1);
	s2.Print();

	return 0;
}
