#include "web_common.h"
#include "HttpHandler.h"

namespace crab {
	HttpHandler::HttpHandler() {}
	HttpHandler::~HttpHandler() {}

	void HttpHandler::doGet(http_request& message, const std::vector<TSTRING>& params) {
		RAISE_UNSUPPORT_METHOD();
	}

	void HttpHandler::doPut(http_request& message, const std::vector<TSTRING>& params) {
		RAISE_UNSUPPORT_METHOD();
	}

	void HttpHandler::doPost(http_request& message, const std::vector<TSTRING>& params) {
		RAISE_UNSUPPORT_METHOD();
	}

	void HttpHandler::doDelete(http_request& message, const std::vector<TSTRING>& params) {
		RAISE_UNSUPPORT_METHOD();
	}

	void HttpHandler::doHead(http_request& message, const std::vector<TSTRING>& params) {
		RAISE_UNSUPPORT_METHOD();
	}

	void HttpHandler::doOptions(http_request& message, const std::vector<TSTRING>& params) {
		RAISE_UNSUPPORT_METHOD();
	}

	void HttpHandler::doTrace(http_request& message, const std::vector<TSTRING>& params) {
		RAISE_UNSUPPORT_METHOD();
	}

	void HttpHandler::doConnect(http_request& message, const std::vector<TSTRING>& params) {
		RAISE_UNSUPPORT_METHOD();
	}

	void HttpHandler::doMerge(http_request& message, const std::vector<TSTRING>& params) {
		RAISE_UNSUPPORT_METHOD();
	}

	void HttpHandler::doPatch(http_request& message, const std::vector<TSTRING>& params) {
		RAISE_UNSUPPORT_METHOD();
	}
}