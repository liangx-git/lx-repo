#include<iostream>
#include<vector>
#include<memory>
#include<queue>
#include<algorithm>


using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::queue;


class Heap
{
public:
	Heap(vector<int> &nums):
		size_(nums.size()),
		capacity_(size_ * 2),
		ptr_container_(make_shared<vector<int>>(capacity_))
	{
		copy(nums.begin(), nums.end(), (*ptr_container_).begin());		
		init();
	}
		
	~Heap(){};

	void init();

	void push(int value);

	void pop();
	
	int top();

	bool isEmpty();

	void print();

private:
	void upAdjust(int index);
	void downAdjust(int index);

private:
	int size_;
	int capacity_;
	shared_ptr<vector<int>> ptr_container_;
};

void Heap::init()
{
	//对数组container中元素进行堆序处理
	
	for (int i = (size_ - 1) / 2; i >=0; --i)
	{
		downAdjust(i);	
	}
}

void Heap::upAdjust(int index)
{
	int temp_value = (*ptr_container_)[index];
	int child_index = index;
	int parent_index = (child_index - 1) / 2;
	while (parent_index >= 0 &&
			(*ptr_container_)[parent_index] > temp_value)
	{
		(*ptr_container_)[child_index] = (*ptr_container_)[parent_index];
		child_index = parent_index;
		parent_index = (parent_index - 1) / 2;
		if (child_index == 0)
			break;
	}
	(*ptr_container_)[child_index] = temp_value;

}

void Heap::downAdjust(int index)
{
	int temp_value = (*ptr_container_)[index]; 	
	int parent_index = index;
	int child_index = parent_index * 2 + 1;
	while (child_index < size_ && (*ptr_container_)[child_index] < temp_value)
	{
		if ((*ptr_container_)[child_index + 1] < (*ptr_container_)[child_index])	//右节点小于左节点时，取右节点	
			++child_index;

		(*ptr_container_)[parent_index] = (*ptr_container_)[child_index];
		parent_index = child_index;
		child_index = child_index * 2 + 1;
	}
	(*ptr_container_)[parent_index] = temp_value;
}

void Heap::push(int value)
{
	if (size_ == capacity_)
	{
		capacity_ *= 2;
		(*ptr_container_).resize(capacity_);
	}

	(*ptr_container_)[size_++] = value;
	upAdjust(size_ - 1);
}

void Heap::pop()
{
	if (size_ == 0)
		return;
	(*ptr_container_)[0] = (*ptr_container_)[size_ - 1];
	downAdjust(0);
	--size_;
}

int Heap::top()
{
	if (isEmpty())
		throw("out of size");

	return (*ptr_container_)[0];
}

bool Heap::isEmpty()
{
	return size_ == 0;
}

void Heap::print()
{
	int each_line_nums= 1;
	int count = 0;
	for (int i = 0; i < size_; ++i)
	{
		std::cout << (*ptr_container_)[i]<< ' ';
		if (++count == each_line_nums
				|| i == size_ -1)
		{
			std::cout << std::endl;
			each_line_nums *= 2;
			count = 0;
		}
	}
}

void start(Heap &heap)
{
	while (true)
	{
		std::cout << "**************************" << std::endl;
		std::cout << "1.输出堆" << std::endl;
		std::cout << "2.插入新元素" << std::endl;
		std::cout << "3.取堆顶元素" << std::endl;
		std::cout << "4.退出" << std::endl;
		std::cout << "**************************" << std::endl;
		int selection = 4;	
		std::cout << "请选择:"; 
		std::cin >> selection;
		switch (selection)
		{
			case 1:
				heap.print();
				break;
			case 2:
				std::cout << "请输入代插入元素:";
				int new_value;
				std::cin >> new_value;
				heap.push(new_value);
				std::cout << std::endl;
				break;
			case 3:
				std::cout << heap.top() << std::endl;
				break;
			case 4:
			default:
				exit(0);
		}
	}
}

int main()
{
	vector<int> nums{5, 7, 2, 1, 6, 3, 4};
	Heap heap(nums);
	start(heap);

	return 0;
}
