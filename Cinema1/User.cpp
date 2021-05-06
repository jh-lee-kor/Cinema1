#include "User.h"

#include <string>
using namespace std;

int User::totaluser = 0;


void User::input_user(string name, std::string id, std::string pw,char gender) {
	this->name = name;
	this->id = id;
	this->pw = pw;
	this->gender = gender;
	totaluser++;
	this->usernum = totaluser;
}

string User::getID() {
	return this->id;
}

string User::getPW() {
	return this->pw;
}

string User::getName() {
	return this->name;
}

void User::setName(string name) {
	this->name = name;
}

char User::getGender() {
	return this->gender;
}

void User::setGender(char gender) {
	this->gender = gender;
}

int User::getPoint() {
	return this->point;
}

void User::setPoint(int point) {
	this->point = point;
}

int User::getusernum() {
	return this->usernum;
}