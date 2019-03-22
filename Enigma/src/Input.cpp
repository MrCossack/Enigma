#include "Input.h"

int* readRotorOrder(int& numRotors) {

	numRotors = readNumber(1, 5, "Choose the number of rotors[1..5]: ");

	int* rotorTypes = new int[numRotors];

	std::cout << "There are 5 different types of rotors." << std::endl;
	std::cout << "1 - Rotor Typ I " << std::endl;
	std::cout << "2 - Rotor Typ II " << std::endl;
	std::cout << "3 - Rotor Typ III " << std::endl;
	std::cout << "4 - Rotor Typ IV " << std::endl;
	std::cout << "5 - Rotor Typ V " << std::endl;

	std::cout << std::endl << "Choose 1-5 rotors with spaces in between: ";
	readNumberSequence(rotorTypes, numRotors, 1, 5);
	return rotorTypes;
}

char* readKey(int numRotors) {
	std::cout << std::endl << "Choose your daily key [" << numRotors << " upper case letters]: ";
	char* key = new char[numRotors];
	readCharSequence(key, numRotors);
	return key;
}

int readNumber(int min, int max, std::string text) {
	std::string input;
	std::stringstream inputStream;
	int number;

	while (true) {
		std::cout << text;
		std::getline(std::cin, input);

		// This code converts from string to number safely.
		inputStream.str(input);		// set the associated string object
		inputStream >> number;		// after extracting the number, the stream is eof
		inputStream.clear();		// reset error state flags to reuse it in the next loop cycle

		if (number >= min && number <= max) {
			break;
		}
		std::cout << std::endl << "Wrong input, try again: " << std::endl;
	}

	return number;
}

void readCharSequence(char chars[], int numChars) {
	std::string input;
	std::stringstream inputStream;

	while (true) {
		std::getline(std::cin, input); 

		inputStream.str(input); // set the associated string object
		bool error = false;

		int numInputs = 0;
		for (int i = 0; i < numChars; ++i) {
			inputStream >> chars[i];
			if (chars[i] < 'A' || chars[i] > 'Z') {
				error = true;
				break;
			}
			numInputs++;
		}
		if (numInputs != numChars) {
			error = true;
		}

		if (!error) {
			break;
		}
		inputStream.clear(); // reset error state flags to reuse it in the next loop cycle
		std::cout << std::endl << "Wrong input, please try again: ";
	}

}

void readNumberSequence(int numbers[], int numNumbers, int min, int max) {
	std::string input;
	std::stringstream inputStream;

	while (true) {
		std::getline(std::cin, input);

		inputStream.str(input); // set the associated string object
		bool error = false;

		int numInputs = 0;
		for (int i = 0; i < numNumbers; ++i) {
			inputStream >> numbers[i];
			if (numbers[i] < min || numbers[i] > max) {
				error = true;
				break;
			}
			numInputs++;
		}
		if (numInputs != numNumbers) {
			error = true;
		}

		if (!error) {
			break;
		}
		inputStream.clear(); // reset error state flags to reuse it in the next loop cycle
		std::cout <<std::endl << "Wrong input, please try again: ";
	}
}


void readSecretMsg(std::string& msg) {
	std::cout << std::endl << "Insert your secret message: ";
	std::getline(std::cin, msg);
}
