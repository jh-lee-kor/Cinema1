#ifndef USER_H
#define USER_H

#include <string>

class User {
	std::string name;
	std::string id;
	std::string pw;
	char gender = '\0'; // �̵�Ͻ� ����Ȯ�� gender�� NUL, gender�� ã�� ��
	int point;
	int usernum = 0; // 0�� �̵��, ���� ������ ��ϵ� ������ �ε��� ��ȣ - 1

public:
	static int totaluser;
	std::string getID();
	std::string getPW();
	void input_user(std::string name, std::string id, std::string pw, char gender);
	std::string getName();
	int getusernum();
	void setName(std::string name);
	char getGender();
	void setGender(char gender);
	int getPoint();
	void setPoint(int point);
};
#endif