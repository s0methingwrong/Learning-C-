#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

struct Info // элемент таблицы
{
	int busy = 0; // признак занятости
	int key; // ключ
	char data[100]; // информация
};

class table
{
private:
	unsigned int size = 10;
	unsigned int count;
	Info* data;

	void destroy();

public:
	table();	//конструктор по умолчанию
	table(Info* elem, int n);	//конструктор из массива
	table(const table& t); //конструктор копирования
	table(table&& t); //конструктор перемещения
	~table();	// деструктор

	table& operator= (const table& t); //оператор присваивания
	table& operator=(table&& t); //оператор перемещения

	table& operator+= (const Info& t);
	table& operator-= (const Info& t);

	Info operator[] (int key); // получение элемента по ключу
	bool operator() (int key); // проверка существования элемента по ключу

	void Clear(); //сжатие таблицы (условное, поскольку память статическая)

	friend ostream& operator << (ostream& str, const table& t); //вывод
	friend istream& operator >> (istream& str, table& t); //ввод

private:
	unsigned int Hash(int key); //функция хеширования
};
