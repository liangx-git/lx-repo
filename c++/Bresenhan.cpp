#include<iostream>
#include<vector>
#include<utility>
#include<math.h>
#include<algorithm>


using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::make_pair;


//画线
void Bresenhan(int x0, int y0, int x1, int y1, vector<pair<int, int>> &vec)
{
	vec.clear();

/*	//先输出开始坐标
	vec.push_back(make_pair(x0, y0));

	double dx = (x1 - x0);	//x方向偏移量
	double dy = (y1 - y0);	//y方向偏移量
	double k = dy / dx;	//斜率


	cout << k << endl;

	//计算x增量后对应的y值
	for (int i = 1; i < x1 - x0; ++i)
	{
		double yi = y0 + i * k;

		if (yi + 0.5 > int(yi) + 1)
			vec.push_back(make_pair(x0 + i, yi + 1));	//交点落在格子中点之上
		else
			vec.push_back(make_pair(x0 + i, yi));	//交点落在格子中点之下
	}

	//最后输出终点左边
	vec.push_back(make_pair(9, 18));
*/

	vec.push_back(make_pair(x0, y0));

	int dx = x1 - x0;
	int dy = y1 - y0;
	int dx2 = dx << 1;
	int dy2 = dy << 1;
	cout << dx2 << " " << dy2 << endl;
	int inc;
	
	//直线斜率小于1
	if (abs(dx) > abs(dy))
	{
		inc = -dx;
		int len = x1 - x0;
		for (int i = 1; i < len; ++i)
		{
			inc += dy2;	//等式右边原为1 * k,即dy/dx,现在等式两边同承dx2
			if (inc > 0)
				vec.push_back(make_pair(x0 + i, vec[i].second + 1));
			else
				vec.push_back(make_pair(x0 + i, vec[i].second));

			inc -= dx2;
		}
	}

	//斜率大于1
	else
	{
		inc = -dy;
		int len = y1 - y0;
		for (int i = 1; i < len; ++i)
		{
			inc += dx2;	//等式右边原为1 * k,即dx/dy,现在等式两边同承dy2
			cout << "i = " << i << " inc = " << inc << endl;
			if (inc > 0)
				vec.push_back(make_pair(vec[i - 1].first + 1, y0 + i));
			else
				vec.push_back(make_pair(vec[i - 1].first , y0 + i));

			inc -= dy2;
			cout << "i = " << i << " inc` = " << inc << endl;
		}
	}

	vec.push_back(make_pair(x1, y1));
	
	return;

}


//画半圆
void DraHalfCircle(int x, int y, int r, vector<pair<int, int>> &vec)
{
	vec.clear();
	
	double dr = r * r;
	for (int i = 0; i < r; ++i)
	{
		double dy = sqrt(dr - ((r - i) * (r - i)));

		cout << "i = " << i << ", dy = " << dy <<endl;
		int yi = (dy + 0.5 > int(dy) + 1) ? (int(dy) + 1) : int(dy);
		vec.push_back(make_pair(x + i - r, yi + y));
	}

	for (int i = 0; i < r; ++i)
	{
		vec.push_back(make_pair(x + i, vec[r - 1 -i].second));
	}
}

int main()
{

	vector<pair<int, int>> vec;
	Bresenhan(1, 3, 9, 18, vec);

	for (auto val : vec)
	{
		cout << "(" << val.first << ", " << val.second << ") "; 
	}
	cout << endl;

	DraHalfCircle(3, -2, 12, vec);
	for (auto val : vec)
		cout << "(" << val.first << ", " << val.second << ") "; 
	cout << endl;
	
	for (int i = 0; i < 24; ++i)
	{
		for (int j = 0; j < 12; ++j)
		{
			if (std::find(vec.begin(), vec.end(), make_pair(i - 9, j - 2)) != vec.end())
				cout << '*';
			else
				cout << ' ';
		}
		cout << endl;
	}


	

	return 0;
}
