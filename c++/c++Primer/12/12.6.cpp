#include<iostream>
#include<vector>

using namespace std;

vector<int> *create_int_vector()
{
	return new vector<int>();
}

vector<int> *init_from_ioInput(istream &in, vector<int> *arr)
{
	cout << "请输入数组元素：" << endl;
	int input;
	while (in >> input)
	{
		arr -> push_back(input);
	}
	return arr;
}

void print_int_vector(vector<int> *arr)
{
	cout << "输出数组元素：" << endl;
	for (auto val : *arr)
		cout << val << " ";
	cout << endl;
	delete arr;
	arr = nullptr;
}


int main()
{
	auto arr = create_int_vector();
	init_from_ioInput(cin, arr);
	print_int_vector(arr);

	return 0;
}
