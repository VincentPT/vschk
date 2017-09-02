#pragma once
#include <vector>

#define RAISE_UNSUPPORT_METHOD() message.reply(status_codes::MethodNotAllowed)
#define RAISE_PATH_NOT_FOUND() message.reply(status_codes::NotFound)

namespace crab {
	class HttpHandler
	{
	public:
		HttpHandler();
		virtual ~HttpHandler();

		virtual void doGet(http_request& message, const std::vector<TSTRING>& params);
		virtual void doPut(http_request& message, const std::vector<TSTRING>& params);
		virtual void doPost(http_request& message, const std::vector<TSTRING>& params);
		virtual void doDelete(http_request& message, const std::vector<TSTRING>& params);
		virtual void doHead(http_request& message, const std::vector<TSTRING>& params);
		virtual void doOptions(http_request& message, const std::vector<TSTRING>& params);
		virtual void doTrace(http_request& message, const std::vector<TSTRING>& params);
		virtual void doConnect(http_request& message, const std::vector<TSTRING>& params);
		virtual void doMerge(http_request& message, const std::vector<TSTRING>& params);
		virtual void doPatch(http_request& message, const std::vector<TSTRING>& params);
	};
}
