// VehicleServices.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "crab_headers.h"
#include "WSVehicleSearch.h"
#include "common/IniReader.h"

using namespace crab;

//
// To start the server, run the below command with admin privileges:
// BlackJack_Server.exe <port>
// If port is not specified, will listen on 34568
//
#ifdef _WIN32
int wmain(int argc, wchar_t *argv[])
#else
int main(int argc, char *argv[])
#endif
{	
	IniReader iniReader;
	iniReader.read("app.ini");
	std::string port;
	iniReader.get("server", "port", port);
	int iPort = atoi(port.c_str());
	if (iPort <= 0) {
		iPort = 12345;
	}

	ServiceEngine* engine = ServiceEngine::getInstance();
	engine->setListenPort(iPort);

	engine->setHandler(U("/vehicles/{registration_number}"), std::make_shared<WSVehicleSeach>() );
	engine->setHandler(U("/vehicles/"), std::make_shared<WSVehicleSeach>());

	WSVehicleSeach::initialize();

	try {
		engine->run();
	}
	catch (std::exception e) {
		std::cout << "Cannot run the server due to: " << e.what() << std::endl;
		std::string line;
		std::getline(std::cin, line);
		WSVehicleSeach::uninitialize();
		return -1;
	}
	std::cout << "Server listening at port: " << iPort << std::endl;
	std::cout << "Press ENTER to exit." << std::endl;

	std::string line;
	std::getline(std::cin, line);

	engine->stop();

	WSVehicleSeach::uninitialize();
	return 0;
}
