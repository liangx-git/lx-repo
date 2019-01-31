#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<stack>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::queue;
using std::stack;



struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	
	TreeNode(int val) : val(val), left(nullptr), right(nullptr) {};
};


//创建一颗默认初始化的二叉树
TreeNode *CreateTree(const vector<int>  &arr)
{
	TreeNode *root = new TreeNode(arr[0]);
	
	//将arr放入树中
	int i = 1;
	queue<TreeNode *> q; //利用队列，广度优先顺序创建二叉树
	q.push(root);
	while (i < arr.size())
	{
		TreeNode *pTreeNode = q.front();
		q.pop();

		pTreeNode -> left = new TreeNode(arr[i++]);
		q.push(pTreeNode -> left);
		
		if (i < arr.size())
		{
			pTreeNode -> right = new TreeNode(arr[i++]);
			q.push(pTreeNode -> right);
		}
	}
	
	return root;
	
}

//根据传入的中序和先须序列实现二叉树重建
TreeNode *ReBuildBinTree(const vector<int> &inOrder, const vector<int> &preOrder, int in_l, int in_r, int pre_l, int pre_r)
{
	//递归终止条件，直到遍历完preOder
	if (pre_l > pre_r)
		return nullptr;

	//创建新结点
	TreeNode *root = new TreeNode(preOrder[pre_l]);
	
	//当前结点为叶结点时，不必构建左右子树
	if (pre_l == pre_r)
		return root;
	

	//找到中序列中根结点所在下标位置
	for (int i = 0; i <= in_r - in_l; ++i)
	{
		//找到相应的根结点
		if (inOrder[in_l + i] == preOrder[pre_l])
		{
			//该根结点存在左子树
			int llen = i;
			if (llen > 0 )
				root -> left = ReBuildBinTree(inOrder, preOrder, in_l, in_l + i - 1, pre_l + 1, pre_l + llen);
			
			//该根结点存在右子树
			int rlen = (in_r - in_l) - i;
			if (rlen > 0)
				root -> right = ReBuildBinTree(inOrder, preOrder, in_l + i + 1, in_r, pre_r - rlen + 1, pre_r);
			break;
		}
	}
	
	return root;	


}


//输出数组
void PrintArr(const vector<int> &arr)
{
	for (auto val : arr)
		cout << val << " ";
	cout << endl;
}



//宽度优先搜索
void WidOrder(TreeNode *root, vector<int> &arr)
{
	TreeNode *p = root;
	queue<TreeNode *> tq;
	tq.push(root);

	//利用队列实现先进先出的性质实现宽度优先遍历
	while (!tq.empty())
	{
		p = tq.front();
		arr.push_back(p -> val);
		tq.pop();

		if (p -> left != nullptr)
			tq.push(p -> left);
		if (p -> right != nullptr)
			tq.push(p -> right);
	}
}


//先根遍历
void PreOrder(TreeNode *root, vector<int> &arr)
{
	arr.clear();

	stack<TreeNode *> ts;
	ts.push(root);
	
	TreeNode *p;
	while (!ts.empty())
	{
		p = ts.top();
		arr.push_back(p -> val);
		ts.pop();

		if (p -> right != nullptr)
			ts.push(p -> right);
		if (p -> left != nullptr)
			ts.push(p -> left);
	}
}


//中根遍历
void InOrder(TreeNode *root, vector<int> &arr)
{
	arr.clear();

	stack<TreeNode *> ts;

	TreeNode *p = root;

	while (p != nullptr || !ts.empty())
	{
		//遍历至数的最左下角，并将经历的结点压入栈
		while (p != nullptr)
		{
			ts.push(p);
			p = p -> left;
		}

		p = ts.top();
		arr.push_back(p -> val);
		ts.pop();

		p = p -> right;
	
	}
}


//后跟遍历
void PostOrder(TreeNode *root, vector<int> &arr)
{
	arr.clear();

	stack<TreeNode *> ts;

	TreeNode *p = root;
	while ( p != nullptr || !ts.empty())
	{
	
		//以左子树由先于右子树顺序遍历到树的左下方
		while (p != nullptr)
		{
			ts.push(p);
			p = (p -> left != nullptr) ? (p -> left) : (p -> right);
		}
		
		TreeNode *pPre = ts.top();
		ts.pop();
		arr.push_back(pPre -> val);
		
		if (!ts.empty() && ts.top() -> left == pPre )
		{
			p = ts.top() -> right;
			while (p != nullptr)
			{
				ts.push(p);
				p = (p -> left != nullptr) ? (p -> left) : (p -> right);
			}
		}

	}
	
}



/**************线索二叉树*****************/

//将二叉树中序线索化
void Thread(TreeNode *pTree)
{
	stack<TreeNode *> ts;
	TreeNode *p = pTree;
	TreeNode *pre = nullptr;

	while (p != nullptr || !ts.empty())
	{
		while (p != nullptr)
		{
			ts.push(p);
			p = p -> left;
		}

		p = ts.top();
		ts.pop();

		//加入线索信息
		if (pre != nullptr)
		{
			if (pre -> right == nullptr)
				pre -> right = p;
			if (p -> left == nullptr)
				p -> left = pre;
		}

		p = p -> right;
	}
}

/******************线索二叉树end***********************/




/*******************搜索二叉树***************************/

class SearchTree
{
public:
	SearchTree() : m_root(nullptr){};
	~SearchTree(){};

	bool Search(int val, TreeNode *&pPos);

	bool Insert(int val);

	bool Remove(int val);

	bool IsEmpty();

	bool Create(const vector<int> &arr);
	
	void Print();

private:
	TreeNode *m_root;
};

bool SearchTree::Create(const vector<int> &arr)
{
	//已经创建过
	if (m_root != nullptr)
		return false;

	for (auto val : arr)
	{
		if (!Insert(val))
			return false;
	}

	return true;
}


bool SearchTree::Search(int val, TreeNode *&pPos)
{
	TreeNode *p = m_root;
	TreeNode *pre = nullptr;


	while (p != nullptr)
	{
		pre = p;
		if (val == p -> val)
		{
			pPos = p;
			return true;
		}
		else if (val < p -> val)
			p = p -> left;
		else if (val > p -> val) 
			p = p -> right;
	}
	pPos = pre;	//当在搜索树中找不到对应结点则返回合适的插入结点指针

	return false;
}


bool SearchTree::Insert(int val)
{
	TreeNode *pPos = nullptr;
	if (Search(val, pPos) == true)
		return false;	//二叉树中已经存在该值
	
	//当前搜索二叉树为空时
	if (pPos == nullptr)
		m_root = new TreeNode(val);

	//插入左子树
	else if (val < pPos -> val)
		pPos -> left = new TreeNode(val);
	
	//插入右子树
	else
		pPos -> right = new TreeNode(val);

	return true;
}

bool SearchTree::IsEmpty()
{
	return m_root == nullptr;
}

bool SearchTree::Remove(int val)
{
	TreeNode *p = m_root;
	TreeNode *pre = nullptr;
	while(p != nullptr)
	{
		if (p -> val == val)
			break;
		else if (val < p -> val)
		{
			pre = p;
			p = p -> left;
		}
		else
		{
			pre = p;
			p = p -> right;

		}
	}

	//当二叉树中没有指定结点时返回错误
	if (p == nullptr)
		return false;
	
	//被删除结点没有左子树
	if (p -> left == nullptr)
	{
		//当删除的是父结点
		if (pre == nullptr)
			m_root = p -> right;

		//结点p是父结点pre的左儿子
		else if (pre -> left == p)
			pre -> left = p -> right;
		
		//结点p是父结点pre的右儿子
		else 
			pre -> right = p -> right;
	}

	//当被删除结点存在左子树时
	else 
	{
		//找到结点p的最大值结点（右下角）
		TreeNode *pm = p -> left;
		while (pm -> right != nullptr)
			pm = pm -> right;
		
		//将p结点的右子树移到pm右子树位置，以满足二叉搜索树的性质
		pm -> right = p -> right;

		//然后将p结点的左儿子代替p的位置
		if (pre == nullptr)
			m_root = p -> left;
		else if (pre -> left == p)
			pre -> left = p -> left;
		else 
			pre -> right = p -> left;

	}

	//回收p结点内存
	delete p;

	return true;
}

void SearchTree::Print()
{
	if (m_root == nullptr) return;

	queue<TreeNode *> q;
	q.push(m_root);
	TreeNode *p;
	while (!q.empty())
	{
		p = q.front();
		q.pop();
		cout << p -> val;
		
		if (p -> left != nullptr)
			q.push(p -> left);
		if (p -> right != nullptr)
			q.push(p -> right);

		if (!q.empty())
			cout << ",";
	}
	cout << endl;

}

/*****************搜索二叉树END**************************/





int main()
{
/*
	vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8};
	TreeNode *root = CreateTree(arr);
	vector<int> result;

	cout << "宽度优先遍历后：" << endl;
	WidOrder(root, result);
	PrintArr(result);

	cout << "先根遍历后：" << endl;
	PreOrder(root, result);
	PrintArr(result);
	
	cout << "中根遍历后：" << endl;
	InOrder(root, result);
	PrintArr(result);

	cout << "后跟遍历后：" << endl;
	PostOrder(root, result);
	PrintArr(result);

*/
	
/*
	vector<int> preOrder{1, 2, 4, 7, 3, 5, 6, 8};	//先根序列数组
	vector<int> inOrder{4, 7, 2, 1, 5, 3, 8, 6};	//中根序列数组
	TreeNode *newtree = ReBuildBinTree(inOrder, preOrder, 0, inOrder.size() - 1, 0, preOrder.size() - 1);
	vector<int> treeArr;
	InOrder(newtree, treeArr);
	PrintArr(treeArr);

*/

	
	SearchTree st;
	vector<int> arr{8, 4, 2, 11, 5, 7, 19, 6, 9};
	st.Create(arr);
	st.Print();
	int i;
	while (true)
	{
		cout << "1.增加索引" << endl;
		cout << "2.删除索引" << endl;
		cout << "3.输出索引" << endl;
		cin >> i;

		if (i == 1)
		{
			cout << "输入索引：" << endl;
			int index;
			cin >> index;
			if (st.Insert(index))
				cout << "添加成功" << endl;
			else 
				cout << "添加失败" << endl;
		}
		else if (i == 2)
		{
			cout << "输入索引：" << endl;
			int index ;
			cin >> index;
			if (st.Remove(index))
				cout << "删除成功" << endl;
			else 
				cout << "删除失败" << endl;
		}
		else if (i == 3)
		{
			st.Print();
		}
		else 
			break;
	}



	return 0;
}




