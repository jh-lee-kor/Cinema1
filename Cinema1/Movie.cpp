#include "Movie.h"

int Movie::totalmovie = 0;

void Movie::input_movie(std::string name, int rtime) {
	this->name = name;
	this->rtime = rtime;
	totalmovie++;
	this->movieid = totalmovie;
}

void Movie::setname(std::string name) {
	this->name = name;
}
std::string Movie::getname() {
	return this->name;
}

void Movie::setrtime(int rtime) {
	this->rtime = rtime;
}

int Movie::getrtime() {
	return this->rtime;
}

int Movie::getid() {
	return this->movieid;
}