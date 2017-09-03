#define CATCH_CONFIG_MAIN

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_RUNNER
#endif

#include "VehicleServicesUTMacros.h"
#include "VehicleDAO/VehicleDAO.h"
#include <locale>         // std::locale, std::touppe
#include <algorithm>
#include "common/string_util.hpp"

TEST_METHOD(TestRegistrationNotFound1)
{
	StolenVehicleDAO dao;
	dao.connectToDatabase();
	TSTRING registration(STRING_T("29A-000.0"));
	auto result = dao.findVehicle(&registration, nullptr, nullptr, nullptr);
	TEST_ASSERT(result.get() == nullptr || result->size() == 0, "it should be no vehicle found");
	dao.disconnectToDatabase();
}

TEST_METHOD(TestRegistrationNotFound2)
{
	StolenVehicleDAO dao;
	dao.connectToDatabase();
	TSTRING registration(STRING_T("29A-000.0"));
	TSTRING vehicle_make(STRING_T("BMW"));
	auto result = dao.findVehicle(&registration, &vehicle_make, nullptr, nullptr);

	TEST_ASSERT(result.get() == nullptr || result->size() == 0, "it should be no vehicle found");
	dao.disconnectToDatabase();
}

TEST_METHOD(TestRegistrationFound1)
{
	StolenVehicleDAO dao;
	dao.connectToDatabase();
	TSTRING registration(STRING_T("29A-000.03"));
	auto result = dao.findVehicle(&registration, nullptr, nullptr, nullptr);

	TEST_ASSERT(result.get() != nullptr && result->size() == 1, "it should be found only one vehicle");

	auto& vehicle = result->front();
	TEST_ASSERT(registration == vehicle.getVehicleRegistration(), "one record found but not match the query");

	dao.disconnectToDatabase();
}

TEST_METHOD(TestRegistrationFound2)
{
	StolenVehicleDAO dao;
	dao.connectToDatabase();
	TSTRING registration(STRING_T("29a-000.03"));
	auto result = dao.findVehicle(&registration, nullptr, nullptr, nullptr);

	TEST_ASSERT(result.get() != nullptr && result->size() == 1, "it should be found only one vehicle");

	auto& vehicle = result->front();
			
	auto registration_result = vehicle.getVehicleRegistration();

	TEST_ASSERT(toUpper(registration) == toUpper(registration_result), "one record found but not match the query");
	dao.disconnectToDatabase();
}

TEST_METHOD(TestRegistrationFound3)
{
	StolenVehicleDAO dao;
	dao.connectToDatabase();
	TSTRING registration(STRING_T("29a-000.03"));
	TSTRING vehicle_make(STRING_T("BMW"));
	auto result = dao.findVehicle(&registration, &vehicle_make, nullptr, nullptr);

	TEST_ASSERT(result.get() != nullptr && result->size() == 1, "it should be found only one vehicle");

	auto& vehicle = result->front();

	auto registration_result = vehicle.getVehicleRegistration();

	TEST_ASSERT(toUpper(registration) == toUpper(registration_result), "one record found but not match the query");
	dao.disconnectToDatabase();
}

TEST_METHOD(TestRegistrationFound4)
{
	StolenVehicleDAO dao;
	dao.connectToDatabase();
	TSTRING vehicle_model(STRING_T("230i Couple"));
	auto result = dao.findVehicle(nullptr, nullptr, &vehicle_model, nullptr);

	TEST_ASSERT(result.get() != nullptr && result->size() == 1, "it should be found only one vehicle");

	auto& vehicle = result->front();

	auto model_result = vehicle.getVehicleModel();

	TEST_ASSERT(toUpper(vehicle_model) == toUpper(vehicle_model), "one record found but not match the query");
	dao.disconnectToDatabase();
}

TEST_METHOD(TestRegistrationFound5)
{
	StolenVehicleDAO dao;
	dao.connectToDatabase();
	TSTRING vehicle_owner(STRING_T("Anh nguyen"));
	auto result = dao.findVehicle(nullptr, nullptr, nullptr, &vehicle_owner);

	TEST_ASSERT(result.get() != nullptr && result->size() == 1, "it should be found only one vehicle");

	auto& vehicle = result->front();
	auto& ownerObj = vehicle.getVehicleOwner();

	TEST_ASSERT(ownerObj.get() != nullptr, "Owner object should not be null");
	auto ownerName = ownerObj->getName();

	TEST_ASSERT(toUpper(vehicle_owner) == toUpper(ownerName), "one record found but not match the query");
	dao.disconnectToDatabase();
}