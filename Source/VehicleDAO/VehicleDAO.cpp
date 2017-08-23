// VehicleDAO.cpp : Defines the exported functions for the DLL application.
//
#include "VehicleDAO.h"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <thread>

#include <string>
#include <locale>
#include <codecvt>
#include <iostream>
#include "common\IniReader.h"

#include <mongocxx/exception/query_exception.hpp>

#ifdef _UNICODE
#define DECODE_UTF8(s) decodeUTF8(s)
#define ENCODE_UTF8(s) encodeUTF8(s)
#else
#define ENCODE_UTF8(s) s
#define DECODE_UTF8(s) s
#endif

// This is the constructor of a class that has been exported.
// see VehicleDAO.h for the class definition
StolenVehicleDAO::StolenVehicleDAO()
{
}

StolenVehicleDAO::~StolenVehicleDAO(void) {

}

std::wstring decodeUTF8(const std::string& utf8_str) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.from_bytes(utf8_str);
}

std::string encodeUTF8(const std::wstring& unicode_str) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.to_bytes(unicode_str);
}

static mongocxx::instance* s_clientInstance = nullptr;
static mongocxx::client* s_connectionInstance = nullptr;

bool StolenVehicleDAO::connectToDatabase() {
	s_clientInstance = new mongocxx::instance();
	//s_connectionInstance = new mongocxx::client( mongocxx::uri("mongodb://dbadmin:mydbadmin@cluster0-shard-00-00-d2qec.mongodb.net:27017,cluster0-shard-00-01-d2qec.mongodb.net:27017,cluster0-shard-00-02-d2qec.mongodb.net:27017/test?ssl=true&replicaSet=Cluster0-shard-0&authSource=admin") );
	return true;
}

bool StolenVehicleDAO::disconnectToDatabase() {
	//if(s_connectionInstance) delete s_connectionInstance;
	if(s_clientInstance) delete s_clientInstance;
	return true;
}

std::shared_ptr<std::list<StolenVehicleInfo>> findVehicle(const bsoncxx::builder::stream::document& filterObject) {
	//if (s_connectionInstance == nullptr) return nullptr;
	IniReader config_reader;
	config_reader.read("app.ini");
	std::string connection_settings = "mongodb://dbadmin:mydbadmin@cluster0-shard-00-00-d2qec.mongodb.net:27017,cluster0-shard-00-01-d2qec.mongodb.net:27017,cluster0-shard-00-02-d2qec.mongodb.net:27017/test?ssl=true&replicaSet=Cluster0-shard-0&authSource=admin";
	std::string database = "test";
	std::string collection_name = "stolen_cars";

	config_reader.get("database", "connection_settings", connection_settings);
	config_reader.get("database", "name", database);
	config_reader.get("database", "collection", collection_name);

	mongocxx::client conn(mongocxx::uri(connection_settings.c_str()));
	auto collection = conn[database][collection_name];
	
	auto vehicleCollection = std::make_shared<std::list<StolenVehicleInfo>>();
	auto filter = filterObject.view();
	
	int maxTryCount = 10;
	while (maxTryCount)
	{
		try {
			auto cursor = collection.find(filter);
			for (auto&& doc : cursor) {
				auto json_str = bsoncxx::to_json(doc);
				StolenVehicleInfo dummy;
				vehicleCollection->push_back(dummy);
				auto& vehicleObj = vehicleCollection->back();
				vehicleObj.fromJson(DECODE_UTF8(json_str));
			}
			break;
		}
		catch (mongocxx::query_exception& e) {
			std::cout << e.what() << std::endl;
			vehicleCollection->clear();			
			maxTryCount--;
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(3s);
		}
	}
	
	return vehicleCollection;
}

std::shared_ptr<std::list<StolenVehicleInfo>> StolenVehicleDAO::findVehicleByRegistrationNumber(const TSTRING& registration_number) {
	auto builder = bsoncxx::builder::stream::document();
	std::string search_value = ENCODE_UTF8(registration_number);
	builder << "Vehicle_Registration" << bsoncxx::types::b_regex("^" + search_value + "$", "i");
	
	return ::findVehicle(builder);
}

std::shared_ptr<std::list<StolenVehicleInfo>> StolenVehicleDAO::findVehicle(
	const TSTRING* vehicle_registration,
	const TSTRING* vehicle_make,
	const TSTRING* vehicle_model,
	const TSTRING* owner_name) {
	
	auto builder = bsoncxx::builder::stream::document();

	if (vehicle_registration) {
		builder << "Vehicle_Registration" << bsoncxx::types::b_regex("^" + ENCODE_UTF8(*vehicle_registration) + "$","i");
	}
	if (vehicle_make) {
		builder << "Vehicle_Make" << bsoncxx::types::b_regex("^" + ENCODE_UTF8(*vehicle_make) + "$", "i");
	}
	if (vehicle_model) {
		builder << "Vehicle_Model" << bsoncxx::types::b_regex("^" + ENCODE_UTF8(*vehicle_model) + "$", "i");
	}
	if (owner_name) {
		builder << "Vehicle_Owner.name" << bsoncxx::types::b_regex("^" + ENCODE_UTF8(*owner_name) + "$", "i");
	}

	return ::findVehicle(builder);
}