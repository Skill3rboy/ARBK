#include <iostream>
#include <thread>
#include <mutex>


std::mutex mutex;

void thread1()
{
	mutex.lock();

	
	for(char letter='a';letter<='z';letter++)
	{
		std::cout << letter << ", ";
	}
	std::cout << std::endl;
	mutex.unlock();
}

void thread2()
{
	mutex.lock();

	
	for (short number =0; number <= 32; number++)
	{
		std::cout << number << ", ";
	}
	std::cout << std::endl;
	mutex.unlock();
}


void thread3()
{
	mutex.lock();


	for (char letter = 'A'; letter <= 'Z'; letter++)
	{
		std::cout << letter << ", ";
	}
	std::cout << std::endl;
	mutex.unlock();
}

int main()
{
	std::thread T1(thread1);
	std::thread T2(thread2);
	std::thread T3(thread3);

	std::cout << "Sync Rumble!" << std::endl;
	T1.join();
	T2.join();
	T3.join();
	std::cout << std::endl;
	std::cout << "Rumble Over" << std::endl;

	system("PAUSE");
	return 0;
}