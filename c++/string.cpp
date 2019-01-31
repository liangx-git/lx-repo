#include "string.h"



//普通构造函数
String::String(const char *str)
{
	if (str == NULL)
	{
		m_data = new char[1];
		m_data[1] = '\0';
	}
	else
	{
		size_t len = strlen(str);
		m_data = new char[len + 1];
		strcpy(m_data, str);
	}
}


//拷贝构造函数
String::String(const String &other)
{
	size_t len = strlen(other.m_data);	//此处因为是在同一个类中，所以可以调用other的私有成员
	m_data = new char[len + 1];
	strcpy(m_data, other.m_data);

}



//析构函数
String::~String()
{
	delete[] m_data;
}


//赋值操作符
String &String::operator = (const String &other)
{
	//防止自赋值，得分点
	if (this == &other)
		return *this;
	
	//释放原有的内存,得分点
	if (m_data)
		delete m_data;
	
	size_t len = strlen(other.m_data);
	m_data = new char[len + 1];
	strcpy(m_data, other.m_data);

	return *this;	//返回对象的引用，得分点
}



int main()
{
	String s1("abc");
	String s2(s1);
	String s3 = s1;

	std::cout << "s1地址：" << &s1 << " s1值：" << s1 << std::endl;
	std::cout << "s2地址：" << &s2 << " s2值：" << s2 << std::endl;
	std::cout << "s3地址：" << &s3 << " s3值：" << s3 << std::endl;
	return 0;
}
