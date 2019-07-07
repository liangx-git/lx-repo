#include<iostream>
#include<thread>

struct func
{
public:
	func(int& i_):
		i(i_)
	{}

	void operator()()
	{
		for (unsigned j = 0; j < 100; ++j)
		{
			++i;
		}
		std::cout << "some_local_state = " << i << std::endl; 
	}

public:
	int &i;

};


class thread_guard
{
public:
	explicit thread_guard(std::thread& t_):
		t(t_)
	{}

	~thread_guard()
	{
		if (t.joinable())
		{
			t.join();
		}
	}

	thread_guard(const thread_guard &) = delete;
	thread_guard& operator=(const thread_guard &) = delete;

private:
	std::thread& t;

};

class scoped_thread
{
public:
	explicit scoped_thread(std::thread t_):
		t(std::move(t_))
	{
		if (!t.joinable())
			throw std::logic_error("No thread");
		//t.join();
	}

	~scoped_thread()
	{
		if (t.joinable())
		{
			//t.join();
			t.detach();
		}
	}

	scoped_thread(const scoped_thread &) = delete;
	scoped_thread& operator=(const scoped_thread &) = delete;	

public:
	std::thread t;
};

int main()
{
	int some_local_state = 0;
	scoped_thread t(std::thread(func(some_local_state)));
	
	std::cout << "created scoped_thread" << std::endl;

	return 0;
}
