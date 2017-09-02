#include <Wt/WApplication>
#include <Wt/WServer>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WStandardItem>
#include <Wt/WTableView>
#include <Wt/WEnvironment>
#include <Wt/WStandardItemModel>
#include <Wt/WPanel>
#include <Wt/WTable>
#include <Wt/WCheckBox>

#include <Wt/Http/Client>
#include <Wt/Http/Request>
#include <Wt/Http/Response>

#include <Wt/Json/Array>
#include <Wt/Json/Object>
#include <Wt/Json/Value>
#include "RESTResponse.h"
#include "StolenVehicleInfo.h"

#include <mutex>
#include <thread>
#include <condition_variable>

#include "HttpRequester.h"
#include "common\IniReader.h"

// c++0x only, for std::bind
// #include <functional>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

using namespace Wt;

/*
* A simple Vehicle searcher application class which demonstrates
* searching vehicles in a mongo database.
*/
class VehicleApplication : public WApplication
{
public:
	VehicleApplication(const WEnvironment& env);

private:
	WLineEdit* _vehicle_registration_input;
	WLineEdit* _vehicle_make_input;
	WLineEdit* _vehicle_model_input;
	WLineEdit* _vehicle_owner_input;

	WCheckBox* _used_vehicle_registration;
	WCheckBox* _used_vehicle_make_input;
	WCheckBox* _used_vehicle_model_input;
	WCheckBox* _used_vehicle_owner_input;

	WText* _message;

	WTableView* _resultView;

	void doSearch();
#if USE_ASYNCHRONOUS_REQUEST
	void handleSerachResult(Wt::Http::Client* client,
		boost::system::error_code err,
		const Wt::Http::Message& response);
#endif
};

/*
* The env argument contains information about the new session, and
* the initial request. It must be passed to the WApplication
* constructor so it is typically also an argument for your custom
* application constructor.
*/
VehicleApplication::VehicleApplication(const WEnvironment& env)
	: WApplication(env)
{
	/* application title */
	setTitle("Stolen Vehicle Check");

	setCssTheme("polished");
	messageResourceBundle().use(appRoot() + "charts");

	/* Search Vehicle */
	WTable *searchSetting = new WTable();
	searchSetting->setMargin(WLength::Auto, Left | Right);

	int row = 0;
	
	searchSetting->elementAt(row, 0)->addWidget(new WText("Vehicle Registration:"));
	_vehicle_registration_input = new WLineEdit(searchSetting->elementAt(row, 1));
	_used_vehicle_registration = new WCheckBox(searchSetting->elementAt(row, 2));
	++row;

	searchSetting->elementAt(row, 0)->addWidget(new WText("Vehicle Make:"));
	_vehicle_make_input = new WLineEdit(searchSetting->elementAt(row, 1));
	_used_vehicle_make_input = new WCheckBox(searchSetting->elementAt(row, 2));
	++row;

	searchSetting->elementAt(row, 0)->addWidget(new WText("Vehicle Model:"));
	_vehicle_model_input = new WLineEdit(searchSetting->elementAt(row, 1));
	_used_vehicle_model_input = new WCheckBox(searchSetting->elementAt(row, 2));
	++row;

	searchSetting->elementAt(row, 0)->addWidget(new WText("Vehicle Owner"));
	_vehicle_owner_input = new WLineEdit(searchSetting->elementAt(row, 1));
	_used_vehicle_owner_input = new WCheckBox(searchSetting->elementAt(row, 2));
	++row;

	_used_vehicle_registration->setChecked(true);

	_message = new WText("");	
	searchSetting->elementAt(row, 0)->addWidget(_message);
	auto button = new WPushButton("Search");	
	searchSetting->elementAt(row, 1)->addWidget(button);

	for (int i = 0; i < searchSetting->rowCount(); ++i) {
		searchSetting->elementAt(i, 0)->setStyleClass("tdhead");
		searchSetting->elementAt(i, 1)->setStyleClass("tddata");
	}

	WPanel *p = new WPanel(root());
	p->setTitle("Search Vehicle");
	p->setCentralWidget(searchSetting);
	p->setCollapsible(false);
	p->setMargin(WLength::Auto, Left | Right);
	p->resize(400, WLength::Auto);
	p->setMargin(20, Top | Bottom);

	_vehicle_registration_input->enterPressed().connect(boost::bind(&VehicleApplication::doSearch, this));
	_vehicle_make_input->enterPressed().connect(boost::bind(&VehicleApplication::doSearch, this));
	_vehicle_model_input->enterPressed().connect(boost::bind(&VehicleApplication::doSearch, this));
	_vehicle_owner_input->enterPressed().connect(boost::bind(&VehicleApplication::doSearch, this));
	button->clicked().connect(this, &VehicleApplication::doSearch);

	/* Search result */
	WStandardItemModel *model = new WStandardItemModel(0, 0, this);
	model->setItemPrototype(new WStandardItem());
	model->insertColumns(0, 4);
	model->setHeaderData(0, boost::any(Wt::WString::fromUTF8("Vehicle Registration")));
	model->setHeaderData(1, boost::any(Wt::WString::fromUTF8("Vehice Make")));
	model->setHeaderData(2, boost::any(Wt::WString::fromUTF8("Vehice Model")));
	model->setHeaderData(3, boost::any(Wt::WString::fromUTF8("Vehicle Oner")));

	_resultView = new WTableView(root());

	_resultView->setMargin(10, Top | Bottom);
	_resultView->setMargin(WLength::Auto, Left | Right);

	_resultView->setModel(model);
	//table->setSortingEnabled(true);
	//table->setColumnResizeEnabled(true);
	// table->setSelectionMode(ExtendedSelection);
	_resultView->setAlternatingRowColors(true);
	_resultView->setColumnAlignment(0, AlignCenter);
	_resultView->setHeaderAlignment(0, AlignCenter);
	_resultView->setRowHeight(22);
	
	_resultView->setColumnWidth(0, 120);
	_resultView->setColumnWidth(1, 120);
	_resultView->setColumnWidth(2, 120);
	_resultView->setColumnWidth(3, 120);
	_resultView->resize(510, 400);

	useStyleSheet("charts.css");
}

void VehicleApplication::doSearch()
{
	JsonRequestObject search_object;
	if (_used_vehicle_registration->isChecked()) {
		search_object[U(JSON_FILED_REGISTRATION)] = JsonRequestObject::string(_vehicle_registration_input->text());
	}
	if (_used_vehicle_make_input->isChecked()) {
		search_object[U(JSON_FILED_MAKE)] = JsonRequestObject::string(_vehicle_make_input->text());
	}
	if (_used_vehicle_model_input->isChecked()) {
		search_object[U(JSON_FILED_MODEL)] = JsonRequestObject::string(_vehicle_model_input->text());
	}
	if (_used_vehicle_owner_input->isChecked()) {
		search_object[U(JSON_FILED_OWNER)] = JsonRequestObject::string(_vehicle_owner_input->text());
	}

	if (search_object.size() == 0) {
		_message->setText("No filed specified");
		return;
	}

	IniReader config_reader;
	config_reader.read("app.ini");
	std::string uri = "http://localhost:12345/vehicles";
	config_reader.get("services", "vehicle_search_services", uri);
	auto uri_w = WString::fromUTF8(uri);

	/*webpage does not update if use anysnchornous htpp request API*/
#if USE_ASYNCHRONOUS_REQUEST
	Wt::Http::Client *client = new Wt::Http::Client();
	client->setTimeout(15);
	client->setMaximumResponseSize(8192);
	client->done().connect(boost::bind(&VehicleApplication::handleSerachResult, this, client, _1, _2));
	client->get("http://localhost:12345/vehicles/51A-178.12");
#else
	HttpRequester requester;
	crab::client::RESTResponse restResponse;	
	requester.sendPost(uri_w, search_object, [this, &restResponse](const http_response& response) {
		auto result = response.extract_utf8string();
		auto reponseContent = result.get();

		restResponse.fromJson(reponseContent);
	});

	auto model = _resultView->model();
	model->removeRows(0, model->rowCount());

	if (restResponse.getCode() == crab::ResponseCode::Success) {
		auto& result = restResponse.getResult();
		if (result.type() == Wt::Json::ArrayType) {
			Wt::Json::Array vehicles = result;
			int row = 0;
			for (auto it = vehicles.begin(); it != vehicles.end(); it++) {

				auto& jsonValue = *it;
				if (jsonValue.type() == Json::ObjectType) {
					StolenVehicleInfo stolenVehilce;
					JSON_T& vehicle = jsonValue;
					stolenVehilce.fromJsonObject(vehicle);

					auto vehicleRegistration = boost::any(Wt::WString::fromUTF8(stolenVehilce.getVehicleRegistration()));
					auto vehicleMake = boost::any(Wt::WString::fromUTF8(stolenVehilce.getVehicleMake()));
					auto vehicleModel = boost::any(Wt::WString::fromUTF8(stolenVehilce.getVehicleModel()));
					auto vehicleOwner = boost::any(L"");
					auto ownerRef = stolenVehilce.getVehicleOwner();
					if (ownerRef) {
						vehicleOwner = boost::any(Wt::WString::fromUTF8(ownerRef->getName()));
					}

					model->insertRow(row);
					model->setData(row, 0, vehicleRegistration);
					model->setData(row, 1, vehicleMake);
					model->setData(row, 2, vehicleModel);
					model->setData(row, 3, vehicleOwner);
					row++;
				}
			}
		}
	}

	if (model->rowCount()) {
		_message->setText("");
	}
	else {
		_message->setText("No vehicle found");		
	}
#endif
}

#if USE_ASYNCHRONOUS_REQUEST
void VehicleApplication::handleSerachResult(
	Wt::Http::Client* client,
	boost::system::error_code err,
	const Wt::Http::Message& response) {
	if (err || response.status() != 200) {
		std::cerr << "Error: " << err.message() << ", " << response.status() << std::endl;
		return;
	}
	auto reponseContent = response.body();
	crab::client::RESTResponse restResponse;
	restResponse.fromJson(reponseContent);
	
	if (restResponse.getCode() == crab::ResponseCode::Success) {
		auto& result = restResponse.getResult();
		if (result.type() == Wt::Json::ArrayType) {
			Wt::Json::Array vehicles = result;
			auto model = _resultView->model();
			model->removeRows(0, model->rowCount());
			int row = 0;
			for (auto it = vehicles.begin(); it != vehicles.end(); it++) {

				auto& jsonValue = *it;
				if (jsonValue.type() == Json::ObjectType) {
					StolenVehicleInfo stolenVehilce;
					JSON_T& vehicle = jsonValue;
					stolenVehilce.fromJsonObject(vehicle);

					auto vehicleRegistration = boost::any(Wt::WString::fromUTF8(stolenVehilce.getVehicleRegistration()));
					auto vehicleMake = boost::any(Wt::WString::fromUTF8(stolenVehilce.getVehicleMake()));
					auto vehicleModel = boost::any(Wt::WString::fromUTF8(stolenVehilce.getVehicleModel()));
					auto vehicleOwner = boost::any(L"");
					auto ownerRef = stolenVehilce.getVehicleOwner();
					if (ownerRef) {
						vehicleOwner = boost::any(Wt::WString::fromUTF8(ownerRef->getName()));
					}

					model->insertRow(row);
					model->setData(row, 0, vehicleRegistration);
					model->setData(row, 1, vehicleMake);
					model->setData(row, 2, vehicleModel);
					model->setData(row, 3, vehicleOwner);
					row++;
				}
			}
		}
	}
	delete client;
}
#endif

WApplication *createApplication(const WEnvironment& env)
{
	/*
	* You could read information from the environment to decide whether
	* the user has permission to start a new application
	*/
	return new VehicleApplication(env);
}

int main(int argc, char **argv)
{
	/*
	* Your main method may set up some shared resources, but should then
	* start the server application (FastCGI or httpd) that starts listening
	* for requests, and handles all of the application life cycles.
	*
	* The last argument to WRun specifies the function that will instantiate
	* new application objects. That function is executed when a new user surfs
	* to the Wt application, and after the library has negotiated browser
	* support. The function should return a newly instantiated application
	* object.
	*/
	return WRun(argc, argv, &createApplication);
}