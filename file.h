#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
using namespace std;

#define SECTOR 4;

typedef struct date_time
{
	int day;
	int month;
	int year;

	int hour;
	int mins;
	int sec;
} date_time;

enum attribute {open, read, hidden, systems};

class file
{
private:
	string directory; //каталог
	string filename;  //имя
	string extention; //расширение
	date_time date_creation;
	attribute atr; //атрибут
	bool is_deleted;
	int num_sectors;
public:
	string getDirectory();
	void setDirectory(string d);
	string getFilename();
	void setFilename(string f);
	string getExtention();
	void setExtention(string e);
	date_time getDateTime();
	void setDateTime(date_time d);
	string getAttributeAsStr();
	attribute getAttribute();
	void setAttribute(int a);
	void setAttribute(attribute a);
	bool getDeleted();
	string getDeletedAsStr();
	void setDeleted(bool i);
	int getNumSectors();
	void setNumSectors(int n);

	void Input();
	void Change(bool admin);
	void Save_to_binfile(ofstream &fout);
	bool Load_from_binfile(ifstream &fin);
	file();
	file(string d, string f, string e, date_time dt, int a, int n);
	~file();
};

void printNum(int num, int N);

void printStr(string str, int N);

void print_file(bool admin, file f);

void print_header();

bool Load_File(ifstream &fin, file &f);
void Save_File(ofstream &fout, file &f);

//компараторы для сортировки и бинарного поиска
bool compare_direct(file &a,file &b);

bool compare_name(file &a,file &b);

bool compare_date(file &a,file &b);

bool compare_del(file &a, file &b);

int InputNum(string str, int min, int max);

string InputStr(string str);
