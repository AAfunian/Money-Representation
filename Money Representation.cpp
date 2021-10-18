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
	Money();
	Money(Currency, long double);
	Currency get_currency();
	long int get_money();
	friend istream& operator>>(istream&, Money& m);
	long int convert(long double);
private:
	long int cents;
	Currency currency;
};
Money::Money() {
	currency = Currency::USD;
	cents = 0;
}
Money::Money(Currency curr, long double c) {
	currency = curr;
	cents = convert(c);
}
long int Money::convert(long double d)
{
	d *= 100; /* Per exercise instructions, we receive input as whole currency which is 
					then converted to cents internally and rounded to the nearest cent */
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
istream& operator>>(istream& is, Money& m) {
	vector<string> store{ "USD", "DKK", "JPY", "IRR", "EUR", "CHF", "GBP", "AUD", "BRL", "CAD", "EGP", "INR", "SEK", "TRY" };
	string temp = "";
	long double amount;
	cout << "\nEnter currency abbreviation (3 letters): ";
	is >> temp;
	cout << "Enter the amount of currency: ";
	is >> amount;
	for (char& x : temp) x = toupper(x);
	for (int i = 0; i < store.size(); ++i) {
		if (temp == store[i]) {
			m.currency = Currency(i);
			m.cents = m.convert(amount);
			return is;
		}
	}
	cout << "Error (Money>>)\n";
	return is;
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
	bool neg = false;
	if (cpy <= 0) {
		cpy = -cpy;
		neg = true;
	}
	while (cpy >= 100) {
		counter++;
		cpy -= 100;
	}
	bool add_zero = false;
	if (cpy < 10) add_zero = true;
	if (!neg) {
		add_zero ? cout << m.get_currency() << ' ' << counter << '.' << 0 << cpy : cout << m.get_currency()
			<< ' ' << counter << '.' << cpy;
	}
	else {
		add_zero ? cout << m.get_currency() << " -" << counter << '.' << 0 << cpy : cout << m.get_currency()
			<< " -" << counter << '.' << cpy;
	}
	return os;
}
void operator+(Money& x, Money& y) {
	cout << '\n';
	if (x.get_currency() == y.get_currency()) {
		double comb = double(x.get_money()) / 100 + double(y.get_money()) / 100;
		Money temp(x.get_currency(), comb);
		cout << x << " + " << y << " = " << temp;
	}
	else cout << "Cannot combine different currencies!\n";
}
void operator-(Money& x, Money& y) {
	cout << '\n';
	if (x.get_currency() == y.get_currency()) {
		double comb = double(x.get_money()) / 100 - double(y.get_money()) / 100;
		Money temp(x.get_currency(), comb);
		cout << x << " - " << y << " = " << temp;
	}
	else cout << "Cannot combine different currencies!\n";
}

int main() {
	Money test(Currency::USD, 532.9);
	cout << test;
	Money test2;
	cin >> test2;
	cout << test2;
	test + test2;
	//test + test2;
	return 0;
}