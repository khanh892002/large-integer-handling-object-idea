#pragma once
#include <iostream>
#include <vector>
using namespace std;

class largeInt {
private:
	bool _isNeg;
	vector<unsigned char>* _num;
public:
	largeInt() : _isNeg(false), _num(new vector<unsigned char>()) {};
	largeInt(int);
	largeInt(unsigned int);
	largeInt(vector<unsigned char>&);
	~largeInt() { _num->clear(); delete _num; }

	vector<unsigned char>* getNum() { return _num; }
	void setNum(int);
	void setNum(unsigned int);
	void setNum(vector<unsigned char>&);
	
	bool getIsNeg() { return _isNeg; }
	void setIsNeg(bool a) { _isNeg = a; }

	bool operator>(largeInt&);
	bool operator==(largeInt&);

	void operator+=(largeInt&);
	void operator-=(largeInt&);
	largeInt operator+(largeInt&);
	largeInt operator-(largeInt&);
	largeInt operator*(largeInt&);
	largeInt operator/(largeInt&);
	largeInt operator%(largeInt&);

	void operator+=(int a);
	void operator-=(int a);
	largeInt operator+(int a) { return largeInt(*this) + largeInt(a); }
	largeInt operator-(int a) { return largeInt(*this) - largeInt(a); }
	largeInt operator*(int a) { return largeInt(*this) * largeInt(a); }
	bool operator>(int a) { return largeInt(*this) > largeInt(a); }
	bool operator>=(int a) { return largeInt(*this) > largeInt(a); }
	largeInt operator/(int a) { return largeInt(*this) / largeInt(a); }
	largeInt operator%(int a) { return largeInt(*this) % largeInt(a); }
};