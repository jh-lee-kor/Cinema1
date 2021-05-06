#ifndef USER_H
#define USER_H

#include <string>

class User {
	std::string name;
	char gender = '\0'; // 미등록시 성별확인 gender는 NUL, gender로 찾을 때
	int point;
	int userid = 0; // 0은 미등록, 값이 있으면 등록된 유저의 id

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