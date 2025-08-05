#pragma once
#include <iostream>
#include <list>
using namespace std;

#define numItr list<char>::iterator

class largeInt {
private:
	list<char>* _num;
public:
	largeInt() : _num(new list<char>()) {};
	largeInt(int);
	largeInt(unsigned int);
	largeInt(list<char>& a) : _num(new list<char>(a)) {};
	~largeInt() { _num->clear(); delete _num; }

	list<char>* getNum() { return _num; }
	void setNum(int);
	void setNum(unsigned int);
	void setNum(list<char>&);
	
	bool operator>(largeInt&);
	bool operator==(largeInt&);

	void operator>>(unsigned int);
	void operator<<(unsigned int);

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