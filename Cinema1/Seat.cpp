#include "Seat.h"

int Seat::getuser() {
	return this->seatuser;
}

void Seat::setuser(int userid) {
	this->seatuser = userid;
}

bool Seat::isbooked() {
	return (this->seatuser) ? true : false; // �¼� ������ 0�̸� ������� ����
}
