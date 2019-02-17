#include<iostream>
#include<vector>
#include<deque>
#include<stack>


using std::vector;
using std::deque;
using std::stack;


struct TreeNode
{
	int value_;
	TreeNode *left_child_;
	TreeNode *right_child_;

	TreeNode(int value, TreeNode *left_child = nullptr, TreeNode *right_child = nullptr):
		value_(value),
		left_child_(left_child),
		right_child_(right_child){}

};
typedef TreeNode* Tree;


TreeNode *createBinTreeByPreorderSequencesAndMidorderSequences(const vector<int> &preorder_sequences, int pre_left, int pre_right, const vector<int> &midorder_sequences, int mid_left, int mid_right)
{
	TreeNode *root = new TreeNode(preorder_sequences[pre_left]);	
	
	if (pre_left == pre_right)
		return root;

	int index_of_root_in_midorder_sequences = 0;
	while (midorder_sequences[mid_left + index_of_root_in_midorder_sequences] != preorder_sequences[pre_left])
		++index_of_root_in_midorder_sequences;
	
	if (index_of_root_in_midorder_sequences != 0) //存在左子树
		root -> left_child_ = createBinTreeByPreorderSequencesAndMidorderSequences(
				preorder_sequences, 
				pre_left + 1, 
				pre_left + index_of_root_in_midorder_sequences, 
				midorder_sequences, 
				mid_left, 
				mid_left + index_of_root_in_midorder_sequences - 1);

	if (mid_left + index_of_root_in_midorder_sequences != mid_right) //存在右子树
		root -> right_child_ = createBinTreeByPreorderSequencesAndMidorderSequences(
				preorder_sequences, 
				pre_left + index_of_root_in_midorder_sequences + 1, 
				pre_right, 
				midorder_sequences, 
				mid_left + index_of_root_in_midorder_sequences + 1, 
				mid_right);

	return root;
}


void print_Tree_by_BFS(TreeNode *tree)
{
	deque<TreeNode *> dq;
	dq.push_back(tree);
	while (!dq.empty()) 
	{
		TreeNode *ptr_TreeNode = dq.front();
		dq.pop_front();
		std::cout << ptr_TreeNode -> value_ << " ";

		if (ptr_TreeNode -> left_child_ != nullptr) //存在左子树
			dq.push_back(ptr_TreeNode -> left_child_);

		if (ptr_TreeNode -> right_child_ != nullptr) //存在右子树
			dq.push_back(ptr_TreeNode ->right_child_);
	}
}


/****************************递归深度搜索************************************/


void print_Tree_by_preorder_DFS_recursion(TreeNode *tree)
{
	if (tree != nullptr)
	{
		std::cout << tree -> value_ << " ";
		print_Tree_by_preorder_DFS_recursion(tree -> left_child_);
		print_Tree_by_preorder_DFS_recursion(tree -> right_child_);
	}
}


void print_Tree_by_midorder_DFS_recursion(TreeNode *tree)
{
	if (tree != nullptr)
	{
		print_Tree_by_midorder_DFS_recursion(tree -> left_child_);
		std::cout << tree -> value_ << " ";
		print_Tree_by_midorder_DFS_recursion(tree -> right_child_);
	}
}


void print_Tree_by_postorder_DFS_recursion(TreeNode *tree)
{
	if (tree != nullptr)
	{
		print_Tree_by_postorder_DFS_recursion(tree -> left_child_);
		print_Tree_by_postorder_DFS_recursion(tree -> right_child_);
		std::cout << tree -> value_ << " ";
	}
}


/*****************************非递深度搜索****************************************/

void print_Tree_by_preorder_DFS(TreeNode *tree)
{
	if (tree == nullptr)
		return;
	
	stack<TreeNode *> st;
	st.push(tree);
	while (!st.empty())
	{
		TreeNode *ptr_TreeNode = st.top();
		st.pop();
		std::cout << ptr_TreeNode -> value_ << " ";
		if (ptr_TreeNode -> right_child_ != nullptr)
			st.push(ptr_TreeNode -> right_child_);
		if (ptr_TreeNode -> left_child_ != nullptr)
			st.push(ptr_TreeNode -> left_child_);
	}
	
}


void print_Tree_by_midorder_DFS(TreeNode *tree)
{
	if (tree == nullptr)
		return;

	stack<TreeNode *> st;
	TreeNode *ptr_TreeNode = tree;
	while (!st.empty() || ptr_TreeNode != nullptr)
	{
		while (ptr_TreeNode != nullptr)	
		{
			st.push(ptr_TreeNode);
			ptr_TreeNode = ptr_TreeNode -> left_child_;
		}

		ptr_TreeNode = st.top();
		st.pop();
		std::cout << ptr_TreeNode -> value_ << " ";
		ptr_TreeNode = ptr_TreeNode -> right_child_;
	}
}


void print_Tree_by_postorder_DFS(TreeNode *tree)
{
	if (tree == nullptr)
		return;

	stack<TreeNode *> st;
	TreeNode *ptr_TreeNode = tree;
	while (!st.empty() || ptr_TreeNode != nullptr)
	{
		while (ptr_TreeNode != nullptr)
		{
			st.push(ptr_TreeNode);
			ptr_TreeNode = (ptr_TreeNode -> left_child_ != nullptr) ? (ptr_TreeNode -> left_child_) : (ptr_TreeNode -> right_child_);
		}
		
		ptr_TreeNode = st.top();
		st.pop();
		std::cout << ptr_TreeNode -> value_ << " ";	
		if (!st.empty())
		{
			TreeNode *ptr_parent_TreeNode = st.top();
			if (ptr_TreeNode == ptr_parent_TreeNode -> left_child_)
				ptr_TreeNode  = ptr_parent_TreeNode -> right_child_;
			else
				ptr_TreeNode = nullptr;
		}
		else 
		{
			ptr_TreeNode = nullptr;
		}
	}
}


int main()
{
	vector<int> preorder_sequences{1, 2, 4, 5, 3, 6, 7};
	vector<int> midorder_sequences{4, 2, 5, 1, 6, 3, 7};
	TreeNode *new_tree = createBinTreeByPreorderSequencesAndMidorderSequences(preorder_sequences, 0, preorder_sequences.size() - 1, midorder_sequences, 0, midorder_sequences.size() - 1);

	std::cout << "宽度优先顺序输出树节点" << std::endl;
	print_Tree_by_BFS(new_tree);
	
	std::cout << '\n' << "先跟顺序输出树节点(递归)" << std::endl;
	print_Tree_by_preorder_DFS_recursion(new_tree);

	std::cout << '\n' << "中根顺序输出树节点(递归)" << std::endl;
	print_Tree_by_midorder_DFS_recursion(new_tree);

	std::cout << '\n' << "后根顺序输出树节点(递归)" << std::endl;
	print_Tree_by_postorder_DFS_recursion(new_tree);
	
	std::cout << '\n' << "先根顺序输出树节点" << std::endl;
	print_Tree_by_preorder_DFS(new_tree);

	std::cout << '\n' << "中根顺序输出树节点" << std::endl;
	print_Tree_by_midorder_DFS(new_tree);

	std::cout << '\n' << "后根顺序输出树节点" << std::endl;
	print_Tree_by_postorder_DFS(new_tree);
	
	std::cout << std::endl;

	return 0;
}
