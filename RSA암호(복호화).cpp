#include<iostream>
#include<cmath>

using namespace std;

long long BinDigits(long long n) {
	int cnt = 0;
	while (n != 1 && n != 0)
	{
		n /= 2;
		cnt++;
	}

	return cnt;
}

long long decryption(long long x, long long N, long long d) {
	unsigned long long y = x % N;
	long long m = 1, r = 1;
	long long digits = BinDigits(d) + 1;
	while (m <= digits)
	{
		if (d % 2 == 1) r = (r * y) % N;
		d /= 2;
		y = (y * y) % N;
		m++;
	}
	return r;
}

int main() {
	long long N = 294677, d = 28411, ap_int = 0, X = 121170, s = 0,i;
	char* ap = new char[20];
	cin >> N;
	cin >> d;
	cin >> X;
	ap_int =decryption(X, N, d);
	for (i = 0; ap_int%100!=0; i++)
	{
		s = (ap_int % 100)+97-11;
		ap_int /= 100;
		cout << s << endl;
		ap[i] = (char)s;
	}
	ap[i + 1] = NULL;
	cout << "해독 결과:" << ap << endl;
}