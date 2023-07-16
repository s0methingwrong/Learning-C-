#pragma once
#include <iostream>
using namespace std;

template<class T>
class my_vector
{
private:
	T* m_arr;
	int m_count;
	int m_capacity;

public:
	my_vector();

	void push_back(T item);
	int count() const;
	T& operator[](int index);
	void remove_at(int index);
};

template<class T>
my_vector<T>::my_vector()
{
	m_count = 0;
	m_capacity = 10;
	m_arr = new T[m_capacity];
}

template<class T>
void my_vector<T>::push_back(T item)
{
	if (m_count == m_capacity) {
		T* temp = new T[m_capacity * 2];
		for (int i = 0; i < m_count; i++)
		{
			temp[i] = m_arr[i];
		}
		delete[] m_arr;
		m_arr = temp;
		m_capacity *= 2;
	}
	m_arr[m_count] = item;
	m_count++;
}

template<class T>
int my_vector<T>::count() const
{
	return m_count;
}

template<class T>
T& my_vector<T>::operator[](int index)
{
	if (index < 0 || index >= count()) {
		throw exception("incorrect index");
	}
	return m_arr[index];
}

template<class T>
void my_vector<T>::remove_at(int index)
{
	if (index < 0 || index >= count()) {
		throw exception("incorrect index");
	}
	for (int i = index; i < m_count - 1; i++)
	{
		m_arr[i] = m_arr[i + 1];
	}
	m_count--;
}
