#include "stdafx.h"
#include "web_common.h"
#include "HttpHandler.h"
#include "ServiceEngine.h"

namespace crab {
	ServiceEngine::ServiceEngine() : _listener(nullptr), _port(230617)
	{
	}

	ServiceEngine::~ServiceEngine()
	{
		if (_listener) {
			delete _listener;
		}
	}

	ServiceEngine* ServiceEngine::getInstance() {
		static ServiceEngine theEngine;
		return &theEngine;
	}

	void ServiceEngine::createListener() {
		if (_listener) return;
#if _WIN32
		web::uri theLisentUri(U("http://localhost:") + TO_STRING_T(_port));
#else
		web::uri theLisentUri(U("http://0.0.0.0:") + TO_STRING_T(_port));
#endif
		_listener = new http_listener(theLisentUri);

		_listener->support(methods::GET, std::bind(&ServiceEngine::handle_get, this, std::placeholders::_1));
		_listener->support(methods::PUT, std::bind(&ServiceEngine::handle_put, this, std::placeholders::_1));
		_listener->support(methods::POST, std::bind(&ServiceEngine::handle_post, this, std::placeholders::_1));
		_listener->support(methods::DEL, std::bind(&ServiceEngine::handle_delete, this, std::placeholders::_1));
		_listener->support(methods::HEAD, std::bind(&ServiceEngine::handle_head, this, std::placeholders::_1));
		_listener->support(methods::OPTIONS, std::bind(&ServiceEngine::handle_options, this, std::placeholders::_1));
		_listener->support(methods::TRCE, std::bind(&ServiceEngine::handle_trace, this, std::placeholders::_1));
		_listener->support(methods::CONNECT, std::bind(&ServiceEngine::handle_connect, this, std::placeholders::_1));
		_listener->support(methods::MERGE, std::bind(&ServiceEngine::handle_merge, this, std::placeholders::_1));
		_listener->support(methods::PATCH, std::bind(&ServiceEngine::handle_patch, this, std::placeholders::_1));
	}

	void ServiceEngine::setListenPort(int port) {
		_port = port;
	}

	void ServiceEngine::run() {	
		createListener();

		//build searching path for future handler search infuture
		/*_pathInfoSearchList.resize(_pathInfoBuilerList.size());
		auto sit = _pathInfoSearchList.begin();
		for (auto it = _pathInfoBuilerList.begin(); it != _pathInfoBuilerList.end(); it++) {
			*sit++ = &*it;
		}*/
	/*	std::sort(_pathInfoSearchList.begin(), _pathInfoSearchList.end(), [](PathInfo* path1, PathInfo* path2) {
			return std::get<0>(*path1) <= std::get<0>(*path2);
		});*/

		_listener->open().wait();
	}

	void ServiceEngine::stop() {
		if (_listener) {
			_listener->close().wait();
		}
	}

	int countLevel(const TSTRING& relative_uri) {
		auto pc = relative_uri.c_str();
		auto pc_end = pc + relative_uri.length();
		int level = 0;
		while (pc < pc_end) {
			if (*pc == '/') {
				pc++;
				while (pc < pc_end && *pc == '/') {
					pc++;
				}
				level++;
			}
			else {
				pc++;
			}
		}

		if (*(pc_end - 1) == '/') {
			level--;
		}

		return level;
	}

	bool ServiceEngine::setHandler(const TSTRING& relative_uri, HttpHandlerRef handler) {
		auto pathParserRef = std::make_shared<RESTUriParser>();
		auto& pattern = pathParserRef->getPattern();
		auto signPath = RESTUriParser::makePathSignature(relative_uri, &pattern);
		pathParserRef->setSignPath(signPath);
		
		for (auto it = _handlers.begin(); it != _handlers.end(); it++) {
			auto& registerParser = it->first;
			auto& registerPattern = registerParser->getPattern();
			if (registerParser->parseParams(pattern)) {
				return false;
			}
			if (pathParserRef->parseParams(registerPattern)) {
				return false;
			}
		}

		_handlers.insert(std::make_pair(pathParserRef, handler));
		return true;
	}


	PathHandlerMap::iterator findIterator(PathHandlerMap& handlers, const TSTRING& relative_uri, std::vector<TSTRING>* params) {
		auto pathParserRef = std::make_shared<RESTUriParser>();
		auto& pattern = pathParserRef->getPattern();
		auto signPath = RESTUriParser::makePathSignature(relative_uri, &pattern);

		auto it = handlers.find(pathParserRef);
		if (it != handlers.end()) {
			return it;
		}
		
		for (auto it = handlers.begin(); it != handlers.end(); it++) {
			auto& registerParser = it->first;
			if (registerParser->parseParams(pattern, params)) {
				return it;
			}
		}

		return handlers.end();
	}

	HttpHandlerRef ServiceEngine::getHandler(const TSTRING& relative_uri, std::vector<TSTRING>* params) {
		auto it = findIterator(_handlers, relative_uri, params);
		if (it != _handlers.end()) {
			return it->second;			
		}
		HttpHandlerRef empty_handler;
		return empty_handler;
	}

	HttpHandlerRef ServiceEngine::removeHandler(const TSTRING& relative_uri) {
		auto it = findIterator(_handlers, relative_uri, nullptr);
		HttpHandlerRef handler;
		if (it != _handlers.end()) {
			handler = it->second;
			_handlers.erase(it);
		}
		
		return handler;
	}

	void ServiceEngine::handle_request(http_request& message, const RequestHandler& requestHandler) {
		auto relative_uri = message.relative_uri();
		auto& path = relative_uri.path();
		CONSOLE_OUT_T << U("received request at") << path << std::endl;
		std::vector<TSTRING> params;
		auto handler = getHandler(path, &params);
		if (!handler) {
			RAISE_PATH_NOT_FOUND();
			return;
		}

		requestHandler(message, handler.get(), params);
	}

	void ServiceEngine::handle_get(http_request message) {
		handle_request(message, [](http_request& message, HttpHandler* handler, const std::vector<TSTRING>& params) {
			handler->doGet(message, params);
		});
	}

	void ServiceEngine::handle_post(http_request message) {
		handle_request(message, [](http_request& message, HttpHandler* handler, const std::vector<TSTRING>& params) {
			handler->doPost(message, params);
		});
	}

	void ServiceEngine::handle_delete(http_request message) {		
		handle_request(message, [](http_request& message, HttpHandler* handler, const std::vector<TSTRING>& params) {
			handler->doDelete(message, params);
		});
	}


	void ServiceEngine::handle_put(http_request message){
		handle_request(message, [](http_request& message, HttpHandler* handler, const std::vector<TSTRING>& params) {
			handler->doPut(message, params);
		});
	}

	void ServiceEngine::handle_head(http_request message) {
		handle_request(message, [](http_request& message, HttpHandler* handler, const std::vector<TSTRING>& params) {
			handler->doHead(message, params);
		});
	}

	void ServiceEngine::handle_options(http_request message) {
		handle_request(message, [](http_request& message, HttpHandler* handler, const std::vector<TSTRING>& params) {
			handler->doOptions(message, params);
		});
	}

	void ServiceEngine::handle_trace(http_request message) {
		handle_request(message, [](http_request& message, HttpHandler* handler, const std::vector<TSTRING>& params) {
			handler->doTrace(message, params);
		});
	}

	void ServiceEngine::handle_connect(http_request message) {
		handle_request(message, [](http_request& message, HttpHandler* handler, const std::vector<TSTRING>& params) {
			handler->doConnect(message, params);
		});
	}

	void ServiceEngine::handle_merge(http_request message) {
		handle_request(message, [](http_request& message, HttpHandler* handler, const std::vector<TSTRING>& params) {
			handler->doMerge(message, params);
		});
	}

	void ServiceEngine::handle_patch(http_request message) {
		handle_request(message, [](http_request& message, HttpHandler* handler, const std::vector<TSTRING>& params) {
			handler->doPatch(message, params);
		});
	}
}