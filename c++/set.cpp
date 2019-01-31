#include<iostream>
#include<vector>


using std::cout;
using std::cin;
using std::endl;
using std::vector;



class Set
{
public:
	Set(int n = 0) : m_arr((n + 7) / 8), m_size(n){};
	
	~Set(){};

	//将index的元素插入到集合
	bool Insert(int index);

	//将index的元素从集合中删除
	bool Remove(int index);

	//在集合中查找index的元素
	bool Find(int index);
	
	//输出集合中元素
	void Print();

private:
	vector<int> m_arr;
	int m_size;

};


bool Set::Insert(int index)
{
	if (index >= 0 && index < m_size)
	{
		//index >> 3得到数组下标，index & 07)表示对8取模
		m_arr[index >> 3] |= (1 << (index & 07));
		
		return true;
	}
	return false;
}


bool Set::Remove(int index)
{
	if (index >= 0 && index < m_size)
	{
		m_arr[index >> 3] &= ~(1 << (index & 07));

		return true;
	}

	return false;
}


bool Set::Find(int index)
{
	if (index >= 0 && index < m_size)
	{
		if (m_arr[index >> 3] & (1 << (index & 07)))
			return true;
	}

	return false;
}

void Set::Print()
{
	for (int i = 0; i < m_size; ++i)
	{
		if (m_arr[i >> 3] & (1 << (i & 07)))
		{
			cout << i;
			if (i + 1 < m_size)
				cout << ",";
		}
	}
	cout << endl;
}

int main()
{

	cout << "输入位向量的位数：";
	int n;
	cin >> n;
	Set set(n);
	while (true)
	{
		cout << "1.插入元素" << endl;
		cout << "2.删除元素" << endl;
		cout << "3.输出元素" << endl;
		cout << "4.推出程序" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			cout << "输入元素下标：";
			int n;
			cin >> n;
			cout << endl;
			set.Insert(n);
		}
		else if (select == 2)
		{
			cout << "输入元素下标：";
			int n;
			cin >> n;
			cout << endl;
			set.Remove(n);
		}
		else if (select == 3)
		{
			set.Print();
		}
		else
			exit(0);
	}


	return 0;
}
