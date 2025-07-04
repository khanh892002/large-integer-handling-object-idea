#pragma once
#include <iostream>
#include <vector>
using namespace std;

class largeInt {
private:
	bool _isNeg = false;
	vector<char>* _num = NULL;
public:
	largeInt(int);
	largeInt(unsigned int);
	largeInt(vector<char>&);
	~largeInt() { _num->clear(); delete _num; }
	vector<char> getNum() { return *_num; }
	void setNum(int);
	void setNum(unsigned int);
	void setNum(vector<char>&);
	bool getIsNeg() { return _isNeg; }
	void setIsNeg(bool a) { _isNeg = a; }

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