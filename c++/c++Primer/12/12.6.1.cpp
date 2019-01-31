#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>


using namespace std;

shared_ptr<vector<int>> create_int_vector()
{
	return make_shared<vector<int>>();
}

void init_from_ioInput(istream &in, const shared_ptr<vector<int>> &arr)
{
	cout << "请输入数组元素：" << endl;
	int input;
	while (in >> input)
	{
		arr -> push_back(input);
	}
}

void print_int_vector(const shared_ptr<vector<int>> &arr)
{
	for (auto val : *arr)
		cout << val << " ";
	cout << endl;
}


int main()
{
	auto arr = create_int_vector();
	init_from_ioInput(cin, arr);
	auto arr2 = arr;
	if (!arr.unique())
	{
		arr.reset(new vector<int>(*arr));
	}
	reverse(arr -> begin(), arr -> end());
	cout << "输出数组arr:" << endl;
	print_int_vector(arr);
	cout << "输出数组arr2:" << endl;
	print_int_vector(arr2);
	return 0;
}
