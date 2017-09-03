#ifndef VEHICLE_SERVICES_UT_MACROS
#define VEHICLE_SERVICES_UT_MACROS
#include <catch.hpp>

#define _TEST_METHOD(x) TEST_CASE(#x)
#define TEST_METHOD(x) _TEST_METHOD(x)

#define TEST_ASSERT(condition, message) if(!(condition)) FAIL(message)

#if _WIN32
#define STRING_T(x) L## x 
#else
#define STRING_T(x) x
#endif

#endif // VEHICLE_SERVICES_UT_MACROS

