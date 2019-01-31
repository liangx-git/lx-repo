#include<iostream>
#include<vector>
#include<string>


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

void BignumMultiply(const string &num1, const string &num2, string &result)
{
	//循环相乘并累加，但先不进位
	vector<int> temp_res(num1.size() + num2.size());
	for (int i = 0; i < num1.size(); ++i)
	{
		int n1 = num1[i] - '0';
		for (int j = 0; j < num2.size(); ++j)
		{
			int n2 = num2[j] - '0';
			temp_res[i + j + 1] += n1 * n2;
		}
	}

	//对结果进位
	for (int i = num1.size() + num2.size() - 1; i > 0; --i)
	{
		temp_res[i - 1] += temp_res[i] / 10;
		temp_res[i] %= 10;
	}

	//将vector转为string
	if (!result.empty()) result.clear();
	int i = temp_res[0] == 0 ? 1 : 0;
	while (i < temp_res.size())
	{
		result += temp_res[i] + '0';
		++i;
	}
	return;
}


int main()
{

	string num1 = "1234";
	string num2 = "56789";
	string result;

	BignumMultiply(num1, num2, result);

	cout << "1234 * 56789 = " << result <<endl;

	return 0;
}
