#pragma once
#include <iostream>
#include "EncoderModule.h"

enum RotorType
{
	ROTOR_TYPE_I = 56789,
	ROTOR_TYPE_II = 33170,
	ROTOR_TYPE_III = 7013023,
	ROTOR_TYPE_IV = 3017,
	ROTOR_TYPE_V = 42,
};

class Rotor : public EncoderModule
{
public:
	explicit Rotor(RotorType type);
	virtual ~Rotor();

	virtual void init() override;

	void setNext(Rotor* next) { m_next = next; }
	void setOffset(int number);
	
	virtual int getIndex(int element) const override;
	virtual int getCode(int idx) const override;

	void rotate();
	void addOffset(int number);
	
private:
	Rotor* m_next;
	int m_offset;
};