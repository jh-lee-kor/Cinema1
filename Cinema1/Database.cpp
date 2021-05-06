#include "Database.h"

const int Database::ticket = 6000; // 티켓 가격 6천원
const int Database::pointratio = 1; // 포인트 적립 비율, 티켓 가격의 (pointratio)% 만큼 적립
const int Database::numoftheater = 6; // 포인트 적립 비율, 티켓 가격의 (pointratio)% 만큼 적립
int Database::businessday = 7;

Database::Database() { // 데이터베이스 생성

	// 프로그램 기동 시기를 영업한지 7일째라고 설정
	moviedb = new Movie[6];
	load_moviedb();
	userdb = new User[30];
	load_userdb();
	prodb = new Program * [businessday]; // 영업일까지의 프로그램 리스트를 만듬
	for (int i = 0; i < businessday; i++)
		prodb[i] = new Program[40]; // (i+1)일째 상영 프로그램 리스트, 최대 40개로 설정
	load_prodb();
	load_reservdb();

}

Database::~Database() {
	for (int i = 0; i < businessday; i++)
		delete[] prodb[i];
	delete[] prodb;
	delete[] userdb;
	delete[] moviedb;
}

int Database::getbusiday() {
	return this->businessday;
}

void Database::load_moviedb() {
	moviedb[0].input_movie("타이타닉", 194);
	moviedb[1].input_movie("시네마 천국", 124);
	moviedb[2].input_movie("미나리", 115);
	moviedb[3].input_movie("아기공룡 둘리", 80);
	moviedb[4].input_movie("캐스트 어웨이", 143);
	moviedb[5].input_movie("포레스트 검프", 842);
}

void Database::load_userdb() {
	//사용자 목록 불러오기
	userdb[0].input_user("고길동", 'M');
	userdb[0].setPoint(6000);
	userdb[1].input_user("또치", 'F');
	userdb[1].setPoint(200);
	userdb[2].input_user("둘리", 'M');
	userdb[2].setPoint(100);
	userdb[3].input_user("도우너", 'M');
	userdb[3].setPoint(110);
	userdb[4].input_user("둘리엄마", 'F');
	userdb[4].setPoint(5000);
	userdb[5].input_user("희동이", 'M');
	userdb[5].setPoint(10000);
	userdb[6].input_user("뽀로로", 'M');
	userdb[6].setPoint(9000);
	userdb[7].input_user("루피", 'F');
	userdb[7].setPoint(500);
	userdb[8].input_user("패티", 'F');
	userdb[8].setPoint(1000);
	userdb[9].input_user("포비", 'M');
	userdb[9].setPoint(50);
	userdb[10].input_user("홍길동", 'M');
	userdb[10].setPoint(6000);
	userdb[11].input_user("호형호제", 'F');
	userdb[11].setPoint(200);
	userdb[12].input_user("카레", 'M');
	userdb[12].setPoint(100);
	userdb[13].input_user("짜장", 'M');
	userdb[13].setPoint(110);
	userdb[14].input_user("짬뽕", 'F');
	userdb[14].setPoint(5000);
	userdb[15].input_user("유희왕", 'F');
	userdb[15].setPoint(10000);
	userdb[16].input_user("콩밥", 'M');
	userdb[16].setPoint(120);
	userdb[17].input_user("해커", 'F');
	userdb[17].setPoint(0);
	userdb[18].input_user("피카소", 'F');
	userdb[18].setPoint(0);
	userdb[19].input_user("샌즈", 'M');
	userdb[19].setPoint(0);
}

void Database::load_prodb() {
	// 영화 프로그램 불러오기
	// 편의를 위해 1~3일에는 1~4번 영화를 상영했고, 4~7일에는 3~6번 영화를 상영했다고 하자.
	// 1~3일 영화 프로그램 배치
	// 1~4상영관에 1~4번 영화를 배치
	int i, j, k, t;
	for (i = 0; i < 3; i++) { // i는 (i+1)일차
		t = 0;
		for (j = 1; j < 5; j++) // j는 j 번호의 영화
			for (k = 0; k < 5; k++) { // 1시, 6시, 11시, 16시, 21시에 상영
				prodb[i][t].input_program(j, j, 1 + 4 * k);
				t++;
			}
	}
	// 5번 상영관에 1번 영화 상영
	for (i = 0; i < 3; i++) { // i는 (i+1)일차
		t = 20;
		for (k = 0; k < 5; k++) { // 1시, 6시, 11시, 16시, 21시에 상영
			prodb[i][t].input_program(1, 5, 1 + 4 * k);
			t++;
		}
	}
	// 6번 상영관에 2번 영화 상영
	for (i = 0; i < 3; i++) { // i는 (i+1)일차
		t = 25;
		for (k = 0; k < 5; k++) { // 1시, 6시, 11시, 16시, 21시에 상영
			prodb[i][t].input_program(2, 6, 1 + 4 * k);
			t++;
		}
	}

	// 4~7일 영화 프로그램 배치
	// 1~4상영관에 3~6번 영화를 배치
	for (i = 3; i < 7; i++) { // i는 (i+1)일차
		t = 0;
		for (j = 3; j < 7; j++) // j는 j 번호의 영화, j-2관에 상영
			for (k = 0; k < 5; k++) { // 1시, 6시, 11시, 16시, 21시에 상영
				prodb[i][t].input_program(j, j-2, 1 + 4 * k);
				t++;
			}
	}
	// 5번 상영관에 4번 영화 상영
	for (i = 3; i < 7; i++) { // i는 (i+1)일차
		t = 20;
		for (k = 0; k < 5; k++) { // 1시, 6시, 11시, 16시, 21시에 상영
			prodb[i][t].input_program(4, 5, 1 + 4 * k);
			t++;
		}
	}
	// 6번 상영관에 6번 영화 상영
	for (i = 0; i < 4; i++) { // i는 (i+1)일차
		t = 25;
		for (k = 0; k < 5; k++) { // 1시, 6시, 11시, 16시, 21시에 상영
			prodb[i][t].input_program(6, 6, 1 + 4 * k);
			t++;
		}
	}
	// 총 30개씩의 프로그램을 불러옴.
}


std::string Database::getmoviename(int id) {
	return moviedb[id - 1].getname();
}

int Database::getmoviertime(int id) {
	return moviedb[id - 1].getrtime();
}

std::string Database::getusername(int id) {
	return userdb[id - 1].getName();
}

int Database::getuserpoint(int id) {
	return userdb[id - 1].getPoint();
}

void Database::setuserpoint(int id, int point) {
	userdb[id - 1].setPoint(point);
}

char Database::getusergender(int id) {
	return userdb[id - 1].getGender();
}

void Database::signup(std::string name, char gender) {
	userdb[User::totaluser].input_user(name, gender);
}

void Database::input_reserv(int day, int pronum, int id, int row, int col) { // 데이터베이스에 과거의 예매 정보를 입력
	prodb[day - 1][pronum].bookseat(row, col, id);
}

void Database::load_reservdb() { // 6일간의 과거 데이터, 오늘의 데이터 입력
	// 외부 프로그램을 이용하여 랜덤한 예약 정보 데이터를 생성하여 입력했다.
	// 만약 데이터가 필요없다면 해당 함수를 지우세요
	// 7일차 예약데이터
	input_reserv(7, 0, 10, 4, 2);
	input_reserv(7, 1, 9, 1, 1);
	input_reserv(7, 1, 1, 7, 5);
	input_reserv(7, 3, 7, 4, 3);
	input_reserv(7, 5, 5, 6, 2);
	input_reserv(7, 5, 18, 6, 3);
	input_reserv(7, 6, 19, 5, 0);
	input_reserv(7, 6, 2, 7, 0);
	input_reserv(7, 7, 2, 4, 2);
	input_reserv(7, 8, 6, 0, 1);
	input_reserv(7, 8, 10, 1, 3);
	input_reserv(7, 10, 8, 2, 4);
	input_reserv(7, 12, 18, 0, 3);
	input_reserv(7, 12, 3, 1, 2);
	input_reserv(7, 12, 11, 7, 1);
	input_reserv(7, 13, 13, 2, 5);
	input_reserv(7, 13, 7, 5, 2);
	input_reserv(7, 13, 8, 5, 7);
	input_reserv(7, 13, 16, 7, 2);
	input_reserv(7, 14, 10, 1, 4);
	input_reserv(7, 14, 4, 6, 4);
	input_reserv(7, 15, 5, 4, 4);
	input_reserv(7, 16, 1, 2, 0);
	input_reserv(7, 16, 18, 3, 0);
	input_reserv(7, 18, 5, 3, 5);
	input_reserv(7, 18, 6, 5, 3);
	input_reserv(7, 19, 20, 0, 7);
	input_reserv(7, 19, 14, 7, 4);
	input_reserv(7, 20, 20, 5, 6);
	input_reserv(7, 22, 1, 4, 5);
	input_reserv(7, 22, 6, 5, 4);
	input_reserv(7, 23, 9, 1, 3);
	input_reserv(7, 24, 2, 6, 7);
	input_reserv(7, 27, 19, 0, 5);
	input_reserv(7, 28, 18, 3, 5);
	input_reserv(7, 28, 10, 5, 6);

	// 1~6일차 예약 데이터
	input_reserv(1, 1, 20, 0, 2);
	input_reserv(1, 1, 8, 3, 2);
	input_reserv(1, 2, 8, 1, 1);
	input_reserv(1, 2, 1, 3, 4);
	input_reserv(1, 2, 14, 7, 4);
	input_reserv(1, 3, 20, 1, 7);
	input_reserv(1, 3, 7, 2, 7);
	input_reserv(1, 3, 6, 3, 1);
	input_reserv(1, 3, 20, 7, 4);
	input_reserv(1, 3, 6, 7, 5);
	input_reserv(1, 4, 11, 2, 6);
	input_reserv(1, 4, 13, 4, 2);
	input_reserv(1, 5, 17, 1, 6);
	input_reserv(1, 5, 10, 2, 0);
	input_reserv(1, 5, 10, 2, 5);
	input_reserv(1, 5, 20, 3, 5);
	input_reserv(1, 6, 2, 0, 3);
	input_reserv(1, 6, 6, 0, 7);
	input_reserv(1, 6, 12, 4, 0);
	input_reserv(1, 6, 11, 4, 1);
	input_reserv(1, 6, 2, 6, 0);
	input_reserv(1, 7, 10, 0, 5);
	input_reserv(1, 7, 4, 2, 4);
	input_reserv(1, 7, 1, 6, 5);
	input_reserv(1, 7, 5, 7, 0);
	input_reserv(1, 8, 2, 0, 0);
	input_reserv(1, 8, 3, 2, 2);
	input_reserv(1, 8, 18, 2, 7);
	input_reserv(1, 8, 18, 5, 3);
	input_reserv(1, 8, 3, 6, 5);
	input_reserv(1, 9, 16, 1, 5);
	input_reserv(1, 9, 5, 3, 4);
	input_reserv(1, 9, 8, 5, 5);
	input_reserv(1, 9, 6, 6, 7);
	input_reserv(1, 10, 4, 2, 5);
	input_reserv(1, 10, 6, 4, 1);
	input_reserv(1, 10, 20, 7, 5);
	input_reserv(1, 11, 11, 0, 3);
	input_reserv(1, 11, 4, 2, 4);
	input_reserv(1, 11, 12, 3, 5);
	input_reserv(1, 12, 16, 3, 3);
	input_reserv(1, 12, 11, 7, 4);
	input_reserv(1, 13, 12, 3, 4);
	input_reserv(1, 13, 16, 6, 2);
	input_reserv(1, 13, 14, 6, 6);
	input_reserv(1, 13, 15, 6, 7);
	input_reserv(1, 14, 1, 0, 1);
	input_reserv(1, 14, 11, 3, 5);
	input_reserv(1, 14, 11, 5, 5);
	input_reserv(1, 14, 15, 6, 3);
	input_reserv(1, 14, 4, 7, 4);
	input_reserv(1, 15, 3, 3, 2);
	input_reserv(1, 15, 14, 3, 7);
	input_reserv(1, 15, 5, 6, 6);
	input_reserv(1, 16, 17, 1, 5);
	input_reserv(1, 16, 6, 5, 7);
	input_reserv(1, 16, 17, 7, 1);
	input_reserv(1, 16, 12, 7, 2);
	input_reserv(1, 17, 5, 3, 4);
	input_reserv(1, 18, 5, 0, 6);
	input_reserv(1, 18, 18, 4, 2);
	input_reserv(1, 18, 6, 5, 1);
	input_reserv(1, 19, 19, 1, 1);
	input_reserv(1, 19, 17, 1, 2);
	input_reserv(1, 19, 4, 4, 5);
	input_reserv(1, 19, 19, 5, 7);
	input_reserv(1, 19, 12, 7, 1);
	input_reserv(1, 20, 3, 3, 3);
	input_reserv(1, 20, 5, 5, 7);
	input_reserv(1, 21, 9, 0, 4);
	input_reserv(1, 21, 13, 0, 6);
	input_reserv(1, 21, 16, 2, 2);
	input_reserv(1, 21, 2, 2, 6);
	input_reserv(1, 21, 1, 6, 4);
	input_reserv(1, 21, 2, 7, 1);
	input_reserv(1, 21, 17, 7, 6);
	input_reserv(1, 21, 12, 7, 7);
	input_reserv(1, 22, 8, 3, 1);
	input_reserv(1, 22, 12, 3, 6);
	input_reserv(1, 22, 17, 4, 1);
	input_reserv(1, 22, 4, 6, 6);
	input_reserv(1, 22, 6, 6, 7);
	input_reserv(1, 22, 1, 7, 1);
	input_reserv(1, 23, 12, 0, 2);
	input_reserv(1, 23, 1, 1, 2);
	input_reserv(1, 23, 11, 6, 1);
	input_reserv(1, 24, 16, 2, 7);
	input_reserv(1, 24, 1, 3, 0);
	input_reserv(1, 24, 6, 3, 7);
	input_reserv(1, 24, 4, 4, 7);
	input_reserv(1, 24, 1, 7, 2);
	input_reserv(1, 24, 15, 7, 6);
	input_reserv(1, 25, 12, 1, 7);
	input_reserv(1, 25, 16, 2, 2);
	input_reserv(1, 25, 16, 4, 5);
	input_reserv(1, 25, 8, 5, 4);
	input_reserv(1, 26, 7, 5, 5);
	input_reserv(1, 26, 17, 7, 0);
	input_reserv(1, 27, 9, 1, 2);
	input_reserv(1, 27, 4, 3, 0);
	input_reserv(1, 27, 12, 3, 7);
	input_reserv(1, 27, 11, 7, 6);
	input_reserv(1, 28, 8, 1, 0);
	input_reserv(1, 28, 20, 3, 5);
	input_reserv(1, 28, 4, 7, 4);
	input_reserv(1, 29, 15, 3, 7);
	input_reserv(2, 0, 10, 3, 3);
	input_reserv(2, 1, 8, 1, 0);
	input_reserv(2, 1, 7, 4, 6);
	input_reserv(2, 1, 11, 6, 3);
	input_reserv(2, 2, 1, 1, 2);
	input_reserv(2, 2, 17, 1, 7);
	input_reserv(2, 2, 14, 3, 7);
	input_reserv(2, 2, 19, 6, 6);
	input_reserv(2, 2, 3, 7, 5);
	input_reserv(2, 3, 4, 4, 4);
	input_reserv(2, 3, 1, 7, 1);
	input_reserv(2, 4, 16, 0, 7);
	input_reserv(2, 4, 11, 2, 4);
	input_reserv(2, 4, 4, 3, 1);
	input_reserv(2, 4, 3, 3, 6);
	input_reserv(2, 4, 16, 5, 3);
	input_reserv(2, 4, 4, 7, 0);
	input_reserv(2, 5, 19, 4, 5);
	input_reserv(2, 6, 15, 0, 6);
	input_reserv(2, 6, 9, 1, 2);
	input_reserv(2, 6, 19, 3, 2);
	input_reserv(2, 6, 16, 3, 4);
	input_reserv(2, 7, 1, 2, 2);
	input_reserv(2, 7, 20, 6, 6);
	input_reserv(2, 7, 6, 6, 7);
	input_reserv(2, 7, 6, 7, 1);
	input_reserv(2, 8, 15, 4, 6);
	input_reserv(2, 8, 11, 6, 3);
	input_reserv(2, 8, 12, 7, 0);
	input_reserv(2, 8, 8, 7, 1);
	input_reserv(2, 9, 16, 0, 5);
	input_reserv(2, 9, 4, 1, 2);
	input_reserv(2, 9, 19, 2, 1);
	input_reserv(2, 9, 10, 4, 6);
	input_reserv(2, 10, 20, 0, 4);
	input_reserv(2, 10, 15, 3, 7);
	input_reserv(2, 10, 8, 4, 6);
	input_reserv(2, 10, 15, 6, 6);
	input_reserv(2, 11, 2, 1, 0);
	input_reserv(2, 11, 8, 2, 5);
	input_reserv(2, 12, 8, 0, 2);
	input_reserv(2, 12, 9, 2, 0);
	input_reserv(2, 12, 5, 2, 7);
	input_reserv(2, 12, 20, 4, 2);
	input_reserv(2, 12, 19, 6, 2);
	input_reserv(2, 13, 9, 0, 6);
	input_reserv(2, 13, 10, 2, 1);
	input_reserv(2, 14, 19, 0, 5);
	input_reserv(2, 14, 13, 2, 2);
	input_reserv(2, 14, 10, 3, 4);
	input_reserv(2, 14, 12, 4, 2);
	input_reserv(2, 14, 20, 6, 0);
	input_reserv(2, 15, 12, 0, 6);
	input_reserv(2, 15, 5, 1, 2);
	input_reserv(2, 15, 19, 2, 3);
	input_reserv(2, 15, 17, 4, 6);
	input_reserv(2, 15, 2, 6, 2);
	input_reserv(2, 16, 14, 2, 3);
	input_reserv(2, 17, 4, 0, 0);
	input_reserv(2, 17, 4, 1, 6);
	input_reserv(2, 17, 7, 2, 0);
	input_reserv(2, 17, 19, 3, 6);
	input_reserv(2, 17, 17, 4, 6);
	input_reserv(2, 17, 13, 7, 4);
	input_reserv(2, 18, 5, 0, 4);
	input_reserv(2, 18, 8, 4, 1);
	input_reserv(2, 18, 6, 6, 1);
	input_reserv(2, 18, 18, 6, 3);
	input_reserv(2, 18, 12, 6, 5);
	input_reserv(2, 18, 12, 7, 5);
	input_reserv(2, 19, 14, 0, 0);
	input_reserv(2, 19, 8, 0, 1);
	input_reserv(2, 19, 18, 3, 6);
	input_reserv(2, 19, 2, 6, 1);
	input_reserv(2, 20, 8, 3, 4);
	input_reserv(2, 20, 6, 4, 4);
	input_reserv(2, 21, 7, 2, 7);
	input_reserv(2, 21, 4, 5, 1);
	input_reserv(2, 21, 13, 6, 6);
	input_reserv(2, 22, 5, 4, 5);
	input_reserv(2, 22, 20, 7, 0);
	input_reserv(2, 23, 4, 1, 0);
	input_reserv(2, 23, 4, 3, 5);
	input_reserv(2, 23, 3, 4, 5);
	input_reserv(2, 23, 14, 5, 5);
	input_reserv(2, 23, 10, 6, 7);
	input_reserv(2, 24, 13, 4, 3);
	input_reserv(2, 24, 11, 4, 4);
	input_reserv(2, 24, 9, 6, 7);
	input_reserv(2, 25, 5, 5, 1);
	input_reserv(2, 25, 1, 7, 5);
	input_reserv(2, 26, 11, 0, 2);
	input_reserv(2, 26, 11, 1, 3);
	input_reserv(2, 26, 9, 3, 5);
	input_reserv(2, 26, 7, 5, 5);
	input_reserv(2, 26, 8, 5, 6);
	input_reserv(2, 26, 17, 7, 1);
	input_reserv(2, 26, 12, 7, 5);
	input_reserv(2, 27, 1, 0, 3);
	input_reserv(2, 27, 4, 3, 5);
	input_reserv(2, 27, 13, 4, 7);
	input_reserv(2, 28, 9, 0, 4);
	input_reserv(2, 28, 12, 0, 6);
	input_reserv(2, 28, 16, 6, 1);
	input_reserv(2, 29, 20, 0, 5);
	input_reserv(2, 29, 7, 1, 6);
	input_reserv(2, 29, 10, 2, 1);
	input_reserv(2, 29, 9, 2, 2);
	input_reserv(2, 29, 13, 6, 3);
	input_reserv(3, 0, 12, 1, 7);
	input_reserv(3, 0, 16, 5, 7);
	input_reserv(3, 1, 8, 5, 3);
	input_reserv(3, 1, 6, 5, 7);
	input_reserv(3, 2, 2, 0, 7);
	input_reserv(3, 2, 9, 1, 0);
	input_reserv(3, 2, 20, 2, 7);
	input_reserv(3, 2, 14, 3, 1);
	input_reserv(3, 2, 18, 4, 5);
	input_reserv(3, 2, 19, 6, 0);
	input_reserv(3, 2, 17, 7, 5);
	input_reserv(3, 3, 9, 0, 6);
	input_reserv(3, 3, 4, 1, 3);
	input_reserv(3, 3, 12, 2, 6);
	input_reserv(3, 4, 3, 2, 4);
	input_reserv(3, 4, 17, 3, 1);
	input_reserv(3, 4, 6, 3, 4);
	input_reserv(3, 4, 20, 6, 5);
	input_reserv(3, 5, 9, 2, 1);
	input_reserv(3, 5, 11, 5, 7);
	input_reserv(3, 5, 9, 6, 1);
	input_reserv(3, 5, 17, 6, 3);
	input_reserv(3, 6, 6, 0, 2);
	input_reserv(3, 6, 11, 1, 6);
	input_reserv(3, 6, 7, 3, 1);
	input_reserv(3, 6, 7, 4, 0);
	input_reserv(3, 7, 8, 3, 7);
	input_reserv(3, 7, 19, 6, 7);
	input_reserv(3, 8, 20, 3, 1);
	input_reserv(3, 8, 6, 3, 7);
	input_reserv(3, 9, 20, 1, 3);
	input_reserv(3, 9, 1, 2, 7);
	input_reserv(3, 9, 12, 4, 0);
	input_reserv(3, 9, 11, 7, 0);
	input_reserv(3, 9, 12, 7, 5);
	input_reserv(3, 10, 11, 1, 2);
	input_reserv(3, 10, 3, 2, 7);
	input_reserv(3, 10, 19, 3, 3);
	input_reserv(3, 10, 3, 4, 7);
	input_reserv(3, 10, 6, 5, 5);
	input_reserv(3, 11, 19, 0, 4);
	input_reserv(3, 11, 9, 0, 7);
	input_reserv(3, 11, 6, 1, 5);
	input_reserv(3, 11, 12, 4, 1);
	input_reserv(3, 11, 3, 4, 6);
	input_reserv(3, 11, 4, 6, 0);
	input_reserv(3, 11, 20, 7, 3);
	input_reserv(3, 11, 20, 7, 7);
	input_reserv(3, 12, 8, 0, 4);
	input_reserv(3, 12, 15, 1, 6);
	input_reserv(3, 12, 6, 2, 0);
	input_reserv(3, 12, 19, 5, 0);
	input_reserv(3, 12, 7, 7, 1);
	input_reserv(3, 12, 19, 7, 3);
	input_reserv(3, 13, 13, 1, 5);
	input_reserv(3, 13, 19, 5, 1);
	input_reserv(3, 13, 6, 6, 4);
	input_reserv(3, 14, 15, 1, 6);
	input_reserv(3, 14, 18, 2, 5);
	input_reserv(3, 14, 11, 3, 7);
	input_reserv(3, 14, 20, 5, 6);
	input_reserv(3, 14, 12, 6, 5);
	input_reserv(3, 14, 11, 6, 6);
	input_reserv(3, 14, 13, 7, 6);
	input_reserv(3, 15, 17, 5, 1);
	input_reserv(3, 15, 10, 5, 7);
	input_reserv(3, 15, 7, 6, 0);
	input_reserv(3, 16, 13, 1, 1);
	input_reserv(3, 17, 14, 1, 7);
	input_reserv(3, 17, 19, 2, 1);
	input_reserv(3, 17, 17, 5, 3);
	input_reserv(3, 17, 9, 6, 4);
	input_reserv(3, 18, 18, 1, 6);
	input_reserv(3, 18, 7, 2, 4);
	input_reserv(3, 18, 19, 3, 4);
	input_reserv(3, 18, 11, 3, 5);
	input_reserv(3, 19, 5, 1, 2);
	input_reserv(3, 19, 14, 3, 1);
	input_reserv(3, 20, 7, 5, 0);
	input_reserv(3, 20, 11, 6, 3);
	input_reserv(3, 20, 16, 7, 4);
	input_reserv(3, 21, 12, 1, 1);
	input_reserv(3, 21, 20, 3, 2);
	input_reserv(3, 21, 18, 4, 0);
	input_reserv(3, 21, 12, 4, 4);
	input_reserv(3, 21, 20, 5, 1);
	input_reserv(3, 21, 16, 6, 2);
	input_reserv(3, 22, 18, 2, 4);
	input_reserv(3, 22, 15, 2, 6);
	input_reserv(3, 22, 19, 3, 5);
	input_reserv(3, 22, 17, 3, 7);
	input_reserv(3, 22, 10, 4, 2);
	input_reserv(3, 22, 9, 4, 5);
	input_reserv(3, 22, 18, 7, 7);
	input_reserv(3, 23, 8, 2, 1);
	input_reserv(3, 23, 16, 4, 0);
	input_reserv(3, 23, 8, 5, 3);
	input_reserv(3, 23, 13, 6, 3);
	input_reserv(3, 24, 18, 0, 5);
	input_reserv(3, 24, 18, 0, 7);
	input_reserv(3, 24, 11, 3, 0);
	input_reserv(3, 24, 11, 4, 1);
	input_reserv(3, 24, 13, 4, 7);
	input_reserv(3, 25, 10, 0, 7);
	input_reserv(3, 25, 1, 2, 3);
	input_reserv(3, 25, 19, 2, 7);
	input_reserv(3, 25, 5, 4, 5);
	input_reserv(3, 26, 4, 5, 5);
	input_reserv(3, 26, 15, 7, 6);
	input_reserv(3, 27, 16, 0, 5);
	input_reserv(3, 27, 15, 3, 6);
	input_reserv(3, 27, 11, 7, 2);
	input_reserv(3, 28, 16, 6, 3);
	input_reserv(3, 29, 15, 1, 5);
	input_reserv(3, 29, 17, 6, 5);
	input_reserv(4, 0, 10, 0, 6);
	input_reserv(4, 0, 10, 1, 0);
	input_reserv(4, 0, 9, 6, 1);
	input_reserv(4, 1, 7, 2, 1);
	input_reserv(4, 1, 20, 4, 3);
	input_reserv(4, 1, 10, 4, 6);
	input_reserv(4, 1, 4, 7, 1);
	input_reserv(4, 2, 2, 1, 7);
	input_reserv(4, 2, 3, 2, 0);
	input_reserv(4, 3, 12, 2, 1);
	input_reserv(4, 3, 1, 2, 6);
	input_reserv(4, 3, 8, 2, 7);
	input_reserv(4, 3, 19, 5, 0);
	input_reserv(4, 3, 12, 6, 7);
	input_reserv(4, 4, 8, 0, 5);
	input_reserv(4, 4, 8, 7, 0);
	input_reserv(4, 4, 8, 7, 4);
	input_reserv(4, 5, 2, 0, 2);
	input_reserv(4, 5, 19, 0, 7);
	input_reserv(4, 5, 8, 2, 3);
	input_reserv(4, 5, 11, 3, 5);
	input_reserv(4, 5, 13, 4, 4);
	input_reserv(4, 5, 18, 4, 5);
	input_reserv(4, 5, 9, 5, 2);
	input_reserv(4, 5, 2, 5, 3);
	input_reserv(4, 5, 6, 5, 5);
	input_reserv(4, 6, 5, 0, 3);
	input_reserv(4, 6, 1, 4, 0);
	input_reserv(4, 6, 4, 4, 3);
	input_reserv(4, 6, 10, 7, 6);
	input_reserv(4, 7, 8, 1, 1);
	input_reserv(4, 7, 7, 4, 5);
	input_reserv(4, 7, 16, 7, 1);
	input_reserv(4, 7, 7, 7, 6);
	input_reserv(4, 8, 1, 1, 4);
	input_reserv(4, 8, 7, 2, 1);
	input_reserv(4, 8, 15, 5, 0);
	input_reserv(4, 8, 2, 6, 3);
	input_reserv(4, 9, 3, 2, 4);
	input_reserv(4, 9, 9, 5, 6);
	input_reserv(4, 9, 10, 7, 3);
	input_reserv(4, 10, 13, 4, 1);
	input_reserv(4, 10, 3, 7, 1);
	input_reserv(4, 11, 13, 3, 7);
	input_reserv(4, 11, 15, 6, 2);
	input_reserv(4, 11, 7, 7, 1);
	input_reserv(4, 11, 5, 7, 6);
	input_reserv(4, 12, 19, 2, 3);
	input_reserv(4, 12, 20, 2, 6);
	input_reserv(4, 12, 2, 4, 5);
	input_reserv(4, 13, 5, 0, 4);
	input_reserv(4, 13, 14, 1, 3);
	input_reserv(4, 13, 15, 3, 3);
	input_reserv(4, 13, 10, 4, 0);
	input_reserv(4, 13, 13, 7, 6);
	input_reserv(4, 14, 20, 1, 2);
	input_reserv(4, 14, 10, 2, 0);
	input_reserv(4, 14, 2, 2, 7);
	input_reserv(4, 14, 15, 6, 6);
	input_reserv(4, 14, 13, 7, 7);
	input_reserv(4, 15, 16, 0, 6);
	input_reserv(4, 15, 1, 3, 4);
	input_reserv(4, 15, 16, 4, 3);
	input_reserv(4, 15, 18, 6, 2);
	input_reserv(4, 15, 12, 7, 1);
	input_reserv(4, 16, 2, 1, 7);
	input_reserv(4, 16, 1, 3, 1);
	input_reserv(4, 16, 8, 5, 2);
	input_reserv(4, 16, 2, 7, 6);
	input_reserv(4, 17, 10, 3, 1);
	input_reserv(4, 17, 3, 5, 6);
	input_reserv(4, 18, 7, 0, 1);
	input_reserv(4, 19, 1, 1, 0);
	input_reserv(4, 19, 14, 3, 1);
	input_reserv(4, 19, 9, 4, 2);
	input_reserv(4, 20, 8, 1, 0);
	input_reserv(4, 20, 7, 2, 3);
	input_reserv(4, 20, 14, 3, 6);
	input_reserv(4, 21, 20, 5, 6);
	input_reserv(4, 21, 8, 6, 5);
	input_reserv(4, 21, 12, 7, 5);
	input_reserv(4, 22, 14, 0, 1);
	input_reserv(4, 22, 3, 4, 4);
	input_reserv(4, 22, 6, 7, 0);
	input_reserv(4, 23, 9, 0, 1);
	input_reserv(4, 23, 12, 5, 2);
	input_reserv(4, 23, 11, 6, 6);
	input_reserv(4, 24, 1, 1, 2);
	input_reserv(4, 24, 14, 2, 2);
	input_reserv(4, 24, 9, 3, 1);
	input_reserv(4, 24, 17, 3, 6);
	input_reserv(4, 24, 11, 6, 7);
	input_reserv(4, 25, 1, 0, 6);
	input_reserv(4, 25, 8, 3, 0);
	input_reserv(4, 25, 8, 3, 3);
	input_reserv(4, 25, 4, 3, 6);
	input_reserv(4, 25, 14, 5, 0);
	input_reserv(4, 26, 9, 1, 3);
	input_reserv(4, 26, 3, 2, 0);
	input_reserv(4, 26, 4, 4, 2);
	input_reserv(4, 26, 17, 4, 6);
	input_reserv(4, 26, 19, 6, 7);
	input_reserv(4, 26, 6, 7, 6);
	input_reserv(4, 27, 18, 3, 1);
	input_reserv(4, 27, 13, 5, 3);
	input_reserv(4, 27, 10, 7, 0);
	input_reserv(4, 28, 12, 1, 3);
	input_reserv(4, 28, 9, 4, 4);
	input_reserv(4, 29, 1, 1, 0);
	input_reserv(4, 29, 5, 4, 5);
	input_reserv(4, 29, 11, 5, 4);
	input_reserv(4, 29, 1, 6, 4);
	input_reserv(5, 0, 20, 2, 7);
	input_reserv(5, 0, 18, 3, 2);
	input_reserv(5, 0, 12, 6, 7);
	input_reserv(5, 0, 2, 7, 5);
	input_reserv(5, 1, 3, 0, 2);
	input_reserv(5, 1, 6, 0, 6);
	input_reserv(5, 1, 3, 1, 3);
	input_reserv(5, 1, 20, 1, 7);
	input_reserv(5, 1, 2, 5, 1);
	input_reserv(5, 1, 13, 5, 2);
	input_reserv(5, 2, 14, 1, 0);
	input_reserv(5, 2, 14, 4, 1);
	input_reserv(5, 2, 14, 4, 5);
	input_reserv(5, 2, 15, 7, 4);
	input_reserv(5, 3, 14, 0, 1);
	input_reserv(5, 3, 7, 3, 3);
	input_reserv(5, 3, 8, 6, 0);
	input_reserv(5, 4, 4, 2, 1);
	input_reserv(5, 5, 9, 0, 4);
	input_reserv(5, 5, 8, 4, 1);
	input_reserv(5, 5, 4, 5, 2);
	input_reserv(5, 5, 13, 7, 5);
	input_reserv(5, 6, 1, 4, 3);
	input_reserv(5, 6, 13, 6, 4);
	input_reserv(5, 7, 19, 0, 0);
	input_reserv(5, 7, 8, 5, 7);
	input_reserv(5, 7, 9, 7, 0);
	input_reserv(5, 8, 16, 0, 3);
	input_reserv(5, 8, 8, 0, 6);
	input_reserv(5, 8, 10, 3, 3);
	input_reserv(5, 8, 15, 5, 0);
	input_reserv(5, 8, 18, 6, 0);
	input_reserv(5, 9, 3, 0, 1);
	input_reserv(5, 9, 8, 0, 7);
	input_reserv(5, 9, 16, 5, 4);
	input_reserv(5, 9, 18, 6, 7);
	input_reserv(5, 9, 16, 7, 0);
	input_reserv(5, 9, 5, 7, 3);
	input_reserv(5, 10, 5, 2, 3);
	input_reserv(5, 10, 8, 3, 4);
	input_reserv(5, 10, 15, 6, 5);
	input_reserv(5, 11, 15, 5, 7);
	input_reserv(5, 11, 14, 6, 0);
	input_reserv(5, 11, 10, 6, 6);
	input_reserv(5, 11, 18, 7, 3);
	input_reserv(5, 12, 1, 0, 3);
	input_reserv(5, 12, 15, 0, 7);
	input_reserv(5, 12, 4, 1, 0);
	input_reserv(5, 12, 16, 1, 2);
	input_reserv(5, 12, 5, 2, 5);
	input_reserv(5, 12, 12, 3, 1);
	input_reserv(5, 13, 3, 0, 4);
	input_reserv(5, 13, 15, 3, 6);
	input_reserv(5, 13, 3, 5, 5);
	input_reserv(5, 13, 10, 6, 2);
	input_reserv(5, 14, 17, 0, 0);
	input_reserv(5, 14, 20, 0, 3);
	input_reserv(5, 14, 6, 3, 2);
	input_reserv(5, 14, 19, 5, 4);
	input_reserv(5, 14, 5, 6, 7);
	input_reserv(5, 15, 13, 0, 2);
	input_reserv(5, 15, 2, 1, 3);
	input_reserv(5, 15, 16, 4, 4);
	input_reserv(5, 16, 17, 0, 3);
	input_reserv(5, 16, 1, 2, 6);
	input_reserv(5, 16, 8, 5, 2);
	input_reserv(5, 16, 20, 6, 1);
	input_reserv(5, 16, 9, 7, 4);
	input_reserv(5, 16, 5, 7, 5);
	input_reserv(5, 16, 20, 7, 6);
	input_reserv(5, 17, 9, 0, 4);
	input_reserv(5, 17, 20, 0, 7);
	input_reserv(5, 17, 6, 2, 7);
	input_reserv(5, 17, 14, 4, 4);
	input_reserv(5, 17, 6, 5, 6);
	input_reserv(5, 17, 5, 6, 5);
	input_reserv(5, 18, 5, 5, 0);
	input_reserv(5, 18, 5, 5, 2);
	input_reserv(5, 18, 3, 6, 3);
	input_reserv(5, 18, 7, 6, 6);
	input_reserv(5, 18, 10, 6, 7);
	input_reserv(5, 19, 18, 1, 1);
	input_reserv(5, 19, 6, 2, 5);
	input_reserv(5, 19, 19, 3, 4);
	input_reserv(5, 19, 6, 7, 6);
	input_reserv(5, 20, 4, 0, 0);
	input_reserv(5, 20, 11, 4, 1);
	input_reserv(5, 20, 9, 6, 0);
	input_reserv(5, 20, 6, 6, 3);
	input_reserv(5, 20, 19, 7, 4);
	input_reserv(5, 21, 1, 1, 3);
	input_reserv(5, 21, 16, 1, 5);
	input_reserv(5, 21, 20, 3, 1);
	input_reserv(5, 21, 8, 5, 3);
	input_reserv(5, 22, 7, 0, 7);
	input_reserv(5, 22, 12, 1, 7);
	input_reserv(5, 22, 3, 2, 3);
	input_reserv(5, 22, 20, 7, 5);
	input_reserv(5, 23, 19, 2, 2);
	input_reserv(5, 23, 3, 4, 5);
	input_reserv(5, 23, 15, 6, 2);
	input_reserv(5, 23, 13, 7, 0);
	input_reserv(5, 24, 1, 1, 7);
	input_reserv(5, 24, 9, 4, 4);
	input_reserv(5, 24, 4, 5, 6);
	input_reserv(5, 24, 18, 6, 7);
	input_reserv(5, 25, 2, 7, 2);
	input_reserv(5, 25, 6, 7, 3);
	input_reserv(5, 25, 8, 7, 7);
	input_reserv(5, 26, 11, 1, 5);
	input_reserv(5, 26, 6, 4, 1);
	input_reserv(5, 26, 7, 4, 3);
	input_reserv(5, 26, 13, 4, 6);
	input_reserv(5, 27, 3, 0, 0);
	input_reserv(5, 27, 2, 1, 2);
	input_reserv(5, 27, 7, 2, 4);
	input_reserv(5, 27, 9, 5, 4);
	input_reserv(5, 28, 18, 0, 7);
	input_reserv(5, 28, 12, 7, 2);
	input_reserv(5, 28, 20, 7, 3);
	input_reserv(5, 28, 12, 7, 5);
	input_reserv(5, 29, 7, 3, 7);
	input_reserv(5, 29, 19, 4, 2);
	input_reserv(5, 29, 19, 6, 0);
	input_reserv(5, 29, 7, 7, 1);
	input_reserv(5, 29, 17, 7, 2);
	input_reserv(5, 29, 14, 7, 6);
	input_reserv(5, 29, 10, 7, 7);
	input_reserv(6, 0, 19, 0, 4);
	input_reserv(6, 0, 8, 3, 1);
	input_reserv(6, 0, 6, 7, 0);
	input_reserv(6, 0, 5, 7, 1);
	input_reserv(6, 0, 11, 7, 3);
	input_reserv(6, 0, 1, 7, 7);
	input_reserv(6, 1, 8, 1, 7);
	input_reserv(6, 1, 20, 2, 7);
	input_reserv(6, 1, 11, 5, 6);
	input_reserv(6, 1, 19, 6, 2);
	input_reserv(6, 2, 7, 0, 1);
	input_reserv(6, 2, 7, 0, 2);
	input_reserv(6, 2, 1, 2, 0);
	input_reserv(6, 2, 14, 2, 1);
	input_reserv(6, 2, 18, 4, 0);
	input_reserv(6, 2, 6, 6, 2);
	input_reserv(6, 2, 18, 7, 1);
	input_reserv(6, 2, 4, 7, 6);
	input_reserv(6, 3, 7, 1, 5);
	input_reserv(6, 3, 1, 2, 3);
	input_reserv(6, 3, 8, 6, 5);
	input_reserv(6, 4, 19, 5, 5);
	input_reserv(6, 5, 2, 1, 3);
	input_reserv(6, 5, 12, 3, 1);
	input_reserv(6, 5, 18, 4, 6);
	input_reserv(6, 5, 4, 7, 0);
	input_reserv(6, 6, 11, 1, 1);
	input_reserv(6, 6, 16, 4, 2);
	input_reserv(6, 6, 16, 5, 4);
	input_reserv(6, 6, 5, 7, 4);
	input_reserv(6, 7, 6, 2, 7);
	input_reserv(6, 7, 20, 5, 1);
	input_reserv(6, 7, 2, 6, 1);
	input_reserv(6, 7, 14, 6, 5);
	input_reserv(6, 7, 12, 7, 1);
	input_reserv(6, 8, 19, 1, 3);
	input_reserv(6, 8, 4, 2, 4);
	input_reserv(6, 8, 19, 4, 1);
	input_reserv(6, 8, 10, 7, 2);
	input_reserv(6, 8, 12, 7, 7);
	input_reserv(6, 9, 5, 2, 6);
	input_reserv(6, 9, 12, 3, 0);
	input_reserv(6, 9, 1, 4, 6);
	input_reserv(6, 9, 8, 5, 4);
	input_reserv(6, 9, 15, 6, 0);
	input_reserv(6, 10, 5, 0, 4);
	input_reserv(6, 10, 2, 0, 5);
	input_reserv(6, 10, 14, 2, 4);
	input_reserv(6, 10, 11, 2, 6);
	input_reserv(6, 10, 9, 5, 7);
	input_reserv(6, 10, 10, 6, 6);
	input_reserv(6, 11, 10, 0, 1);
	input_reserv(6, 11, 18, 2, 0);
	input_reserv(6, 11, 16, 3, 4);
	input_reserv(6, 11, 13, 5, 0);
	input_reserv(6, 11, 14, 5, 2);
	input_reserv(6, 11, 19, 7, 4);
	input_reserv(6, 12, 4, 1, 7);
	input_reserv(6, 12, 1, 6, 2);
	input_reserv(6, 12, 12, 6, 6);
	input_reserv(6, 12, 1, 7, 4);
	input_reserv(6, 13, 13, 5, 4);
	input_reserv(6, 13, 17, 7, 6);
	input_reserv(6, 14, 5, 2, 3);
	input_reserv(6, 14, 8, 4, 3);
	input_reserv(6, 14, 10, 5, 2);
	input_reserv(6, 14, 5, 6, 1);
	input_reserv(6, 14, 1, 6, 4);
	input_reserv(6, 14, 20, 7, 4);
	input_reserv(6, 15, 2, 3, 6);
	input_reserv(6, 15, 12, 6, 7);
	input_reserv(6, 16, 10, 1, 7);
	input_reserv(6, 16, 3, 2, 0);
	input_reserv(6, 16, 9, 4, 2);
	input_reserv(6, 16, 17, 6, 7);
	input_reserv(6, 16, 13, 7, 6);
	input_reserv(6, 17, 10, 0, 5);
	input_reserv(6, 17, 19, 6, 5);
	input_reserv(6, 17, 2, 7, 5);
	input_reserv(6, 18, 1, 2, 6);
	input_reserv(6, 18, 19, 3, 5);
	input_reserv(6, 18, 10, 5, 0);
	input_reserv(6, 18, 8, 6, 2);
	input_reserv(6, 19, 12, 0, 0);
	input_reserv(6, 19, 1, 6, 5);
	input_reserv(6, 19, 5, 7, 3);
	input_reserv(6, 19, 9, 7, 7);
	input_reserv(6, 20, 10, 2, 7);
	input_reserv(6, 20, 3, 3, 6);
	input_reserv(6, 21, 13, 0, 6);
	input_reserv(6, 21, 15, 3, 4);
	input_reserv(6, 21, 10, 3, 7);
	input_reserv(6, 21, 10, 4, 2);
	input_reserv(6, 21, 3, 4, 3);
	input_reserv(6, 21, 11, 4, 6);
	input_reserv(6, 21, 17, 5, 0);
	input_reserv(6, 21, 17, 6, 1);
	input_reserv(6, 22, 19, 1, 4);
	input_reserv(6, 22, 4, 2, 2);
	input_reserv(6, 22, 19, 6, 1);
	input_reserv(6, 23, 12, 6, 3);
	input_reserv(6, 24, 17, 0, 4);
	input_reserv(6, 24, 20, 5, 0);
	input_reserv(6, 24, 17, 5, 3);
	input_reserv(6, 24, 13, 6, 5);
	input_reserv(6, 25, 9, 0, 7);
	input_reserv(6, 26, 20, 0, 7);
	input_reserv(6, 26, 19, 5, 7);
	input_reserv(6, 26, 14, 6, 0);
	input_reserv(6, 26, 19, 7, 7);
	input_reserv(6, 27, 14, 0, 7);
	input_reserv(6, 27, 14, 1, 0);
	input_reserv(6, 27, 19, 1, 2);
	input_reserv(6, 27, 3, 1, 6);
	input_reserv(6, 27, 15, 4, 0);
	input_reserv(6, 27, 10, 4, 5);
	input_reserv(6, 27, 14, 6, 5);
	input_reserv(6, 27, 14, 7, 2);
	input_reserv(6, 28, 10, 0, 3);
	input_reserv(6, 28, 19, 5, 2);
	input_reserv(6, 28, 17, 7, 3);
	input_reserv(6, 29, 16, 1, 7);
	input_reserv(6, 29, 2, 5, 1);
}