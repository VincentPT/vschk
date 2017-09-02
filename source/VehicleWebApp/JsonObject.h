#pragma once
#include <string>

namespace Wt { namespace Json { class Object; } }
typedef Wt::Json::Object JSON_T;

class JsonObject
{
public:
	JsonObject();
	~JsonObject();

	virtual void fromJsonObject(const JSON_T&) = 0;
	virtual void toJsonObject(JSON_T& value) const = 0;
};

