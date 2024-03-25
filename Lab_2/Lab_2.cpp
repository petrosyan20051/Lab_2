#include <iostream>
#include <windows.h>
#include <filesystem>
#include <errno.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>
#include <conio.h>
#include <fstream>

using namespace std;
using namespace filesystem;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	typedef double elemType;

	char action = -1;
	string temp, path;

	do
	{
		cout << "Выберите действие:\n"
			<< "1. Создать файл с исходными данными\n"
			<< "2. Загрузить исходные данные\n"
			<< "3. Вывести исходные данные\n"
			<< "4. Обработать данные\n"
			<< "5. Завершить работу с программой" << endl;
		action = _getch();
		
		if ((int)action < 49 || (int) action > 53)
		{
			system("cls");
			cout << "Введено некорректное значение!\n";
			continue;
		}

		if (action == '5')
		{
			system("cls");
			exit(0);
			_getch();
			break;
		}
		else if (action == '1')
		{
			system("cls");
			size_t size;
			istringstream iss;

			/*
			do
			{
				cout << "Введите количество значений, которые вы хотите записать: " << endl;
				cin >> temp;
				
				iss.clear();
				istringstream iss(temp);
				iss >> size;
			} while (!iss.eof() && size == 0);
			*/

			cout << "Введите количество значений, которые вы хотите записать: " << endl;
			while (true)
			{
				cin >> ws >> size;
				int p = cin.peek();
				if (p != EOF && p != '\n')
				{
					cout << "Введено некорректное значение, попробуйте ещё раз" << endl;
					cin.clear();
				}
				break;
			}

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
			size_t i = 0;

			cout << "Поочерёдно вводите значения:\n";
			while (i < size)
			{
				cin >> temp;
				replace(temp.begin(), temp.end(), ',', '.');
				istringstream iss(temp);
				iss >> num;
				if (iss.fail())
					cout << "Обнаружено некорректное значение. Попробуйте ещё раз!" << endl;
				else
				{
					arr[i] = num;
					i++;
				}
			}

			bool rewrite = true;
			cout << "Введите имя двоичного файла: ";
			cin >> path;
			if (exists(path))
			{
				cout << "Указанный файл уже существует! Желаете перезаписать? ('y' - да, 'n' - нет)";
				do
				{
					cin >> temp;
				} while (temp != "y" && temp != "n");

				if (temp == "n")
					rewrite = false;
			}

			if (!rewrite)
				continue;

			ofstream wr;
			wr.open(path, ios::binary);
			if (!wr.is_open())
			{
				cout << "Файл \"" << path << "\" не открыт, попробуйте ещё раз!\n"
					<< "Код ошибки: " << errno << endl;
				perror("Системное сообщение об ошибке: ");
				continue;
			}

			wr.write((char*)arr, size * sizeof(elemType));
			system("cls");
			break;
		}
		else if (action == '2')
		{
			/// Сделать проверку целостности читаемых данных...

			system("cls");

		}


	} while (true);

	return 0;
}