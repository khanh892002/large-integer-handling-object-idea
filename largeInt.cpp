#include "largeInt.h"
void inputing(vector<char>*& a, int val) {
	
}

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
	vector<unsigned char>* Aval = a.getNum();
	if (Aval->size()) {
		if (_isNeg ^ a.getIsNeg()) {
			// |_num| < |a|: flip sign, switch _num and a, subtract a
			// |_num| > |a|: not need to flip sign, just subtract a
			// |_num| = |a|: subtract a, switch sign of _num if isNeg is true ???
			if (_num->size() > Aval->size()) {
				
			} else if (_num->size() < Aval->size()){

			} else {
				size_t sz = _num->size();
				
			}
		} else {
			short temp = 0;
			size_t i = 0;
			while (i < Aval->size() && i < _num->size()) {
				temp += _num->at(i) + Aval->at(i);
				_num->at(i) = temp;
				temp >>= 8;
				i++;
			}
			while (i < Aval->size()) {
				temp += Aval->at(i);
				_num->push_back(temp);
				temp >>= 8;
				i++;
			}
			while (i < _num->size() && temp) {
				temp += _num->at(i);
				_num->at(i) = temp;
				temp >>= 8;
				i++;
			}
			if (temp) _num->push_back(1);
		}
	}
}
void largeInt::operator-=(largeInt& a) {
	a.setIsNeg(!(a.getIsNeg()));
	*this += a;
	a.setIsNeg(!(a.getIsNeg()));
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