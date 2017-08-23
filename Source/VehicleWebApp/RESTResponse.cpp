#include "RESTResponse.h"
#include <sstream>
#include <Wt/Json/Array>
#include <Wt/Json/Value>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>

namespace crab {
	namespace client {
		RESTResponse::RESTResponse() : _code(ResponseCode::Success)
		{
		}

		RESTResponse::~RESTResponse()
		{
		}

		ResponseCode RESTResponse::getCode() const {
			return _code;
		}

		const std::string& RESTResponse::getMessage() const {
			return _message;
		}

		const Wt::Json::Value& RESTResponse::getResult() const {
			return _result;
		}

		void RESTResponse::fromJson(const std::string& s) {
			Wt::Json::Object response;
			Wt::Json::parse(s, response);

			if (response.contains("code")) {
				_code = (ResponseCode)(int)response.get("code");
			}
			if (response.contains("message")) {
				_message = response.get("message");
			}
			if (response.contains("result")) {
				_result = response.get("result");
			}
		}
	}
}