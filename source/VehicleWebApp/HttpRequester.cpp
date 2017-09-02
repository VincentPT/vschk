#include "WebAppMacros.h"

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

// must include after cpp rest headers
#include "HttpRequester.h"

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams


HttpRequester::HttpRequester() {}
HttpRequester::~HttpRequester() {}

void HttpRequester::sendGet(const TSTRING& url, const ReponseHandler& f) {
	http_client client(url);
	auto response = client.request(methods::GET).get();
	if (response.status_code() == status_codes::OK) {
		f(response);
	}
}

void HttpRequester::sendPost(const TSTRING& url, const JsonRequestObject& content, const ReponseHandler& f) {
	http_client client(url);
	
	auto response = client.request(methods::POST,U(""), content).get();
	if (response.status_code() == status_codes::OK) {
		f(response);
	}
}