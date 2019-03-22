#pragma once

#include <iostream>
#include <stdlib.h>

#include "EncoderModule.h"

class Reflector : public EncoderModule
{
public:
	Reflector();
	~Reflector();

	
	// randomly swap two elements until
	// all elements have been swapped
	void init();
};