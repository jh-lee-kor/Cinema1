#include "Seat.h"

int Seat::getuser() {
	return this->seatuser;
}

void Seat::setuser(int usernum) {
	this->seatuser = usernum;
}

bool Seat::isbooked() {
	return (this->seatuser) ? true : false; // �¼� ������ 0�̸� ������� ����
}
