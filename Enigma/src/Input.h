#pragma once
#include <iostream>
#include <sstream>

// print the user information about types of rotors and
// read number and order of the rotors
int* readRotorOrder(int& numRotors);

// input prompt for the daily and message key
char* readKey(int numRotors);

// input prompt for the message to be encrypted
void readSecretMsg(std::string& msg);

// read a number
int readNumber(int min, int max, std::string text);

// read a sequence of 'numChars' characters
void readCharSequence(char chars[], int numChars);

// read a sequence of 'numNumbers' integers and check if the are in range [min..max]
void readNumberSequence(int numbers[], int numNumbers, int min, int max);