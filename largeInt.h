#pragma once
#include <iostream>
#include <list>
using namespace std;

largeInt zero(0);

#define numItr list<char>::iterator

class largeInt {
private:
	list<char>* _num;
public:
	largeInt() : _num(new list<char>(1, 0)) {};
	largeInt(int);
	largeInt(unsigned int);
	largeInt(list<char>& a) : _num(a.size() ? new list<char>(a) : new list<char>(1, 0)) {};
	largeInt(largeInt& a) : largeInt(*(a.getNum())) {};
	~largeInt() { _num->clear(); delete _num; }

	list<char>* getNum() { return _num; }
	void setNum(int);
	void setNum(unsigned int);
	void setNum(list<char>&);
	void setNum(largeInt& a) { this->setNum(*(a.getNum())); }
	
	bool operator>(largeInt&);
	bool operator<(largeInt& a) { return a > *this; }
	bool operator==(largeInt&);
	bool operator>=(largeInt& a) { return (*this > a) || (*this == a); }
	bool operator!=(largeInt& a) { return !(*this == a); }

	void operator>>=(unsigned int);
	void operator<<=(unsigned int);

	void operator+=(largeInt&);
	void operator-=(largeInt&);
	void operator%=(largeInt&);

	largeInt operator-();
	largeInt operator+(largeInt&);
	largeInt operator-(largeInt&);
	largeInt operator*(largeInt&);
	largeInt operator/(largeInt&);
	largeInt operator%(largeInt&);

	void operator+=(int a) { *this += largeInt(a); }
	void operator-=(int a) { *this += largeInt(-a); }
	largeInt operator+(int a) { return largeInt(*this) + largeInt(a); }
	largeInt operator-(int a) { return largeInt(*this) - largeInt(a); }
	largeInt operator*(int a) { return largeInt(*this) * largeInt(a); }
	bool operator>(int a) { return largeInt(*this) > largeInt(a); }
	bool operator>=(int a) { return largeInt(*this) > largeInt(a); }
	largeInt operator/(int a) { return largeInt(*this) / largeInt(a); }
	largeInt operator%(int a) { return largeInt(*this) % largeInt(a); }

private:
	largeInt karatsuba_simple(largeInt& a, largeInt& b); // this function is for multiplying with numbers that are no more than 4B
	largeInt karatsuba_multiply(largeInt& a, largeInt& b); // used in * operator, a is make sure to be larger in size than b in the function
};