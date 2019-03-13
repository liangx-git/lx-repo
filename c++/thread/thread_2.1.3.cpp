#include<iostream>
#include<thread>

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

int main()
{


	return 0;
}
