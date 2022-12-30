#include "Task.h"
#include "Work.h"

Task::Task(int countElements, int threadCount, int b)
{
	initArrayRandomData(countElements);

	Work work(arrA, threadCount, b);
}

void Task::initArrayRandomData(int countElements)
{
	srand(time(0));
	for (int i = 0; i < countElements; i++) {
		arrA.push_back(rand() % ((10000000 + 1) - 100) + 100);
	}
}

void writeOutputData(std::string name, int result, double time)
{
	std::cout << name;

	std::cout << "\nРезультат: " << result << "\nДлительность работы: " << time << " секунд.\n";
}