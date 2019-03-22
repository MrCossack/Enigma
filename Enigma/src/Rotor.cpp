#include "Rotor.h"

Rotor::Rotor(RotorType type) : EncoderModule(type), m_offset(0), m_next(0)
{
	init();
}

Rotor::~Rotor(void)
{
}

void Rotor::init()
{
	for (int i = 0; i < NUM_LETTERS; ++i) {
		int j = rand() % (i + 1);

		m_configuration[i] = m_configuration[j];
		m_configuration[j] = i;
	}
}

void Rotor::setOffset(int number)
{
	m_offset = number;

	while (m_offset < 0)
	{
		m_offset += NUM_LETTERS;
	}
	m_offset %= NUM_LETTERS;
}

int Rotor::getCode(int idx) const
{
	return m_configuration[(idx - m_offset + NUM_LETTERS) % NUM_LETTERS];
}

int Rotor::getIndex(int element) const
{
	int index = EncoderModule::getIndex(element);
	index += m_offset;
	index = index % NUM_LETTERS;

	return index;
}

void Rotor::rotate()
{
	m_offset++;
	if (m_offset > NUM_LETTERS)
	{
		m_offset = 0;
		if (m_next != NULL)
		{
			m_next->rotate();
		}
	}
}

void Rotor::addOffset(int number)
{
	m_offset += number;

	while (m_offset < 0)
	{
		m_offset += NUM_LETTERS;
	}
	m_offset %= NUM_LETTERS;
}