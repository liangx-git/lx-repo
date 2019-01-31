#include<iostream>
#include<vector>
#include<memory>
#include<initializer_list>
#include<string>
#include<iterator>


using namespace std;

class StrBolb
{
friend ostream &print_StrBolb(ostream &out, const StrBolb &strBo);

friend class StrBolbPtr;

public:
	//默认构造函数
	StrBolb();

	//列表初始化参数的构造函数
	StrBolb(const initializer_list<string> &il);

	//数组初始化
	StrBolb(const vector<string> &arr);
		
	//使用合成拷贝构造函数
	StrBolb(const StrBolb &other) = default;
	
	//使用合成拷贝赋值运算符
	StrBolb& operator=(const StrBolb &other) = default;
	
	//使用合成析构函数
	~StrBolb() = default;
	
	//获取容器大小
	typedef vector<string>::size_type size_type;
	size_type size() const;

	bool empty() const ;

	string &front();

	//重载front
	const string &front() const;

	string &back();

	//重载back
	const string &back() const;
	
	void push_back(const string &str);

	void pop_back();

private:
	//检查下标是否越界
	void check(size_type i, const string &msg) const;
	
private:
	shared_ptr<vector<string>> data;	
};

StrBolb::StrBolb() : data(make_shared<vector<string>>()){}

StrBolb::StrBolb(const initializer_list<string> &il) 
	: data(make_shared<vector<string>>(il)) {};

StrBolb::StrBolb(const vector<string> &arr) 
	: data(make_shared<vector<string>>(arr.cbegin(), arr.cend())){}

typedef vector<string>::size_type size_type;
size_type StrBolb::size() const
{
	return data -> size();
}

bool StrBolb::empty() const
{
	return data -> empty();
}

void StrBolb::check(size_type i, const string &msg) const
{
	if (i >= size())
		throw out_of_range(msg);
}

const string& StrBolb::front() const
{
	check(0, "front on empty StrBolb!");
	return data -> front();
}

string& StrBolb::front()
{
	//为了避免代码重复，使用强制类型转换，在no-const重载函数中调用const版本函数
	//内转换是将this指针转为const型（安全）使得可以调用const版本front函数
	//外层转换将const返回值转为no-const
	return const_cast<string &>(
			static_cast<const StrBolb &>(*this).front());
}

const string& StrBolb::back() const
{
	check(0, "back on empty StrBolb!");
	return data -> back();
}

string& StrBolb::back()
{
	return const_cast<string &>(
			static_cast<const StrBolb &>(*this).back());
}

void StrBolb::push_back(const string &str)
{
	data -> push_back(str);
}

void StrBolb::pop_back()
{
	check(0, "pop_back on empty StrBolb!");
	data -> pop_back();
}


ostream &print_StrBolb(ostream &out, const StrBolb &strBo)
{
	for (auto val : *(strBo.data))
		out << val << " ";
	return out;
}

vector<string> create_vector_from_istream(istream &in)
{
	istream_iterator<string> is_iter_begin(cin),is_iter_end;
	return vector<string>(is_iter_begin, is_iter_end);
}

//*****************************StrBolbPtr**********************************************
class StrBolbPtr
{
public:
	StrBolbPtr() : curr(0){};
	StrBolbPtr(const StrBolb &sb, size_t sz = 0) : wptr(sb.data), curr(sz){};

	string &deref() const;
	StrBolbPtr& incr();
private:
	shared_ptr<vector<string>> check(size_t i, const string &msg) const;

private:
	weak_ptr<vector<string>> wptr;
	size_t curr;
};

shared_ptr<vector<string>> StrBolbPtr::check(size_t i, const string &msg) const
{
	auto ret = wptr.lock();
	if (!ret)
		throw runtime_error("unbound StrBolb!");
	if (i >= ret -> size())
		throw out_of_range(msg);
	return ret;
}

string &StrBolbPtr::deref() const
{
	auto ret = check(curr, "dereference past end");
	return (*ret)[curr];
}

StrBolbPtr &StrBolbPtr::incr()
{
	check(curr, "increment past end of StrBolbPtr");
	++curr;
	return *this;
}

int main()
{
	StrBolb sb{"aa", "bb", "cc", "dd"};
	print_StrBolb(cout, sb) << endl;
	return 0;
}
