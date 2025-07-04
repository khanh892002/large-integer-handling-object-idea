#include "largeInt.h"
void inputing(vector<char>*& a, int val) {
	while (val) {
		a->push_back((char)(val & 0xFF));
		val >>= 8;
	}
}

largeInt::largeInt(int val) {
	if (val < 0) {
		_isNeg = true;
		val = -val;
	}
	_num = new vector<char>();
	inputing(_num, val);
}
largeInt::largeInt(unsigned int val) {
	_num = new vector<char>();
	inputing(_num, val);
}
largeInt::largeInt(vector<char>& a) {_num = new vector<char>(a);}

void largeInt::setNum(int val) {
	_num->clear();
	if (val < 0) {
		_isNeg = true;
		val = -val;
	}
	inputing(_num, val);
	_isNeg = false;
}
void largeInt::setNum(unsigned int val) {
	_num->clear();
	inputing(_num, val);
	_isNeg = false;
}
void largeInt::setNum(vector<char>& a) {
	_num->clear();
	for (char ch : a) _num->push_back(ch);
	_isNeg = false;
}

largeInt largeInt::operator+(largeInt a) {
	largeInt res;

	return res;
}

largeInt largeInt::operator-(largeInt a) {
	largeInt res;

	return res;
}

largeInt largeInt::operator*(largeInt a) {
	largeInt res;
	
	return res;
}

bool largeInt::operator>(largeInt a) {
	
}

bool largeInt::operator>=(largeInt a) {
	
}

largeInt largeInt::operator/(largeInt a) {
	largeInt res;
	
	return res;
}

largeInt largeInt::operator%(largeInt a) {
	largeInt res;
	
	return res;
}