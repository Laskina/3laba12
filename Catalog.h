#pragma once
#include <vector>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <fstream>
#include "file.h"
using namespace std;

template <class T>
class Catalog {
private:
	vector<T> vect;
	string FileName;//имя файла
public:
	void Assign(vector<T> b);
	Catalog();
	_int32 Count();
	bool Add(bool(*f)(T&, T&), T &need);
	bool Delete(bool(*f)(T&, T&), T &need);
	bool Contains(bool(*f)(T&, T&), T &need);
	bool Change(bool(*f)(T&, T&), T &need, T &next);
	vector<T> LinSearch(bool(*f)(T&, T&), T need);//линейный поиск
	vector<T> BinSearch(bool(*f)(T&, T&), T need);//бинарный поиск
	void  LoadFromFile(bool(*f)(ifstream&,T&));//загрузить из файла
	void  SaveToFile(void(*f)(ofstream&,T&));//сохранить в файл
	void Print(bool admin, void(*f)(bool,T));//печать в консоль
};

template <class T>
void Catalog<T>::Assign(vector<T> b) {
	vect.assign(b);
}

bool AskTypeOfUser(string str) {
	cout << str << endl;
	cout << "1 - Администратор" << endl;
	cout << "2 - Пользователь" << endl;
	return InputNum("", 1, 2)==1;
}

template <class T>
Catalog<T>::Catalog() {
	FileName = "file.dat";
}

template <class T>
_int32 Catalog<T>::Count() {
	return vect.size();
}
template <class T>
bool Catalog<T>::Add(bool(*f)(T&, T&), T &need) {
	for (T tmp : vect) {
		if (!f(tmp, need) && !f(need, tmp))
			return false;
	}
	vect.push_back(need);
	return true;
}
template <class T>
bool Catalog<T>::Delete(bool(*f)(T&, T&), T &need) {
	for (auto tmp = vect.begin(); tmp != vect.end(); tmp++)
	{
		if (!f(*tmp, need) && !f(need, *tmp))
		{
			vect.erase(tmp);
			return true;
		}
	}
	return false;
}
template <class T>
bool Catalog<T>::Change(bool(*f)(T&, T&), T &need, T &next){
	for (auto tmp = vect.begin(); tmp != vect.end(); tmp++)
	{
		if (!f(*tmp, need) && !f(need, *tmp))
		{
			*tmp = next;
			return true;
		}
	}
	return false;
}
template <class T>
bool Catalog<T>::Contains(bool(*f)(T&, T&), T &need) {
	for (T tmp : vect) {
		if (!f(tmp, need) && !f(need, tmp)) {
			need = tmp;
			return true; 
		}
	}
	return false;
}

template <class T>
vector<T> Catalog<T>::LinSearch(bool(*f)(T&, T&), T need) {
	vector<T> Result;
	for (auto it = base.begin(); it != base.end(); it++) {
		if (!f(*it, need) && !f(need, *it)) {
			Result.push_back(*it);
		}
	}
	return Result;
}
template <class T>
vector<T> Catalog<T>::BinSearch(bool(*f)(T&, T&), T need) {
	vector<T> Result;
	sort(base.begin(), base.end(), f);
	_int32 begin = 0, end = base.size() - 1;
	while (begin != end) {
		_int32 m = (begin + end) / 2;
		if (f(base[m], need)) {
			begin = m + 1;
		}
		else
		{
			end = m;
		}
	}
	_int32 i = begin - 1;
	while (i > 0 && !f(base[i], need) && !f(need, base[i])) {
		Result.push_back(base[i]);
		i--;
	}
	while (begin < base.size() && !f(base[begin], need) && !f(need, base[begin])) {
		Result.push_back(base[begin]);
		begin++;
	}
	return Result;
}

template <class T>
void  Catalog<T>::LoadFromFile(bool(*f)(ifstream&,T&)) {
	vect.clear();
	ifstream fin(FileName, ios::binary);
	if (fin) {
		T tmp;
		while (f(fin,tmp)){
			vect.push_back(tmp);
		}
	}
	fin.close();
}
template <class T>
void  Catalog<T>::SaveToFile(void(*f)(ofstream&,T&)) {
	ofstream fout(FileName, ios::binary);
	for (T p : vect) {
		f(fout, p);
	}
	fout.close();
}
template <class T>
void Catalog<T>::Print(bool admin, void(*f)(bool, T)) {
	print_header();
	for (vector<file>::iterator it = vect.begin(); it != vect.end(); it++) 
		f(admin,*it);
}

