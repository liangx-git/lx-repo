#include<iostream>
#include<string>
#include<vector>
#include<initializer_list>
#include<memory>

using namespace std;

class StrBlobPtr;

class StrBlob
{
	friend class StrBlobPtr;
public:
	StrBlob();
	StrBlob(initializer_list<string> il);
	~StrBlob();

	typedef vector<string>::size_type size_type;
	vector<string>::size_type size() const;

	bool is_empty() const;
	
	//添加和删除元素
	void push_back(const string& str);
	void pop_back();

	//元素访问
	string & front();
	string & back();

	StrBlobPtr begin();
	StrBlobPtr end();

private:
	void check(size_type i, const string &msg) const;

private:
	shared_ptr<vector<string>> data;
};

class StrBlobPtr
{
public:
	StrBlobPtr() : curr(0){};
	StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz){};
	~StrBlobPtr();
	string& deref() const;
	StrBlobPtr& incr();

private:
	shared_ptr<vector<string>> check(size_t, const string &msg) const;

private:
	weak_ptr<vector<string>> wptr;
	size_t curr;
};



StrBlob::StrBlob() : data(make_shared<vector<string>>()){}

StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}

StrBlob::~StrBlob(){}

vector<string>::size_type StrBlob::size() const
{
	return data -> size();
}

bool StrBlob::is_empty() const
{
	return data -> empty();
}

void StrBlob::check(size_type i, const string &msg) const
{
	if (i <= data -> size())
		throw out_of_range(msg);
}

string & StrBlob::front()
{
	check(0, "front on the empty StrBlob");
	return data -> front();
}

string & StrBlob::back()
{
	check(0, "back on the empty StrBlob");
	return data -> back();
}

void StrBlob::push_back(const string &str)
{
	check(0, "push_back on the empty StrBlob");
	data -> push_back(str);
}

void StrBlob::pop_back()
{
	check(0, "pop_back on the empty StrBlob");
	data -> pop_back();
}

string& StrBlobPtr::deref() const
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
	check(curr, "increment past en of StrBlobptr");
	++curr;
	return *this;
}

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const
{
	auto ret = wptr.lock();
	if (!ret)
		throw runtime_error("unbound StrBlobPtr");
	if (i >= ret -> size())
		throw out_of_range(msg);
	return ret;
}


int main()
{
	int n = 10;
	allocator<string> alloc;
	auto p = alloc.allocate(n);
	alloc.construct(p, n, 's');
	cout << *p << endl;
	alloc.destroy(p);
	alloc.deallocate(p, n);
	return 0;
}
