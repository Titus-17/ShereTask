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

int	GetIterSize();																// Получить количество измерений из log.csv
void ReadCoords(std::ifstream &infile, Thing &thing, int i);					// Прочитать строку из infile и записать в i-ые элементы полей thing
void SetCoords(Thing &thing1, Thing &thing2, Thing &thing3, int iter_size);		// Записать iter_size измерений в thing1, thing2, thing3

#endif