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

	unsigned short int action;
	string temp;

	do
	{
		cout << "Выберите действие:\n"
			<< "1. Создать файл с исходными данными\n"
			<< "2. Загрузить исходные данные\n"
			<< "3. Вывести исходные данные\n"
			<< "4. Обработать данные\n"
			<< "5. Завершить работу с программой" << endl;
		cin >> temp;
		istringstream iss(temp);
		iss >> action;

		if (iss.fail())
		{
			cout << "Введено некорректное значение!\n"
				<< "Код ошибки:" << errno << endl;
			perror("Системное сообщение об ошибке: ");
			_set_errno(0);
			continue;
		}
		else if ((int) action <= 0 || (int) action > 5)
		{
			cout << "Введено некорректное значение!\n";
			continue;
		}

		switch (action)
		{
		case 5:
			exit(0);
			_getch();
			break;
		case 1:
			size_t size;
			do
			{
				cout << "Введите количество элементов, которые вы хотите записать: " << endl;
				cin >> temp;
				istringstream iss(temp);
				iss >> size;
			} while (iss.fail());

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

			string path;
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
		};
	} while (true);

	return 0;
}