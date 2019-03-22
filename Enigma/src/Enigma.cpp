#include "Enigma.h"

#include <iostream>
#include <sstream>


Enigma::Enigma(int numRotors) : m_numRotors(numRotors)
{
	m_rotors = new Rotor*[numRotors];
	m_msgKey = new char[numRotors + 1];
	m_msgKey[numRotors] = '\0';

	for (int i = 0; i < numRotors; ++i)
	{
		m_rotors[i] = 0;
	}
}

Enigma::~Enigma()
{
	for (int i = 0; i < m_numRotors; ++i)
	{
		delete m_rotors[i];
	}
	delete[] m_rotors;
	delete[] m_msgKey;
}

void Enigma::setDailyKey(char key[])
{
	for (int i = 0; i < m_numRotors; ++i)
	{
		m_rotors[i]->setOffset(toInt(key[i]));
	}
}

void Enigma::setMessageKey(char key[])
{
	memcpy(m_msgKey, key, m_numRotors);
}

void Enigma::reset()
{
	for (int i = 0; i < m_numRotors; ++i)
	{
		m_msgKey[i] = 0;
		if (0 != m_rotors[i])
		{
			m_rotors[i]->setOffset(0);
		}
	}
}

void Enigma::applyMsgKey()
{
	for (int i = 0; i < m_numRotors; ++i)
	{
		m_rotors[i]->addOffset(toInt(m_msgKey[i]));
	}
}

// get the index of the char ’c’ (range: [A..Z,a..z])
int Enigma::toInt(char c)
{
	int asciiCode = (int)c;

	if (asciiCode >= 65 && asciiCode <= 90) {
		return asciiCode - 65;
	}

	if (asciiCode >= 97 && asciiCode <= 122) {
		return asciiCode - 97;
	}

	return 0;
}

// get the corresponding char for the int ’i’ (range: [0..NUM_LETTERS[)
char Enigma::toChar(int i)
{
	return (char)(i + 65);
}

std::string Enigma::encrypt(const std::string& msg)
{
	std::string encryptedMsg;
	std::string encryptedKey;

	processMsg(m_msgKey, encryptedKey);
	applyMsgKey();
	processMsg(msg, encryptedMsg);

	return encryptedKey + " " + encryptedMsg;
}

std::string Enigma::decrypt(const std::string& msg)
{
	std::string decryptedMsg;

	processMsg(msg.substr(0, m_numRotors), decryptedMsg);
	strcpy_s(m_msgKey, m_numRotors+1, decryptedMsg.substr(0, m_numRotors).c_str());

	applyMsgKey();
	processMsg(msg.substr(m_numRotors + 1), decryptedMsg);

	return decryptedMsg;
}

void Enigma::addRotor(RotorType type)
{
	int index = 0;
	for (; index < m_numRotors && 0 != m_rotors[index]; ++index);

	if (index < m_numRotors) {
		m_rotors[index] = new Rotor(type);

		if (index > 0) {
			m_rotors[index - 1]->setNext(m_rotors[index]);
		}
	}
}

void Enigma::changeRotor(Rotor& rotor, int posIdx)
{
	if (0 <= posIdx && m_numRotors > posIdx) {
		delete m_rotors[posIdx];
		m_rotors[posIdx] = new Rotor(rotor);
	}
}

std::string Enigma::performingEncryption(	const std::string& dailyKey,
											const std::string& msgKey,
											const std::string& msg)
{
	reset();
	setDailyKey(const_cast <char*> (dailyKey.c_str()));
	setMessageKey(const_cast <char*> (msgKey.c_str()));
	return encrypt(msg);
}

std::string Enigma::performDecryption(		const std::string&dailyKey,
											const std::string& msg)
{
	reset();
	setDailyKey(const_cast <char*> (dailyKey.c_str()));
	return decrypt(msg);
}

void Enigma::processMsg(const std::string& msg, std::string& encryptedMsg) {
	std::stringstream stream(msg);

	std::string word;

	while (stream >> word) {
		for (unsigned int i = 0; i < word.length(); ++i) {
			int x = toInt(word.at(i));

			for (int j = 0; j < m_numRotors; ++j) {
				x = m_rotors[j]->getCode(x);
			}
			x = m_reflector.getCode(x);

			for (int j = m_numRotors - 1; j >= 0; --j) {
				x = m_rotors[j]->getIndex(x);
			}
			encryptedMsg += toChar(x);

			// the first rotor will rotate the next rotor, if necessary
			m_rotors[0]->rotate(); 
		}
		encryptedMsg += " ";
	}
}