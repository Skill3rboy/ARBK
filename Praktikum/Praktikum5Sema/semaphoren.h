#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

class semaphore
{

private:

	std::mutex mutex;
	std::condition_variable con_var;
	short runs;

public:

	semaphore(short runs=1): runs(runs){}

	void open();
	void block(short id);
};