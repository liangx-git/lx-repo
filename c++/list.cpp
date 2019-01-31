#include<iostream>
#include<string>
#include<vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;



struct Node
{
	int val;
	Node *next;

	Node(int val) : val(val), next(nullptr){};
};


void ReverseList(Node *&pHead)
{
	Node *pPre = nullptr;
	Node *pCur = nullptr;
	Node *pNext = nullptr;
	
	pPre = pHead;
	pCur = pHead -> next;	//从第二结点开始反转
	while (pCur)
	{
		pNext = pCur -> next;	//记录下个结点的地址
		pCur -> next = pPre;	//将当前结点中指向下个结点的指针指向上个结点
		
		//将pPre和pCur指针右移
		pPre = pCur;	
		pCur = pNext;
	}

	pHead -> next = nullptr;
	pHead = pPre;	//修改pHead指向当前头结点指针
}


void CreateList(vector<int> arr, Node *&list)
{
	list = new Node(arr[0]);
	Node *p = list;
	for (int i = 1; i < arr.size(); ++i)
	{
		Node * pNew = new Node(arr[i]);
		p -> next = pNew;
		p = p -> next;
	}
	
}

void PrintList(Node *pList)
{
	Node *p = pList;
	while (p != nullptr)
	{
		cout << p -> val << " ";
		p = p -> next;
	}
	cout << endl;
}

//创建带头结点的链表


int main()
{
	vector<int> arr{1, 2, 3, 4, 5};
	Node *pTree;
	CreateList(arr, pTree);
	cout << "链表逆序前：" << endl;
	PrintList(pTree);
	cout << "链表逆序后：" << endl;
	ReverseList(pTree);
	PrintList(pTree);

	return 0;
}
