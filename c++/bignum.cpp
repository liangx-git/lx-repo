#include<iostream>
#include<string>
#include<vector>


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


void BigNumMultiply(const string &num1, const string &num2, string &result)
{
	vector<int> temp_result(num1.size() + num2.size(), 0);	//保存临时结果	

	//在循环中暂不处理进位
	for (int i = 0; i < num1.size(); ++i)
	{
		int n1 = num1[i] - '0';
		for (int j = 0; j < num2.size(); ++j)
		{
			int n2 = num2[j] - '0';
			temp_result[i + j + 1] += n1 * n2;	//保留第一位存储来自最高位的进位 
		}
	
	}

	//处理进位
	int carrybit = 0;
	for (int i = temp_result.size() - 1; i >= 0; --i)
	{
		temp_result[i] += carrybit;
		carrybit = temp_result[i] / 10;
		temp_result[i] %= 10;
	}

	//将vector转为string
	if (!result.empty()) result.clear();
	
	int k = (carrybit != 0 ? 0 : 1);
	while(k < temp_result.size())
	{
		result += temp_result[k++] + 48;
	}


	return;
}


int main()
{
	string num1 = "12345";
	string num2 = "6789";
	string result;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;
	BigNumMultiply(num1, num2, result);
	cout << "num1 * num2 = " << result << endl;

	return 0;
}
