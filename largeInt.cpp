#include "largeInt.h"
void inputing(vector<unsigned char>*& a, int val) {
	//val is not negative at this point
	while (val) {
		a->push_back((unsigned char)(val & 0xFF));
		val >>= 8;
	}
}

largeInt::largeInt(int val) {
	if (val < 0) {
		_isNeg = true;
		val = -val;
	}
	_num = new vector<unsigned char>();
	inputing(_num, val);
}
largeInt::largeInt(unsigned int val) {
	_num = new vector<unsigned char>();
	inputing(_num, val);
}
largeInt::largeInt(vector<unsigned char>& a) {
	_isNeg = false;
	_num = new vector<unsigned char>(a);
	while (!_num->back()) _num->pop_back();
}

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
void largeInt::setNum(vector<unsigned char>& a) {
	_isNeg = false;
	_num->assign(a.begin(), a.end());
	while (!_num->back()) _num->pop_back();
}

bool largeInt::operator>(largeInt& a) {
	if (_isNeg ^ a.getIsNeg()) return !_isNeg;

	vector<unsigned char>* rightVal = a.getNum();
	size_t sz = _num->size();
	if (sz > rightVal->size()) return !_isNeg;
	if (sz < rightVal->size()) return _isNeg;
	if (!sz) return false;
	sz--;
	while (sz >= 0) {
		if (_num->at(sz) > rightVal->at(sz)) return !_isNeg;
		if (_num->at(sz) < rightVal->at(sz)) return _isNeg;
		sz--;
	}
	return false;
}
bool largeInt::operator==(largeInt& a) {
	if (_isNeg != a.getIsNeg()) return false;
	size_t sz = _num->size();
	vector<unsigned char>* otherVal = a.getNum();
	if (sz != otherVal->size()) return false;
	if (!sz) return true;
	sz--;
	while (sz >= 0) {
		if (_num->at(sz) != otherVal->at(sz)) return false;
		sz--;
	}
	return true;
}

void largeInt::operator+=(largeInt& a) {
	vector<unsigned char>* Aval = a.getNum();
	if (Aval->size()) {
		if (_isNeg ^ a.getIsNeg()) {

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

}

largeInt largeInt::operator+(largeInt& a) {
	largeInt res(*_num);
	res.setIsNeg(_isNeg);
	res += a;
	return res;
}
largeInt largeInt::operator-(largeInt& a) {
	largeInt res(*_num);
	res.setIsNeg(_isNeg);
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