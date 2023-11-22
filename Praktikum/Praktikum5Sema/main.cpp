

#include "semaphoren.h"

semaphore s(1); // allow 1 semaphore

void thread1() // thread 1 a-z
{
	s.block(1); // blocks thread 1
	for(char letter='a';letter<='z';letter++)
	{
		std::cout << letter << ", ";
	}

	std::cout << std::endl;

	s.open(); // open the thread
}

void thread2() // thread 2 0-32
{
	s.block(2); // block thread 2
	
	for (short number = 0; number <= 32; number++)
	{
		std::cout << number << ", ";
	}
	std::cout << std::endl;

	s.open(); // open thread
}

void thread3() // thread 3 A-Z
{
	s.block(3); // block thread 3
	
	for (char letter = 'A'; letter <= 'Z'; letter++)
	{
		std::cout << letter << ", ";
	}
	std::cout << std::endl;

	s.open(); // open thread
}

int main()
{
	// Threads erstellen
	std::thread T1(thread1);
	std::thread T2(thread2);
	std::thread T3(thread3);

	std::cout << "Rumble the semaphore!" << std::endl;
	// threads starten
	T1.join();
	T2.join();
	T3.join();

	std::cout << "Rumble over!" << std::endl;

	system("PAUSE");
	return 0;
}
