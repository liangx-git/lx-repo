#include<iostream>
#include<memory>

using namespace std;

int main()
{
	allocator<string> alloca;
	auto const p = alloca.allocate(10);
	alloca.construct(p, 5, 'a');
	//for (auto q = p; q != p + 10; ++q)
	//	cout << *q << " ";
	//cout << endl;
	auto ret = uninitialized_fill_n(p + 1, 9, "bddd");
	//uninitialized_fill(ret, p + 10, 'c');
	for (auto q = p; q != p + 10; ++q)
		cout << *q << endl;
	return 0;
}
