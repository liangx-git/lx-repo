#include<iostream>
#include<cstring>

class String
{
public:
	String(const char *str = NULL);
	String(const String &other);
	~String();
	String &operator=(const String &other);
private:
	char *m_data;
};



String::String(const char *str)
{
	if (str == NULL)
	{	
		m_data = new char[1];
		m_data[0] = '\0';	//对于默认参数，开辟一个字节内存并赋值‘\0’
	}
	else
	{
		size_t len = strlen(str);
		m_data = new char[len + 1];
		strcpy(m_data, str);
		m_data[len] = '\0';
	}
}


String::String(const String &other)
{
	size_t len = strlen(other.m_data);
	m_data = new char[len + 1];
	strcpy(m_data, other.m_data);
	m_data[len] = '\0';
}

String::~String()
{
	delete[] m_data;
}

String &String::operator=(const String &other)
{
	if (this == &other)
		return this;

	if (m_data)
		delete[] m_data;	//回收之前开辟的空间
	
	size_t len = strlen(other.m_data);
	m_data = new char[len + 1];
	strcpy(m_data, other.m_data);
	m_data[len] = '\0';
	
	return *this;
	
}
