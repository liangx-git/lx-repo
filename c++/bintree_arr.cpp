#include<iostream>
#include<string>
#include<queue>
#include<stack>
#include<exception>

#define MAXVALUE 10000

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::queue;
using std::stack;
using std::pair;
using std::make_pair;
using std::exception;

void CreateTree(const vector<int> &preArr, const vector<int> &inArr, vector<int> &tree, int index, int pre_l, int pre_r, int in_l, int in_r)
{
	if (pre_l == pre_r)
	{
		tree[index++] = preArr[pre_l];
		return;
	}
	if (pre_l < pre_l)
	{
		tree[index++] = -1;
	}
	
	for (int i = 0; i < in_r - in_l; ++i)
	{
		if (preArr[pre_l] == inArr[i])
		{
			//当结点i存在左子树时
			int llen = i;
			if (i > 0)
				CreateTree(preArr, inArr, tree, index * 2 + 1, pre_l + 1, pre_l + llen, in_l, in_l + llen - 1);
			
			//当结点i存在右子树
			int rlen = (in_r - in_l) - i;
			if (rlen > 0)
				CreateTree(preArr, inArr, tree, index * 2 + 2, pre_l + i + 1, pre_l + i + rlen, in_l + rlen + 1, in_r);
			
			break;
		}
		
	}

}



void PrintBinTree(const vector<int> &tree)
{
	for (auto val : tree)
	{
		if (val != -1)
			cout << val << " ";
	}
	cout << endl;

}

/************************大根堆的实现***************************/

class Heap
{
public:
	Heap(int n = 0) : m_arr(n), m_size(n), m_index(0){};
	~Heap(){};

	//查看堆是否为空
	bool IsEmpty();
	
	//宽度优先输出堆中元素
	void WidOrdPrint();

	//插入新元素，从堆尾部开始插入
	void Insert(int val);
	
	//返回堆顶元素
	int Front();

	//将堆顶元素弹出
	void Pop();

	
private:
	vector<int> m_arr; 	//存储堆中元素
	int m_size;	//堆的容量
	int m_index;	//当前堆尾元素下个位置下标
};



bool Heap::IsEmpty()
{
	return m_index == 0;

}

void Heap::WidOrdPrint()
{
	queue<pair<int, int>> q;
	q.push(make_pair(0, m_arr[0]));
	int i = 0;
	while (!q.empty())
	{
		cout << q.front().second;
		i = q.front().first;
		q.pop();
		if (i < m_index - 1)
			cout << ',';

		if (2 * i + 1 < m_index)
			q.push(make_pair(2 * i + 1, m_arr[2 * i + 1]));
		if (2 * i + 2 < m_index)
			q.push(make_pair(2 * i + 2, m_arr[2 * i + 2]));

	}
	cout << endl;

}



void Heap::Insert(int val)
{
	//堆满
	if (m_index >= m_size)
		return;
	
	//当堆中没有元素
	if (m_index == 0)
	{
		m_arr[m_index++] = val;
		return;
	}

	//从下向上比较结点和val大小，并向上移动空位
	int i;
	for (i = m_index; i > 0 && m_arr[(i - 1) / 2] < val; i = (i - 1) / 2)
		m_arr[i] = m_arr[(i - 1) / 2];
	m_arr[i] = val;
	++m_index;
}


int Heap::Front()
{
	try
	{
		if (IsEmpty())
			throw("The heap is empty!");
		else
			return m_arr[0];


	}
	catch (exception &e)
	{
		e.what();
	}

}



void Heap::Pop()
{
	if (IsEmpty())
		return;

	int temp = m_arr[m_index - 1]; //栈存堆中尾元素

	//将位元素从上往下作比较，使得堆顶的空格下移到合适位值后将元素填入，完成堆顶元素删除
	int parent = 0;
	int child = 1;
	while (child < m_index - 1)
	{
		//选择子结点中最大元素与temp作比较
		if (child + 1 < m_index -1 && m_arr[child + 1] > m_arr[child])
			++child;
		if (temp < m_arr[child])
		{
			m_arr[parent] = m_arr[child];
			parent = child;
			child = child * 2 + 1;
		}
		else 
			break;
	}
	m_arr[parent] = temp;
	m_index = (m_index - 1 >= 0) ? (m_index - 1) : 0;

}



/*************************大根堆的实现END*****************************/




/*************************哈夫曼树*********************************/
struct Node
{
	int val;
	int parent;
	int right;
	int left;

	Node(int val = 0): val(val), parent(-1), right(-1), left(-1) {}
};


class Huffman
{
public:
	Huffman(const vector<int> &arr) : m_arr(2 * arr.size() - 1)
	{
		Init(arr);
		Create();
	};

	~Huffman(){};
	
	//初始化m_arr内存空间
	void Init(const vector<int> &arr);
	
	//创建huffman树
	void Create();

	//输出WPL
	void PrintWPL();

	//输出huffman编码
	void PrintHfCode();

	//顺序输出数组内容
	void Print();

private:
	vector<Node> m_arr;

};

void Huffman::Init(const vector<int> &arr)
{
	//根据arr初始化m_arr前n个元素的val成员
	for (int i = 0; i < arr.size(); ++i)
	{
		m_arr[i].val = arr[i];
	}
}


void Huffman::Create()
{
	int len = (m_arr.size() + 1) / 2;	//对于给定n个元素的树组构造哈夫曼树需要2*n-1个结点，所以需要循环额外构造n-1个结点
	for (int i = 0; i < len - 1; ++i)
	{
		int min_value = MAXVALUE;	//当前序列中未加入哈夫曼树权值最小结点
		int min_index;
		int next_value = MAXVALUE;	//次最小权值
		int next_index;
		//查找的范围随着i的增加而增加
		for (int j = 0; j < len + i; ++j)
		{
			//未加入huffman的最小权结点
			if ((m_arr[j].parent == -1) && (m_arr[j].val < min_value))
			{
				next_value = min_value;
				next_index = min_index;

				min_value = m_arr[j].val;
				min_index = j;
			}	
			else if((m_arr[j].parent == -1) && (m_arr[j].val < next_value))
			{
				next_value = m_arr[j].val;
				next_index = j;
			}
		}

		m_arr[min_index].parent = len + i;
		m_arr[next_index].parent = len + i;
		m_arr[len + i].val = min_value + next_value;
		m_arr[len + i].left = min_index;
		m_arr[len + i].right = next_index;
	}

}


void Huffman::PrintWPL()
{
	cout << "WPL: " << m_arr[m_arr.size() - 1].val << endl;
}

void Huffman::PrintHfCode()
{
	int len = (m_arr.size() + 1) / 2;	//len个叶结点
	for (int i = 0; i < len; ++i)
	{
		cout << m_arr[i].val << " : ";
		int j = i;
		int par = m_arr[j].parent;
		while (par != -1)
		{	
			if (m_arr[par].left == j)
				cout << 0;
			else
				cout << 1;
			j = par;
			par = m_arr[par].parent;
		}
		cout << endl;
	}

}

void Huffman::Print()
{
	int i = 0;
	for (auto v : m_arr)
	{
		cout << i++ <<" val=" << v.val << " parent=" << v.parent << " left=" << v.left << " right=" << v.right << endl;
	}
}


/*************************哈夫曼树END******************************/

int main()
{
/*	vector<int> preArr = {1, 2, 4, 7, 3, 5, 6, 8};	//前序序列
	vector<int> inArr = {4, 7, 2, 1, 5, 3, 8, 6};	//后序序列
	vector<int> tree(20);
	int index = 0;
	CreateTree(preArr, inArr, tree, index, 0, preArr.size() - 1, 0, inArr.size() - 1);
	PrintBinTree(tree);
*/

/*
	vector<int> arr{1, 2, 3, 4, 5, 6};
	Heap heap(20);
	for (auto val : arr)
		heap.Insert(val);
	heap.WidOrdPrint();

	while (true)
	{
		cout << "---选择操作---" << endl;
		cout << "1.弹出最大元素" << endl;
		cout << "2.输出最大元素" << endl;

		int select;
		cin >> select;
		if (select == 1)
		{
			heap.Pop();
			cout << "删除出堆中最大元素后，宽度优先遍历堆可得：" << endl;
			heap.WidOrdPrint();
		}
		else if (select == 2)
		{
			int val = heap.Front();
			cout << "最大元素为：" << val << endl;
		}
	}

*/

	vector<int> arr{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
	Huffman hf(arr);
	hf.Print();
	hf.PrintWPL();
	hf.PrintHfCode();
	


	return 0;
}
