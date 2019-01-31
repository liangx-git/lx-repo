#include<iostream>
#include<algorithm>
#include<numeric>
#include<vector>
#include<list>
#include<set>
#include<iterator>


using namespace std;

int main()
{
	/*
	vector<int> arr{1, 2, 3, 4, 5, 6, 7};
	int sum = accumulate(arr.begin(), arr.end(), 0);
	cout << sum << endl;
	*/

	vector<string> s1{"aa", "bb", "cc"};
	list<string> s2{"aa", "bb", "cc"};
	set<string> s3{"aa", "bb", "cc"};


	if (equal(s3.cbegin(), s3.cend(), s1.cbegin()))
		cout << "s1 == s3" << endl;
	else
		cout << "s1 != s3" << endl;

	fill(s1.begin(), s1.end(), "ok");
	for (auto val : s1) 
		cout << val << " ";
	cout << endl;

	fill_n(s1.begin(), s1.size(), "ko");
	for (auto val : s1)
		cout << val << " ";
	cout << endl;

	vector<int> init{1, 2, 3, 4, 5, 6};
	vector<int> arr;
	/*
	auto insert_ite = back_inserter(arr);
	for (auto val : init)
		*insert_ite++ = val;

	for (auto val : arr)
		cout << val << " ";
	cout << endl;
 	*/
	//fill_n(back_inserter(arr), init.size(), 6);
	copy(init.cbegin(), init.cend(), back_inserter(arr));
	for (auto val : arr)
		cout << val << " ";
	cout << endl;
	
	return 0;
}
