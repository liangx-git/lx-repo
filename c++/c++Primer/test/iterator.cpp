#include<iostream>
#include<list>
#include<iterator>
#include<vector>
#include<algorithm>
#include<numeric>
#include<string>
#include<fstream>

using namespace std;

void print_arr(vector<int>::const_iterator cbegin, vector<int>::const_iterator cend)
{
	//for (auto val : arr)
	//	cout << val << " ";
	copy(cbegin, cend, ostream_iterator<int>(cout, " "));
	cout << endl;
}

void test()
{
	/*
	istream_iterator<int> is_it_begin(cin), is_it_end;
	list<int> arr(is_it_begin, is_it_end);
	print_arr(arr.cbegin(), arr.cend());

	//list<int> arr{1, 2, 3, 4, 5};
	list<int> arr_cp_1;
	copy(arr.cbegin(), arr.cend(), back_inserter(arr_cp_1));
	print_arr(arr_cp_1.begin(), arr_cp_1.end());
	
	list<int> arr_cp_2;
	auto insert_it = back_inserter(arr_cp_2);
	for (auto val : arr)
		*insert_it = val;
	print_arr(arr_cp_2.begin(), arr_cp_2.end());

	list<int> arr_cp_3;
	copy(arr.cbegin(), arr.cend(), front_inserter(arr_cp_3));
	print_arr(arr_cp_3.begin(), arr_cp_3.end());

	copy(arr.cbegin(), arr.cend(), inserter(arr_cp_3, arr_cp_3.begin()));
	print_arr(arr_cp_3.begin(), arr_cp_3.end());

	list<int> arr_cp_4;
	copy(arr.cbegin(), arr.cend(), inserter(arr_cp_4, arr_cp_4.end()));
	print_arr(arr_cp_4.begin(), arr_cp_4.end());

	string words = "I am groot, I am groot";
	auto index_it = find(words.begin(), words.end(), ',');
	copy(words.begin(), index_it, ostream_iterator<char>(cout));
	cout << endl;
	
	istream_iterator<int> cin_begin(cin), cin_end;
	ostream_iterator<int> cout_begin(cout);
	copy(cin_begin, cin_end, cout_begin);
	*/

	string file_path("./arr.txt");
	ifstream fin(file_path);
	vector<int> arr;
	//cout << "请输入数组元素：" << endl;
	istream_iterator<int> cin_begin(fin), cin_end;
	copy(cin_begin, cin_end, back_inserter(arr));
	cout << "未排序前：" << endl;
	print_arr(arr.cbegin(), arr.cend());

	cout << "排序后：" << endl;
	sort(arr.begin(), arr.end());
	print_arr(arr.cbegin(), arr.cend());

	cout << "查重排序后：" << endl;
	auto uni_end = unique(arr.begin(), arr.end());
	print_arr(arr.cbegin(), arr.cend());

	cout << "去重后：" << endl;
	arr.erase(uni_end, arr.end());
	print_arr(arr.cbegin(), arr.cend());

	cout << "倒序输出：" << endl;
	vector<int> arr_temp;
	reverse_copy(arr.begin(), arr.end(), back_inserter(arr_temp));
	print_arr(arr_temp.cbegin(), arr_temp.cend());

	cout << "请输入要删除的元素：";
	int input;
	cin.clear();
	cin >> input;
	auto ret = remove_if(arr.begin(), arr.end(), [input](int i){ return i == input;}); 
	if(ret != arr.end())
	{
		arr.erase(ret, arr.end());
		print_arr(arr.begin(), arr.end());	
	}
	else
	{
		cout << "不存在该元素！" << endl;
	}

}

int main()
{
	test();
	return 0;
}
