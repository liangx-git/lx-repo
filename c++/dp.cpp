#include<iostream>
#include<map>
#include<utility>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::make_pair;


//递归形式
int DpFun(int n, int m)
{
	if (m == 0) 
		return 1;
	else if (n <= 0 && m > 0 
			|| m < 0)
		return 0;
	
	return DpFun(n - 1, m) + DpFun(n - 1, m - n);
}


//备忘录法
int DpFunRecord(int n, int m, map<pair<int, int>, int> &record)
{
	if (m == 0)
		return 1;
	else if (n <= 0 && m > 0
			|| m < 0)
		return 0;
	else if (record.find(make_pair(n, m)) != record.end())
		return record[make_pair(n, m)];
	else
	{
		int temp = DpFunRecord(n - 1, m, record) + DpFunRecord(n - 1, m - n, record);
		record[make_pair(n, m)] = temp;
		return temp;
	}
}



int main ()
{

	int n = 6, m = 8;
	map<pair<int, int>, int> record;
	cout << "n = " << n << ", m = " << m << " : " << DpFunRecord(6, 8, record) << endl;


	return 0;
}
