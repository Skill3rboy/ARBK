

#include "semaphoren.h"

semaphore s(1); // allow 1 semaphore

void thread1()
{
	s.block(1);
	for(char letter='a';letter<='z';letter++)
	{
		std::cout << letter << ", ";
	}

	std::cout << std::endl;

	s.open();
}

void thread2()
{
	s.block(2);
	for (char letter = 'A'; letter <= 'Z'; letter++)
	{
		std::cout << letter << ", ";
	}

	std::cout << std::endl;

	s.open();
}

void thread3()
{
	s.block(3);
	for (short number = 0; number <= 32; number++)
	{
		std::cout << number << ", ";
	}

	std::cout << std::endl;

	s.open();
}

int main()
{
	std::thread T1(thread1);
	std::thread T2(thread2);
	std::thread T3(thread3);

	std::cout << "Rumble the semaphore!" << std::endl;

	T1.join();
	T2.join();
	T3.join();

	std::cout << "Rumble over!" << std::endl;

	system("PAUSE");
	return 0;
}
