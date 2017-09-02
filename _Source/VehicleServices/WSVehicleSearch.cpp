#include "stdafx.h"
#include "WSVehicleSearch.h"
#include "VehicleDAO\VehicleDAO.h"
#include "RESTResponse.h"

using namespace crab;

WSVehicleSeach::WSVehicleSeach() {}
WSVehicleSeach::~WSVehicleSeach(){}

bool WSVehicleSeach::initialize() {
	return StolenVehicleDAO::connectToDatabase();
}

bool WSVehicleSeach::uninitialize() {
	return StolenVehicleDAO::disconnectToDatabase();
}

void WSVehicleSeach::doGet(http_request& message, const std::vector<crab::TSTRING>& params) {
	RESTResponse response;
	
	if(params.size() <= 0) {
		response.fail(ResponseCode::BadParameters, U("no parameter was specified")).result(U("[]"));
		message.reply(status_codes::OK, response.toString(), U("application/json"));
		return;
	}
	StolenVehicleDAO vehicleDataAccess;
	utility::string_t registration_number = params[0];
	auto vehicles = vehicleDataAccess.findVehicleByRegistrationNumber(registration_number);
	if (vehicles && vehicles->size()) {
		auto result = StolenVehicleInfo::convertToJsonArray(*vehicles.get());
		response.result(result);
	}
	else
	{
		response.result(U("[]"));
	}
	message.reply(status_codes::OK, response.toString(), U("application/json"));
}

void WSVehicleSeach::doPost(http_request& message, const std::vector<crab::TSTRING>& params) {
	RESTResponse response;
	StolenVehicleDAO vehicleDataAccess;
	auto jsonValueTask = message.extract_json();
	auto jsonValue = jsonValueTask.get();

	const crab::TSTRING* vehicle_registration = nullptr;
	const crab::TSTRING* vehicle_make = nullptr;
	const crab::TSTRING* vehicle_model = nullptr;
	const crab::TSTRING* owner_name = nullptr;

	if (jsonValue.has_field(JSON_FILED_REGISTRATION) && jsonValue[JSON_FILED_REGISTRATION].is_string()) {
		vehicle_registration = &jsonValue[JSON_FILED_REGISTRATION].as_string();
	}
	if (jsonValue.has_field(JSON_FILED_MAKE) && jsonValue[JSON_FILED_MAKE].is_string()) {
		vehicle_make = &jsonValue[JSON_FILED_MAKE].as_string();
	}
	if (jsonValue.has_field(JSON_FILED_MODEL) && jsonValue[JSON_FILED_MODEL].is_string()) {
		vehicle_model = &jsonValue[JSON_FILED_MODEL].as_string();
	}
	if (jsonValue.has_field(JSON_FILED_OWNER) && jsonValue[JSON_FILED_OWNER].is_string()) {
		owner_name = &jsonValue[JSON_FILED_OWNER].as_string();
	}

	auto vehicles = vehicleDataAccess.findVehicle(vehicle_registration, vehicle_make, vehicle_model, owner_name);
	if (vehicles && vehicles->size()) {
		auto result = StolenVehicleInfo::convertToJsonArray(*vehicles.get());
		response.result(result);
	}
	else
	{
		response.result(U("[]"));
	}
	message.reply(status_codes::OK, response.toString(), U("application/json"));
}