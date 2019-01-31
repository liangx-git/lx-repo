#include<iostream>
#include<vector>
#include<queue>
#include<stack>

using namespace std;

struct TreeNode
{
	int value;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int v) : value(v), left(nullptr), right(nullptr){};
};

typedef void (*FunType)(TreeNode *);

class Tree
{
public:
	Tree(const vector<int> &arr);
	~Tree();

	void BFSPrint();

	void PreDFSPrint();

	void MidDFSPrint();

	void PostDFSPrint();

private:
	//宽度优先遍历
	void BFS(FunType fun);

	//先根遍历
	void PreDFS(FunType fun);

	//中根遍历
	void MidDFS(FunType fun);

	//后跟遍历
	void PostDFS(FunType fun);

	//创建树
	bool Init(const vector<int> &arr);

	static void PrintTreeNode(TreeNode *pTreeNode);

	static void DeleteTreeNode(TreeNode *pTreeNode);

private:
	TreeNode *m_root;
};

Tree::Tree(const vector<int> &arr)
{
	Init(arr);
}

Tree::~Tree()
{
	if (m_root != nullptr)
	{
		cout << ">>开始删除树" << endl;
		PostDFS(DeleteTreeNode);
	}
}

bool Tree::Init(const vector<int> &arr)
{
	cout << ">>开始构造二叉树" << endl;	//
	queue<TreeNode *> tq;
	m_root = new TreeNode(arr[0]);
	cout << "添加结点：" << m_root -> value << endl;	//
	tq.push(m_root);
	TreeNode *p = nullptr;
	int len = arr.size();
	for (int i = 1; i < len;)
	{
		p = tq.front();
		tq.pop();
		p -> left = new TreeNode(arr[i++]);
		cout << "添加结点：" << (p -> left) -> value << endl;	//
		tq.push(p -> left);
		if (i < len)
		{
			p ->right = new TreeNode(arr[i++]);
			cout << "添加结点：" << (p -> right) -> value << endl;	//
			tq.push(p -> right);
		}
	}
	return true;
}


void Tree::BFS(FunType fun)
{
	queue<TreeNode *> tq;
	tq.push(m_root);
	TreeNode *p;
	while (!tq.empty())
	{
		p = tq.front();
		tq.pop();
		fun(p);	//根据传入的函数指针处理树结点
		if (p -> left != nullptr)
			tq.push(p -> left);
		if (p -> right != nullptr)
			tq.push(p -> right);
	}
}

void Tree::PreDFS(FunType fun)
{
	stack<TreeNode *> ts;
	ts.push(m_root);
	TreeNode *p = nullptr;
	while (!ts.empty())
	{
		p = ts.top();
		ts.pop();
		fun(p);
		if (p -> right != nullptr)
			ts.push(p -> right);
		if (p -> left != nullptr)
			ts.push(p -> left);
	}
}

void Tree::MidDFS(FunType fun)
{
	stack<TreeNode *> ts;
	TreeNode *p = m_root;
	while (p != nullptr || !ts.empty())
	{
		while (p != nullptr)
		{
			ts.push(p);
			p = p -> left;
		}
		p = ts.top();
		ts.pop();
		fun(p);
		p = p -> right;
	}
}

void Tree::PostDFS(FunType fun)
{
	stack<TreeNode *> ts;
	TreeNode *p = m_root;
	while (p != nullptr || !ts.empty())
	{
		while (p != nullptr)
		{
			ts.push(p);
			p = (p -> left != nullptr) ? (p -> left) : (p -> right);
		}

		TreeNode *pChild = ts.top();
		ts.pop();
		fun(pChild);
		if (!ts.empty())
		{
			p = ts.top();
			if (p -> left == pChild)
				p = p -> right;
			else
				p = nullptr;
		}
	}
}

void Tree::BFSPrint()
{
	BFS(PrintTreeNode);
}

void Tree::PreDFSPrint()
{
	PreDFS(PrintTreeNode);
}

void Tree::MidDFSPrint()
{
	MidDFS(PrintTreeNode);
}

void Tree::PostDFSPrint()
{
	PostDFS(PrintTreeNode);
}

void Tree::PrintTreeNode(TreeNode *pTN)
{
	cout << pTN -> value << " ";
}

void Tree::DeleteTreeNode(TreeNode *pTN)
{
	cout << "删除结点:" << pTN -> value << endl;
	delete pTN;
}

int main()
{
	vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9};
	Tree tree(arr);
	cout << "宽度优先输出树结点:" << endl;
	tree.BFSPrint();
	cout << endl;

	cout << "先根顺序输出树结点：" << endl;
	tree.PreDFSPrint();
	cout << endl;

	cout << "中根顺序输出树结点：" << endl;
	tree.MidDFSPrint();
	cout << endl;

	cout << "后跟顺序输出树结点：" << endl;
	tree.PostDFSPrint();
	cout << endl;

	return 0;
}
