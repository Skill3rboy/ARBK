#include <iostream>
#include <thread>
#include <mutex>


std::mutex mutex; // Mutex objekt erstellen, managet resurcen für threads

void thread1() // thread 1 a-z
{
	mutex.lock(); // Mutex sperren

	
	for(char letter='a';letter<='z';letter++)
	{
		std::cout << letter << ", ";
	}
	std::cout << std::endl;
	mutex.unlock(); // wieder freigeben
}

void thread2() // Thread 2 0-32
{
	mutex.lock(); // sperren

	
	for (short number =0; number <= 32; number++)
	{
		std::cout << number << ", ";
	}
	std::cout << std::endl;
	mutex.unlock(); // freigeben
}


void thread3() // thread 3 A-Z
{
	mutex.lock(); // Sperren


	for (char letter = 'A'; letter <= 'Z'; letter++)
	{
		std::cout << letter << ", ";
	}
	std::cout << std::endl;
	mutex.unlock(); // Freigeben
}

int main()
{
	// Erstellung 3 Threads
	std::thread T1(thread1);
	std::thread T2(thread2);
	std::thread T3(thread3);

	//Threadsstarten
	std::cout << "Sync Rumble!" << std::endl;
	T1.join();
	T2.join();
	T3.join();
	std::cout << std::endl;
	std::cout << "Rumble Over" << std::endl;

	system("PAUSE");
	return 0;
}