#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//-------------------//
/*

Distance:
1ft = 0.3048m

Temp:
F = (9/5 * C) + 32

Mass:
1lb = 453.592g

*/
//-------------------//

int main() {
	string temp;

	//MVP Task 1
	cout << "Please select the type of measurement you wish to convert" << endl;
	cout << "(Type the associated letter and hit enter)" << endl;
	cout << endl;
	cout << "Options:" << endl;
	cout << "[D]istance, [T]emperature, or [M]ass" << endl;

	string user_measurement_selection;
	getline(cin, user_measurement_selection);
	cout << "You selected: " << user_measurement_selection << endl;

	//MVP Task 2
	cout << endl;
	cout << "Please select:" << endl;
	cout << "[M]etric or [I]mperial" << endl;

	string user_unit_type_selection;
	getline(cin, user_unit_type_selection);
	cout << "You selected: " << user_unit_type_selection << endl;

	//MVP Task 3
	cout << setprecision(16); //Using this without "fixed" shows user-entered decimal places; Even NASA uses no more than 16 decimal places so this should be plenty accurate
	cout << endl;
	cout << "Enter the NUMERICAL value to be converted: ";
	getline(cin, temp);
	double user_value = stod(temp);
	cout << "You entered: " << user_value << endl;

	return 0;
}