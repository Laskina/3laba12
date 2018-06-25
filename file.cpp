#include "file.h"
#include <fstream>
using namespace std;
file::file()
{
	directory = "";
	filename = "";
	extention = "";
	atr = read;
	is_deleted = false;
	num_sectors = 1*SECTOR;
}

file::file(string d, string f, string e, date_time dt, int a, int n)
{
	setDirectory(d);
	setFilename(f);
	setExtention(e);
	setDateTime(dt);
	setAttribute(0);
	setDeleted(false);
	setNumSectors(n);
}


file::~file()
{
}

//путь к файлу
string file::getDirectory() {
	return directory;
}
void file::setDirectory(string d){
	if (d == "") throw  "Невозможно указать пустой путь";
	directory = d;

}

//имя файла
string file::getFilename() {
	return filename;
}
void file::setFilename(string f) {
	if (f == "") throw  "Невозможно указать пустое имя";
	filename = f;
}

//расширение
string file::getExtention() {
	return extention;
}
void file::setExtention(string e) {
	if (e == "") throw  "Невозможно указать пустое имя";
	extention = e;
}

//дата и время
date_time file::getDateTime() {
	return date_creation;
}

bool CheckDate(date_time d) {
	_int32 maxdd;
	switch (d.month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12: {maxdd = 31; break; }
	case 2: {
		maxdd = (d.year % 4 == 0 && d.year % 100 != 0) || (d.year % 400 == 0) ? 29 : 28;//проверка
		break;
	}
	case 4:
	case 6:
	case 9:
	case 11: {maxdd = 30; break; }
	default: return false;
	}
	return d.day > 0 && d.day <= maxdd && d.year > 0 && (d.hour>=0) && (d.hour<=23) &&
			(d.mins>=0) && (d.mins<=59) && (d.sec>=0) && (d.sec<=59);
}


void file::setDateTime(date_time d) {
	if (CheckDate(d))
		date_creation = d;
}

// атрибут
string file::getAttributeAsStr() {
	string result;
	switch (atr) {
	case 0: result = "open";
		break;
	case 1: result = "read";
		break;
	case 2: result = "hidden";
		break;
	case 3: result = "systems";
		break;
	}
	return result;
}

attribute file::getAttribute() {
	return atr;
}

void file::setAttribute(int a) {
	switch (a){
	case 0: atr = open;
		break;
	case 1: atr = read;
		break;
	case 2: atr = hidden;
		break;
	case 3: atr = systems;
		break;
	}
}

void file::setAttribute(attribute a) {
	atr = a;
}

//признак удаления
bool file::getDeleted() {
	return is_deleted;
}
void file::setDeleted(bool i) {
	is_deleted = i;
}

string file::getDeletedAsStr() {
	return is_deleted ? "Помечен" : "Не помечен";
}

//количество секторов
int file::getNumSectors() {
	return num_sectors/ SECTOR;
}
void file::setNumSectors(int n) {
	if (n < 1) throw "Количество должно быть положительным";
	num_sectors = n*SECTOR;
}

string date_to_str(date_time d) {
	string result;
	result = to_string(d.day) + "." + to_string(d.month) + "." + to_string(d.year) + "  " +
			to_string(d.hour) + ":" + to_string(d.mins) + ":" + to_string(d.sec);
	return result;
}

void printNum(int num, int N) {
	string str = to_string(num);
	for (int i = str.size(); i < N; i++) {
		str += ' ';
	}
	str.substr(N);
	cout << str;
}

void printStr(string str, int N) {
	for (int i = str.size(); i < N; i++) {
		str += ' ';
	}
	str.substr(N);
	cout << str;
}

void print_file(bool admin, file f)
{
	if (!admin && ((f.getAttribute() == hidden) || (f.getAttribute() == systems))) return;
	int N = 20;
	printStr(f.getDirectory(),N);
	printStr(f.getFilename(),N);
	printStr(f.getExtention(),N);
	printStr(f.getAttributeAsStr(), N);
	printStr(f.getDeletedAsStr(), N);
	printStr(date_to_str(f.getDateTime()), N);
	printNum(f.getNumSectors(), N);
	cout << endl;
}

void print_header() {
	int N = 20;
	printStr("Директория", N);
	printStr("Имя файла", N);
	printStr("Расширение", N);
	printStr("Аттрибут", N);
	printStr("Помечен", N);
	printStr("Дата создания", N);
	printStr("Номер сектора", N);
	cout << endl;
}

date_time str_to_date(string date,string  time) {
	date_time result;
	//date
	int i = 1;
	result.day = (int)(date[0]-'0');
	while (date[i] !='.') {
		result.day *= 10;
		result.day += (int)(date[i] - '0');
		i++;
	}
	i++;
	result.month = (int)(date[i] - '0');
	i++;
	while (date[i] != '.') {
		result.month *= 10;
		result.month += (int)(date[i] - '0');
		i++;
	}
	i++;
	result.year = (int)(date[i] - '0');
	i++;
	while (i<date.length()) {
		result.year *= 10;
		result.year += (int)(date[i] - '0');
		i++;
	}

	//time
	i = 1;
	result.hour = (int)(time[0] - '0');
	while (time[i] != '.') {
		result.hour *= 10;
		result.hour += (int)(time[i] - '0');
		i++;
	}
	i++;
	result.mins = (int)(time[i] - '0');
	i++;
	while (time[i] != '.') {
		result.mins *= 10;
		result.mins += (int)(time[i] - '0');
		i++;
	}
	i++;
	result.sec = (int)(time[i] - '0');
	i++;
	while (i<time.length()) {
		result.sec *= 10;
		result.sec += (int)(time[i] - '0');
		i++;
	}

	return result;
}

void save_str_to_binfile(ofstream &fout, string str) {
	size_t len = str.length() + 1;
	const char *buf = str.c_str();
	fout.write((char *)(&len), sizeof(len));
	fout.write((char *)(buf), len);
	//delete[] buf;
}

bool load_str_from_binfile(ifstream &fin, string &str) {
	size_t len;
	if (fin.read((char *)(&len), sizeof(len))) {
		char * buf = new char[len];
		if (fin.read((char *)(buf), len)) {
			str = buf;
			//delete[] buf;
			return true;
		}
		//delete[] buf;
	}
	return false;
}

void file::Save_to_binfile(ofstream &fout) {
	save_str_to_binfile(fout,directory); //каталог
	save_str_to_binfile(fout, filename);  //имя
	save_str_to_binfile(fout,extention); //расширение
	fout.write((char *)(&date_creation), sizeof(date_time));
	fout.write((char *)(&atr), sizeof(attribute));
	fout.write((char *)(&is_deleted), sizeof(bool));
	fout.write((char *)(&num_sectors), sizeof(int));
}

bool file::Load_from_binfile(ifstream &fin) {
	return (load_str_from_binfile(fin, directory) &&
		load_str_from_binfile(fin, filename) &&
		load_str_from_binfile(fin, extention) &&
		fin.read((char *)(&date_creation), sizeof(date_time)) &&
		fin.read((char *)(&atr), sizeof(attribute)) &&
		fin.read((char *)(&is_deleted), sizeof(bool)) &&
		fin.read((char *)(&num_sectors), sizeof(int)));
}

bool Load_File(ifstream &fin, file  &f) {
	return f.Load_from_binfile(fin);
}
void Save_File(ofstream &fout, file &f) {
	f.Save_to_binfile(fout);
}

int InputNum(string str, int min, int max) {
	cout << str << endl;
	int res;
	while (!(cin >> res) || (res<min) || res>max) {
		cout << "Ошибка!"  << endl;
	}
	return res;
	return res;
}

string InputStr(string str) {
	cout << str << endl;
	string res;
	cin >> res;
	while (res == "") cin >> res;
	return res;
}

attribute InputAttr(string str) {
	cout << str << endl;
	cout << "0 - Доступный." << endl;
	cout << "1 - Только на чтение." << endl;
	cout << "2 - Скрытый." << endl;
	cout << "3 - Системный." << endl;
	return (attribute)InputNum("", 0, 3);
}

//ввод даты
date_time input_date() {
	date_time result;
	int tmp_int;
	do {
		cout << "Введите дату созданию:" << endl;
		result.day = InputNum("Введите день", 1, 31);
		result.month = InputNum("Введите месяц", 1, 12);
		result.year = InputNum("Введите год", 1, 100000);
		result.hour = InputNum("Введите час", 0, 23);
		result.mins = InputNum("Введите минуту", 0, 59);
		result.sec = InputNum("Введите секунду", 0, 59);
	} while (!CheckDate(result));
	return result;
}

//ввод 1 записи с консоли
void file::Input() {
	setDirectory(InputStr("Введите путь к файлу"));
	setFilename(InputStr("Введите имя файла"));
	setExtention(InputStr("Введите расширение файла"));
	setDateTime(input_date());
	setAttribute(InputAttr("Введите аттрибут"));
	setNumSectors(InputNum("Введите количество секторов",1,4));
}

bool InputQuery(string str) {
	cout << str << endl;
	cout << "1 - да" << endl;
	cout << "2 - нет" << endl;
	return InputNum("", 1, 2) == 1;
}

void file::Change(bool admin) {
	if (InputQuery("Изменить расположение файла?")) 
		setDirectory(InputStr("Введите путь к файлу"));
	if (InputQuery("Изменить имя файла?"))
		setFilename(InputStr("Введите имя файла"));
	if (admin && InputQuery("Изменить расширение файла?"))
		setExtention(InputStr("Введите расширение файла"));
	if (admin && InputQuery("Изменить дату создания файла?"))
		setDateTime(input_date());
	if (admin && InputQuery("Изменить аттрибут?"))
		setAttribute(InputAttr("Введите аттрибут"));
	if (admin && InputQuery("Изменить пометку?"))
		setDeleted(!is_deleted);
	if (admin && InputQuery("Изменить количество секторов?"))
		setNumSectors(InputNum("Введите количество секторов", 1, 4));
}

//компараторы для сортировки и бинарного поиска
bool compare_direct(file &a, file &b) {
	return (a.getDirectory() < b.getDirectory() );
}

bool compare_name(file &a, file &b) {
	return (a.getFilename() < b.getFilename());
}

bool compare_date(file &a, file &b) {
	date_time da = a.getDateTime();
	date_time db = b.getDateTime();
	if (da.year != db.year)
		return (da.year < db.year);
	if (da.month != db.month)
		return (da.month < db.month);
	if (da.day != db.day)
		return (da.day < db.day);
	if (da.hour != db.hour)
		return (da.hour < db.hour);
	if (da.mins != db.mins)
		return (da.mins < db.mins);
	if (da.sec != db.sec)
		return (da.sec < db.sec);
}

bool compare_del(file &a, file &b) {
	return(a.getDeleted()<b.getDeleted());
}

