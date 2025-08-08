#include "largeInt.h"

largeInt::largeInt(int val) {
	_num = new list<char>();
	do {
		_num->push_back((unsigned char)(val & 0xFF));
		val >>= 8;
	} while (val && ~val); // if val only have 1 kind of bit, the loop breaks
	if ((_num->back() ^ val) & 0x80) _num->push_back(val & 0xFF);
}
largeInt::largeInt(unsigned int val) {
	_num = new list<char>();
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
void largeInt::setNum(list<char>& a) {
	numItr j = --(a.end());
	while (j != a.begin() && !(*j && ~(*j))) {
		numItr i = j; i--;
		if ((*i ^ *j) & 0x80) break;
		j--;
	}
	_num->assign(a.begin(), ((j == a.begin()) ? ++j : j));
}

bool largeInt::operator>(largeInt& a) {
	list<char>* otherVal = a.getNum();
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
	list<char>* otherVal = a.getNum();
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

void largeInt::operator>>=(unsigned int a) {
	numItr i = _num->end(); i--;
	while ((a >> 3) && (i != _num->begin())) {
		_num->pop_front();
		a -= 8;
	}
	// after this, if a > 8 => _num->size = 1
	if (a > 8) { *i >>= 7; return; }
	i = _num->begin();
	numItr j = i; j++;
	char moveLeft = 8 - a;
	while (j != _num->end()) {
		*i = (*j << moveLeft) | ((unsigned char)(*i) >> a);
		i = j; j++;
	}
	*i >>= a;
	if ((_num->size() > 1) && (*i && ~*i) && !((*i ^ *(--i)) & 0x80))
		_num->pop_back();
}
void largeInt::operator<<=(unsigned int a) {
	char Nbits = a & 7;
	numItr i = --(_num->end());
	char temp = *i ^ (*i << 1);
	while (Nbits && !(temp & 0x80)) {
		temp <<= 1;
		Nbits--;
	}
	if (Nbits) _num->push_back(*i >> (8 - (a & 7)));
	Nbits = a & 7; temp = 8 - Nbits;
	if (i == _num->begin()) *i <<= Nbits;
	else {
		numItr j = i; j--;
		while (j != _num->begin()) {
			*i = (*i << Nbits) | ((unsigned char)(*j) >> temp);
			i = j; j--;
		}
		*j <<= Nbits;
	}
	a >>= 3;
	while (a) {
		_num->push_front(0);
		a--;
	}
}

void largeInt::operator+=(largeInt& a) {
	list<char>* Aval = a.getNum();
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
void largeInt::operator%=(largeInt& a) {
	if (a == zero) return;
	bool isNeg = a < zero;
	if (isNeg) {
		for (numItr i = a.getNum()->begin(); i != a.getNum()->end(); i++)
			*i = ~*i;
		a += 1;
	}
	largeInt temp(a);
	if (*this < zero) {
		for (numItr i = _num->begin(); i != _num->end(); i++)
			*i = ~*i;
		*this += 1;

		while (temp < *this) temp <<= 1;
		temp -= *this;
		this->setNum(*(temp.getNum()));
	}
	temp.setNum(a);
	while (temp < *this) temp <<= 1;
	while (*this >= a) {
		while (temp > *this) temp >>= 1;
		*this -= temp;
	}
	if (isNeg) {
		for (numItr i = a.getNum()->begin(); i != a.getNum()->end(); i++)
			*i = ~*i;
		a += 1;
	}
}

largeInt largeInt::operator-() {
	largeInt res(*_num);
	numItr i_end = res.getNum()->end();
	for (numItr i = res.getNum()->begin(); i != i_end; i++)
		*i = ~*i;
	res += 1;
	return res;
}
largeInt largeInt::operator+(largeInt& a) {
	largeInt res(*_num);
	res += a;
	return res;
}
largeInt largeInt::operator-(largeInt& a) {
	largeInt res(*_num);
	res -= a;
	return res;
}
largeInt largeInt::operator*(largeInt& a) {
	if (*this == zero || a == zero) return zero;
	// use simple multiplication for small number
	if (_num->size() <= 4 && a.getNum()->size() <= 4) return karatsuba_simple(*this, a);
	// Use Karatsuba algorithm for larger numbers
	return karatsuba_multiply(*this, a);
}

largeInt largeInt::karatsuba_simple(largeInt& a, largeInt& b) {
	list<char>* aNum = a.getNum(), *bNum = b.getNum();
	// Create result with enough space
	list<char> result(aNum->size() + bNum->size(), 0);
	
	// Simple schoolbook multiplication
	int carry = 0, aPos = 0;
	
	for (numItr aIt = aNum->begin(); aIt != aNum->end(); ++aIt, ++aPos) {
		carry = 0;
		int bPos = 0;
		
		for (numItr bIt = bNum->begin(); bIt != bNum->end(); ++bIt, ++bPos) {
			int product = *aIt * *bIt + carry;
			
			// Add to existing result
			auto resultIt = result.begin();
			advance(resultIt, aPos + bPos);
			product += *resultIt;
			
			*resultIt = product & 0xFF;
			carry = product >> 8;
		}
		
		// Handle remaining carry
		if (carry > 0) {
			auto resultIt = result.begin();
			advance(resultIt, aPos + bPos);
			*resultIt = carry;
		}
	}
	
	// Remove leading zeros
	while (result.size() > 1 && result.back() == 0) {
		result.pop_back();
	}
	
	return largeInt(result);
}

largeInt largeInt::karatsuba_multiply(largeInt& a, largeInt& b) {
	list<char>* aNum = a.getNum(), *bNum = b.getNum();
	
	size_t aSize = aNum->size(), bSize = bNum->size();
	
	if (aSize < bSize) return karatsuba_multiply(b, a);
	if (aSize <= 4) return karatsuba_simple(a, b);
	size_t split = aSize >> 1;
	
	// Split a into high and low parts
	list<char> aHigh, aLow;
	numItr aIt = aNum->begin();
	for (size_t i = 0; i < split && aIt != aNum->end(); ++i, ++aIt) {
		aLow.push_back(*aIt);
	}
	while (aIt != aNum->end()) {
		aHigh.push_back(*aIt);
		aIt++;
	}
	
	// Split b into high and low parts
	list<char> bHigh, bLow;
	auto bIt = bNum->begin();
	for (size_t i = 0; i < split && bIt != bNum->end(); ++i, ++bIt) {
		bLow.push_back(*bIt);
	}
	for (; bIt != bNum->end(); ++bIt) {
		bHigh.push_back(*bIt);
	}
	
	// Create largeInt objects for the parts
	largeInt aHighInt(aHigh);
	largeInt aLowInt(aLow);
	largeInt bHighInt(bHigh);
	largeInt bLowInt(bLow);
	
	// Karatsuba's three recursive multiplications
	largeInt z0(aLowInt * bLowInt);
	largeInt z2(aHighInt * bHighInt);
	
	// (a_high + a_low) * (b_high + b_low) - z0 - z2
	largeInt sumA(aHighInt + aLowInt);
	largeInt sumB(bHighInt + bLowInt);
	largeInt z1(sumA * sumB - z0 - z2);
	
	// Combine results: z2 * 2^(2*split) + z1 * 2^split + z0
	largeInt result(z0);
	
	// Add z1 * 2^split
	largeInt z1Shifted(z1);
	z1Shifted <<= (split << 3);
	result += z1Shifted;
	
	// Add z2 * 2^(2*split)
	largeInt z2Shifted(z2);
	z2Shifted <<= (2 * split * 8);
	result += z2Shifted;
	
	return result;
}
largeInt largeInt::operator/(largeInt& a) {
	largeInt res;
	
	return res;
}
largeInt largeInt::operator%(largeInt& a) {
	largeInt res(*_num);
	res %= a;
	return res;
}