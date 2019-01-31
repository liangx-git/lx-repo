#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class Heap
{
public:
	Heap(int n = 0) : m_len(0), m_size(n + 1), m_arr(n + 1){};
	~Heap(){};
	
	//初始化堆
	void Init();

	//获取堆顶元素
	int Top();

	//插入
	bool Push(int num);

	//删除堆顶元素
	bool Pop();

	//宽度优先顺序输出堆
	void Print();

private:
	//向上调整
	void UpAdjust(int index);

	//向下调整
	void DownAdjust(int index);

private:
	int m_len;	//当前数组的使用量
	int m_size;	//数组的最大容量
	vector<int> m_arr;

};

void Heap::UpAdjust(int index)
{
	int temp = m_arr[index];
	int child = index;
	int parent = (child - 1) / 2;
	while (child > 0 && m_arr[parent] < temp)
	{
		m_arr[child] = m_arr[parent];
		child = parent;
		parent = (parent - 1) / 2;
	}
	m_arr[child] = temp;

	return;
}

void Heap::DownAdjust(int index)
{
	int temp = m_arr[index];
	int parent = index;
	int child = parent * 2 + 1;
	while (child < m_len && m_arr[child] > temp)
	{
		//右儿子比左儿子大
		if (child + 1 < m_len && m_arr[child + 1] > m_arr[child])
			++child;
		m_arr[parent] = m_arr[child];
		parent = child;
		child = child * 2 + 1;
	}
	m_arr[parent] = temp;

	return;
}

void Heap::Init()
{
	vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9};
	m_size = arr.size() * 2;
	m_arr.resize(m_size);
	for (auto val : arr)
		Push(val);
}

int Heap::Top()
{
	if (m_len != 0)
	{
		return m_arr[0];
	}
	return -1;
}

bool Heap::Push(int num)
{
	//始终保持堆尾预留一个空格，存放堆数组的容量满了后，扩容至之前的两倍
	if (m_len + 1 == m_size)
	{
		m_size = 2 * m_size;
		m_arr.resize(2 * m_size);
	}
	
	//将新元素插入到堆尾元素,并从堆尾向上调整堆，使得整体满足堆序性
	m_arr[m_len] = num;
	UpAdjust(m_len);
	++m_len;
	
	return true;
}

bool Heap::Pop()
{
	if (m_len == 0)
		return false;

	//将堆尾元素交换到堆顶，并由堆顶自下调整堆，使得满足堆序性
	m_arr[0] = m_arr[--m_len];
	DownAdjust(0);

	return true;
}

void Heap::Print()
{
	for (int i = 0; i < m_len; ++i)
		cout << m_arr[i] << " ";
	cout << endl;
}

int main()
{
	Heap hp;
	
	hp.Init();
	cout << "使用默认数据初始化堆" << endl;
	while(true)
	{
		cout << "1.插入元素" << endl;
		cout << "2.删除元素" << endl;
		cout << "3.输出堆" << endl;
		int select;
		if (cin >> select)
		{
			if (select == 1)
			{
				cout << "输入元素：";
				int element;
				cin >> element;
				cout << endl;
				if (hp.Push(element))
					cout << "插入成功" << endl;
				else
					cout << "插入失败" << endl;
			}
			else if (select == 2)
			{
				if (hp.Pop())
					cout << "删除成功" << endl;
				else 
					cout << "删除失败" << endl;
			}
			else if (select == 3)
			{
				hp.Print();
			}
			else
				break;
		}
		else 
			break;
	}
	return 0;
}
