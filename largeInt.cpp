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
	numItr j = a.end();
	while (j != a.begin() && !(*j && ~(*j))) {
		numItr i = j; i--;
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
	numItr i = _num->end(), j = otherVal->end(), beg = _num->begin();
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
	numItr i = _num->begin(), j = otherVal->begin(),
	end = _num->end();
	while (i != end) {
		if (*i != *j) return false;
		i++; j++;
	}
	return true;
}

void largeInt::operator+=(largeInt& a) {
	vector<char>* Aval = a.getNum();
	while (_num->size() < Aval->size())
		_num->push_back(_num->back() >> 7);
	numItr i(_num->begin()), i_end(_num->end()),
			j(Aval->begin()), j_end(Aval->end());
	short temp = 0;
	while (j != j_end) {
		temp += (*i & 0xFF) + (*j & 0xFF);
		*i = temp & 0xFF;
		temp >>= 8;
		i++; j++;
	}
	while (i != i_end && temp) {
		if (++(*i)) temp = 0;
		i++;
	}
	i_end--;
	while ((i_end != _num->begin()) && !(*i_end && ~*i_end)) {
		i = i_end; i--;
		if ((*i ^ *i_end) & 0x80) break;
		i_end = i;
		_num->pop_back();
	}
}
void largeInt::operator-=(largeInt& a) { *this += -a; }

largeInt largeInt::operator-() {
	vector<char> res(*_num);
	numItr i = res.begin();
	while (i != res.end()) {
		*i = ~*i;
		i++;
	}
	return largeInt(res) + 1;
	// this create another largeInt for 1, hopefully a good approach
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
	vector<char> res;
	
	return largeInt(res);
}
largeInt largeInt::operator/(largeInt& a) {
	largeInt res;
	
	return res;
}
largeInt largeInt::operator%(largeInt& a) {
	largeInt res;
	
	return res;
}