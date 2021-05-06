#ifndef USER_H
#define USER_H

#include <string>

class User {
	std::string name;
	char gender = '\0'; // �̵�Ͻ� ����Ȯ�� gender�� NUL, gender�� ã�� ��
	int point;
	int userid = 0; // 0�� �̵��, ���� ������ ��ϵ� ������ id

public:
	static int totaluser;
	void input_user(std::string name, char gender);
	std::string getName();
	void setName(std::string name);
	char getGender();
	void setGender(char gender);
	int getPoint();
	void setPoint(int point);
};

#endif