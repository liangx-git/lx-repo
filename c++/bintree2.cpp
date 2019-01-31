#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<stack>


using namespace std;


struct TreeNode
{
	int data;
	TreeNode *left;
	TreeNode *right;
	
	TreeNode(int n = 0) : data(n), left(nullptr), right(nullptr){};
};


void Print(int n)
{
	cout << n << ' ';
}

class Tree
{
public:
	Tree() : m_pRoot(nullptr){}
	
	~Tree();

	//根据中根树序和先根序列构造树
	bool Create(vector<int> &preArr, vector<int> &midArr);

	//宽度优先遍历输出
	void WidOrd();

	//先根遍历递归
	void PreOrdRec();
	
	//中根遍历递归
	void MidOrdRec();

	//后跟遍历递归
	void PostOrdRec();

	//先根遍历非递归
	void PreOrd();

	//中根遍历非递归
	void MidOrd();

	//后跟遍历非递归
	void PostOrd();

private:
	TreeNode* CreateRec(vector<int> &preArr, vector<int> &midArr, int pl, int pr, int ml, int mr);

private:
	TreeNode *m_pRoot;

};

Tree::~Tree()
{
	if (m_pRoot != nullptr)
	{
		stack<TreeNode *>ts;
		TreeNode * p = m_pRoot;
		while (p != nullptr || !ts.empty())
		{
			while (p != nullptr)
			{
				ts.push(p);
				p = (p -> left != nullptr) ? (p -> left) : (p -> right);
			}

			TreeNode *pre = ts.top();
			ts.pop();
			delete pre;	//释放内存
			p = ts.top();
			if (p -> left == pre)
			{
				p = p -> right;
				while (p != nullptr)
				{
					ts.push(p);
					p = (p -> left != nullptr) ? (p -> left) : (p -> right);
				}
			}
			
		}

	}
}

TreeNode* Tree::CreateRec(vector<int> &preArr, vector<int> &midArr, int pl, int pr, int ml, int mr)
{
	TreeNode *pTNode = nullptr;
	if (pr >= pl)
	{
		//创建新结点
		pTNode = new TreeNode(preArr[pl]);
		for (int i = ml; i <= mr; ++i)
		{
			if (midArr[i] == preArr[pl])
			{
				int mid = i;
				int llen = mid - ml;
				int rlen = mr - mid;
				pTNode -> left = CreateRec(preArr, midArr, pl + 1, pl + llen, ml, ml + mid - 1);
				pTNode -> right = CreateRec(preArr, midArr, pl + llen + 1, pr, ml + mid + 1, mr);
				break;
			}
		}
	}
	return pTNode;
}

bool Tree::Create(vector<int> &preArr, vector<int> & midArr)
{
	int len = preArr.size();
	m_pRoot = CreateRec(preArr, midArr, 0, len - 1, 0, len - 1);

	return m_pRoot;
}


void Tree::WidOrd()
{
	queue<TreeNode *> tq;
	tq.push(m_pRoot);
	TreeNode *p;
	while (!tq.empty())
	{
		p = tq.front();
		tq.pop();
		Print(p -> data);
		tq.push(p -> left);
		tq.push(p -> right);
	}
}




int main()
{
	Tree tree;
	vector<int> preArr{1, 2, 4, 5, 3, 6, 7};
	vector<int> midArr{4, 2, 5, 1, 6, 3, 7};
	if (tree.Create(preArr, midArr))
	{
		//宽度优先
		//tree.WidOrd();
	}

	return 0;
}
