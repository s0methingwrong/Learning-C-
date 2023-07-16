#include <iostream>
#include "server.h"
#include <string>
#include "package_descriptor_mail.h"

descriptor_message* create_descriptor_message() {
	cout << "Создание описателя сообщения: ";
	unsigned int len_message;
	cout << "Введите длину сообщения: ";
	cin >> len_message;
	
	cin.ignore();

	char* message = new char[len_message + 1];
	cout << "Введите сообщение: ";
	cin.getline(message, len_message);

	descriptor_message* d_mes = new descriptor_message(len_message, message);
	return d_mes;
}

void fill_descriptor_links(descriptor_link** descriptor_links, int n) {
	for (int i = 0; i < n; i++)
	{
		cout << "Выберите тип протокола 1.ftp, 2.http ";
		int pr;
		cin >> pr;
		cin.ignore();

		type_protokol protok = (type_protokol)(pr - 1);
		string server_name;
		cout << "Имя сервера: ";
		getline(cin, server_name);

		descriptor_links[i] = new descriptor_link(protok, server_name);
	}
}

package_descriptor* create_package_descriptor() {
	cout << "1.Почта" << endl;
	cout << "2.Файл" << endl;
	cout << "3.Гипертекст" << endl;

	int choice;
	cin >> choice;
	cin.ignore();

	string address_sender, address_recipient;

	cout << "Введите адрес отправителя: ";
	getline(cin, address_sender);

	cout << "Введите адрес получателя: ";
	getline(cin, address_recipient);

	descriptor_message* d_mes = create_descriptor_message();

	if (choice == 1) {
		cout << "Введите имя пользователя: ";
		string user_name;
		cin >> user_name;

		package_descriptor_mail* p = new package_descriptor_mail(address_sender, address_recipient, d_mes, user_name);
		return p;
	}
	else if (choice == 2) {
		cout << "Выберите тип кода 1.ACII, 2.BIN" << endl;
		int type_c;
		cin >> type_c;

		type_code t = (type_code)(type_c - 1);

		cout << "Выберите тип информации 1.Управляющая, 2.Данные" << endl;
		int type_i;
		cin >> type_i;

		info_type ti = (info_type)(type_i - 1);
		package_descriptor_file* p = new package_descriptor_file(address_sender, address_recipient, d_mes, t, ti);
		return p;
	}
	else {
		int count_url;
		cout << "Введите кол-во ссылок: ";
		cin >> count_url;

		descriptor_link** links = new descriptor_link*[count_url];
		fill_descriptor_links(links, count_url);

		cout << "Выберите тип кода 1.ACII, 2.BIN" << endl;
		int type_c;
		cin >> type_c;

		type_code t = (type_code)(type_c - 1);

		cout << "Выберите тип информации 1.Управляющая, 2.Данные" << endl;
		int type_i;
		cin >> type_i;

		info_type ti = (info_type)(type_i - 1);

		package_descriptor_hypertext* p = new package_descriptor_hypertext(address_sender, address_recipient, d_mes, t, ti, count_url, links);
		return p;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

	string name;
	cout << "Введите имя сервера: ";
	cin >> name;

	string address;
	cout << "Введите адрес сервера: ";
	cin >> address;

	auto ser = make_unique<server>(name, address);
	int action;

	do
	{
		cout << "1.Добавить пакет" << endl;
		cout << "2.Поиск пакета" << endl;
		cout << "3.Показать таблицу передач" << endl;
		cout << "4.Удалить пакет" << endl;
		cout << "5.Показать информацию обо всех отправителях пакетов" << endl;
		cout << "0.Выход" << endl;

		cin >> action;
		cin.ignore();

		if (action == 1) {
			package_descriptor* p = create_package_descriptor();
			ser->add(p);
		}
		else if (action == 2) {
			string address;
			cout << "Введите адрес получателя: ";
			getline(cin, address);

			cout << "Выберите тип пакета 1.mail, 2.file, 3.hypertext" << endl;
			int t;
			cin >> t;
			type_package type = (type_package)(t - 1);

			package_descriptor* package = ser->find_package(address, type);
			if (package != nullptr) {
				package->show_info();
			}
			else {
				cout << "Пакет не найден" << endl;
			}
		}
		else if (action == 3) {
			ser->show();
		}
		else if (action == 4) {
			string address;
			cout << "Введите адрес получателя: ";
			getline(cin, address);

			cout << "Выберите тип пакета 1.mail, 2.file, 3.hypertext" << endl;
			int t;
			cin >> t;
			type_package type = (type_package)(t - 1);

			if (ser->remove_package(address, type)) {
				cout << "Удаление успешно" << endl;
			}
			else {
				cout << "Пакет не найден" << endl;
			}
		}
		else if (action == 5) {
			ser->show_senders();
		}
	} 
	while (action != 0);

}
