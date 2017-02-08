#pragma once
#include "stdafx.h"
class controlmodule
{
private:
	translate _trans;
	controller* _contr;
	CoordinatesXYZ _lastXYZ;
	CoordinatesXY _lastXY;

    CoordinatesXY inicialitzaCoord();
	

public:
	//default methods
	controlmodule();
	~controlmodule();

	//operations
	bool input(const CoordinatesXYZ&);
	bool rawmove(const CoordinatesXY & in);
};

