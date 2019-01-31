#include<iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;


class String
{
public:
	String(const char *str);
	String(const String &str);
	~String();
	String &operator=(const String &other);

private:
	char *m_str;
};

String::String(const char *str)
{
	if (str == nullptr)
	{
		m_str = new char[1];
		*m_str = '\0';
	}
	else
	{
		int len = strlen(str);
		m_str = new char[len + 1];
		strcpy(m_str, str);
	}
}

String::String(const String &other)
{
	int len = strlen(other.m_str);
	m_str = new char[len + 1];
	strcpy(m_str, other.m_str);
}

String::~String()
{
	if (m_str != nullptr)
		delete m_str;
}

String &String::operator=(const String &other)
{
	if (&other == this)
		return *this;

	if (m_str != nullptr)
		delete m_str;

	int len = strlen(other.m_str);
	m_str = new char[len + 1];
	strcpy(m_str, other.m_str);

	return *this;
}


int main()
{
	string s("Hello world!!!");
	decltype(s.size()) punct_cnt = 0;
	for (auto &c : s)
	{
		if (isalpha(c) && islower(c))
		{
			c = toupper(c);
		}
	}
	cout << s <<endl;


	return 1;
}
