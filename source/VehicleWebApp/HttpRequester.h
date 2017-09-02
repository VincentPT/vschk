#pragma once
#include <functional>
#include <string>

namespace web { namespace http { class http_response;} }
namespace web { namespace json { class value; } }
typedef web::json::value JsonRequestObject;

typedef std::function<void(const web::http::http_response&)> ReponseHandler;
class HttpRequester
{
public:
	HttpRequester();
	~HttpRequester();

	void sendGet(const TSTRING& url, const ReponseHandler& f);
	void sendPost(const TSTRING& url, const JsonRequestObject& content, const ReponseHandler& f);
};

