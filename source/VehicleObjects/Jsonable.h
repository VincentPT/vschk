#pragma once
#include "VehicleObjectsMacros.h"

class VEHICLEOBJECTS_API Jsonable
{
public:
	Jsonable();
	virtual ~Jsonable();

	virtual void fromJson(const TSTRING&) = 0;
	virtual TSTRING toJson() = 0;
};

