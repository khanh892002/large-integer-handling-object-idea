#include "largeInt.h"
#include <vector>

largeInt N, phiN, e, d, one(1);

vector<bool> binaryBool(largeInt n) {
	vector<bool> result;
	while (n.getNum() != "0") {
		if ((n % 2).getNum() == "1") result.push_back(true);
		else result.push_back(false);
		n = n / 2;
	}
	return result;
}

bool inUsedList(vector<largeInt>& list, largeInt& a) {
	int size = list.size();
	for (int i = 0; i < size; i++)
		if (a.getNum() == list[i].getNum())
			return true;

	return false;
}

largeInt random(largeInt& a) {
	// assume a is positive
	// this function return a random number smaller than a
	largeInt result;
	list<char>* num = a.getNum();
	size_t sz = (rand() % num->size()) + 1;
	while (sz >> 2) {

		sz -= 4;
	}
	while (sz) {

	}
	return result % a;
}

bool FermatTest(largeInt n, int k) {
	largeInt mu = n - 1;
	list<char>* muLi(mu.getNum());
	vector<largeInt> usedNums;
	int count = 0, size = binMu.size();
	while (count < k) {
		largeInt a;
		do {
			a.setNum(*(random(n - 3).getNum()));
			a += 2;
		} while (inUsedList(usedNums, a));
		usedNums.push_back(a);

		largeInt power(1);
		while (mu != zero)
			if () power = (power * power * a) % n;
			else power = (power * power) % n;

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

largeInt powerMod(largeInt a, largeInt b, largeInt n) {
	vector<bool> binMu(binaryBool(b));
	largeInt result("1");
	int i = binMu.size() - 1;
	while (i >= 0) {
		if (binMu[i]) result = (result * result * a) % n;
		else result = (result * result) % n;
		i--;
	}
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
	while (!(a == zero) && !(b == zero))
		if (a > b) a = a % b;
		else b = b % a;
	return a + b;
}

bool MillerRabinTest(largeInt n, int k) {
	largeInt a;
	vector<largeInt> arr;
	int i = 0;
	while (i < k) {
		do {
			a.setNum(random(n - 2)); a = a + 2;
		} while (inUsedList(arr, a));
		arr.push_back(a);
		if (gcd(a, n).getNum() != "1") return false;
		else if (powerMod(a, n - 1, n).getNum() != "1") return false;
		else return Witness(a, n);
		i++;
	}
	return true;
}

largeInt nghichDao(largeInt& a, largeInt& p) {//mac dinh gcd(a, n) = 1
	vector<largeInt> arr;
	largeInt a1(a.getNum()), p1(p.getNum());
	while (a1.getNum() != "1") {
		arr.push_back(largeInt("-1") * (p1 / a1));
		string temp = (p1 % a1).getNum();
		p1.setNum(a1.getNum());
		a1.setNum(temp);
	}
	int i = arr.size() - 1;
	largeInt m("1"), n(arr[i].getNum());
	i--;
	while (i >= 0) {
		string temp1 = n.getNum(), temp2 = (m + (n * arr[i])).getNum();
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
			<< "\tN = " << N.getNum() << '\n'
			<< "\te = " << e.getNum() << '\n'
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

bool operator==(string a, string b) {
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
		isPrime = FermatTest(largeInt(p), 100);
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
		isPrime = FermatTest(largeInt(p), 100);
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
		primeToEachother = gcd(largeInt(exp), phiN).getNum() == "1";
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
	if ((largeInt(min[min.size() - 1]) % 2).getNum() == "0") p = p + 1;
	if ((largeInt(delta[delta.size() - 1]) % 2).getNum() == "1") q = q + 1;

	while (!FermatTest(p, 10)) p = p + 2;
	q = p + q;
	while (!FermatTest(q, 10)) q = q + 2;

	N.setNum((p * q).getNum());
	phiN.setNum(((p - 1) * (q - 1)).getNum());

	largeInt phin((phiN / 4).getNum());
	while ((phin % 2).getNum() == "0") phin = phin / 2;
	e.setNum(random((phin / 2) - 1));
	e = (e * 2) + 3;
	while (gcd(e, phin).getNum() != "1") e = (e + 2) % phiN;
	d = nghichDao(e, phiN);
}

void crypting(string a) {//a la "encrypt" hoac "decrypt"
	string fileName = "";
	cout << "Nhap ten file/path cua file can ma hoa: "; getline(cin, fileName);
	ifstream fin(fileName);//ten file mac dinh co duoi txt
	if (fin.is_open()) {
		string content = "";
		string line;
		largeInt i("1");
		while (getline(fin, line))
			content += line + '\n';
		content.pop_back();
		fin.close();

		fileName.resize(fileName.size() - 4);
		string result = "";
		largeInt b, eightBits("256");
		i.setNum("1");
		for (int j = content.size() - 1; j >= 0; j--) {
			cout << content[j] << ' ' << int((content[j] < 0) ? content[j] + 256 : content[j]) << ", i = " << i.getNum() << '\n';
			b = b + (i * largeInt(int((content[j] < 0) ? content[j] + 256 : content[j])));
			i = i * eightBits;
		}
		cout << "b = " << b.getNum() << '\n';
		if (N > b) {
			largeInt c = powerMod(b, (a == "encrypt") ? e : d, N);
			cout << "c = " << c.getNum() << '\n';
			system("pause");
			while (c.getNum() != "0") {
				i = c % eightBits;

				result = char(stoi(i.getNum())) + result;
				c = c / eightBits;
			}
		}
		if (result != "") {
			ofstream fout(fileName + "_" + a + ".txt");
			if (fout.is_open()) {
				fout << result;
				fout.close();
			}
			else {
				cout << "khong du dung luong de luu thong tin da ma hoa.\n";
				system("pause");
			}
		}
		else {
			cout << "noi dung co gia tri lon hon N.\n";
			system("pause");
		}
	}
	else {
		cout << "Khong mo duoc file " << fileName << '\n';
		system("pause");
	}
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