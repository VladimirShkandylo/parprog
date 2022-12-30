#pragma once
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <omp.h>
#include <conio.h>
#include <vector>

class Work {
public:
	Work(std::vector <int> arrA, int countTh, int b);
private:
	int countThreads;
	std::vector <int> arrA;
	int b;
	void executeSingleThread();
	void executeThreadCS();
	void executeThreadRV();
};