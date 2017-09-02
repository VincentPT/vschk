#include "stdafx.h"
#include "CppUnitTest.h"
#include "VehicleServices\web_common.h"
#include "VehicleServices\ServiceEngine.h"
#include "VehicleServices\HttpHandler.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace crab;

namespace VehicleServicesUT
{		
	TEST_CLASS(ServiceEngineUT)
	{
	public:
		
		TEST_METHOD(SetHandler1)
		{
			auto engine = ServiceEngine::getInstance();
			auto handlerRef1 = std::make_shared<HttpHandler>();
			bool res1 = engine->setHandler(U("/path1"), handlerRef1);

			auto handlerRef2 = std::make_shared<HttpHandler>();
			bool res2 = engine->setHandler(U("/path1"), handlerRef2);

			Assert::IsTrue(res1, L"register handler for path1 should be success");
			Assert::IsFalse(res2, L"register handler for same path should be failed");

			auto removeHandler = engine->removeHandler(U("/path1"));
			Assert::AreEqual((size_t)handlerRef1.get(), (size_t)removeHandler.get(), L"registered handler should be found");
		}

		TEST_METHOD(SetHandler2)
		{
			auto engine = ServiceEngine::getInstance();
			auto handlerRef1 = std::make_shared<HttpHandler>();
			bool res1 = engine->setHandler(U("/path1"), handlerRef1);

			auto handlerRef2 = std::make_shared<HttpHandler>();
			bool res2 = engine->setHandler(U("/path1"), handlerRef2);

			Assert::IsTrue(res1, L"register handler for path1 should be success");
			Assert::IsFalse(res2, L"register handler for same path should be failed");

			auto removeHandler = engine->removeHandler(U("/path1"));
			Assert::AreEqual((size_t)handlerRef1.get(), (size_t)removeHandler.get(), L"registered handler should be found");
		}

		TEST_METHOD(SetHandler3)
		{
			auto engine = ServiceEngine::getInstance();
			auto handlerRef1 = std::make_shared<HttpHandler>();
			bool res1 = engine->setHandler(U("/path1"), handlerRef1);

			auto handlerRef2 = std::make_shared<HttpHandler>();
			bool res2 = engine->setHandler(U("/path1/path2"), handlerRef2);

			Assert::IsTrue(res1, L"register handler for path1 should be success");
			Assert::IsTrue(res2, L"register handler for path1/path2 should be success");

			auto removeHandler1 = engine->removeHandler(U("/path1"));
			Assert::AreEqual((size_t)handlerRef1.get(), (size_t)removeHandler1.get(), L"registered handler should be found");

			auto removeHandler2 = engine->removeHandler(U("/path1/path2"));
			Assert::AreEqual((size_t)handlerRef2.get(), (size_t)removeHandler2.get(), L"registered handler should be found");
		}

		TEST_METHOD(SetHandler4)
		{
			auto engine = ServiceEngine::getInstance();
			auto handlerRef1 = std::make_shared<HttpHandler>();
			bool res1 = engine->setHandler(U("/path1"), handlerRef1);

			auto handlerRef2 = std::make_shared<HttpHandler>();
			bool res2 = engine->setHandler(U("/path2"), handlerRef2);

			Assert::IsTrue(res1, L"register handler for path1 should be success");
			Assert::IsTrue(res2, L"register handler for path2 should be success");

			auto removeHandler1 = engine->removeHandler(U("/path1"));
			Assert::AreEqual((size_t)handlerRef1.get(), (size_t)removeHandler1.get(), L"registered handler should be found");

			auto removeHandler2 = engine->removeHandler(U("/path2"));
			Assert::AreEqual((size_t)handlerRef2.get(), (size_t)removeHandler2.get(), L"registered handler should be found");
		}

		TEST_METHOD(GetHandler1)
		{
			auto engine = ServiceEngine::getInstance();
			auto handlerRef1 = std::make_shared<HttpHandler>();
			bool res1 = engine->setHandler(U("/path1"), handlerRef1);
			Assert::IsTrue(res1, L"register handler for path1 should be success");
			
			std::vector<TSTRING> params;
			auto removeHandler1 = engine->getHandler(U("/path1"), &params);
			Assert::AreEqual((size_t)handlerRef1.get(), (size_t)removeHandler1.get(), L"registered handler should be found");
			Assert::AreEqual(0, (int)params.size(), L"param count should be zero");

			removeHandler1 = engine->removeHandler(U("/path1"));
			Assert::AreEqual((size_t)handlerRef1.get(), (size_t)removeHandler1.get(), L"registered handler should be removed");
		}

		TEST_METHOD(GetHandler2)
		{
			auto engine = ServiceEngine::getInstance();
			auto handlerRef1 = std::make_shared<HttpHandler>();
			bool res1 = engine->setHandler(U("/path1"), handlerRef1);

			auto handlerRef2 = std::make_shared<HttpHandler>();
			bool res2 = engine->setHandler(U("/path2"), handlerRef2);

			Assert::IsTrue(res1, L"register handler for path1 should be success");
			Assert::IsTrue(res2, L"register handler for path2 should be success");

			std::vector<TSTRING> params;
			auto removeHandler1 = engine->getHandler(U("/path1"), &params);
			Assert::AreEqual((size_t)handlerRef1.get(), (size_t)removeHandler1.get(), L"registered handler should be found");
			Assert::AreEqual(0, (int)params.size(), L"param count should be zero");

			auto removeHandler2 = engine->getHandler(U("/path2"), &params);
			Assert::AreEqual((size_t)handlerRef2.get(), (size_t)removeHandler2.get(), L"registered handler should be found");
			Assert::AreEqual(0, (int)params.size(), L"param count should be zero");

			removeHandler1 = engine->removeHandler(U("/path1"));
			Assert::AreEqual((size_t)handlerRef1.get(), (size_t)removeHandler1.get(), L"registered handler should be removed");

			removeHandler2 = engine->removeHandler(U("/path2"));
			Assert::AreEqual((size_t)handlerRef2.get(), (size_t)removeHandler2.get(), L"registered handler should be removed");
		}

		TEST_METHOD(GetHandler_withParams1)
		{
			auto engine = ServiceEngine::getInstance();
			auto handlerRef1 = std::make_shared<HttpHandler>();
			bool res1 = engine->setHandler(U("/path1/{p1}"), handlerRef1);
			
			Assert::IsTrue(res1, L"register handler for path1 should be success");

			std::vector<TSTRING> params;
			auto removeHandler1 = engine->getHandler(U("/path1/param1"), &params);
			Assert::AreEqual((size_t)handlerRef1.get(), (size_t)removeHandler1.get(), L"registered handler should be found");
			Assert::AreEqual(1, (int)params.size(), L"param count should be 1");
			Assert::AreEqual(U("param1"), params[0].c_str(), L"parse param failed");

			removeHandler1 = engine->removeHandler(U("/path1/{p1}"));
			Assert::AreEqual((size_t)handlerRef1.get(), (size_t)removeHandler1.get(), L"registered handler should be removed");
		}

		TEST_METHOD(GetHandler_withParams2)
		{
			auto engine = ServiceEngine::getInstance();
			auto handlerRef1 = std::make_shared<HttpHandler>();
			bool res1 = engine->setHandler(U("/{p1}/path"), handlerRef1);

			Assert::IsTrue(res1, L"register handler for path1 should be success");

			std::vector<TSTRING> params;
			auto removeHandler1 = engine->getHandler(U("/param1/path"), &params);
			Assert::AreEqual((size_t)handlerRef1.get(), (size_t)removeHandler1.get(), L"registered handler should be found");
			Assert::AreEqual(1, (int)params.size(), L"param count should be 1");
			Assert::AreEqual(U("param1"), params[0].c_str(), L"parse param failed");

			removeHandler1 = engine->removeHandler(U("/{p1}/path"));
			Assert::AreEqual((size_t)handlerRef1.get(), (size_t)removeHandler1.get(), L"registered handler should be removed");
		}

		TEST_METHOD(GetHandler_withParams3)
		{
			auto engine = ServiceEngine::getInstance();
			auto handlerRef1 = std::make_shared<HttpHandler>();
			bool res1 = engine->setHandler(U("/{p1}/{p2}"), handlerRef1);

			Assert::IsTrue(res1, L"register handler for path1 should be success");

			std::vector<TSTRING> params;
			auto removeHandler1 = engine->getHandler(U("/param1/param2"), &params);
			Assert::AreEqual((size_t)handlerRef1.get(), (size_t)removeHandler1.get(), L"registered handler should be found");
			Assert::AreEqual(2, (int)params.size(), L"param count should be 1");
			Assert::AreEqual(U("param1"), params[0].c_str(), L"parse param failed");
			Assert::AreEqual(U("param2"), params[1].c_str(), L"parse param failed");

			removeHandler1 = engine->removeHandler(U("{p1}/{p2}"));
			Assert::AreEqual((size_t)handlerRef1.get(), (size_t)removeHandler1.get(), L"registered handler should be removed");
		}
	};
}