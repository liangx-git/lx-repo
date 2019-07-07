#include<iostream>
#include<memory>

using std::cin;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::make_shared;

template <typename T>
struct TreeNode{

	TreeNode(T value, shared_ptr<TreeNode<T>> left = nullptr, shared_ptr<TreeNode<T>> right = nullptr)
		:value(value), left(left), right(right){}

	T value;
	shared_ptr<TreeNode<T>> left;
	shared_ptr<TreeNode<T>> right;
};


//二叉排序数，小根
template <typename T>
class BinarySortTree{
public:

	BinarySortTree(){
		ptr_root = nullptr;
	}

	BinarySortTree(T value){
		ptr_root = make_shared<TreeNode<T>>(value);
	}

	~BinarySortTree(){};

	//插入元素
	void push(T value);

	//删除最小元素（根节点）
	void pop();

	//获取最小元素(根节点)
	T top();

	//当二叉数为空时返回true
	bool empty();

	//当T存在二叉树中时返回true
	bool hasElement(T value);

private:

	//返回value对应的节点，同时参数返回父节点，
	//当不存在value对应节点时ptr_parentNode指向value应该插入的位置
	shared_ptr<TreeNode<T>> findElement(T value, shared_ptr<TreeNode<T>> &ptr_parentNode);

	shared_ptr<TreeNode<T>> ptr_root;
};


template <typename T>
bool BinarySortTree<T>::empty(){
	return ptr_root == nullptr;
}


template <typename T>
T BinarySortTree<T>::top(){
	return ptr_root -> value; 
}


template <typename T>
shared_ptr<TreeNode<T>> BinarySortTree<T>::findElement(T value, shared_ptr<TreeNode<T>> &ptr_parentNode){
	if (empty()){	//二叉数为空
		ptr_parentNode = nullptr;
		return nullptr;
	}

	shared_ptr<TreeNode<T>> ptr_TreeNode = ptr_root;
	ptr_parentNode = nullptr;
	while (ptr_TreeNode != nullptr){
		if (ptr_TreeNode -> value == value){
			return ptr_TreeNode;
		}else if (ptr_TreeNode -> value > value){
			ptr_parentNode = ptr_TreeNode; 
			ptr_TreeNode = ptr_TreeNode -> left;	
		}else{
			ptr_parentNode = ptr_TreeNode;
			ptr_TreeNode = ptr_TreeNode -> right;
		}
	}
	return ptr_TreeNode;
}


template <typename T>
bool BinarySortTree<T>::hasElement(T value){
	shared_ptr<TreeNode<T>> ptr_parentNode;
	return (findElement(value, ptr_parentNode) != nullptr);
}


template <typename T>
void BinarySortTree<T>::push(T value){
	if (empty()){
		ptr_root = make_shared<TreeNode<T>>(value);
		return;
	}	
	
	shared_ptr<TreeNode<T>> ptr_parentNode;
	if (findElement(value, ptr_parentNode) == nullptr){
		if (value < ptr_parentNode -> value){
			ptr_parentNode -> left = make_shared<TreeNode<T>>(value);
		}else{
			ptr_parentNode -> right = make_shared<TreeNode<T>>(value);
		}	
	}
}

void printMenu(){
	cout << "******************" << endl;
	cout << "1.输出最小元素" << endl;
	cout << "2.插入元素" << endl;
	cout << "3.删除元素" << endl;
	cout << "4.输出所有元素" << endl;
	cout << "******************" << endl;
	cout << "请选择功能" << endl;
}

int main(){
	BinarySortTree<int> bt;

	int value;
	while (true){
		printMenu();
		int select;
		cin >> select;
		switch (select){
			case 1:
				cout << bt.top() << endl;
				break;
			case 2:
				cout << "输入需要插入的元素：";
				cin >> value;
				cout << endl;
				bt.push(value);
				break;
			case 3:
				cout << "请输入需要删除的元素：";
				cin >> value;
				cout << endl;
				//bt.pop(value);
				break;
			defalut:
				break;
		}
	}

	return 0;
}
