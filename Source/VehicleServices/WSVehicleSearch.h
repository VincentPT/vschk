#pragma once

#include "web_common.h"
#include "HttpHandler.h"

class WSVehicleSeach : public crab::HttpHandler
{
public:
	WSVehicleSeach();
	~WSVehicleSeach();

	static bool initialize();
	static bool uninitialize();

	void doGet(http_request& message, const std::vector<crab::TSTRING>& params) override;
	void doPost(http_request& message, const std::vector<crab::TSTRING>& params) override;
};