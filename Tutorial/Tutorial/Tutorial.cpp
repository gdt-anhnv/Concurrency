// Tutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include "common.h"
#include "unique_lock_tut.h"
#include "cond_var_tut.h"

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

int main_1()
{
	auto t1 = std::thread(AddData);
	auto t2 = std::thread(RemoveData);
	auto t3 = std::thread(RemoveData);
	ThreadObj to1(t1);
	ThreadObj to2(t2);
	ThreadObj to3(t3);
	return 0;
}

int main_2()
{
	Data data{};
	std::thread t1(std::bind(LockData, std::ref(data)));
	std::thread t2(std::bind(LockData, std::ref(data)));
	std::thread t3(std::bind(LockData, std::ref(data)));
	ThreadObj to1(t1);
	ThreadObj to2(t2);
	ThreadObj to3(t3);

	std::thread report(std::bind(ReportData, std::ref(data)));
	ThreadObj to4(report);
	return 0;
}

int main()
{
	DataCV data{};
	std::thread t1(std::bind(&DataCV::AddData, std::ref(data)));
	std::thread t2(std::bind(&DataCV::AddData, std::ref(data)));

	std::thread t3(std::bind(&DataCV::Process, std::ref(data)));
	std::thread t4(std::bind(&DataCV::Process, std::ref(data)));

	ThreadObj to1(t1);
	ThreadObj to2(t2);
	ThreadObj to3(t3);
	ThreadObj to4(t4);

	return 0;
}