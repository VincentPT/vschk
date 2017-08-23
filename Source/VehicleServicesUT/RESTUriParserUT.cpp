#include "stdafx.h"
#include "CppUnitTest.h"
#include "VehicleServices\web_common.h"
#include "VehicleServices\RESTUriParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace crab;

namespace VehicleServicesUT
{		
	TEST_CLASS(RESTUriParserUT)
	{
	public:
		
		TEST_METHOD(MakePathSignature_Empty)
		{
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U(""));
			Assert::AreEqual(U(""), signPath.c_str(), L"make sign path failed");
		}

		TEST_METHOD(MakePathSignature_OnlyFlashBegin)
		{
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/"));
			Assert::AreEqual(U(""), signPath.c_str(), L"make sign path failed");
		}

		TEST_METHOD(MakePathSignature_FlashBegin)
		{
			TSTRING signPath =  crab::RESTUriParser::makePathSignature(U("/path"));
			Assert::AreEqual(U("path"), signPath.c_str(), L"make sign path failed");
		}

		TEST_METHOD(MakePathSignature_FlashEnd)
		{
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("path/"));
			Assert::AreEqual(U("path"), signPath.c_str(), L"make sign path failed");
		}

		TEST_METHOD(MakePathSignature_FlashBeginEnd)
		{
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/path/"));
			Assert::AreEqual(U("path"), signPath.c_str(), L"make sign path failed");
		}

		TEST_METHOD(MakePathSignature_MultiBranch)
		{
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/path1/path2"));
			Assert::AreEqual(U("path1/path2"), signPath.c_str(), L"make sign path failed");
		}

		TEST_METHOD(MakePathSignature_MultiBranchWithParamAt1)
		{
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/{p1}/path"));
			Assert::AreEqual(U("{0}/path"), signPath.c_str(), L"make sign path failed");
		}

		TEST_METHOD(MakePathSignature_MultiBranchWithParamAt2)
		{
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/path/{p2}"));
			Assert::AreEqual(U("path/{0}"), signPath.c_str(), L"make sign path failed");
		}

		TEST_METHOD(MakePathSignature_MultiBranchWithParamInBoth)
		{
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/{p1}/{p2}"));
			Assert::AreEqual(U("{0}/{1}"), signPath.c_str(), L"make sign path failed");
		}

		TEST_METHOD(ParseParam_ZeroParamFailed)
		{
			crab::RESTUriParser parser;
			auto& pattern = parser.getPattern();
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/path1"), &pattern);
			Assert::AreEqual(U("path1"), signPath.c_str(), L"make sign path failed");

			std::vector<TSTRING> params;
			bool res = parser.parseParams(U("path2"), params);
			Assert::IsFalse(res, L"parse param should be failed");
		}

		TEST_METHOD(ParseParam_ZeroParam)
		{
			crab::RESTUriParser parser;
			auto& pattern = parser.getPattern();
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/path"), &pattern);
			Assert::AreEqual(U("path"), signPath.c_str(), L"make sign path failed");

			std::vector<TSTRING> params;
			bool res = parser.parseParams(U("path"), params);
			Assert::IsTrue(res, L"parse param should be success");
			Assert::AreEqual(0, (int)params.size(), L"param count should be zero");
		}

		TEST_METHOD(ParseParam_OneParam1)
		{
			crab::RESTUriParser parser;
			auto& pattern = parser.getPattern();
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/{p1}"), &pattern);
			Assert::AreEqual(U("{0}"), signPath.c_str(), L"make sign path failed");

			std::vector<TSTRING> params;
			bool res = parser.parseParams(U("param1"), params);
			Assert::IsTrue(res, L"parse param should be success");
			Assert::AreEqual(1, (int)params.size(), L"param count should be 1");
			Assert::AreEqual(U("param1"), params[0].c_str(), L"parse param should be success");
		}

		TEST_METHOD(ParseParam_OneParam2)
		{
			crab::RESTUriParser parser;
			auto& pattern = parser.getPattern();
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/path/{p1}"), &pattern);
			Assert::AreEqual(U("path/{0}"), signPath.c_str(), L"make sign path failed");

			std::vector<TSTRING> params;
			bool res = parser.parseParams(U("path/param1"), params);
			Assert::IsTrue(res, L"parse param should be success");
			Assert::AreEqual(1, (int)params.size(), L"param count should be 1");
			Assert::AreEqual(U("param1"), params[0].c_str(), L"parse param should be success");
		}

		TEST_METHOD(ParseParam_OneParam3)
		{
			crab::RESTUriParser parser;
			auto& pattern = parser.getPattern();
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("{p1}/path"), &pattern);
			Assert::AreEqual(U("{0}/path"), signPath.c_str(), L"make sign path failed");

			std::vector<TSTRING> params;
			bool res = parser.parseParams(U("param1/path"), params);
			Assert::IsTrue(res, L"parse param should be success");
			Assert::AreEqual(1, (int)params.size(), L"param count should be 1");
			Assert::AreEqual(U("param1"), params[0].c_str(), L"parse param should be success");
		}

		TEST_METHOD(ParseParam_OneParamFailed)
		{
			crab::RESTUriParser parser;
			auto& pattern = parser.getPattern();
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/path1/{p1}"), &pattern);
			Assert::AreEqual(U("path1/{0}"), signPath.c_str(), L"make sign path failed");

			std::vector<TSTRING> params;
			bool res = parser.parseParams(U("/path2/{p1}"), params);
			Assert::IsFalse(res, L"parse param should be failed");
		}

		TEST_METHOD(ParseParam_TwoParam1)
		{
			crab::RESTUriParser parser;
			auto& pattern = parser.getPattern();
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("{p1}/{p2}"), &pattern);
			Assert::AreEqual(U("{0}/{1}"), signPath.c_str(), L"make sign path failed");

			std::vector<TSTRING> params;
			bool res = parser.parseParams(U("param1/param2"), params);
			Assert::IsTrue(res, L"parse param should be success");
			Assert::AreEqual(2, (int)params.size(), L"param count should be 2");
			Assert::AreEqual(U("param1"), params[0].c_str(), L"parse param should be success");
			Assert::AreEqual(U("param2"), params[1].c_str(), L"parse param should be success");
		}

		TEST_METHOD(ParseParam_TwoParam2)
		{
			crab::RESTUriParser parser;
			auto& pattern = parser.getPattern();
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("{p1}/{p2}/path"), &pattern);
			Assert::AreEqual(U("{0}/{1}/path"), signPath.c_str(), L"make sign path failed");

			std::vector<TSTRING> params;
			bool res = parser.parseParams(U("param1/param2//path"), params);
			Assert::IsTrue(res, L"parse param should be success");
			Assert::AreEqual(2, (int)params.size(), L"param count should be 2");
			Assert::AreEqual(U("param1"), params[0].c_str(), L"parse param should be success");
			Assert::AreEqual(U("param2"), params[1].c_str(), L"parse param should be success");
		}

		TEST_METHOD(ParseParam_TwoParam3)
		{
			crab::RESTUriParser parser;
			auto& pattern = parser.getPattern();
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("path1/{p1}/{p2}/path2"), &pattern);
			Assert::AreEqual(U("path1/{0}/{1}/path2"), signPath.c_str(), L"make sign path failed");

			std::vector<TSTRING> params;
			bool res = parser.parseParams(U("/path1/param1/param2//path2"), params);
			Assert::IsTrue(res, L"parse param should be success");
			Assert::AreEqual(2, (int)params.size(), L"param count should be 2");
			Assert::AreEqual(U("param1"), params[0].c_str(), L"parse param should be success");
			Assert::AreEqual(U("param2"), params[1].c_str(), L"parse param should be success");
		}

		TEST_METHOD(ParseParam_TwoParam4)
		{
			crab::RESTUriParser parser;
			auto& pattern = parser.getPattern();
			TSTRING signPath = crab::RESTUriParser::makePathSignature(U("/{p1}/path1/{p2}/path2"), &pattern);
			Assert::AreEqual(U("{0}/path1/{1}/path2"), signPath.c_str(), L"make sign path failed");

			std::vector<TSTRING> params;
			bool res = parser.parseParams(U("/param1/path1//param2/path2"), params);
			Assert::IsTrue(res, L"parse param should be success");
			Assert::AreEqual(2, (int)params.size(), L"param count should be 2");
			Assert::AreEqual(U("param1"), params[0].c_str(), L"parse param should be success");
			Assert::AreEqual(U("param2"), params[1].c_str(), L"parse param should be success");
		}
	};
}