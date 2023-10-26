#include "semaphoren.h"

// If funktion called, mutex will get blocked
// If funktion done, notify
//if mutex get the notify, mutex will open
//mutex open== next thread can start
void semaphore::open()
{

	//mutex get unique lock
	//thread open
	//mutex open
	std::unique_lock<std::mutex> lock(mutex);

	runs++;

	std::cout << " Next Thread" << std::endl << std::endl;

	con_var.notify_one();
}

void semaphore::block(short id)
{
	// mutex get unique lock
	// if no thread is ready write it
	// conditionvariable wating until mutex is no longer blocked
	std::unique_lock<std::mutex> lock(mutex);

	if(runs==0)
	{
		std::cout << "Thread waiting: " << id << std::endl;
		con_var.wait(lock);
		std::cout << "Thread starting: " << id << std::endl;
	}

	runs--;
}

