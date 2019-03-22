#include <cstdlib>
#include <cassert>
#include <string>
#include <iostream>
#include <sstream>

#include "Input.h"
#include "Enigma.h"

#include <vld.h>

int main()
{
	// read number of rotors and sequence
	int numRotors = 0;
	int* rotorTypes = readRotorOrder(numRotors);
	int quit_program;

	// create enigma
	Enigma enigma(numRotors);

	// add rotors of specific type
	for (int i = 0; i < numRotors; ++i) {
		switch (rotorTypes[i]) {
			case 1: enigma.addRotor(ROTOR_TYPE_I); break;
			case 2: enigma.addRotor(ROTOR_TYPE_II); break;
			case 3: enigma.addRotor(ROTOR_TYPE_III); break;
			case 4: enigma.addRotor(ROTOR_TYPE_IV); break;
			case 5: enigma.addRotor(ROTOR_TYPE_V); break;
		}
	}
	delete[] rotorTypes;

	// read the daily key
	char* dailyKey = readKey(numRotors);
	

	std::string message;
	
	// run the program until '0' is entered for exit
	do
	{
		// set the daily key
		enigma.setDailyKey(dailyKey);

		// read and set the current message key
		char* msgKey = readKey(numRotors);
		enigma.setMessageKey(msgKey);
		
		// read the message entered by the user
		readSecretMsg(message);
		
		// encrypt the message with the daily and message key settings
		std::string encryptedMsg = enigma.encrypt(message);
		std::cout << "encrypted message:" << encryptedMsg << std::endl;

		// clear daily and message key settings
		enigma.reset();
		
		
		// set the daily key again after resetting the enigma				
		enigma.setDailyKey(dailyKey);
		
		// decrypt the message with the daily key settings
		// the message key setting are read from the message
		std::string decryptedMsg = enigma.decrypt(encryptedMsg);
		std::cout << "decrypted message:" << decryptedMsg << std::endl << std::endl;
		
		// clear daily and message key settings
		enigma.reset();

		delete[] msgKey;

		quit_program = readNumber(0, 1, "Press 0: To quite the program\nPress 1: To continue the programm\n");
	} while (quit_program);
	
	delete[] dailyKey;
	
	return 0;
}