#ifndef SEAT_H
#define SEAT_H

class Seat {
	int seatuser = 0; // 0일 때 예매되지 않은 상태, 예매되었을 때 회원번호

public:
	int getuser();
	void setuser(int userid);
	bool isbooked();
};

#endif