﻿/*
В программе циклически осуществляется вывод запроса пользователю на выбор действия и выполнение выбранного действия. Доступные действия: «1. Создать файл с исходными данными», «2. Загрузить исходные данные», «3. Вывести исходные данные», «4. Обработать данные», «5. Завершить работу с программой». Каждое действие выбирается пользователем путем однократного нажатия на соответствующую цифровую клавишу.
При выборе действия «1» у пользователя запрашивается: имя двоичного файла, в который будет сохраняться задаваемый пользователем массив; кол-во элементов массива; значения самих элементов. Результат открытия файлового потока должен проверяться. В случае ошибки, имя файла должно запрашиваться повторно. Также необходимо проверять на существование по указанному пути файла с указанным именем и, в случае его наличия, выдавать пользователю запрос на перезапись этого файла. Такую проверку можно реализовать средствами потока. Корректность вводимых пользователем числовых значений количества элементов и самих элементов должна проверяться. В случае некорректности, соответствующее значение должно запрашиваться повторно. Имя файла можно запрашивать в последнюю очередь. Это позволит (при дополнительной программной реализации такой возможности) пользователю отказаться от записи данных в файл, но при этом сформированный массив останется в памяти и будет доступен для дальнейшей обработки.
При выборе действия «2» у пользователя должен запрашиваться ввод с клавиатуры имени двоичного файла, из которого будут загружаться элементы массива. Результат открытия файлового потока должен проверяться. При неуспешном открытии потока имя файла должно запрашиваться повторно. При успешной загрузке данных, исходный массив должен сразу выводиться на экран. Должны присутствовать простейшие проверки целостности данных, загружаемых из файла.
Память под хранение элементов массива должна выделяться динамически с помощью оператора new (освобождаться – с помощью delete), размер выделяемой памяти должен определяться программой автоматически по содержимому файла (а не вводиться пользователем с клавиатуры). Результат выделения памяти должен проверяться. При неуспешном выделении должно выводиться соответствующее сообщение.
Вывод результатов на экран – форматированный. Если выводится массив, то в первой строке – порядковые номера элементов, а строго под ними – значения соответствующих элементов; в начале строки с номерами – слово «Номера:», в начале строки с элементами – слово «Элементы:».
При выборе действия «3» выполняется вывод ранее созданного (в результате выполнения действия «1») или загруженного из файла в память (в результате выполнения действия «2») исходного массива на экран.
При выборе действия «4» выполняется обработка ранее созданного или загруженного из файла в память исходного массива и вывод результатов обработки на экран.
Выбор пользователем действий «3» и «4» никогда не должен приводить к возникновению необработанных ошибок. Повторное выполнение действий «1» и «2» не должно приводить к утечке памяти.
Для возврата к выбору следующего действия (т.е. в меню) после выполнения действий «1-4» должно ожидаться нажатие пользователем любой клавиши с выводом соответствующей подсказки. Меню всегда должно выводиться в чистом окне консоли. После выбора пользователем нужного действия (пункта меню) консоль также должна очищаться.
В любом месте программы продемонстрировать применение адресной арифметики для обращения к элементам массива.
При выборе действия «5» работа программы завершается.
В программе должны присутствовать все необходимые подписи, приглашения к вводу и подсказки для пользователя на русском языке.
Если по Вашему варианту задания №6 дано 2 исходных массива, то в целях упрощения задачи можно свести условие задачи к одному массиву. Например: «заменить в первом массиве все отрицательные элементы на максимальный элемент из второго» → «заменить в массиве все отрицательные элементы на максимальный».
*/

/*
Задание 6
Дан массив P1, ... , P40.
Заменить Pmax и Pmin на среднее арифметическое всего ряда.
*/

#include <iostream>
#include <windows.h>
#include <filesystem>
#include <errno.h>
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
/// 4. Спросить у Кирилла Александровича:
///		1. Как реализовать п3 и п4 - как создать возможность использовать динамические массивы из п1 и п2, если у них ограниченная видимость?


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	locale loc("russian_russia");
	cout.imbue(loc);


	typedef double elemType;

	char action;
	string temp, path;
	bool ret = false, rewrite = false;

	elemType* arr = nullptr;
	size_t size;

	
	do
	{
		ret = false;
		cout << "Выберите действие:\n"
			<< "1. Создать файл с исходными данными\n"
			<< "2. Загрузить исходные данные\n"
			<< "3. Вывести исходные данные\n"
			<< "4. Обработать данные\n"
			<< "5. Завершить работу с программой" << endl;
		action = _getch();

		// 1. Создание файла с исходными данными
		if (action == '1')
		{
			while (true)
			{
				system("cls");

				cout << "Введите количество значений, которые вы хотите записать ('*' для возврата в меню): ";

				if ((cin.ignore(cin.rdbuf()->in_avail())).peek() == '*')
				{
					ret = true;
					break;
				}

				cin >> size;
				if (cin.peek() != '\n')
				{
					cout << "Введено некорректное значение, попробуйте ещё раз!\n"
						<< "Нажмите любую клавишу для продолжения работы" << endl;
					_getch();
					cin.clear();
					continue;
				}
				break;
			}
			if (ret)
			{
				system("cls");
				continue;
			}

			if (rewrite)
				delete[] arr;
			arr = new (nothrow) elemType[size];
			if (arr == nullptr)
			{
				cout << "Ошибка выделения памяти!\n"
					<< "Код ошибки: " << errno << endl;
				perror("Системное сообщение об ошибке: ");
				_set_errno(0);
				continue;
			}

			elemType num;
			size_t i = 0;

			if (size)
			{
				cout << "Поочерёдно вводите значения ('*' для выхода в меню):\n";
				while (i < size)
				{
					cin >> temp;
					if (temp == "*")
					{
						delete[] arr;
						system("cls");
						ret = true;
						break;
					}
					replace(temp.begin(), temp.end(), ',', '.');
					istringstream iss(temp);
					iss >> num;
					if (iss.fail() || !iss.eof())
						cout << "Обнаружено некорректное значение. Попробуйте ещё раз!" << endl;
					else
					{
						arr[i] = num;
						i++;
					}
				}
			}

			if (ret)
			{
				system("cls");
				continue;
			}

			while (true)
			{
				cout << "Введите название двоичного файла ('*' для возвращения в меню): ";
				getline(cin.ignore(cin.rdbuf()->in_avail()), path);
				if (exists(path))
				{
					cout << "Указанный файл уже существует! Желаете перезаписать? ('y' - да, 'n' - нет, '*' - вернуться меню): ";
					do
					{
						temp = _getch();
					} while (temp != "y" && temp != "n" && temp != "*");
				}
				if (temp == "*")
				{
					ret = true;
					break;
				}
				if (temp != "n")
				{
					ofstream wr;
					wr.open(path, ios::binary);
					if (!wr.is_open())
					{
						cout << "Файл \"" << path << "\" не открыт, попробуйте ещё раз!\n"
							<< "Код ошибки: " << errno << endl;
						perror("Системное сообщение об ошибке: ");
						continue;
					}
					size_t buffer[1]; buffer[0] = size;

					wr.write((char*)buffer, sizeof(size_t));
					wr.write((char*)arr, size * sizeof(elemType));
					rewrite = true;
					wr.close();
					break;
				}
				cout << endl;
			}

			if (ret)
			{
				system("cls");
				continue;
			}
			system("cls");
		}
		// 2. Загружаем данные из существующего файла
		else if (action == '2')
		{
			system("cls");

			ifstream rd;
			cout << "Введите название двоичного файла ('*' для возвращения в меню): ";
			while (true)
			{
				cin.ignore(cin.rdbuf()->in_avail()) >> path;
				if (path == "*")
				{
					ret = true;
					break;
				}
				// Пытаемся открыть поток
				rd.open(path, ios::binary);
				if (!rd.is_open())
				{
					cout << "Не удалось открыть файл! Попробуйте ещё раз." << endl;
					continue;
				}
				break;
			}

			if (ret)
			{
				system("cls");
				continue;
			}

			// count_value - количество значений в последовательности символов
			size_t count_value[1];
			rd.read((char*)count_value, sizeof(size_t));
			if (!*count_value)
			{
				rd.close();
				cout << "Файл пуст!" << endl;
				continue;
			}

			// Находим длину последовательности двоичных символов;
			rd.seekg(0, ios::end);
			size = rd.tellg();
			// Обновляем её для самой простой проверки кратности последовательности двоичных символов на длину типа данных и проверки совпадения фактического количества значений и указанного в файле
			size -= sizeof(size_t);
			rd.seekg(sizeof(size_t));

			if (size % sizeof(elemType) || *count_value != size / sizeof(elemType))
			{
				rd.close();
				cout << "Файл повреждён!" << endl;
				cout << "Нажмите любую клавишу для продолжения: " << endl;
				_getch();
				continue;
			}

			if (rewrite)
				delete[] arr;
			arr = new elemType[size / sizeof(elemType)];
			if (arr == nullptr)
			{
				rd.close();
				cout << "Ошибка выделения памяти!\n"
					<< "Код ошибки: " << errno << endl;
				perror("Системное сообщение об ошибке: ");
				cout << "Нажмите любую клавишу для продолжения: " << endl;
				_getch();
				_set_errno(0);
				continue;
			}

			rd.read((char*)arr, size);
			rd.close();


			// Находим: 1. Максимальную длину между наибольшим порядковым номером числа и строки "Номер" (5)
			//			2. Максимальную длину прочитанных значений
			size /= sizeof(elemType);
			size_t max_order = max(to_string(size).length(), 5),
				max_number = 8;

			for (size_t i = 0; i < size; i++)
			{
				istringstream iss(arr[i]);
				iss >> temp;
				if (temp.length() > max_number) max_number = temp.length();
			}

			// Выводим массив значений
			cout << setw(max_order) << "Номер" << " | " << setw(max_number) << "Значение" << endl;
			for (size_t i = 0; i < size; i++)
				cout << setw(max_order) << i + 1 << " | " << setw(max_number) << arr[i] << endl;
			rewrite = true;

			cout << "Введите любую клавишу для продолжения: ";
			_getch();
			system("cls");
		}
		// 3. Выводим загруженные данные в консоль
		else if (action == '3')
		{
			system("cls");

			if (arr == nullptr)
			{
				cout << "Массив отсутствует!\n"
					<< "Нажмите любую клавишу для продолжения работы программы: ";
				_getch();
				system("cls");
				continue;
			}

			// Находим: 1. Максимальную длину между наибольшим порядковым номером числа и строки "Номер" (5)
			//			2. Максимальную длину прочитанных значений
			size_t max_order = max(to_string(size).length(), 5),
				max_number = 8;

			for (size_t i = 0; i < size; i++)
			{
				istringstream iss(arr[i]);
				iss >> temp;
				if (temp.length() > max_number) max_number = temp.length();
			}

			// Выводим массив значений
			cout << setw(max_order) << "Номер" << " | " << setw(max_number) << "Значение" << endl;
			for (size_t i = 0; i < size; i++)
				cout << setw(max_order) << i + 1 << " | " << setw(max_number) << arr[i] << endl;
			rewrite = true;

			cout << "Введите любую клавишу для продолжения: ";
			_getch();
			system("cls");
		}
		// 4. Обрабатываем загруженные данные
		else if (action == '4')
		{
			system("cls");
			if (arr == nullptr)
			{
				cout << "Массив отсутствует!\n"
					<< "Нажмите любую клавишу для продолжения работы программы: ";
				_getch();
				system("cls");
				continue;
			}

			elemType mx = -9e+99, 
					 mn = 9e99,
					 s = 0;

			// Ищем максимальное и минимальное число и сумму все последовательности массива
			for (size_t i = 0; i < size; i++)
			{
				if (arr[i] > mx) mx = arr[i];
				if (arr[i] < mn) mn = arr[i];
				s += arr[i];
			}

			double avg = s / size;
			cout << "Файл содержит " << size << " значений(-ия, -ие)\n"
				<< "Максимальное значение = " << mx << '\n'
				<< "Минимальное значение = " << mn << '\n'
				<< "Среднее арифметическое ряда = " << avg << endl;

			// Заменяем Pmax и Pmin на avg
			for (size_t i = 0; i < size; i++)
			{
				if (arr[i] == mx) arr[i] = avg;
				if (arr[i] == mn) arr[i] = avg;
			}

			// Находим: 1. Максимальную длину между наибольшим порядковым номером числа и строки "Номер" (5)
			//			2. Максимальную длину прочитанных значений
			size_t max_order = max(to_string(size).length(), 5),
				max_number = 8;

			for (size_t i = 0; i < size; i++)
			{
				istringstream iss(arr[i]);
				iss >> temp;
				if (temp.length() > max_number) max_number = temp.length();
			}

			// Выводим массив значений
			cout << setw(max_order) << "Номер" << " | " << setw(max_number) << "Значение" << endl;
			for (size_t i = 0; i < size; i++)
				cout << setw(max_order) << i + 1 << " | " << setw(max_number) << arr[i] << endl;
			rewrite = true;
		}
		// 5. Завершаем работу программы
		else if (action == '5')
		{
			system("cls");
			exit(0);
			break;
		}
		// Обрабатываем исключение ввода действия
		else
		{
			system("cls");
			cout << "Введено некорректное значение!\n";
		}
	} while (true);
	
	return 0;
}