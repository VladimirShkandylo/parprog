#include "Work.h"

Work::Work(std::vector <int> arrA, int countTh, int b) : arrA(arrA), countThreads(countTh), b(b)
{
	executeSingleThread();
	executeThreadCS();
	executeThreadRV();
}

void Work::executeSingleThread()
{
	double result = 0;

	double time = omp_get_wtime();
	for (int i = 0; i < arrA.size(); i++) {
		if (arrA[i] == b) {
			result++;
		}
	}
	time = omp_get_wtime() - time;

	std::cout << "Выполнение в однопоточном режиме. Результат: " << result << ". Время выполнения: " << time << "\n";
}

void Work::executeThreadCS()
{
	double result = 0;
	double pResult = 0;

	double time = omp_get_wtime();
	omp_set_dynamic(false);
	omp_set_num_threads(countThreads);
#pragma omp parallel firstprivate(pResult) shared(result) 
	{
		pResult = 0;
#pragma omp for
		for (int i = 0; i < arrA.size(); i++) {
			if (arrA[i] == b) {
				pResult++;
			}
		}
#pragma omp critical
		{
			result += pResult;
		}
	}
	time = omp_get_wtime() - time;
	std::cout << "Выполнение в многопоточном режиме(critical section). Результат: " << result << ". Время выполнения: " << time << "\n";
}

void Work::executeThreadRV()
{
	double result = 0;

	double time = omp_get_wtime();
#pragma omp parallel for reduction (+:result)	
	for (int i = 0; i < arrA.size(); i++) {
		if (arrA[i] == b) {
			result++;
		}
	}
	time = omp_get_wtime() - time;
	std::cout << "Выполнение в многопоточном режиме(reductive variable). Результат: " << result << ". Время выполнения: " << time;
}
