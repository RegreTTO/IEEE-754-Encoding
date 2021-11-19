#include <iostream>
#include<string>

using namespace std;

bool itc_isDigit(unsigned char c) {
	return c >= '0' && c <= '9';
}
unsigned long long itc_len(string s) {
	unsigned long long siz = 0;
	while (s[siz] != '\0')siz++;
	return siz;
}
bool isLetter(char c) {
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';

}
unsigned long long itc_atoi(string s) {
	unsigned long long n = itc_len(s);
	unsigned long long answ = 0;
	for (long long i = n - 1, exp = 1; i >= 0; i--, exp *= 10)
		if (itc_isDigit(s[i]))answ += (s[i] - '0') * exp;
		else return -1;
	return answ;
}
string itc_itoa(unsigned long long n) {
	string s = "";
	while (n > 0) {
		s = char((n % 10) + '0') + s;
		n /= 10;
	}
	return s;
}
string convertToBin(unsigned long long dec) {
	if (dec == -1)return "";
	string bin = "";
	while (dec > 0) {
		bin = char(dec % 2 + '0') + bin;
		dec /= 2;
	}

	if (bin == "")return "0";
	return bin;
}
unsigned long long _log(unsigned long long n, unsigned long long d = 10) {
	unsigned long long l = 0;
	while (n > 0)l++, n /= d;
	return l;
}
string convertToReversedBin(long long real, int chars) {
	//chars--;
	unsigned long long len = 0;
	long long delimetr = 1;
	for (long long i = 0; i < chars; i++, delimetr *= 10);
	string bin = "";
	while (real > 0 && len<32) {
		real = real * 2;
		bin = bin + char(real / delimetr + '0');
		
		real %= delimetr;
		len++;
	}


	if (bin == "")return "0";
	return bin;
}

int main() {
	string num; cin >> num;
	unsigned long long dec = 0, real = 0;
	string construct = "";
	bool negate = false;
	int log10real = 0;
	if (num[0] == '-') {
		negate = true;
		num[0] = '0';
	}
	// Разбиение на вещественную и целую часть
	bool isInt = 1;
	for (unsigned long long i = 0, points = 0; num[i] != '\0' && points<2; i++) {
		if (num[i] != '.' && num[i] !=',')construct += num[i];
		else {
			points++;
			isInt = 0;
			if (points < 2) {
				dec = itc_atoi(construct);
				if (dec == -1) {
					cout << "error"; return 0;
				}
				construct = "";
			}
		}
	}

	if (!isInt) {
		int n = itc_len(construct);
		log10real = n;
		string new_constr = "";
		for (int i = n - 1;  i >= 0  ; i--){
			if(construct[i] != '0')
				new_constr = construct[i] + new_constr;
		}
		real = itc_atoi(new_constr);
	}
	else dec = itc_atoi(construct);
	if (real >= 1e8-1);
	string dec_bin = convertToBin(dec);
	string real_bin = convertToReversedBin(real, log10real);

	long long exp = 0;
	string mantiss = "";
	//считаем экспоненту
	
	if (dec_bin == "0") {
		for (unsigned long long i = 0; real_bin[i] != '\0' && real_bin[i] == '0'; i++, exp--);
		for (unsigned long long i = (exp - 1) * -1, j = 0; real_bin[i] != '\0' && j < 23; j++) {
			mantiss += real_bin[i+j];
		}
		exp -= 1;

	}
	else {
		string binnum = dec_bin + real_bin;
		exp = itc_len(dec_bin);
		for (unsigned long long i = 1; binnum[i] != '\0' && i<=23 ; i++)mantiss += binnum[i];
		exp -= 1;

	}
    
    if(real_bin == "0" && dec_bin == "0"){
        exp = -127;
        mantiss = "";
    }
	//проверка на переполнение
	if (exp > 127 || exp<-127) {
		cout << "NaN";
		return 0;
	}
	string binary_excp = convertToBin(exp + 127);
	for (unsigned long long i = itc_len(binary_excp); i < 8; i++)binary_excp = '0' + binary_excp;
	for (unsigned long long i = itc_len(mantiss); i < 23; i++)mantiss +='0';

	char IEEE_754_encoded = char(int(negate) + '0');// + binary_excp + mantiss;
	cout << IEEE_754_encoded<<binary_excp<<mantiss;
}
