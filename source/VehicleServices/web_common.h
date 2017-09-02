#pragma once
#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

namespace crab {
	typedef utility::string_t TSTRING;
}

#ifdef _UTF16_STRINGS
#define TO_STRING_T(x) std::to_wstring(x)
#define CONSOLE_OUT_T std::wcout
#else
#define TO_STRING_T(x) std::to_string(x)
#define CONSOLE_OUT_T std::cout
#endif // _UTF16_STRINGS