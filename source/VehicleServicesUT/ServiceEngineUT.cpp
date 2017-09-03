#include "VehicleServicesUTMacros.h"
#include "VehicleServices\web_common.h"
#include "VehicleServices\ServiceEngine.h"
#include "VehicleServices\HttpHandler.h"

using namespace crab;
		
TEST_METHOD(SetHandler1)
{
	auto engine = ServiceEngine::getInstance();
	auto handlerRef1 = std::make_shared<HttpHandler>();
	bool res1 = engine->setHandler(U("/path1"), handlerRef1);

	auto handlerRef2 = std::make_shared<HttpHandler>();
	bool res2 = engine->setHandler(U("/path1"), handlerRef2);

	TEST_ASSERT(res1, "register handler for path1 should be success");
	TEST_ASSERT(res2 == false, "register handler for same path should be failed");

	auto removeHandler = engine->removeHandler(U("/path1"));
	TEST_ASSERT((size_t)handlerRef1.get() == (size_t)removeHandler.get(), "registered handler should be found");
}

TEST_METHOD(SetHandler2)
{
	auto engine = ServiceEngine::getInstance();
	auto handlerRef1 = std::make_shared<HttpHandler>();
	bool res1 = engine->setHandler(U("/path1"), handlerRef1);

	auto handlerRef2 = std::make_shared<HttpHandler>();
	bool res2 = engine->setHandler(U("/path1"), handlerRef2);

	TEST_ASSERT(res1, "register handler for path1 should be success");
	TEST_ASSERT(res2 == false, "register handler for same path should be failed");

	auto removeHandler = engine->removeHandler(U("/path1"));
	TEST_ASSERT((size_t)handlerRef1.get() == (size_t)removeHandler.get(), "registered handler should be found");
}

TEST_METHOD(SetHandler3)
{
	auto engine = ServiceEngine::getInstance();
	auto handlerRef1 = std::make_shared<HttpHandler>();
	bool res1 = engine->setHandler(U("/path1"), handlerRef1);

	auto handlerRef2 = std::make_shared<HttpHandler>();
	bool res2 = engine->setHandler(U("/path1/path2"), handlerRef2);

	TEST_ASSERT(res1, "register handler for path1 should be success");
	TEST_ASSERT(res2, "register handler for path1/path2 should be success");

	auto removeHandler1 = engine->removeHandler(U("/path1"));
	TEST_ASSERT((size_t)handlerRef1.get() == (size_t)removeHandler1.get(), "registered handler should be found");

	auto removeHandler2 = engine->removeHandler(U("/path1/path2"));
	TEST_ASSERT((size_t)handlerRef2.get() == (size_t)removeHandler2.get(), "registered handler should be found");
}

TEST_METHOD(SetHandler4)
{
	auto engine = ServiceEngine::getInstance();
	auto handlerRef1 = std::make_shared<HttpHandler>();
	bool res1 = engine->setHandler(U("/path1"), handlerRef1);

	auto handlerRef2 = std::make_shared<HttpHandler>();
	bool res2 = engine->setHandler(U("/path2"), handlerRef2);

	TEST_ASSERT(res1, "register handler for path1 should be success");
	TEST_ASSERT(res2, "register handler for path2 should be success");

	auto removeHandler1 = engine->removeHandler(U("/path1"));
	TEST_ASSERT((size_t)handlerRef1.get() == (size_t)removeHandler1.get(), "registered handler should be found");

	auto removeHandler2 = engine->removeHandler(U("/path2"));
	TEST_ASSERT((size_t)handlerRef2.get() == (size_t)removeHandler2.get(), "registered handler should be found");
}

TEST_METHOD(GetHandler1)
{
	auto engine = ServiceEngine::getInstance();
	auto handlerRef1 = std::make_shared<HttpHandler>();
	bool res1 = engine->setHandler(U("/path1"), handlerRef1);
	TEST_ASSERT(res1, "register handler for path1 should be success");
			
	std::vector<TSTRING> params;
	auto removeHandler1 = engine->getHandler(U("/path1"), &params);
	TEST_ASSERT((size_t)handlerRef1.get() == (size_t)removeHandler1.get(), "registered handler should be found");
	TEST_ASSERT(0 == (int)params.size(), "param count should be zero");

	removeHandler1 = engine->removeHandler(U("/path1"));
	TEST_ASSERT((size_t)handlerRef1.get() == (size_t)removeHandler1.get(), "registered handler should be removed");
}

TEST_METHOD(GetHandler2)
{
	auto engine = ServiceEngine::getInstance();
	auto handlerRef1 = std::make_shared<HttpHandler>();
	bool res1 = engine->setHandler(U("/path1"), handlerRef1);

	auto handlerRef2 = std::make_shared<HttpHandler>();
	bool res2 = engine->setHandler(U("/path2"), handlerRef2);

	TEST_ASSERT(res1, "register handler for path1 should be success");
	TEST_ASSERT(res2, "register handler for path2 should be success");

	std::vector<TSTRING> params;
	auto removeHandler1 = engine->getHandler(U("/path1"), &params);
	TEST_ASSERT((size_t)handlerRef1.get() == (size_t)removeHandler1.get(), "registered handler should be found");
	TEST_ASSERT(0 == (int)params.size(), "param count should be zero");

	auto removeHandler2 = engine->getHandler(U("/path2"), &params);
	TEST_ASSERT((size_t)handlerRef2.get() == (size_t)removeHandler2.get(), "registered handler should be found");
	TEST_ASSERT(0 == (int)params.size(), "param count should be zero");

	removeHandler1 = engine->removeHandler(U("/path1"));
	TEST_ASSERT((size_t)handlerRef1.get() == (size_t)removeHandler1.get(), "registered handler should be removed");

	removeHandler2 = engine->removeHandler(U("/path2"));
	TEST_ASSERT((size_t)handlerRef2.get() == (size_t)removeHandler2.get(), "registered handler should be removed");
}

TEST_METHOD(GetHandler_withParams1)
{
	auto engine = ServiceEngine::getInstance();
	auto handlerRef1 = std::make_shared<HttpHandler>();
	bool res1 = engine->setHandler(U("/path1/{p1}"), handlerRef1);
			
	TEST_ASSERT(res1, "register handler for path1 should be success");

	std::vector<TSTRING> params;
	auto removeHandler1 = engine->getHandler(U("/path1/param1"), &params);
	TEST_ASSERT((size_t)handlerRef1.get() == (size_t)removeHandler1.get(), "registered handler should be found");
	TEST_ASSERT(1 == (int)params.size(), "param count should be 1");
	TEST_ASSERT(U("param1") == params[0], "parse param failed");

	removeHandler1 = engine->removeHandler(U("/path1/{p1}"));
	TEST_ASSERT((size_t)handlerRef1.get() == (size_t)removeHandler1.get(), "registered handler should be removed");
}

TEST_METHOD(GetHandler_withParams2)
{
	auto engine = ServiceEngine::getInstance();
	auto handlerRef1 = std::make_shared<HttpHandler>();
	bool res1 = engine->setHandler(U("/{p1}/path"), handlerRef1);

	TEST_ASSERT(res1, "register handler for path1 should be success");

	std::vector<TSTRING> params;
	auto removeHandler1 = engine->getHandler(U("/param1/path"), &params);
	TEST_ASSERT((size_t)handlerRef1.get() == (size_t)removeHandler1.get(), "registered handler should be found");
	TEST_ASSERT(1 == (int)params.size(), "param count should be 1");
	TEST_ASSERT(U("param1") == params[0], "parse param failed");

	removeHandler1 = engine->removeHandler(U("/{p1}/path"));
	TEST_ASSERT((size_t)handlerRef1.get() == (size_t)removeHandler1.get(), "registered handler should be removed");
}

TEST_METHOD(GetHandler_withParams3)
{
	auto engine = ServiceEngine::getInstance();
	auto handlerRef1 = std::make_shared<HttpHandler>();
	bool res1 = engine->setHandler(U("/{p1}/{p2}"), handlerRef1);

	TEST_ASSERT(res1, "register handler for path1 should be success");

	std::vector<TSTRING> params;
	auto removeHandler1 = engine->getHandler(U("/param1/param2"), &params);
	TEST_ASSERT((size_t)handlerRef1.get() == (size_t)removeHandler1.get(), "registered handler should be found");
	TEST_ASSERT(2 == (int)params.size(), "param count should be 1");
	TEST_ASSERT(U("param1") == params[0], "parse param failed");
	TEST_ASSERT(U("param2") == params[1], "parse param failed");

	removeHandler1 = engine->removeHandler(U("{p1}/{p2}"));
	TEST_ASSERT((size_t)handlerRef1.get() == (size_t)removeHandler1.get(), "registered handler should be removed");
}