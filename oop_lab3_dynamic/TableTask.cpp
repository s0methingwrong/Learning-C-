#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "table.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	//setlocale(LC_ALL, ".UTF8");

	{
		table a;
		int action;

		do
		{
			cout << "1.Добавить данные" << endl;
			cout << "2.Поиск по ключу" << endl;
			cout << "3.Вывод таблицы" << endl;
			cout << "4.Удаление по ключу" << endl;
			cout << "5.Очистка от удаленных" << endl;
			cout << "0.Выход" << endl;

			cin >> action;

			if (action == 1) {
				Info el;
				el.busy = 1;

				cout << "Введите ключ" << endl;
				cin >> el.key;
				cout << "Введите данные: ";
				cin.ignore();
				cin.getline(el.data, 100);

				a += el;
			}
			else if (action == 2) {
				int key;
				cout << "Введите ключ: ";
				cin >> key;


				if (a(key)) {
					cout << "Запись найдена: " << a[key].data << endl;
				}
				else {
					cout << "Нет такой записи" << endl;
				}
			}
			else if (action == 3) {
				cout << a << endl;
			}
			else if (action == 4) {
				int key;
				cout << "Введите ключ: ";
				cin >> key;
				if (a(key)) {
					a -= a[key];
					cout << "Операция успешно выполнена" << endl;
				}
				else {
					cout << "Нет такой записи" << endl;
				}
			}
			else if (action == 5) {
				a.Clear();
			}
		} while (action != 0);

	}

	_CrtDumpMemoryLeaks();
}
