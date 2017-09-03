# vschk
This is a training project which make a simple searching system for stolen cars.

## Getting Started

The project is focus on traning C++ and it uses some following related technologies.
* Mongodb for storing database.
* Casablanca C++ REST SDK for building vehicle searching services.
* Webtoolkit 3.3.7 for building web UI for vehicle searching system.
* C++ 14.

### Prerequisites
    #### Windows
    * Visual studio 2012, 2015. 
    * CMake 3.2 or above
    * Webtoolkit 3.3.7 or above
    * Casablanca C++ REST SDK 2.9.1
    * Boost 1.64
    * mongo-c-driver 1.7.0
    * MongoDB C++11 Driver 3.1.3
    
    #### Linux
    * GCC or equivalent C++ compiler that support C++14.
    * CMake 3.2 or above
    * Webtoolkit 3.3.7 or above
    * Casablanca C++ REST SDK 2.9.1
    * mongo-c-driver 1.7.0
    * MongoDB C++11 Driver 3.1.3

### Install development environment
    You can install all prerequisite library yourself and specify the library when building projects or you can do some following steps to install them.
    #### Windows
    * Webtoolkit
      (download and install Wt-3.3.7-msvs2015-Windows-x64-SDK.exe from https://github.com/emweb/wt/releases)
      
    * Casablanca C++ REST SDK 2.9.1 & Boost 1.64        
      run install-dependencies.bat in source folder, its will invoke nuget to download these libraries to source\packages folder.
      Current Nuget support built-in C++ REST SDK 2.9.1 lib and dlls file for Visual Studio 2012 and Visual Studio 2015
      
    * mongo-c-driver 1.7.0 & MongoDB C++11 Driver 3.1.3
      These libraries are already built and place in project folder(In source\external).

    #### Linux
    * Webtoolkit(this installation will have no examples and documents)
      On terminal, run following command.
      $ sudo apt-get install witty witty-dev
      
    * Casablanca C++ REST SDK 2.9.1
      On terminal, run following command.
      $ sudo apt-get install libcpprest-dev
      
    * mongo-c-driver 1.7.0
       link: https://github.com/mongodb/mongo-c-driver/releases/download/1.7.0/mongo-c-driver-1.7.0.tar.gz
       1. Install optional dependencies(SSL and Cyrus SASL)
          $ sudo apt-get install pkg-config libssl-dev libsasl2-dev
       2. Download and install
          $ wget <mongo-c-driver download link above>
          $ tar xzf mongo-c-driver-1.7.0.tar.gz
          $ cd mongo-c-driver-1.7.0
          $ ./configure --disable-automatic-init-and-cleanup
          
          after these step, the library will be configured to install on /usr/include and /usr/lib
       3. Build and install the library
          $ make
          $ sudo make install
       For detail information, go to this link and read installation instructions.
       http://mongoc.org/libmongoc/current/installing.html
       
    * MongoDB C++11 Driver 3.1.3
      link: https://github.com/mongodb/mongo-cxx-driver/archive/r3.1.3.tar.gz
       1. Download and install
          $ curl -OL <above download link>
          $ tar -xzf r3.1.3.tar.gz
          $ cd mongo-cxx-driver-r3.1.3/build
          
       2. Configure the driver.
          Remember that on above steps of installing mongo-c-driver, the driver would be installed at /usr/include and /usr/lib.
          So, LIBMONGOC_DIR and LIBBSON_DIR should be the same and the c++ driver should place at the same place for easy in use in the future.
          
          $ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DLIBMONGOC_DIR=/usr DLIBBSON_DIR=/usr DBSONCXX_POLY_USE_MNMLSTC=1 ..
          We also set BSONCXX_POLY_USE_MNMLSTC=1 and don't forget the last '..' on the command.
          
       3. Build and install the library
          $ make
          $ sudo make install
       For detail information, go to this link and read installation instructions.
       https://mongodb.github.io/mongo-cxx-driver/mongocxx-v3/installation/
       
## Initialize Database
    The solution is using mongodb cloud and the database is already initalized.
    Incase you want to build database server yourself.
    Do following steps.
    1. Install MongoDB server. (optional)
       Incase, you use mongo cloud server, this step should be skipped.
       Or goto bellow link to install a community mongodb server or setup and database as services in cloud.(depend on you).
       https://www.mongodb.com/
           
    2. Install MongoDB client.
       go to bellow link and install Comunity Sever package but choose only client to install.
       https://www.mongodb.com/
            
    3. Connect to server using mongo client tool.

    4. Select database.
       run command:
       use <databse_name>
            
    5. Create collection schema & initalize data.
       run commands on two section in file ./SQL/datase_scripts.txt

## Build.
    ### Windows.
        1. Download dependencies.           
           If you are already have cpprestsdk 2.9.1 and boots 1.64 this step should be skipped.
           > install-dependencies.bat

        2. Configure project.
           Before run the command you must ensure that Webtoolkit is already installed in correct platform(x64).
           if you choose to install prerequisite libraries by following instructions in above steps. You can simple run below command.
           
           > cd build
           > cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_INSTALL_PREFIX=./bin -DWT_INSTALLED_DIR="<Webtoolkit Root Path>" ..
           Example: cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_INSTALL_PREFIX=./bin -DWT_INSTALLED_DIR="C:/Program Files/Wt 3.3.7 msvs2015 x64" ..           
            
           In case you have your own Webtoolkit, cpprestsdk 2.9.1 and boots 1.64 following variable must be set to run configure command.
           using -D<variable_name> to set it through command line.

            * CPPRESTSDK_INCLUDE_DIR
            * CPPRESTSDK_LIB_DIR
                this directory should have the same structure at bellow.
                |
                -x86
                |   + Debug
                |   + Release
                -x64
                    + Debug
                    + Release
                and on each leaf folder, it should contain .lib and dll files.
                
            * BOOST_INSTALLED_DIR
                this directory should have the same structure at bellow.
                |                
                -include
                    + boost

            * WT_INSTALLED_DIR
                this directory should have the same structure at bellow.
                |
                -bin                
                -include
                -lib
                bin folder should contain dll files for Debug and Release config types.
                lib folder should contain lib files for Debug and Release config types.
        3. Build project.
            Open your project in Visual Studio and build the the target ALL_BUILD.

        4. Install.
            Open your project in Visual Studio and build the the target INSTALL.
            this will install applications on .\bin\windows, now everything is almost done.
        
        If you are using visual studio 2015. You can simply run three bat files in folder build.
        > cd build
        > configure.bat
        > build.bat
        > install.bat
    
    ### Linux.
        1. Configure project.
           Before run the command you must ensure that Webtoolkit is already installed in correct platform(x64).
           if you choose to install prerequisite libraries by following instructions in above steps. You can simple run below command.
           
           $ cd build
           $ configure
           $ make
           $ install
            
           In case you have your own Webtoolkit, cpprestsdk 2.9.1 and boots 1.64 following variable must be set to run configure command.
           using -D<variable_name> to set it through command line.

            * CPPRESTSDK_INCLUDE_DIR
            * CPPRESTSDK_LIB_DIR
            * BOOST_INSTALLED_DIR
            * WT_INCLUDE_DIR
            * WT_LIB_DIR        
## Run.
    After Prepare database and build project successfully. Now, It is time to run the apps.
    Before run the apps, we must set some require parameters.
    
    * Open app.ini in folder ./bin/windows/VehicleServices or ./bin/linux/VehicleServices.
        set your mongodb connection string through variable 'connection_settings value'.
        specify listen port for searching services on your system.
    
    * Open app.ini in folder ./bin/windows/VehicleWebApp or ./bin/linux/VehicleWebApp.
        specify searching services connection through variable 'vehicle_search_services'
        its value has format http://<searching services ip address>:<searching services port>/vehicles
    
    * Open run-web-app.bat in folder ./bin/windows/VehicleWebApp or run-web-app in folder ./bin/linux/VehicleWebApp.
        set the port to access the web app here: --http-port 8080
        
    Run the searching services:
        On Windows:
        > VehicleServices.exe
        On Linux:
        $ ./VehicleServices
    
    Run the Web app:
        On Windows:
        > run-web-app.bat
        On Linux:
        $ ./run-web-app        
        
    Now, open your browser and access to the web page through the url that you set.(the url base on default setting is: localhost:8080)
    try to fill some fields and click 'Search'.
    If the items found, they should be displayed in the web page.
    
## Testing
    * Curent, the project supports run Unit Test on Windows by using Cpp Unit Test.
    * Make sure you have internet connection in case want to connect to database or remote Vehicle Web services.
      And remeber set the setting for searching services in file .\source\VehicleServicesUT\app.ini before run the test.

## Authors
* **Vincent Pham** - [VincentPT](https://github.com/VincentPT)

## License
This project is licensed under the MIT License 
