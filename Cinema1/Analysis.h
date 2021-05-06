#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "Database.h"

class Analysis {
public:
	void run(Database& db);
	void statistics(Database& db);
	void seatinfo(Database& db);

	void rank_total(Database& db);
	void rank_movie(Database& db);
	void rank_gender(Database& db);
	void rank_theater(Database& db);

	void top3_show(int countarr[][8]);

	void movie_count(Database& db);
	void gender_ratio(Database& db);
	void time_count(Database& db);

	void showseat();
	
};



#endif