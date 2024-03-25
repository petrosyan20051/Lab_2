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

// Задачи:
/// 1. Сделать проверку целостности читаемых данных (п2)
/// 2. Сделать возможность выхода на предыдущий пункт меню (п1, п2, п3, п4, п5)
/// 3. Узнать, почему в п1 wr записывает "мусорные" значения в файл и исправить это


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	typedef double elemType;

	char action = -1;
	string temp;

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
				streampos p = cin.peek();
				if (p != EOF && p != '\n')
				{
					cout << "Введено некорректное значение, попробуйте ещё раз" << endl;
					cin.clear();
					continue;
				}
				break;
			}

			double* out = new double;
			try
			{
				out = new double[size];
			}
			catch (bad_alloc)
			{
				delete out;
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
				if (iss.fail() || !iss.eof())
					cout << "Обнаружено некорректное значение. Попробуйте ещё раз!" << endl;
				else
				{
					out[i] = num;
					i++;
				}
			}

			bool rewrite = true;
			string path;
			cout << "Введите имя двоичного файла: ";
			cin >> path;
			if (exists(path))
			{
				cout << "Указанный файл уже существует! Желаете перезаписать? ('y' - да, 'n' - нет): ";
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

			wr.write((char*)out, size * sizeof(elemType));

			/*
			ifstream ex;
			ex.open(path, ios::binary);
			double exa;
			ex >> exa; cout << exa << endl;
			*/
			wr.close();
			system("cls");
		}
		else if (action == '2')
		{
			system("cls");

			ifstream rd;
			bool ret = false;
			string path;
			cout << "Введите название двоичного файла ('*' для возвращения в меню): ";
			while (true)
			{
				cin.ignore(1, '\n');
				getline(cin, path);
				if (path == "*")
				{
					ret = true;
					break;
				}
				// Пытаемся открыть поток. В случае успеха используем побитовое "или" для флагов ios::binary и ios::ate (перемещение указателя за пределы файла) 
				rd.open(path, ios::binary | ios::ate);
				if (!rd.is_open())
				{
					cout << "Не удалось открыть файл! Попробуйте ещё раз." << endl;
					continue;
				}
				break;
			}

			if (ret)
				continue;
			// Находим длину последовательности двоичных символов
			size_t len = rd.tellg();
			elemType* in;
			try
			{
				in = new elemType[len];
			}
			catch (bad_alloc)
			{
				cout << "Ошибка выделения памяти!\n"
					<< "Код ошибки: " << errno << endl;
				perror("Системное сообщение об ошибке: ");
				_set_errno(0);
				continue;
			}
			rd.read((char*)in, len);
			rd.close();

			// Находим: 1. Максимальную длину между наибольшим порядковым номером числа и строки "Номер |" (7)
			//			2. Максимальную длину прочитанных значений
			size_t max_order = max(to_string(len).length(), 7),
				   max_number = 0;

			rd.seekg(0);
			for (size_t i = 0; i < len / sizeof(elemType); i++)
				if (to_string(in[i]).length() > max_number)
					max_number = to_string(in[i]).length();

			// Выводим массив значений
			cout << setw(max_order) << "Номер |" << setw(max_number) << "Значение" << endl;
			for (size_t i = 0; i < len / sizeof(elemType); i++)
				cout << setw(max_order) << i + 1 << setw(max_number) << in[i] << endl;
			delete [] in;
		}


	} while (true);

	return 0;
}