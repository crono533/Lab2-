// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#ifndef BOOLINTERVAL_H
#define BOOLINTERVAL_H

#include "BBV.h"

class BoolInterval
{
private:

public:
	BBV vec;
	BBV dnc;
	BBV GetVec() {return vec;}
	BBV GetDnc() {return dnc;}

	explicit BoolInterval(size_t len = 8);
	BoolInterval(const char *vec_in, const char *dnc_in);
	explicit BoolInterval(const char *vector);
	BoolInterval(BBV &vec_in, BBV &dnc_in);
	void setInterval(BBV &vec, BBV &dnc);

	BoolInterval &operator=(BoolInterval &ibv);
	bool operator == (BoolInterval &ibv);
	bool operator != (BoolInterval &ibv);
	operator string();
	int length(); // Длина или количество переменных
	int rang();// Ранг интервала

	bool isOrthogonal(BoolInterval &ibv);
	bool isEqualComponent(BoolInterval &ibv);

	BoolInterval &mergeInterval(BoolInterval &ibv);  // Построение пересечения интервалов

	bool isIntersection(BoolInterval &ibv);

	bool isAbsorb(BoolInterval &ibv);

	char getValue(int ix);//Получить i ое значение компоненты интервала

	void setValue(char value, int ix); //Установить iое значение интервала

};

#endif // BOOLINTERVAL_H
