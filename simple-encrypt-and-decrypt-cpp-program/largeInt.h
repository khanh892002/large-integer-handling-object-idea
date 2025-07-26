#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class largeInt {
private:
	string num;
public:
	largeInt() { num = "0"; }
	largeInt(unsigned int a) { stringstream ss; ss << a; ss >> num; }
	largeInt(string);
	~largeInt() { num.clear(); }
	string getNum() { return num; }
	void setNum(string);

	largeInt operator+(largeInt);
	largeInt operator-(largeInt);
	largeInt operator*(largeInt);
	bool operator>(largeInt);
	bool operator>=(largeInt);
	largeInt operator/(largeInt);
	largeInt operator%(largeInt);
	largeInt operator+(int a) { return largeInt(*this) + largeInt(a); }
	largeInt operator-(int a) { return largeInt(*this) - largeInt(a); }
	largeInt operator*(int a) { return largeInt(*this) * largeInt(a); }
	bool operator>(int a) { return largeInt(*this) > largeInt(a); }
	bool operator>=(int a) { return largeInt(*this) > largeInt(a); }
	largeInt operator/(int a) { return largeInt(*this) / largeInt(a); }
	largeInt operator%(int a) { return largeInt(*this) % largeInt(a); }
};