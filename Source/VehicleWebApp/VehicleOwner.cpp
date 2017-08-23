#include "VehicleOwner.h"

#include <Wt/Json/Value>
#include <Wt/Json/Object>

VehicleOwner::VehicleOwner() {}


VehicleOwner::~VehicleOwner() {}

const TSTRING& VehicleOwner::getName() const {
	return _name;
}

void VehicleOwner::setName(const TSTRING& name) {
	_name = name;
}

const TSTRING& VehicleOwner::getNumber() const {
	return _number;
}

void VehicleOwner::setNumber(const TSTRING& number) {
	_number = number;
}

const TSTRING& VehicleOwner::getAddress() const {
	return _address;
}

void VehicleOwner::setAddress(const TSTRING& address) {
	_address = address;
}

void VehicleOwner::fromJsonObject(const JSON_T& value) {
	if (value.contains(JSON_FILED_NAME)) {
		_name = value.at(JSON_FILED_NAME);
	}
	else {
		_name.clear();
	}
	if (value.contains(JSON_FILED_NUMBER)) {
		_number = value.at(JSON_FILED_NUMBER);
	}
	else {
		_number.clear();
	}
	if (value.contains(JSON_FILED_ADDRESS)) {
		_address = value.at(JSON_FILED_ADDRESS);
	}
	else {
		_address.clear();
	}
}

void VehicleOwner::toJsonObject(JSON_T& obj) const {
	obj[JSON_FILED_NAME] = Wt::Json::Value(_name);
	obj[JSON_FILED_NUMBER] = Wt::Json::Value(_number);
	obj[JSON_FILED_ADDRESS] = Wt::Json::Value(_address);
}