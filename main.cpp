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
//bool check_double_overflow(double input);
//bool check_double_underflow(double input);
//bool check_double_wraparound(double input);
//void catch_double_wraparound(double input);
void validate_input(double value, enum measurement_category category, enum unit_type unit);

//Using enums to avoid "magic numbers" (assigns a keyword to a value so programmers know what the number means)
//Ex. Can just type DISTANCE instead of 0 for clarity
enum measurement_category {
	DISTANCE = 0,
	TEMPERATURE = 1,
	MASS = 2
};

enum unit_type {
	METRIC = 0,
	IMPERIAL = 1
};

enum error_type {
	INVALID_INPUT = -1,
	O_FLOW = -2,
	U_FLOW = -3,
	WRAPAROUND = -4
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
	char input = tolower(temp[0]); //Because we're pulling only the first letter of the input string, typing out the full word WILL still work

	unsigned short selected_measurement_type{}; // {} sets the variable to 0 (otherwise intellisense will complain) the same as "var = 0" would
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
			graceful_exit("Invalid input, enter a valid option! (d, t, or m)", INVALID_INPUT);
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
			graceful_exit("Invalid input, enter a valid option! (m or i)", INVALID_INPUT);
	}

	//MVP Task 3
	newline(1);
	cout << "Enter the NUMERICAL value to be converted: ";
	getline(cin, temp);
	double user_value = stod(temp); //stod already detects wraparound and non-numerical values, but does not handle/catch them (program just crashes).
									//The max/min size of a double is astronomically high though (1 followed by 309 zeros) and is unlikely to be reached.
									//Might be able to fix the crashing with the try/catch feature

	newline(1);

	//The main "algorithm"
	if (selected_measurement_type == DISTANCE && selected_unit_type == METRIC) { //METERS to FEET
		validate_input(user_value, DISTANCE, METRIC);
		cout << user_value << " meter(s) is " << tofeet(user_value) << " feet" << endl;
	}
	else if (selected_measurement_type == DISTANCE && selected_unit_type == IMPERIAL) { //FEET to METERS
		validate_input(user_value, DISTANCE, IMPERIAL);
		cout << user_value << " feet is " << tometers(user_value) << " meter(s)" << endl;
	}
	else if (selected_measurement_type == TEMPERATURE && selected_unit_type == METRIC) { //CELSIUS to FAHRENHEIT
		validate_input(user_value, TEMPERATURE, METRIC);
		cout << user_value << " celsius is " << toF(user_value) << " fahrenheit" << endl;
	}
	else if (selected_measurement_type == TEMPERATURE && selected_unit_type == IMPERIAL) { //FAHRENHEIT TO CELSIUS
		validate_input(user_value, TEMPERATURE, IMPERIAL);
		cout << user_value << " fahrenheit is " << toC(user_value) << " celsius" << endl;
	}
	else if (selected_measurement_type == MASS && selected_unit_type == METRIC) { //GRAMS to POUNDS
		validate_input(user_value, MASS, METRIC);
		cout << user_value << " gram(s) is " << topounds(user_value) << " pound(s)" << endl;
	} else if (selected_measurement_type == MASS && selected_unit_type == IMPERIAL) {
		validate_input(user_value, MASS, IMPERIAL);
		cout << user_value << " pound(s) is " << tograms(user_value) << " gram(s)" << endl; //POUNDS to GRAMS
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
	return (fahrenheit - 32.0) * (5.0 / 9.0);
}

double topounds(double grams) {
	return grams / 453.592;
}

double tograms(double pounds) {
	return pounds * 453.592;
}

//This code isn't able to be used for input validation because of how stod works, but it's a good proof of concept and reference for later if eventually using try/catch

//bool check_double_overflow(double input) {
//	if (input > DBL_MAX) { return true; }
//	return false;
//}
//
//bool check_double_underflow(double input) {
//	if (input < DBL_MIN) { return true; }
//	return false;
//}
//
//bool check_double_wraparound(double input) {
//	if (check_double_overflow(input) || check_double_underflow(input)) {
//		return true;
//	}
//	return false;
//}
//
//void catch_double_wraparound(double input) {
//	if (check_double_wraparound(input)) {
//		graceful_exit("Wraparound detected! (overflow / underflow) Please enter a value that's closer to 0", WRAPAROUND);
//	}
//}

void validate_input(double value, enum measurement_category category, enum unit_type unit) {
	if (category == DISTANCE || category == MASS) {
		if (value < 0) graceful_exit("Value must be non-negative!", INVALID_INPUT);
	}
	else if (category == TEMPERATURE) {
		if (unit == METRIC && value < -273.15) {
			graceful_exit("Value cannot be less than absolute zero! (-273.15C)", INVALID_INPUT);
		}
		else if (unit == IMPERIAL && value < toF(-273.15)) {
			graceful_exit("Value cannot be less than absolute zero! (-459.67F)", INVALID_INPUT);
		}
	}
}