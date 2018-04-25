#ifndef Read_h
#define Read_h

class Thing
{
public:
	GLfloat *x;
	GLfloat *y;
	GLfloat *z;
	GLfloat *xspeed;
	GLfloat *yspeed;
	GLfloat *zspeed;
	Thing(int SIZE)
	{
		x = new GLfloat[SIZE];
		y = new GLfloat[SIZE];
		z = new GLfloat[SIZE];
		xspeed = new GLfloat[SIZE];
		yspeed = new GLfloat[SIZE];
		zspeed = new GLfloat[SIZE];
	};
	~Thing()
	{
		delete[]x;
		delete[]y;
		delete[]z;
		delete[]xspeed;
		delete[]yspeed;
		delete[]zspeed;
	};
};

int	GetIterSize();																// �������� ���������� ��������� �� log.csv
void ReadCoords(std::ifstream &infile, Thing &thing, int i);					// ��������� ������ �� infile � �������� � i-�� �������� ����� thing
void SetCoords(Thing &thing1, Thing &thing2, Thing &thing3, int iter_size);		// �������� iter_size ��������� � thing1, thing2, thing3

#endif