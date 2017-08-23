#include "VehicleOwner.h"

#include <cpprest/json.h>
using namespace web;

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
	if (value.has_field(JSON_FILED_NAME)) {
		_name = value.at(JSON_FILED_NAME).as_string();
	}
	else {
		_name.clear();
	}
	if (value.has_field(JSON_FILED_NUMBER)) {
		_number = value.at(JSON_FILED_NUMBER).as_string();
	}
	else {
		_number.clear();
	}
	if (value.has_field(JSON_FILED_ADDRESS)) {
		_address = value.at(JSON_FILED_ADDRESS).as_string();
	}
	else {
		_address.clear();
	}
}

void VehicleOwner::toJsonObject(JSON_T& obj) const {
	obj[JSON_FILED_NAME] = json::value::string(_name);
	obj[JSON_FILED_NUMBER] = json::value::string(_number);
	obj[JSON_FILED_ADDRESS] = json::value::string(_address);
}