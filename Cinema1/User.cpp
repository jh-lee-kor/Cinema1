#include "User.h"

#include <string>
using namespace std;

int User::totaluser = 0;


void User::input_user(string name, char gender) {
	this->name = name;
	this->gender = gender;
	totaluser++;
	this->userid = totaluser;
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