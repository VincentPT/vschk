#include "VehicleServicesUTMacros.h"
#include "VehicleServices/web_common.h"
#include "VehicleServices/RESTUriParser.h"
using namespace crab;

TEST_METHOD(MakePathSignature_Empty)
{
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U(""));
	TEST_ASSERT(U("") == signPath, "make sign path failed");
}

TEST_METHOD(MakePathSignature_OnlyFlashBegin)
{
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/"));
	TEST_ASSERT(U("") == signPath, "make sign path failed");
}

TEST_METHOD(MakePathSignature_FlashBegin)
{
	TSTRING signPath =  crab::RESTUriParser::makePathSignature(U("/path"));
	TEST_ASSERT(U("path") == signPath, "make sign path failed");
}

TEST_METHOD(MakePathSignature_FlashEnd)
{
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("path/"));
	TEST_ASSERT(U("path") == signPath, "make sign path failed");
}

TEST_METHOD(MakePathSignature_FlashBeginEnd)
{
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/path/"));
	TEST_ASSERT(U("path") == signPath, "make sign path failed");
}

TEST_METHOD(MakePathSignature_MultiBranch)
{
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/path1/path2"));
	TEST_ASSERT(U("path1/path2") == signPath, "make sign path failed");
}

TEST_METHOD(MakePathSignature_MultiBranchWithParamAt1)
{
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/{p1}/path"));
	TEST_ASSERT(U("{0}/path") == signPath, "make sign path failed");
}

TEST_METHOD(MakePathSignature_MultiBranchWithParamAt2)
{
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/path/{p2}"));
	TEST_ASSERT(U("path/{0}") == signPath, "make sign path failed");
}

TEST_METHOD(MakePathSignature_MultiBranchWithParamInBoth)
{
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/{p1}/{p2}"));
	TEST_ASSERT(U("{0}/{1}") == signPath, "make sign path failed");
}

TEST_METHOD(ParseParam_ZeroParamFailed)
{
	crab::RESTUriParser parser;
	auto& pattern = parser.getPattern();
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/path1"), &pattern);
	TEST_ASSERT(U("path1") == signPath, "make sign path failed");

	std::vector<TSTRING> params;
	bool res = parser.parseParams(U("path2"), params);
	TEST_ASSERT(res == false, "parse param should be failed");
}

TEST_METHOD(ParseParam_ZeroParam)
{
	crab::RESTUriParser parser;
	auto& pattern = parser.getPattern();
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/path"), &pattern);
	TEST_ASSERT(U("path") == signPath, "make sign path failed");

	std::vector<TSTRING> params;
	bool res = parser.parseParams(U("path"), params);
	TEST_ASSERT(res, "parse param should be success");
	TEST_ASSERT(0  == (int)params.size(), "param count should be zero");
}

TEST_METHOD(ParseParam_OneParam1)
{
	crab::RESTUriParser parser;
	auto& pattern = parser.getPattern();
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/{p1}"), &pattern);
	TEST_ASSERT(U("{0}") == signPath, "make sign path failed");

	std::vector<TSTRING> params;
	bool res = parser.parseParams(U("param1"), params);
	TEST_ASSERT(res, "parse param should be success");
	TEST_ASSERT(1 == (int)params.size(), "param count should be 1");
	TEST_ASSERT(U("param1") == params[0], "parse param should be success");
}

TEST_METHOD(ParseParam_OneParam2)
{
	crab::RESTUriParser parser;
	auto& pattern = parser.getPattern();
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/path/{p1}"), &pattern);
	TEST_ASSERT(U("path/{0}") == signPath, "make sign path failed");

	std::vector<TSTRING> params;
	bool res = parser.parseParams(U("path/param1"), params);
	TEST_ASSERT(res, "parse param should be success");
	TEST_ASSERT(1 == (int)params.size(), "param count should be 1");
	TEST_ASSERT(U("param1") == params[0], "parse param should be success");
}

TEST_METHOD(ParseParam_OneParam3)
{
	crab::RESTUriParser parser;
	auto& pattern = parser.getPattern();
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("{p1}/path"), &pattern);
	TEST_ASSERT(U("{0}/path") == signPath, "make sign path failed");

	std::vector<TSTRING> params;
	bool res = parser.parseParams(U("param1/path"), params);
	TEST_ASSERT(res, "parse param should be success");
	TEST_ASSERT(1 == (int)params.size(), "param count should be 1");
	TEST_ASSERT(U("param1") == params[0], "parse param should be success");
}

TEST_METHOD(ParseParam_OneParamFailed)
{
	crab::RESTUriParser parser;
	auto& pattern = parser.getPattern();
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/path1/{p1}"), &pattern);
	TEST_ASSERT(U("path1/{0}") == signPath, "make sign path failed");

	std::vector<TSTRING> params;
	bool res = parser.parseParams(U("/path2/{p1}"), params);
	TEST_ASSERT(res == false, "parse param should be failed");
}

TEST_METHOD(ParseParam_TwoParam1)
{
	crab::RESTUriParser parser;
	auto& pattern = parser.getPattern();
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("{p1}/{p2}"), &pattern);
	TEST_ASSERT(U("{0}/{1}") == signPath, "make sign path failed");

	std::vector<TSTRING> params;
	bool res = parser.parseParams(U("param1/param2"), params);
	TEST_ASSERT(res, "parse param should be success");
	TEST_ASSERT(2 == (int)params.size(), "param count should be 2");
	TEST_ASSERT(U("param1") == params[0], "parse param should be success");
	TEST_ASSERT(U("param2") == params[1], "parse param should be success");
}

TEST_METHOD(ParseParam_TwoParam2)
{
	crab::RESTUriParser parser;
	auto& pattern = parser.getPattern();
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("{p1}/{p2}/path"), &pattern);
	TEST_ASSERT(U("{0}/{1}/path") == signPath, "make sign path failed");

	std::vector<TSTRING> params;
	bool res = parser.parseParams(U("param1/param2//path"), params);
	TEST_ASSERT(res, "parse param should be success");
	TEST_ASSERT(2 == (int)params.size(), "param count should be 2");
	TEST_ASSERT(U("param1") == params[0], "parse param should be success");
	TEST_ASSERT(U("param2") == params[1], "parse param should be success");
}

TEST_METHOD(ParseParam_TwoParam3)
{
	crab::RESTUriParser parser;
	auto& pattern = parser.getPattern();
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("path1/{p1}/{p2}/path2"), &pattern);
	TEST_ASSERT(U("path1/{0}/{1}/path2") == signPath, "make sign path failed");

	std::vector<TSTRING> params;
	bool res = parser.parseParams(U("/path1/param1/param2//path2"), params);
	TEST_ASSERT(res, "parse param should be success");
	TEST_ASSERT(2 == (int)params.size(), "param count should be 2");
	TEST_ASSERT(U("param1") == params[0], "parse param should be success");
	TEST_ASSERT(U("param2") == params[1], "parse param should be success");
}

TEST_METHOD(ParseParam_TwoParam4)
{
	crab::RESTUriParser parser;
	auto& pattern = parser.getPattern();
	TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/{p1}/path1/{p2}/path2"), &pattern);
	TEST_ASSERT(U("{0}/path1/{1}/path2") == signPath, "make sign path failed");

	std::vector<TSTRING> params;
	bool res = parser.parseParams(U("/param1/path1//param2/path2"), params);
	TEST_ASSERT(res, "parse param should be success");
	TEST_ASSERT(2 == (int)params.size(), "param count should be 2");
	TEST_ASSERT(U("param1") == params[0], "parse param should be success");
	TEST_ASSERT(U("param2") == params[1], "parse param should be success");
}