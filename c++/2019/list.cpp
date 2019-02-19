#include<iostream>
#include<vector>
#include<string>


struct Node
{
	int value;
	Node *next;
	Node(int v = 0, Node *n = nullptr):
		value(v),
		next(n){}
};


class List
{
public:
	List() : head_(nullptr){}

	~List()
	{
		destroy();
	}

	bool empty();
	
	void push(int value);

	void pop();

	int	top(); 

	int back();

	void reverse();

	Node *begin();

	Node *end();
	
private:
	void destroy();

	void check(const std::string &msg);

	void reverse_default();

	void reverse_insert();

private:
	Node *head_;
				
};

void List::destroy()
{
	if (head_ == nullptr)
		return;

	Node *ptr_Node = head_;
	Node *ptr_next_Node = nullptr;
	while (ptr_Node != nullptr)
	{
		ptr_next_Node = ptr_Node -> next;
		delete ptr_Node;
		ptr_Node = ptr_next_Node;
	}
}

void List::check(const std::string &msg)
{
	if (head_ == nullptr)
		throw(msg);
}

bool List::empty()
{
	return head_ == nullptr;
}

void List::push(int value)
{
	Node *ptr_new_Node = new Node(value);
	if (empty())
	{
		head_ = ptr_new_Node; 
		return;
	}

	Node *ptr_Node = head_;
	while (ptr_Node -> next != nullptr)
		ptr_Node = ptr_Node -> next;

	ptr_Node -> next = ptr_new_Node; 

	return;
}

void List::pop()
{
	check("no values in the list");
	
	//只有一个节点
	if (head_ -> next == nullptr)
	{
		delete head_;
		head_ = nullptr;
		return;
	}
	
	Node *ptr_Node = head_;
	Node *ptr_pre_Node = nullptr;
	while (ptr_Node -> next != nullptr)
	{
		ptr_pre_Node = ptr_Node;
		ptr_Node = ptr_Node -> next;
	}

	delete ptr_Node;
	if (ptr_pre_Node != nullptr)
		ptr_pre_Node ->next = nullptr;
}

int List::top()
{
	check("no values in the list");

	return head_ -> value;
}

int List::back()
{
	check("no values in the list");

	Node *ptr_Node = head_;
	while (ptr_Node -> next != nullptr)
		ptr_Node = ptr_Node -> next;

	return ptr_Node -> value;	
}

Node *List::begin()
{
	return head_;
}

Node *List::end()
{
	return nullptr;
}

void List::reverse()
{
	if (head_ == nullptr || head_ -> next == nullptr)
		return;
	
	Node *ptr_pre_Node = head_;
	Node *ptr_Node = head_ -> next;
	Node *ptr_next_Node = nullptr;
	while (ptr_Node != nullptr)
	{
		ptr_next_Node = ptr_Node -> next;
		ptr_Node -> next = ptr_pre_Node;
		ptr_pre_Node = ptr_Node;
		ptr_Node = ptr_next_Node;
	}
	head_ -> next = nullptr;
	head_ = ptr_pre_Node;
	
}

void print(Node *begin, Node *end)
{
	if (begin == nullptr)
	{
		std::cout << "no values" << std::endl;
		return;
	}

	for (auto ptr_Node = begin; ptr_Node != end; ptr_Node = ptr_Node -> next)
	{
		std::cout << ptr_Node -> value;	
		if (ptr_Node -> next != nullptr)
			std::cout << " -> ";
	}
	std::cout << std::endl;
}



int main()
{
	List list;
	list.push(2);
	print(list.begin(), list.end());	
	list.push(8);
	print(list.begin(), list.end());	
	list.push(5);
	print(list.begin(), list.end());	
	list.push(9);
	print(list.begin(), list.end());	
	std::cout << "反转链表：" << std::endl;
	list.reverse();
	print(list.begin(), list.end());

	return 0;
}
