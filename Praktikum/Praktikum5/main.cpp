
#include <iostream>
#include <thread>
#include <mutex>

void thread1()
{
	for (char letter = 'a'; letter <= 'z'; letter++)
	{
		std::cout << letter << ", ";
	}

	
}
void thread2()
{
	
	for(short number=0;number<=32;number++)
	{
		std::cout << number << ", ";
	}
}
void thread3()
{
	for (char letter = 'A'; letter <= 'Z'; letter++)
	{
		std::cout << letter << ", ";
	}

}


int main()
{
	std::cout << "Hello World!" << std::endl;

	std::thread T1(thread1);
	std::thread T2(thread2);
	std::thread T3(thread3);
	

	std::cout << "Lets Rumble!" << std::endl;
	T1.join();
	T2.join();
	T3.join();
	std::cout << "Rumble Over!" << std::endl;

	system("PAUSE");
	return 0;

}

