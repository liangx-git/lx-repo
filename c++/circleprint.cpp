#include<iostream>
#include<string>
#include<vector>


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;



void GetArrFromConsole(vector<int> &arr)
{

	/*使用一维数组保存二维数组*/

	cout << "请输入数组元素，以-1结束当前行" << endl;
	
	int val;
	int index = 0;	//当前数组下标
	while (cin >> val)
	{	
		arr.push_back(val);
		
	}
}


void PrintArr(const vector<int> &arr)
{
	for (auto val : arr)
	{
		if (val == -1)
		{
			cout << endl;
			continue;
		}

		cout << val << " ";
	}

}

//顺时针输出
void PrintArrByCirOrder(const vector<int> &arr)
{
	int rows = 0;	//行数
	int cols = 0;	//列数
	int sum = 0;
	for (auto val : arr)
	{
		//计算列数
		if (rows == 0 && val != -1)
			++cols;
		//计算行数	
		if (val == -1)
			++rows;

		if (val != -1)
			sum++;
	}

	int count = 0;	//计数当前输出的变量数量 
	int r_end = rows - 1;
	int c_end = cols - 1;
	for (int beg = 0; 2 * beg < rows && 2 * beg < cols; ++beg)
	{
		//无论何种情都会输出上面行
		for (int i = 0; i <= c_end - beg; ++i)
		{
			//由于使用的是一维数组保存二维数组，且以-1分割不同行，所以需要特别计算下标
			int index = beg * cols + beg + i + beg; //最后一个beg是-1数量	
			cout << arr[index];

			++count;
			if (count < sum)
				cout << ",";
		}
		
		//输出右边列
		if (beg < r_end)
		{
			for (int i = 0; i <= r_end - beg -1; ++i)
			{
				int index = (beg + 1 + i) * cols + c_end + (beg + 1 + i);	//最后(beg + 1 + i)是包含-1的数量
				cout << arr[index];
				++count;
				if (count < sum)
					cout << ",";
			}
		}

		//输出下面行
		if (beg < r_end && beg < c_end)
		{
			for (int i = 0; i <= c_end - beg - 1; ++i)
			{
				int index = (r_end * cols) + (c_end - 1) + r_end - i;	//最后那个r_end表示-1数量
				cout << arr[index];
				++count;
				if (count < sum)
					cout << ",";
			}
		}

		//输出左边列
		if (beg < r_end -1 && beg < c_end)
		{	
			for (int i = 0; i <= r_end - beg - 2; ++i)
			{
				int index = (r_end - 1 - i) * cols + beg + (r_end - 1 - i); //(r_end - 1 - i)表示-1数量
				cout << arr[index];
				++count;
				if (count < sum)
					cout << ",";
			}
		}

		--r_end;
		--c_end;
	}
	cout << endl;
}


int main()
{

	vector<int> arr;
	GetArrFromConsole(arr);
	PrintArr(arr);
	cout << endl;
	PrintArrByCirOrder(arr);

	return 0;
}
