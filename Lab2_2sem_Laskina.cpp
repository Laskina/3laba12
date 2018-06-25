// Lab2_2sem_Laskina.cpp: ���������� ����� ����� ��� ����������� ����������.
/*������ � ����� ������������ ���������� � ������: �������, ��� �����, ����������, ���� � ����� ��������, 
��������(������ �� ������, �������, ���������), ������� ��������, ���������� ���������� ��������(������ ������� ���������� ����������).
����� �� ��������, ��������, ����, �������� ��������.

1. ������������� �������� ����������, ��������� � �������� �������� ����������.
2. ����������� ���� � ����� ��������� ���������� � �������������� ��������� ���������� �� ����� � � ����.
3. ����������� �������� ������ �� �������� ��������� � ������� ������������ ��������� �� �������� ���������.
����������� ����� � ���� ��������� : �������� ����� � �������� ����� �� ��������������� ����������.
4. ������������� ����� ������������ ������� �� ����� � � ����.*/
#pragma once
#include "file.h"
#include "Catalog.h"

void PrintMenu() {
	cout << "����:" << endl;
	cout << "1.��������." << endl;
	cout << "2.����������." << endl;
	cout << "3.�������." << endl;
	cout << "4.��������." << endl;
	cout << "5.�����." << endl;
	cout << "0.�����." << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Catalog<file> catalog;
	catalog.LoadFromFile(Load_File);
	bool admin = AskTypeOfUser("������� ������� �������");
	int choise;
	do {
		PrintMenu();
		choise = InputNum("�������� ��������", 0, 5);
		switch (choise) {
			case 1:
			{
				file f;
				f.Input();
				if (!catalog.Add(compare_name, f))
					cout << "���� � ����� ������ ��� ����������!" << endl;
				break;	}
			case 2:
			{
				catalog.Print(admin, print_file);
				break;	}
			case 3:
			{
				file f;
				f.setFilename(InputStr("������� ��� ���������� �����"));
				if (!catalog.Contains(compare_name, f))
				{
					cout << "���� �� ������ " << endl;
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
							cout << "���� �������� ������ ��� ������" << endl;
						else
							cout << "���� �� ������ " << endl;
				}
				break; }
			case 4:
			{
				file f;
				f.setFilename(InputStr("������� ��� ����������� �����"));
				if (!catalog.Contains(compare_name, f))
				{
					cout << "���� �� ������ " << endl;
					break;
				}
				if (admin || f.getAttribute() == open) {
					file next=f;
					next.Change(admin);
					catalog.Change(compare_name, f, next);
					break;
				}
				if (f.getAttribute() == read) {
					cout << "���� �������� ������ ��� ������" << endl;
				}
				else
					cout << "���� �� ������ " << endl;

				break; }
			case 5:
			{
				file f;
				f.setFilename(InputStr("������� ��� �������� �����"));
				if (!catalog.Contains(compare_name, f))
				{
					cout << "���� �� ������ " << endl;
					break;
				}
				if (admin || f.getAttribute() == open || f.getAttribute() == read) {
					print_file(admin, f);
					break;
				}
				else
					cout << "���� �� ������ " << endl;

				break; }
		}
	
	} while (choise != 0);
	catalog.SaveToFile(Save_File);
	return 0;
}

