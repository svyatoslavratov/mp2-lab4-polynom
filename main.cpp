#include <iostream>
#include "Polynom.h"
using namespace std;

void UserPolimom(TPolynom& pol, int cost);

int main()
{
	try
	{
		int amountOfMon1;
		cout << "Please, enter amount of monoms for first polynom: " << endl;
		cin >> amountOfMon1;
		TPolynom pol;
		UserPolimom(pol, amountOfMon1);

		cout << "Please, enter amount of monoms for second polynom: " << endl;
		int amountOfMon2;
		cin >> amountOfMon2;
		TPolynom pol2;
		UserPolimom(pol2, amountOfMon2);
		cout << "first polynom: " << pol << endl;
		cout << "second polinom: " << pol2 << endl;
		cout << "pol1 + pol2 = " << pol + pol2 << endl;
		cout << "pol1 - pol2 = " << pol - pol2 << endl;
		cout << "pol1 * pol2 = " << pol * pol2 << endl;
		cout << "enter value: ";
		int val;
		cin >> val;
		cout << "1st " << val << ": " << pol.Calculate(val) << endl;
		cout << "2nd" << val << ": " << pol2.Calculate(val) << endl;
	}
	catch (exception str) {
		throw exception(str);
	}

	const char exit = 'e';
	char ch;
	do {
		cin >> ch;
	} while (ch != exit);

	return 0;
}

void UserPolimom(TPolynom& pol, int cost)
{
	for (int i = 0; i < cost; i++)
	{
		int coeff;
		int power;
		cout << "Please, enter coefficient and power of monom : " << i + 1 << endl;
		cin >> coeff;
		cin >> power;
		pol.Insert(coeff, power);
	}
}