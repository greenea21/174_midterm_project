#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h> //For text color
HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);

void set_out_color(int color) {
	SetConsoleTextAttribute(hndl, color);
}

enum colors {
	RED = 12,
	GREEN = 10,
	YELLOW = 14,
	WHITE = 15,
	dGRAY = 7 //default gray
};

using namespace std;

bool continue_program = true;
bool retry_try_again = true;
string temp;
bool user_try_again;
void graceful_exit(string message, int exit_code);
void newline(unsigned int numlines);
double tofeet(double meters);
double tometers(double feet);
double toF(double celsius);
double toC(double fahrenheit);
double topounds(double grams);
double tograms(double pounds);
double kilo_convert(double value);
string format_metric(double value, string unit);
void validate_input(double value, enum measurement_category category, enum unit_type unit);
void prompt_user_try_again();

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
	set_out_color(WHITE);
	char input;
	unsigned short selected_measurement_type{}; // {} sets the variable to 0 (otherwise intellisense will complain) the same as "= 0;" would
	unsigned short selected_unit_type{};
	double user_value;

	cout << setprecision(16);

	while (continue_program) {
		//MVP Task 1
		cout << "Select your measurement type" << endl;
		cout << "(Type the associated letter and hit enter)" << endl;
		newline(1);
		cout << "[D]istance, [T]emperature, or [M]ass" << endl;

		set_out_color(GREEN);
		getline(cin, temp);
		set_out_color(WHITE);
		input = tolower(temp[0]); //Because we're pulling only the first letter of the input string, typing out the full word will still work

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

		set_out_color(GREEN);
		getline(cin, temp);
		set_out_color(WHITE);

		input = tolower(temp[0]);

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

		set_out_color(GREEN);
		getline(cin, temp);
		set_out_color(WHITE);

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
			cout << format_metric(user_value, "m") << " is " << tofeet(user_value) << " feet" << endl;
		}
		else if (selected_measurement_type == DISTANCE && selected_unit_type == IMPERIAL) { //FEET to METERS
			validate_input(user_value, DISTANCE, IMPERIAL);
			double meters = tometers(user_value);
			cout << user_value << " feet is " << format_metric(meters, "m") << endl;
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
			cout << format_metric(user_value, "g") << " is " << topounds(user_value) << " pound(s)" << endl;
		}
		else if (selected_measurement_type == MASS && selected_unit_type == IMPERIAL) {
			validate_input(user_value, MASS, IMPERIAL);
			double grams = tograms(user_value);
			cout << user_value << " pound(s) is " << format_metric(grams, "g") << endl;
		}


		//convert mass to weight values
		if (selected_measurement_type == MASS) {
			set_out_color(YELLOW);
			cout << "Would you like to see additional weight values of your measurement? (y/n) ";
			set_out_color(GREEN);
			getline(cin, temp);
			set_out_color(WHITE);
			char yn = tolower(temp[0]);
			if (yn == 'y' && selected_unit_type == METRIC) {
				double earth_N = (user_value / 1000) * 9.81;
				double moon_N = (user_value / 1000) * 1.62;
				double mars_N = (user_value / 1000) * 3.71;
				double jupiter_N = (user_value / 1000) * 24.79;
				cout << "Earth: " << earth_N << " N " << "Moon: " << moon_N << " N " << "Mars: " << mars_N << " N " << "Jupiter: " << jupiter_N << endl;
			}
			else if (yn == 'y' && selected_unit_type == IMPERIAL) {
				double earth_N = (tograms(user_value) / 1000) * 9.81;
				double moon_N = (tograms(user_value) / 1000) * 1.62;
				double mars_N = (tograms(user_value) / 1000) * 3.71;
				double jupiter_N = (tograms(user_value) / 1000) * 24.79;
				cout << "Earth: " << earth_N << " N\t" << "Moon: " << moon_N << " N\t" << "Mars: " << mars_N << " N\t" << "Jupiter: " << jupiter_N << endl;
			}
			else if (yn != 'n') {
				graceful_exit("Invalid input! Please respond y for yes or n for no.", INVALID_INPUT);
			}
		}

		//Try again?
		newline(2);
		prompt_user_try_again();
		newline(2);
	}

	return 0;
}


void prompt_user_try_again() {
	while (retry_try_again) {
		set_out_color(YELLOW);
		cout << "Would you like to do another conversion?" << endl;
		cout << "[Y]es or [N]o?" << endl;
		set_out_color(WHITE);

		set_out_color(GREEN);
		getline(cin, temp);
		set_out_color(WHITE);

		if (tolower(temp[0]) == 'n') {
			continue_program = false;
			exit(0);
		}
		else if (tolower(temp[0]) != 'y') {
			set_out_color(RED);
			cout << "Invalid input! Enter y or n" << endl;
			set_out_color(WHITE);
		}
	else if(tolower(temp[0]) == 'y') {
			retry_try_again = false;
		}
	}

	retry_try_again = true;
}

void graceful_exit(string exit_message, int exit_code) {
	newline(1);
	set_out_color(RED);
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

string format_metric(double value, string unit) {
	if (value >= 1000) {
		return to_string(value / 1000) + " k" + unit;
	}
	else if (value >= 1) {
		return to_string(value) + " " + unit;
	}
	else if (value >= 0.01) {
		return to_string(value * 100) + " c" + unit;
	}
	else {
		return to_string(value * 1000) + " m" + unit;
	}
}

void validate_input(double value, enum measurement_category category, enum unit_type unit) {
	if (category == DISTANCE || category == MASS) {
		if (value < 0) {
			graceful_exit("Value must be non-negative!", INVALID_INPUT);
		}
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
