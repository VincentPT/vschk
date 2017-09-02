#include "RESTResponse.h"
#include <sstream>

#ifdef _UTF16_STRINGS
typedef std::wstringstream stream_t;
#else
typedef std::stringstream stream_t;
#endif // _UTF16_STRINGS

namespace crab {
	RESTResponse::RESTResponse() : _code(ResponseCode::Success)
	{
	}


	RESTResponse::~RESTResponse()
	{
	}

	RESTResponse& RESTResponse::success() {
		return *this;
	}

	RESTResponse& RESTResponse::fail(ResponseCode code, const TSTRING& message) {
		_code = code;
		_message = message;
		return *this;
	}

	RESTResponse& RESTResponse::result(const TSTRING& result) {
		_result = result;
		return *this;
	}

	RESTResponse& RESTResponse::result(TSTRING&& result) {
		_result = result;
		return *this;
	}

	ResponseCode RESTResponse::getCode() const {
		return _code;
	}

	const TSTRING& RESTResponse::getMessage() const {
		return _message;
	}

	const TSTRING& RESTResponse::getResult() const {
		return _result;
	}

	TSTRING RESTResponse::toString() const {
		stream_t ss;
		ss << "{\n\t\"code\":" << (int)_code
			<< ",\n\t\"message\":\"" << _message
			<< "\",\n\t\"result\":" << _result
			<< "\n}";

		return ss.str();
	}
}