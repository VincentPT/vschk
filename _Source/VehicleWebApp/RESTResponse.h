#pragma once
#include <string>
#include <Wt/Json/Value>

namespace crab {
	enum class ResponseCode : int {
		Success = 0,
		BadParameters,
		Unauthorzied,
	};

	namespace client {
		class RESTResponse
		{
			ResponseCode _code;
			std::string _message;
			Wt::Json::Value _result;
		public:
			RESTResponse();
			virtual ~RESTResponse();

			ResponseCode getCode() const;
			const std::string& getMessage() const;
			const Wt::Json::Value& getResult() const;
			void fromJson(const std::string& s);
		};
	}
}
