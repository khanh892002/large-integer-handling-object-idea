#include "largeInt.h"

largeInt::largeInt(int val) {
	_num = new numLi();
	do {
		_num->push_back(val & 0xFF);
		val >>= 8;
	} while (val && ~val); // if val only have 1 kind of bit, the loop breaks
	if ((_num->back() ^ val) & 0x80) _num->push_back(val & 0xFF);
}
largeInt::largeInt(unsigned int val) {
	_num = new numLi();
	do {
		_num->push_back(val & 0xFF);
		val >>= 8;
	} while (val);
	if (_num->back() & 0x80) _num->push_back(0);
}
largeInt::largeInt(string& str) {
	_num = new numLi();
	size_t i = 0;
	while (str[i] != '\0') _num->push_back(str[i++]);
	if (_num->back() & 0x80) _num->push_back(0);
}

void largeInt::setNum(int val) {
	_num->clear();
	do {
		_num->push_back(val & 0xFF);
		val >>= 8;
	} while (val && ~val); // if val only have 1 kind of bit, the loop breaks
	if ((_num->back() ^ val) & 0x80) _num->push_back(val & 0xFF);
}
void largeInt::setNum(unsigned int val) {
	_num->clear();
	do {
		_num->push_back(val & 0xFF);
		val >>= 8;
	} while (val);
	if (_num->back() & 0x80) _num->push_back(0);
}
void largeInt::setNum(numLi& a) {
	if (a.size() == 0) { _num->assign(1, 0); return; }
	numItr j = --(a.end());
	while (j != a.begin() && !(*j && ~(*j))) {
		numItr i = j; i--;
		if ((*i ^ *j) & 0x80) break;
		j--;
	}
	_num->assign(a.begin(), ((j == a.begin()) ? ++j : j));
}
void largeInt::setNumWithStrNum(string& str) {
	strHelper num(str);
	// TODO
}

bool largeInt::operator>(largeInt& a) {
	numLi* otherVal = a.getNum();
	if ((_num->back() ^ otherVal->back()) & 0x80) return !(_num->back() & 0x80);

	size_t sz = _num->size();
	if (sz > otherVal->size()) return !(_num->back() & 0x80);
	if (sz < otherVal->size()) return (_num->back() & 0x80);
	numItr i = --(_num->end()), j = --(otherVal->end()), beg = _num->begin();
	while (i != beg) {
		if (*i > *j) return true;
		if (*i < *j) return false;
		i--; j--;
	}
	return (*i > *j);
}
bool largeInt::operator==(largeInt& a) {
	numLi* otherVal = a.getNum();
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
	// after this, if a >= 8 => _num->size = 1
	if (a >> 3) { *i = ((*i & 0x80) ? 0xFF : 0); return; }
	if (a == 0) return;
	i = _num->begin();
	numItr j = i; j++;
	char moveLeft = 8 - a;
	while (j != _num->end()) {
		*i = (*j << moveLeft) | (*i >> a);
		i = j; j++;
	}
	*i = (char)*i >> a;

	if ((_num->size() > 1) && (*i && ~*i) && !((*i ^ *(--i)) & 0x80))
		_num->pop_back();
}
void largeInt::operator<<=(unsigned int a) {
	char Nbits = a & 7;
	if (Nbits) {
		numItr i = --(_num->end());
		char temp = *i ^ (*i << 1);
		while (Nbits && !(temp & 0x80)) {
			temp <<= 1;
			Nbits--;
		}
		if (Nbits) _num->push_back((char)*i >> (8 - (a & 7)));
		Nbits = a & 7; temp = 8 - Nbits;
		*i <<= Nbits;
		if (i != _num->begin()) {
			numItr j = i; j--;
			while (j != _num->begin()) {
				*i |= (*j >> temp);
				*j <<= Nbits;
				i = j; j--;
			}
			*i |= (*j >> temp);
			*j <<= Nbits;
		}
	}
	a >>= 3;
	while (a) {
		_num->push_front(0);
		a--;
	}
}

void largeInt::operator+=(largeInt& a) {
	numLi* Aval = a.getNum();
	while (_num->size() < Aval->size())
		_num->push_back((_num->back() * 0x80) ? 0xFF : 0);
	numItr i(_num->begin()), i_end(_num->end()),
			j(Aval->begin()), j_end(Aval->end());
	short temp = 0;
	while (j != j_end) {
		temp += *i + *j;
		*i = temp;
		temp >>= 8;
		i++; j++;
	}
	while (i != i_end && temp) if (++(*i++)) temp = 0;
	
	i_end--;
	while ((i_end != _num->begin()) && !(*i_end && ~*i_end)) {
		i = i_end; i--;
		if ((*i ^ *i_end) & 0x80) break;
		i_end = i;
		_num->pop_back();
	}
}
void largeInt::operator%=(largeInt& a) {
	if (a == zero) return;
	bool isNeg = a < zero;
	if (isNeg) a.Neg();
	largeInt temp(a);
	if (*this < zero) {
		this->Neg();

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
	if (isNeg) a.Neg();
}
void largeInt::Neg() {
	for (numItr i(_num->begin()); i != _num->end(); i++)
		*i ^= 0xFF;
	*this += 1;
}

largeInt largeInt::operator*(largeInt& a) {
	char flip = 0;
	if (_num->back() & 0x80) {
		flip = 1;
		this->Neg();
	}
	if (a.getNum()->back() & 0x80) {
		flip |= 2;
		a.Neg();
	}
	largeInt res(multiply(*this, a));
	if ((flip & 1) ^ (flip >> 1)) res.Neg();
	if (flip & 1) this->Neg();
	if (flip & 2) a.Neg();
	return res;
}

largeInt largeInt::multiply(largeInt& a, largeInt& b) {
	// all number are assumed to be not negative
	if (*this == zero || a == zero) return zero;
	// use simple multiplication for small number
	if (_num->size() <= 4 && a.getNum()->size() <= 4) return normal_mult(*this, a);
	// Use Karatsuba algorithm for larger numbers
	return karatsuba_mult(*this, a);
}

largeInt largeInt::normal_mult(largeInt& a, largeInt& b) {
	// this function work with the assumption that a and b are not negative
	numLi* aNum = a.getNum(), *bNum = b.getNum();
	// Create result with enough space
	// It is provable that the result size is not larger than the sum of the numbers size
	numLi result(aNum->size() + bNum->size(), 0);
	
	// Simple schoolbook multiplication
	unsigned short carry = 0;
	size_t aPos = 0, bPos;
	
	for (numItr aIt = aNum->begin(); aIt != aNum->end(); ++aIt, ++aPos) {
		if (*aIt == 0) continue;

		carry = 0;
		bPos = 0;
		
		for (numItr bIt = bNum->begin(); bIt != bNum->end(); ++bIt, ++bPos) {
			unsigned short product = *aIt * *bIt + carry;
			
			// Add to existing result
			numItr resultIt = result.begin();
			advance(resultIt, aPos + bPos);
			product += *resultIt;
			
			*resultIt = product & 0xFF;
			carry = product >> 8;
		}
		
		// Handle remaining carry
		if (carry > 0) {
			numItr resultIt = result.begin();
			advance(resultIt, aPos + bPos);
			*resultIt = carry;
		}
	}
	
	// Remove unnecessary leading zeros
	while (result.size() > 1 && result.back() == 0) result.pop_back();
	if (result.back() & 0x80) result.push_back(0);
	return largeInt(result);
}

largeInt largeInt::karatsuba_mult(largeInt a, largeInt b) {
	numLi* aNum = a.getNum(), *bNum = b.getNum();
	
	size_t aSize = aNum->size(), bSize = bNum->size();
	
	if (aSize < bSize) {
		numLi* temp = aNum;
		aNum = bNum;
		bNum = temp;
	}
	if (aSize <= 4) return normal_mult(a, b);
	size_t split = aSize >> 1;
	
	// Split a into high and low parts
	numLi aHigh, aLow;
	numItr aIt = aNum->begin();
	for (size_t i = 0; i < split && aIt != aNum->end(); ++i, ++aIt)
		aLow.push_back(*aIt);
	if (aLow.back() & 0x80) aLow.push_back(0);
		while (aIt != aNum->end()) aHigh.push_back(*(aIt++));
	
	// Split b into high and low parts
	numLi bHigh, bLow;
	numItr bIt = bNum->begin();
	for (size_t i = 0; i < split && bIt != bNum->end(); ++i, ++bIt)
		bLow.push_back(*bIt);
	if (bLow.back() & 0x80) bLow.push_back(0);
	while (bIt != bNum->end()) bHigh.push_back(*(bIt++));
	
	// Create largeInt objects for the parts
	// the HighInts's nums may larger than the lowInt's ones by 1 byte
	largeInt aHighInt(aHigh), bHighInt(bHigh),
			 aLowInt(aLow), bLowInt(bLow);
	
	// Karatsuba's three recursive multiplications
	largeInt z0(karatsuba_mult(aLowInt, bLowInt)),
			 z2(karatsuba_mult(aHighInt, bHighInt));
	if (z0.getNum()->back() & 0x80) z0.getNum()->push_back(0);
	if (z2.getNum()->back() & 0x80) z2.getNum()->push_back(0);

	// z1 = a_high * b_low + a_low * b_high
	// = (a_high + a_low) * (b_high + b_low) - z0 - z2
	largeInt z1(aHighInt); z1 += aLowInt;
	z1.setNum(karatsuba_mult(z1, bHighInt + bLowInt));
	z1 -= z0; z1 -= z2;
	
	// Combine results: z2 * 2^(2*split) + z1 * 2^split + z0
	// recycling aNum
	aNum = z0.getNum();
	while (aNum->size() < split) aNum->push_back(0);
	while (aNum->size() > split) aNum->pop_back();
	aNum->splice(aNum->end(), *(z2.getNum()));
	// z0 is now (z2 << (2 split)) | z0)
	z1 <<= (split << 3); // split * 8
	z0 += z1;
	
	return z0;
}
largeInt largeInt::operator/(largeInt& a) {
	if (a == zero) throw runtime_error("Divided by 0");
	
	largeInt divided(*_num), dividing, result;
	char flip = 0;
	if (_num->back() & 0x80) {
		flip = 1;
		divided.Neg();
	}
	if (a.getNum()->back() & 0x80) {
		flip |= 2;
		a.Neg();
		dividing.setNum(a);
	}

	if (divided.getNum()->size() > dividing.getNum()->size())
		dividing <<= ((divided.getNum()->size() - dividing.getNum()->size()) << 3);
	while (divided >= dividing) dividing <<= 1;
	while (divided < dividing) dividing >>= 1;
	while (divided >= a) {
		divided -= dividing;
		result += 1;
		if (divided < a) break;
		while (divided < dividing) {
			result <<= 1;
			dividing >>= 1;
		}
	}

	if (flip & 2) a.Neg();
	if ((flip & 1) ^ (flip >> 1)) result.Neg();
	return result;
}

largeInt::strHelper::strHelper(string& str) {
	if (str.size() == 0) throw runtime_error("largeInt::strHelper construct failed: empty string");
	string::iterator i = str.begin(); if (*i == '-') i++;
	while (i != str.end()) {
		if ((*i < '0') || (*i > '9')) throw runtime_error("largeInt::strHelper construct failed: Not a numeric string input");
		i++;
	}
	_num = str;
}

void largeInt::strHelper::operator+=(largeInt::strHelper& a) {
	string aNum = a.getNum();
	size_t numI(_num.size() - 1), aI(aNum.size() - 1);
	bool carry = false;
	while (~numI && ~aI) {
		_num[numI] &= 0xF; _num[numI] += (aNum[aI] & 0xF);
		if (carry) _num[numI]++;
		carry = _num[numI] > 9;
		if (carry) _num[numI] -= 10;
		_num[numI] |= 0x30;
		numI--; aI--;
	}
	// either numI or aI is 0xFFFFFF... now
	if (carry) {
		while (~numI && (_num[numI] == '9')) _num[numI--] = '0';
		if (~numI) _num[numI]++;
		else if (~aI) {
			while (~aI && (aNum[aI] == '9')) _num = '0' + _num;
			if (~aI) {
				_num = char(aNum[aI--] + 1) + _num;
				while (~aI) _num = aNum[aI--] + _num;
			}
			else _num = '1' + _num;
		}
		else _num = '1' + _num;
	} else
		while (~aI) _num = aNum[aI--] + _num;
}
void largeInt::strHelper::doubleUp() {
	size_t i = _num.size() - 1;
	bool carry = false;
	while (~i) {
		_num[i] &= 0xF; _num[i] <<= 1;
		if (carry) _num[i]++;
		carry = _num[i] > 9;
		if (carry) _num[i] -= 10;
		_num[i] |= 0x30;
		i--;
	}
	if (carry) _num = '1' + _num;
}

string largeInt::getStrInt() {
	bool isNeg = _num->back() & 0x80;
	if (isNeg) this->Neg();
	
	strHelper result, pow2(1);
	for (numItr i(_num->begin()); i != _num->end(); i++)
		for (char bit = 1; bit; bit <<= 1) {
			if (bit & *i) result += pow2;
			pow2.doubleUp();
		}

	string res = result.getNum();
	if (isNeg) {
		this->Neg();
		res = '-' + res;
	}
	return res;
}