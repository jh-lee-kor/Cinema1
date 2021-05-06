#include "Seat.h"

int Seat::getuser() {
	return this->seatuser;
}

void Seat::setuser(int usernum) {
	this->seatuser = usernum;
}

bool Seat::isbooked() {
	return (this->seatuser) ? true : false; // 좌석 유저가 0이면 예약되지 않음
}
