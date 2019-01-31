#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


bool Check(const vector<vector<int>> &arr, int x, int y)
{
	int len = arr.size();
	for (int i = 0; i < len; ++i)
	{
		//检查y方向
		if (i != x && arr[i][y] == 1)
			return false;
		
		//检查左斜角方向
		if ((x - 1 - i >= 0) && (y - 1 - i >= 0) && arr[x - 1 - i][y - 1 - i] == 1 )
			return false;

		//检查右斜对角线
		if ((x + 1 + i < len) && (y - 1 - i >= 0) && arr[x + 1 + i][y - 1 - i] == 1)
			return false;
	}

	return true;
}

void PrintQueen(const vector<vector<int>> &arr)
{
	int len = arr.size();
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < len; ++j)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void SettleQueen(vector<vector<int>> &arr, int row)
{
	int len = arr.size();
	if (row > len - 1)
	{
		PrintQueen(arr);
		return;
	}

	for (int i = 0; i < len; ++i)
	{
		//为当前行清除数据，以免递归返回时有脏数据
		for (int j = 0; j < len; ++j)
			arr[row][j] = 0;

		if (Check(arr, row, i))
		{
			arr[row][i] = 1;
			
			SettleQueen(arr,row + 1);
		}

	}
	return;
}

int main()
{
	vector<vector<int>> arr(5, vector<int>(5, 0));
	SettleQueen(arr, 0);

	return 0;
}
