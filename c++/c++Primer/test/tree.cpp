#include<iostream>
#include<vector>
#include<stack>
#include<queue>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::stack;
using std::queue;

namespace Tree{

struct TreeNode
{
	int value;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int val = 0) : value(val), left(nullptr), right(nullptr){}
};

class Tree
{
public:
	//普通构造函数
	Tree(const vector<int> &arr);

	//拷贝构造函数
	Tree(const Tree &other_tree);
	
	//拷贝赋值运算符
	Tree& operator=(Tree other_tree);
	
	//析构函数
	~Tree();

	void pre_dfs_print();

	void mid_dfs_print();

	void post_dfs_print();

	void swap(Tree &other);

private:
	void init_from_bdVec(const vector<int> &bd_arr);

	void init_from_preVec_and_midVec(const vector<int> &pre_arr, const vector<int> &mid_arr);
	
	void init_from_postVec_and_midVec(const vector<int> &post_arr, const vector<int> &mid_arr);

	void copy_from_other_tree(const Tree &tree);

	void remove_current_tree();

	typedef void FunType(TreeNode * tree_node);
	void bfs(FunType f);

	void pre_dfs(FunType f);

	void mid_dfs(FunType f);

	void post_dfs(FunType f);

	void print_TreeNode(TreeNode *);

	void remove_TreeNode(TreeNode *);
	
	void copy_TreeNode(TreeNode *);
private:
	TreeNode *root;
};

Tree::Tree(const vector<int> &arr)
{
	init_from_bdVec(arr);
}

Tree::Tree(const Tree &other_tree)
{
	copy_from_other_tree(other_tree);
}

Tree& Tree::operator=(Tree other_tree)
{
	//采用拷贝交换技术避免自赋值情况异常
	swap(other_tree);
	return *this;
}

Tree::~Tree()
{
	remove_current_tree();
}

void Tree::swap(Tree &other_tree)
{
	using std::swap;
	swap(root, other_tree.root);
}

//no-member版本swap
void swap(Tree &tree_a, Tree &tree_b)
{
	tree_a.swap(tree_b);
}

void Tree::init_from_bdVec(const vector<int> &arr)
{
	queue<TreeNode *> tq;
	tq.push(new TreeNode(arr[0]));
	int i = 1;
	int len = arr.size();
	while (!tq.empty() && i <len)
	{
		TreeNode *pcur_TreeNode = tq.front();
		
		tq.pop();
		if(pcur_TreeNode -> left != nullptr)
		{
			TreeNode *ptemp = new TreeNode(arr[i++]);
			pcur_TreeNode -> left = ptemp;
			tq.push(pcur_TreeNode -> left);
		}
		if (pcur_TreeNode -> right != nullptr)
		{
			TreeNode *ptemp = new TreeNode(arr[i++]);
			pcur_TreeNode -> right = ptemp;
			tq.push(pcur_TreeNode -> right);
		}
	}
}

void Tree::copy_from_other_tree(const Tree &other_tree)
{
	
}

}	/*end Tree作用域*/


//在std声明域中特化Tree版本swap()
namespace std
{
	using Tree::Tree;
	template<>
	void swap<Tree>(Tree &tree_a, Tree &tree_b)
	{
		tree_a.swap(tree_b);
	}
}



int main()
{
	return 0;
}
