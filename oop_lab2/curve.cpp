#include "curve.h"

curve::curve(double r)
{
	this->r = r;
}

void curve::set_r(double r)
{
	this->r = r;
}

double curve::get_r()
{
	return r;
}

double curve::calc_distance(int fi)
{
	float dis = sqrt(2 * (r / 2) * (r / 2) * cos(2 * fi));		// расстояние в полярных координатах
	return dis;
}

double curve::cur_r_fi(int fi)
{
	int dis = (2 * (r / 2) * (r / 2)) / (3 * sqrt(2 * (r / 2) * (r / 2) * cos(2 * fi)));    // 2*c^2 / 3р
	return dis;
}

int curve::cur_r(int dlina_rad)
{
	int rad = (2 * (r / 2) * (r / 2)) / (3 * dlina_rad);		// здесь мы указываем длину радиуса и из нее находим радиус кривизны
	return rad;
}


double curve::get_sector(int fi)
{
	double s = (r / 2) * (r / 2) / (2 * sin(2*fi));
	return s;
}

double curve::calc_area()
{
	return (r / 2) * (r / 2);		// (r / 2) <=> c
}
