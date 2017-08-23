#pragma once
#include "web_common.h"

namespace crab {

	enum class ResponseCode : int {
		Success = 0,
		BadParameters,
		Unauthorzied,
	};

	class RESTResponse
	{
		ResponseCode _code;
		TSTRING _message;
		TSTRING _result;
	public:
		RESTResponse();
		virtual ~RESTResponse();

		RESTResponse& success();
		RESTResponse& fail(ResponseCode code, const TSTRING& message);
		RESTResponse& result(const TSTRING& result);
		RESTResponse& result(TSTRING&& result);

		ResponseCode getCode() const;
		const TSTRING& getMessage() const;
		const TSTRING& getResult() const;
		TSTRING toString() const;
	};
}
