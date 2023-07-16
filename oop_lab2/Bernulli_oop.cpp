#include <iostream>
#include "curve.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	cout << "Введите расстояние между фокусами: ";
	double r;
	cin >> r;

	curve cur(r);
	int action;

	do
	{
		cout << "0.Ввести координаты" << endl;
		cout << "1.Изменить расстояние между фокусами" << endl;
		cout << "2.Получить информацию о параметрах кривой" << endl;
		cout << "3.Получить расстояние до центра" << endl;
		cout << "4.Получить радиус кривизны от угла" << endl;
		cout << "5.Получить радиус кривизны от длины радиуса" << endl;
		cout << "6.Получить площадь сектора" << endl;
		cout << "7.Получить площадь" << endl;

		cin >> action;

		switch (action)
		{
		case 1:
		{
			cout << "Введите расстояние: ";
			cin >> r;
			cur.set_r(r);
			break;
		}
		case 2:
		{
			int fi;
			cout << "Введите угол:" << "\n";
			cin >> fi;
			cout << "Информация о параметрах кривой: ";
			cout << "\nУгол: " << fi << "\nРасстояние между фокусами: " << r << "\n";
			break;

		}
		case 3:
		{
			int fi;
			cout << "Введите угол:" << "\n";
			cin >> fi;
			double dis = cur.calc_distance(fi);
			cout << "Расстояние до центра: " << dis << "\n";
			break;
		}
		case 4:
		{
			int fi;
			cout << "Введите угол:" << "\n";
			cin >> fi;
			int rad = cur.cur_r_fi(fi);
			cout << "Радиус кривизны: " << rad << "\n";
			break;

		}
		case 5:
		{
			int dlina_rad;
			cout << "Введите длину радиуса" << "\n";
			cin >> dlina_rad;
			int rad = cur.cur_r(dlina_rad);
			cout << "Радиус кривизны: " << rad << "\n";
			break;
		}
		case 6:
		{
			int fi;
			cout << "Введите угол:" << "\n";
			cin >> fi;
			double sector = cur.get_sector(fi);
			cout << "Площадь сектора равна: " << sector << "\n";
			break;
		}
		case 7:
		{
			double s = cur.calc_area();
			cout << "Площадь равна: " << s << "\n";
			break;
		}
		default:
			break;
		}
	} while (true);
}
