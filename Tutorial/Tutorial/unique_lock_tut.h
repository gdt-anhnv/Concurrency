#ifndef _UNIQUE_LOCK_TUT_H_
#define _UNIQUE_LOCK_TUT_H_

#include "common.h"

#include <iostream>
#include <mutex>
#include <thread>
#include <list>

class Data
{
public:
	std::list<int> test;
	std::mutex mutex;

	Data() :
		test{},
		mutex{}
	{}

	Data(const Data& d) :
		test{ d.test },
		mutex{}
	{}

	void Worker()
	{
		if (random() % 2)
		{
			test.push_back(1);
		}
		else
		{
			if (test.size() > 0)
				test.pop_back();
		}
	}


	void Reporter()
	{
		std::cout << test.size() << std::endl;
	}
};

void LockData(Data& d)
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(random()));

		std::lock_guard<std::mutex> lock(d.mutex);
		d.Worker();
	}
}

void ReportData(Data& d)
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		d.Reporter();
	}
}

#endif