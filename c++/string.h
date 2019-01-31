#include<iostream>
#include<cstring>


using std::ostream;

class String
{
friend	ostream &operator<<(ostream &os, const String &str);

public:
	String(const char *str = NULL);
	String(const String &other);
	~String();
	String &operator=(const String &other);

private:
	char *m_data;
};

ostream &operator<<(ostream &os, const String &str)
{
	os << str.m_data;

	return os;
}
