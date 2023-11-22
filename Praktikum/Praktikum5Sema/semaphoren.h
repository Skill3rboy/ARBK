#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

class semaphore
{

private:

	std::mutex mutex; // mutex siehe andere Datei
	std::condition_variable con_var; // conditon variable für semaphore
	short runs; // runcounter

public:

	semaphore(short runs=1): runs(runs){}

	void open();
	void block(short id);
};