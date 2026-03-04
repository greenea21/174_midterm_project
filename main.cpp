#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void graceful_exit(string message, int exit_code);
void newline(unsigned int numlines);
double tofeet(double meters);
double tometers(double feet);
double toF(double celsius);
double toC(double fahrenheit);
double topounds(double grams);
double tograms(double pounds);
double kilo_convert(double value);
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
	INVALID_INPUT = -1
};

int main() {
	string temp;
	cout << setprecision(16);

	//MVP Task 1
	cout << "Select your measurement type" << endl;
	cout << "(Type the associated letter and hit enter)" << endl;
	newline(1);
	cout << "[D]istance, [T]emperature, or [M]ass" << endl;

	getline(cin, temp);
	char input = tolower(temp[0]); //Because we're pulling only the first letter of the input string, typing out the full word will still work

	unsigned short selected_measurement_type{}; // {} sets the variable to 0 (otherwise intellisense will complain) the same as "= 0;" would
	switch (input) { //Switch is just a cleaner alternative to chaining if/if else statements
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
	double user_value;
	cout << "Enter the NUMERICAL value to be converted: ";
	getline(cin, temp);

	//Try/catch used to validate input and ensure a graceful exit if non numerical character is entered.
	try {
		user_value = stod(temp);
	}
	catch (std::exception h) {
		graceful_exit("Invalid input! Please enter a real number.", INVALID_INPUT);
	}
	
	newline(1);

	//The main "algorithm"
	if (selected_measurement_type == DISTANCE && selected_unit_type == METRIC) { //METERS to FEET
		validate_input(user_value, DISTANCE, METRIC);
		// These if else statments are for strech goal 2. 
		if (user_value >= 1000) {
			cout << kilo_convert(user_value) << " km is " << tofeet(user_value) << " feet" << endl;
		}
		else {
			cout << user_value << " meter(s) is " << tofeet(user_value) << " feet" << endl;
		}
	}
	else if (selected_measurement_type == DISTANCE && selected_unit_type == IMPERIAL) { //FEET to METERS
		validate_input(user_value, DISTANCE, IMPERIAL);
		double meters = tometers(user_value);
		if (meters >= 1000) {
			cout << user_value << " feet is " << kilo_convert(meters) << " km" << endl;
		}
		else {
			cout << user_value << " feet is " << meters << " meter(s)" << endl;
		}
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
		if (user_value >= 1000) {
			cout << kilo_convert(user_value) << " kg is " << topounds(user_value) << " pound(s)" << endl;
		}
		else {
			cout << user_value << " gram(s) is " << topounds(user_value) << " pound(s)" << endl;
		}
	} else if (selected_measurement_type == MASS && selected_unit_type == IMPERIAL) {
		validate_input(user_value, MASS, IMPERIAL);
		double grams = tograms(user_value);

		if (grams >= 1000) {
			cout << user_value << " pound(s) is " << kilo_convert(grams) << " kg" << endl;
		}
		else {
			cout << user_value << " pound(s) is " << grams << " gram(s)" << endl;
		}
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

double kilo_convert(double value)
{
	if (value >= 1000)
	{
		return value / 1000;
	}

	return value;
}

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
