#ifndef SEAT_H
#define SEAT_H

class Seat {
	int seatuser = 0; // 0�� �� ���ŵ��� ���� ����, ���ŵǾ��� �� ȸ����ȣ

public:
	int getuser();
	void setuser(int usernum);
	bool isbooked();
};

#endif