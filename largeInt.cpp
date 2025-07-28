#include "largeInt.h"

largeInt::largeInt(int val) {
	_num = new vector<char>();
	do {
		_num->push_back((unsigned char)(val & 0xFF));
		val >>= 8;
	} while (val && ~val); // if val only have 1 kind of bit, the loop breaks
	if ((_num->back() ^ val) & 0x80) _num->push_back(val & 0xFF);
}
largeInt::largeInt(unsigned int val) {
	_num = new vector<char>();
	do {
		_num->push_back((unsigned char)(val & 0xFF));
		val >>= 8;
	} while (val);
	if (_num->back() & 0x80) _num->push_back(0);
}

void largeInt::setNum(int val) {
	_num->clear();
	do {
		_num->push_back((unsigned char)(val & 0xFF));
		val >>= 8;
	} while (val && ~val); // if val only have 1 kind of bit, the loop breaks
	if ((_num->back() ^ val) & 0x80) _num->push_back(val & 0xFF);
}
void largeInt::setNum(unsigned int val) {
	_num->clear();
	do {
		_num->push_back((unsigned char)(val & 0xFF));
		val >>= 8;
	} while (val);
	if (_num->back() & 0x80) _num->push_back(0);
}
void largeInt::setNum(vector<char>& a) {
	vector<char>::iterator j = a.end();
	while (j != a.begin() && !(*j && ~(*j))) {
		vector<char>::iterator i = j; i--;
		if ((*i ^ *j) & 0x80) break;
		j--;
	}
	_num->assign(a.begin(), j);
}

bool largeInt::operator>(largeInt& a) {
	vector<char>* otherVal = a.getNum();
	if ((_num->back() ^ otherVal->back()) & 0x80) return !(_num->back() & 0x80);

	size_t sz = _num->size();
	if (sz > otherVal->size()) return !(_num->back() & 0x80);
	if (sz < otherVal->size()) return (_num->back() & 0x80);
	vector<char>::iterator i = _num->end(), j = otherVal->end(), beg = _num->begin();
	i--; j--;
	while (i != beg) {
		if (*i > *j) return true;
		if (*i < *j) return false;
		i--; j--;
	}
	return (*i > *j);
}
bool largeInt::operator==(largeInt& a) {
	vector<char>* otherVal = a.getNum();
	size_t sz = _num->size();
	if (sz != otherVal->size()) return false;
	vector<char>::iterator i = _num->begin(), j = otherVal->begin(),
	end = _num->end();
	while (i != end) {
		if (*i != *j) return false;
		i++; j++;
	}
	return true;
}


void largeInt::operator+=(largeInt& a) {
	vector<char>* Aval = a.getNum();
	vector<char>::iterator i(_num->begin()), i_end(_num->end()),
						j(Aval->begin()), j_end(Aval->end());
	short temp = 0;
	while (i != i_end && j != j_end) {
		temp += (*i & 0xFF) + (*j & 0xFF);
		*i = temp & 0xFF;
		temp >>= 8;
		i++; j++;
	}
	// this still more work on what actually need to be handled
	// if _num is positive, if _num is negative
	// if both the numbers are positive, it would've been easy
	// when both numbers are negative, is it handled similar to the positive case
	// and when the signs are not the same
	while (i != i_end && temp) {
		if (++*i) temp = 0;
		i++;
	}
	while (j != j_end) {

	}
}
void largeInt::operator-=(largeInt& a) {
	
}

largeInt largeInt::operator+(largeInt& a) {
	largeInt res(*this);
	res += a;
	return res;
}
largeInt largeInt::operator-(largeInt& a) {
	largeInt res(*this);
	res -= a;
	return res;
}
largeInt largeInt::operator*(largeInt& a) {
	largeInt res;
	
	return res;
}
largeInt largeInt::operator/(largeInt& a) {
	largeInt res;
	
	return res;
}
largeInt largeInt::operator%(largeInt& a) {
	largeInt res;
	
	return res;
}