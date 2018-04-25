#include <iostream>
#include <fstream>
#include <string>
#include <GL/glut.h>		// Для определения типов в классе. GLRotatef требует свой тип 
#include "Read.hpp"			// GLfloat, поэтому, лучше сразу все записать в GLfloat
using namespace std;

int GetIterSize()												// Получить количество измерений
{
	ifstream source("log.csv");
	if (!source)
	{
		cout << "log file... cannot be open!\n";
		//return 1;
	}
	else
		cout << "log file... OK!\n";

	char *str = new char[128];
	for (int i = 0; i < 5; i++)									// Проходим нулевую итерацию, где нет скоростей
	{
		source.getline(str, 128, '\n');
	}
		
	int iteration_size = 0;
	while (!source.eof())										// Считаем строки до конца файла
	{
		source.getline(str, 128);
		iteration_size++;
	}
	iteration_size = iteration_size / 4;

	source.close();	
	delete str;
	return iteration_size;
}

void ReadCoords(ifstream &infile, Thing &thing, int i)
{
	char ch[100];
	infile.getline(ch, 40, ' ');								// Пропускаем название частицы
	infile.getline(ch, 40, ','); thing.x[i] = atof(ch);			// X координата
	infile.getline(ch, 40, ','); thing.y[i] = atof(ch);			// Y координата

	// Так как Z координату и speeds разделяет пробел, а пробелов до speeds 2,
	// то зацепиться не за что. Сместим курсор через первый пробел, чтобы прочитать до
	// второго
	infile.getline(ch, 1, ' ');
	infile.getline(ch, 40, ' '); thing.z[i] = atof(ch);			// Z координата
	infile.getline(ch, 40, ' ');								// Пропуск speeds
	infile.getline(ch, 40, ','); thing.xspeed[i] = atof(ch);	// Скорость по X
	infile.getline(ch, 40, ','); thing.yspeed[i] = atof(ch);	// Скорость по Y
	infile.getline(ch, 40, ','); thing.zspeed[i] = atof(ch);	// Скорость по Z
	//cout << thing.x[i] << "\n";
	//cout << thing.y[i] << "\n";
	//cout << thing.z[i] << "\n";
	//cout << thing.xspeed[i] << "\n";
	//cout << thing.yspeed[i] << "\n";
	//cout << thing.zspeed[i] << "\n";
}

void SetCoords(Thing &thing1,Thing &thing2, Thing &thing3, int iter_size)
{
	ifstream source("log.csv");
	if (!source)
		cout << "log file... cannot be open!\n";
	else
		cout << "log file... OK!\n";

	char *str = new char[128];
	for (int i = 0; i < 5; i++)					// Проходим нулевую итерацию, где нет скоростей
	{
		source.getline(str, 128, '\n');
	}
	
	for (int i = 1; i < iter_size; i++)			// Начинаем с 1 чтобы не путаться (нулевую итерацию пропустили)
	{
		ReadCoords(source, thing1, i);
		ReadCoords(source, thing2, i);
		ReadCoords(source, thing3, i);
	}

	delete str;
	source.close();
}