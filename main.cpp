#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <map>

using namespace std;

void graceful_exit(string message, int exit_code);
void newline(unsigned int numlines);
double tofeet(double meters);
double tometers(double feet);
double toF(double celsius);
double toC(double fahrenheit);
double topounds(double grams);
double tograms(double pounds);

enum measurement_category {
	DISTANCE = 0,
	TEMPERATURE = 1,
	MASS = 2
};

enum unit_type {
	METRIC = 0,
	IMPERIAL = 1
};

string measurement_categories[] = {
	"DISTANCE",
	"TEMPERATURE",
	"MASS"
};

string unit_types[] = {
	"METERS",
	"FEET"
};

int main() {
	string temp;
	cout << setprecision(16); //NASA uses no more than 16 decimal places so this should be plenty accurate

	//MVP Task 1
	cout << "Select your measurement type" << endl;
	cout << "(Type the associated letter and hit enter)" << endl;
	newline(1);
	cout << "[D]istance, [T]emperature, or [M]ass" << endl;

	getline(cin, temp);
	char input = tolower(temp[0]);

	unsigned short selected_measurement_type{}; //have to set this to zero with '{}' so intellisense doesn't complain, despite the fact it doesn't need to be
	switch (input) {
		case 'd':
			selected_measurement_type = DISTANCE;
			break;
		case 't':
			selected_measurement_type = TEMPERATURE;
			break;
		case 'm':
			selected_measurement_type = MASS;
			break;
		default:
			graceful_exit("Invalid input, enter a valid option! (d, t, or m)", -1);
	}

	//MVP Task 2
	newline(2);
	cout << "Is your value metric or imperial?" << endl;
	cout << "[M]etric or [I]mperial" << endl;

	getline(cin, temp);
	input = tolower(temp[0]);

	unsigned short selected_unit_type{};
	switch (input) {
		case 'm':
			selected_unit_type = METRIC;
			break;
		case 'i':
			selected_unit_type = IMPERIAL;
			break;
		default:
			graceful_exit("Invalid input, enter a valid option! (m or i)", -1);
	}

	//MVP Task 3
	newline(1);
	cout << "Enter the NUMERICAL value to be converted: ";
	getline(cin, temp);
	double user_value = stod(temp); //TODO if not numerical value then exit

	newline(1);

	if (selected_measurement_type == DISTANCE && selected_unit_type == METRIC) {
		cout << user_value << "meters is " << tofeet(user_value) << " feet" << endl;
	}
	else if (selected_measurement_type == DISTANCE && selected_unit_type == IMPERIAL) {
		cout << user_value << "feet is " << tometers(user_value) << " meters" << endl;
	}
	else if (selected_measurement_type == TEMPERATURE && selected_unit_type == METRIC) {
		cout << user_value << "celsius is " << toF(user_value) << " fahrenheit" << endl;
	}
	else if (selected_measurement_type == TEMPERATURE && selected_unit_type == IMPERIAL) {
		cout << user_value << "fahrenheit is " << toC(user_value) << " celsius" << endl;
	}
	else if (selected_measurement_type == MASS && selected_unit_type == METRIC) {
		cout << user_value << "grams is " << topounds(user_value) << " pounds" << endl;
	} else if (selected_measurement_type == MASS && selected_unit_type == IMPERIAL) {
		cout << user_value << "pounds is " << tograms(user_value) << " grams" << endl;
	}

	return 0;
}

void graceful_exit(string exit_message, int exit_code) {
	newline(1);
	cout << exit_message << endl;
	exit(exit_code);
}

void newline(unsigned int numlines) {
	for (int i = 0; i < numlines; i++) {
		cout << endl;
	}
}

double tofeet(double meters) {
	return meters * 3.28084;
}

double tometers(double feet) {
	return (feet * .3048);
}

double toF(double celsius) {
	return ((9.0 / 5.0) * celsius) + 32.0;
}

double toC(double fahrenheit) {
	return (fahrenheit - 32) * (5.0 / 9.0);
}

double topounds(double grams) {
	return grams / 453.592;
}

double tograms(double pounds) {
	return pounds * 453.592;
}