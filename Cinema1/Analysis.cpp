#include "Analysis.h"

#include <iostream>
using namespace std;

void Analysis::run(Database& db) {
	int i;
	bool flag = false;
	
	while (!flag) {
		cout << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "예매 좌석 분석 메뉴입니다." << endl;
		cout << endl;
		cout << endl;
		cout << "1. 가장 많이 예매된 좌석" << endl;
		cout << endl;
		cout << "2. 좌석별 세부 정보" << endl;
		cout << endl;
		cout << "3. 돌아가기" << endl;
		cout << endl;
		cout << "메뉴를 입력해주십시오. : ";
		cin >> i;

		switch (i) { // 메뉴 선택
		case 1:
			statistics(db);
			break;

		case 2:
			seatinfo(db);
			break;

		case 3:
			flag = true;
			break;

		default:
			cout << "잘못 입력하셨습니다. 다시 입력해주세요." << endl;
			break;
		}
	}
}

void Analysis::statistics(Database& db) {
	int i;
	bool flag = false;
	while (!flag) {
		cout << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "최근 일주일간 가장 많이 예매된 좌석 3개를 찾습니다." << endl;
		cout << endl;
		cout << endl;
		cout << "1. 전체 상영관 가장 많이 예매된 좌석 Top3" << endl;
		cout << endl;
		cout << "2. 상영관별 가장 많이 예매된 좌석 Top3" << endl;
		cout << endl;
		cout << "3. 영화별 가장 많이 예매된 좌석 Top3" << endl;
		cout << endl;
		cout << "4. 남녀별 가장 많이 예매된 좌석 Top3" << endl;
		cout << endl;
		cout << "5. 돌아가기" << endl;
		cout << endl;
		cout << "메뉴를 입력해주십시오. : ";
		cin >> i;

		switch (i) { // 메뉴 선택
		case 1:
			rank_total(db);
			break;

		case 2:
			rank_theater(db);
			break;

		case 3:
			rank_movie(db);
			break;

		case 4:
			rank_gender(db);
			break;

		case 5:
			flag = true;
			break;

		default:
			cout << "잘못 입력하셨습니다. 다시 입력해주세요." << endl;
			break;
		}
	}
}

void Analysis::seatinfo(Database& db) {
	int i;
	bool flag = false;
	while (!flag) {
		cout << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "선택한 좌석의 정보를 찾습니다." << endl;
		cout << endl;
		cout << endl;
		cout << "1. 영화별 예매 횟수" << endl;
		cout << endl;
		cout << "2. 남녀 예매 비율" << endl;
		cout << endl;
		cout << "3. 상영대별 예매 횟수" << endl;
		cout << endl;
		cout << "4. 돌아가기" << endl;
		cout << endl;
		cout << "메뉴를 입력해주십시오. : ";
		cin >> i;

		switch (i) { // 메뉴 선택
		case 1:
			movie_count(db);
			break;

		case 2:
			gender_ratio(db);
			break;

		case 3:
			time_count(db);
			break;

		case 4:
			flag = true;
			break;

		default:
			cout << "잘못 입력하셨습니다. 다시 입력해주세요." << endl;
			break;
		}
	}
}

void Analysis::rank_total(Database& db) {
	
	int today = db.getbusiday() - 1;
	int countarr[8][8] = { 0 };
	// 예매 횟수 검색
	for (int day = today - 6 ; day <= today; day++) // day 일의
		for (int p = 0; p < 40; p++) // 프로그램 DB 전체 조사 (40개)
			for (int r = 0; r < 8; r++)
				for (int c = 0; c < 8; c++)
					if (db.prodb[day][p].getseatuser(r, c)) { // 0일경우 false, 그 외의 경우 true
						countarr[r][c]++;
					}
	// 검색한 자료를 가장 큰 3개 정렬
	cout << "-------------------------------------------------" << endl;
	cout << "가장 예매가 많이 된 좌석은 다음과 같습니다." << endl;
	top3_show(countarr);
}

void Analysis::rank_movie(Database& db) {

	cout << "-------------------------------------------------" << endl;
	cout << "본 영화관에서 제공중인 영화는 다음과 같습니다." << endl;
	cout << "-------------------------------------------------" << endl;

	for (int m = 1; m <= Movie::totalmovie; m++)
		cout << m << "." << db.getmoviename(m) << " | " << db.getmoviertime(m) << "분" << endl;

	int sel1;
	while (true) {
		
		cout << "-------------------------------------------------" << endl;
		cout << "조회하실 영화를 선택해주세요" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "입력 : ";
		cin >> sel1;
		if ((1 <= sel1) && (sel1 <= Movie::totalmovie))
			break;
		else {
			cout << "-------------------------------------------------" << endl;
			cout << "정확히 입력해주세요." << endl;
		}
	}


	int today = db.getbusiday() - 1;
	int countarr[8][8] = { 0 };
	// 해당 영화의 예매 횟수 검색
	for (int day = today - 6 ; day <= today; day++) // day (오늘로부터 6일전 ~ 오늘) 일의
		for (int p = 0; p < 40; p++) // 프로그램 전체 조사 (40개)
			for (int r = 0; r < 8; r++)
				for (int c = 0; c < 8; c++)
					if (db.prodb[day][p].getmovie() == sel1) // 해당 영화에서
						if (db.prodb[day][p].getseatuser(r, c)) { // 0일경우 false, 그 외의 경우 true
							countarr[r][c]++;
						}
	// 검색한 자료를 가장 큰 3개 정렬
	cout << "-------------------------------------------------" << endl;
	cout << db.getmoviename(sel1) << " 에서 가장 예매가 많이 된 좌석은 다음과 같습니다." << endl;
	top3_show(countarr);
}

void Analysis::rank_gender(Database& db) {
	int sel1;
	char gen;
	while (true) {
		cout << "-------------------------------------------------" << endl;
		cout << "조회하실 성별을 선택해주세요" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "| 1. 남성               | 2. 여성               |" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "입력 : ";
		cin >> sel1;
		if (sel1 == 1) {
			gen = 'M';
			break;
		}
		else if (sel1 == 2) {
			gen = 'F';
			break;
		}
		else {
			cout << "-------------------------------------------------" << endl;
			cout << "정확히 입력해주세요." << endl;
		}
	}
	int today = db.getbusiday() - 1;
	int countarr[8][8] = { 0 };
	// gen 성별의 예매 횟수 검색
	for (int day = today - 6; day <= today; day++) // 오늘로부터 6일전~ 오늘
		for (int p = 0; p < 40; p++) // 프로그램 전체 조사 (40개)
			for (int r = 0; r < 8; r++)
				for (int c = 0; c < 8; c++)
					if (db.prodb[day][p].getseatuser(r, c) != 0) // 0일 경우 해당 좌석은 미등록
						if (db.getusergender(db.prodb[day][p].getseatuser(r, c)) == gen) // 성별 확인 
							countarr[r][c]++;
	// 검색한 자료를 가장 큰 3개 정렬
	cout << "-------------------------------------------------" << endl;
	if(sel1 == 1)
		cout << "남성 고객님께서 가장 많이 예매하신 좌석은 다음과 같습니다." << endl;
	else if (sel1 == 2)
		cout << "여성 고객님께서 가장 많이 예매하신 좌석은 다음과 같습니다." << endl;
	top3_show(countarr);
}

void Analysis::rank_theater(Database& db) {
	int sel1;
	while (true) {
		cout << "-------------------------------------------------" << endl;
		cout << "조회하실 상영관 번호를 선택해주세요" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "입력 : ";
		cin >> sel1;
		if ((1 <= sel1) && (sel1 <= db.numoftheater))
			break;
		else {
			cout << "-------------------------------------------------" << endl;
			cout << "정확히 입력해주세요." << endl;
		}
	}

	int today = db.getbusiday() - 1;
	int countarr[8][8] = {0};
	// t상영관의 예매 횟수 검색
	for (int day = today - 6 ; day <= today ; day ++) // day 일의
		for (int p = 0; p < 40; p++) // 프로그램 전체 조사 (40개)
			for (int r = 0; r < 8; r++) 
				for (int c = 0; c < 8; c++)
					if (db.prodb[day][p].gettheater() == sel1) // t 상영관에서
						if (db.prodb[day][p].getseatuser(r, c)) { // 0일경우 false, 그 외의 경우 true
							countarr[r][c]++;
						}
	// 검색한 자료를 가장 큰 3개 정렬
	cout << "-------------------------------------------------" << endl;
	cout << sel1 << "상영관에서 가장 예매가 많이 된 좌석은 다음과 같습니다." << endl;
	top3_show(countarr);		
}

void Analysis:: top3_show(int countarr[][8]) {
	int arr1[3] = { 0,0,0 }; // 1위의 row, column , count
	int arr2[3] = { 0,0,0 }; // 2위의 row, column , count
	int arr3[3] = { 0,0,0 }; // 3위의 row, column , count
	for (int r = 0; r < 8; r++)
		for (int c = 0; c < 8; c++) {
			if (countarr[r][c] > arr1[2]) {
				arr3[0] = arr2[0];
				arr3[1] = arr2[1];
				arr3[2] = arr2[2];
				arr2[0] = arr1[0];
				arr2[1] = arr1[1];
				arr2[2] = arr1[2];
				arr1[0] = r;
				arr1[1] = c;
				arr1[2] = countarr[r][c];
			}
			else if (countarr[r][c] > arr2[2]) {
				arr3[0] = arr1[0];
				arr3[1] = arr1[1];
				arr3[2] = arr1[2];
				arr2[0] = r;
				arr2[1] = c;
				arr2[2] = countarr[r][c];
			}
			else if (countarr[r][c] > arr3[2]) {
				arr3[0] = r;
				arr3[1] = c;
				arr3[2] = countarr[r][c];
			}
		}
	cout << "-------------------------------------------------" << endl;
	if (arr1[2] != 0){
		cout << "1. " << (char)(arr1[0] + 65) << arr1[1] + 1 << " 좌석 | " << arr1[2] << "회 예매됨" << endl;
		cout << endl;
	}
	if (arr2[2] != 0) {
		cout << "2. " << (char)(arr2[0] + 65) << arr2[1] + 1 << " 좌석 | " << arr2[2] << "회 예매됨" << endl;
		cout << endl;
	}
	if (arr3[2] != 0) {
		cout << "3. " << (char)(arr3[0] + 65) << arr3[1] + 1 << " 좌석 | " << arr3[2] << "회 예매됨" << endl;
		cout << "-------------------------------------------------" << endl;
	}	
}

void Analysis::movie_count(Database& db) {
	cout << "-------------------------------------------------" << endl;
	cout << "본 영화관에서 제공중인 영화는 다음과 같습니다." << endl;
	cout << "-------------------------------------------------" << endl;

	for (int m = 1; m <= Movie::totalmovie; m++)
		cout << m << "." << db.getmoviename(m) << " | " << db.getmoviertime(m) << "분" << endl;

	int sel1;
	while (true) {

		cout << "-------------------------------------------------" << endl;
		cout << "조회하실 영화를 선택해주세요" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "입력 : ";
		cin >> sel1;
		if ((1 <= sel1) && (sel1 <= Movie::totalmovie))
			break;
		else {
			cout << "-------------------------------------------------" << endl;
			cout << "정확히 입력해주세요." << endl;
		}
	}
	cout << "-------------------------------------------------" << endl;
	cout << db.getmoviename(sel1) << " 를 선택하셨습니다." << endl;
	cout << endl;
	cout << "좌석 배치는 다음과 같습니다." << endl;
	showseat();
	cout << "-------------------------------------------------" << endl;
	cout << "좌석 번호를 입력해주십시오 (예:A1) : ";
	string pickedseat;
	int r, c;
	while (true) {
		cin >> pickedseat;
		r = (int)pickedseat[0] - 65;
		c = (int)pickedseat[1] - 49;
		if ((r < 0) || (r > 8) || (c < 0) || (c > 8))
			cout << "잘못 입력하셨습니다." << endl;
		else
			break;
		cout << "-------------------------------------------------" << endl;
		cout << "좌석 번호를 입력해주십시오 (예:A1) : ";
	}
	cout << "-------------------------------------------------" << endl;
	cout << pickedseat << "좌석을 을 선택하셨습니다." << endl;
	int today = db.getbusiday() - 1;
	int count = 0;
	// 해당 영화의 예매 횟수 검색
	for (int day = today - 6; day <= today; day++) // day (오늘로부터 6일전 ~ 오늘) 일의
		for (int p = 0; p < 40; p++) // 프로그램 전체 조사 (40개)
			if (db.prodb[day][p].getmovie() == sel1) // 해당 영화에서
				if (db.prodb[day][p].getseatuser(r, c)) { // 0일경우 false, 그 외의 경우 true
					count++;
				}
	cout << "-------------------------------------------------" << endl;
	cout << (char)(r + 65) << c + 1 << " 좌석 | " << count << "회 예매됨" << endl;
	cout << "-------------------------------------------------" << endl;
}


void Analysis::gender_ratio(Database& db){
	cout << "-------------------------------------------------" << endl;
	cout << "좌석별 성별 비율을 조회합니다." << endl;
	cout << endl;
	cout << "좌석 배치는 다음과 같습니다." << endl;
	showseat();
	cout << "-------------------------------------------------" << endl;
	cout << "좌석 번호를 입력해주십시오 (예:A1) : ";
	string pickedseat;
	int r, c;
	while (true) {
		cin >> pickedseat;
		r = (int)pickedseat[0] - 65;
		c = (int)pickedseat[1] - 49;
		if ((r < 0) || (r > 8) || (c < 0) || (c > 8))
			cout << "잘못 입력하셨습니다." << endl;
		else
			break;
		cout << "-------------------------------------------------" << endl;
		cout << "좌석 번호를 입력해주십시오 (예:A1) : ";
		}
		cout << "-------------------------------------------------" << endl;
		cout << pickedseat << "좌석을 을 선택하셨습니다." << endl;
	int today = db.getbusiday() - 1;
	int mcount = 0;
	int fcount = 0;
	for (int day = today - 6; day <= today; day++) // day (오늘로부터 6일전 ~ 오늘) 일의
		for (int p = 0; p < 40; p++) // 프로그램 전체 조사 (40개)
			if (db.prodb[day][p].getseatuser(r, c) != 0) { // 0일 경우 해당 좌석은 미등록
				if (db.getusergender(db.prodb[day][p].getseatuser(r, c)) == 'M') // 남성 카운트 
					mcount++;
				else if (db.getusergender(db.prodb[day][p].getseatuser(r, c)) == 'F') // 여성 카운트
					fcount++;
			}
	double mratio = (double)mcount / ((double)mcount + (double)fcount);
	cout << "-------------------------------------------------" << endl;
	cout << "| " << (char)(r + 65) << c + 1 << " 좌석의 남녀 비율 | " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "|   남성 : " << (int) (mratio*100.0)  << "%   |   여성 : " << (int)(100.0*(1.0 - mratio)) << "%   | " << endl;
	cout << "-------------------------------------------------" << endl;
}

void Analysis::time_count(Database& db) {
	cout << "-------------------------------------------------" << endl;
	cout << "좌석 배치는 다음과 같습니다." << endl;
	showseat();
	cout << "-------------------------------------------------" << endl;
	cout << "좌석 번호를 입력해주십시오 (예:A1) : ";
	string pickedseat;
	int r, c;
	while (true) {
		cin >> pickedseat;
		r = (int)pickedseat[0] - 65;
		c = (int)pickedseat[1] - 49;
		if ((r < 0) || (r > 8) || (c < 0) || (c > 8))
			cout << "잘못 입력하셨습니다." << endl;
		else
			break;
		cout << "-------------------------------------------------" << endl;
		cout << "좌석 번호를 입력해주십시오 (예:A1) : ";
	}
	cout << "-------------------------------------------------" << endl;
	cout << pickedseat << "좌석을 을 선택하셨습니다." << endl;
	int today = db.getbusiday() - 1;
	int stime;
	int daytime = 0; // 주간 영화 (09시 ~ 17시)
	int nighttime = 0; // 야간 영화 (18시 ~ 익일 01시)
	int jjsy = 0; // 조조, 심야 영화 (01시 ~ 08시)
	for (int day = today - 6; day <= today; day++) // day (오늘로부터 6일전 ~ 오늘) 일의
		for (int p = 0; p < 40; p++) // 프로그램 전체 조사 (40개)
			if (db.prodb[day][p].getseatuser(r, c)) { // 0일경우 false, 그 외의 경우 true
				stime = db.prodb[day][p].getstime(); // stime은 해당 영화 시작시간
				if ((stime >= 1) && (stime <= 8))
					jjsy++;
				else if ((stime >= 9) && (stime <= 17))
					daytime++;
				else
					nighttime++;
			}
	cout << "-------------------------------------------------" << endl;
	cout << (char)(r + 65) << c + 1 << " 좌석 | " << endl;
	cout << endl;
	cout << endl;
	cout << " 주간 시간대 | 09시 ~ 17시 시작 영화 | " << daytime << "회 예매됨" << endl;
	cout << endl;
	cout << " 야간 시간대 | 18시 ~ 01시 시작 영화 | " << nighttime << "회 예매됨" << endl;
	cout << endl;
	cout << " 조조·심야 시간대 | 01시 ~ 08시 시작 영화 | " << jjsy << "회 예매됨" << endl;
	cout << "-------------------------------------------------" << endl;
}

void Analysis::showseat() {
	cout << "-------------------------------------------------" << endl;
	cout << endl;
	cout << "--------------------SCREEN--------------------" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "----------------------------------------------" << endl;
	for (int i = 0; i < 8; i++) {
		cout << "  ";
		for (int j = 0; j < 8; j++) {
			cout << "|";
			cout << ' ' << (char)(i + 65) << j + 1 << ' ';
		}
		cout << "|" << endl;
		cout << "----------------------------------------------" << endl;
	}
}