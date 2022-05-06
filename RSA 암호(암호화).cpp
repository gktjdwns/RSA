#include<iostream>
#include <random>
#include<cmath>
#include<string>
#include<stack>

using namespace std;

class RSA_key//
{
public:
	RSA_key();
	long long getX();
private:
	long long p, q, e, d, N, intialA,X;
	long long randpn(long long s=1);
	bool tfpn(long long a);
	long long gcd(long long a, long long b);
	long long lcm(long long a, long long b);
	long long coprimeE(long long N);
	long long producePK(long long e, long long phi);
	long long encryption(long long a, long long N, long long e);
	long long BinDigits(long long n);
	long long intialTask();
};

long long RSA_key::getX() {
	return X;
}

long long RSA_key::intialTask() {
	stack<char>stack;
	char a[20];
	long long a_int = 0, s;
	int cnt = 0;
	cin >> a;
	for (int i = 0; a[i] != NULL; i++)
	{
		stack.push(a[i]);
		cnt++;
	}
	for (int j = 0; j < cnt; j++)
	{
		a[j] = stack.top();
		cout << "a(" << j << "):" << a[j] << endl;
		stack.pop();
		a_int *= 100;
		s = (long long)a[j];
		a_int += s - 97 + 11;
	}
	cout <<"a_int:" << a_int << endl;
	return a_int;
}

long long RSA_key::randpn(long long s) {
	long long a = 100;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<long long> dis(100, 1000);
	while (1)
	{
		a = dis(gen);
		//cout << a << endl;
		if (tfpn(a) && a != s)
		{
			break;
		}
	}
	return a;
}

long long RSA_key::gcd(long long a, long long b) {
	long long tmp;
	if (a < b) {
		tmp = a;
		a = b;
		b = tmp;
	}
	while (b) {
		tmp = a % b;
		a = b;
		b = tmp;
	}
	//cout << "a:" << a << endl;
	return a;
}

long long RSA_key::lcm(long long a, long long b) {
	return (a * b) / gcd(a, b);
}

long long RSA_key::coprimeE(long long N) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<long long> dis(20, 40);

	long long e= dis(gen);
	while (gcd(N,e)!=1)
	{
		e = dis(gen);
	}
	return e;
}

long long RSA_key::producePK(long long e, long long phi) {
	long long r1 = e, r2 = phi;
	long long s1 = 1, s2 = 0;
	long long t1 = 0, t2 = 1;

	long long r, s, t, q;
	while (r2) {
		q = r1 / r2;
		// gcd 계산
		r = r1 % r2;
		r1 = r2, r2 = r;

		// s 계산
		s = s1 - q * s2;
		s1 = s2, s2 = s;

		// t 계산
		t = t1 - q * t2;
		t1 = t2, t2 = t;
	}
	r = r1;
	s = s1, t = t1;
	//cout << "s:" << s << endl;
	//cout << "r:" << r << endl;
	if (r == 1) {
		if (s < 0) {
			s += phi;
		}
		return s;
	}

	
	return s;
}

bool RSA_key::tfpn(long long a) {
	long long flag = 0;
	for (int i = 2; i <= sqrt(a); i++)
	{
		if (a % i == 0)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1)return false;
	else if (flag == 0) return true;
}

long long RSA_key:: BinDigits(long long n) {
	int cnt = 0;
	while (n!=1&&n!=0)
	{
		n /= 2;
		cnt++;
	}

	return cnt;
}

long long RSA_key:: encryption(long long a,long long N,long long e) {
	unsigned long long y = a % N;
	long long m = 1, r = 1;
	long long digits = BinDigits(e)+1;
	while (m<= digits)
	{
		if (e % 2 == 1) r = (r * y) % N;
		e /= 2;
		y = (y * y) % N;
		m++;
	}
	return r;
}

RSA_key::RSA_key()
{
	intialA = intialTask();
	//cout << "intialA:" << intialA << endl;
	p = randpn();
	//cout << "p:" << p << endl;
	q = randpn(p);
	//cout << "q:" << q << endl;
	N = p * q;
	cout << "N:" << N << endl;
	e = coprimeE((p - 1) * (q - 1));
	//e = coprimeE(lcm(p - 1,q - 1));
	//cout << "e:" << e << endl;
	//d = producePK(e, lcm(p - 1, q - 1));
	d = producePK(e, (p - 1)* (q - 1));
	cout << "d:" << d << endl;
	//cout << "ed:" << e * d << endl;
	//cout << "lcm" << lcm(p - 1, q - 1) << endl;
	//cout << "phi" << (p - 1)*(q - 1) << endl;

	X = encryption(intialA, N, e);

}

int main() {
	RSA_key RSA;
	cout << "x:" <<RSA.getX() << endl;
}