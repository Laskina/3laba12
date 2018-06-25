// Lab2_2sem_Laskina.cpp: определяет точку входа для консольного приложения.
/*Данные о файле представлены структурой с полями: каталог, имя файла, расширение, дата и время создания, 
атрибуты(только на чтение, скрытый, системный), признак удаления, количество выделенных секторов(размер сектора фиксирован константой).
Поиск по каталогу, названию, дате, признаку удаления.

1. Предусмотреть операции добавления, изменения и удаления элемента контейнера.
2. Реализовать ввод и вывод элементов контейнера с использованием потоковых итераторов на экран и в файл.
3. Реализовать операции поиска по заданным критериям и выборки подмножества элементов по заданным критериям.
Реализовать поиск в двух вариантах : линейный поиск и двоичный поиск на отсортированном контейнере.
4. Предусмотреть вывод подмножества выборки на экран и в файл.*/
#pragma once
#include "file.h"
#include "Catalog.h"

void PrintMenu() {
	cout << "Меню:" << endl;
	cout << "1.Добавить." << endl;
	cout << "2.Напечатать." << endl;
	cout << "3.Удалить." << endl;
	cout << "4.Изменить." << endl;
	cout << "5.Поиск." << endl;
	cout << "0.Выход." << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Catalog<file> catalog;
	catalog.LoadFromFile(Load_File);
	bool admin = AskTypeOfUser("Введите уровень доступа");
	int choise;
	do {
		PrintMenu();
		choise = InputNum("Выберите действие", 0, 5);
		switch (choise) {
			case 1:
			{
				file f;
				f.Input();
				if (!catalog.Add(compare_name, f))
					cout << "Файл с таким именем уже существует!" << endl;
				break;	}
			case 2:
			{
				catalog.Print(admin, print_file);
				break;	}
			case 3:
			{
				file f;
				f.setFilename(InputStr("Введите имя удаляемого файла"));
				if (!catalog.Contains(compare_name, f))
				{
					cout << "Файл не найден " << endl;
					break;
				}
				if (admin) {
					catalog.Delete(compare_name, f);
				}
				else {
					if (f.getAttribute() == open)
					{
						file next = f;
						next.setDeleted(true);
						catalog.Change(compare_name, f, next);
					}
					else
						if (f.getAttribute() == read)
							cout << "Файл доступен только для чтения" << endl;
						else
							cout << "Файл не найден " << endl;
				}
				break; }
			case 4:
			{
				file f;
				f.setFilename(InputStr("Введите имя изменяемого файла"));
				if (!catalog.Contains(compare_name, f))
				{
					cout << "Файл не найден " << endl;
					break;
				}
				if (admin || f.getAttribute() == open) {
					file next=f;
					next.Change(admin);
					catalog.Change(compare_name, f, next);
					break;
				}
				if (f.getAttribute() == read) {
					cout << "Файл доступен только для чтения" << endl;
				}
				else
					cout << "Файл не найден " << endl;

				break; }
			case 5:
			{
				file f;
				f.setFilename(InputStr("Введите имя искомого файла"));
				if (!catalog.Contains(compare_name, f))
				{
					cout << "Файл не найден " << endl;
					break;
				}
				if (admin || f.getAttribute() == open || f.getAttribute() == read) {
					print_file(admin, f);
					break;
				}
				else
					cout << "Файл не найден " << endl;

				break; }
		}
	
	} while (choise != 0);
	catalog.SaveToFile(Save_File);
	return 0;
}

