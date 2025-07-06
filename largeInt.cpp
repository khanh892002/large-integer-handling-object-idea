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

largeInt largeInt::operator+(largeInt& a) {
	largeInt res;
	vector<char> val;
	if (_isNeg xor a.getIsNeg()) {
		
	} else {
		res.setIsNeg(_isNeg);
	}
	return res;
}

largeInt largeInt::operator-(largeInt& a) {
	largeInt res;

	return res;
}

largeInt largeInt::operator*(largeInt& a) {
	largeInt res;
	
	return res;
}

bool largeInt::operator>(largeInt& a) {
	if (_isNeg xor a.getIsNeg()) return !_isNeg;

	vector<char>* rightVal = a.getNum();
	size_t sz = _num->size();
	if (sz > rightVal->size()) return !_isNeg;
	if (sz < rightVal->size()) return _isNeg;

	sz--;
	while (sz >= 0) {
		if ((*_num)[sz] > (*rightVal)[sz]) return !_isNeg;
		if ((*_num)[sz] < (*rightVal)[sz]) return _isNeg;
		sz--;
	}
	return false;
}

bool largeInt::operator==(largeInt& a) {
	if (_isNeg != a.getIsNeg()) return false;
	size_t sz = _num->size();
	vector<char>* otherVal = a.getNum();
	if (sz != otherVal->size()) return false;

	sz--;
	while (sz >= 0) {
		if ((*_num)[sz] != (*otherVal)[sz]) return false;
		sz--;
	}
	return true;
}

largeInt largeInt::operator/(largeInt& a) {
	largeInt res;
	
	return res;
}

largeInt largeInt::operator%(largeInt& a) {
	largeInt res;
	
	return res;
}