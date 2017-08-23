#pragma once
#include "JsonObject.h"
#include <memory>

#define JSON_FILED_NAME		"name"
#define JSON_FILED_NUMBER	"number"
#define JSON_FILED_ADDRESS	"address"

class VehicleOwner : public JsonObject
{
	TSTRING _name;
	TSTRING _number;
	TSTRING _address;
public:
	VehicleOwner();
	~VehicleOwner();
	const TSTRING& getName() const;
	void setName(const TSTRING& name);

	const TSTRING& getNumber() const;
	void setNumber(const TSTRING& number);

	const TSTRING& getAddress() const;
	void setAddress(const TSTRING& address);

	virtual void fromJsonObject(const JSON_T&);
	virtual void toJsonObject(JSON_T& value)  const;

};

typedef std::shared_ptr<VehicleOwner> VehicleOwnerRef;