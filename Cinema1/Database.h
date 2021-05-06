#ifndef DATABASE_H
#define DATABASE_H

#include "User.h"
#include "Program.h"
#include "Movie.h"

#include <string>

class Database {
	Movie* moviedb;
	User* userdb;
	static int businessday;

public:
	Database();
	~Database();
	int getbusiday();
	void load_moviedb();
	void load_userdb();
	void load_prodb();
	void load_reservdb();

	std::string getmoviename(int id);
	int getmoviertime(int id);

	std::string getusername(int id);
	int getuserpoint(int id);
	void setuserpoint(int id, int point);
	char getusergender(int id);
	void signup(std::string name, std::string id, std::string pw , char gender);
	int login(std::string id, std::string pw);
	std::string getuserid(int num);
	std::string getuserpw(int num);
	void input_reserv(int day, int pronum, int id, int row, int col);

	const static int ticket;
	const static int pointratio;
	const static int numoftheater;

	Program** prodb;
};

#endif