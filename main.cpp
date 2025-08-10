#include "largeInt.h"
#include <vector>

largeInt N, phiN, e, d, one(1);

bool inUsedList(vector<largeInt>& list, largeInt& a) {
	int size = list.size();
	for (int i = 0; i < size; i++)
		if (a == list[i])
			return true;

	return false;
}

largeInt random(largeInt& a) {
	// assume a is positive
	// this function return a random number smaller than a
	largeInt result;
	list<char>* num = a.getNum(), *res = result.getNum();
	size_t sz = (rand() % num->size()) + 1;
	int temp;
	while (sz >> 2) {
		temp = rand();
		res->push_back(temp & 0xFF); temp >>= 8;
		res->push_back(temp & 0xFF); temp >>= 8;
		res->push_back(temp & 0xFF); temp >>= 8;
		res->push_back(temp & 0xFF);
		sz -= 4;
	}
	temp = rand();
	while (sz) {
		res->push_back(temp & 0xFF);
		temp >>= 8;
		sz--;
	}
	if (!((*(--(--res->end()))) & 0x80)) res->pop_back();
	// if num is 00000000 0...
	result %= a;
	return result;
}

bool FermatTest(largeInt n, int k) {
	largeInt mu(n - 1);
	list<char>* muLi = mu.getNum();
	vector<largeInt> usedNums;
	int count = 0;
	while (count < k) {
		largeInt a;
		do {
			a.setNum(*(random(n - 3).getNum()));
			a += 2;
		} while (inUsedList(usedNums, a));
		usedNums.push_back(a);

		largeInt power(1);
		numItr i = --(muLi->end());
		while (i != muLi->begin()) {
			for (unsigned char bit(0x80); bit; bit>>=1)
				power.setNum(*(
					(((*i & bit) ? power * power * a : power * power) % n)
					.getNum()
				));
			i--;
		}
		for (unsigned char bit(0x80); bit; bit>>=1)
			power.setNum(*(
				(((*i & bit) ? power * power * a : power * power) % n)
				.getNum()
			));
		if (power != one) return false;
		count++;
	}

	return true;
}

int decompose(largeInt a) {
	string anum = a.getNum();
	int size = anum.size();
	int count = 0;
	while ((anum[size - 1] & 1) == 0) {
		a = a / 2;
		anum = a.getNum();
		size = anum.size();
		count++;
	}
	return count;
}

largeInt powerMod(largeInt& a, largeInt& b, largeInt& n) {
	largeInt result(1);
	list<char>* bNum = b.getNum();
	numItr i = --(bNum->end());
	while (i != bNum->begin()) {
		for (unsigned char bit(0x80); bit; bit>>=1)
			result.setNum(*(
				(((*i & bit) ? result * result * a : result * result) % n)
				.getNum()
			));
		i--;
	}
	for (unsigned char bit(0x80); bit; bit>>=1)
		result.setNum(*(
			(((*i & bit) ? result * result * a : result * result) % n)
			.getNum()
		));
	return result;
}

bool Witness(largeInt a, largeInt n) {
	int twos = decompose(n - 1);
	largeInt mu(n - 1);
	for (int i = 0; i < twos; i++)
		mu = mu / 2;
	a = powerMod(a, mu, n);
	if (a.getNum() == "1") return true;
	vector<largeInt> B;
	B.push_back(a);
	int i = 0;
	do {
		B.push_back((B[i] * B[i]) % n);
		i++;
		if (B[i].getNum() == "1")
			if (B[i - 1].getNum() == (n - 1).getNum())
				return true;
			else return false;
	} while (i < twos);
	return false;
}

largeInt gcd(largeInt a, largeInt b) {
	while ((a != zero) && (b != zero))
		if (a > b) a %= b;
		else b %= a;
	a += b;
	return a;
}

bool MillerRabinTest(largeInt n, int k) {
	largeInt a;
	vector<largeInt> arr;
	int i = 0;
	while (i < k) {
		do {
			a.setNum(*(random(n - 2).getNum()));
			a = a + 2;
		} while (inUsedList(arr, a));
		arr.push_back(a);
		if (gcd(a, n) != one) return false;
		else if (powerMod(a, n - 1, n) != one) return false;
		else return Witness(a, n);
		i++;
	}
	return true;
}

largeInt nghichDao(largeInt& a, largeInt& p) {
	// assume gcd(a, n) = 1
	vector<largeInt> arr;
	largeInt a1(a), p1(p);
	while (a1 != one) {
		arr.push_back(-(p1 / a1));
		largeInt temp(p1 % a1);
		p1.setNum(a1);
		a1.setNum(temp);
	}
	int i = arr.size() - 1;
	largeInt m(1), n(arr[i]);
	i--;
	while (i >= 0) {
		largeInt temp1(n), temp2(m + (n * arr[i]));
		m.setNum(temp1);
		n.setNum(temp2);
		i--;
	}
	return n % p;
}

int menu() {
	bool cinFail = true;
	int choice;
	do {
		system("cls");
		cout << "================ MENU ================\n"
			<< "\tN = " << N.getStrInt() << '\n'
			<< "\te = " << e.getStrInt() << '\n'
			<< "1. Nhap khoa.\n"
			<< "2. Sinh khoa tu dong.\n"
			<< "3. Ma hoa.\n"
			<< "4. Giai ma.\n"
			<< "5. Ket Thuc.\n"
			<< "=========> Lua chon cua ban: ";
		cin >> choice;
		cinFail = cin.fail();
		if (cinFail) {
			cout << "Ban da nhap sai kieu du lieu.\n";
			system("pause");
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (choice < 1 || choice > 5) {
			cinFail = true;
			cout << "Khong co lua chon phu hop.\n";
			system("pause");
		}
		cin.clear();
		cin.ignore();
	} while (cinFail);
	return choice;
}

bool checkInt(string str) {
	int i = str[0] == '-';
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9') i++;
	return str[i] == '\0';
}

bool operator==(string& a, string& b) {
	int sizea = a.size(), sizeb = b.size();
	if (a != b) return false;
	for (int i = 0; i < sizea; i++)
		if (a[i] != b[i]) return false;
	return true;
}

void nhapKhoa() {
	string p, q, exp;
	cout << "Nhap 2 so nguyen to p va q:\n";
	cout << "Nhap p: p = ";
	bool isInt = true, isPrime = true;
	do {
		getline(cin, p);
		isInt = checkInt(p);
		isPrime = isInt && FermatTest(largeInt(p), 100);
		if (!isInt) {
			cout << "Ban da nhap sai, moi nhap lai: p = ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (!isPrime) cout << "So vua nhap khong nguyen to, moi nhap lai: p = ";
	} while (!isInt || !isPrime);
	cout << "Nhap q: q = ";
	bool bangP = true;
	do {
		getline(cin, q);
		isInt = checkInt(q);
		isPrime = isInt && FermatTest(largeInt(p), 100);
		bangP = q == p;
		if (!isInt) cout << "Ban da nhap sai, moi nhap lai: q = ";
		else if (!isPrime) cout << "So vua nhap khong nguyen to, moi nhap lai: q = ";
		else if (bangP) cout << "q phai khac p, moi nhap lai: q = ";
	} while (!isInt || !isPrime || bangP);
	
	N = largeInt(p) * largeInt(q);
	phiN = (largeInt(p) - 1) * (largeInt(q) - 1);
	cout << "\nNhap khoa e: e = ";
	bool primeToEachother = true;
	do {
		getline(cin, exp);
		isInt = checkInt(exp);
		primeToEachother = isInt && (gcd(largeInt(exp), phiN) == one);
		if (!isInt) {
			cout << "Ban da nhap sai, moi nhap lai: e = ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (!primeToEachother) cout << "e phai nguyen to cung nhau voi phi(p * q), moi nhap lai: e = ";
	} while (!isInt || !primeToEachother);
	e.setNum(exp);
	d = nghichDao(e, phiN);
}

void sinhKhoa() {
	string min, delta;
	cout << "Cac so nguyen to can lon hon toi thieu bao nhieu?: ";
	bool isInt = true;
	do {
		getline(cin, min);
		isInt = checkInt(min);
		if (!isInt) {
			cout << "Ban da nhap sai, moi nhap lai: ";
			cin.clear();
			cin.ignore();
		}
	} while (!isInt);

	cout << "2 so nguyen to se chenh lech nhau bao nhieu?(nhap so am hay duong deu duoc, chuong trinh se lay gia tri tuyet doi): ";
	do {
		getline(cin, delta);
		isInt = checkInt(delta);
		if (!isInt) {
			cout << "Ban da nhap sai, moi nhap lai: ";
			cin.clear();
			cin.ignore();
		}
	} while (!isInt);
	if (delta[0] == '-') delta = &delta[1];

	largeInt p(min), q(delta);
	if ((largeInt(min[min.size() - 1]) % 2) == zero) p = p + 1;
	if ((largeInt(delta[delta.size() - 1]) % 2) == one) q = q + 1;

	while (!FermatTest(p, 10)) p = p + 2;
	q = p + q;
	while (!FermatTest(q, 10)) q = q + 2;

	N.setNum(p * q);
	phiN.setNum((p - 1) * (q - 1));

	largeInt phin(phiN >> 2);
	while ((phin % 2) == zero) phin >>= 1;
	e.setNum(random((phin / 2) - 1));
	e <<= 1; e += 3;
	while (gcd(e, phin) != one) { e += 2; e %= phiN; }
	d.setNum(nghichDao(e, phiN));
}

void crypting(string a) {//a la "encrypt" hoac "decrypt"
	string fileName = "";
	cout << "Nhap ten file/path cua file can ma hoa: "; getline(cin, fileName);
	ifstream fin(fileName);//ten file mac dinh co duoi txt
	if (!(fin.is_open())) {
		cout << "Khong mo duoc file " << fileName << '\n';
		system("pause"); return;
	}
	string content = "";
	string line;
	while (getline(fin, line))
		content += line + '\n';
	content.pop_back();//remove \0
	fin.close();

	fileName.resize(fileName.size() - 4);
	largeInt b(content), i(one);
	cout << "b = " << b.getNum() << '\n';
	largeInt c = (N > b) ? powerMod(b, (a == "encrypt") ? e : d, N) : zero;
	// TODO:
	cout << "c = " << c.getNum() << '\n';
	system("pause");
	if (c == zero) {
		cout << "noi dung co gia tri lon hon N.\n";
		system("pause"); return;
	}

	ofstream fout(fileName + "_" + a + ".txt");
	if (!(fout.is_open())) {
		cout << "khong du dung luong de luu thong tin da ma hoa.\n";
		system("pause"); return;
	}
	numItr i_end = c.getNum()->end();
	for (numItr i = c.getNum()->begin(); i != i_end; i++)
		fout << *i;
	fout.close();
}

int main() {
	int chon = 0;
	do {
		chon = menu();
		switch (chon) {
		case 1: nhapKhoa(); break;
		case 2: sinhKhoa(); break;
		case 3: crypting("encrypt"); break;
		case 4: crypting("decrypt");
		}
	} while (chon != 5);
	return 0;
}