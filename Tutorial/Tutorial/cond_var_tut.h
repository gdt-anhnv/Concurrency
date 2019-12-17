#ifndef _COND_VAR_TUT_H_
#define _COND_VAR_TUT_H_

#include "common.h"

#include <iostream>
#include <list>
#include <mutex>
#include <thread>

struct DataCV
{
	std::list<int> data;

	std::mutex mutex;
	std::condition_variable cond_var;

	DataCV() :
		data{},
		mutex{},
		cond_var{}
	{}

	void Process()
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(random()));
			std::unique_lock<std::mutex> ul(mutex);
			cond_var.wait(ul, [&]()
			{
				if (data.size() > 0)
				{
					std::cout << std::this_thread::get_id() << " " << data.size() << std::endl;
					return data.size() > 0;
				}
			});

			std::cout << data.front() << std::endl;
			data.pop_front();
		}
	}

	void AddData()
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			std::lock_guard<std::mutex> lg(mutex);
			data.push_back(random());
			cond_var.notify_all();
		}
	}
};

#endif