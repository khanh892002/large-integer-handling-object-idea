#include "largeInt.h"

largeInt::largeInt(string a) {
	int i = a[0] == '-';
	if (i) num = "-";
	while (a[i] == '0') i++;
	if (a[i] == '\0') num = "0";
	else
		while (a[i] != '\0') {
			if (a[i] > '9' || a[i] < '0') {
				cout << a << " khong phai la so nguyen";
				num = "0";
				break;
			}
			else num += a[i];
			i++;
		}
}

largeInt largeInt::operator+(largeInt a) {
	string result = "";
	bool neg1 = num[0] == '-', neg2 = a.num[0] == '-';
	int size1 = neg1, size2 = neg2;//will be number of digit
	string bigger = "", smaller = "";//will be identified later based on absolute value
	while (num[size1] != '\0') bigger += num[size1++];
	while (a.num[size2] != '\0') smaller += a.num[size2++];
	size1 -= neg1, size2 -= neg2;
	if (size1 == size2) {
		int i = 0;
		while (i < size1 && bigger[i] == smaller[i]) i++;
		if (i < size1 && bigger[i] < smaller[i]) {
			string a = &bigger[0];
			bigger = smaller;
			smaller = a;
			if (neg1 != neg2) {
				neg1 = neg2;
				neg2 = !neg1;
			}
		}
	}
	else if (size1 < size2) {
		int temp = size1;
		size1 = size2;
		size2 = temp;
		string a = &bigger[0];
		bigger = smaller;
		smaller = a;
		if (neg1 != neg2) {
			neg1 = neg2;
			neg2 = !neg1;
		}
	}

	if (neg1 == neg2) {
		bool nho = false;
		for (int i = 1; i <= size2; i++) {
			int sum = bigger[size1 - i] + smaller[size2 - i] - 96 + nho;
			nho = sum > 9;
			result = (char)(sum % 10 + 48) + result;
		}
		for (int i = size1 - size2 - 1; i >= 0; i--) {
			int sum = bigger[i] - 48 + nho;
			nho = sum > 9;
			result = (char)(sum % 10 + 48) + result;
		}
		if (nho) result = '1' + result;
	}
	else {
		bool nho = false;
		for (int i = 1; i <= size2; i++) {
			int sub = bigger[size1 - i] - smaller[size2 - i] - nho;
			nho = sub < 0;
			result = (char)(sub + 10 * nho + 48) + result;
		}
		for (int i = size1 - size2 - 1; i >= 0; i--) {
			int sub = bigger[i] - 48 - nho;
			nho = sub < 0;
			result = (char)(sub + 10 * nho + 48) + result;
		}
	}
	int i = 0;
	while (result[i] == 0) i++;
	if (i != 0) result = &result[i];
	if (neg1) result = '-' + result;
	return largeInt(result);
}

largeInt largeInt::operator-(largeInt a) {
	string negnum = a.getNum();
	if (negnum[0] == '-') negnum = &negnum[1];
	else negnum = '-' + negnum;
	a.setNum(negnum);
	return *this + a;
}

largeInt largeInt::operator*(largeInt a) {
	string anum = a.getNum();
	bool neg1 = num[0] == '-', neg2 = anum[0] == '-';
	int size1 = neg1, size2 = neg2;
	while (num[size1] != '\0') size1++;
	while (anum[size2] != '\0') size2++;
	size1 -= neg1, size2 -= neg2;
	if (size1 == 1 && size2 == 1) {
		stringstream ss;
		ss << (num[neg1] - 48) * (anum[neg2] - 48);
		return largeInt(((neg1 == neg2) ? "" : "-") + ss.str());
	}

	int size = (size1 > size2) ? size1 : size2;
	int halfSize = size - (size >> 1);
	string num1L = "", num1R = "", num2L = "", num2R = "";
	for (int i = 0; i < size1 - halfSize; i++) num1L += num[i + neg1];
	for (int i = 0; i < size2 - halfSize; i++) num2L += anum[i + neg2];
	if (num1L == "") num1L = "0";
	if (num2L == "") num2L = "0";

	if (size1 > halfSize) num1R = &num[size1 - halfSize + neg1];
	else num1R = &num[neg1];
	if (size2 > halfSize) num2R = &anum[size2 - halfSize + neg2];
	else num2R = &anum[neg2];

	largeInt NUM1L(num1L), NUM1R(num1R), NUM2L(num2L), NUM2R(num2R);

	largeInt b = NUM1L * NUM2L, c = NUM1R * NUM2R;
	string d = ((NUM1L + NUM1R) * (NUM2L + NUM2R) - (b + c)).getNum();
	for (int i = 0; i < halfSize; i++) d += '0';

	string preResult = c.getNum();
	halfSize = halfSize << 1;
	for (int i = preResult.size(); i < halfSize; i++) preResult = '0' + preResult;
	preResult = b.getNum() + preResult;
	string result = (largeInt(preResult) + largeInt(d)).getNum();
	if (neg1 != neg2 && result != "0") result = '-' + result;
	return largeInt(result);
}

bool largeInt::operator>(largeInt a) {
	string anum = a.getNum();
	bool neg1 = num[0] == '-', neg2 = anum[0] == '-';
	int size1 = num.size() - neg1, size2 = anum.size() - neg2;
	if (size1 > size2) return !neg1;
	if (size1 < size2) return neg2;

	int i = 0;
	while (num[i + neg1] != '\0' && num[i + neg1] == anum[i + neg2]) i++;
	if (i == size1) return !neg1 && neg2;
	if (num[i + neg1] > anum[i + neg2]) return !neg1;
	else return neg2;
}

bool largeInt::operator>=(largeInt a) {
	string anum = a.getNum();
	bool neg1 = num[0] == '-', neg2 = anum[0] == '-';
	int size1 = num.size() - neg1, size2 = anum.size() - neg2;
	if (size1 > size2) return !neg1;
	if (size1 < size2) return neg2;

	int i = 0;
	while (num[i + neg1] != '\0' && num[i + neg1] == anum[i + neg2]) i++;
	if (i == size1) return neg1 == neg2;
	if (num[i + neg1] > anum[i + neg2]) return !neg1;
	else return neg2;
}

largeInt largeInt::operator/(largeInt a) {
	string anum = a.getNum();
	bool neg1 = num[0] == '-', neg2 = anum[0] == '-';
	largeInt divided(&num[neg1]), divisor(&anum[neg2]);
	int size1 = num.size() - neg1, size2 = anum.size() - neg2;
	largeInt result;
	while (divided >= divisor) {
		int size = size2, sizeBiChia = divided.getNum().size();
		largeInt zeros("1");
		for (int i = size2; i < sizeBiChia; i++) zeros = zeros * 10;
		string biChia = "", soBiChia = divided.getNum();
		for (int i = 0; i < size2; i++) biChia += soBiChia[i];

		if (divisor > largeInt(biChia)) {
			zeros = zeros / 10;
			biChia += soBiChia[size++];
		}
		largeInt BiChia(biChia);
		int count = 0;
		while (BiChia >= divisor) {
			BiChia = BiChia - divisor;
			count++;
		}
		result = result + (zeros * count);
		divided = largeInt(BiChia.getNum() + &soBiChia[size]);
	}
	if (neg1 != neg2) result.setNum('-' + result.getNum());
	return result;
}

largeInt largeInt::operator%(largeInt a) {
	string anum = a.getNum();
	bool neg1 = num[0] == '-', neg2 = anum[0] == '-';
	largeInt divided(&num[neg1]), divisor(&anum[neg2]);
	int size1 = num.size() - neg1, size2 = anum.size() - neg2;

	while (divided >= divisor) {
		int size = size2;
		string biChia = "", soBiChia = divided.getNum();
		for (int i = 0; i < size2; i++) biChia += soBiChia[i];
		if (divisor > largeInt(biChia)) biChia += soBiChia[size++];
		largeInt BiChia(biChia);
		while (BiChia >= divisor) BiChia = BiChia - divisor;
		divided = largeInt(BiChia.getNum() + &soBiChia[size]);
	}
	if (neg1) divided = divisor - divided;

	return divided;
}

void largeInt::setNum(string newNum) {
	int i = newNum[0] == '-';
	while (newNum[i] == '0') i++;
	string _newNum = "";
	while (newNum[i] != '\0' && newNum[i] >= '0' && newNum[i] <= '9') {
		_newNum += newNum[i];
		i++;
	}
	if (newNum[i] == '\0') {
		if (_newNum == "") num = "0";
		else {
			num = (newNum[0] == '-') ? "-" : "";
			num += _newNum;
		}
	}
	else
		cout << newNum << " khong phai la so nguyen.\n";
}