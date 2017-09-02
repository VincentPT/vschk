#pragma once
#ifdef _WIN32
    #ifdef VEHICLEOBJECTS_EXPORTS
        #define VEHICLEOBJECTS_API __declspec(dllexport)
    #else
        #define VEHICLEOBJECTS_API __declspec(dllimport)
    #endif //VEHICLEOBJECTS_EXPORTS
#else //_WIN32
    #define VEHICLEOBJECTS_API
#endif //_WIN32
#include <string>
#ifdef _WIN32
#define _UNICODE_STRING
typedef std::wstring TSTRING;
#else
typedef std::string TSTRING;
#endif