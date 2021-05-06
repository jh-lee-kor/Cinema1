#ifndef MOVIE_H
#define MOVIE_H

#include <string>

class Movie {
	std::string name;
	int rtime;
	int movieid;
public:
	static int totalmovie;
	void input_movie(std::string name, int rtime);
	void setname(std:: string name);
	std::string getname();
	void setrtime(int rtime);
	int getrtime();
	int getid();
};

#endif