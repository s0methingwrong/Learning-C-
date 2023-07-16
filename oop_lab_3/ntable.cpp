#include "ntable.h"
#include <string.h>

table::table() : count(0) //обнуляем число элементов
{
}

table::~table()
{
}

table::table(Info* elem, int n)
{
    if (n > size) throw "Too big array"; //если размер массива больше максимального
    count = n; //сохраняем количество
    for (int i = 0; i < n; i++) { //идём по элементам
        int j = Hash(elem[i].key); //получаем адрес
        if (data[j].busy != 0) { //если уже занят
            for (int k = 1; k < size; k++) { //ищем новый адрес
                j = Hash(elem[i].key + k);
                if (data[j].busy == 0) break;
            }
        }
        if (data[j].busy != 0) throw "Too many keys with one hash"; //все места заняты - ошибка
        data[j].busy = 1; //записываем элемент, помечаем место занятым
        data[j].key = elem[i].key;
        strcpy(data[j].data, elem[i].data);
    }
}

table::table(const table& t) //конструктор копирования
{
    count = t.count; //копируем всё из другого экземпляра
    for (int i = 0; i < size; i++) {
        data[i].key = t.data[i].key;
        data[i].busy = t.data[i].busy;
        strcpy(data[i].data, t.data[i].data);
    }
}

table& table::operator= (const table t) //оператор присваивания
{
    count = t.count; //копируем всё из другого экземпляра
    for (int i = 0; i < size; i++) {
        data[i].key = t.data[i].key;
        data[i].busy = t.data[i].busy;
        strcpy(data[i].data, t.data[i].data);
    }
    return *this;
}

table& table::operator+= (const Info& t)
{
    if (count == size) return *this; //если таблица уже заполнена, ничего не делаем
    int j = Hash(t.key); //получаем адрес
    if (data[j].busy != 0) { //если место занято, ищём новое
        for (int k = 1; k < size; k++) {
            j = Hash(t.key + k);
            if (data[j].busy == 0) break;
        }
    }
    if (data[j].busy != 0) return *this; //если все места заняты, ничего не делаем
    data[j].busy = 1; //записываем новый элемент
    data[j].key = t.key;
    strcpy(data[j].data, t.data);
    count++; //увеличиваем количество
    return *this;
}

table& table::operator-= (const Info& t)
{
    if (count == 0) return *this; //если таблица пуста, ничего не делаем
    int j = Hash(t.key); //получаем адрес
    if (data[j].busy == 0 || data[j].key != t.key) { //если место свободно или на нём другой элемент
        for (int k = 1; k < size; k++) { //перебираем другие адреса
            j = Hash(t.key + k);
            if (data[j].busy != 0 && data[j].key == t.key) break;
        }
    }
    if (data[j].busy == 0 || data[j].key != t.key) return *this; //не нашли - ничего не делаем
    data[j].busy = 0; //условно удаляем
    count--; //уменьшаем количество
    return *this;
}

Info table::operator[] (int key)
{
    Info null; //пустой элемент для возврата
    strcpy(null.data, "Not exist");
    if (count == 0) return null; //если таблица пуста, возвращаем пустой
    int j = Hash(key); //ищем элемент аналогично прочим функциям
    if (data[j].busy == 0) {
        for (int k = 1; k < size; k++) {
            j = Hash(key + k);
            if (data[j].busy != 0 && data[j].key == key) break;
        }
    }
    if (data[j].busy == 0 || data[j].key != key) return null; //если не нашли, возвращаем пустой
    else return data[j]; //иначе возвращаем найденный
}

bool table::operator() (int key)
{
    if (count == 0) return false; //аналогично [], только вместо элемента возвращаем true/false
    int j = Hash(key);
    if (data[j].busy == 0) {
        for (int k = 1; k < size; k++) {
            j = Hash(key + k);
            if (data[j].busy != 0 && data[j].key == key) break;
        }
    }
    if (data[j].busy == 0 || data[j].key != key) return false;
    else return true;
}

void table::Clear()
{
    if (count == 0) return; //если таблица пуста, нечего сжимать
    for (int i = 0; i < size; i++) { //идём по массиву
        if (data[i].busy == 0) continue; //если место свободно, пропускаем
        int j = Hash(data[i].key); //определяем "идеальный" адрес
        if (i == j) continue; //если элемент на нём и стоит, пропускаем
        for (int k = 0; k < size && j < i; k++) { //перебираем другие подходящие адреса, расположенные раньше текущего
            j = Hash(data[i].key + k);
            if (data[j].busy == 0) break; //если нашли свободный, прерываем
        }
        if (data[j].busy == 0 && j < i) { //если нашли свободный и он раньше текущего
            data[j] = data[i]; //кладём элемент на лучшую позицию
            data[i].busy = 0; //старое место освобождаем
        }
    }
}

unsigned int table::Hash(int key)
{
    return key % size; //вычисляем адрес элемента как остаток от деления на максимальный размер таблицы
}

ostream& operator << (ostream& str, table& t) //вывод
{
    str << endl;
    for (int i = 0; i < t.size; i++) { //выводим все элементы, кроме условно удалённых
        if (t.data[i].busy == 0) continue;
        str << i << ": key = " << t.data[i].key << ", " << t.data[i].data << endl;
    }
    return str;
}

istream& operator >> (istream& str, table& t) //ввод
{
    Info tmp; //временная переменная для элемента
    str >> tmp.key; //ввод ключа
    str >> tmp.data; //ввод информации
    t += tmp; //добавление элемента
    return str;
}
