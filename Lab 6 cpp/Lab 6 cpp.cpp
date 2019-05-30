#include <iostream>
#include <string>
#include <fstream>
#include <Windows.H>

using namespace std;

struct Computer
{
	string name;
	double ggz;
	double ddr;
	double hdd;
	double cost;
};



void Init(Computer* arr, const int n)
{
	
	for (int i = 0; i < n; i++)
	{
		cout << "Введите название: ";
		getline(cin, arr[i].name);
		//cin >> arr[i].name; cin.ignore();
		cout << "Введите кол-во ГГц: ";
		cin >> arr[i].ggz; cin.ignore();
		cout << "Введите кол-во Гб оперативной памяти: ";
		cin >> arr[i].ddr; cin.ignore();
		cout << "Введите объём жесткого диска: ";
		cin >> arr[i].hdd; cin.ignore();
		cout << "Введите стоимость: ";
		cin >> arr[i].cost; cin.ignore();
		cout << endl;
	}
}

void Print(Computer* arr, const int n)
{
	cout << "\nКомпьютеры: " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << " Название                |  " << arr[i].name ;
		cout << "\n Кол-во ГГЦ              |  " << arr[i].ggz << " Ггц";
		cout << "\n Оперативная память Гб   |  " << arr[i].ddr << " ГБ";
		cout << "\n Жесткий диск ГБ         |  " << arr[i].hdd << " ГБ";
		cout << "\n Цена                    |  " << arr[i].cost << " грн." << endl;
		cout << "---------------------------------------------" << endl;
	}
}



void Write(Computer* arr, const int n) {
	ofstream file("C:\\Users\\user\\Desktop\\file.txt", ios::binary | ios::in);
	if (file.is_open()) {
		file.write((char*)& n , sizeof n);
		for (int i = 0; i < n; i++)
		{
			if (arr[i].hdd < 250 && arr[i].ddr < 2) {

				double cost = arr[i].cost - (arr[i].cost * 10) / 100;
				arr[i].cost = cost;
				file.write((char*)& arr[i].name, sizeof arr[i].name);
				file.write((char*)& arr[i].ggz, sizeof arr[i].ggz);
				file.write((char*)& arr[i].ddr, sizeof arr[i].ddr);
				file.write((char*)& arr[i].hdd, sizeof arr[i].hdd);
				file.write((char*)& arr[i].cost, sizeof arr[i].cost);
			}
			else if (arr[i].hdd < 250) {
				double cost2 = arr[i].cost - (arr[i].cost * 5) / 100;
				arr[i].cost = cost2;
				file.write((char*)& arr[i].name, sizeof arr[i].name);
				file.write((char*)& arr[i].ggz, sizeof arr[i].ggz);
				file.write((char*)& arr[i].ddr, sizeof arr[i].ddr);
				file.write((char*)& arr[i].hdd, sizeof arr[i].hdd);
				file.write((char*)& arr[i].cost, sizeof arr[i].cost);
			}
			else {
				file.write((char*)& arr[i].name, sizeof arr[i].name);
				file.write((char*)& arr[i].ggz, sizeof arr[i].ggz);
				file.write((char*)& arr[i].ddr, sizeof arr[i].ddr);
				file.write((char*)& arr[i].hdd, sizeof arr[i].hdd);
				file.write((char*)& arr[i].cost, sizeof arr[i].cost);
			}

		}
	}
	else {
		cout << "Ошибка открытия файла!" << endl;
	}
	file.close();
}

/* Вариант 17. Переписать бинарный файл так, чтобы уменьшить стоимость компьютера на 5% если объем жесткого диска меьше чем 250Гбай
	т и на 10% - если к тому же объем оперативной памяти меньше 2Гбайт*/
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n;
	cout << "Введите кол-во компьютеров:";
	cin >> n;
	cin.ignore();
	
	Computer* arr = new Computer[n];
	Init(arr, n);
	Print(arr, n);
	Write(arr, n);
	


	cout << endl << "Обновленные записи" << endl;
	//считывание данных из бинарного файла
	int length;
	
	ifstream file("C:\\Users\\user\\Desktop\\file.txt", ios::binary);
	file.read((char*)& length, sizeof length);
	Computer* arrUpdated = new Computer[length];
	if (file.is_open()) {

		for (int i = 0; i < length; i++) {
			file.read((char*)& arrUpdated[i].name, sizeof arrUpdated[i].name);
			file.read((char*)& arrUpdated[i].ggz, sizeof arrUpdated[i].ggz);
			file.read((char*)& arrUpdated[i].ddr, sizeof arrUpdated[i].ddr);
			file.read((char*)& arrUpdated[i].hdd, sizeof arrUpdated[i].hdd);
			file.read((char*)& arrUpdated[i].cost, sizeof arrUpdated[i].cost);
		}
	}
	else {
		cout << "Ошибка открытия файла!" << endl;
	}
	file.close();


	Print(arr, n);

	delete[] arr;
	delete[] arrUpdated;
	return 0;
}