
#include <iostream>
#include <thread>
#include <mutex>

void thread1() // Thread 1 a-z
{
	for (char letter = 'a'; letter <= 'z'; letter++)
	{
		std::cout << letter << ", ";
	}

	
}
void thread2() // Thread 2 0-32
{
	
	for(short number=0;number<=32;number++)
	{
		std::cout << number << ", ";
	}
}
void thread3() //thread 3 A-Z
{
	for (char letter = 'A'; letter <= 'Z'; letter++)
	{
		std::cout << letter << ", ";
	}

}


int main()
{
	std::cout << "Hello World!" << std::endl;

	//Erstellung der 3 Threads
	std::thread T1(thread1);
	std::thread T2(thread2);
	std::thread T3(thread3);
	

	std::cout << "Lets Rumble!" << std::endl; // Threads werden gestartet
	T1.join();
	T2.join();
	T3.join();
	std::cout << "Rumble Over!" << std::endl; // Alle Threads vorbei

	system("PAUSE");
	return 0;

}

