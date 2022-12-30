#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Task {
public:
	Task(int countElements, int threadCount, int b);
private:
	std::vector <int> arrA;
	int b;
	friend void writeOutputData(std::string name, int result, double time);
	void initArrayRandomData(int countElements);
};