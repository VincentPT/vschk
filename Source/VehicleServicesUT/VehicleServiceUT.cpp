#include "stdafx.h"
#include "CppUnitTest.h"
#include "VehicleDAO\VehicleDAO.h"
#include <tchar.h>
#include <locale>         // std::locale, std::touppe
#include <algorithm>
#include "common\string_util.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VehicleServicesUT
{
	TEST_CLASS(VehicleServicesUT)
	{
	public:
		TEST_METHOD(TestRegistrationNotFound1)
		{
			StolenVehicleDAO dao;
			dao.connectToDatabase();
			TSTRING registration(__T("29A-000.0"));
			auto result = dao.findVehicle(&registration, nullptr, nullptr, nullptr);

			Assert::IsTrue(result.get() == nullptr || result->size() == 0, L"it should be no vehicle found");
			dao.disconnectToDatabase();
		}

		TEST_METHOD(TestRegistrationNotFound2)
		{
			StolenVehicleDAO dao;
			dao.connectToDatabase();
			TSTRING registration(__T("29A-000.0"));
			TSTRING vehicle_make(__T("BMW"));
			auto result = dao.findVehicle(&registration, &vehicle_make, nullptr, nullptr);

			Assert::IsTrue(result.get() == nullptr || result->size() == 0, L"it should be no vehicle found");
			dao.disconnectToDatabase();
		}

		TEST_METHOD(TestRegistrationFound1)
		{
			StolenVehicleDAO dao;
			dao.connectToDatabase();
			TSTRING registration(__T("29A-000.03"));
			auto result = dao.findVehicle(&registration, nullptr, nullptr, nullptr);

			Assert::IsTrue(result.get() != nullptr && result->size() == 1, L"it should be found only one vehicle");

			auto& vehicle = result->front();
			Assert::AreEqual(registration, vehicle.getVehicleRegistration(), L"one record found but not match the query");

			dao.disconnectToDatabase();
		}

		TEST_METHOD(TestRegistrationFound2)
		{
			StolenVehicleDAO dao;
			dao.connectToDatabase();
			TSTRING registration(__T("29a-000.03"));
			auto result = dao.findVehicle(&registration, nullptr, nullptr, nullptr);

			Assert::IsTrue(result.get() != nullptr && result->size() == 1, L"it should be found only one vehicle");

			auto& vehicle = result->front();
			
			auto registration_result = vehicle.getVehicleRegistration();

			Assert::AreEqual(toUpper(registration), toUpper(registration_result), L"one record found but not match the query");
			dao.disconnectToDatabase();
		}

		TEST_METHOD(TestRegistrationFound3)
		{
			StolenVehicleDAO dao;
			dao.connectToDatabase();
			TSTRING registration(__T("29a-000.03"));
			TSTRING vehicle_make(__T("BMW"));
			auto result = dao.findVehicle(&registration, &vehicle_make, nullptr, nullptr);

			Assert::IsTrue(result.get() != nullptr && result->size() == 1, L"it should be found only one vehicle");

			auto& vehicle = result->front();

			auto registration_result = vehicle.getVehicleRegistration();

			Assert::AreEqual(toUpper(registration), toUpper(registration_result), L"one record found but not match the query");
			dao.disconnectToDatabase();
		}

		TEST_METHOD(TestRegistrationFound4)
		{
			StolenVehicleDAO dao;
			dao.connectToDatabase();
			TSTRING vehicle_model(__T("230i Couple"));
			auto result = dao.findVehicle(nullptr, nullptr, &vehicle_model, nullptr);

			Assert::IsTrue(result.get() != nullptr && result->size() == 1, L"it should be found only one vehicle");

			auto& vehicle = result->front();

			auto model_result = vehicle.getVehicleModel();

			Assert::AreEqual(toUpper(vehicle_model), toUpper(vehicle_model), L"one record found but not match the query");
			dao.disconnectToDatabase();
		}

		TEST_METHOD(TestRegistrationFound5)
		{
			StolenVehicleDAO dao;
			dao.connectToDatabase();
			TSTRING vehicle_owner(__T("Anh nguyen"));
			auto result = dao.findVehicle(nullptr, nullptr, nullptr, &vehicle_owner);

			Assert::IsTrue(result.get() != nullptr && result->size() == 1, L"it should be found only one vehicle");

			auto& vehicle = result->front();
			auto& ownerObj = vehicle.getVehicleOwner();

			Assert::IsTrue(ownerObj.get() != nullptr, L"Owner object should not be null");
			auto ownerName = ownerObj->getName();

			Assert::AreEqual(toUpper(vehicle_owner), toUpper(ownerName), L"one record found but not match the query");
			dao.disconnectToDatabase();
		}
	};
}