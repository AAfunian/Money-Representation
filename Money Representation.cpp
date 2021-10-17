// Money Representation
// 10/17/2021
// Amir Afunian

#include <iostream>
#include <cmath>
using namespace std;

class Money {
public:
	Money(long double);
	long int get_money();
private:
	long int convert(long double);
	long int cents;
};
Money::Money(long double c) {
	cents = convert(c);
}
long int Money::convert(long double d)
{
	long double remainder = fmod(d, 1);
	if (remainder < .5) { // truncate/round down to the nearest cent
		return d - remainder;
	}
	// else round up to the nearest cent
	else return d + 1;
}
long int Money::get_money() {
	return cents;
}
ostream& operator<<(ostream& os, Money m) {
	int cpy = m.get_money();
	int counter = 0;
	while (cpy >= 100) {
		counter++;
		cpy -= 100;
	}
	bool on = false;
	if (cpy < 10) on = true;

	on ? cout << '$' << counter << '.' << 0 << cpy : cout << '$' << counter << '.' << cpy;
	return os;
}
istream& operator>>(istream& is, long double c) {
	Money m = Money(c);
}

int main() {
	Money test(5332.9);
	cout << test;

	return 0;
}