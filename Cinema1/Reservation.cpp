#include "Reservation.h"

#include <iostream>
using namespace std;


void Reservation::run(Database & db) {
	flag1 = false;
	flag2 = false;
	flag3 = false;
	while (!flag1) {
		user_check(db);
	}
	while (!flag2) {
		movie_select(db);
	}
	while (!flag3) {
		seat_select(db);
	}
	payment(db);
}

void Reservation::user_check(Database & db) {
	cout << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "환영합니다. 기존에 등록되신 고객님이신가요?" << endl;
	cout << endl;
	cout << "신규 고객님께서는 회원 등록이 필요합니다." << endl;
	cout << endl;
	cout << "회원 등록을 통해 ABC포인트를 적립해보세요." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "| 1. 회원이다         | 2. 회원이 아니다        |" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "입력 : ";
	
	int select;
	cin >> select;
	if (select == 1) {
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



		if (db.login(id1, pw1) != 0) { 
			sel_usernum = db.login(id1, pw1);
			string name = db.getusername(sel_usernum);
			cout << "-------------------------------------------------" << endl;
			cout << name << "님, 환영합니다." << endl;
			cout << "-------------------------------------------------" << endl;
			sel_name = name;
			flag1 = true;
		}
		else {
			cout << "-------------------------------------------------" << endl;
			cout << "잘못된 ID 혹은 비밀번호입니다. 다시 확인해주세요." << endl;
			cout << endl;
			cout << "처음 화면으로 돌아갑니다." << endl;
			cout << "-------------------------------------------------" << endl;
		}
		
	}
	else if (select == 2) {
		cout << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "신규 회원등록을 시작합니다." << endl;
		cout << endl;
		cout << "회원님의 성함을 입력해주세요." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "입력 : ";
		string name;
		cin.ignore();
		getline(cin, name, '\n');
		char gen;
		while (true) {
			cout << "-------------------------------------------------" << endl;
			cout << name << "회원님 환영합니다." << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "회원님의 성별을 입력해주세요." << endl;
			cout << endl;
			cout << "남성 회원님은 M, 여성회원님은 F를 입력해주세요." << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "입력 : ";
			cin >> gen;
			if ((gen == 'M') || (gen == 'F'))
				break;
			else{
				cout << "정확히 입력해주십시오." << endl;
				cout << "남성 회원님은 M, 여성회원님은 F를 입력해주세요." << endl;
			}	
		}
		cout << "-------------------------------------------------" << endl;
		cout << "회원님의 아이디를 입력해주세요." << endl;
		string nid;
		while (true) {
			cout << "-------------------------------------------------" << endl;
			cout << "입력 : ";
			cin >> nid;
			int i = 0;
			while (i < User::totaluser) {
				if (db.getuserid(i) == nid)
					break;
				i++;
			}
			if (i == User::totaluser)
				break;
			else
				cout << "이미 등록된 아이디입니다." << endl;
		}
		cout << "-------------------------------------------------" << endl;
		cout << "회원님의 비밀번호를 입력해주세요." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "입력 : ";
		string npw;
		cin >> npw;
		cout << "-------------------------------------------------" << endl;
		cout << "회원 정보를 확인해주세요." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "이름 : " << name << " | 성별 : "<< gen <<  endl;
		cout << endl;
		cout << "ID   : " << nid << " | PW   : " << npw << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "정보가 맞으시면 확인을, 틀린 점이 있다면 취소를 눌러주세요." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "| 1. 확인             | 2. 취소                 |" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "입력 : ";
		int sel2;
		while (true) {
			cin >> sel2;
			if (sel2 == 1) {
				db.signup(name, nid, npw, gen);
				sel_name = name;
				sel_usernum = User::totaluser;
				flag1 = true;

				cout << "-------------------------------------------------" << endl;
				cout << name << "회원님 환영합니다." << endl;
				cout << endl;
				cout << "ABC시네마와 함께 좋은 시간 되시길 바랍니다." << endl;
				cout << "-------------------------------------------------" << endl;

				
				break;
			}
			else if (sel2 == 2) {
				cout << "-------------------------------------------------" << endl;
				cout << "회원 등록을 취소하셨습니다." << endl;
				cout << "최초 화면으로 돌아갑니다." << endl;
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
	}
	else {
		cout << "잘못된 입력입니다. 다시 시도해주세요." << endl;
	}

}

void Reservation::movie_select(Database& db) {
	cout << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "영화 예매를 시작합니다." << endl;
	cout << "현재 ABC시네마에서 상영중인 영화는 다음과 같습니다." << endl;
	cout << "-------------------------------------------------" << endl;
	for (int m = 1; m <= Movie::totalmovie; m++)
		cout << m << "." << db.getmoviename(m) << " | " << db.getmoviertime(m) << "분" << endl;
	cout << "-------------------------------------------------" << endl;
	int mov;
	while (true) {
		cout << "-------------------------------------------------" << endl;
		cout << "상영하실 영화의 번호를 선택해주세요." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "입력 : ";
		cin >> mov;
		if ((1 <= mov) && (mov <= Movie::totalmovie))
			break;
		else{
			cout << "-------------------------------------------------" << endl;
			cout << "정확히 입력해주세요." << endl;
		}
			
	}
	cout << "-------------------------------------------------" << endl;
	cout << db.getmoviename(mov) << " 영화를 선택하셨습니다." << endl;
	cout << endl;
	cout << "상영중인 해당 영화 프로그램은 다음과 같습니다." << endl;
	cout << "-------------------------------------------------" << endl;
	int pickedMV = 0;
	int plist[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	int bday = db.getbusiday() - 1;
	for (int n = 0; n < 40; n++) {
		if (db.prodb[bday][n].getmovie() == mov) {
			plist[pickedMV] = n;
			cout << pickedMV + 1 << " | " << db.getmoviename(mov) << " | " << db.prodb[bday][n].getstime() << "시 시작 | " << db.prodb[bday][n].gettheater() << "상영관" << endl;
			pickedMV++;
		}
	}
	if (plist[0] == -1) {
		cout << "해당 영화는 현재 상영중인 프로그램이 없습니다." << endl;
		cout << "-------------------------------------------------" << endl;
	}
	else {
		int select;
		while (true) {
			cout << "-------------------------------------------------" << endl;
			cout << "상영하실 영화를 선택해주세요." << endl;
			cout << "입력 : ";
			cin >> select;

			if ((select < 1) || plist[select - 1] == -1) {
				cout << "-------------------------------------------------" << endl;
				cout << "정확히 입력해주십시오." << endl;
			}
			else
				break;
		}
		cout << "-------------------------------------------------" << endl;
		cout << db.getmoviename(mov) << " | " << db.prodb[bday][plist[select - 1]].getstime() << "시 시작 | " << db.prodb[bday][plist[select - 1]].gettheater() << "상영관" << endl;
		cout << "을 선택하셨습니다." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "맞으시면 확인을, 틀린 점이 있다면 취소를 눌러주세요." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "| 1. 확인             | 2. 취소                 |" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "입력 : ";
		int sel2;
		while (true) {
			cin >> sel2;
			if (sel2 == 1) {
				cout << "-------------------------------------------------" << endl;
				cout << "확인되었습니다." << endl;
				cout << "-------------------------------------------------" << endl;

				sel_movieid = mov;
				sel_programnum = plist[select - 1];
				flag2 = true;
				break;
			}
			else if (sel2 == 2) {
				cout << "-------------------------------------------------" << endl;
				cout << "영화 선택이 취소되었습니다." << endl;
				cout << endl;
				cout << "최초 화면으로 돌아갑니다." << endl;
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
	}
	
}

void Reservation::seat_select(Database& db) {
	cout << "좌석을 선택하겠습니다." << endl;
	cout << endl;
	cout << "사회적 거리두기에 의해 예매된 좌석 근처 한칸은 이용 불가능합니다.";
	cout << endl;
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
			if (db.prodb[(db.getbusiday()-1)][sel_programnum].isseatbooked(i, j))
				cout << " XX ";
			else if ((i != 0) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(i-1, j))
				cout << " -- "; // 위쪽 거리두기
			else if ((i != 7) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(i+1, j))
				cout << " -- "; // 아래쪽 거리두기
			else if ((j != 0) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(i, j-1))
				cout << " -- "; // 왼쪽 거리두기
			else if ((j != 7) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(i, j+1))
				cout << " -- "; // 오른쪽 거리두기
			else
				cout << ' ' << (char)(i + 65) << j+1 << ' ';
		}
		cout << "|" << endl;
		cout << "----------------------------------------------" << endl;
	}
	cout << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "좌석번호: 사용 가능한 좌석" << endl;
	cout << endl;
	cout << "XX : 이미 예약된 좌석 / -- : 사회적 거리두기 적용 좌석" << endl;
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
		else if (db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(r, c))
			cout << "이미 예매된 좌석입니다. 다시 입력해주세요." << endl;
		else if ((r != 0) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(r - 1, c))
			cout << "거리두기 좌석입니다. 다시 입력해주세요." << endl;
		else if ((r != 7) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(r + 1, c))
			cout << "거리두기 좌석입니다. 다시 입력해주세요." << endl; // 아래쪽 거리두기
		else if ((c != 0) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(r, c - 1))
			cout << "거리두기 좌석입니다. 다시 입력해주세요." << endl; // 왼쪽 거리두기
		else if ((c != 7) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(r, c + 1))
			cout << "거리두기 좌석입니다. 다시 입력해주세요." << endl; // 오른쪽 거리두기
		else
			break;
		cout << "-------------------------------------------------" << endl;
		cout << "좌석 번호를 입력해주십시오 (예:A1) : ";
	}
	cout << "-------------------------------------------------" << endl;
	cout << pickedseat << " 좌석을 예매하시겠습니까?" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "| 1. 확인             | 2. 취소                 |" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "입력 : ";
	int sel2;
	while (true) {
		cin >> sel2;
		if (sel2 == 1) {
			cout << "-------------------------------------------------" << endl;
			cout << "확인되었습니다." << endl;
			cout << "-------------------------------------------------" << endl;

			sel_row = r;
			sel_col = c;
			flag3 = true;
			break;
		}
		else if (sel2 == 2) {
			cout << "-------------------------------------------------" << endl;
			cout << "좌석 선택이 취소되었습니다." << endl;
			cout << endl;
			cout << "좌석 선택 화면으로 돌아갑니다." << endl;
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
}

void Reservation::payment(Database& db) {
	cout << "-------------------------------------------------" << endl;
	cout << "결제를 진행하겠습니다." << endl;
	cout << endl;
	cout << "티켓은 1매당 " << db.ticket << " 원입니다." << endl;
	cout << endl;
	cout << "결제는 현금으로만 진행됩니다." << endl;
	cout << endl;
	cout << "현금을 넣어주십시오. : " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "입력 : ";
	int money = 0;
	int inputmoney = 0;
	while (true) {
		cin >> inputmoney;
		money += inputmoney;
		if (money >= db.ticket)
			break;
		else{
			cout << "-------------------------------------------------" << endl;
			cout << "금액이 부족합니다. 돈을 더 넣어주십시오. :";
			cout << endl;
			cout << "현재 잔액 : " << money << "원" <<  endl;
			cout << endl;
			cout << "입력 : ";
		}
	}
	cout << "-------------------------------------------------" << endl;
	cout << "티켓 1매 구입합니다." << endl;
	cout << endl;
	cout << "포인트는 " << db.ticket / (db.pointratio * 100) << " P 적립됩니다." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "결제를 취소하시면 초기 화면으로 돌아갑니다." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << endl;
	cout << "영화 : " << db.getmoviename(sel_movieid);
	cout << endl;
	cout << "상영관 : " << db.prodb[(db.getbusiday() - 1)][sel_programnum].gettheater() << " | " << db.prodb[(db.getbusiday() - 1)][sel_programnum].getstime() << "시 시작" << endl;
	cout << endl;
	cout << (char)(sel_row + 65) << (char)(sel_col + 48) << " 좌석 | " << db.ticket << "원 | " << " 포인트 | " << db.ticket/(db.pointratio*100) << " P 적립" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "| 1. 확인             | 2. 취소                 |" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "입력 : ";
	int sel2;
	while (true) {
		cin >> sel2;
		if (sel2 == 1) {
			money -= db.ticket;
			int point = db.ticket / (db.pointratio * 100);
			db.prodb[(db.getbusiday()-1)][sel_programnum].bookseat(sel_row, sel_col, sel_usernum);
			db.setuserpoint(sel_usernum, db.getuserpoint(sel_usernum) + point);
			

			cout << "-------------------------------------------------" << endl;
			cout << "티켓을 예매했습니다." << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "영화 : " << db.getmoviename(sel_movieid);
			cout << endl;
			cout << "상영관 : " << db.prodb[(db.getbusiday() - 1)][sel_programnum].gettheater() << " | " << db.prodb[(db.getbusiday() - 1)][sel_programnum].getstime() << "시 시작" << endl;
			cout << endl;
			cout << (char)(sel_row + 65) << (char)(sel_col + 48) << " 좌석 | " << db.ticket << "원 | " << " 포인트 | " << point << " P 적립" << endl;
			cout << "현재 포인트 : " << db.ticket / (db.pointratio * 100) << " P" << endl;
			cout << "-------------------------------------------------" << endl;
			cout << endl;

			if (money > 0) {
				cout << "거스름돈 " << money << "를 반환합니다." << endl;
				cout << endl;
				cout << "-------------------------------------------------" << endl;
			}

			cout << "이용해주셔서 감사합니다." << endl;
			cout << endl;
			cout << "초기 화면으로 돌아갑니다." << endl;
			cout << "-------------------------------------------------" << endl;

			break;
		}
		else if (sel2 == 2) {
			cout << "-------------------------------------------------" << endl;
			cout << "결제가 취소되었습니다." << endl;
			cout << endl;
			cout << "초기 화면으로 돌아갑니다." << endl;
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
}