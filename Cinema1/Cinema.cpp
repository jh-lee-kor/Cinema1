#include "Cinema.h"
#include "Database.h"
#include "Reservation.h"
#include "Check.h"
#include "Analysis.h"



void Cinema::run() {

	bool flag = false;
	int i;

	Database db;
	
	while (!flag) {
		cout << "-------------------------------------------------" << endl;
		cout << endl;
		cout << "안녕하세요, ABC영화관입니다." << endl;
		cout << "메뉴를 선택하십시오." << endl;
		cout << endl;
		cout << endl;
		cout << "1. 영화 예매" << endl;
		cout << endl;
		cout << "2. 예매 확인/취소, 포인트 조회" << endl;
		cout << endl;
		cout << "3. 예매 좌석 분석" << endl;
		cout << endl;
		cout << "4. 종료" << endl;
		cout << endl;
		cout << "메뉴를 입력해주십시오. : ";
		cin >> i;

		Reservation rv;
		Check ck;
		Analysis ay;

		switch (i) { // 메뉴 선택
		case 1:
			rv.run(db);
			break;

		case 2:
			ck.run(db);
			break;

		case 3:
			ay.run(db);
			break;

		case 4:
			flag = true;
			break;

		default:
			cout << "-------------------------------------------------" << endl;
			cout << "잘못 입력하셨습니다. 다시 입력해주세요." << endl;
			cout << "-------------------------------------------------" << endl;
			cout << endl;
			break;
		}
	}
}