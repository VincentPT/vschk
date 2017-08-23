#pragma once
#ifdef VEHICLEOBJECTS_EXPORTS
#define VEHICLEOBJECTS_API __declspec(dllexport)
#else
#define VEHICLEOBJECTS_API __declspec(dllimport)
#endif
#include <string>
#ifdef _UNICODE
typedef std::wstring TSTRING;
#else
typedef std::string TSTRING;
#endif