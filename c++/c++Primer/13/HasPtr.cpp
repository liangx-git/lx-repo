#include<iostream>
#include<string>

using namespace std;

class HasPtr
{

public:
	typedef size_t Ptr_Count;

	//一般构造函数
	HasPtr(const string &str = string()) : 
		data(new string(str)), count(new Ptr_Count(1)){}
	
	//拷贝构造函数
	HasPtr(const HasPtr &rhs) :
		data(rhs.data), count(rhs.count) { ++*count; }

	//拷贝赋值运算符
	HasPtr &operator=(HasPtr &rhs);

	//析构函数
	~HasPtr();

	Ptr_Count ptr_count() const;

private:
	string *data;
	Ptr_Count *count;
};

HasPtr &HasPtr::operator=(HasPtr &rhs)
{
	//通过先递增右侧运算对象的计数器，避免自赋值
	++*rhs.count;
	if (--count == 0)
	{
		delete data;
		delete count;
	}
	count = rhs.count;
	data = rhs.data;
	return *this;
}

HasPtr::~HasPtr()
{
	if (--*count == 0)
	{
		delete count;
		delete data;
	}

}

typedef size_t Ptr_Count;
Ptr_Count HasPtr::ptr_count() const
{
	return *count;
}

int main()
{

	HasPtr hp("string");
	cout << "hp : " << hp.ptr_count() << endl;
	HasPtr hp2(hp);
	cout << "hp2 : " << hp2.ptr_count() << endl;
	HasPtr hp3("aaaa");
	cout << "hp3 : " << hp3.ptr_count() << endl;
	hp3 = hp2;
	cout << "after hp3 = hp2, hp : " << hp.ptr_count() << ", hp2 : " << hp2.ptr_count() << ", hp3 : " << hp3.ptr_count() << endl;

	return 0;
}
