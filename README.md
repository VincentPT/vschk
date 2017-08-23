# vschk
Vehicle Stolen Check Solution
This solution is a simple system for searching stolen cars.

Technology use:
 + mongodb cloud for storing database.
 + Casablanca C++ REST SDK for build search vehicle services.
 + Webtoolkit 3.3.7.
 + C++

I. PREPARE DEVELOPMENT ENVIRONMENT
	1. Visual studio 2015.
	2. Windows 7 or above.
	3. Webtoolkit 3.3.7 or above
	  (download and install Wt-3.3.7-msvs2015-Windows-x64-SDK.exe from https://github.com/emweb/wt/releases)	
	4. A PC can connect to internet.
		For Compiling: At first time, when you build the solution, it need download some dependency packages from internet.
		For Running and Testing: If you choose cloud database server, the application need connect to internet to run.

II. INITIALIZE DATABASE
The solution is using mongodb cloud and the database is already initalized.
Incase you want to build database server yourself.
Do following steps.

	1. Install MongoDB server. (optional)
	   Incase, you use my mongo cloud server, this step should be skipped.
	   Or goto bellow link to install a community mongodb server or setup and database as services in cloud.(depend on you).
	   https://www.mongodb.com/
	   
	2. Install MongoDB client.
		go to bellow link and install Comunity Sever package but choose only client to install.
		https://www.mongodb.com/
		
	3. Connect to server.
		Incase, you use my database. open command line and run following command.
		mongo "mongodb://cluster0-shard-00-00-d2qec.mongodb.net:27017,cluster0-shard-00-01-d2qec.mongodb.net:27017,cluster0-shard-00-02-d2qec.mongodb.net:27017/test?replicaSet=Cluster0-shard-0" --authenticationDatabase admin --ssl --username dbadmin --password mydbadmin
		
		This server will be available for a serveral months.
		
	4. Select database.
		run command:
		use <databse_name>
		
	5. Create collection schema.
		Following command should be run after select a databse.
		db.createCollection( "stolen_cars",
		   { validator: { $and:
			  [
				 { Vehicle_Registration: { $type: "string", $exists: true}},
				 { Vehicle_Make: { $type: "string" } },
				 { Vehicle_Model: { $type: "string" } },
				 { Vehicle_Owner: { $type: "object" } },
				 { "Vehicle_Owner.name": { $type: "string" } },
				 { "Vehicle_Owner.number": { $type: "string" } },
				 { "Vehicle_Owner.address": { $type: "string" } }
			  ]
		   }
		} );

	6. Create initalized data.
		db.stolen_cars.insert({Vehicle_Registration:'29A-000.03',Vehicle_Make:'BMW', Vehicle_Model:'230i Couple', Vehicle_Owner:{name:"Anh nguyen",number:"0123456789",address:"12 Dong Khoi Street, Ho Chi Minh city, Viet Nam"}});
		db.stolen_cars.insert({Vehicle_Registration:'51A-178.12',Vehicle_Make:'Ford', Vehicle_Model:'Focus RS', Vehicle_Owner:'Vincent Pham');
		db.stolen_cars.insert({Vehicle_Registration:'50C-17-15',Vehicle_Make:'BMW', Vehicle_Model:'X3 xDrive45i', Vehicle_Owner:'Trung Nguyen');
		db.stolen_cars.insert(Vehicle_Registration:'12SA-3456',Vehicle_Make:'Toyota', Vehicle_Model:'Avalon', Vehicle_Owner:'Quoc Hoang');
		db.stolen_cars.insert(Vehicle_Registration:'34BC-3465',Vehicle_Make:'Ford', Vehicle_Model:'Fiesta ST', Vehicle_Owner:'Quoc Hoang');
		db.stolen_cars.insert(Vehicle_Registration:'56FE-3546',Vehicle_Make:'Ford', Vehicle_Model:'FT', Vehicle_Owner:'Hanh Nguyen');
		db.stolen_cars.insert(Vehicle_Registration:'78GH-3654',Vehicle_Make:'Toyota', Vehicle_Model:'Camry', Vehicle_Owner:'Chien Pham');

III. HOW TO BUILD AND RUN.
	1. Set environment variable for Webtoolkit SDK
		set WTK_SDK_DIR to root folder of Webtoolkit
		example: C:\Program Files\Wt 3.3.7 msvs2015 x64
	
	2. Select support build platform.
		The solution only support for x64 platform. So, After Open solution in Visual Studio 2015.
		You should select x64 platform.
		After build application will be deploy in bellow folders;
		+ .\Code\VehicleManager\VehicleServices\bin\
		+ .\Code\VehicleManager\VehicleWebApp\bin\
		
	3. Make sure all configuration is set correctly.
		1. Check if database setting in file .\Code\VehicleManager\VehicleServices\bin\app.ini is correct.
			They should be setting of your databse.
			
		2. Check if services setting in file .\Code\VehicleManager\VehicleWebApp\bin\app.ini is correct.
			It should corresponding with host information of services application.
		
	4. Run
		You can run the applications through Visual Studio.
		1. Run Web Services application.
			run file VehicleServices.exe in folder .\Code\VehicleManager\VehicleServices\bin\
		2. Run Web App
			run_server.bat in folder .\Code\VehicleManager\VehicleServices\bin\
			open browser and browse to Web Application's host.
			The Web Application's port can be changed in file run_server.bat.
		3. Run Unit Test project.
			Make sure you are setting x64 platform before run the unit test.
		
IV. Assumptions
	+ All required database fields is assuming is string except Vehicle_Owner.
      It is a json object that contain some useful information about a Vehicle Owner.
	  In futrure, we can use it to contact the person who lost their car.
	+ Allow case insentive search.
	+ The webservice support RESTful Webservices.
	+ the service used in the solution is POST /vehicles, with body is Json object contain field's values to search.
	  beside that, the Web Services also offer a reverser API is GET /vehicles/{vehicle_registration}. It is considered as a referece for who
	  want to continue develop on this solution.

V. Problems.
	During development time, I've faced some problems that take time to resolved.
	1. Cannot use one connection instance for database to speed up time to response.
		For VehicleServices app. It's use MongoDB C++ driver to connect to database.
		But if we use one instane accross multiple thread. The application may crashs.
		So, current I accept to use separate connection instance for each thread.
		It is spent much time to handsake with server.
		
		I can resolved this problem by using cached connection instance to reduce handshake time.
	
	2. Cannot use http client of Webtoolkit for VehicleWebApp project.
		The http client of Webtoolkit is asynchonous APIs and the webpage will not update when response is return in another thread.
		I've tried to use many techniques like mutex and condition variable to turn it to synchonous API. But it make the program hangup.
		So, finnaly I must use http client of CPP REST SDK.
		This work properly but make the program size is bigger.
	
VI. Testing
	During development I use cpp unit test and post man to test the solution.
	Make sure you have internet connection in case want to connect to database or remote Vehicle Web services.
