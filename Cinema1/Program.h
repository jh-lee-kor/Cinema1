#ifndef PROGRAM_H
#define PROGRAM_H

#include "Seat.h"

class Program {
	
	int movie; // ��ȭ��ȣ
	int theater; // �󿵰� ��ȣ
	int screentime; // �󿵽ð�
	Seat seats[8][8];

public:
	void input_program(int movie, int theater, int stime);
	int getmovie();
	void setmovie(int movie);
	int gettheater();
	void settheater();
	int getstime();
	void setstime(int t);
	bool isseatbooked(int row, int col);
	void bookseat(int row, int col, int userid);
	int getseatuser(int row, int col);



};

#endif