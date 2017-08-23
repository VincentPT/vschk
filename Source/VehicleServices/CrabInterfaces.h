#pragma once
#include <memory>
namespace crab {
	class HttpHandler;
	typedef std::shared_ptr<HttpHandler> HttpHandlerRef;
}