#pragma once
#include <iostream>
#include <vector>
using namespace std;

#define numItr vector<char>::iterator

class largeInt {
private:
	vector<char>* _num;
public:
	largeInt() : _num(new vector<char>()) {};
	largeInt(int);
	largeInt(unsigned int);
	largeInt(vector<char>& a) : _num(new vector<char>(a)) {};
	~largeInt() { _num->clear(); delete _num; }

	vector<char>* getNum() { return _num; }
	void setNum(int);
	void setNum(unsigned int);
	void setNum(vector<char>&);
	
	bool operator>(largeInt&);
	bool operator==(largeInt&);

	void operator+=(largeInt&);
	void operator-=(largeInt&);

	largeInt operator-();
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