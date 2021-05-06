#ifndef RESERVATION_H
#define RESERVATION_H

#include "Database.h"
#include <string>
using namespace std;

class Reservation {
public:
	
	bool flag1, flag2, flag3;
	string sel_name;
	int sel_usernum;
	int sel_movieid;
	int sel_programnum;
	int sel_row, sel_col;

	void run(Database& db);
	void user_check(Database& db);
	void movie_select(Database& db);
	void seat_select(Database& db);
	void payment(Database& db);
};

#endif