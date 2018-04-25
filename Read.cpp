#include <iostream>
#include <fstream>
#include <string>
#include <GL/glut.h>		// ��� ����������� ����� � ������. GLRotatef ������� ���� ��� 
#include "Read.hpp"			// GLfloat, �������, ����� ����� ��� �������� � GLfloat
using namespace std;

int GetIterSize()												// �������� ���������� ���������
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
	for (int i = 0; i < 5; i++)									// �������� ������� ��������, ��� ��� ���������
	{
		source.getline(str, 128, '\n');
	}
		
	int iteration_size = 0;
	while (!source.eof())										// ������� ������ �� ����� �����
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
	infile.getline(ch, 40, ' ');								// ���������� �������� �������
	infile.getline(ch, 40, ','); thing.x[i] = atof(ch);			// X ����������
	infile.getline(ch, 40, ','); thing.y[i] = atof(ch);			// Y ����������

	// ��� ��� Z ���������� � speeds ��������� ������, � �������� �� speeds 2,
	// �� ���������� �� �� ���. ������� ������ ����� ������ ������, ����� ��������� ��
	// �������
	infile.getline(ch, 1, ' ');
	infile.getline(ch, 40, ' '); thing.z[i] = atof(ch);			// Z ����������
	infile.getline(ch, 40, ' ');								// ������� speeds
	infile.getline(ch, 40, ','); thing.xspeed[i] = atof(ch);	// �������� �� X
	infile.getline(ch, 40, ','); thing.yspeed[i] = atof(ch);	// �������� �� Y
	infile.getline(ch, 40, ','); thing.zspeed[i] = atof(ch);	// �������� �� Z
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
	for (int i = 0; i < 5; i++)					// �������� ������� ��������, ��� ��� ���������
	{
		source.getline(str, 128, '\n');
	}
	
	for (int i = 1; i < iter_size; i++)			// �������� � 1 ����� �� �������� (������� �������� ����������)
	{
		ReadCoords(source, thing1, i);
		ReadCoords(source, thing2, i);
		ReadCoords(source, thing3, i);
	}

	delete str;
	source.close();
}