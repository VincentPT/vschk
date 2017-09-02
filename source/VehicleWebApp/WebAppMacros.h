#pragma once
#define USE_ASYNCHRONOUS_REQUEST 0

#include <string>

#if _WIN32
typedef std::wstring TSTRING;
#define STRING2T(x) Wt::WString::fromUTF8(x)
#define WSTRING2T(x) x
#define _MAKE_TSTR(x) L ## x
#define JSON_VALUE_TO_TSTRING(x) (x).operator const Wt::WString &()
#else
typedef std::string TSTRING;
#define STRING2T(x) x
#define WSTRING2T(x) x.toUTF8()
#define _MAKE_TSTR(x) x
#define JSON_VALUE_TO_TSTRING(x) (x).operator std::string()
#endif
#define MAKE_TSTR(x) _MAKE_TSTR(x)