/***************************************************************
 * Author : liangx
 *
 * Date : 2019-7-4
 *
 * Description : 实现一个Heap，具备增加、删除、显示等功能
 *
 * **************************************************************/

#include<iostream>
#include<vector>
#include<memory>
#include<queue>


//小根堆
template<typename T>
class Heap{
public:

	/**
	 *  Description: 包含默认参数的构造函数，允许接受一个vector数组作为参数构造Heap
	 * 				 ptr_container指向容量为0存储int的vector
	 *
	 * 	Parmeters:
	 * 		
	 * 		nums: 构造Heap时，如果传入nums时使用其构造Heap，
	 * 			  否则使用默认参数vector<T>(0)构造Heap
	 */
	Heap(const std::vector<T> &nums = std::vector<T>(0));


	/**
	 *  Description: 向Heap中添加元素
	 *  
	 *  Paramerts:
	 *
	 *  	vallue: 需要添加的元素
	 *
	 *  Return: void
	 */
	void push(T value);


	/**
	 *  Description: 返回堆顶元素
	 *
	 *  Return: 堆顶元素
	 */
	T top();


	/**
	 * Description: 将堆顶元素删除，并重新调整堆中序列
	 */
	void pop();


	/**
	 *  Description: 判断堆是否为空 
	 *  
	 *  Return: 堆为空时返回true,不为空返回false
	 */
	bool isEmpty();


	/**
	 *  Description: 输出当前堆中元素
	 */
	void show();


private:
	void init();	//将ptr_container中的元素堆序化

	void downAdjust(std::vector<T> &nums, std::size_t len, std::size_t index);	//向下调整

	void upAdjust(std::vector<T> &nums, std::size_t index);		//向上调整

	bool isFull();	//当存储空间size达到上限capatity时返回true

	void expandCapacity();	//扩充容积为当前capacity的两倍

private:
	std::size_t size;		//堆当前存储的大小
	std::size_t capacity;	//堆的最大容量
	std::shared_ptr<std::vector<T>> ptr_container;	//指向vector容器的智能指针	
};


template<typename T>
Heap<T>::Heap(const std::vector<T> &nums) :
	size(nums.size()),		
	capacity(2 * nums.size()),
	ptr_container(std::make_shared<std::vector<T>>(capacity))
{
	copy(nums.begin(), nums.end(), ptr_container -> begin());
	init();
}

template<typename T>
void Heap<T>::init(){

	//从第一个非叶子节点开始调整数组满足堆序性
	for (int i = (size - 1) / 2; i >= 0; --i){
		downAdjust(*ptr_container, size, i);
	}
}


template<typename T>
void Heap<T>::downAdjust(std::vector<T> &nums, std::size_t len, std::size_t index){
	T temp_value = nums[index];		//保存待调整节点值,此时认为index为空位
	std::size_t parent_index = index;
	std::size_t child_index = index * 2 + 1;
	while (child_index < len) {		//从index开始依据父子节点关系向下调整序列

		//当存在右子节点并且值小于左子节点时，child_index指向右子节点
		if (child_index + 1 < len 
				&& nums[child_index + 1] < nums[child_index]){
			++child_index;
		}

		if (nums[child_index] < temp_value){
			nums[parent_index] = nums[child_index];
		}else{
			break;
		}

		parent_index = child_index;
		child_index = child_index * 2 + 1;
	}

	nums[parent_index] = temp_value;	//将temp_value填入正确的空位中
}


template<typename T>
void Heap<T>::upAdjust(std::vector<T> &nums, std::size_t index){
	T temp_value = nums[index];
	int child_index = index;
	int parent_index = (child_index - 1) / 2;
	while (parent_index >= 0) {
		if (nums[parent_index] > temp_value){
			nums[child_index] = nums[parent_index];
		}else{
			break;
		}
		
		child_index = parent_index;
		if (child_index == 0)
			break;
		parent_index = (parent_index - 1) / 2;
	}

	nums[child_index] = temp_value;
}


template<typename T>
bool Heap<T>::isFull(){
	return size == capacity;
}


template<typename T>
void Heap<T>::expandCapacity(){
	if (capacity != 0){
		capacity *= 2;
	}else{
		capacity = 5;
	}
	(*ptr_container).resize(capacity);
}


template<typename T>
void Heap<T>::push(T value){
	
	if (isFull()){
		expandCapacity();
	}

	(*ptr_container)[size] = value;
	upAdjust(*ptr_container, size);
	++size;
}


template<typename T>
void Heap<T>::pop(){
	if (!isEmpty()) {
		(*ptr_container)[0] = (*ptr_container)[size - 1];
		downAdjust(*ptr_container, --size, 0);
	}
}


template<typename T>
T Heap<T>::top(){
	return (*ptr_container)[0];
}


template<typename T>
bool Heap<T>::isEmpty() {
	return size == 0; 
}

template<typename T>
void Heap<T>::show(){
	for (std::size_t i = 0; i < size; ++i) {
		std::cout << (*ptr_container)[i] << " ";
	}
	std::cout << std::endl;

}


void printMenu(){
	std::cout << "\n***********************" << std::endl;
	std::cout << "* 1.输出堆            *" << std::endl;
	std::cout << "* 2.添加新元素        *" << std::endl;
	std::cout << "* 3.堆顶元素          *" << std::endl;
	std::cout << "* 4.删除堆顶元素      *" << std::endl;
	std::cout << "* 5.退出              *" << std::endl;
	std::cout << "***********************\n" << std::endl;
}


int main(){

	//std::vector<int> nums{3, 6, 1, 0, 9, 4, 7, 5, 2, 8};
	std::vector<int> nums(0);
	Heap<int> heap(nums);
	while (true){
		printMenu();
		std::cout << ">> ";
		std::size_t select;
		std::cin >> select;
		switch(select){
			case 1:
				heap.show();
				break;
			case 2: {
					int value;
					std::cout << "请输入要插入的值：";
					std::cin >> value;
					heap.push(value);
					break;
				}
			case 3:
				std::cout << heap.top() << std::endl;
				break;
			case 4:
				heap.pop();
				break;
			case 5:
			default:
					exit(0);
		}
	}


	return 0;
}
