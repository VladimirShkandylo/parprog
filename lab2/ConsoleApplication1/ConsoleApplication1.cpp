// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Task.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	int elementCount;
	int threadCount;
	int b; 

	bool errorFlag = true;

	do {
		std::cout << "Для выхода из программы введите 0.\nВведите количество элементов от 100000 до 1000000:\n";

		if (std::cin >> elementCount && elementCount >= 0) {
			if (elementCount == 0)
			{
				exit(0);
			}

			if (elementCount >= 100000 && elementCount <= 1000000) {
				errorFlag = false;
			}
			else {
				std::cout << "Значение должно быть в промежутке от 100000 до 1000000! Попробуйте еще раз";
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
		}
		else {
			std::cout << "Ошибка ввода! Попробуйте еще раз";
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}

	} while (errorFlag);

	errorFlag = true;

	do {
		std::cout << "Для выхода из программы введите 0.\nВведите количество потоков:\n";

		if (std::cin >> threadCount && threadCount >= 0) {
			if (threadCount == 0)
			{
				exit(0);
			}
			errorFlag = false;
		}
		else {
			std::cout << "Ошибка ввода! Попробуйте еще раз";
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}

	} while (errorFlag);

	do {
		std::cout << "Для выхода из программы введите 0.\nВведите число для поиска в списке от 100 до 1000000:\n";

		if (std::cin >> b && b >= 100) {
			errorFlag = false;
		}
		else {
			std::cout << "Ошибка ввода! Попробуйте еще раз";
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}

	} while (errorFlag);

	Task task(elementCount, threadCount, b);

	std::cout << "\n\nКонец программы!";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
