#include "Check.h"

#include <iostream>
using namespace std;


void Check::run(Database& db) {
	int i;
	bool flag = false;
	while (!flag) {
		cout << "-------------------------------------------------" << endl;
		cout << "예매 확인/취소 메뉴입니다." << endl;
		cout << endl;
		cout << "기능을 선택하십시오." << endl;
		cout << endl;
		cout << endl;
		cout << "1. 예매 확인 / 취소" << endl;
		cout << endl;
		cout << "2. 포인트 조회" << endl;
		cout << endl;
		cout << "3. 돌아가기" << endl;
		cout << endl;
		cout << "메뉴를 입력해주십시오. : ";
		cin >> i;


		switch (i) { // 메뉴 선택
		case 1:
			viewncancel(db);
			break;

		case 2:
			pointcheck(db);
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

void Check::viewncancel(Database& db) {
	cout << "-------------------------------------------------" << endl;
	cout << "예매 확인입니다." << endl;
	cout << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "회원님의 확인을 위해 아이디를 입력해주십시오." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "ID : ";
	string id1;
	cin >> id1;
	cout << "-------------------------------------------------" << endl;
	cout << "비밀번호를 입력해주십시오." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "PW : ";
	string pw1;
	cin >> pw1;



	if (db.login(id1, pw1) == 0) {
		cout << "-------------------------------------------------" << endl;
		cout << "잘못된 ID 혹은 비밀번호입니다. 다시 확인해주세요." << endl;
		cout << endl;
		cout << "처음 화면으로 돌아갑니다." << endl;
		cout << "-------------------------------------------------" << endl;
	}
	else {
		int sel_usernum = db.login(id1, pw1);
		string name = db.getusername(sel_usernum);
		cout << "-------------------------------------------------" << endl;
		cout << name << "님, 환영합니다." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "오늘 상영하는 영화가 조회됩니다." << endl;
		cout << "-------------------------------------------------" << endl;
		int here = 0;
		int darr[40][4];
		int today = db.getbusiday() - 1;
		for (int p = 0; p < 40; p++)
			for (int r = 0; r < 8; r++)
				for (int c = 0; c < 8; c++)
					if (db.prodb[today][p].getseatuser(r, c) == sel_usernum) {
						darr[here][0] = today;
						darr[here][1] = p;
						darr[here][2] = r;
						darr[here][3] = c;
						here++;
					}
		if (here == 0)
			cout << "조회된 예매가 없습니다." << endl;
		else {
			for (int i = 0; i < here; i++) {
				cout << i + 1 << "번" << endl;
				cout << db.getmoviename(db.prodb[darr[i][0]][darr[i][1]].getmovie()) << " | 상영관 " << db.prodb[darr[i][0]][darr[i][1]].gettheater() << endl;
				cout << db.prodb[darr[i][0]][darr[i][1]].getstime() << "시 시작 | " << (char)(darr[i][2] + 65) << (char)(darr[i][3] + 49) << "좌석" << endl;
				cout << "-------------------------------------------------" << endl;
			}
			cout << "취소할 예매를 선택해주세요. 취소할 예매가 없으시면 0을 선택해주세요." << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "입력 : ";
			int sel1;
			while (true) {
				cin >> sel1;
				if (sel1 == 0) {
					cout << "-------------------------------------------------" << endl;
					cout << "이전 화면으로 돌아갑니다." << endl;
					cout << "-------------------------------------------------" << endl;
					break;
				}
				else if ((sel1 < 0) || (sel1 > here)) {
					cout << "-------------------------------------------------" << endl;
					cout << "잘못 입력하셨습니다. 다시 입력해주세요." << endl;
					cout << endl;
					cout << "취소할 예매를 선택해주세요. 취소할 예매가 없으시면 0을 선택해주세요." << endl;
					cout << "-------------------------------------------------" << endl;
					cout << "입력 : ";
				}
				else {
					sel1--;
					cout << "-------------------------------------------------" << endl;
					cout << darr[sel1][0] << "일 | " << db.getmoviename(db.prodb[darr[sel1][0]][darr[sel1][1]].getmovie()) << " | 상영관 " << db.prodb[darr[sel1][0]][darr[sel1][1]].gettheater() << endl;
					cout << db.prodb[darr[sel1][0]][darr[sel1][1]].getstime() << "시 시작 | " << (char)(darr[sel1][2] + 65) << (char)(darr[sel1][3] + 49) << "좌석" << endl;
					cout << "-------------------------------------------------" << endl;
					cout << "해당 좌석을 취소하시겠습니까?" << endl;
					cout << "-------------------------------------------------" << endl;
					cout << "| 1. 예             | 2. 아니오                 |" << endl;
					cout << "-------------------------------------------------" << endl;
					cout << "입력 : ";
					int sel2;
					while (true) {
						cin >> sel2;
						if (sel2 == 1) {
							db.prodb[darr[sel1][0]][darr[sel1][1]].bookseat(darr[sel1][2], darr[sel1][3], 0); // 좌석 환원 
							db.setuserpoint(sel_usernum, db.getuserpoint(sel_usernum) - (db.ticket / (100 * db.pointratio))); // 유저 포인트 - 적립포인트

							cout << "-------------------------------------------------" << endl;
							cout << "예매가 취소되었습니다." << endl;
							cout << endl;
							cout << "해당 예매건으로 적립된 포인트는 반환되었습니다.";
							cout << endl;
							cout << "이용해주셔서 감사합니다.";
							cout << "-------------------------------------------------" << endl;
							cout << "환불 금액 : " << db.ticket << "원" << endl;
							cout << endl;
							cout << "잔여 포인트 : " << db.getuserpoint(sel_usernum) << "P" << endl;
							cout << "-------------------------------------------------" << endl;
							break;
						}
						else if (sel2 == 2) {
							cout << "-------------------------------------------------" << endl;
							cout << "예약 취소를 선택이 취소되었습니다." << endl;
							cout << endl;
							cout << "메뉴 화면으로 돌아갑니다." << endl;
							cout << "-------------------------------------------------" << endl;
							break;
						}
						else {
							cout << "-------------------------------------------------" << endl;
							cout << "정확히 입력해주십시오." << endl;
							cout << "-------------------------------------------------" << endl;
							cout << "입력 : ";
						}
					}
					break;
				}
			}
		}

	}
}


void Check::pointcheck(Database& db) {
	cout << "-------------------------------------------------" << endl;
	cout << "예매 확인입니다." << endl;
	cout << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "회원님의 확인을 위해 아이디를 입력해주십시오." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "ID : ";
	string id1;
	cin >> id1;
	cout << "-------------------------------------------------" << endl;
	cout << "비밀번호를 입력해주십시오." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "PW : ";
	string pw1;
	cin >> pw1;



	if (db.login(id1, pw1) == 0) {
		cout << "-------------------------------------------------" << endl;
		cout << "잘못된 ID 혹은 비밀번호입니다. 다시 확인해주세요." << endl;
		cout << endl;
		cout << "처음 화면으로 돌아갑니다." << endl;
		cout << "-------------------------------------------------" << endl;
	}
	else {
		int sel_usernum = db.login(id1, pw1);
		string name = db.getusername(sel_usernum);
		cout << "-------------------------------------------------" << endl;
		cout << name << "님, 환영합니다." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "잔여 포인트는 " << db.getuserpoint(sel_usernum) << "P 입니다." << endl;
		cout << "-------------------------------------------------" << endl;
	}
}