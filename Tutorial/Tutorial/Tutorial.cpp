// Tutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <algorithm>
#include <random>
#include <ctime>
#include <chrono>

auto data = std::list<int>();
std::mutex mutex;

int random()
{
	std::srand(std::time(nullptr));
	return std::rand() % 1000;
}

void AddData()
{
	while (true)
	{
		std::lock_guard<std::mutex> guard(mutex);
		std::this_thread::sleep_for(std::chrono::microseconds(random()));
		data.push_back(random());
	}
}

void RemoveData()
{
	while (true)
	{
		std::lock_guard<std::mutex> guard(mutex);
		if (data.size() > 0)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(random()));
			data.pop_back();
		}
	}
}

struct ThreadObj
{
	std::thread& thread;
	ThreadObj(std::thread& t) : thread(t) {}
	~ThreadObj()
	{
		if (thread.joinable())
			thread.join();
	}

	ThreadObj(const ThreadObj&) = delete;
	ThreadObj& operator=(const ThreadObj&) = delete;
};

int main()
{
	auto t1 = std::thread(AddData);
	auto t2 = std::thread(RemoveData);
	auto t3 = std::thread(RemoveData);
	ThreadObj to1(t1);
	ThreadObj to2(t2);
	ThreadObj to3(t3);
	return 0;
}
