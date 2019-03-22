#pragma once

#include <string>

#include "Rotor.h"
#include "Reflector.h"
#include "EncoderModule.h"

class Enigma
{
public:

	Enigma(int numRotors);
	~Enigma();

	// add a rotor of a specific type
	void addRotor(RotorType type);
	// exchange the rotor at position ’posIdx’
	void changeRotor(Rotor & rotor, int posIdx);

	// set the daily key settings
	void setDailyKey(char key[]);
	// set the message key settings
	void setMessageKey(char key[]);
	// clear daily and message key settings
	void reset();

	// encrypt the message key with the daily key settings
	// encrypt ’msg’ with the current daily and message key settings
	std::string encrypt(const std::string & msg);
	// decrypt the message with current daily and message key settings
	// (the message key is read at the beginning of the message)
	std::string decrypt(const std::string & msg);

	std::string performingEncryption(const std::string& dailyKey,
		const std::string& msgKey,
		const std::string& msg);

	std::string performDecryption(const std::string& dailyKey,
		const std::string& msg);


private:
	// apply the message key setting (set offset for each rotor)
	void applyMsgKey();
	// read each word from ’msg’ and encrypt/decrypt it
	void processMsg(const std::string & msg, std::string & out);
	// get the index of the char ’c’ (range: [A..Z,a..z])
	int toInt(char c);
	// get the corresponding char for the int ’i’ (range: [0..NUM_LETTERS[)
	char toChar(int i);



private:
	// the number of rotors
	int m_numRotors; 
	// array of pointers to rotors
	Rotor** m_rotors;
	// the reflector module
	Reflector m_reflector;
	// the current msgKey
	char* m_msgKey;
};

