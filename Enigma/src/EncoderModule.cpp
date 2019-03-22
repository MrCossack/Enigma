#include <iostream>

#include "EncoderModule.h"

EncoderModule::EncoderModule(int randSeed)
{
	srand(randSeed);
}

EncoderModule::~EncoderModule()
{
}

void EncoderModule::print() const
{
	for (int i = 0; i < 2 * NUM_LETTERS + 1; ++i)
	{
		std::cout << "-";
	}

	std::cout << std::endl << " ";

	for (int i = 0; i < NUM_LETTERS; ++i)
	{
		std::cout << char('A' + i) << " ";
	}

	std::cout << std::endl;

	for (int i = 0; i < NUM_LETTERS; ++i)
	{
		std::cout << char('A' + getCode(i)) << " ";
	}

	std::cout << std::endl;

	for (int i = 0; i < 2 * NUM_LETTERS + 1; ++i)
	{
		std::cout << "-";
	}

	std::cout << std::endl << " ";
}

int EncoderModule::getCode(int idx) const
{
	return m_configuration[idx];
}

int EncoderModule::getIndex(int element) const
{
	for (int i = 0; i < NUM_LETTERS; ++i)
	{
		if (m_configuration[i] == element)
		{
			return i;
		}
	}
	return 0;
}