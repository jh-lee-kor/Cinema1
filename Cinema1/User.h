#ifndef USER_H
#define USER_H

#include <string>

class User {
	std::string name;
	std::string id;
	std::string pw;
	char gender = '\0'; // 미등록시 성별확인 gender는 NUL, gender로 찾을 때
	int point;
	int usernum = 0; // 0은 미등록, 값이 있으면 등록된 유저의 인덱스 번호 - 1

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