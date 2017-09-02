#include "WebAppMacros.h"
#include "StolenVehicleInfo.h"
	
#include <Wt/Json/Value>
#include <Wt/Json/Object>

using namespace Wt::Json;

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
	if (value.contains(JSON_FILED_REGISTRATION)) {
		_vehicleRegistration = JSON_VALUE_TO_TSTRING(value.at(JSON_FILED_REGISTRATION));
	}
	if (value.contains(JSON_FILED_MAKE)) {
		_vehicleMake = JSON_VALUE_TO_TSTRING(value.at(JSON_FILED_MAKE));
	}
	if (value.contains(JSON_FILED_MODEL)) {
		_vehicleModel = JSON_VALUE_TO_TSTRING(value.at(JSON_FILED_MODEL));
	}

	if (value.contains(JSON_FILED_OWNER)) {
		_vehicleOwner = std::make_shared<VehicleOwner>();
		_vehicleOwner->fromJsonObject(value.at(JSON_FILED_OWNER));
	}
	else {
		_vehicleOwner.reset();
	}
}


void StolenVehicleInfo::toJsonObject(JSON_T& obj) const {
	obj[JSON_FILED_REGISTRATION] = Value(_vehicleRegistration);
	obj[JSON_FILED_MAKE] = Value(_vehicleMake);
	obj[JSON_FILED_MODEL] = Value(_vehicleModel);
	if (_vehicleOwner) {
		Value valueObject(ObjectType);
		JSON_T& ownerObject = valueObject;
		_vehicleOwner->toJsonObject(ownerObject);
		obj[JSON_FILED_OWNER] = valueObject;
	}
}