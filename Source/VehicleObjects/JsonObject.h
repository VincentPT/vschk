#pragma once
#include "Jsonable.h"

namespace web { namespace json { class value; } }
typedef web::json::value JSON_T;

class VEHICLEOBJECTS_API JsonObject : public Jsonable
{
public:
	JsonObject();
	~JsonObject();

	virtual void fromJson(const TSTRING&);
	virtual TSTRING toJson();
	virtual void fromJsonObject(const JSON_T&) = 0;
	virtual void toJsonObject(JSON_T& value) const = 0;
};

