// Money Representation
// 10/17/2021
// Amir Afunian

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

enum class Currency {
	USD, DKK, JPY, IRR, EUR, CHF, GBP, AUD, BRL, CAD, EGP, INR, SEK, TRY
};
class Money {
public:
	Money(Currency, long double);
	Currency get_currency();
	long int get_money();
private:
	long int convert(long double);
	long int cents;
	Currency currency;
};
Money::Money(Currency curr, long double c) {
	currency = curr;
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
Currency Money::get_currency() {
	return currency;
}
long int Money::get_money() {
	return cents;
}
ostream& operator<<(ostream& os, Currency c) {
	vector<string> store {"USD", "DKK", "JPY", "IRR", "EUR", "CHF", "GBP", "AUD", "BRL", "CAD", "EGP", "INR", "SEK", "TRY"};
	for (int i = 0; i < store.size(); ++i) {
		if (i == int(c)) return os << store[i];
	}
	cout << "Error! (<<curr)\n";
	return os;
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

	on ? cout << m.get_currency() << ' ' << counter << '.' << 0 << cpy : cout << m.get_currency() 
		<< ' ' << counter << '.' << cpy;
	return os;
}
/*istream& operator>>(istream& is, long double c) {
	Money m = Money("USD", 534);
}*/

int main() {
	Money test(Currency::CHF, 5332.9);
	cout << test;

	return 0;
}