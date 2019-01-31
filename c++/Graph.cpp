#include<iostream>
#include<vector>
#include<queue>

#define END -1

using std::cin;
using std::cout;
using std::endl;
using std::ends;
using std::vector;
using std::queue;


class Graph
{
public:
	Graph(){};
	~Graph(){};

	//使用默认数据初始化图
	void Init();

	//创建图
	void Create();

	//输出邻接矩阵
	void PrintArcs();

	//输出顶点序列
	void PrintVexs();

	//使用递归方法深度优先遍历输出图的结点
	void DefOrdPrintRecursive(int vex);

	//宽度优先遍历输出图的结点
	void BorOrdPrint(int vex);



private:
	//查找值对应结点在vexs数组中下标,查找失败返回-1
	int Search(int val);

	//获取该当前结点可到达的第一个结点（依据vexs表顺序）
	int FirstAdjacent(int vex);

	//依次获得获当前结点parVex可到达的下个结点，除了第一个结点.
	int NextAdjacent(int parVex, int preVex);

private:

	int m_len; 	//顶点数量
	vector<int> m_vexs;	//顶点表
	vector<vector<int>> m_arcs;	//边表
	vector<int> m_state;	//记录图结点的访问状态，1表示已经访问过，0表示未访问过
};


int Graph::Search(int key)
{
	for (int i = 0; i < m_vexs.size(); ++i)
	{
		if (m_vexs[i] == key)
			return i;
	}
	return -1;
}


int Graph::FirstAdjacent(int vex)
{
	if (vex < 0 || vex >= m_len)
		return END;

	for (int i = 0; i < m_len; ++i)
	{
		if (m_arcs[vex][i] == 1 && m_state[i] == 0)
			return i;
	}

	return END;
}


int Graph::NextAdjacent(int parVex, int preVex)
{
	if (parVex < 0 || parVex >= m_len)
		return END;

	for (int i = 0; i < m_len; ++i)
	{
		if (m_arcs[parVex][i] == 1 && i != preVex
				&& m_state[i] == 0)
			return i;
	}

	return END;
}


void Graph::Init()
{
	//初始化值
	m_len = 9;
	vector<int> initVexs{0, 1, 2, 3, 4, 5, 6, 7, 8};
	vector<vector<int>> initArcs = {{0, 1, 0, 1, 1, 0, 0, 0, 0}, 
					{0, 0, 0, 0, 0, 1, 0, 0, 0},
					{0, 0, 0, 0, 0, 0, 0, 1, 0},
					{0, 0, 0, 0, 0, 0, 0, 0, 1},
					{0, 0, 1, 0, 0, 0, 0, 0, 0},
					{0, 0, 0, 0, 0, 0, 0, 0, 0},
					{0, 0, 0, 0, 0, 0, 0, 0, 0},
					{0, 0, 0, 0, 0, 0, 1, 0, 0},
					{0, 0, 0, 0, 0, 0, 0, 0, 0}};
	
	//使用初始值初始化m_vexs
	m_vexs.resize(m_len);
	m_vexs.assign(initVexs.begin(), initVexs.end());

	//使用初始值初始化m_arcs
	m_arcs.resize(m_len);
	for (auto &val : m_arcs)
		val.resize(m_len);
	m_arcs.assign(initArcs.begin(), initArcs.end());

	//初始化m_state
	m_state.resize(m_len, 0);
}


void Graph::Create()
{
	if (m_len != 0)
	{
		m_vexs.clear();
		m_arcs.clear();
	}


	cout << "请输入顶点信息(ctrl + d结束输入)" << endl;
	int n;
	while (cin >> n)
	{
		m_vexs.push_back(n);
	}

	//初始化边表信息
	m_len = m_vexs.size();
	m_arcs.resize(m_len);
	for (auto &val : m_arcs)
		val.resize(m_len, 0);

	//初始化结点状态表
	m_state.resize(m_len, 0);

	cout << endl << "请输入边表信息(ctrl + d结束输入)" << endl;
	cin.clear();
	int vex1, vex2;
	while (cin >> vex1 >> vex2)
	{
		int row, col;
		for (auto val : m_vexs)
		{
			if (val == vex1)
				row = val;
			else if (val == vex2)
				col = val;
		}

		m_arcs[row][col] = 1;
	}
}


void Graph::PrintArcs()
{
	for (int i = 0; i < m_len; ++i)
	{
		for (int j = 0; j < m_len; ++j)
		{
			cout << m_arcs[i][j] << " ";
		}
		cout << endl;
	}
}


void Graph::DefOrdPrintRecursive(int vex)
{

	if (vex < 0 || vex >= m_len)
		return;

	//输出当前结点信息
	cout << vex << " ";	
	m_state[vex] = 1;

	for (int i = FirstAdjacent(vex); i != END; i = NextAdjacent(vex, i))
		DefOrdPrintRecursive(i);

	if (vex == 0)
		cout << endl;

	return;
}

void Graph::BorOrdPrint(int vex)
{
	queue<int> que;
	que.push(vex);

	while (!que.empty())
	{
		int t = que.front();
		que.pop();
		cout << t << " ";
		m_state[t] = 1;

		for (int i = FirstAdjacent(t); i != END; i = NextAdjacent(t, i))
		{
			que.push(i);
		}
	}
	cout << endl;

	return;
}


void Graph::PrintVexs()
{
	for (auto val : m_vexs)
		cout << val << " ";
	cout << endl;
}

int main()
{
	Graph g;
	//g.Create();
	g.Init();

	cout << "顶点序列：" << endl;
	g.PrintVexs();
	cout << "邻接矩阵：" << endl;
	g.PrintArcs();

	//cout << "从根结点0开始深度优先遍历图并输出" << endl;
	//g.DefOrdPrintRecursive(0);

	cout << "宽度优先遍历输出：" << endl;
	g.BorOrdPrint(0);

	return 0;
}
