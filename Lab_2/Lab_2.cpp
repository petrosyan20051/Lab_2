#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <errno.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	unsigned short int action;

	do
	{
		cout << "Выберите действие:\n"
			<< "1. Создать файл с исходными данными\n"
			<< "2. Загрузить исходные данные\n"
			<< "3. Вывести исходные данные\n"
			<< "4. Обработать данные\n"
			<< "5. Завершить работу с программой" << endl;
		cin >> action;

		if (cin.fail())
		{
			cout << "Введено некорректное значение!\n"
				<< "Код ошибки:" << errno << endl;
			perror("Системное сообщение об ошибке: ");
			_set_errno(0);
			continue;
		}
		else if (action == 0 || action > 5)
		{
			cout << "Введено некорректное значение!\n";
			continue;
		}

		switch (action == 5)
		{
		case 5:
			cout << "Работа программы завершена!" << endl;
			exit(0);
			break;
		case 1:
			size_t size;
			do
			{
				cout << "Введите количество элементов, которые вы хотите записать: " << endl;
				cin >> size;
			} while (cin.fail());
			
			double* arr = new double;
			try
			{
				arr = new double[size];
			}
			catch (bad_alloc)
			{
				cout << "Ошибка выделения памяти!\n"
					<< "Код ошибки: " << errno << endl;
				perror("Системное сообщение об ошибке: ");
				_set_errno(0);
				continue;
			}

			string value;
			double num;
			
			cout << "Поочерёдно вводите значения:\n";
			for (size_t i = 0; i < size; i++)
			{
				cin >> value;
				replace(value.begin(), value.end(), ',', '.');
				istringstream iss(value);
				iss >> num;
				if (iss.fail())
				{
					iss.clear();
					int position = iss.tellg();
					char c = iss.peek();
					cout << "Файл содержит некорректное значение: \"" << value << "\"\n"
						<< "Некорректный символ последовательности: \'" << c << "\'\n"
						<< "Абсолютная позиция некорректного символа последовательности: " << position + 1 << '\n';
					i--;
					cout << "Введите значение повторно: ";
				}
			}

			bool error = false;
			string filename;
			do
			{ 
				cout << "Введите двоичное имя файла: " << endl;
				cin >> filename;
				for (size_t index = 0, count = 0; index < filename.find('.'); index++)
				{
					if (filename[index] == '1' || filename[index] == '0')
						count++;
					else
					{
						cout << "Некорректное имя файла!";
						error = true;
						break;
					}
				}
			} while(error)
			
			

		}


	} while (true);

	return 0;
}