#include "Program.h"


void Program::input_program(int movie, int theater, int stime) {
	this->movie = movie;
	this->theater = theater;
	this->screentime = stime;
}

int Program::getmovie() {
	return this->movie;
}

void Program::setmovie(int movie) {
	this->movie = movie;
}

int Program::gettheater() {
	return this->theater;
}

void Program::settheater() {
	this->theater = theater;
}

int Program::getstime() {
	return this->screentime;
}

void Program::setstime(int t) {
	this->screentime = t;
}

bool Program::isseatbooked(int row, int col) {
	return this->seats[row][col].isbooked();
}
void Program::bookseat(int row, int col, int userid) {
	this->seats[row][col].setuser(userid);
}

int Program::getseatuser(int row, int col) {
	return this->seats[row][col].getuser();
}