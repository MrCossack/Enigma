#include "Reflector.h"


/**
* 349809 - A magic number to generate always the same random number
*/
Reflector::Reflector() : EncoderModule(349809)
{	
	for (int i = 0; i < NUM_LETTERS; ++i)
	{
		m_configuration[i] = i;
	}
	init();
}

Reflector::~Reflector()
{
}


void Reflector::init()
{
	for (int i = 0; i < NUM_LETTERS; ++i)
	{
		if (m_configuration[i] == i)
		{
			int rndIdx = 0;

			do
			{
				rndIdx = rand() % NUM_LETTERS;
			} while (m_configuration[rndIdx] != rndIdx);

			m_configuration[i] = m_configuration[rndIdx];

			m_configuration[rndIdx] = i;
		}
	}
}