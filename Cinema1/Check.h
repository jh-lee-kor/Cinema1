#ifndef CHECK_H
#define CHECK_H

#include "Database.h"

class Check {
public:
	void run(Database & db);
	void viewncancel(Database& db);
	void pointcheck(Database& db);
};

#endif