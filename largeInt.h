#pragma once
#include <iostream>
#include <list>
using namespace std;

largeInt zero(0);

#define numLi list<unsigned char>
#define numItr numLi::iterator

class largeInt {
private:
	numLi* _num;
public:
	largeInt() : _num(new numLi(1, 0)) {};
	largeInt(int);
	largeInt(unsigned int);
	largeInt(numLi& a) : _num((a.size()) ? new numLi(a) : new numLi(1, 0)) {};
	largeInt(largeInt& a) : largeInt(*(a.getNum())) {};
	largeInt(string&);
	~largeInt() { _num->clear(); delete _num; }

	numLi* getNum() { return _num; }
	void setNum(int);
	void setNum(unsigned int);
	void setNum(numLi&);
	void setNum(largeInt& a) { this->setNum(*(a.getNum())); }
	
	bool operator>(largeInt&);
	bool operator<(largeInt& a) { return a > *this; }
	bool operator==(largeInt&);
	bool operator>=(largeInt& a) { return (*this > a) || (*this == a); }
	bool operator!=(largeInt& a) { return !(*this == a); }

	void operator>>=(unsigned int);
	void operator<<=(unsigned int);

	void operator+=(largeInt&);
	void operator-=(largeInt& a) { *this += -a; };
	void operator%=(largeInt&);
	void operator/=(largeInt&);

	largeInt operator-();
	largeInt operator+(largeInt& a) { largeInt res(*_num); res += a; return res; }
	largeInt operator-(largeInt& a) { largeInt res(*_num); res -= a; return res; }
	largeInt operator*(largeInt& a) { largeInt res(*_num); res *= a; return res; }
	largeInt operator/(largeInt& a) { largeInt res(*_num); res /= a; return res; }
	largeInt operator%(largeInt& a) { largeInt res(*_num); res %= a; return res; }
	largeInt operator>>(unsigned int a) { largeInt res(*_num); res >>= a; return res; }
	largeInt operator<<(unsigned int a) { largeInt res(*_num); res <<= a; return res; }

	void operator+=(int a) { *this += largeInt(a); }
	void operator-=(int a) { *this += largeInt(-a); }
	largeInt operator+(int a) { return largeInt(*this) + largeInt(a); }
	largeInt operator-(int a) { return largeInt(*this) - largeInt(a); }
	largeInt operator*(int a) { return largeInt(*this) * largeInt(a); }
	bool operator>(int a) { return largeInt(*this) > largeInt(a); }
	bool operator>=(int a) { return largeInt(*this) > largeInt(a); }
	largeInt operator/(int a) { return largeInt(*this) / largeInt(a); }
	largeInt operator%(int a) { return largeInt(*this) % largeInt(a); }

	string getStrInt();
private:
	largeInt normal_mult(largeInt& a, largeInt& b); // this function is for multiplying with numbers that are no more than 4B
	largeInt karatsuba_mult(largeInt a, largeInt b); // used in * operator, a is make sure to be larger in size than b in the function
};