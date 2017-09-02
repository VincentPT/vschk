#pragma once
#include <map>
#include <list>
#include <vector>
#include <string>
#include <tuple>
#include "CrabInterfaces.h"
#include "RESTUriParser.h"
#include <functional>


namespace crab {
	typedef std::function<void(http_request&, HttpHandler*, const std::vector<TSTRING>&)> RequestHandler;
	typedef std::map<TSTRING, HttpHandlerRef> RelURIHandlerMap;
	typedef std::map<RESTUriParserRef, HttpHandlerRef, CompareParserRef> PathHandlerMap;
	class web::http::experimental::listener::http_listener;
	typedef std::tuple<int, const TSTRING*, HttpHandler*> PathInfo;
#define MakePathInfo std::make_tuple
	class ServiceEngine
	{
		//map between a relative uri to and handler object
		PathHandlerMap _handlers;
		/*std::list<PathInfo> _pathInfoBuilerList;
		std::vector<PathInfo*> _pathInfoSearchList;*/
		http_listener* _listener;
		int _port;
	protected:
		ServiceEngine();

		void createListener();
		void handle_request(http_request& message, const RequestHandler& requestHandler);
	protected:
#pragma region http supported methods
		void handle_get(http_request message);
		void handle_put(http_request message);
		void handle_post(http_request message);
		void handle_delete(http_request message);
		void handle_head(http_request message);
		void handle_options(http_request message);
		void handle_trace(http_request message);
		void handle_connect(http_request message);
		void handle_merge(http_request message);
		void handle_patch(http_request message);
#pragma endregion
	public:
		static ServiceEngine* getInstance();
		virtual ~ServiceEngine();

		void setListenPort(int port);
		void run();
		void stop();

		bool setHandler(const TSTRING& relative_uri, HttpHandlerRef handler);
		HttpHandlerRef removeHandler(const TSTRING& relative_uri);
		HttpHandlerRef getHandler(const TSTRING& relative_uri, std::vector<TSTRING>* params);
	};
}
