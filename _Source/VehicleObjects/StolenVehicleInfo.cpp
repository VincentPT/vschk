#include "StolenVehicleInfo.h"

#include <cpprest/json.h>
using namespace web;

StolenVehicleInfo::StolenVehicleInfo()
{
}

StolenVehicleInfo::~StolenVehicleInfo()
{
}

const TSTRING& StolenVehicleInfo::getVehicleRegistration() const {
	return _vehicleRegistration;
}

void StolenVehicleInfo::setVehicleRegistration(const TSTRING& vehicleRegistration) {
	_vehicleRegistration = vehicleRegistration;
}

const TSTRING& StolenVehicleInfo::getVehicleMake() const {
	return _vehicleMake;
}

void StolenVehicleInfo::setVehicleMake(const TSTRING& vehicleMake) {
	_vehicleMake = vehicleMake;
}

const TSTRING& StolenVehicleInfo::getVehicleModel() const {
	return _vehicleModel;
}

void StolenVehicleInfo::setVehicleModel(const TSTRING& vehicleModel) {
	_vehicleModel = vehicleModel;
}

const VehicleOwnerRef& StolenVehicleInfo::getVehicleOwner() const {
	return _vehicleOwner;
}
void StolenVehicleInfo::setVehicleOwner(const VehicleOwnerRef& vehicleOwner) {
	_vehicleOwner = vehicleOwner;
}

void StolenVehicleInfo::fromJsonObject(const JSON_T& value) {
	if (value.has_field(JSON_FILED_REGISTRATION)) {
		_vehicleRegistration = value.at(JSON_FILED_REGISTRATION).as_string();
	}
	else {
		_vehicleRegistration.clear();
	}
	if (value.has_field(JSON_FILED_MAKE)) {
		_vehicleMake = value.at(JSON_FILED_MAKE).as_string();
	}
	else {
		_vehicleMake.clear();
	}
	if (value.has_field(JSON_FILED_MODEL)) {
		_vehicleModel = value.at(JSON_FILED_MODEL).as_string();
	}
	else {
		_vehicleModel.clear();
	}
	if (value.has_field(JSON_FILED_OWNER)) {
		_vehicleOwner = std::make_shared<VehicleOwner>();
		_vehicleOwner->fromJsonObject(value.at(JSON_FILED_OWNER));
	}
	else {
		_vehicleOwner.reset();
	}
}


void StolenVehicleInfo::toJsonObject(JSON_T& obj) const {
	obj[JSON_FILED_REGISTRATION] = json::value::string(_vehicleRegistration);
	obj[JSON_FILED_MAKE] = json::value::string(_vehicleMake);
	obj[JSON_FILED_MODEL] = json::value::string(_vehicleModel);
	if (_vehicleOwner) {
		json::value ownerObject;
		_vehicleOwner->toJsonObject(ownerObject);
		obj[JSON_FILED_OWNER] = ownerObject;
	}
}

std::shared_ptr<std::list<StolenVehicleInfo>> StolenVehicleInfo::parseFromJsonArray(const TSTRING& s) {
	std::shared_ptr<std::list<StolenVehicleInfo>> objs;
	json::value arrayObj = json::value::parse(s);
	if (arrayObj.is_array() == false) {
		return objs;
	}

	objs = std::make_shared<std::list<StolenVehicleInfo>>();
	auto& jsArray = arrayObj.as_array();
	for (auto it = jsArray.begin(); it != jsArray.end(); it++) {
		if (it->is_object()) {
			StolenVehicleInfo dummy;
			objs->push_back(dummy);
			auto& obj = objs->back();
			obj.fromJsonObject(*it);
		}
	}

	return objs;
}

TSTRING StolenVehicleInfo::convertToJsonArray(const std::list<StolenVehicleInfo>& vehicles) {
	json::value arrayVal;	
	int idx = 0;
	for (const StolenVehicleInfo& vehicle : vehicles) {
		json::value object;
		vehicle.toJsonObject(object);
		arrayVal[idx++] = object;
	}

	return arrayVal.to_string();
}