#include<iostream>
#include<vector>
#include<string>
#include<queue>



using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::queue;


struct TreeNode
{
	int val;
	int bf;
	TreeNode *left;
	TreeNode *right;

	TreeNode(int val = 0) : val(val), bf(0), left(nullptr), right(nullptr){}
};


class AVLTree
{
public:
	AVLTree() : m_root(nullptr){};
	~AVLTree(){};

	//宽度优先顺序输出
	void Print();


	//插入新元素，并动态调整满足平衡二叉树性质
	bool Insert(int val);

	//创建AVL树
	bool Create(const vector<int> &arr);
	
	//删除元素
	bool Delete(int val);

private:
	TreeNode *LL(TreeNode *pa, TreeNode *pb);
	TreeNode *LR(TreeNode *pa, TreeNode *pb);
	TreeNode *RR(TreeNode *pa, TreeNode *pb);
	TreeNode *RL(TreeNode *pa, TreeNode *pb);

	bool Delete(TreeNode *pTree, int val);

	bool BeginDelete(TreeNode *pTree);

private:
	TreeNode *m_root;

};

void AVLTree::Print()
{
	queue<TreeNode *> q;
	q.push(m_root);
	while (!q.empty())
	{
		TreeNode *p = q.front();
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



bool AVLTree::Insert(int val)
{
	if (m_root == nullptr)
	{
		m_root = new TreeNode(val);
		return true;
	}

	TreeNode *p = m_root, *pre = nullptr;
	TreeNode *pTree = m_root, *pTreePar = nullptr;		//pTree指向插入结点所在最小调整树根结点，bf不为0的结点,pTreePar指向pTree的父结点
	TreeNode *pSubTree = nullptr;		//pSubTree指向pTree树中插入结点所在一边的子树的结点
	int bf = 0;	//-1表示新结点插入在pTree左子树，1表示新结点插入在pTree右子树

	//找到新结点插入位置
	while (p != nullptr)
	{
		//找到最小调整子树根结点
		if (p -> bf != 0)
		{
			pTree = p;
			pTreePar = pre;
		}

		if (p -> val == val)
			return false;
		pre = p;
		if (val < p -> val)
			p = p -> left;
		else 
			p = p -> right;
	}
	
	//插入新结点
	p = new TreeNode(val);
	if (val < pre -> val)
		pre -> left = p;
	else 
		pre -> right = p;

	//设置bf和确定pSubTree指向
	if (val < pTree -> val)
	{
		pSubTree = pTree -> left;
		bf = -1;
	}
	else 
	{
		pSubTree = pTree -> right;
		bf = 1;
	}

	//调整pSubTree至新结点pre之间结点的bf
	pre = pSubTree;
	while (pre != p)
	{
		if (val < pre -> val)
		{
			pre -> bf = -1;
			pre = pre -> left;
		}
		else 
		{
			pre -> bf = 1;
			pre = pre -> right;
		}

	}

	//开始调整二叉树	
	//pTree指向结点bf = 0插入新结点后不会破坏平衡
	if (pTree -> bf == 0)
	{
		pTree -> bf = bf;
		return true;
	}

	//新增结点在pTree中的较低子树中，不会破坏平衡
	if (pTree -> bf == -bf)
	{
		pTree -> bf = 0;
		return true;
	}
	
	//新结点在较高子树中，需要调整
	//在pTree左子树
	if (bf == -1)
	{
		//LL型
		if (pSubTree -> bf == -1)
			p = LL(pTree, pSubTree);
		
		//LR型
		else 
			p = LR(pTree, pSubTree);

	}

	//在pTree右子树
	else 
	{
		//RR型
		if (pSubTree -> bf == 1)
			p = RR(pTree, pSubTree);
		
		//RL型
		else
		{
			p = RL(pTree, pSubTree);
		}
	}
	
	if (pTree == nullptr)
		m_root = pTree;
	else
	{
		if (pTreePar -> left == pTree)
			pTreePar -> left = p;
		else 
			pTreePar -> right = p;
	}
	
	return true;

}


TreeNode *AVLTree::LL(TreeNode *pa, TreeNode *pb)
{
	pa -> left = pb -> right;
	pa -> bf = 0;
	pb -> right = pa;
	pb -> bf = 0;

	return pb;
}


TreeNode *AVLTree::LR(TreeNode *pa, TreeNode *pb)
{
	TreeNode *pc = pb -> right;
	pb -> right = pc -> left;
	pa -> left = pc -> right;
	pc -> left = pb;
	pc -> right = pa;

	switch (pc -> bf)
	{
		case 0:
			pa -> bf = 0;
			pb -> bf = 0;
			break;
		case -1:
			pa -> bf = 1;
			pb -> bf = 0;
			break;
		case 1:
			pa -> bf = 0;
			pb -> bf = -1;
			break;
	}

	return pc;
}

TreeNode *AVLTree::RR(TreeNode *pa, TreeNode *pb)
{
	pa -> right = pb -> left;
	pa -> bf = 0;
	pb -> left = pa;
	pb -> bf = 0;

	return pb;
}

TreeNode *AVLTree::RL(TreeNode *pa, TreeNode *pb)
{
	TreeNode *pc = pb -> left;
	pa -> right = pc -> left;
	pb -> left = pc -> right;
	pc -> left = pa;
	pc -> right = pb;

	switch(pc -> bf)
	{
		case 0:
			pa -> bf = 0;
			pb -> bf = 0;
			break;
		case -1:
			pc -> bf = 0;
			pa -> bf = 0;
			pb -> bf = 1;
			break;
		case 1:
			pc -> bf = 0;
			pa -> bf = -1;
			pb -> bf = 0;
			break;
	}
	return pc;
}

bool AVLTree::Create(const vector<int> &arr)
{
	for (auto val : arr)
	{
		Insert(val);
	}
	return true;
}


//
bool AVLTree::BeginDelete(TreeNode *pTree)
{
	
}

//删除结点,当被删除结点不是叶结点时，转换为删除叶结点的情况
bool AVLTree::Delete(TreeNode *pTree, int val)
{
	
	static bool blance = false;

	//递归查找带删除结点
	if (pTree == nullptr)
		return false;
	
	//找到当前元素
	if (pTree -> val == val)
	{	
		//待删除结点是非叶结点，转为叶结点删除情况
		if (pTree -> left != nullptr 
				|| pTree -> right != nullptr)
		{
			TreeNode *p;
			TreeNode *pre;
			if (pTree -> bf = -1)	//左子树较深
			{
				//此时在pTree的左子树中找到最大的结点代替pTree的位置
				p = pTree -> left;
				while (p -> right != nullptr)
				{
					p -> bf -= 1;	//调整pTree到叶结点的bf
					
					pre = p;
					p = p -> right;
				}

				pre -> right = p -> left;
				pre -> left = nullptr;

				delete p;

			}
			else	//右子树较深
			{
				//找到右子树中最小值结点代替pTree结点位置
				p = pTree -> right;
				while (p -> left != nullptr)
				{
					p -> bf += 1;
					
					pre = p;
					p = p -> left;
				}
				pre -> left = p -> right;
				pre -> right = nullptr;
				
				delete p;
			}
		}

		
		return true;
	}
	else if (pTree -> val > val)	//val在左子树中
	{
		Delete(pTree -> left, val);

		//递归返回时调整结点的bf
		if (!blance)
			pTree -> bf += 1;
		
		if (pTree -> bf == 0)
			blance = true;

	}
	else	//val在右子树中
	{
		Delete(pTree -> right, val);

		//递归返回时调整结点的bf
		if (!blance)
			pTree -> bf -= 1;

		if (pTree -> bf == 0)
			blance = true;
	}
}


bool AVLTree::Delete(int val)
{
	if (Delete(m_root, val))
		return true;

	return false;
}


int main()
{

	vector<int> arr{5, 4, 9, 21, 7, 0, 63, 8, 22};
	cout << "向量arr数据成员有：" << endl;
	for (auto val : arr)
		cout << val << " ";
	cout << endl;
	
	cout << "生成AVL树后宽度优先遍历输出：" << endl;
	AVLTree at;
	at.Create(arr);
	at.Print();

	while (true)
	{
		cout << "1.增加元素" << endl;
		cout << "2.删除元素" << endl;
		cout << "3.输出元素" << endl;

		int select;
		cin >> select;
		if (select == 1)
		{
			cout << "输入要插入的元素：" << endl;
			int num;
			cin >> num;
			if (!at.Insert(num)) 
				cout << "插入失败！" << endl;
			else
				cout << "插入成功！" << endl;
		}
		else if (select == 2)
		{
			cout << "输入要删除的元素：" << endl;
			int num;
			cin >> num;
			if (!at.Delete(num))
				cout << "删除失败！" << endl;
			else 
				cout << "删除成功！" << endl;
		}
		else if (select == 3)
		{
			at.Print();
		}
		else 
			exit(0);

	}

	return 0;
}
